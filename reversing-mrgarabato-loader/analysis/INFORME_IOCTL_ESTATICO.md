# INFORME DE ANÁLISIS ESTÁTICO — iQVW64E.SYS (payload_embebido.exe)

**Fichero analizado:** `c2_descargas/payload_embebido.exe`
**SHA-256:** `8349ea7814494415e6f0b3d803050e23a4534a410bafd3a9801c300694eb76e4`
**Tamaño:** 41808 bytes · PE32+ · ImageBase `0x10000` · sin packer
**Versión (recurso):** `Intel(R) Network Adapter Diagnostic Driver` — `iQVW64.SYS` 1.03.0.7, `Nov 14 2013`, PDB `c:\users\cloudbuild\337244\sdk\nal\src\winnt_wdm\driver\objfre_wnet_AMD64\amd64\iqvw64e.pdb`
**Tipo de análisis:** 100 % estático (capstone 5.0.7 + radare2 como contraste). **El binario NUNCA se ha ejecutado.**

> Todas las direcciones de este informe son **RVA** (RVA = VA − `0x10000`). Ejemplo: el dispatcher real
> está en VA `0x11150` / RVA `0x1150`.

---

## 1. RESUMEN EJECUTIVO

**Los códigos IOCTL SÍ se han recuperado. Son 4, y están escritos como literales inmediatos en el
dispatcher. No hay ninguna tabla que reconstruir en runtime.**

| IOCTL | DeviceType | Function | Method | Access | Handler (RVA) | Nº sub-IDs |
|---|---|---|---|---|---|---|
| `0x80862007` | `0x8086` (Intel) | `0x801` (2049) | `METHOD_NEITHER` | `FILE_ANY_ACCESS` | `0x13C0` | 59 |
| `0x8086200b` | `0x8086` (Intel) | `0x802` (2050) | `METHOD_NEITHER` | `FILE_ANY_ACCESS` | `0x1A60` | 7 |
| `0x8086200f` | `0x8086` (Intel) | `0x803` (2051) | `METHOD_NEITHER` | `FILE_ANY_ACCESS` | `0x1330` | 3 |
| `0x80862013` | `0x8086` (Intel) | `0x804` (2052) | `METHOD_NEITHER` | `FILE_ANY_ACCESS` | `0x3FA0` | 8 |

Además:
* El mapeo de `MajorFunction[]` ha quedado **corregido** (ver §3): el handler de `IRP_MJ_DEVICE_CONTROL`
  es `0x1150`, **no** `0x1020`.
* El mapeo completo `NAL_WIN_*_FUNCID` → valor numérico → handler está **determinado con evidencia del
  propio binario** (§6), no inferido.
* La tabla de 6 MB en `.data` **no** es una tabla de IOCTL: es la *memory-map table* del SDK NAL
  (ver §8.3 y corrección en §2.3).

---

## 2. METODOLOGÍA Y CORRECCIONES A DATOS PREVIOS

### 2.1 Herramientas
`python3` + `capstone 5.0.7` (desensamblado y xrefs propios, con *sweep* lineal por offset para no
detenerse en el primer byte no decodificable), `radare2` (contraste independiente de las
conclusiones clave), `rabin2` (cabeceras/imports/recursos), `objdump`. No se usó `angr` ni `speakeasy`.

### 2.2 Corrección 1 — el punto de entrada de `.pdata` y las cadenas de depuración
* `.text` tiene **VirtualSize `0x4615`** (no `0x5000`); rawsize `0x4800`, rawptr `0x400`.
* Las cadenas `"NalDeviceControl: ..."`, `"NalResolveOsSpecificIoctl: ..."`, etc. **no están en `.rdata`**
  sino **dentro de `.text`**, en el rango `0x4730`–`0x55F0` (el compilador lasacoló tras el último
  `ret` de `.text`). Los RVA reales:
  * `0x49D0` `NalDeviceControl: InputBuffer was NULL`
  * `0x4A00` `Nal Windows DriverDeviceControl: Invalid IOCTL code 0x%0x`
  * `0x4A40` `NAL_ENABLE_DEBUG_PRINT_FUNCID: FunctionData is NULL`
  * `0x4A80` `NAL_KKMEMCPY_FUNCID: ...` · `0x4AC0` `NAL_KUMEMCPY_FUNCID: ...` · `0x4B00` `NAL_KMEMSET_FUNCID: ...`
  * `0x51D0` `Looking for match for %d/%d/%d`
  * `0x52F0` `NalResolveOsSpecificIoctl: FuctionId = %d` · `0x55F0` `NalOsSpecificIoctl: FunctionId = %d`
* **DeviceName / SymbolicLink:** `\Device\Nal` (`0x48C0`), `\DosDevices\Nal` (`0x4860`), `\??\Nal` (`0x47B0`)
  — todas UTF-16LE válidas.

