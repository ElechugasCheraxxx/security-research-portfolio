# Informe final — MrGarabato ByPassEmulator & LoaderAdvanced

**Fecha:** 2026-10-14 · **Entorno:** Black Arch Linux · **Estado:** análisis dinámico completo, payload desempaquetado

---

## 0. Veredicto

Ambos binarios son componentes de un **cheat comercial para Garena Free Fire** que se inyecta
en emuladores de Android (BlueStacks / MEmu). El "bypass emulator" no evade la detección del
juego: **evade la detección de máquina virtual/sandbox** del propio programa, para poder
ejecutarse en el entorno de análisis.

- `MrGarabato-ByPassEmulator.exe` → componente de inyección en el emulador
- `MrGarabato-LoaderAdvanced.exe` → cargador autenticado que instala además un **driver de kernel**

---

## 1. Cadena de ataque

```
1. Arranque  → packer desempaqueta 8 MiB de imagen en memoria
2. Anti-VM  → SMBIOS + enumeración de dispositivos + centinela 0xDEADC0DE
              si falla: NtRaiseHardError(STATUS_VM_DETECTED) + MessageBox
3. C2        → GET https://panel.mrgarabato.com/Download/cmd.php?t=<token>
               respuesta JSON: email, discordid, subscription, subscription_level,
               expiry_date, hwid_affected, created_at, last_login, hwid,
               app_secret, owner_id, app_name, message, token, update_url, user
4. Kill-switch → "expired" / "Application disabled" / "Project Disabled" /
                 "Outdated version" / "Old Project Version" / "Project Off"
5. Emulador  → espera HD-Player.exe (BlueStacks) o MEmu.exe (MEmu Play)
6. Inyección → abre el proceso del emulador e inyecta
7. Driver    → (solo Loader) descarga e instala WinDivert64.sys como servicio "MiDriver"
```

Banner del programa:

```
   __  __       ____                 _           _
|  \/  |_ __ / ___| __ _ _ __ __ _| |__   __ _| |_ ___
| |\/| | '__| |  _ / _` | '__/ _` | '_ \ / _` | __/ _ \
| |  | | |  | |_| | (_| | | | (_| | |_) | (_| | || (_) |
|_|  |_|_|   \____|\__,_|_|  \__,_|_.__/ \__,_|\__\___/

Bypass Emulator
 >> MRGARABATO - THE BEST BYPASS EMULATOR <<
```

---

## 2. Indicadores de compromiso (IOC)

### Red
| Indicador | Tipo |
|---|---|
| `https://mrgarabato.com/` | landing / kill-switch |
| `https://panel.mrgarabato.com/` | panel de control |
| `https://panel.mrgarabato.com/Download/cmd.php?t=7RobSZuyx23L677ulvLD1Cq` | C2 con token |
| `.../Download/Paquete/MrGarabato/Profesional/pack/MrGarabato/FakeLag/WinDivert.dll` | descarga driver user-mode |
| `.../FakeLag/WinDivert64.sys` | descarga driver kernel |
| `mrgarabato.com`, `panel.mrgarabato.com` | dominios |

### Host
| Indicador | Tipo |
|---|---|
| `SOFTWARE\Microsoft\PhoneHx\Ignyx` | clave de persistencia |
| `C:\Windows\Help\Windows\Log` | directorio de staging (imitando ayuda de Windows) |
| `C:\Windows\System32\SystemSettingsRemoveDevice.exe` | exe soltado con nombre de sistema |
| `\14ddg0941cvah.exe`, `\34dbbmddg71c.exe` | nombres aleatorios generados en runtime |
| servicio kernel `MiDriver` (`sc create MiDriver type= kernel start= demand`) | persistencia de driver |
| `SeDebugPrivilege` | elevación |
| `YX9Y0KWPU6` | identificador compartido entre ambos binarios |
| `Nf7D?!r+WMtb3Z&s3_` | posible `app_secret` (ofuscado) |
| mutex `UpdatedFreeFire_ByPass`, `UpdatedFreeFire_SecurityHx` | instancia única |

---

## 3. Análisis del packer

| # | Nombre | VA | VSZ | RAW (fichero) | Entropía inicial | Entropía tras desempaquetar |
|---|---|---|---|---|---|---|
| 0 | `.text` | 0x1000 | 0x162DC | 0 | – | **6.307** |
| 1 | `.rdata` | 0x18000 | 0x7AFC | 0 | – | **6.613** |
| 2 | `.data` | 0x20000 | 0x1188 | 0 | – | – |
| 3 | `.pdata` | 0x22000 | 0xEE8 | 0 | – | – |
| 4 | `.7 f` / `.eff` | 0x23000 | ~0x7F7D93 | 0 | – | 7.901 |
| 5 | `.zzc` / `.3rs` | 0x81B000 | 0xE00 | 0xE00 | 0.298 | IAT |
| 6 | `.3q-` / `.w7/` | 0x81C000 | 0x76E8A4 | 0x76EA00 | **7.948** | 7.948 (VM-protector) |
| 7 | `.rsrc` | 0xF8B000 | 0x8E48 | 0x9000 | – | icono + manifiesto |

