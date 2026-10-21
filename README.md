# Security Research Portfolio — Reversing & Authorized Black-Box Pentest

Portafolio de investigación en seguridad ofensiva con dos proyectos completos:

| # | Proyecto | Tipo | Resultado |
|---|---|---|---|
| 1 | [`pentest-mrgarabato-com/`](pentest-mrgarabato-com/) | Black-box pentest autorizado (aplicación web) | **9 vulnerabilidades confirmadas** (1 crítica, 2 altas, 4 medias, 2 bajas), CVSS v3.1, PoCs ejecutados end-to-end |
| 2 | [`reversing-mrgarabato-loader/`](reversing-mrgarabato-loader/) | Análisis estático + dinámico de binarios Windows | Packer custom, anti-VM, inyección en emuladores y driver de kernel desentrañados; 900+ funciones descompiladas |

---

## Proyecto 1 — Black-box pentest: mrgarabato.com

Evaluación black-box extrema y autorizada sobre la plataforma de licenciado **Neural Auth**
(`mrgarabato.com`, `panel.mrgarabato.com`), sin acceso a código fuente, con pruebas
directas al origen bypaseando el WAF de Cloudflare vía routing de vhost por Host header.

**Resumen:** compromiso total del modelo de negocio de licencias sin autenticación —
falsificación de pagos sin auth que emite licencias reales, divulgación completa de la base
de licencias de clientes, y descarga directa del producto estrella de 1.6 GB sin gate de
licencia. La capa de infraestructura (HestiaCP, phpMyAdmin, OpenSSH) resistió: el compromiso
es 100% en la capa de aplicación / lógica de negocio.

- Metodología: OWASP WSTG + PTES, reconocimiento primero, verificación independiente de cada
  hallazgo con controles negativos.
- Entregables: informe ejecutivo + técnico, 9 write-ups con PoC, `findings.sarif`,
  `vulnerabilities.json/csv`, `coverage.json`.
- **Estado:** todas las vulnerabilidades reportadas al vendor y **parcheadas** antes de
  publicar este portfolio.

➡️ Detalles: [`pentest-mrgarabato-com/README.md`](pentest-mrgarabato-com/README.md)

## Proyecto 2 — Reversing: MrGarabato ByPassEmulator & LoaderAdvanced

Análisis completo (estático + dinámico) de dos binarios Windows: un componente de inyección
en emuladores de Android (BlueStacks/MEmu) y un cargador autenticado que instala además un
driver de kernel. El "bypass emulator" no evade la detección del juego: **evade la detección
de máquina virtual/sandbox** del propio programa para poder ejecutarse en entornos de análisis.

**Cadena desentrañada:** packer (8 MiB reconstruidos en memoria) → anti-VM (SMBIOS,
enumeración de dispositivos, centinela `0xDEADC0DE`) → C2 con kill-switch → espera del
emulador → inyección → descarga e instalación de `WinDivert64.sys` como servicio `MiDriver`.

- Herramientas: Ghidra, IDA/Hex-Rays, angr, Speakeasy, BinDea, RetDec, CAPA, FLOSS, Wine
  (+ hooks `WINEDEBUG=+relay`), radare2, mitmproxy.
- Entregables: 20+ informes (desofuscación, pseudocódigo, IOCTL, RunPE, virtualización,
  rondas de análisis), 900+ funciones descompiladas, scripts de automatización, IOCs.
- **Nota:** las muestras vivas y los datos de clientes reales **no se hospedan aquí** —
  ver [`MUESTRAS-E-IOCS.md`](reversing-mrgarabato-loader/MUESTRAS-E-IOCS.md) (hashes SHA256
  incluidos para verificación independiente).

➡️ Detalles: [`reversing-mrgarabato-loader/README.md`](reversing-mrgarabato-loader/README.md)

---

## Ética y alcance

- El pentest se realizó bajo **autorización** sobre infraestructura propia del vendor
  (`mrgarabato.com`), con alcar documentado y verificación independiente de cada hallazgo.
- Las vulnerabilidades fueron reportadas de forma responsable y **parcheadas** antes de
  esta publicación; los PoCs se publican con fines educativos.
- El análisis de binarios se realizó en entorno aislado (VMs + Wine) sobre muestras
  obtenidas legítimamente del producto comercial analizado.
- No se hospedan muestras activas de malware ni datos personales de clientes reales.

## Mapa del repositorio

```
├── README.md                                  ← este archivo
├── pentest-mrgarabato-com/
│   ├── README.md                              ← resumen del engagement
│   ├── penetration_test_report.md             ← informe ejecutivo + técnico
│   ├── findings.sarif                         ← hallazgos en formato SARIF
│   ├── vulnerabilities.json / .csv           ← datos estructurados de hallazgos
│   ├── coverage.json                          ← cobertura de la evaluación
│   └── vulns/vuln-0001..0009.md               ← write-ups con PoC por hallazgo
└── reversing-mrgarabato-loader/
    ├── README.md                              ← resumen del análisis
    ├── MUESTRAS-E-IOCS.md                     ← muestras retenidas + IOC + hashes
    ├── INFORME_FINAL.md                       ← informe principal
    ├── INFORME_*.md, REPORTE_TRIAGE.md, ...   ← informes por área
    ├── bypass_manifest.xml, loader_manifest.xml
    ├── bypass_icon.png, loader_icon.png
    ├── samples/                               ← estructura de datos sanitizada
    └── analysis/                              ← artefactos: scripts, descompilación,
                                                  pseudocódigo, logs, capturas
```