### 2.3 Corrección 2 — el mapeo `MajorFunction[]` (el error más importante del análisis previo)

Del desensamblado real de `DriverEntry` (RVA `0x5D2033`, dentro de la sección `INIT`):

```
0x5d2065  lea     rax, [rip - 0x5d0f93]        ; -> 0x1090
0x5d206c  lea     rcx, [rip - 0x1fa623]        ; -> 0x3d7a50   (otra tabla)
0x5d2073  mov     edx, 0xc350                  ; 50000
0x5d2078  mov     qword ptr [rbx + 0x70], rax ; <== MajorFunction[0]  = IRP_MJ_CREATE        -> 0x1090
0x5d207c  lea     rax, [rip - 0x5d0f93]        ; -> 0x10f0
0x5d2083  mov     qword ptr [rbx + 0x80], rax ; <== MajorFunction[2]  = IRP_MJ_CLOSE         -> 0x10f0
0x5d208a  lea     rax, [rip - 0x5d0f41]        ; -> 0x1150
0x5d2091  mov     qword ptr [rbx + 0xe0], rax ; <== MajorFunction[14] = IRP_MJ_DEVICE_CONTROL-> 0x1150
0x5d2098  lea     rax, [rip - 0x5d108f]        ; -> 0x1010
0x5d209f  mov     qword ptr [rbx + 0x68], rax ; <== DriverUnload                           -> 0x1010
```

Con el layout x64 real de `DRIVER_OBJECT` (`DriverUnload` en `+0x68`, `MajorFunction[]` en `+0x70`):

| Offset | Campo | Índice | Handler (RVA) | Función |
|---|---|---|---|---|
| `+0x68` | `DriverUnload` | — | **`0x1010`** | `Nal Windows DriverUnload` |
| `+0x70` | `MajorFunction[0]` | 0 | **`0x1090`** | `IRP_MJ_CREATE` (`DriverCreate`) |
| `+0x80` | `MajorFunction[2]` | 2 | **`0x10F0`** | `IRP_MJ_CLOSE` (`DriverClose`) |
| `+0xE0` | `MajorFunction[14]` | 14 | **`0x1150`** | **`IRP_MJ_DEVICE_CONTROL`** |

**Correcciones concretas:**
1. El índice es **14**, no 11 (`0x70 + 14*8 = 0xE0`). `0x70+11*8 = 0xC8`, que el driver nunca escribe.
2. El handler es **`0x1150`**, no `0x1020`. `0x1020` está **en medio** de la función `DriverUnload`
   (`0x1010..0x1081`): es la instrucción `call 0x1F30` (DbgPrint) que sigue al `lea` de la cadena
   `"Nal Windows DriverUnload: Starting"`. No es un handler.
3. Solo se registran 4 handlers. No hay `IRP_MJ_INTERNAL_DEVICE_CONTROL`, ni PnP, ni Power.

### 2.4 Corrección 3 — la "tabla de IOCTL" de `0x354B` es **código muerto**
El análisis previo se centró en `NalDeviceControl` (`0x354B..0x35F4`), que recibe un puntero a tabla
por `[rsp+0x20]`, compara solo `Function`/`Method` y tiene el puntero a handler en `+0x38`.
Eso es la función genérica `NalDeviceControl()` del SDK NAL (una *API*, no el dispatch de este driver).

**Verificación de alcanzabilidad:** barrido de todos los sitios `call` dentro de los límites de las 86
entradas `.pdata`:
```
0x00354b : NO CALLERS (dead code)
0x0035f4 : NO CALLERS (dead code)
```
No hay ninguna referencia a `0x3540..0x364B` desde el camino de ejecución del driver (sí la usan otras
funciones del SDK, p.ej. `0x3980`, `0x3A00`, `0x3B20` la llaman). **Es boilerplate del SDK enlazado y
no usado por el driver.** Por tanto la hipótesis de "tabla construida en runtime" era incorrecta.

### 2.5 Corrección 4 — la tabla de 6 MB
El bucle de `DriverEntry` a `0x5D20B0` limpia **50000 (`0xC350`) entradas de stride `0x50`** en `.data`.
No es una tabla de IOCTL: es `Global_WinMemoryMapTable` del SDK NAL. Layout deducido del consumidor
`0x2520` (§8.3): base **RVA `0x7140`**, lock dword, VA kernel, VA usuario, PA, offset, tamaño.

### 2.6 Salvedad sobre `.pdata` (86 entradas)
Las 86 `RUNTIME_FUNCTION` son en su mayor parte fiables, **pero no son 100 % fieles**:
* Varias entradas terminan en **datos de jump-table**, no en código (`0x13C0..0x1A54`, `0x1A60..0x1C10`,
  `0x3FA0..0x4264`) — normal, pero engañoso para un desensamblador lineal.