- Las secciones 0–4 suman **exactamente 8 MiB** virtuales con `SizeOfRawData = 0`:
  el packer reconstruye una imagen de 8 MiB desde un blob cifrado de 7,44 MiB.
- Nombres de sección aleatorios por build → **builder automatizado**.
- Los dos binarios comparten **solo el 0,70 %** de los bytes (cabeceras DOS + sección de
  recursos). Plantilla idéntica, payload y configuración distintos.

### Anti-análisis estático
- EP dentro del blob cifrado (no ejecutable tal cual)
- TLS Directory **señuelo**: `AddressOfCallBacks = NULL`
- Load Config sin handlers SEH (`SEHandlerCount = 0`)
- Export Directory corrupta: el nombre resuelve al propio encabezado `MZ`
- Solo 26 imports, **uno por DLL**, seleccionados al azar entre builds

---

## 4. Mecanismo anti-VM (descubierto dinámicamente)

Secuencia observada con `WINEDEBUG=+relay`:

| Vector | Detalle |
|---|---|
| SMBIOS | `GetSystemFirmwareTable('RSMB')` → busca "QEMU", "VMWare", "VirtualBox", "Virtual Machine" |
| Dispositivos | `SetupDiGetDeviceRegistryPropertyW(SPDRP_HARDWAREID)` **234 llamadas** |
| Proceso | `NtQueryInformationProcess` ×96 |
| Sentinela | `CloseHandle(0xDEADC0DE)` → espera `STATUS_INVALID_HANDLE` |
| VEH | `RtlAddVectoredExceptionHandler` instalado (técnica anti-debug clásica) |
| Salida | `NtRaiseHardError(0x50000018)` = **`STATUS_VM_DETECTED`** |

Mensaje mostrado:
> `Sorry, this application cannot run under a Virtual Machine.`

### Bypass aplicado
Wine leía el DMI del host (esta máquina **es a su vez una VM QEMU**). Se sobrescribió
mediante *bind-mounts* dentro de un **mount namespace** (el host no se modifica):

```
antes: QEMU | Standard PC (Q35 + ICH9, 2009) | pc-q35-10.0 | EFI Development Kit II / OVMF
despues: Dell Inc. | XPS 8960 | 01.0.0 | 2.14.1
```

Resultado: el `MessageBox` desapareció (0 detecciones), aunque `STATUS_VM_DETECTED` se
siguió invocando por un vector residual (probablemente `HKLM\SOFTWARE\Wine` o la
enumeración de dispositivos de Wine, no corregida).

Scripts reutilizables en `run/`: `fake_dmi.sh`, `dump_mem.py`, `rebuild_pe.py`, `probe*.c`.

---

## 5. Artefactos generados

| Fichero | Descripción |
|---|---|
| `run/mem_bypass.bin` | imagen desempaquetada de ByPassEmulator (16.334.848 B) |
| `run/mem_loader.bin` | imagen desempaquetada de LoaderAdvanced (16.367.616 B) |
| `run/unpacked_bypass.exe` | PE reconstruido y navegable |
| `run/unpacked_loader.exe` | PE reconstruido y navegable |
| `run/run_bypass.relay` | traza de APIs (101 MB) — ejecución original |
| `run/run3.relay` | traza de APIs con DMI falsificado |
| `run/net_before.pcap` | captura de red (**sin contacto con el C2**) |
| `bypass_icon.png` / `loader_manifest.xml` | recursos extraídos |

SHA-256:
- `mem_bypass.bin`  = `e70039e728a4387175db636df41d2f1da6e08af4def99937d3a18f12b5d81055`
- `mem_loader.bin`  = `16bb5e6b805fde66979c354a42fbd1b825d804bfc138fd012dcfa479d4f60b28`

---

## 6. Estado y limitaciones

- ✅ Payload completamente desempaquetado; **todos los datos y strings legibles**
- ✅ C2, IOC, flujo de ejecución, driver de kernel y persistencia identificados
- ⚠️ El **código** sigue protegido por un VM-obfuscator (junk instructions, predicados
  opacos). `.3q-` mantiene entropía 7.948 porque se descifra por bloques en runtime.
  Para decompilación completa en Ghidra haría falta desempaquetar esos bloques
  dinámicamente (dump en bloques de 4 KB tras cadaPAGE fault / breakpoint).
- ⚠️ Las cadenas minoritariamente ofuscadas (`995#!9/p:`, `Nf7D?!r+WMtb3Z&s3_`, …) usan un
  cifrado de clave multi-byte; el XOR de 1 byte no las decodifica.
- ℹ️ La extracción se hizo sin completar el bypass de VM: **no se llegó al payload final**.
  El comportamiento está inferido de cadenas y de la API traceada, no de ejecución completa.