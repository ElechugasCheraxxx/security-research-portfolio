# Índice de herramientas — Black Arch (instalación actual)

**Fecha:** 2026-10-14 · Host: Black Arch Linux · 7.204 paquetes instalados
Repos activos: `core`, `extra`, `multilib`, `blackarch`

Grupos de herramientas de seguridad instalados:

| Grupo | Paquetes |
|---|---|
| `blackarch-scanner` | 672 |
| `blackarch-webapp` | 454 |
| `blackarch-exploitation` | 325 |
| `blackarch-crypto` | 120 |
| **`blackarch-reversing`** | **111** |
| `blackarch-wireless` | 94 |
| **`blackarch-malware`** | **54** |

---

## 1. Decompiladores / Desensambladores

| Herramienta | Ruta | Estado | Notas |
|---|---|---|---|
| **Ghidra 12.1.2** | `/opt/ghidra` | ✅ | headless en `/opt/ghidra/support/analyzeHeadless` |
| **rizin / radare2** | `/sbin/r{izin,adare2}` | ✅ | con backend **rz-ghidra** (`pd:g`) — usado en este análisis |
| **Cutter** | `/sbin/cutter` | ✅ | GUI de rizin |
| **IDA Free** | `/usr/bin/ida64` | ✅ | desensamblador excelente, decompilador solo 32-bit |
| **Hopper** | `/usr/bin/hopper` | ⚠️ | por verificar modo headless |
| **RetDec** (suite) | `/usr/bin/retdec-*` | ✅ | `decompiler`, `unpacker`, `fileinfo`, `bin2pat`, `pat2yara` |
| **Binary Ninja** | grupo reversing | ⚠️ | requiere licencia |
| **JEB** | grupo reversing | ⚠️ | 4 variantes (android/arm/intel/mips/webasm) |

> **Lección aplicada**: con código desincronizado a propósito, cada motor falla de forma
> distinta. Conviene siempre probar **varios** y quedarse con el que mejor recupere.

## 2. Análisis estático

| Herramienta | Ruta | Uso |
|---|---|---|
| **angr 9.2.194** | venv `/tmp/opencode/angr-venv` | CFG recovery, ejecución simbólica |
| **Triton** | módulo python | emulación simbólica con taint — ideal para VM-obfuscation |
| **bindead** | `/sbin/bindead` | análisis profundo, similitud de código, recuperación de símbolos |
| **unicorn 2.1.4** | python | emulación de CPU |
| **capstone 5.0.9** | python | desensamblado |
| **lief 0.17.0** | python | manipulación de PE/ELF |
| **pefile** | python | parsing de PE |
| **r2pipe 1.9.8** | python | control de rizin desde python |
| **vivisect 1.3.2** | python | framework RE en python |
| **pypacker 5.4** | python | detección de packers |
| **binwalk**, **foremost**, **yara** | `/sbin/` | carve, firmas |

### Fix aplicado: angr
angr estaba **roto** (paquete de Black Arch compilado contra python anterior):
```
AttributeError: property 'filename' of 'CLexer' object has no setter
```
Causa: **pycparser 3.11** (rewrite mayor) incompatible con angr 9.2.194.
Arreglo (sin tocar el sistema):
```bash
python3 -m venv --system-site-packages /tmp/opencode/angr-venv
/tmp/opencode/angr-venv/bin/pip install pycparser==2.22
```
+ shim `angr_shim.py` que inyecta `PEStubs` (ausente en cle 9.2.160).
**No usar** `pip install angr==9.2.194`: compila libvex y el build aislado reintroduce pycparser 3.x.

## 3. Extracción de cadenas

| Herramienta | Ruta | Estado |
|---|---|---|
| **FLOSS** (FLARE) | `/sbin/floss` | ⚠️ roto: requiere `vstruct<2` (yo instalé la 2.0.2, falta `vstruct.cparse`) |
| `strings`, `rabin2 -z` | sistema | ✅ |
| descifrador propio | `run/decode_strings.py` | ✅ funcionando — `plain[i]=cipher[i]^(0x53+i)` |

## 4. Emulación / Análisis dinámico

| Herramienta | Ruta | Notas |
|---|---|---|
| **damm** | `/sbin/damm` | emulador de Windows en Python |
| **Wine 11.19** | `/sbin/wine` | usado para ejecutar el sample; `WINEDEBUG=+relay` traza APIs |
| **frida 17.7.3** | `/sbin/frida` + python | hooking |
| **speakeasy** | — | ❌ no instalado |
| **zerowine** | — | ❌ no instalado |

Debuggers/instrumentación: `gdb`, `lldb`, **`rr`** (record/replay), `strace`, `ltrace`, `valgrind`.
Intel PIN: `pin`, `pintool`, `pintool2`, `dynamorio`.

## 5. Desempaquetado / Volcado de memoria

| Herramienta | Estado |
|---|---|
| `unblob` | ✅ `/sbin/unblob` |
| `hollows-hunter` | ❌ no instalado (sería útil: dumpea memoria inyectada) |
| `pcileech`, `ppee`, `pclm` | ✅ (volcado de memoria física) |
| scripts propios | ✅ `run/dump_mem.py` (vuelca `/proc/PID/mem`), `run/fake_dmi.sh` (DMI falso) |

## 6. Análisis de malware

