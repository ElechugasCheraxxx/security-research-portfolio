# Ronda 2 — Devirtualización / Desobfuscación

**Fecha:** 2026-10-14 · Continuación de `INFORME_DESOFUSCACION.md`

## Resultado en una línea

Se ha **roto la capa de ofuscación** (API hashing + cifrado de cadenas) y se ha
**corregido un diagnóstico previo erróneo** sobre qué capas existen.

---

## 1. Corrección importante del diagnóstico anterior

En el informe anterior afirmé que el programa estaba "virtualizado" y que `.3q-` era
bytecode de una VM. **Eso era incorrecto.** La evidencia real:

| Sección | Contenido real |
|---|---|
| `.text` (94 KB) | **Aplicación C++ limpia de MSVC** — sin ofuscar, descompilable |
| `.7 f` inicio (212 KB) | CRT de MSVC (memcpy, `std::string`, TLS) |
| `.7 f` resto | 8 MB virtuales, solo parcialmente poblados |
| `.3q-` (7,4 MB) | **Segunda etapa**: contiene la detección de VM que aborta + el payload |

Datos que lo demuestran:
- El código ejecutado está en `.text` (**604 direcciones**), no en `.3q-` (**27**)
- Las APIs se llaman desde `.text`; `NtRaiseHardError` desde `.3q-` (`RVA 0xE38696`)
- `.text` descompila a C++ normal: `cmp [rdx+0x18], 7` (umbral SSO de `std::string`),
  `movabs rsi, 0x7ffffffffffffffe` (`std::string::max_size`)
- `.text` **no** descompila código con referencias al C2 → la lógica del cheat
  no está ahí

---

## 2. angr arreglado (recapitulación)

```bash
python3 -m venv --system-site-packages /tmp/opencode/angr-venv
/tmp/opencode/angr-venv/bin/pip install pycparser==2.22
/tmp/opencode/angr-venv/bin/python angr_shim.py unpacked_bypass.exe
```

Causa raíz: pycparser 3.11 eliminó `pycparser.ply` y `reset_lineno()`, y volvió
`CLexer.filename` read-only. Complemento: shim que inyecta `PEStubs` (ausente en
cle 9.2.160 de Arch; angr solo lo usa en dos `isinstance()`).

`pip install angr==9.2.194` **no sirve**: compila libvex y el build aislado reintroduce
pycparser 3.x.

---

## 3. API hashing FNV-1a — ROTO (15/15)

El binario resuelve APIs por hash sobre los exports del PEB:

```c
piVar1 = **(*(*(GS:[0x60] + 0x18) + 0x10));   // PEB->Ldr->InLoadOrderModuleList
uVar7 = 0x811c9dc5;
do { uVar7 = (c ^ uVar7) * 0x1000193; } while (*++p);
if (uVar7 == 0x9bc5a608) { /* resuelto */ }
```

Hashes resueltos enumerando los exports reales de las DLL de Wine:

| Hash | API | Para qué |
|---|---|---|
| `0x185776b5` | `CreateToolhelp32Snapshot` | snapshot de procesos |
| `0x15eec872` | `Process32Next` | **enumeración de procesos** (emulador + debuggers) |
| `0x4cfe97c1` | `CheckRemoteDebuggerPresent` | detección de debugger remoto |
| `0x85cca27e` | `GetThreadContext` | **lectura de registros Dr0–Dr7** (breakpoints HW) |
| `0x6dd8a845` | `GetCurrentProcess` | proceso actual para lo anterior |
| `0x9bc5a608` | `GetCurrentThread` | hilo actual |
| `0xe971d8a3` | `RegOpenKeyA` | **claves de registro** (detección de VM) |
| `0x57949ea7` | `RegGetValueA` | valores de registro |
| `0x5056df37` / `0x21ddcd8b` | `GetLastError` / `SetLastError` | gestión de errores |
| `0xc5f6a8e5` | `OutputDebugStringA` | truco anti-debug |
| `0xfaba0065` | `CloseHandle` | limpieza |

**Suite anti-debug completa**: enumeración de procesos + debugger remoto +
registros de depuración por hardware + registro + centinela `0xDEADC0DE` +
VEH handler.

Herramienta: `crack_hashes.py` (enumera exports de las DLL de Wine del prefix y
compara). Resultado en `fnv_map.txt`.

---

## 4. Cifrado de cadenas — ROTO

Encontrado el bucle exacto en `fcn.1400120f0`:

