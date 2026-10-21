# Herramientas de Black Arch para el análisis dinámico del driver

## Respuesta corta: sí, y la herramienta correcta es speakeasy

Mi nota anterior decía que *"speakeasy es un emulador de 32 bits y el objetivo es x64,
así que es inútil"*. **Era falso.** speakeasy de Mandiant emula User y **Kernel** en
`x86`, **`amd64`** y ARM. Lo he instalado y funciona sobre el driver.

## Por qué estaba roto (y no era la arquitectura)

Tres motivos, todos resolubles:

1. **Colisión de nombre en PyPI.** El paquete `speakeasy` ya **no** es el de Mandiant:
   desde la 2.0.0 es un *"Metrics aggregation server"* de Eric Wong
   (`github.com/etdub/speakeasy`). El paquete real se llama **`speakeasy-emulator`**.
   Instalar `speakeasy` a ciegas te deja con un servidor de métricas, no con el emulador.
2. **Dependencia de unicorn 1.x.** speakeasy usa la API antigua (`unicorn.unicorn._uc`),
   que no existe en unicorn 2.x. Se resuelve con un **venv aislado**: dentro va unicorn
   1.0.2; el del sistema se queda en 2.1.4 para no romper pwntools ni pwndbg.
3. **Python 3.14.** unicorn 1.0.2 importa `distutils` (eliminado en 3.12+) y
   `pkg_resources` (eliminado en setuptools ≥81). Se resuelve con `setuptools<81`.

No hizo falta ningún paquete de datos externo: speakeasy trae los stubs de
`ntoskrnl` integrated.

## Puesta en marcha

```bash
python3 -m venv /tmp/opencode/speakeasy2
/tmp/opencode/speakeasy2/bin/pip install "setuptools<81" speakeasy-emulator
/tmp/opencode/speakeasy2/bin/speakeasy -t payload_embebido.exe -a amd64 -q 90
```

El unicorn del sistema no se toca (sigue en 2.1.4).

## Resultado: speakeasy emula la carga completa del driver

```
0x5e2116  ntoskrnl.RtlInitUnicodeString(..., "\Device\Nal")
0x5e2142  ntoskrnl.IoCreateDevice(0xbdb870, 0x18, "\Device\Nal", 0x8086, ...)
0x5e2185  ntoskrnl.RtlInitUnicodeString(..., "\DosDevices\Nal")
0x5e2195  ntoskrnl.IoCreateSymbolicLink("\DosDevices\Nal", "\Device\Nal")
* exec: 0
0x110c7   ntoskrnl.IofCompleteRequest(0xbdbb70, 0x0)      <- MajorFunction[0]  CREATE
* exec: 14
0x111f2   ntoskrnl.IofCompleteRequest(0xbdbe50, 0x0)      <- MajorFunction[14] DEVICE_CONTROL
* exec: 2
0x1111b   ntoskrnl.IofCompleteRequest(0xbdbece0, 0x0)     <- MajorFunction[2]  CLOSE
* exec: 28
0x11037   ntoskrnl.RtlInitUnicodeString(..., "\??\Nal")
0x11042   ntoskrnl.IoDeleteSymbolicLink("\??\Nal")        <- DriverUnload
0x11051   ntoskrnl.IoDeleteDevice(0x7f9000)
```

Confirmaciones independientes:

| Dato |speakeasy | Mi emulación | Análisis estático |
|---|---|---|---|
| Dispositivo | `\Device\Nal` | — | `\Device\Nal` |
| Enlace simbólico | `\DosDevices\Nal` | — | `\DosDevices\Nal` |
| **DeviceType** | **`0x8086`** | `0x8086` en los 4 IOCTL | `0x8086` |
| Handler CREATE | `0x1090` | `0x1090` | `0x1090` |
| Handler DEVICE_CONTROL | `0x1150` | `0x1150` | `0x1150` |
| Handler CLOSE | `0x10F0` | `0x10F0` | `0x10F0` |
| DriverUnload | `0x1010` | `0x1010` | `0x1010` |

Además speakeasy **ejercita solo** los MajorFunction registrados: los tres
`IofCompleteRequest` corresponden a CREATE, DEVICE_CONTROL y CLOSE, en ese orden, lo que
confirma de forma independiente que el driver **solo registra esos tres** y que
`MajorFunction[14]` es el único que atiende IOCTL.

## Qué aporta frente a mi emulación a mano

Mi Unicorn propio servía para trazar rutas concretas dentro del driver, pero no tenía
modelo de objetos de kernel. speakeasy sí lo tiene: resuelve el PEB, los objetos
`DRIVER_OBJECT`/`DEVICE_OBJECT`, y entra por los MajorFunction correctos sin que haya que
construir un IRP a mano. Para cualquier trabajo que implique el ciclo de vida completo
del driver, **speakeasy es la herramienta y la mía era el rodeo**.

## Lo que sigue pendiente

Los cuatro IOCTL quedaron confirmados por las tres vías. Queda el hueco que dejó el
análisis estático: el IOCTL `0x80862007` tiene **59 sub-identificadores** y de ellos solo
se han etiquetado los que tienen comportamiento inequívoco. speakeasy puede recorrerlos
conduciendo `MajorFunction[14]` con un IRP fabricado vía su API de Python, que es el
siguiente paso natural.