* Cuatro entradas son **fragmentos que no acotan una función completa** (empiezan por el prólogo
  `mov rax,rsp / sub rsp,…` pero no contienen `ret`):
  `0x2220..0x224E`, `0x3540..0x354B` (11 B), `0x3640..0x364B` (11 B), `0x5D2010..0x5D2033` (35 B).
  La función real que empieza en `0x3540` es `0x3540..0x364B`; la de `0x2220` es `0x2220..0x23A1`;
  `DriverEntry` real es `0x5D2010..0x5D21F9` (3 entradas encadenadas).
  → **Los límites hay que confirmarlos por control de flujo, no solo por `.pdata`.**
  Los cuatro handlers de IOCTL sí están correctamente delimitados (contienen `ret` y les sigue un prólogo nuevo).

---

## 3. EL DISPATCHER REAL (RVA `0x1150`, 179 bytes)

```
0x001150  sub     rsp, 0x28
0x001154  mov     rax, qword ptr [rdx + 0xb8]   ; IRP->Tail.Overlay.CurrentStackLocation
0x001165  mov     rcx, qword ptr [rax + 0x20]   ; IOSP->Parameters.DeviceIoControl.Type3InputBuffer
0x001169  mov     rdi, rdx                       ; rdi = IRP
0x00116c  mov     edx, dword ptr [rax + 0x18]    ; IOSP->Parameters.DeviceIoControl.IoControlCode
0x00116f  test    rcx, rcx
0x001172  je      0x111cb                        ; -> "NalDeviceControl: InputBuffer was NULL", STATUS_INVALID_PARAMETER
0x001174  cmp     edx, 0x80862007
0x00117a  je      0x111c2                        ; -> call 0x13c0
0x00117c  cmp     edx, 0x8086200b
0x001182  je      0x111b9                        ; -> call 0x1a60
0x001184  cmp     edx, 0x8086200f
0x00118a  je      0x111b0                        ; -> call 0x1330
0x00118c  cmp     edx, 0x80862013
0x001192  je      0x111a7                        ; -> call 0x3fa0
0x001194  lea     rcx, [rip + 0x3865]            ; "Nal Windows DriverDeviceControl: Invalid IOCTL code 0x%0x"
0x00119b  mov     ebx, 0xc000000d                ; STATUS_INVALID_PARAMETER
0x0011dc  xor     edx, edx
0x0011e1  mov     qword ptr [rdi + 0x38], 0      ; IoStatus.Information = 0
0x0011e9  mov     dword ptr [rdi + 0x30], ebx    ; IoStatus.Status = <retval>
0x0011ec  call    [IofCompleteRequest]
```

**Puntos clave:**
* Los handlers se llaman como `handler(rcx = Type3InputBuffer, rdx = IoControlCode)`.
* **El dispatcher NO lee `InputBufferLength` (`IOSP+0x10`) ni `OutputBufferLength` (`IOSP+0x08`).**
  Únicamente comprueba que `Type3InputBuffer != NULL`.
* El sub-dispatch de segundo nivel (`FunctionId`) lo hace cada handler leyendo
  `*(ULONG*)InputBuffer` (offset 0 del buffer de usuario).

> Contraste con radare2 (`r2 -qc 's 0x11150; pd 26'`) produce un desensamblado **idéntico**: los 4 `cmp`
> y los 4 destinos de `call` coinciden. La conclusión no depende de una única herramienta.

---

## 4. LOS 4 CÓDIGOS IOCTL — detalle de campos

Descomposición `CTL_CODE`: `DeviceType = code>>16`, `Access = (code>>14)&3`,
`Function = (code>>2)&0xFFF`, `Method = code&3`.

| Código | DeviceType | Function | Method | Access | Handler | Tamaño |
|---|---|---|---|---|---|---|
| `0x80862007` | `0x8086` Intel | `0x801` = 2049 | `3` `METHOD_NEITHER` | `0` `FILE_ANY_ACCESS` | `0x13C0` | 1684 B |
| `0x8086200b` | `0x8086` Intel | `0x802` = 2050 | `3` `METHOD_NEITHER` | `0` `FILE_ANY_ACCESS` | `0x1A60` | 432 B |
| `0x8086200f` | `0x8086` Intel | `0x803` = 2051 | `3` `METHOD_NEITHER` | `0` `FILE_ANY_ACCESS` | `0x1330` | 136 B |
| `0x80862013` | `0x8086` Intel | `0x804` = 2052 | `3` `METHOD_NEITHER` | `0` `FILE_ANY_ACCESS` | `0x3FA0` | 708 B |

**Los cuatro son `METHOD_NEITHER` + `FILE_ANY_ACCESS`.**

