# El loader: ISA abierta vs acotada — RESUELTO

## Veredicto

**No hay una VM que devirtualizar.** Los 1,33 MB de payload son **código x86-64
nativo ofuscado**, presentes **en claro dentro del fichero protegido en disco**.
La ISA es, por tanto, **abierta** (x86-64), no una ISA de VM acotada.

La decisión de proyecto cambia por completo: el trabajo es **desofuscar**, no
hacer *lifting* de handlers de VM.

---

## 1. Cómo se llegó aquí

`.w7/` / `.3q-` (7,79 MB) seemed un bloque homogéneo de χ²≈0. No lo es. Con una
ventana deslizante de 64 KB y la métrica **χ²/255** (independiente del tamaño
del bloque) aparece una frontera nítida:

```
bloque   H       chi2/255   veredicto
0x609000 7.992       2.84    cifrado
0x611000 7.657     257.43    ─┐
0x619000 7.030     834.78     │ CODIGO x86-64
0x631000 6.845     921.94     │ ofuscado
0x671000 6.933     828.22    ─┘
```

**Región de código: `0x611000` → `0x76E000`, 1.396.736 B (1,33 MB).**

Los ~6,2 MB previos sí están cifrados de verdad (χ²/255 ≈ 0,004 → uniforme
perfecto, que es lo que da un cifrado de flujo con keystream no repetible: el
índice de coincidencia es plano en 0,00429 de L=1 a L=4096).

---

## 2. Las pruebas de que es x86-64, no bytecode de VM

Recuento de patrones en la región de 1,33 MB, frente a lo que daría el azar
uniforme:

| Patrón | Cuenta | Esperado | Ratio |
|---|---|---|---|
| `48 81 EC` `sub rsp,imm32` (prólogo MSVC) | **123** | ~0 | **1477×** |
| `48 89 5C 24` `mov [rsp+x],rbx` | **2** | ~0 | **6150×** |
| `48 8D 05` `lea rax,[rip+..]` | **22** | ~0 | **264×** |
| `48 8D 0D` `lea rcx,[rip+..]` | **10** | ~0 | **120×** |
| `48 8B EC` `mov rbp,rsp` | **2** | ~0 | **24×** |
| `0F 85` `jne rel32` | 674 | 21 | 31,6× |
| `0F 84` `je rel32` | 259 | 21 | 12,2× |
| `E9` `jmp rel32` | 37.455 | 5.456 | 6,9× |
| `C3` `ret` | 10.894 | 5.456 | 2,0× |
| `C2` `ret imm16` | 8.784 | 5.456 | 1,6× |

Un compilador es lo único que emite `sub rsp,imm32` 1477 veces por encima del
azar. Un bytecode de VM no puede contenerlo.

### Y los idioms habituales están borrados a propósito

| Patrón | Cuenta | |
|---|---|---|
| `FF 15` `call [rip+disp32]` con destino válido | **0** | |
| `48 31 C0` `xor rax,rax` | **0** | |
| `48 89 C3` `mov rbx,rax` | **0** | |

`call [rip+disp32]` es **cómo MSVC llama a un import**. Que haya **cero** es una
decisión del ofuscador.

---

## 3. El perfil de las instrucciones: junk insertion

Sobre una muestra de 4 MB (413.649 instrucciones):

| Mnemónico | % |
|---|---|
| `mov` | 9 % |
| `jmp` | **8 %** |
| `xor` | 6 % |
| `add` | 6 % |
| `cmp` / `test` | 5 % cada uno |
| **`clc`** | **3 %** |
| **`cmc`** | **3 %** |
| **`stc`** | **3 %** |
| `ror` / `rol` / `bswap` / `neg` / `not` | ~1 % cada uno |

`clc`, `stc` y `cmc` manipulan solo el flag de acarreo y no hacen nada útil. En
código compilado real **prácticamente nunca aparecen**. Aquí son el **9 % del
programa**. Junto con `jmp` al 8 % (aplanado de flujo) y `ror/rol/bswap` (rotación
y byte-swap masivo), es la firma inequívoca de **inserción de basura + aplanado
de flujo**.

El **35 % de las llamadas son indirectas** (a través de registro), lo que confirma
resolución dinámica de imports: el ofuscador sustituye `call [IAT]` por
`mov reg, <resuelto> ; call reg`.

---

## 4. Sobre Themida: plausible, no confirmado

| Indicio | A favor | En contra |
|---|---|---|
| Imports ocultos (tabla de importación cifrada, `Name: 0xDFCF90` en `.w7/`) | ✓ | |
| Llamadas 35 % indirectas | ✓ | |
| RICH header eliminado | ✓ | |
| Secciones con `SizeOfRawData = 0` | ✓ | |
| Nombres de sección aleatorizados por build | ✓ | |
| `.pdata` destruido (298 entradas basura) | ✓ | |
| Junk insertion masivo + aplanado de flujo | ✓ | |
| **TLS callbacks** | | **✗ `AddressOfCallBacks = 0x0`** |
| Cuerdas del protector | | ninguna |

