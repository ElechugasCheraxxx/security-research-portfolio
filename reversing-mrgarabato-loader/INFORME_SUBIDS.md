# INFORME — Validación dinámica de los sub-identificadores (speakeasy)

## Resultado: 59/59 coinciden con el análisis estático

Todos los FunctionIds del IOCTL `0x80862007` se recorrieron despachando un
`IRP_MJ_DEVICE_CONTROL` real a través del `MajorFunction[14]` que el propio driver
registró, y registrando con un *code hook* qué direcciones del driver se ejecutan.
**Las 59 rutas coinciden exactamente con las que el análisis estático dedujo.**

Herramienta: speakeasy-emulator 1.6.1 (Mandiant), venv aislado `/tmp/opencode/speakeasy2`.
Script: `run/enum_subids.py` → `subids_out.txt`, `subids_dinamico.json`.

## Mapa validado del IOCTL `0x80862007` (handler `0x13C0`)

| Fid | Caso | Hoja alcanzada | Acción | Estático |
|---|---|---|---|---|
| 1 | `0x1402` | `in al, dx` | ReadPortUchar | ✓ |
| 2 | `0x1421` | `in ax, dx` | ReadPortUshort | ✓ |
| 3 | `0x1441` | `in eax, dx` | ReadPortUlong | ✓ |
| 4–6 | `0x1950` | — | inválido | ✓ |
| 7 | `0x1460` | `out dx, al` | WritePortUchar | ✓ |
| 8 | `0x1483` | `out dx, ax` | WritePortUshort | ✓ |
| 9 | `0x14A6` | `out dx, eax` | WritePortUlong | ✓ |
| 10–12 | `0x1950` | — | inválido | ✓ |
| 13 | `0x14C8` | `*(BYTE*)p` | ReadMmUchar | ✓ |
| 14 | `0x14E7` | `*(WORD*)p` | ReadMmUshort | ✓ |
| 15 | `0x1507` | `*(DWORD*)p` | ReadMmUlong | ✓ |
| 16–18 | `0x1950` | — | inválido | ✓ |
| 19 | `0x1526` | `*(BYTE*)p = dl` | WriteMmUchar | ✓ |
| 20 | `0x1549` | `*(WORD*)p = dx` | WriteMmUshort | ✓ |
| 21 | `0x156C` | `*(DWORD*)p = edx` | WriteMmUlong | ✓ |
| 22–24 | `0x1950` | — | inválido | ✓ |
| 25 | `0x158E` | `0x2AC0` | MmMapIoSpace | ✓ |
| 26 | `0x15B5` | `0x21C0` | MmUnmapIoSpace | ✓ |
| 27 | `0x15DC` | `0x1DB0` | KeQueryPerformanceCounter | ✓ |
| 28 | `0x15F8` | `0x2450` | lectura de global | ✓ |
| 29–34 | `0x1950` | — | inválido | ✓ |
| 35 | `0x162F` | `0x23C0` | KeStallExecutionProcessor | ✓ |
| 36 | `0x1614` | `0x1D50` | retardo en µs | ✓ |
| **37** | `0x164A` | **`0x2010`** | **MmGetPhysicalAddress** | ✓ |
| 38 | `0x166A` | `0x25A6` | alloc + mapeo no paginado | ✓ |
| 39 | `0x1697` | `0x28E0` | MmFreeContiguousMemory | ✓ |
| 40 | `0x17B7` | `0x1ED0` | refcount++ (`lock xadd`) | ✓ |
| 41 | `0x17D6` | `0x1EF0` | refcount-- | ✓ |
| 42 | `0x17F5` | `0x1F10` | `lock cmpxchg` | ✓ |
| 43–46 | `0x1950` | — | inválido | ✓ |
| 47 | `0x183C` | `0x1F30` | NAL_ENABLE_DEBUG_PRINT | ✓ |
| 48 | `0x16B8` | `0x16E0` | NAL_KMEMSET | ✓ |
| 49 | `0x16FD` | `0x172B` | NAL_KUMEMCPY | ✓ |
| 50 | `0x1748` | `0x1776` | NAL_KKMEMCPY | ✓ |
| 51 | `0x1793` | `0x1EA0` | memcpy kernel→user | ✓ |
| 52–53 | `0x1950` | — | inválido | ✓ |
| 54 | `0x181B` | `0x2000` | flag global de depuración | ✓ |
| **55** | `0x187D` | **`0x25A6`** | **MmAllocateContiguousMemory + MDL + MmMapLockedPagesSpecifyCache** | ✓ |
| 56 | `0x18B0` | `0x2770` | MmUnmapLockedPages + IoFreeMdl + MmFreeContiguousMemory | ✓ |
| 57 | `0x18D6` | `0x29C0` | MmMapIoSpace | ✓ |
| 58 | `0x1901` | `0x2220` | MmMapIoSpace | ✓ |
| 59 | `0x192C` | `0x1DE0` | recorrido de registro | ✓ |