### 4.1 Exclusividad — prueba de que no hay más IOCTL
Se recorrieron todos los immediatos de 32 bits de todas las instrucciones dentro de las 86 entradas
`.pdata`, filtrando los que podrían formar un IOCTL (16 bits altos en `0x8000..0xFFFF`):

```
0x80862007  (cmp)  x1      <-- IOCTL
0x8086200b  (cmp)  x1      <-- IOCTL
0x8086200f  (cmp)  x1      <-- IOCTL
0x80862013  (cmp)  x1      <-- IOCTL
0x8d000041  (push) x1      (no IOCTL: 0x8d00 no es DeviceType válido de este driver)
0xc0000001 / 0xc000000d / 0xc000009a / 0xc00000bb   (STATUS_* de NT)
0xc86a****  (mov)  NAL status codes del SDK
```
Además, `0x9B0C` **no aparece como inmediato en ninguna parte**, ni en `.text` ni en `.data`/`.rdata`
(las dos coincidencias byte a byte en `0x215B` y `0x271D` caen dentro de otras instrucciones, no son
inmediatos). **No hay construcción de IOCTL por `or`/`shl`.**

**⇒ El driver expone exactamente 4 códigos IOCTL.** No hay más.

---

## 5. IOCTL `0x80862007` → handler `0x13C0` (59 FunctionIds)

Mecánica: `FunctionId = *(ULONG*)InputBuffer`; `if (FunctionId-1 > 0x3A) → 0xC86A2018`;
salto indexado por la jump-table de **RVA `0x1968`** (59 dwords absolutos, base = 0).
`0x1950` = caso por defecto → `mov eax, 0xC86A2018` (STATUS de NAL: *function id inválido*).

| Fid | Hex | Caso (RVA) | Acción real (verificada por la llamada hoja) |
|---|---|---|---|
| 1 | 0x01 | `0x1402` | `in al, dx` → **ReadPortUchar** |
| 2 | 0x02 | `0x1421` | `in ax, dx` → **ReadPortUshort** |
| 3 | 0x03 | `0x1441` | `in eax, dx` → **ReadPortUlong** |
| 4–6 | | `0x1950` | *inválido* |
| 7 | 0x07 | `0x1460` | `out dx, al` → **WritePortUchar** |
| 8 | 0x08 | `0x1483` | `out dx, ax` → **WritePortUshort** |
| 9 | 0x09 | `0x14A6` | `out dx, eax` → **WritePortUlong** |
| 10–12 | | `0x1950` | *inválido* |
| 13 | 0x0D | `0x14C8` | `*(BYTE*)p` (NULL→0) → **ReadMmUchar** |
| 14 | 0x0E | `0x14E7` | `*(WORD*)p` → **ReadMmUshort** |
| 15 | 0x0F | `0x1507` | `*(DWORD*)p` → **ReadMmUlong** |
| 16–18 | | `0x1950` | *inválido* |
| 19 | 0x13 | `0x1526` | `*(BYTE*)p = dl` → **WriteMmUchar** |
| 20 | 0x14 | `0x1549` | `*(WORD*)p = dx` → **WriteMmUshort** |
| 21 | 0x15 | `0x156C` | `*(DWORD*)p = edx` → **WriteMmUlong** |
| 22–24 | | `0x1950` | *inválido* |
| 25 | 0x19 | `0x158E` | `0x2AC0` → `MmMapIoSpace` |
| 26 | 0x1A | `0x15B5` | `0x21C0` → `MmUnmapIoSpace` |
| 27 | 0x1B | `0x15DC` | `0x1DB0` → `KeQueryPerformanceCounter(0)` (timer) |
| 28 | 0x1C | `0x15F8` | `0x2450` → lee global qword `[0x7130]` |
| 29–34 | | `0x1950` | *inválido* |
| 35 | 0x23 | `0x162F` | `0x23C0` → `KeStallExecutionProcessor` |
| 36 | 0x24 | `0x1614` | `0x1D50` → bucle `KeStallExecutionProcessor` (µs) |
| 37 | 0x25 | `0x164A` | `0x2010` → **`MmGetPhysicalAddress`** |
| 38 | 0x26 | `0x166A` | `0x28B0` → `0x2520` → **alloc+mapeo de memoria no paginada** |
| 39 | 0x27 | `0x1697` | `0x28E0` → **`MmFreeContiguousMemory`** |
| 40 | 0x28 | `0x17B7` | `0x1ED0` → `lock xadd [+1]` (refcount++) |
| 41 | 0x29 | `0x17D6` | `0x1EF0` → `lock xadd [−1]` (refcount−−) |
| 42 | 0x2A | `0x17F5` | `0x1F10` → `lock cmpxchg` |
| 43–46 | | `0x1950` | *inválido* |
| **47** | **0x2F** | `0x183C` | `DbgPrint` → **`NAL_ENABLE_DEBUG_PRINT_FUNCID`** (confirmado por cadena `0x4A40`) |
| **48** | **0x30** | `0x16B8` | `0x1E70`→`memset` → **`NAL_KMEMSET_FUNCID`** (cadena `0x4B00`) |
| **49** | **0x31** | `0x16FD` | `0x1EA0`→`memcpy` → **`NAL_KUMEMCPY_FUNCID`** (cadena `0x4AC0`) |
| **50** | **0x32** | `0x1748` | `0x1EA0`→`memcpy` → **`NAL_KKMEMCPY_FUNCID`** (cadena `0x4A80`) |
| 51 | 0x33 | `0x1793` | `0x1EA0`→`memcpy` (sin comprobaciones de NULL) → memcpy kernel→user |
| 52–53 | | `0x1950` | *inválido* |
| 54 | 0x36 | `0x181B` | `0x2000` → `mov byte ptr [0x7128], cl` (flag global de depuración) |
| 55 | 0x37 | `0x187D` | `0x2520` → **MmAllocateContiguousMemory + IoAllocateMdl + MmBuildMdlForNonPagedPool + MmMapLockedPagesSpecifyCache** |
| 56 | 0x38 | `0x18B0` | `0x2770` → **MmUnmapLockedPages + IoFreeMdl + MmFreeContiguousMemory** |
| 57 | 0x39 | `0x18D6` | `0x29C0` → `MmMapIoSpace` |
| 58 | 0x3A | `0x1901` | `0x2220` → `MmMapIoSpace` |
| 59 | 0x3B | `0x192C` | `0x1DE0` → recorrido de registro (global `0x7180`) |

