# El loader y la pregunta ISA acotada vs abierta

## Resumen ejecutivo

La pregunta **no se puede responder con los artefactos que teníamos**, y ahora
sé exactamente por qué. El Phase 0 anterior (175 handlers / 184 edges) se ejecutó
sobre **texto cifrado**: era ruido.

Lo que sí queda establecido:

| | |
|---|---|
| Empaquetador | protector de VM comercial (clase VMProtect) |
| Secciones | **nombres aleatorizados por build** |
| Contenido en disco | solo 3 zonas; todo lo demás con `SizeOfRawData = 0` |
| Intérprete VM | **cifrado en reposo**; no está en `.text` |
| Anti-VM en `.text` | **ninguna** (corrección importante) |
| Ofuscación de cadenas | XOR posicional `plain[i] = cipher[i] ^ (0x53+i)` — ya resuelta |

---

## 1. Estructura del empaquetado

### En disco (`MrGarabato-LoaderAdvanced.exe`, 7.832.064 B)

| Offset | Tamaño | H | χ² | Contenido |
|---|---|---|---|---|
| `0x400` | 3.584 B | 0,29 | 232 | **stub** (`.3rs`) — solo **82 bytes no nulos** |
| `0x1200` | 7.790.592 B | **7,948** | **0** | **payload cifrado** (`.w7/`) |
| `0x76F200` | 36.864 B | **7,899** | **0** | recursos cifrados (`.rsrc`) |

Todas las demás secciones (`.text`, `.rdata`, `.data`, `.pdata`, `.eff`) tienen
`SizeOfRawData = 0`: **no existen en el fichero**.

El stub son 82 bytes no nulos en 28 bloques de 3 bytes separados por ceros —
una **tabla dispersa de RVA de fixup** cada 16 bytes, no código.

### Entry point

```asm
0x140d88535   call 0x140da07c9     ; EP real: RVA 0xd88535, dentro de .w7/
0x140d8853a   out 0x10, eax        ; <- basura, sigue cifrado
```

El EP está **dentro de la sección cifrada** y salta a un trampolín. Todo lo que
viene después es indescifrable estáticamente.

### `.3q-` sí existe — pero en otra build

Los nombres se **aleatorizan por build**:

| Muestra | Sección grande | Nombre |
|---|---|---|
| `MrGarabato-LoaderAdvanced.exe` | 8.327.423 B | `.eff` |
| `MrGarabato-LoaderAdvanced.exe` | 7.790.356 B | `.w7/` |
| `MrGarabato-ByPassEmulator.exe` | 8.355.219 B | `.7 f` |
| `MrGarabato-ByPassEmulator.exe` | 7.792.804 B | **`.3q-`** |

Por eso las notas previas hablan de `.3q-`: es el nombre real, pero **de la otra
muestra**.

---

## 2. `.pdata` cifrado — anti-análisis deliberado

`.pdata` debería contener 298 `RUNTIME_FUNCTION` de 12 bytes. En la imagen
descifrada tiene **H = 7,829** y χ² ≈ 1: **las 298 entradas son basura**
(`Begin=0xf606e246 End=0x0f542a60`…).

Destruir la tabla de unwind es una medida anti-análisis deliberada: rompe la
detección de funciones de IDA, Ghidra y cualquier profiler. Una tool que confíe
en `.pdata` verá **cero** funciones correctamente.

---

## 3. REA sobre `.text` — el resultado

El `provider_timeout` anterior no era el problema del binario: era que REA
intentaba auto-analizar los 16 MB de texto cifrado.

**Solución**: `recortar_loader.py` pone a cero `VirtualSize`/`SizeOfRawData` de
`.pdata`, `.eff`, `.w7/` y `.rsrc`, y limpia los data directories que apuntan a
ellas (`EXPORT`, `IMPORT`, `EXCEPTION`, `TLS`, `LOADCFG`, `RESOURCE`).

Resultado sobre `loader_solo_text.exe` (188 KB reales):

```
segment_count   = 6
procedure_count = 259
```

r2 da **420 funciones**. Las mayores son `std::string`/`std::vector` (umbral SSO
`0xF`), CRT y `memmove`/`memset` estáticamente enlazados.

**Conclusión de tamaño**: `.text` son 133 KB. Un intérprete de protector de VM
típico ocupa **1–4 MB**. No cabe. **El intérprete no está en `.text`.**

---

## 4. Corrección importante: no hay anti-VM en `.text`

Inventario real de instrucciones sensibles:

```
.text:  CPUID=3  RDTSC=0  XGETBV=1  RDTSCP=0
.rdata: CPUID=0  RDTSC=0  XGETBV=0  RDTSCP=0
```

En 7,79 MB de texto cifrado caben **~119 coincidencias de `0F A2` al azar**
(1/65536 por posición). Las cifras previas de «111 CPUID + 146 RDTSC» estaban
**infladas por ruido de cifrado**.