La ausencia de TLS callbacks es el único dato que **juega en contra** de
Themida clásico, que los usa de forma sistemática como punto de entrada. Pero
Themida 3.x puede parchear el entry directamente y no declararlos.

**Mi conclusión honesta**: el comportamiento es **consistente con Themida /
WinLicense**, pero **no puedo confirmarlo** con lo que tengo, y no voy a
afirmarlo. Lo que sí es seguro es la categoría: **protector comercial de
ofuscación con motor de descifrado**.

---

## 5. Estructura completa del fichero

```
MrGarabato-LoaderAdvanced.exe  (7.832.064 B)
├── 0x400     3.584 B   stub/tabla de fixup — 82 bytes no nulos, dispersos
├── 0x1200    7.790.592 B   [.w7/]
│   ├── 0x000000 .. 0x611000   6,2 MB  CIFRADO (χ²/255 ≈ 0,004, flujo)
│   └── 0x611000 .. 0x76E000   1,33 MB  x86-64 ofuscado EN CLARO
└── 0x76F200  36.864 B   [.rsrc] — icono PNG, NO cifrado
```

Secciones con `SizeOfRawData = 0` (no existen en disco): `.text`, `.rdata`,
`.data`, `.pdata`, `.eff`. El EntryPoint (`RVA 0xD88535`) cae **dentro de la
zona cifrada**: `call 0x140DA07C9` y después basura.

`.text` una vez desempaquetado son 133 KB de lógica de loader (C2, instalador),
con 3 `CPUID` que son **detección de CPU GenuineIntel + AVX/AVX-512**, no
anti-VM, y 0 `RDTSC`.

---

## 6. Qué significa para el proyecto

**No hay devirtualización que hacer.** La pregunta con la que abrimos esta fase
("¿la ISA es acotada?") tiene respuesta: es **abierta**, porque no hay VM en el
payload. El trabajo real es:

1. **Recuperar el grafo de control** de 1,33 MB de código con 8 % de `jmp` y 9 %
   de basura. Ghidra encuentra **1 solo procedimiento** — necesita ayuda.
2. **Identificar y podar el relleno**: `clc`/`stc`/`cmc` son 9 % del binario y se
   pueden eliminar por patrón sin análisis semántico.
3. **Reconstruir los imports**: 35 % de llamadas indirectas y cero
   `call [rip+disp]`.
4. **Aplanado de flujo**: es la parte difícil, porque los 8 % de `jmp`，实
   codifican el flujo real.

Es un trabajo de desofuscación clásico, no una investigación de ISA nueva.

### Lo que queda del protector

Los 6,2 MB cifrados y el motor de 82 bytes siguen sin descifrar. Contiene el
stub de arranque y posiblemente una capa de virtualización **fuera** de este
payload. Para cerrarlo haría falta la captura en runtime que ya está planificada.

---

## 7. Correcciones registradas en esta sesión

| Afirmación anterior | Correcto |
|---|---|
| «Bytecode de 6,12 MB con 175 handlers / 184 edges» | Era **texto cifrado**. El grafo nunca existió |
| «111 CPUID + 146 RDTSC en el intérprete» | **Ruido de cifrado.** Real: 3 `CPUID`, 0 `RDTSC` en `.text`, y son detección de CPU, no anti-VM |
| «`.3q-` es la sección grande» | Hay dos: `.3q-` (build ByPass) y `.w7/` (build Loader). Nombres aleatorizados |
| «Recursos cifrados» | **Falso**: el icono es un **PNG válido** (`89 50 4E 47 … IHDR`); su entropía alta es por compresión |
| «`.eff` / `.w7/` todo cifrado» | Solo los **6,2 MB previos** al offset `0x611000`. Los últimos **1,33 MB están en claro** |
| «χ²≈0 en todo el blob» | El blob tiene dos mitades: 6,2 MB uniformes (χ²/255≈0,004) y 1,33 MB de código (χ²/255≈800) |

## 8. Archivos

- `recortar_loader.py` — PE reducido analizable por REA
- `wrap_pe.py` — envuelve código crudo en PE para Ghidra/REA
- `loader_solo_text.exe` — 133 KB de `.text` real
- `stage3_code.exe` — 1,33 MB del payload en claro, envueltos en PE
- `/tmp/opencode/stage3_code.bin` — el payload crudo
- `rea_out/stage3_ghidra.md` — análisis Ghidra (1 procedimiento: la ofuscación
  rompe la detección de límites de función)