**Fids implementados: 33 de 59. Los otros 26 caen en el caso inválido `0x1950`.**

Estructura del buffer de entrada (deducida del uso de `rdi = InputBuffer`):
`+0x10` = resultado/salida · `+0x18` = puntero de contexto (NalDeviceContext) ·
`+0x20`/`+0x24` = operandos · `+0x28`/`+0x30` = punteros auxiliares.

---

## 6. IOCTL `0x80862013` → handler `0x3FA0` = `NalOsSpecificIoctl`  ★ objetivo secundario

Cadena en `0x3FD5`: `NalOsSpecificIoctl: FunctionId = %d`.
`FunctionId = *(ULONG*)InputBuffer`; `if (FunctionId-1 > 7) → 0x420A` (imprime `0x52F0`
`NalResolveOsSpecificIoctl: FuctionId = %d` y devuelve `0xC86A2018`).
Jump-table en **RVA `0x4244`**, 8 dwords absolutos.

### 6.1 Mapeo `NAL_WIN_*_FUNCID` — DETERMINADO, con evidencia del binario

La evidencia es directa: el camino "error" (`je`) de **cada** caso referencia una cadena única que
nombra el FunctionId. No hay inferencia ni conocimiento externo.

| FunctionId | Hex | Caso (RVA) | Handler interno | Cadena de error en el propio driver | Nombre canónico |
|---|---|---|---|---|---|
| **1** | `0x01` | `0x4005` | `0x3640` (strncpy) | `0x55A0` `NAL_WIN_GET_PDO_POINTER_FUNCID` | `NAL_WIN_GET_PDO_POINTER_FUNCID` |
| **2** | `0x02` | `0x4051` | `0x3EF0` | `0x5540` `NAL_WIN_GET_SYMBOLIC_NAME_FUNCID` | `NAL_WIN_GET_SYMBOLIC_NAME_FUNCID` |
| **3** | `0x03` | `0x407E` | `0x3E60` (`ExAllocatePoolWithTag`) | `0x54E0` `NAL_WIN_ALLOC_DEV_CONTEXT_FUNCID` | `NAL_WIN_ALLOC_DEV_CONTEXT_FUNCID` |
| **4** | `0x04` | `0x40A4` | `0x3EA0` (`ExFreePoolWithTag`+`ObfDereferenceObject`) | `0x5480` `NAL_WIN_FREE_DEV_CONTEXT_FUNCID` | `NAL_WIN_FREE_DEV_CONTEXT_FUNCID` |
| **5** | `0x05` | `0x40CD` | `0x3D00` | `0x5430` `NAL_WIN_OS_DEVICE_FUNCID` | `NAL_WIN_OS_DEVICE_FUNCID` |
| **6** | `0x06` | `0x4168` | `0x1210` | `0x53D0` `NAL_WIN_DRIVER_GET_REF_COUNT_FUNCID` | `NAL_WIN_DRIVER_GET_REF_COUNT_FUNCID` |
| **7** | `0x07` | `0x418D` | `0x1220` | `0x5380` `NAL_WIN_ADAPTER_IN_USE_FUNCID` | `NAL_WIN_ADAPTER_IN_USE_FUNCID` |
| **8** | `0x08` | `0x41CF` | `0x12F0` | `0x5320` `NAL_WIN_IS_ADAPTER_IN_USE_FUNCID` | `NAL_WIN_IS_ADAPTER_IN_USE_FUNCID` |

