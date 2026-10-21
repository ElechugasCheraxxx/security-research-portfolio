# REA 6.5.0 — instalación y estado de los cuatro motores

## Qué es

**REA** (`morluto/rea`, MIT, 250k estrellas) es un workflow de ingeniería inversa
que conecta agentes con motores nativos (Ghidra, Hopper, IDA) y con jadx para
Android. No es un decompilador nuevo: es una capa que **orquesta** motores ya
existentes, automatiza la selección de proveedor y estandariza la evidencia.
Instalado desde el repo oficial por clonado + `npm install` + build.

## Estado de los cuatro motores

| Motor | Estado REA | Motor real | Bloqueo |
|---|---|---|---|
| **Ghidra 12.1.2** | `healthy` | ✅ operativo (decompilador nativo x64, JDK 27) | — |
| **IDA** (`ida-registration`) | `healthy` | Registro MCP válido + plugin compilado y cargado | El **análisis** requiere la GUI con el plugin sirviendo en `127.0.0.1:13337`. GUI levantada y funcionando, pero IDA Free tiene el decompilador **en la nube y con batch descompilado deshabilitado** |
| **jadx** | `healthy` | JAR validado (SHA-256 conforme) | — |
| **Hopper v4** | `config_drift` | Binario presente y arranca | **Gate de REA**: la verificación de publisher sólo admite familias de paquetes nativas `deb`/`rpm`/`arch` detectadas de forma nativa; el bundle de Hopper aquí no encaja. No es un fallo de Hopper |

### Lo que hice para que Hopper al menos arrancara
Tenía `libxml2.so.2` ausente (libxml2 2.15 ya no lo trae). Instalé
`libxml2-legacy` (2.13.9), que sí provee el soname antiguo → Hopper resuelve
dependencias. El `doctor` ahora lo marca `healthy`/`unknown` en vez de
`missing_analysis_engine`. El bloqueo restante es **el gate de publisher de
REA**, deliberado: no lo he saltado ni pienso hacerlo — es exactamente la
comprobación que existe para no ejecutar binarios no autenticados.

### Lo que hice para IDA

**IDA está levantada y operativa.** Display virtual `:99` (Xvfb) + openbox como
window manager (sin WM, Qt no abre menús ni acepta `_NET_ACTIVE_WINDOW`).

- Descargué el plugin nativo [`0xshlomil/ida-free-mcp`](https://github.com/0xshlomil/ida-free-mcp)
- Inicialicé su submódulo `idasdk` (167 MB, `HexRaysSA/ida-sdk`)
- Compilé `ida_mcp64.so` contra el SDK con CMake/Ninja
- Creé el registro `rea_cfg/ida_mcp.json` (modo `attached`, protocolo nativo)

Lo que IDA ha analizado del driver `iQVW64E.SYS`, de forma independiente:

- `DriverEntry` en `0x5E2200` (INIT), grafo de control completo
- FLIRT aplicado: reconoce `DriverEntry`, `DbgPrint`, `memmove`, `memset`,
  `_security_check_cookie` — firmas del **Windows Driver Kit 7/10 64bit**
- Lista de funciones con ~112 entradas

#### Tres fallos reales encontrados al integrar el plugin

1. **`NEEDED libida.so` no existía.** El plugin se enlaza contra la stub del
   SDK, pero la instalación real de IDA trae `libida64.so`. `dlopen` fallaba →
   IDA informaba `Configured plugin "ida_mcp" could not be found. Skipping.`
   → Creado `/opt/ida-free/libida.so -> libida64.so`. `ldd -r` pasa limpio.
2. **Falta el sufijo `64`.** IDA exige que los plugins de 64 bits se llamen
   `*64.so` (documentado en su propio `plugins.cfg`). `ida_mcp.so` → `ida_mcp64.so`.
3. **Falta la entrada en `plugins.cfg`.** Añadida con los 5 campos completos.

Tras las tres correcciones el `.so` **se carga** (5 entradas en `/proc/PID/maps`),
pero IDA **no lo registra como plugin invocable**: ni aparece en `Edit > Plugins`
ni en `Quick plugins view` (que solo lista Hex-Rays y DWARF). Queda pendiente el
motivo exacto de rechazo, que IDA solo escribe en su Output window (inundado de
`Command "JumpEnter" failed`, sin scroll utilizable bajo X11 sintético).

#### El límite que decide la cuestión

IDA Free **arranca**, pero su descompilador Hex-Rays lo dice al propia ventana:

> *The decompilation functionality is provided by a decompiler plugin… Your copy
> of the decompiler has limited functionality, namely: **1. Batch decompilation is
> disabled** 2. **It is cloud based** 3. Only x64 code is supported.*

Es decir: aunque el plugin MCP llegara a registrar, `decompile` **no puede
funcionar automáticamente**, por diseño de licencia. **IDA Free no puede ser un
proveedor automatizado de REA**; sí sirve como **verificador manual de terceros**
(FLIRT + desensamblado propio + grafo). Se declined usar el decompilador cloud:
enviar el código de un driver a un servicio de terceros no es algo que vaya a
hacer sin que lo pidas explícitamente.

### Lo que hice para jadx
Descargué `jadx-headless-mcp-0.7.1-all.jar` (40,6 MB) del release oficial y
verifiqué su SHA-256 contra el digest fijado por REA:
`6e5eacf5…573ff75` → **OK**.

## Resultados reales obtenidos

- **Driver `iQVW64E.SYS`**: `procedure_count=112`, `string_count=130`,
  `segment_count=8`, x86_64. PDB `iqvw64e.pdb` (GUID be0abb50-…) confirmado por
  Ghidra.
- **Descompilación del dispatcher `IRP_MJ_DEVICE_CONTROL` (0x11150)** vía Ghidra:
  pseudo-C limpio que **confirma de forma independiente** lo que habíamos
  obtenido con r2-ghidra y Unicorn, y añade dos cadenas:
  `"NalDeviceControl: InputBuffer was NULL"` y
  `"Nal Windows DriverDeviceControl: Invalid IOCTL code 0x%0x"`.
- **RunPE (`execute_stage.bin`)**: `procedure_count=157`, análisis limpio.

## Limitación relevante para nuestro caso

El análisis estático del **loader desempaquetado** (`unpacked_loader.exe`, 6,4 MB)
**expira** (`provider_timeout`): su sección `.3q-` son 6,1 MB de bytecode de VM
más 1,3 MB de intérprete desincronizado, que el auto-análisis de Ghidra no puede
procesar en tiempo razonable. Es coherente con lo ya sabemos: el `.3q-` requiere
devirtualización instrumentada (traza + reificación), no descompilación estática
masiva. Para ese objetivo la vía correcta sigue siendo **speakeasy** (que ya
funciona) más el lifting manual por traza.

## Ficheros

- Repo clonado: `run/rea/rea/` (commit `ab45bf6`)
- Configuración de motores: `run/rea_cfg/`
  - `ida_mcp.json`
  - `jadx-headless-mcp-0.7.1-all.jar`
  - `rea_env.sh` (exporta las tres variables)
- Resultados: `run/rea_out/*.md`