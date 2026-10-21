# `iQVW64E.SYS` — informe final

**77 funciones únicas** decompiladas con Hex-Rays (cloud) y contrastadas con r2 y
Ghidra/REA. Cobertura: 94 extracciones, **0 fallos**; los duplicados son
direcciones interiores de `.pdata` que resuelven a su función contenedora.

- Volcados: `run/hexrays/*.c`
- Extractor: `run/hexrays_dump.sh` (portapapeles: `Ctrl+A`/`Ctrl+C` → `xsel`)
- Lote: `run/batch_hexrays.sh`

Direcciones en **VA** (ImageBase `0x10000`); RVA entre paréntesis.

---

## 1. Atribución

```
c:\users\cloudbuild\337244\sdk\nal\src\winnt_wdm\driver\windriverpci_i.c
c:\users\cloudbuild\337244\sdk\nal\src\winnt_wdm\driver\objfre_wnet_AMD64\amd64\iqvw64e.pdb
C:\Aplicaciones\Visual Studio\Auto Updated\Process-Hollowing-main\Source\x64\Release\runpe.pdb
```

Compilado en **Google Cloud Build** (proyecto `337244`), SDK root `nal` — mismo
prefijo que `NalDeviceControl`/`NalWindowsDrv`/`_NalWinGetUserAddress` —,
config `fre_wnet`, y `C:\Aplicaciones\` (**Windows en español**).

**No reutilizaron un binario firmado: recompilaron desde el código fuente** de un
driver de red y añadieron su superficie `Nal*` conservando `iqvw64e.pdb` para
aparentar el driver Intel original. Pool tag **`"Ddk "`** (`0x206B6444`) en todas
las asignaciones.

---

## 2. Superficie completa expuesta a ring 3

`IRP_MJ_CREATE` (`0x11090`) **no hace ningún control de acceso**: ni ACL, ni
descriptor de seguridad, ni chequeo de privilegio — solo
`_InterlockedIncrement(&dword_17120)` y `IofCompleteRequest` con STATUS_SUCCESS.
**Todo lo de la tabla siguiente es alcanzable por cualquier proceso local.**

### 2.1 Memoria física ↔ virtual

| Fid | Handler | Operación |
|---|---|---|
| **57** | `sub_129C0` | `MmMapIoSpace(física, size)` **+ alias user-mode escribible** |
| 25 | `sub_12AC0` | `MmMapIoSpace(física, size)` — solo kernel |
| 26 | `sub_121C0` | `MmUnmapIoSpace` |
| 58 | `sub_12220` | desmontaje completo por `ProcessId` |
| 55 | `sub_12520` | `MmAllocateContiguousMemory(size, 0xFFFFFFFF)` + `MmGetPhysicalAddress` |
| 56 | `sub_12770` | `MmFreeContiguousMemory` + `MmUnmapLockedPages` + `IoFreeMdl` |
| `0x12010` | `sub_12010` | `MmGetPhysicalAddress(VA)` — VA→físico |
| 59 | `sub_11DE0` | **inversa**: dado `(alias, ProcessId)` → `MmGetPhysicalAddress` |

```c
// sub_129C0 — NalMmapAddressEx (Fid 57)
v9 = MmMapIoSpace(a2, *a3, 0LL);            // ← física ARBITRARIA → VA de kernel
if (a4) *a1 = sub_12030(v9, *a3, a4);       // → puntero USER-MODE escribible

