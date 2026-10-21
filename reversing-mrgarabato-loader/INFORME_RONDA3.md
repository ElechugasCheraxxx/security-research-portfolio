# INFORME RONDA 3 — Parcheo de la puerta anti-VM y preparations para capturar el C2

## Resumen

**La puerta anti-VM ha sido superada de forma reproducible en AMBAS muestras.**
`NtRaiseHardError(STATUS_VM_DETECTED)` = 0 en todas las ejecuciones parcheadas, y el
diálogo *"Sorry, this application cannot run under a Virtual Machine"* ha desaparecido.

La causa raíz resultó ser **inline**, no basada en API: `CPUID` y `RDTSC`.

---

## 1. Por qué el parcheo en `.text` no bastaba

Se localizaron y neutralizaron 9 funciones de comprobación en `.text` (C++ limpio,
descompilado sin problemas):

| RVA | Comprobación |
|---|---|
| `0x12290` | Enumera procesos buscando `vmtoolsd.exe`, `vmwaretray.exe`, `vmwareuser.exe`, `vmacthlp.exe`, `VGAuthService.exe` |
| `0x120F0`, `0x12100` | Registro `HARDWARE\ACPI\DSD` |
| `0x0EE70`, `0x0EE80` | Registros de depuración |
| `0x0F1E0` | `CreateToolhelp32Snapshot` / `Process32Next` |
| `0x0DD10`, `0x10E20`, `0x11020` | Otros usuarios del hash FNV |

**Funcionó**: tras el parcheo, `SetupDiGetDeviceRegistryProperty`, `RegOpenKeyA`,
`CreateToolhelp32Snapshot`, `Process32Next` y `GetThreadContext` **dejan de llamarse**
(comprobado sobre la traza). La traza pasó de 69,7 MB a 101,6 MB: el programa hace más
trabajo. **Pero el abort seguía disparándose.**

El motivo: la **decisión se computa dentro de la VM** (`.3q-`), no en `.text`.

## 2. La llamada universal de la VM

Todas las invocaciones de API desde el intérprete de la VM usan exactamente esta
secuencia:

```
mov rax,[rsp+0x00] ; sub rsp,0x20 ; call rax ; mov rsp,[rsp+0x25]
```

El `mov rsp,[rsp+0x25]` posterior **restaura la pila desde el frame de la VM**, así que
anular el `call rax` (`FF D0` → `90 90`) no desequilibra nada. Esto permite localizar
cualquier llamada a partir de su dirección de retorno en la traza de relay, sin
desensamblar código desincronizado.

Comprobado: `CloseHandle(0xDEADC0DE)` devuelve `c0000008` (STATUS_INVALID_HANDLE),
**idéntico a Windows real**; ese centinela pasa correctamente. La VM usa 5 llamadas
nativas de detección, todas anuladas:

| Sitio | Llamada |
|---|---|
| `0x0E809E4` | `NtQueryInformationProcess(ProcessDebugPort)` |
| `0x0F06BCE` | `NtQueryInformationProcess(ProcessDebugObjectHandle)` |
| `0x0E39BD6` | `NtQuerySystemInformation(SystemKernelDebuggerInformation)` |
| `0x0EB3A28` | `NtQuerySystemInformation(SystemModuleInformation)` |
| `0x0F46856` | `NtQuerySystemInformation(SystemModuleInformation)` |

**Resultado: `NtRaiseHardError` siguió disparando.** Ninguna de esas APIs es la decisión.

## 3. La causa real: `CPUID` y `RDTSC`

Estas detecciones **no generan ninguna llamada a API**, por lo que son invisibles en la
traza de relay e inalcanzables desde `.text`. Es exactamente el hueco que quedaba.

Contado en el intérprete (código real, 1,31 MB):

| Instrucción | `.text` | Intérprete |
|---|---|---|
| `0F A2` `CPUID` | 3 | 111 |
| `0F 31` `RDTSC` | 1 | 146 |

Sustituidas por `31 C0` (`xor eax,eax`), **misma longitud**, para no desplazar nada:

- `CPUID` → `xor eax,eax`  → hoja 0, sin hipervisor
- `RDTSC` → `xor eax,eax`  → delta de tiempo cero

**Resultado decisivo:**

```
NtRaiseHardError(VM_DETECTED)  = 0
MessageBox "Virtual Machine"   = 0
```

Verificado en 6 ejecuciones (3 de cada muestra), incluido el modo `cpuid` aislado y el
modo `rdtsc` aislado: **cualquiera de los dos por separado ya anula el abort**, es decir
la comprobación es redundante.

## 4. Corrección de un error previo

Mi informe anterior situaba la URL del C2 en **ByPassEmulator**. Es incorrecto: las URLs
están en **LoaderAdvanced**, en claro en `mem_loader.bin` a `0x230D8`:

```
https://panel.mrgarabato.com/Download/cmd.php?t=7RobSZuyx23L677ulvLD1Cq
https://panel.mrgarabato.com/Download/Paquete/MrGarabato/Profesional/pack/MrGarabato/FakeLag/WinDivert.dll
https://panel.mrgarabato.com/Download/Paquete/MrGarabato/Profesional/pack/MrGarabato/FakeLag/WinDivert64.sys
```