```c
uStack_38 = *0x14001a470;   /* 16 bytes desde .rdata */
uStack_28 = 0x30393027;     /* literales inmediatos */
uStack_24 = 0x35312725;
uStack_20 = 0x34;
do {
    *(&uStack_38 + i) = *(&uStack_38 + i) ^ i + 0x53U;
} while (i < 0x19);          /* 25 bytes */
```

Es decir: **`plain[i] = cipher[i] ^ (0x53 + i)`**, con el índice reiniciado por cadena.

Verificación byte a byte (`0x1a470`):
```
cifrado  : 1b 15 07 12 00 19 0b 1f 07 1d 1e 0e 16 3c 25 31
descifr. : H  A  R  D  W  A  R  E  \  A  C  P  I  \  D  S
```

### Cadenas descifradas

| Descifrado | Significado |
|---|---|
| `HARDWARE\ACPI\DSD\VBX__` | tabla ACPI del dispositivo — detección de VM |
| `\\.\VBoxMiniRdrD` | **driver de VirtualBox** — detección de VM |
| `SystemBiosVersion` | versión de BIOS — detección de VM |
| `IDA\History64` | **artefacto de IDA Pro** — detección de analista |

Herramienta: `decode_strings.py`. Barrido masivo delegado a subagente
(`decode_all_strings.py`).

---

## 5. `.3q-` no está cifrado con clave simple

Análisis criptográfico del blob de 7,43 MB:

| Medida | Valor | Uniforme | Interpretación |
|---|---|---|---|
| Índice de coincidencia (todos los periodos 1–32) | 0,0043 | 0,0039 | **sin periodicidad** → no hay clave XOR corta |
| Bytes REX (`0x40`–`0x4f`) | **5,15 %** | 3,12 % | firma de x86-64 |
| Bytes `0x00` | **1,37 %** | 0,39 % | relleno típico de PE |
| Bloques 8 KB >90 % decodificables | 97 / 476 | — | mezcla de código y datos |

Conclusión: `.3q-` **contiene binarios x86-64 embebidos**, no un cifrado de flujo
simple. Tampoco hay PE anidados localizables con `binwalk`.

---

## 6. Estado del bypass anti-VM

| Vector | Estado |
|---|---|
| SMBIOS (`QEMU`, `OVMF`, `pc-q35`) | ✅ neutralizado con DMI falso (mount namespace) |
| MessageBox "cannot run under a Virtual Machine" | ✅ desaparece con DMI falso |
| `NtRaiseHardError(STATUS_VM_DETECTED)` | ⚠️ se sigue invocando (vector residual) |
| `HARDWARE\ACPI\DSD` | ⚠️ **crear la clave hace PEOR** (el programa detecta el árbol ACPI anómalo) |
| `\\.\VBoxMiniRdrD` | ✅ no existe en Wine (correcto) |
| `IDA\History64` | ✅ no existe (correcto) |

Script reutilizable: `fake_dmi.sh` (bind-mounts en `unshare -m`, no toca el host).

---

## 7. Lo que queda y por qué es difícil

El objetivo pendiente es el contenido de `.3q-`: la detección de VM que aborta la
ejecución y el payload que se inyecta en el emulador.

Dificultades medidas:
- El punto de llamada a `NtRaiseHardError` (`RVA 0xE38696`) **no** es un `call rel32`
  → el código está desincronizado a propósito
- El beam-search de recuperación de flujo produce basura (`ret 0x41e9`, `ret 0xdc37`)
  porque premia demasiado los `ret`
- 632 direcciones ejecutadas dan anclas, pero solo 27 caen en `.3q-`

Plan para la siguiente ronda:
1. Recuperação de flujo guiada por traza (anclas de ejecución + heap de basic blocks),
   no por puntuación global
2. Localizar el bucle dispatcher en `.3q-` (patrón `jmp [reg+reg*8]` sobre tabla)
3. Hooking con `frida` de las APIs de detección para forzar el resultado
   (más fiable que parcheo estático sobre código ofuscado)
4. Dump del payload descifrado una vez superado el check

## 8. Scripts

| Script | Función |
|---|---|
| `crack_hashes.py` | rompe hashes FNV-1a enumerando exports de Wine → `fnv_map.txt` |
| `decode_strings.py` | descifrador verificado `plain[i]=cipher[i]^(0x53+i)` |
| `decode_all_strings.py` | barrido masivo con índice variable (delegado a subagente) |
| `fake_dmi.sh` | DMI falso en mount namespace |
| `resync.py` | beam-search de recuperación de flujo (resultado: insuficiente aquí) |
| `dispatch.py` | perfila direcciones ejecutadas desde la traza |
| `angr_shim.py` / `angr_cfg.py` | angr funcional + CFGFast |
| `decompile_all.py` | descompilación en lote con rz-ghidra |