**Verificación cruzada de coherencia** (todo encaja, nada supuesto):
* Fid 3 llama a `0x3E60` (`ExAllocatePoolWithTag` con tag `"Ddk "`) = *alloc*; Fid 4 llama a `0x3EA0`
  (`ExFreePoolWithTag`+`ObfDereferenceObject`) = *free*. ✓ consistente con ALLOC/FREE.
* Fid 6 llama a `0x1210` = `mov eax, dword ptr [0x7120]`. El global `0x7120` es exactamente el que
  incrementan `DriverCreate` (`0x1090`→`0x1ED0`, `lock xadd +1`) y decrementa `DriverClose`
  (`0x10F0`→`0x1EF0`, `lock xadd −1`), y que `DriverEntry` pone a 0. ✓ = *driver ref count*.
* Fid 7 (`0x1220`) recorre la tabla de BSS `0x5BFEC0` buscando la clave y **incrementa** un contador.
* Fid 8 (`0x12F0`) recorre la misma tabla y solo **consulta** si hay entrada activa (devuelve `TRUE`/`FALSE`
  con marca en `+0x108`). ✓ = *adapter in use* (acción) vs *is adapter in use* (consulta).
* Fid 2 llama a `0x3EF0`, que usa `RtlInitUnicodeString` + `RtlUnicodeStringToAnsiString` +
  `strstr` + `ExAllocatePoolWithTag`/`ExFreePoolWithTag` → obtener/copiar el nombre simbólico. ✓

---

## 7. IOCTL `0x8086200B` y `0x8086200F`

### 7.1 `0x8086200B` → `0x1A60` (7 FunctionIds, jump-table en `0x1BF4`)

Copia `0x108` bytes del contexto a la pila del kernel (`memcpy` `0x42B0`) antes de operar.

| Fid | Caso (RVA) | Destino | Descripción |
|---|---|---|---|
| 1 | `0x1A9D` | `0x3740` | **`_NalReadPciDeviceCount`** — cuenta dispositivos PCI vía `IoGetDeviceInterfaces` (`0x32B0`); imprime `0x51F0` `"_NalReadPciDeviceCount found %d devices (%d)"`; devuelve `USHORT` |
| 2 | `0x1AB1` | `0x37D0` | Reescribe **línea/pin de interrupción** de cada dispositivo encontrado: recorre la lista y hace `xor …and 0x1F00` y `xor …and 0xE000` sobre cada entrada de `0x108`; `ObfDereferenceObject` al final |
| 3 | `0x1ACC` | `0x38B0` | `ExAllocatePoolWithTag(0, 0x100, tag='Ddk ')`, `memcpy`, `IoBuildSynchronousFsdRequest`/`IofCallDriver` → **lectura de configuración del adaptador desde el registro**; referencia `windriverpci_i.c`; status `0xC86A8002` |
| 4 | `0x1B06` | `0x3980` | `0x3540` (enum) + `0x2C60` (`IoBuildSynchronousFsdRequest`/`IofCallDriver`/`KeInitializeEvent`/`KeWaitForSingleObject`) → acceso al registro |
| 5 | `0x1B3F` | `0x3A00` | `0x3540` + registro (idéntica infra a la anterior, firma distinta) |
| 6 | `0x1B78` | `0x3B20` | Rutina grande (472 B): `0x3540` + `0x3A00` + **6×** `0x2C60` → acceso masivo a registro/configuración |
| 7 | `0x1BB9` | `0x3100` | **STUB**: `xor eax,eax; ret` (devuelve 0, no implementado) |

### 7.2 `0x8086200F` → `0x1330` (3 FunctionIds, cadena `dec`/`je`, sin jump-table)

| Fid | Caso (RVA) | Acción |
|---|---|---|
| 1 | `0x1391` | `0x3DF0` = **STUB** `mov eax, 0xC86A0003; ret` → escribe ese status en `[buf+0x10]` |
| 2 | `0x1374` | `0x3E00` = lee y **pone a 0** el byte `[ctx+0x129]`; imprime `0x52A0` `"_NalHasInterruptOccurred returning %s"` con `0x52E0`/`0x52D0` = `"TRUE"`/`"FALSE"` → **NAL_HAS_INTERRUPT_OCCURRED** |
| 3 | `0x1358` | **STUB** idéntico a Fid 1 (comparte el bloque `0x13A5`) |
| otros | `0x134D` | `mov eax, 0xC86A2018` |

---

## 8. HALLAZGOS DE SEGURIDAD Y ESTRUCTURA

