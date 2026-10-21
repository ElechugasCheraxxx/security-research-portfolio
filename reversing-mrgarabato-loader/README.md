# Reversing — MrGarabato ByPassEmulator & LoaderAdvanced

Análisis estático y dinámico completo de dos binarios Windows: un componente de inyección
en emuladores de Android (BlueStacks / MEmu) y un cargador autenticado que instala además
un driver de kernel. El "bypass emulator" no evade la detección del juego: **evade la
detección de máquina virtual/sandbox** del propio programa para poder ejecutarse en
entornos de análisis.

**Veredicto:** ambos binarios son componentes de un cheat comercial para Garena Free Fire.

## Cadena de ataque desentrañada

```
1. Arranque   → packer desempaqueta 8 MiB de imagen en memoria (blob cifrado de 7,44 MiB)
2. Anti-VM    → SMBIOS + enumeración de dispositivos + centinela 0xDEADC0DE
                si falla: NtRaiseHardError(STATUS_VM_DETECTED) + MessageBox
3. C2         → GET panel.mrgarabato.com/Download/cmd.php?t=<token> (JSON con suscripción,
                expiry, hwid, app_secret, kill-switch...)
4. Kill-switch→ "expired" / "Application disabled" / "Project Disabled" / ...
5. Emulador   → espera HD-Player.exe (BlueStacks) o MEmu.exe (MEmu Play)
6. Inyección  → abre el proceso del emulador e inyecta
7. Driver     → (solo Loader) descarga e instala WinDivert64.sys como servicio "MiDriver"
```

## Entregables

### Informes (raíz del proyecto)
| Informe | Contenido |
|---|---|
| [`INFORME_FINAL.md`](INFORME_FINAL.md) | Informe principal: veredicto, cadena de ataque, IOCs, packer, anti-VM |
| [`INFORME_C2.md`](INFORME_C2.md) | Protocolo C2, kill-switch, campos del JSON de comando |
| [`INFORME_DESOFUSCACION.md`](INFORME_DESOFUSCACION.md) | Desofuscación de strings y datos |
| [`INFORME_PSEUDOCODIGO.md`](INFORME_PSEUDOCODIGO.md) | Pseudocódigo de las rutinas clave |
| [`INFORME_PAYLOAD.md`](INFORME_PAYLOAD.md) | Análisis del payload |
| [`INFORME_IOCTL_DINAMICO.md`](INFORME_IOCTL_DINAMICO.md) | IOCTLs del driver en ejecución |
| [`INFORME_PLAN_DEVIRTUALIZACION.md`](INFORME_PLAN_DEVIRTUALIZACION.md) | Plan de virtualización del packer |
| [`INFORME_RONDA2.md`](INFORME_RONDA2.md) / [`RONDA3`](INFORME_RONDA3.md) | Rondas de análisis iterativo |
| [`INFORME_SUBIDS.md`](INFORME_SUBIDS.md) | Subsistemas identificados |
| [`REPORTE_TRIAGE.md`](REPORTE_TRIAGE.md) | Triage inicial |
| [`INDICE_HERRAMIENTAS.md`](INDICE_HERRAMIENTAS.md) | Índice de herramientas usadas |

### Artefactos (`analysis/`)
- **900+ funciones descompiladas** (`decomp_bypass/`, `decomp_text/`, `hexrays/`,
  `decomp_loader/`) y descompilación Ghidra (`rea_out/`, `chunk0_ghidra.md`)
- Scripts de automatización (angr, decodificación de strings, bruteforce de posiciones,
  extracción de secciones, shims, bridges IDA/mitmproxy/cutter)
- Pseudocódigo del driver (`driver_decomp.c`, `driver_pseudoc.c`)
- Logs de instrumentación (Wine relay, angr, Ghidra, Speakeasy, CAPA, FLOSS)
- Capturas de red/flujo y páginas de checkout (`chk_*.html`, `pago.html`, `c2_capture.log`)
- Informes adicionales: [`INFORME_MAESTRO.md`](analysis/INFORME_MAESTRO.md),
  [`INFORME_HEXRAYS.md`](analysis/INFORME_HEXRAYS.md),
  [`INFORME_RUNPE.md`](analysis/INFORME_RUNPE.md),
  [`INFORME_VOLCADO_WINE.md`](analysis/INFORME_VOLCADO_WINE.md), entre otros

### Muestras y datos
[`MUESTRAS-E-IOCS.md`](MUESTRAS-E-IOCS.md) — binarios retenidos con hashes SHA256,
IOCs completos (red/host/anti-análisis) y nota sobre datos de clientes.
[`samples/`](samples/) — estructura sanitizada de los stores de licencias del panel.

## Herramientas

Ghidra · IDA Pro / Hex-Rays · angr · Speakeasy · BinDea · RetDec · CAPA · FLOSS ·
Wine (`WINEDEBUG=+relay`) · radare2 · mitmproxy · binwalk · foremost · xorscan ·
Python (peles/pwntools-style automation)

## Nota

Las muestras vivas, volcados de memoria, capturas pcap y los stores de licencias con datos
de clientes reales **no se hospedan en este repositorio** (políticas de GitHub y PII).
Ver [`MUESTRAS-E-IOCS.md`](MUESTRAS-E-IOCS.md).
