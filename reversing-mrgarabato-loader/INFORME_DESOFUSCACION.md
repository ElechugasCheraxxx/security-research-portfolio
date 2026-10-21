# Desofuscación — Qué se ha desofuscado y qué queda

**Fecha:** 2026-10-14 · Continuación del análisis estático/dinámico

## Respuesta corta

Sí se puede desofuscar con herramientas de Black Arch, y **ya se ha hecho en 2 de las 3 capas**.
La tercera capa no es cifrado: es **virtualización de código**, y esa requiere devirtualización,
no una herramienta de un clic.

| Capa | Contenido | Método | Estado |
|---|---|---|---|
| 1. Empaquetado | blob de 7,4 MB → imagen de 8 MB | volcado de memoria bajo Wine + DMI falso | ✅ **superada** |
| 2. Datos | cadenas, IOCs, configuración | extracción directa | ✅ **superada** |
| 3. Código | lógica del cheat | region A = CRT legible / región B = bytecode VM | ⚠️ **parcial** |

---

## 1. Corrección de angr (estaba roto)

Causa raíz: **pycparser 3.11** (rewrite mayor) incompatible con angr 9.2.194, que espera la API 2.x.

```
AttributeError: property 'filename' of 'CLexer' object has no setter
  angr/sim_type.py:3916 -> self.clex.filename = filename
```

pycparser 3.x eliminó además `pycparser.ply` y `CLexer.reset_lineno()`, ambos usados por angr.

**Arreglo aplicado** (sin tocar paquetes del sistema):
1. venv con `--system-site-packages` + `pycparser==2.22` → sombrea el 3.11 del sistema
2. shim `angr_shim.py` que inyecta `PEStubs` (cle 9.2.160 de Arch no lo exporta;
   angr solo lo usa en dos `isinstance()` para modelar stubs de API)

```bash
python3 -m venv --system-site-packages /tmp/opencode/angr-venv
/tmp/opencode/angr-venv/bin/pip install pycparser==2.22
/tmp/opencode/angr-venv/bin/python angr_shim.py unpacked_bypass.exe
```

> Nota: `pip install angr==9.2.194` **falla** — compila libvex desde fuente y el
> entorno de build aislado vuelve a usar pycparser 3.x. El shim es la vía limpia.

## 2. Bug propio corregido: PE reconstruido inconsistente

La primera reconstrucción escribía la imagen de memoria cruda pero **no la tabla de
secciones modificada**. r2 leía `paddr=0, size=0` para `.7 f` y no veía nada.

Corrección: realinear `PointerToRawData = VirtualAddress` **y escribir de verdad esa
cabecera** en el fichero de salida (`rebuild_pe.py`).

## 3. Mapa de la imagen: dónde hay código real

Mapeo por "code-likeness" con Capstone sobre el volcado:

| Región | Rango | Tamaño | Contenido |
|---|---|---|---|
| `.text` | `0x140001000–0x140018000` | 94 KB | stubs de arranque del **CRT** (`lea rcx,[rip+X]; jmp __scrt_common_main_seh`) |
| `.7 f` inicio | `0x140023000–0x140057000` | 212 KB | **CRT de MSVC** (memcpy, string, TLS) — código limpio |
| `.7 f` resto | `0x140059000+` | — | mixto |
| `.3q-` | `0x14081C000–0x140F8A8A4` | 7,4 MB | **bytecode de la VM + dispatcher** |

## 4. Prueba de virtualización (no cifrado)

`.3q-` en memoria es **100,00 % idéntico** al fichero en disco (0 bytes de 7.793.152 distintos).
Nunca se descifra → no es cifrado, es un **intérprete**.

Refuerzos:
- entropía constante 7,948 (bytecode, no código)
- la traza muestra las APIs llamándose **desde dentro de `.3q-`**
  (`GetModuleHandleA(...) ret=140965365`)
- las cadenas están en `.rdata` pero **con cero xrefs** desde el código: el bytecode
  las referencia como constantes de VM, no como inmediatos x86

## 5. Descompilación lograda (capa CRT)

453 funciones descompiladas con **rz-ghidra** (backend del decompilador de Ghidra dentro
de rizin) → **1,9 MB de pseudocódigo C limpio**.

```c
/* RVA 0x3ef2c */
int64_t fcn.14003ef2c(void) {
    int64_t iVar1 = fcn.14003e954();
    if (iVar1 == 0) iVar1 = 0x140053b58;
    else            iVar1 = iVar1 + 0x10;
    return iVar1;
}
```

Perfil de llamadas confirma que es runtime, no lógica del cheat:

```
344 x fcn.14003dc60    (probable memcpy/memset)
127 x fcn.14003ef2c    (helper TLS)
 62 x fcn.14003e9d8
 52 x fcn.14004242c
```

**Ninguna de las 453 funciones referencia las cadenas del C2, del emulador ni de la inyección.**

## 6. Qué haría falta para la capa 3

La lógica real del cheat vive como bytecode interpretado. Opciones, de menor a mayor esfuerzo:

1. **Triton** (`triton_vm.py` preparado) — emular el dispatcher y trazar qué bytecode
   produce cada llamada a la API. Reconstruye el *comportamiento* sin devolver código nativo.
2. **angr + Triton** — trackeo de tainted data para mapear cada bloque de bytecode
   a su instrucción x86 original.
3. **Devirtualizador a medida** — reconstruir la ISA de la VM (decodificación de operandos,
   tabla de handlers) y reescribir a x86. Semanas de trabajo; solo merece la pena si
   hace falta el código exacto.

Nota: el análisis de comportamiento **ya está hecho** por otra vía (trayectoría de API +
cadenas), así que el valor marginal de la devirtualización es bajo para el objetivo
de IOC, y alto solo si necesitas el código fuente reconstruido.

## 7. Scripts

| Script | Función |
|---|---|
| `angr_shim.py` | compatibilidad pycparser/PEStubs para angr |
| `angr_cfg.py` | CFGFast sobre el PE desempaquetado |
| `rebuild_pe.py` | PE navegable desde el volcado (cabeceras correctas) |
| `map_code.py` | mapa de qué regiones son código real |
| `decompile_all.py` | descompilación en lote con rz-ghidra |
| `find_xrefs.py` | xrefs a cadenas clave (0 resultados → confirma virtualización) |
| `triton_vm.py` | esqueleto de emulación del dispatcher |
| `fake_dmi.sh` | DMI falso en mount namespace para el bypass anti-VM |
| `dump_mem.py` | volcado de la imagen de memoria bajo Wine |
| `probe.c` / `probe2.c` | inspección de SMBIOS y registro tal y como los ve el sample |