| Herramienta | Ruta |
|---|---|
| **viper** | `/sbin/viper` |
| **malcom** | `/sbin/malcom` |
| **pe-sieve / pesieve** | grupo malware |
| malheur, malscan, maltrieve, vipermonkey, polyquark, quark-engine | grupo malware |
| clamscan, yara, vt-cli, osslsigncode | grupo malware |

## 7. PE / Estáticos Windows

`pedump`, `pescan`, `pehash`, `pesec`, `readpe`, `osslsigncode`, `peframe`, `resourcehacker`,
`packerid`, `detect-it-easy` (DIE), `pestudio` (no instalado).

## 8. Red

`tcpdump`, `tshark`, `mitmproxy`, `fakenet-ng`, `nmap`, `ncat`, `wireshark-cli`.

## 9. Módulos Python (pip)

```
angr 9.2.194      angrop            capstone 5.0.9     claripy 9.2.221
construct 2.10.70 flare-floss 3.1.1 frida 17.7.3      frida-tools 14.11.0
keystone-engine   lief 0.17.0       pefile 2024.8.26  pwntools 4.15.0
pyelftools        pypacker 5.4      pyvex 9.2.221     r2pipe 1.9.8
unicorn 2.1.4     vivisect 1.3.2    z3-solver 4.16.0   vstruct 2.0.2 (⚠️ incompatible)
```

## 10. Otros relevantes

| Herramienta | Ruta | Notas |
|---|---|---|
| **mingw-w64** | `x86_64-w64-mingw32-gcc` | compilar PE/DLL de prueba y shims |
| **anarchivos .NET** | `de4dot`, `de4dotex`, `redasm`, `redress`, `dnspy`, `dotpeek` | para muestras .NET |
| Java | `jd-cli`, `jadx`, `baksmali`, `cfr` | |
| Android | `androguard`, `jadx`, `apktool`, `objection`, `frida-ios-dump` | |

---

## 11. Recetas que funcionaron en este análisis

```bash
# ejecución del sample con DMI falso + traza de API
export WINEPREFIX=/root/mrgarabato_analysis/run/wineprefix DISPLAY=
./fake_dmi.sh "env WINEDEBUG=+relay wine C:\\work\\sample.exe" > out.txt 2> traza.relay

# volcar la imagen de memoria del proceso
python3 dump_mem.py "C:\\work\\sample.exe" mem.bin

# descifrar las cadenas del payload
python3 decode_strings.py mem.bin

# romper hashes FNV-1a de APIs
python3 crack_hashes.py <sysdir_wine> hashes.txt

# descomprimir una función concreta (comando pd:g, no pdg)
r2 -qc 's 0xADDR; af; pd:g' unpacked.exe
```

## 12. Fallos y soluciones (registro)

| Síntoma | Causa | Solución |
|---|---|---|
| angr: `CLexer.filename` read-only | pycparser 3.x vs angr 9.2 | venv con pycparser 2.22 |
| angr: `cannot import PEStubs` | cle 9.2.160 de Arch | shim que inyecta el símbolo |
| `pip install angr` falla al compilar | pycparser 3.x en build aislado | usar el venv + shim |
| floss: `No module named vstruct.cparse` | vstruct 2.x incompatible | `pip install 'vstruct<2'` |
| r2 no ve secciones tras reconstruir un PE | headers no reescritos | escribir la tabla de secciones, no solo el contenido |
| `capa` tarda >10 min sin resultado | blob cifrado de 7,8 MB | descartar para material cifrado |

### Instalación de los ausentes — resultado

| Herramienta | ¿Disponible? | Resultado |
|---|---|---|
| **speakeasy** | ✅ PyPI `speakeasy-emulator 1.5.11` | ⚠️ **instalado pero inservible aquí**: degrada unicorn a 1.0.2 (rompía pwntools/pwndbg → restaurado a 2.1.4, aislado en venv). Es un emulador de malware **de 32 bits**; nuestro PE es x64 heavily ofuscado. Carga el PE pero no emula útilmente. |
| **zerowine** | ✅ pacman `blackarch` 0.0.2-10 | Ya **estaba instalado**. No tiene binario en PATH: scripts en `/usr/share/zerowine/bin/` |
| **hollows-hunter** | ✅ pacman `blackarch` 0.4.1.1-1 | Ya **estaba instalado**. Sin entrada en PATH |
| **pestudio** | ❌ | No existe para Linux (GUI solo Windows) |
| **FLOSS** | ⚠️ | **Irreparable en este sistema.** Necesita `vivisect 1.3.2`, que importa `vstruct.cparse`, `vstruct.primitives` y `vstruct.defs.windows.*`. vstruct 2.x es un rewrite completo que eliminó los tres, y vstruct 1.x no existe en PyPI para Python 3.14. Haría falta docenas de shims. Descartado. |

### Nota sobre subagentes
Los 7 subagentes lanzados en paralelo (FLOSS, decompiladores alternativos, damm,
bindead, LoaderAdvanced, Frida/bypass, decodificación de cadenas) **fallaron todos**
por *rate limit* del servicio antes de producir ningún resultado. El trabajo se ha
seguido haciendo de forma secuencial en el hilo principal.

### Receta añadida: venv para herramientas con dependencias conflictivas
```bash
# speakeasy (exige unicorn 1.0.2) y angr (exige pycparser 2.x) van en venv aparte
python3 -m venv --system-site-packages /tmp/opencode/angr-venv
python3 -m venv --system-site-packages /tmp/opencode/speakeasy-venv
/tmp/opencode/speakeasy-venv/bin/pip install speakeasy-emulator 'setuptools<81'
```
