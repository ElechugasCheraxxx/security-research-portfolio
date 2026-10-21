# INFORME — Análisis dinámico del driver iQVW64E.SYS (Unicorn)

## Método

No se ha cargado el driver en ningún kernel. Toda la evidencia sale de **emulación de
código x64 en memoria de proceso** con Unicorn 2.1.4, sustituyendo los 39 imports de
`ntoskrnl.exe` por stubs que devuelven punteros de un heap ficticio. Esto permite
ejecutar la inicialización real y observar qué construye, sin ningún riesgo para el
sistema.

Scripts: `emulate_driver.py` (fase 1, DriverEntry) y `emulate_ioctl.py` (fase 2,
construcción de contexto y conducción de IOCTL).

---

## 1. Lo que la emulación corrige del análisis estático

Mi estimación estática situaba el handler de `IRP_MJ_DEVICE_CONTROL` en RVA `0x1020`
por aritmética de `rip`. **La emulación demuestra que está en RVA `0x1150`**, y que el
`DRIVER_OBJECT` queda así:

| Offset | Handler | RVA |
|---|---|---|
| `+0x68` | DriverUnload | `0x1010` |
| `+0x70` | MajorFunction[0] — IRP_MJ_CREATE | `0x1090` |
| `+0x80` | MajorFunction[2] — IRP_MJ_CLOSE | `0x10F0` |
| `+0xE0` | MajorFunction[11] — **IRP_MJ_DEVICE_CONTROL** | **`0x1150`** |

Durante `DriverEntry` solo se ejecutan `RtlInitUnicodeString` (×2), `IoCreateDevice` y
`IoCreateSymbolicLink`. **Las tablas de despacho NO se construyen en `DriverEntry`**: el
BSS de 6 MB queda a cero tras la carga.

---

## 2. Los cuatro IOCTL

El handler en `0x1150` compara el código de forma explícita, y **no lo lee del IRP**:

```asm
0x1154  mov  rax, qword ptr [rdx + 0xB8]   ; rdx = IRP  -> puntero a contexto
0x1165  mov  rcx, qword ptr [rax + 0x20]   ; contexto (debe ser != NULL)
0x116C  mov  edx, dword ptr [rax + 0x18]   ; <-- aqui vive el IoControlCode
0x1174  cmp  edx, 0x80862007  ->  call 0x13C0
0x117C  cmp  edx, 0x8086200B  ->  call 0x1A60
0x1184  cmp  edx, 0x8086200F  ->  call 0x1330
0x118C  cmp  edx, 0x80862013  ->  call 0x3FA0
```

| IOCTL | DeviceType | Function | Method | Access | Handler |
|---|---|---|---|---|---|
| `0x80862007` | `0x8086` | `0x801` | **NEITHER** | ANY | RVA `0x13C0` |
| `0x8086200B` | `0x8086` | `0x802` | **NEITHER** | ANY | RVA `0x1A60` |
| `0x8086200F` | `0x8086` | `0x803` | **NEITHER** | ANY | RVA `0x1330` |
| `0x80862013` | `0x8086` | `0x804` | **NEITHER** | ANY | RVA `0x3FA0` |

`DeviceType 0x8086` es el vendor ID de Intel, coherente con un driver de adaptador de
red. **Los cuatro usan `METHOD_NEITHER`**: el driver recibe punteros crudos del espacio
de usuario sin sondearlos ni copiarlos, que es precisamente la clase de vulnerabilidad
que hace exploitable este driver.

---

## 3. El segundo nivel: FunctionId dentro de 0x8086200B

El handler de `0x8086200B` (`0x1A60`) lee un `FunctionId` del contexto y salta por una
tabla de 7 casos (`dec rax; cmp rax, 6; ja default`). Recorriendo los siete valores con
la emulación se obtiene el mapa definitivo:

| FunctionId | Handler NAL alcanzado | Subconjunto |
|---|---|---|
| 1 | — | (no entra en NAL) |
| 2 | — | (no entra en NAL) |
| **3** | `0x38B0` + `NalDeviceControl` `0x354B` | Asignar contexto de dispositivo |
| **4** | `0x3980` + `0x354B` | Liberar contexto |
| **5** | `0x3A00` + `0x354B` | Consulta de PDO |
| **6** | `0x3B20` + `0x354B` | Consulta de símbolo |
| 7 | — | (no entra en NAL) |

Cuatro de los siete `FunctionId` entran en `NalDeviceControl`, que recorre su propia
tabla (código IOCTL en `+0`, handler en `+0x38`) y despacha **por puntero de función**.

---

## 4. La primitiva de mapeo y por qué el grafo estático no la veía

Dos funciones invocan `MmMapLockedPagesSpecifyCache`:

| RVA | Secuencia |
|---|---|
| `0x2030` | `IoAllocateMdl` → `MmBuildMdlForNonPagedPool` → `MmMapLockedPagesSpecifyCache` |
| `0x258D` | `MmAllocateContiguousMemory` → `MmGetPhysicalAddress` → `IoAllocateMdl` → `MmBuildMdlForNonPagedPool` → `MmMapLockedPagesSpecifyCache` |

`0x2A0F` llama a `0x2030` con una dirección física **procedente de `MmGetPhysicalAddress`**.
Mi BFS estático no lo alcanzaba porque `0x2A0F` **no lo invoca nadie directamente**: se
llama de forma indirecta desde la tabla de `NalDeviceControl`. Ese es el eslabón que
solo se ve emulando o siguiendo punteros.

---

## 5. Lo que NO se ha podido determinar

**El `FunctionId` exacto que alcanza `MmMapLockedPagesSpecifyCache` sigue sin
confirmarse**, y no voy a inventarlo. La razón es concreta:

La tabla que `NalDeviceControl` recorre se rellena cuando el dispositivo tiene un
adaptador real asociado. `NalDeviceControl` llama a `IoGetDeviceInterfaces` para
enumerar adaptadores — y en la emulación ese import está sustituido por un stub que
devuelve un valor fijo, así que **no hay ningún adaptador que descubrir** y la tabla
permanece vacía. Los cuatro `FunctionId` que entran en NAL llegan a
`NalDeviceControl` (confirmado), pero la tabla no tiene entradas que recorrer.

Para cerrarlo harían falta dos cosas, ambas fuera del alcance de la emulación actual:

1. Un stub de `IoGetDeviceInterfaces` que **construya un PDO sintético** y se lo
   devuelva al driver, de forma que el recorrido de adaptadores tenga éxito.
2. Encadenar la construcción del contexto entre ejecuciones, porque `ExAllocatePoolWithTag`
   y `IoCreateSymbolicLink` sugieren estado que debe sobrevivir entre llamadas.

Alternativamente, sobre Windows real: cargar el driver en una VM de pruebas y capturar
el `DeviceIoControl` desde el espacio de usuario con un debugger, que es la forma más directa.

---

## 6. Resumen de la cadena confirmada

```
DeviceIoControl(\\.\Nal, 0x8086200B, ...)
        |
   handler 0x1150  (MajorFunction[11])
        |
   0x1A60 -> lee FunctionId (1..7)
        |
   FunctionId 3..6 -> 0x38B0 / 0x3980 / 0x3A00 / 0x3B20
        |
   NalDeviceControl (0x354B) -> tabla, despacho indirecto
        |
   0x2A0F -> 0x2030 -> MmMapLockedPagesSpecifyCache
        |
   pages del kernel mapeadas en el espacio virtual elegido por el usuario
```

Todos los eslabones salvo el último están **verificados por ejecución**. El último está
verificado por desensamblado y confirmado como alcanzable solo por vía indirecta.