### 8.1 No hay ningún sondeo de buffers de usuario
Las 39 importaciones **no incluyen** `ProbeForRead`, `ProbeForWrite`, `MmGetSystemAddressForMdlSafe`,
`MmProbeAndLockPages` ni `MmSecureZeroMemory`. El dispatcher pasa el **puntero de espacio de usuario**
tal cual a los handlers, que:
* hacen `memcpy` de `0x108` bytes **desde memoria de usuario** a la pila del kernel (`0x1ACC`, `0x1B06`,
  `0x1B3F`, `0x1B78`, `0x1BB9`, `0x4005`, `0x40CD`, `0x418D`, `0x41CF`), y
* lo **escriben** directamente (Fids 7/8/9/19/20/21 → `out dx,…`, `*(BYTE*)p=dl`, …).

Combinado con `METHOD_NEITHER` + `FILE_ANY_ACCESS` y la **ausencia de validación de
`InputBufferLength`**, esto es exactamente el patrón que da lectura/escritura arbitraria de memoria
del kernel: `READ_PORT_*` / `READ_MM_*` con dirección controlada por el usuario.

### 8.2 Comprobaciones de NULL degeneradas (`add rdi,0x10; je`)
En `NalOsSpecificIoctl` (`0x3FA0`) y en `0x13C0`, MSVC compila la comprobación
`FunctionData == NULL` como **`add reg, 0x10` seguido de `je`** (que solo salta si
`reg == 0xFFFFFFFFFFFFFFF0`), en lugar de `test reg,reg; je`:

| Caso | Bytes | Tipo |
|---|---|---|
| `0x4005`, `0x407E`, `0x4168`, `0x418D`, `0x41CF` | `48 83 c7 10 74 …` | degenerada |
| `0x40CD` | `48 83 c7 10 0f 84 …` | degenerada (`je rel32`) |
| `0x4051`, `0x40A4` | `48 8d 4f 10 48 85 c9 74 …` | **correcta** (`lea`+`test`) |

⇒ **6 de 8** casos tienen la comprobación inoperante: con un `Type3InputBuffer` de usuario la rama de
error `"… FunctionData is NULL"` es **código muerto**. El propio binario lo delata: es el mensaje que se
imprime, pero nunca se alcanza.

### 8.3 Globales relevantes (`.data` BSS)

| RVA | Tamaño | Contenido / uso | Nº de xrefs medidas |
|---|---|---|---|
| `0x7108` | 8 | GS security cookie (`0x0000B0002D992DDF2A32`) | 2 |
| `0x7120` | 4 | **Driver ref-count** (CREATE/CLOSE, y `NAL_WIN_DRIVER_GET_REF_COUNT`) | 3 (`0x10A5`, `0x111B`, `0x5D2045`) |
| `0x7128` | 1 | **Flag global de depuración**: lo escribe `0x2000` (Fid 54) y lo comprueba `0x1F5A` (envoltorio `DbgPrint`) | 2 |
| `0x7130` | 8 | Puntero global consultado por `0x2450` (Fid 28) | 2 (`0x2454`, `0x2500`) |
| `0x7140` | `0xC350`×`0x50` = 2,6 MB | **`Global_WinMemoryMapTable`**: `+0x00` lock, `+0x08` VA kernel, `+0x10` VA usuario, `+0x18`/`+0x20` PA, `+0x28` offset, `+0x2C` tamaño | 6 (`0x2557`, `0x25C8`, `0x26E2`, `0x2711`, `0x2816`, `0x294B`) |
| `0x7180` | … | Raíz del recorrido de registro en `0x1DE0` | 1 (`0x1DE8`) |
| `0x5BFEC0` | `0x100`×`0x110` | Tabla de índices de adaptador (usada por `NAL_WIN_{,IS_}ADAPTER_IN_USE`) | 2 (`0x1231`, `0x5D203E`) |
| `0x3D7A50` | `0xC350`×`0x28` | Segunda tabla limpiada por `DriverEntry` | **1** (`0x5D206C`) — *sin ningún consumidor* |

### 8.4 Imports de la primitiva crítica
`MmAllocateContiguousMemory` `0x25A6` · `MmGetPhysicalAddress` `0x25E7` · `IoAllocateMdl` `0x2662` ·
`MmBuildMdlForNonPagedPool` `0x2679` · `MmMapLockedPagesSpecifyCache` `0x269D` — todos en la función
`0x2520` (asignada a los Fids 38 y 55 de `0x80862007`), con tabla de ranuras de `0xC350` protegida por
`lock cmpxchg`. Esto confirma que la ruta de mapeo de memoria arbitraria es alcanzable desde userland.

---

## 9. LO QUE NO SE PUDO DETERMINAR

1. **No hace falta emulación para los códigos IOCTL.** Se resolvieron estáticamente al 100 %: son
   literales inmediatos en el dispatcher y la tabla de IOCTL *no existe* (§2.4).