Y los 3 `CPUID` reales (RVA `0x1ad67`, `0x1ad8e`, `0x1ae1e`) están en **una sola
función**, `FUN_14001ad54`, que REA/Ghidra decompila como:

```c
piVar1 = cpuid_basic_info(0);
puVar2 = cpuid_Version_info(1);
if (piVar1[2] == 0x49656e69 && piVar1[3] == 0x6c65746e && piVar1[1] == 0x756e6547)
    //                     "ineI"              "ntel"              "Genu"   → "GenuineIntel"
uVar7 = *puVar2 & 0xfff3ff0;                  // familia/modelo/stepping de Intel
if (uVar7 == 0x106c0 || uVar7 == 0x20660 || uVar7 == 0x20670 ||
    (uVar7 - 0x30650 < 0x21 && (0x100010001U >> ((uVar7 - 0x30650) & 0x3f) & 1)))
    DAT_14002fad4 |= 1;
...
uVar5 = xinuse(0);                            // XGETBV → XCR0
if ((in_XCR0 & 6) == 6) {                    // AVX activo
    DAT_14002f554 = 0xe;  _DAT_14002f550 = 3;
    if ((uVar8 & 0x20) != 0) {               // CPUID.7:EBX[5] = AVX2
        DAT_14002f554 = 0x2e; _DAT_14002f550 = 5;
        if ((uVar8 & 0xd0030000) == 0xd0030000 && (in_XCR0 & 0xe0) == 0xe0)
            DAT_14002f554 = 0x6e; _DAT_14002f550 = 6; } } }
```

**Es detección de CPU y capacidades AVX/AVX-512, no detección de VM.** Los `bt`
que aparecen son `ebx,9` (ERMS), `edi,0x14` (SSE4.2), `edi,0x1b` (AVX),
`edi,0x1c` (FMA). **`ecx` nunca se prueba contra el bit 31**, que es donde vive
el indicador de hipervisor.

**Por tanto**: `NtRaiseHardError(VM_DETECTED) = 0` no se explica por estos
`CPUID`. Cualquier detección real estaría en las secciones cifradas —es decir, en
el código del propio protector—, y eso **no se ha verificado**.

---

## 5. ISA acotada vs abierta: estado

**No determinable con lo disponible.** Los tres motivos:

1. **El bytecode está cifrado en reposo.** `.3q-`/`.w7/` a χ²≈0. Hay que
   capturarlo **ya descifrado**, en runtime.
2. **El intérprete tampoco está.** 133 KB de `.text` no bastan; el intérprete
   de un protector comercial mide 1–4 MB.
3. **El grafo anterior era ruido.** 175 handlers / 184 edges / max in-degree 5
   salieron de barrer texto cifrado con un patrón de bytes. No era un grafo de
   dispatch.

### Lo que sí sugiere la evidencia

- Es un **protector de VM comercial**: nombres de sección aleatorizados, todas las
  secciones con raw size 0 salvo tres, EP dentro de una sección cifrada, y
  directorios `TLS` + `EXCEPTION` + `LOADCFG` presentes. Eso implica una VM con
  **conjunto de handlers finito** → ISA **acotada por construcción**, pero con
  un número de handlers alto (cientos), no las decenas de una VM de juego.
- El factor de expansión 7.790.592 → 8.327.423 (**+6,9 %**) no es compresión;
  es consistente con descifrado que produce algo mayor (codigo nativo ofuscado o
  bytecode re-expandido).

**No lo doy por cerrado.** Afirmar «acotada» sin ver el dispatch sería exactamente
el tipo de conclusión que este trabajo ha-its purpose de evitar.

---

## 6. Caracterización criptográfica de `.w7/` / `.3q-` (7,79 MB)

He-characterizado los 7,79 MB **directamente del fichero en disco**. Cuatro tests
descartan hipótesis de una en una:

### Descartado: no es código x86-64 nativo

| Patrón | Observado | Si uniforme | Ratio |
|---|---|---|---|
| `48 8B EC` (`mov rbp,rsp`) | **2** | 10.144 | **0,0002×** |
| `48 83 EC` (`sub rsp,imm8`) | **2** | 10.144 | **0,0002×** |
| `40 55` (`push rbp`) | 107 | 15.216 | 0,007× |
| `31 C0` (`xor eax,eax`) | 117 | 15.216 | 0,008× |
| `FF 10` (`call [rax]`) | 128 | 15.216 | 0,008× |
| `E8` (`call rel32`) | 30.579 | 30.432 | 1,00× |
| `E9` (`jmp rel32`) | 62.066 | 30.432 | 2,04× |

Bytes sueltos en o por encima de lo uniforme, pero **patrones de instrucción de
2+ bytes suprimidos 100–5000×**. En 7,79 MB de x64 real habría *miles* de
`48 83 EC`; hay **2**.