ByPassEmulator solo contiene `https://mrgarabato.com/` (`0x19F70`). LoaderAdvanced usa
**WinHttp** (`WinHttpReceiveResponse failed:`), no WinINet.

## 5. Infraestructura de captura del C2 montada

El host **no tiene salida TCP a Internet** (solo DNS): `panel.mrgarabato.com` resuelve a
`15.204.248.132` pero `curl https://mrgarabato.com/` agota 20 s y devuelve HTTP 000.

Preparado:

- `run/c2_server.py` — servidor HTTPS local que registra método, ruta, cabeceras y cuerpo.
- `run/fake_dmi_net.sh` — namespace de montaje que aplica a la vez el DMI falso (Dell
  XPS 8960) y un `/etc/hosts` falso que manda el panel a `127.0.0.1`. El tráfico nunca
  sale a Internet: queda en la máquina.
- Certificado autofirmado para `panel.mrgarabato.com`.

Verificado: dentro del namespace, `panel.mrgarabato.com → 127.0.0.1` y el SMBIOS
devuelve `Dell Inc. / XPS 8960` simultáneamente.

## 6. Comportamiento tras superar la puerta

Ambas muestras, ya sin abort, ejecutan la misma secuencia y salen con `exit(0)`:

1. Lectura de SMBIOS (`GetSystemFirmwareTable('RSMB')`) → valores Dell
2. Huella del equipo: `MachineId`, `NetworkCards\1..7`, `ProfileList`, `gethostname`
3. `getaddrinfo("<hostname del host>")` — resuelve **solo su propio nombre**, jamás el
   dominio del panel
4. `wcscmp("GenuineIntel","AuthenticAMD")` → cadena de CPU `"%s Family %..."`
5. Intento de renombrado: `GetPrivateProfileSectionW(L"rename", …, L"wininit.ini")` →
   **falla** (`retval=0`), luego `SetComputerNameExA`
6. `InternetOpenW(L"Wine")` → `InternetCloseHandle` → **`exit(0)`**

**No se llega a contactar con el C2**: cero `InternetConnectA`/`HttpOpenRequestA`, cero
peticiones al servidor local, y ni el ASCII-art banner llega a imprimirse. La traza es
byte a byte idéntica entre ejecuciones (31.512.424 B), o sea totalmente determinista.

La tabla de mensajes del servidor en `.rdata` (`0x19F50`–`0x19FE2`) — `expired`,
`Application disabled`, `Proyect Disabled`, `Outdated version`, `Old Project Version`,
`Project Off` — junto con los campos JSON `username` / `email` / `discordid` /
`subscription` / `token`, indica que es un **producto licenciado que valida contra su
servidor**. Lo que aún no se ha resuelto es qué condición bloquea el paso a la fase de
red.

## 7. Errores propios corregidos en esta ronda

| Error | Causa |
|---|---|
| Los volcados daban 51 KB en vez de 16 MB | `find_pid` cogía el proceso Wine de PID más bajo; Wine mapea en `0x140000000` en **cada** proceso (33 a la vez). Corregido filtrando por nombre de ejecutable |
| 0 parches aplicados | Abría `/proc/PID/mem` en `"rb"`; escribir exige `"rb+"`. `io.UnsupportedOperation` hereda de `OSError` y mi `except` lo tragaba en silencio |
| La rama nunca se parcheaba | La fijé en `0x0E4D451` cuando estaba en `0x0E4D441` (error de aritmética al indexar la ventana) |
| Trazas mezcladas entre muestras | `open(...,"wb")` trunca pero no invalida el descriptor del proceso anterior, que seguía escribiendo |

## 8. Estado

| Objetivo | Estado |
|---|---|
| Packer | **Superado** |
| Cifrado de cadenas | **Superado** |
| Anti-VM / anti-debug | **Superado** (CPUID + RDTSC + parches `.text`) |
| Huella del equipo | **Documentada** |
| Captura del C2 | **Infraestructura lista**, sin tráfico capturado todavía |
| Extracción del payload | **Pendiente** — bloqueada por el paso a la fase de red |

## 9. Próximo paso

Determinar qué condición impide el paso a la fase de red. Candidatos, en orden de
rentabilidad:

1. **Rastrear la condición de salida** con el mismo método que funcionó aquí: buscar
   comprobaciones *inline* adicionales, ya que la decisión no está en ninguna API.
2. **Sonda de conectividad**: el patrón `InternetOpenW` → `InternetCloseHandle` →
   `exit` sugiere un test de red que we're viendo pasar. Interceptar *todo* el tráfico
   TCP saliente con `iptables -t nat -A OUTPUT -j DNAT` dentro de un namespace de red,
   en lugar de redirigir solo el dominio del panel.
3. **Estado de licencia**: la tabla de mensajes sugiere que falta autenticación. Los
   campos `username`/`token` podrían construirse en runtime; rastrearlos igual que se
   hizo con los nombres de proceso.