// sub_12030 — NalWinGetUserAddress
Md1    = IoAllocateMdl(a1, a2, 0, 0, 0);
MmBuildMdlForNonPagedPool(Md1);
locked = MmMapLockedPagesSpecifyCache(v8, 1 /*UserMode*/, 1 /*Write*/, 0, 0, 16);
result = (locked & 0xFFFFFFFFFFFFF000LL) + *(uint *)(v8 + 44);   // + MDL->MdlOffset
```

**`MmMapIoSpace` acepta una dirección física arbitraria** ⇒ Fid 57 **por sí solo
es lectura/escritura de memoria física arbitraria desde ring 3**. El allocate
contiguo (Fid 55) solo está para reservar rango limpio.

### 2.2 Puertos I/O — sin validación de puerto

| Fid | Handler | Operación |
|---|---|---|
| 1 / 2 / 3 | `sub_11C20` / `11C30` / `11C40` | `__inbyte` / `__inword` / `__indword` |
| 7 / 8 / 9 | `sub_11C50` / `11C60` / `11C80` | `__outbyte` / `__outword` / `__outdword` |

Puerto de 16 bits arbitrario, sin lista blanca: CF8/CFC, ACPI, SMM, legacy.

### 2.3 Espacio de configuración PCI y BAR — `IOCTL 0x8086200B`

| Case | Handler | Función |
|---|---|---|
| 1 | `sub_13740` | `_NalReadPciDeviceCount` — cuenta dispositivos `VEN_` |
| 2 | `sub_137D0` | lectura de IDs de dispositivo |
| 3 | `sub_138B0` | lectura de config space (dword, vía `sub_12C60`) |
| 4 | `sub_13980` | escritura de config space |
| 5 | `sub_13A00` | lectura/escritura de config space por bloques |
| **6** | `sub_13B20` | **manipulación de BAR**, byte/word/dword seleccionables |
| 7 | `sub_13100` | stub (`return 0`) |

```c
// sub_13B20 — BAR write
if (a3 & 1) { v12[0] = (uint8)a4;  sub_12C60(v10, v12, 16, 4*a2+0, 1); }
if (a3 & 2) { v12[0] = BYTE1(a4);  sub_12C60(v10, v12, 16, 4*a2+1, 1); }
if (a3 & 4) { v12[0] = BYTE2(a4);  sub_12C60(v10, v12, 16, 4*a2+2, 1); }
if (a3 & 8) { v12[0] = HIBYTE(a4); sub_12C60(v10, v12, 16, 4*a2+3, 1); }
```

`sub_12C60` verificado en ensamblador (el pseudocode etiqueta mal los offsets):

```asm
mov dword [rax+0x30], 0xC00000BB    ; IoStatus = STATUS_NOT_IMPLEMENTED (sonda)
mov byte  [rdx], 0x1B               ; MajorFunction = IRP_MJ_PNP
mov byte  [rdx+1], sil              ; MinorFunction = 15 (0x0F)
call IofCallDriver
```

**Cierto**: `IRP_MJ_PNP` + MinorFunction 15, buffers en la unión de parámetros,
`IofCallDriver` sobre el `DeviceObject` del dispositivo coincidente, espera por
evento si `STATUS_PENDING`.
**No afirmo** la semántica exacta del MinorFunction 15 — la unión de parámetros
PnP es específica del fabricante.

### 2.4 Atomics y helpers

| Handler | Exposición |
|---|---|
| `sub_11C90` / `11CB0` / `11CD0` | lecturas null-safe 8/16/32 bits |
| `sub_11CF0` / `11D10` / `11D30` | escrituras null-safe + `_InterlockedOr(&retaddr, 0)` — barrera `lock or [rsp],0` de MSVC, para escrituras en memoria mapeada |
| `sub_11F10` | **`_InterlockedCompareExchange` null-safe** — CAS atómico arbitrario |
| `sub_11E70` / `11EA0` | `memset` / `memmove` guardados por `KeGetCurrentIrql() <= DISPATCH_LEVEL` |
| `sub_11DB0` | `KeQueryPerformanceCounter` |
| `sub_12000` | **`byte_17128 = a1`** — el usuario **activa/desactiva el log del kernel** |
| `sub_11D50` / `sub_123C0` | `KeStallExecutionProcessor` — **retraso en CPU** disparable desde ring 3 |

### 2.5 Falso driver de red — `IOCTL 0x80862013` (`NalOsSpecificIoctl`)

Casos **nombrados en el propio código**:

| Case | Nombre |
|---|---|
| 1 | `NAL_WIN_GET_PDO_POINTER_FUNCID` |
| 2 | `NAL_WIN_GET_SYMBOLIC_NAME_FUNCID` |
| 3 | `NAL_WIN_ALLOC_DEV_CONTEXT_FUNCID` |
| 4 | `NAL_WIN_FREE_DEV_CONTEXT_FUNCID` |
| 5 | `NAL_WIN_OS_DEVICE_FUNCID` (`FillKernelContext`) |
| 6 | `NAL_WIN_DRIVER_GET_REF_COUNT_FUNCID` |
| 7 | `NAL_WIN_ADAPTER_IN_USE_FUNCID` |
| 8 | `NAL_WIN_IS_ADAPTER_IN_USE_FUNCID` |

---

## 3. Tablas globales

| Símbolo | Tamaño | Contenido |
|---|---|---|
| `byte_5CFEC0` | **256 × 0x110** | tabla de adaptadores; slot[0] puntero, slot[264] flag "in use" |
| `unk_17140` | **50.000 × 0x50** | asignaciones contiguas |
| **`unk_3E7A40`** | **50.000 × 0x28** | **`Global_WinMemoryMapTable`** = `{MappedAddress, OriginalMemoryMapped, Mdl, LockedPtr, ProcessId}` |
| `unk_17150`, `unk_17180`, `unk_17188` | 50.000 × 0x50 | tablas auxiliares |
| `dword_17120` | 1 | handles abiertos |
| `qword_17130` | 1 | calibración de temporizador |
| `byte_17128` | 1 | flag de logging (**controlable desde ring 3**) |
| `qword_17108` / `qword_17100` | 2 | security cookie y su complemento |

El nombre `Global_WinMemoryMapTable` aparece en el log de `NalUnmapAddressEx` y
corresponde a `unk_3E7A40` (stride `0x28`), **no** a `unk_17140` (stride `0x50`).

---

## 4. Dispatch

`DriverEntry` (`0x5E2200`) solo inicializa el security cookie MSVC
(`0x2B992DDFA232`) y delega en `sub_5E2010`:

```c
a1[13] = sub_11010;   // +0x68  DriverUnload
a1[14] = sub_11090;   // +0x70  MajorFunction[0]  IRP_MJ_CREATE
a1[16] = sub_110F0;   // +0x80  MajorFunction[2]  IRP_MJ_CLOSE
a1[28] = sub_11150;   // +0xE0  MajorFunction[14] IRP_MJ_DEVICE_CONTROL
IoCreateDevice(a1, 24LL, &DestinationString, 32902LL, 0, FALSE, &v14);  // 0x8086
*(_DWORD *)(v14 + 48) |= 4u;      // DO_BUFFERED_IO
*(_DWORD *)(v14 + 48) &= ~0x80u;  // ~DO_DEVICE_SURVEILLANCE
```

`sub_11150` (`0x1150`) despacha 4 IOCTL, todos `METHOD_NEITHER` +
`FILE_ANY_ACCESS`, sin `ProbeForRead/Write`:

```
0x80862007 → sub_113C0   switch de 59 FunctionIds (jump table @ 0x11968, indexada por Fid-1)
0x8086200B → sub_11A60   PCI: config space y BAR
0x8086200F → sub_11330   estado de interrupción / refs
0x80862013 → sub_13FA0   NalOsSpecificIoctl (falsa API de adaptador)
```

**Bug del atacante (huella)**: en `DriverEntry` los dos `else` tienen los
mensajes **intercambiados** — el fallo de `IoCreateDevice` imprime
`"IoCreateSymbolicLink failed"` y viceversa.

---

## 5. Anti-análisis

`sub_12450` (`0x2450`) calibra contra el **contador de rendimiento**, cacheando en
`qword_17130`:

```c
do { KeStallExecutionProcessor(50LL); ... } while (...);   // ~1000 iteraciones
qword_17130 = (KeQueryPerformanceCounter(0LL) - t0) / 0x186A0uLL;
```

Es el **equivalente en el driver** de la anti-VM por `CPUID`/`RDTSC` que ya
neutralizamos en el loader.

Defecto latente en el wrapper de log (`sub_11F30`):

```c
vsprintf(Dest, Format, Args);   // sin límite
strcpy(Formata, "Kernel: ");
strncpy(&Formata[8], Dest, 0x1F3uLL);
```

Todos los formatos observados son literales ⇒ **no alcanzable** con la
superficie actual. Y `sub_14270` es `__report_gsfailure` →
`KeBugCheckEx(247, ...)`, el bugcheck de desbordamiento de cookie.

---

## 6. Cadena de ataque completa

```
ring 3   CreateFile("\\\\.\\Nal")            ← sin ACL: cualquiera
ring 3   DeviceIoControl(h, 0x80862007, {Fid, …})
           ├─ Fid 57  MmMapIoSpace(física)  →  IoAllocateMdl
           │           + MmMapLockedPagesSpecifyCache(UserMode, Write)
           │           ⇒ puntero ESCRIBIBLE en espacio de usuario
           ├─  1/2/3/7/8/9  puertos I/O arbitrarios
           ├─ 55  MmAllocateContiguousMemory  → dirección física limpia
           ├─  0x8086200B case 6  escritura de BAR de PCI
           └─  0x12010 / 59  MmGetPhysicalAddress en ambos sentidos