> Trampa evitada: un barrido con capstone en modo `skipdata` daba «94 %
> desensamblable» con perfil x64 coherente (`mov`, `push`, `xchg`…). Es un
> artefacto: con `skipdata` capstone rellena huecos y decodifica *cualquier*
> secuencia de bytes. No es evidencia de código.

### Descartado: no es compresión estándar

- `unlzma`, `lz4`, `unzstd`, `7z` → ninguno reconoce el formato
- `aplib` (el compresor típico de VMProtect) instalado y probado desde 10 offsets
  distintos → ninguna salida válida
- aPLib no tiene magic, pero falló desde el inicio de sección y desde el offset
  del EntryPoint

### Descartado: no es XOR de clave repetida

Índice de coincidencia **plano en 0,00429 para toda longitud de clave de 1 a 4096**:

```
L=    1  IC = 0.00429        L=   64  IC = 0.00429
L=    8  IC = 0.00429        L=  256  IC = 0.00429
L=   32  IC = 0.00429        L= 4096  IC = 0.00429
```

Y ningún XOR de un solo byte (0x00–0xFF) produce caída de entropía.

### Descartado: cifrado fuerte uniforme

χ²/n = **0,155**, no ~3×10⁻⁵. AES-CTR o ChaCha20 darían salida perfectamente
uniforme.

### Lo que sí es

Las dos cosas a la vez:

1. **Frecuencias preservadas**: `0x00` aparece 109.133 veces (1,4 % del total,
   3,6× lo uniforme), `0x41` (REX.B) 100.499, `0x0f` (escape de dos bytes) 70.398,
   `0xe9` (`jmp rel32`) 62.066, `0x66` 71.498. Esos son precisamente los bytes
   más frecuentes de **código x86 ofuscado**.
2. **Keystream uniforme y no repetitivo** (IC plana).

⇒ **Cifrado de flujo con clave larga** (maloable, tipo XOR con keystream no
repetible) aplicado sobre un plaintext que era código ofuscado.

**El plaintext es casi con seguridad x86-64 ofuscado, no una ISA de VM
inventada.** Pero eso sigue siendo una inferencia del perfil de frecuencias, no
una prueba: para afirmar la estructura del dispatch habría que **descifrar**.

### Corolario sobre el Phase 0 anterior

El barrido sobre «6,12 MB de bytecode»找 175 handlers / 184 edges se hizo sobre
texto cifrado. **Era ruido.** Queda invalidado, no refutado: la pregunta sigue
abierta pero sin respuesta.

---

## 7. El siguiente paso concreto

**Capturar el VM descifrado en runtime.** La cadena ya existe y funciona:

- `dump_mem.py` — vuelca la imagen PE de un proceso Wine vivo (eleva a
  volcar también el resto del espacio de direcciones)
- `live_patch5.py` + `fake_dmi_net.sh` — arranque en el namespace con DMI falsa
- `speakeasy` — emulación de kernel en Python (ya validado con el driver)

Evidencia que ya apunta al camino: **`mem_p4.bin` tiene `.3q-` íntegramente a
ceros** (H = −0,00). Eso significa que en ese punto el protector ya había
**consumido** la sección. El dato no desapareció: se descifró en otro sitio del
espacio de direcciones. Hay que ir a buscarlo allí.

Plan:
1. Relanzar el loader en el namespace y volcar **todo** el espacio de
   direcciones, no solo la imagen PE
2. Localizar la región de ~7,8 MB que χ² haya bajado de ~0 a valores de código
3. Analizar esa región con REA/Ghidra para encontrar el dispatch
4. Solo entonces: ¿tabla de handlers acotada o decodificador x86 abierto?

---

## 8. Correcciones registradas

| Afirmación anterior | Correcto |
|---|---|
| Bytecode «6,12 MB» con 175 handlers / 184 edges | Era **texto cifrado**. χ²≈0. El grafo no existía |
| «111 CPUID + 146 RDTSC en el intérprete» | **Ruido de cifrado.** Real: 3 `CPUID`, 0 `RDTSC` en `.text` |
| Esos CPUID = anti-VM | Son **detección de CPU GenuineIntel + AVX/AVX-512**. Sin bit de hipervisor |
| Sección `.3q-` | Nombre real, pero **de la otra build**. Se aleatorizan |
| `provider_timeout` de REA | No era el binario: eran los 16 MB de texto cifrado. `recortar_loader.py` lo resuelve → 259 procedimientos |
| Formato χ² personal | Estaba mal escalada (dividía por n). Corregida: χ² real = valor × n |

## 9. Archivos

- `recortar_loader.py` — genera el PE reducido analizable
- `loader_solo_text.exe` — 133 KB de `.text` real, analizable por REA/Ghidra
- `isa_probe.py` — sonda acotada-vs-abierta (no concluyente sobre blob mixto)
- `rea_out/loader_text_ghidra.md`, `rea_out/antivm.md`, `rea_out/antivm_cpuid.md`