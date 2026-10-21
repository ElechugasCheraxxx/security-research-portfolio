# Ronda 3 — El payload: VM localizada

**Fecha:** 2026-10-14

## Hallazgo principal: `.3q-` son DOS cosas distintas

El análisis por regiones (entropía + distribución de bytes) parte la sección de 7,43 MB
en dos bloques con perfiles radicalmente distintos:

| Región | Tamaño | Entropía | Bytes REX | `0x00` | Naturaleza |
|---|---|---|---|---|---|
| `0x81C000 – 0xE3C000` | **6,2 MB** | 7,97 – 7,99 | 6,0 – 7,2 % | ~0,4 % | **bytecode** (uniforme, indetectable por análisis estático) |
| `0xE3C000 – 0xF8A8A4` | **1,31 MB** | 6,80 – 7,06 | **15,5 – 17,2 %** | 5 – 7 % | **intérprete VM en x86-64 real** |

Los bytes REX (`0x40`–`0x4F`) al 16 % frente al 3,1 % uniforme son una firma
inequívoca de código x86-64. La frontera exacta está en `RVA 0xE3C000`.

## Arquitectura del protector

```
0x140001000  .text      94 KB    App C++ limpia (loader, chequeos de registro/procesos)
0x140023000  .7 f      212 KB    CRT de MSVC
0x14081C000  .3q- (a)  6,2 MB    BYTECODE  <- el programa virtualizado
0x140E3C000  .3q- (b)  1,3 MB    INTÉRPRETE VM  <- dispatcher + handlers
0x140F8B000  .rsrc      36 KB    icono + manifiesto
```

El patrón de dispatch es inequívoco:

```asm
sub  r11, 4            ; retrocede el puntero de bytecode
mov  edi, [r11]        ; lee el operando
jmp  0x140ebfd82       ; salta al handler correspondiente
```

y el handler principal asigna el contexto de la VM en la pila:

```asm
lea  rdx, [rsp + 0x140]    ; contexto VM = 0x140 bytes
cmp  rbp, rdx
ja   ...
mov  rax, rsp
```

## Recuperación del intérprete por descenso recursivo

El desensamblado **lineal es inútil**: muere en el primer byte inválido porque el
código está desincronizado a propósito. Con descenso recursivo sembrado en puntos
conocidos (destinos de salto ya observados + las 27 direcciones de `.3q-` que la
traza de ejecución demuestra ejecutadas):

| Métrica | Valor |
|---|---|
| Direcciones decodificadas | **2.342** |
| Saltos/llamadas directos | 184 |
| Handlers alcanzados | **175** |
| Grafo exportado | `vm_dispatch_graph.json` |

Semilla más rentable: `0x140E49F04` (5 referencias) — es el dispatcher principal,
el que asigna el contexto de VM.

## Por qué no hay tabla de handlers

Busqué secuencias de qwords alineados que apunten a handlers conocidos
(≥6 de 64 entradas). **Cero resultados.** El protector calcula la dirección del
handler por aritmética (`base + opcode × stride`), no por tabla indirecta.

Consecuencia práctica: **la recuperación estática de la ISA no es viable.** El opcode
hay que deducirlo dinámicamente del estado en el momento del salto.

## Ruta que queda (dinámica)

1. Emular el intérprete con **unicorn**, sembrando el contexto VM (r8/r11 = puntero
   de bytecode, rbp = base del contexto, 0x140 bytes)
2. Registrar la dirección de handler en cada dispatch
3. El estado de entrada permite deducir el opcode por diferencia
4. Levantar cada handler a una operación semántica (usando las técnicas de Symbolic
   Execution de Triton sobre el bloque del handler)
5. Reconstruir el bytecode a x86

Escalar estimado: semanas. El límite se puede ver ya: para esto hace falta conocer
el estado inicial de la VM, que solo se obtiene ejecutando el sample hasta que
supera el check anti-VM — que es exactamente lo que está atacando el subagente
dedicado a Frida.

## Artefactos

| Fichero | Contenido |
|---|---|
| `stage2_code.bin` | los 1,31 MB del intérprete extraídos |
| `vm_dispatch_graph.json` | 2.342 direcciones + 184 aristas |
| `anchors_3q.txt` | las 27 direcciones de `.3q-` ejecutadas |
| `vm_recover.py` | descenso recursivo del intérprete |
| `map_payload.py` | mapa estructural por entropía y distribución de bytes |
| `find_dispatch.py` | búsqueda de tabla de handlers |

## Correcciones acumuladas de diagnósticos previos

1. «Está cifrado con XOR» → **falso**. IC plano (0,0043) para todos los periodos 1–32.
2. «`.3q-` es bytecode de VM, todo virtualizado» → **parcialmente falso**.
   El bytecode es 6,2 MB, pero 1,31 MB son el intérprete nativo.
3. «El código no tiene xrefs porque es bytecode» → ahora se entiende: la lógica
   está en el bytecode, que no genera xrefs estáticas por definición.