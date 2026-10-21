# Muestras retenidas e indicadores (IOC)

Este documento documenta los artefactos que **no se hospedan en el repositorio** y por qué.
Práctica estándar en research de reversing: se publica el análisis, el pseudocódigo y los
indicadores; las muestras vivas se comparten por canales controlados (p. ej. MalwareBazaar,
VirusTotal, intercambio directo con el vendor) y nunca en un repo de portfolio.

---

## 1. Binarios retenidos (no hospedados)

GitHub no permite el alojamiento de muestras activas de malware en sus términos de servicio
(aplica también a repositorios privados). Los binarios analizados tienen características
objetivas de malware (packer con secciones de entropía 7.9, anti-VM, inyección en procesos,
instalación de driver de kernel, C2 con kill-switch), por lo que cualquier motor los marca.
Se publican sus hashes para verificación independiente.

| Artefacto | SHA256 |
|---|---|
| `MrGarabato-ByPassEmulator.exe` (original) | retenido — muestra del vendor |
| `MrGarabato-LoaderAdvanced.exe` (original) | retenido — muestra del vendor |
| `unpacked_loader.exe` (imagen desempaquetada en memoria) | `70471c0041dfb5004b07cf53517d5dc0d2f3ce7958661f64192a8a16ad4defd5` |
| `loader_textonly.exe` | `c36f79647d1133e15eeea7eedb2c91d894913a346bc080b6e66a87e934a1b38e` |
| `WinDivert.dll` (user-mode, descargado del C2) | `a97859785a2df1d4462e7d48d33ccbd89fedd40dac4970f4afd89e63f59ee1ec` |
| `WinDivert64.sys` (driver de kernel, instalado como servicio `MiDriver`) | `53ab28ec00be6e6f8aefa9ee76fc2735e94d7f3f9dbc06eb2b7ac8cd3084a6af` |
| `14ddg0941cvah.exe`, `34dbbmddg71c.exe` (payloads con nombre aleatorio) | retenidos — ver `c2_descargas/` local |
| `builds/` (MrGarabatoD.exe, MrGarabatoTv.exe, VIP_FF.exe) | retenidos — builds del vendor |

También retenidos: volcados de memoria (`dumps/`, `*.relay`, `*.bin`), capturas de red
(`*.pcap`), prefijos de Wine (`wineprefix*`, `wine_hooks/`) y paquetes descargados del panel
(`panel_dl/`, `c2_descargas/` completo).

## 2. Datos de clientes retenidos (PII)

Los stores de licencias del panel (`store2.json`, `bypass_store.json`, `freefire_store.json`)
contienen **604 + 603 + 396 registros reales de clientes** (códigos de licencia, HWID, IP,
fechas). Aunque el repositorio es privado, no se publican datos personales de clientes reales.

- En su lugar: [`samples/license-store-structure-sanitized.json`](samples/license-store-structure-sanitized.json)
  (estructura real con IPs y notas redactadas).
- Las capturas del panel (`panel/`) se retienen por contener códigos de licencia reales
  incrustados en el HTML.

## 3. IOC

### Red
| Indicador | Tipo |
|---|---|
| `https://mrgarabato.com/` | landing / kill-switch |
| `https://panel.mrgarabato.com/` | panel de control |
| `https://panel.mrgarabato.com/Download/cmd.php?t=<token>` | C2 |
| `.../Download/Paquete/MrGarabato/Profesional/pack/MrGarabato/FakeLag/WinDivert.dll` | descarga driver user-mode |
| `.../FakeLag/WinDivert64.sys` | descarga driver kernel |

### Host
| Indicador | Tipo |
|---|---|
| `SOFTWARE\Microsoft\PhoneHx\Ignyx` | clave de persistencia |
| `C:\Windows\Help\Windows\Log` | directorio de staging (imitando ayuda de Windows) |
| `C:\Windows\System32\SystemSettingsRemoveDevice.exe` | exe soltado con nombre de sistema |
| servicio kernel `MiDriver` (`sc create MiDriver type= kernel start= demand`) | persistencia de driver |
| `SeDebugPrivilege` | elevación |
| `YX9Y0KWPU6` | identificador compartido entre ambos binarios |
| mutex `UpdatedFreeFire_ByPass`, `UpdatedFreeFire_SecurityHx` | instancia única |

### Anti-análisis
- Packer: 8 MiB virtuales reconstruidos desde blob cifrado de 7,44 MiB; secciones con
  entropía 7.9 (VM-protector); nombres de sección aleatorios por build (builder automatizado).
- Anti-VM: SMBIOS + enumeración de dispositivos + centinela `0xDEADC0DE`;
  `NtRaiseHardError(STATUS_VM_DETECTED)` al detectar sandbox.
- Kill-switch: `expired`, `Application disabled`, `Project Disabled`, `Outdated version`,
  `Old Project Version`, `Project Off`.
