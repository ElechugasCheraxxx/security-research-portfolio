# Plan de devirtualización de `.3q-` — alcance realista

## Premisa: las herramientas no son el cuello de botella

Con 2.800 herramientas y tiempo completo se puede eliminar casi cualquier obstáculo
técnico. Lo que **no** se elimina con herramientas es una pregunta de arquitectura:

> ¿La ISA de esta VM es **acotada** (hay un número finito y enumerable de handlers)
> o es **abierta** (el handler se sintetiza en runtime según el opcode)?

Si es acotada, devirtualizar es un trabajo largo y aburrido. Si es abierta, no lo es.

**Esa es la Fase 0, y es la única que importa.** Todo lo demás es consecuencia.

## Estado medido (no estimado)

| Métrica | Valor |
|---|---|
| Bytecode `.3q-` | 6.421.528 B (6,12 MB) |
| Intérprete | 1.370.276 B (1,31 MB) |
| Handlers identificados | **175** |
| Aristas del grafo | 184 |
| Nodos visitados | 2.342 |
| Grado de entrada máximo del grafo | **5** |

Ese último número es la señal de alarma: un bucle de dispatch real tendría un grado
de entrada enorme. El grafo que tenemos no es el control flow de la VM, es lo poco
que se pudo descifrar por descenso recursivo desde puntos conocidos. **Prácticamente
no sabemos nada de la estructura de la VM todavía.**

Estimación de escala: si la densidad media de una instrucción de VM está entre 30 y
60 B, una ISA que cubra 6,12 MB tendría del orden de **100.000–200.000 handlers**.
Tenemos 175. Independientemente de si la estimación es exacta, la cobertura es
marginal.

---

## Fase 0 — Resolver la pregunta de arquitectura (EL punto de todo el proyecto)

Objetivo: encontrar el **sitio de dispatch** y determinar la fórmula con la que se
calcula la dirección del handler.

Método: traza con speakeasy (ya verificado que emula la muestra) + *code hook* sobre
`0xE3C000–0xF8A8A4` registrando qué direcciones se ejecutan. El dispatch se
reconoce por:

1. Un bucle con arista de retorno muy-hot (el mismo par origen/destino una y otra vez)
2. Leída de un opcode desde `[reg + offset]` (dónde está el PC del bytecode)
3. Aritmética sobre ese valor: `lea`, `shl`, `imul`, `add`
4. Salto indirecto: `jmp reg` / `call reg` / `push reg; ret`

Tres desenlaces posibles y qué significan:

| Resultado | Lectura | Viabilidad |
|---|---|---|
| `handler = base + opcode * K` con `K` y `base` **constantes** | ISA **acotada** | El número de handlers es `max_opcode/K`. enumerable por fuerza bruta: todos los handlers están en el intérprete | **Viable**, semanas |
| `handler = f(opcode, estado)` con tabla en `.data` | ISA **acotada**, tabla reconstruible | Igual de viable, más fácil | **Viable**, semanas |
| El handler se **construye/descifra en runtime** (código generado) | ISA **abierta** | No hay ISA que enumerar | **No viable** de forma exhaustiva |

**Presupuesto: 1–3 días.** Si sale acotada, el proyecto continúa. Si sale abierta,
se para aquí y se cambia de estrategia.

---

## Fase 1 — Enumerar la ISA completa (solo si la Fase 0 dice "acotada")

Extraer todos los handlers, no 175 sino los que haya. El barrido es mecánico:
calcular el destino para cada opcode representable y comprobar si cae en rango
válido del intérprete y desensambla. Los que no desensamblen son stubs, no handlers.

**Presupuesto: 2–5 días** según el tamaño real de la ISA.

## Fase 2 — Levantar la semántica de cada handler

Cada handler está en x64 **desincronizado y ofuscado**. Se necesita:

- Desensamblado con control de flujo (capstone con detalle + recuperación de
  sobreescrituras de pila, tipo el `vm_recover.py` pero denso)
- Clasificación por los effects sobre el contexto de VM (los 0x140 B de contexto en
  pila) y sobre los flags
- Mapeo a una IR (SSA o similar)

Aquí es donde se va el 80% del tiempo y donde las herramientas **sí** ayudan:
Triton, angr, miasm, lifter frameworks, LLVM IR de salida.

**Presupuesto: 2–4 semanas para los handlers comunes**, más tiempo para los raros.

## Fase 3 — Lifter de bytecode → C

Con la ISA caracterizada, se recorre el bytecode y se emite C. Problema conocido:
el bytecode tiene **6,12 MB**, así que la salida sería enorme y en su mayor parte
irrelevante (rutinas de ofuscación, código muerto,anti-debug).

**Presupuesto: 1–2 semanas** la infraestructura; el volumen de salida es otro problema.

---

## El argumento de alcance que creo que pesa más

Antes de invertir semanas: **devirtualizar todo el bytecode probablemente no es el
objetivo correcto**, por esto:

1. El payload **no está en el bytecode**. Lo sabemos con certeza: se descarga del C2.
   El `RunPE`, `iQVW64E.SYS` y `WinDivert` ya están identificados y analizados.

2. Lo que el bytecode implementa es el **loader**: anti-VM, fingerprinting,
   persistencia, cliente HTTP. Y eso **ya lo conocemos empíricamente**: lo
   capturamos dinámicamente con trazas de relay, con el informe de mensajes del
   servidor, con los artefactos del C2 descargados.

3. Lo que **no** sabemos del bytecode es cómo se implementa por dentro: qué
  Instructions de VM corresponden a la comprobación de CPUID, cómo se construye la
   URL, cómo se cifra. Eso tiene valor real, pero es valor de **reimplementación** y
   de **IOC**, no de comprensión de la amenaza — que ya está.

Consecuencia práctica: un lift-and-match **guiado por los caminos que ya
conocieron** (la puerta anti-VM, la fase de red, la persistencia) daría el 90% del
valor en una fracción del esfuerzo, sin necesidad de enumerar la ISA entera.

---

## Recomendación

1. **Hacer la Fase 0 ya.** Es barata y decide el proyecto. Es la única decisión
   binaria con consecuencias de meses.
2. Si la ISA es acotada, decidir explícitamente si se levanta **completa** o
   **guiada por los caminos de interés**. La segunda opción es la que yo
   defendería.
3. Si la ISA es abierta, abandonar la devirtualización exhaustiva y documentarlo
   como límite del análisis — que es una conclusión legítima y útil.

Lo que **no** es una buena inversión de tiempo: abrir las 2.800 herramientas y
probar decompiler sobre 6 MB de bytecode ofuscado. Ninguna gana contra una VM cuyo
dispatch se computa en runtime.