# ¿Se puede recuperar código fuente? — Respuesta por componente

La respuesta es muy distinta según el fichero, y conviene no mezclarla. Hay
cuatro componentes en la cadena y **ninguno tiene el mismo grado de recuperabilidad**.

| Componente | ¿Fuente real? | ¿Pseudo-C? | Calidad |
|---|---|---|---|
| `iQVW64E.SYS` (driver) | **No, nunca existió pública** | **Sí** | Muy alta |
| `execute` (RunPE) | **Posible: proyecto público** | **Sí** | Muy alta |
| `WinDivert` .dll/.sys | **Ya es código abierto** | n/a | — |
| Los 2 samples MrGarabato | No (VM) | Parcial | Alta en `.text`, nula en la VM |

---

## 1. El driver: fuente imposible, pseudo-C excelente

**El fuente original no es recuperable y no lo será.** No es una cuestión de
esfuerzo: `iQVW64E.SYS` es código interno de Microsoft, del SDK **NAL** (Network
Abstraction Layer). Nunca se publicó. El PDB solo aporta la ruta de compilación:

```
c:\users\cloudbuild\337244\sdk\nal\src\winnt_wdm\driver\objfre_wnet_AMD64\amd64\iqvw64e.pdb
```

Lo que sí se recupera es **pseudo-C de muy buena calidad**, porque el binario va
desnudo:

- sin packer (entropía máx. 6,23 en `.text`)
- sin ofuscación ni VM
- **build *free***, es decir sin optimizaciones agresivas: el código se parece mucho al original
- `.pdata` válida con 86 funciones delimitadas
- **Rich Header intacto** (`Utc1400_C`, `Masm800`, `Linker800`) → binario original, no recompilado
- las cadenas de `DbgPrint` **delatan los nombres de función del propio SDK** (`NalDeviceControl`, `NalOsSpecificIoctl`, `NalResolveOsSpecificIoctl`, `_NalReadPciDeviceCount`…)

Entregado en `c2_descargas/driver_pseudoc.c`, con el dispatcher de IOCTL y
`NalMapMemoryMap` (la primitiva) reconstruidos desde el descompilado de rz-ghidra.
Herramientas usadas: `r2 6.2.2` + r2-ghidra, y como contraste disponibles
`ida64`, `hopper`, `retdec-decompiler` y `ghidra`.

## 2. El inyector RunPE: aquí sí puede haber fuente real

```
dbg_file  C:\...\Process-Hollowing-main\Source\x64\Release\runpe.pdb
```

Ese camino corresponde al árbol de fuentes de un **proyecto público** de Process
Hollowing. Si el binario se compiló de ese repositorio, el pseudo-C que Produce
rz-ghidra es prácticamente el fuente real renombrado.

Entregado en `c2_descargas/runpe_pseudoc.c`. La lógica se lee sin esfuerzo:

```
CreateProcessA(destino, …, CREATE_SUSPENDED, …)   → proceso suspendido
VirtualAllocEx / WriteProcessMemory                 → se escribe el payload
GetThreadContext / SetThreadContext (o Wow64…)      → se redirige el punto de entrada
ResumeThread                                        → se reanuda con el código inyectado
```

**Límite honesto:** no he contrastado línea a línea contra ese repositorio porque
no tengo el original a mano aquí. Que la técnica sea la canónica de process
hollowing está **verificado**; que el fichero sea *exactamente* ese fuente, es
una hipótesis que marco con la ruta del PDB, no un hecho comprobado.

## 3. WinDivert: no hay nada que recuperar

`WinDivert.dll` y `WinDivert64.sys` **no son malware ni están modificados**. Son el
build normal de una biblioteca de código abierto (`basil00/WinDivert`, "Basil's
Projects", v1.4). El malware solo la usa para la función "FakeLag". El fuente ya
está disponible públicamente.

## 4. Los dos samples MrGarabato: partida en dos

Aquí es donde hay que ser más preciso, porque conviven dos cosas incompatibles:

**`.text` (94 KB de C++ limpio, MSVC)** — se descompila bien. Ya se publicaron
**751 funciones** (453 en `decomp_bypass/`, 298 en `decomp_text/`) con rz-ghidra.
Ahí está el código "normal" de los muestras: el parser JSON, la resolución de
nombres de proceso, el manejo de cadenas cifradas, la enumeración de red.

**`.3q-` (6,2 MB de bytecode + 1,3 MB de intérprete)** — aquí **no es realista
recuperar fuente**. Es una VM con handlers computados aritméticamente
(`base + opcode*stride`), no una tabla, y el código está desincronizado. Convertir
eso a C exigiría devirtualización completa, que es un proyecto de investigación por
sí solo, no una tarea de afternoon.

---

## Resumen accionable

- **Mejor retorno inmediato:** el RunPE y el driver ya están en pseudo-C legible.
- **El driver no tiene fuente posible** — es interno de Microsoft. Cualquier
  expectativa de "recover the source" en ese caso es irreal.
- **Lo que falta por recuperar**, si te interesa, es el bytecode de la VM de los
  samples. Ahí el camino no es descompilar sino **capturar el comportamiento**:
  ya sabemos qué hace (anti-VM, fingerprinting, persistencia, descarga del C2,
  RunPE + driver), pero no tenemos su código fuente ni vamos a obtenerlo.

Ficheros generados:

- `c2_descargas/runpe_pseudoc.c` — inyector reconstruido
- `c2_descargas/driver_pseudoc.c` — driver reconstruido
- `c2_descargas/runpe_decomp.c` — 967 líneas de descompilado crudo del RunPE
- `c2_descargas/driver_decomp.c` — 603 líneas de descompilado crudo del driver