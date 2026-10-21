# Triage estático — MrGarabato-ByPassEmulator.exe / MrGarabato-LoaderAdvanced.exe

Fecha: 2026-10-14
Entorno: Black Arch Linux (31 GB RAM, 8 cores)

## 1. Identificación

| | ByPassEmulator | LoaderAdvanced |
|---|---|---|
| SHA-256 | `b9d04b25c581b7f69fcf9d40f9b7624bc13f9d18e9431d9e7cd89212da80d005` | `8cf34c97e2b660f1bfea68e0ecf6ff4731191d4e022f2337999a802aa35c887a` |
| Tamaño | 7.834.624 | 7.832.064 |
| Formato | PE32+ x86-64, consola (Subsystem 3) | idem |
| Linker | MSVC 14.39 (VS2022 ~17.9+) | idem |
| TimeDateStamp | 2026-03-29 23:56:40 UTC | 2026-04-24 16:53:11 UTC |
| Firma digital | ninguna (Security Directory = 0) | ninguna |
| ASLR | **NO** (DynamicBase ausente) + relocaciones eliminadas → base fija `0x140000000` | idem |
| Manifiesto | `requestedExecutionLevel level='requireAdministrator'` (pide UAC) | idem |

## 2. Estructura del packer (mismo esquema, distinto contenido)

| # | Nombre (bypass / loader) | VA | VSZ | RAW | Entropía | Papel |
|---|---|---|---|---|---|---|
| 0 | `.text` | 0x1000 | 0x162DC | **0** | — | destino de desempaquetado |
| 1 | `.rdata` | 0x18000 | 0x7AFC | **0** | — | destino |
| 2 | `.data` | 0x20000 | 0x1188 | **0** | — | destino |
| 3 | `.pdata` | 0x22000 | 0xEE8 | **0** | — | destino |
| 4 | `.7 f` / `.eff` | 0x23000 | 0x7F7D93 | **0** | — | buffer de descompresión |
| 5 | `.zzc` / `.3rs` | 0x81B000 | 0xE00 | 0xE00 | 0.298 | IAT + tabla de 25 RVA |
| 6 | `.3q-` / `.w7/` | 0x81C000 | 0x76E8A4 | 0x76EA00 | **7.948** | blob cifrado |
| 7 | `.rsrc` | 0xF8B000 | 0x8E48 | 0x9000 | 7.899 | icono PNG 256² + manifiesto |

- Las secciones 0–4 suman **exactamente 0x800000 = 8 MiB** de espacio virtual con `SizeOfRawData = 0`.
  El packer reconstruye una imagen de 8 MiB en memoria a partir del blob de 7,44 MiB de la sección 6.
- Nombres de sección aleatorios → builder automatizado que genera un nombre distinto por build.
- La IAT (`RVA 0x81B000`) vive en `.zzc`, pero el Import Directory (`RVA 0xE22348`) está en el blob → el loader lo resuelve en runtime.

## 3. El blob está cifrado (confirmado)

Perfil de entropía por bloques de 256 KiB dentro de `.3q-`:

```
+0x000000..+0x5C0000   7.994 – 7.999   <- distribución uniforme (cifrado de flujo)
+0x600000              7.580          <- transición
+0x640000..+0x740000   6.973 – 7.026   <- solo ~1,5 MB,entropy de dato comprimido
```

Pruebas negativas ejecutadas:

| Prueba | Resultado |
|---|---|
| XOR 1 byte (0x00–0xFF) sobre cabecera del blob | sin `MZ` ni `PE` |
| XOR 1 byte sobre bloque del EP (0x144917) | sin prólogos MSVC (`48 89 5c 24`, `55 48 8b ec`, …) |
| `zlib` / `zlib-raw` / `lzma` / `bz2` en offsets 0, 0x100, 0x400, 0x600000 | todos fallan |
| Firmas embebidas | `MZ`=111, `78 9C`=101, `1F 8B`=1 → **exactamente lo esperado por azar** en 7,8 MB de datos aleatorios |