**33 implementados, 26 inválidos** (`0x1950` = `STATUS 0xC86A2018`).

## Confirmación explícita de la primitiva de exploit

El Fid **55** alcanza `0x25A6`, que está dentro de la función `0x258D..0x2743`, donde
se encadena `MmAllocateContiguousMemory` → `MmGetPhysicalAddress` → `IoAllocateMdl` →
`MmBuildMdlForNonPagedPool` → `MmMapLockedPagesSpecifyCache`. **Dinámicamente
confirmado**, ya no es una hipótesis de desensamblado.

El Fid 37 → `0x2010` (`MmGetPhysicalAddress`) queda igualmente confirmado.

## Los otros tres IOCTL también despachan

| IOCTL | Handler | Fids | Comportamiento observado |
|---|---|---|---|
| `0x8086200B` | `0x1A60` | 1–7 | 1–6 entran en el subsistema NAL (hoja `0x332C`); el 7 toma la ruta corta `0x1BE4` |
| `0x8086200F` | `0x1330` | 1–3 | **Fids 1 y 3 ejecutan código idéntico** (`0x3DF0`→`0x3DF5`), lo que confirma que el subagente los marcó como indistinguibles |
| `0x80862013` | `0x3FA0` | 1–8 | Todos entran en `NalOsSpecificIoctl`. Los Fids 7 y 8 ejecutan 2279 y 2010 instrucciones: recorren la tabla de BSS buscando adaptadores |

## Detalles que solo se ven emulando

- **Fid 35 ejecuta 7066 instrucciones.** Es `KeStallExecutionProcessor` en un bucle de
  espera activa: una primitiva de retardo deliberado, no un fallo.
- **Fids 1–3, 7–9 ejecutan `in`/`out`.** El driver da al usuario modo lectura y
  escritura de **puertos de E/S arbitrarios** desde espacio de usuario. Con Fids 37/38/55
  eso convierte el driver en acceso completo a hardware y a memoria del kernel.

## Un punto que sigue abierto

El subagente affirmative que `0x354B` (`NalDeviceControl`) es código muerto con cero
callers. En esta corrida de speakeasy los Fids 1–6 de `0x8086200B` **no** pasan por
`0x354B` (terminan en `0x332C`), mientras que en mi emulación con Unicorn sí se ejecutó.
Ambos resultados dependen de cómo se montó el contexto del dispositivo, que es
precisamente lo que no se puede reproducir sin un adaptador real. **Lo dejo como no
resuelto** en lugar de elegir una de las dos hipótesis.

## Conclusión

La superficie de ataque del driver queda cerrada y **triplemente verificada** (estática
del subagente, mi emulación con Unicorn, y speakeasy):

- **I/O de puertos arbitrario** desde user mode (Fids 1–3, 7–9)
- **Mapeo de memoria física y del kernel** (Fids 25, 37, 38, 55, 57, 58)
- **Copia de memoria kernel→user** sin sondeo (Fids 49–51)
- Todo ello vía `METHOD_NEITHER` + `FILE_ANY_ACCESS`, sin `ProbeForRead`/`ProbeForWrite`
  y con el `InputBufferLength` sin comprobar

Eso es exactamente lo que convierte a `iQVW64E.SYS` en un driver BYOVD útil: no hace
falta ningún exploit de kernel, solo la firma válida.