2. **Nombres canónicos del SDK NAL para los Fids 1–59 de `0x80862007`.** Solo 6 tienen nombre
   **confirmado por cadenas del propio binario** (47 `NAL_ENABLE_DEBUG_PRINT_FUNCID`,
   48 `NAL_KMEMSET_FUNCID`, 49 `NAL_KUMEMCPY_FUNCID`, 50 `NAL_KKMEMCPY_FUNCID`). El resto se describe
   por **comportamiento verificado** (instrucción/API llamada). Los nombres tipo `NAL_READ_PORT_UCHAR_FUNCID`
   son *etiquetas descriptivas*, **hipótesis** de nomenclatura, no datos extraídos del binario.
3. **Fid 54 de `0x80862007`** comparte el bloque de error con Fid 47 (ambos saltan a `0x1860`, que
   imprime `"NAL_ENABLE_DEBUG_PRINT_FUNCID: FunctionData is NULL"`). La evidencia apunta a que
   **son un par**: Fid 54 (`0x181B` → `0x2000`) **escribe el flag** `byte [0x7128]`, y ese mismo flag es
   el que comprueba el envoltorio `DbgPrint` (`0x1F30`):
   ```
   0x001f5a  cmp     byte ptr [rip + 0x51c7], 1   ; -> 0x7128   (flag de depuración)
   0x001f61  jne     0x11fd5
   ...
   0x001fd5  mov     eax, 0xc86a800b               ; "debug print deshabilitado"
   ```
   Es decir, Fid 54 = *habilitar depuración*, Fid 47 = *emitir cadena*. Que compartan el mensaje de error
   es un artefacto de *copy-paste* en el SDK. Aun así, **el binario no contiene una segunda cadena que
   lo confirme de forma independiente**, así que la identidad exacta de Fid 54 se marca como
   *hipótesis fuerte*, no como hecho.
4. **Fids 1 y 3 de `0x8086200F` son idénticos** (comparten el bloque `0x13A5`) y ambos devuelven el
   stub `0xC86A0003`. Cuál de los dos corresponde a qué semántica **no se puede determinar** de forma
   distinguible, porque el código es literalmente el mismo.
5. **Semántica exacta de los Fids 1–6 de `0x8086200B`** más allá de "operan sobre configuración del
   adaptador vía registro e interrupción". El binario no contiene cadenas que las nombre. Inferir los
   nombres exactos del SDK exigiría las cabeceras `nal.h`, que no están disponibles localmente.
6. **Valores numéricos de los STATUS `0xC86A****`** (`0x0003`, `0x2018`, `0x4002`, `0x4009`, `0x8002`,
   `0x8004`, `0x800B`). Se reportan en crudo; sus nombres simbólicos (`NalStatus…`) no aparecen en el binario.
7. **Semántica de la segunda tabla de 6 MB** (`0x3D7A50`, stride `0x28`, `0xC350` entradas): se limpia en
   `DriverEntry` y se ha medido que tiene **exactamente una referencia en todo el binario** (`0x5D206C`,
   el propio bucle de limpieza). No hay ningún consumidor. Se documenta como scratch reservado sin uso.
8. **El `.rsrc` está truncado**: `SecurityDirectory` apunta a `0x6800` con tamaño `0x1F08`, y el fichero
   acaba en `0xA350`. Los certificados Authenticode van cortados — la firma **no es verificable**
   con este fichero (normal: se extrajo el driver del contenedor PE del RunPE sin su firma completa).

---

## 10. REPRODUCIBILIDAD

Scripts usados (Capstone + radare2), en `/tmp/opencode/iqvw/`:
`pe.py` (parser PE/RVA/sections), `fn.py` (imports + volcado de función anotado),
`xref2.py` (xrefs por sweep lineal), `pdata_check.py` (validación de `.pdata`),
`case_strs.py` (cadenas por caso de jump-table), `final_table.py` (tabla consolidada).

Comprobaciones de una línea para reproducir lo esencial:

```bash
# los 4 IOCTL y el despacho
r2 -q -e scr.color=0 -c 's 0x11150; pd 26' payload_embebido.exe
# la tabla NAL_WIN_* (8 entradas en 0x14244 VA)
r2 -q -e scr.color=0 -c 'px 32 @ 0x14244' payload_embebido.exe
```

---

**Conclusión:** la superficie de IOCTL del driver está completamente caracterizada — 4 códigos
`0x80862007/0b/0f/13`, todos `METHOD_NEITHER` + `FILE_ANY_ACCESS`, con 59+7+3+8 sub-dispatchers
identificados y el mapeo `NAL_WIN_*_FUNCID` establecido con evidencia directa del binario. No se ha
inventado ningún valor: lo no determinable está aislado y justificado en §9.