**Conclusión: cifrado real (clave + algoritmo dentro del stub), no simple XOR ni compresión directa.**

## 4. Anti-análisis

- **EP (0x960917 / 0xD88535) cae DENTRO del blob cifrado** → no es código ejecutable tal cual.
- **TLS Directory presente pero señuelo**: `AddressOfCallBacks = NULL`, resto del directorio basura (`Characteristics = 0x300000`). No ejecuta nada.
- **Load Configuration**: `SEHandlerTable = 0`, `SEHandlerCount = 0` → sin handlers SEH.
- **Export Directory corrupto** (0xC4F bytes): el puntero de nombre resuelve al propio encabezado `MZ` en el offset 0. r2/rabin2 lo muestran como binario basura. Anti-parsing.
- Solo **26 imports, exactamente uno por DLL**, con selección **aleatoria** entre builds → IAT generada, no la del programa original.
- `BaseReloc = 0`.

## 5. Imports = perfil loader/dropper con C2

| DLL | Función | Capacidad |
|---|---|---|
| urlmon | `URLDownloadToFileA/W` | descarga de payload |
| WINHTTP | `WinHttpSetTimeouts` / `WinHttpReceiveResponse` | comunicación C2 |
| SHELL32 | `ShellExecuteA` | ejecución del payload |
| ADVAPI32 | `RegSetValueExW` | persistencia |
| ntdll | `RtlAdjustPrivilege` | elevación de privilegios |
| USER32 | `LoadImageA`, `ShowWindow`, `CharUpperBuffW` | UI |
| SHLWAPI | `PathFileExistsA` | comprobaciones de entorno |
| KERNEL32 | `LoadLibraryA`, `GetProcAddress`, `LocalAlloc/Free` | resolución dinámica |

Diferencias entre ambos (evidencia de builder con *pool* de imports):

| ByPassEmulator | LoaderAdvanced |
|---|---|
| `URLDownloadToFileW` | `URLDownloadToFileA` |
| `WinHttpSetTimeouts` | `WinHttpReceiveResponse` |
| `_initterm`, `rand`, `__std_terminate` | `_cexit`, `malloc`, `getenv`, `__C_specific_handler` |

## 6. Los dos binarios NO son el mismo programa

- Solo **0,70 %** de los bytes del prefijo común coinciden (54 759 / 7 832 064).
- Prefijo común: **136 bytes** (cabeceras DOS hasta `TimeDateStamp`, que difiere).
- Sufijo común: **36 646 bytes** = la sección `.rsrc` completa (icono y manifiesto **idénticos**, mismo SHA-256 en el PNG).
- Icono: silueta de conejo morado 256×256 PNG — "MrGarabato".

→ **Dos compilaciones independientes del mismo builder**, con payload/configuración distintos. Plantilla idéntica, contenido cifrado distinto.

## 7. Contexto / atribución

- "MrGarabato" aparece públicamente como autor de un inyector para Roblox
  (`Injectador - ByMrGarabato.exe`, ruta `MrGarabato & MrZoom\Ultra Injectador Menu\v4`).
- `mrgarabato.com` opera una plataforma de licencias/HWID para bots.
- Existe trabajo público (abr-2026) sobre *bypass de detección de emulador Android* leyendo
  `ro.build.product`, `/proc/mounts` (vboxsf), `libhoudini`, `bluestacks`, `ro.product.cpu.abilist`.
  Perfil coherente con el nombre "ByPassEmulator".

## 8. Estado del análisis

**Estático agotado.** El código y los datos útiles están cifrados, y el propio desempaquetador
no es localizable estáticamente porque el EP cae dentro del material cifrado y no hay
TLS/SEH alternative entry point. El siguiente paso obligatorio es **dinámico**: ejecutar,
dejar que desempaquete y volcar memoria.

Restricciones del entorno actual:
- No hay VM utilizable: `virsh` no conecta con ningún daemon, `vboxmanage list vms` vacío.
- Sí hay Wine 11.19, Ghidra (`/opt/ghidra`), Rizin, capa, YARA.