```

Para un cheat de emulador esto es lo que permite tocar la memoria del proceso
emulado; para un atacante local, **lectura/escritura de memoria física arbitraria
y E/S de puertos desde cualquier proceso sin privilegios**.

---

## 7. Correcciones a informes previos

| Afirmación anterior | Correcto |
|---|---|
| "Fid 55 → `MmAllocateContiguousMemory` + MDL + `MmMapLockedPagesSpecifyCache`" | **Fid 55** = solo allocate + `MmGetPhysicalAddress`. La cadena MDL está en **Fid 57**, precedida de **`MmMapIoSpace`**, que faltaba por completo |
| "`Global_WinMemoryMapTable` en `0x17140`, 50.000 × `0x50`" | El nombre pertenece a **`unk_3E7A40`**, stride **`0x28`**, con `ProcessId` por slot. `unk_17140` es la tabla de contiguos, stride `0x50` (esto sí correcto) |
| "4 IOCTL `0x80862007/0B/0F/13`" | Confirmado literalmente |
| "MajorFunction index 14" | Confirmado (`a1[28]` = offset `0xE0`) |
| Avance de cabecera RAR5 = `pos+4+hdrsize` | `pos + 4 + len(vint) + hdrsize` (el `header size` se cuenta desde `Header type`) |

---

## 8. Lo que queda fuera

- **~20 funciones** de las 112 que ve IDA siguen sin pseudo (CRT: `memset`,
  `memmove`, excepción); no aportan.
- El paquete RAR tiene **~806 MB con compresión método 3 sin inspeccionar**.
  El subagente verificó que `14ddg0941cvah.exe` y `34dbbmddg71c.exe` **no están**
  en el paquete por 3 vías independientes: son nombres generados en runtime.
- La semántica exacta del MinorFunction 15 de IRP_MJ_PNP queda sin resolver.

## 9. Limitación del método

Hex-Rays en IDA Free tiene **batch decompilation deshabilitado**: se compila
función a función por GUI. `hexrays_dump.sh` + `batch_hexrays.sh` lo automatizan
a ~13 s/función. Es un **verificador manual de terceros**, no un proveedor
automatizado de REA (Ghidra lo es).