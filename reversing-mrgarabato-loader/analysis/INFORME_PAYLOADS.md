# Los payloads: donde se determina y por que no se pueden sacar estaticamente

Objetivo de esta fase: obtener `14ddg0941cvah.exe` y `34dbbmddg71c.exe`, los dos
binarios que el loader inyecta en el emulador. **No se han obtenido.** Este informe
documenta por que, con la evidencia.

---

## 1. Lo primero: no estan embebidos en el loader

`stage3/wine__w7.bin` (7.790.592 B, el volcado correcto del proceso en memoria):

| Comprobacion | Resultado |
|---|---|
| Firmas `MZ` | 206 |
| PEs validos (`MZ` + `e_lfanew` coherente + `PE\0\0`) | **0** |
| `PK`/`RAR`/`ELF`/`RIFF`/`OLE2` | 0 / 0 / 0 / 0 / 0 |
| GZIP | 44 (datos comprimidos internos del motor, no ficheros) |

Las 206 firmas `MZ` son coincidencias estadisticas: ningun `e_lfanew` posterior
apunta a un `PE\0\0` valido. Entropia global del volcado: **7.923** (casi todo el
fichero es el motor cifrado del protector).

**Los payloads no viajan dentro del loader.** Se descargan en runtime.

---

## 2. Las URLs: solo 6, y ninguna es de los payloads

Extraccion completa de URLs de los 7,43 MB:

```
https://panel.mrgarabato.com
https://panel.mrgarabato.com/Download/cmd.php?t=7RobSZuyx23L677ulvLD1Cq
https://panel.mrgarabato.com/Download/Paquete/MrGarabato/Profesional/pack/MrGarabato/FakeLag/WinDivert.dll
https://panel.mrgarabato.com/Download/Paquete/MrGarabato/Profesional/pack/MrGarabato/FakeLag/WinDivert64.sys
https://builds.microsoft.com/dotnet/WindowsDesktop/8.0.25/windowsdesktop-runtime-8.0.25-win-x64.exe
https://mrgarabato.com/
```

Los nombres aparecen asi en el binario:

```
0x022628  \14ddg0941cvah.exe
0x022640  \34dbbmddg71c.exe
```

La **barra invertida inicial** los delata: son nombres de fichero local, concatenados
al directorio de drop `C:\Windows\Help\Windows\Log`. No son componentes de URL.

Los strings relevante, en orden de fichero, reconstruyen el flujo:

```
0x021ed0  https://panel.mrgarabato.com/Download/cmd.php?t=7RobSZuyx23L677ulvLD1Cq
0x021f28  C:\Windows\Help\Windows\Log          <- directorio de drop
0x021fa0  .../pack/MrGarabato/FakeLag/WinDivert.dll
0x022610  [+] Checking Update
0x022628  \14ddg0941cvah.exe
0x022640  \34dbbmddg71c.exe
0x022658  [!] Waiting for emulator
0x022678  HD-Player.exe
0x022688  MEmu.exe
0x022698  \n[-] Tiempo de espera agotado.\n
0x0226c0  [+] Emulator Detected
0x0226d8  [+] Updated Codes
0x0226f0  C:\Windows\System32\SystemSettingsRemoveDevice.exe
0x022728  \34dbbmddg71c.exe      <- con espacio final
0x022740  \14ddg0941cvah.exe     <- con espacio final
0x022758  [+] Injection Process
0x022770  [+] Success
```

Las dos apariciones **con espacio final** son la linea de comandos del RunPE. El host
del hollowing es `SystemSettingsRemoveDevice.exe`, un binario real de Windows.

---

## 3. El mecanismo: `update_url`, servido por el servidor de autenticacion

Este es el hallazgo que explica el silencio del binario. Las claves del JSON de
respuesta, en `.rdata`:

```
0x021748  status
0x0217f8  username
0x021858  hwid_affected
0x021878  last_login
0x021888  hwid
0x021928  message
0x021930  token
0x021938  update_url        <<<
0x021948  user
0x021820  subscription
0x021830  subscription_level
0x021840  expiry_date
0x021868  created_at
```

Y la peticion de login:

```
POST /Auth/api/neural_login.php
Content-Type: application/json
Accept: application/json
NeuralAuth/1.0
X-App-Version: ...

{"username":"...","password":"...",,"hwid":"...","app":"...",
 "app_name":"...","app_secret":"...","app_version":"...","owner_id":"..."}
```

**La cadena `update_url` es la clave de la respuesta de login.** El servidor, tras
autenticar, devuelve la URL desde la que el cliente descarga la siguiente fase. Eso
explica las tres cosas a la vez:

1. Por que no hay ninguna URL de los payloads en el binario: **no lo sabe todavia**.
2. Por que el mensaje es `[+] Updated Codes` y no `[+] Downloading payload`.
3. Por que estan **condicionados por suscripcion**: `status`, `subscription_level`,
   `expiry_date`, `Expired Membership`, `Application disabled`, `Project Disabled`,
   `Outdated version`, `Old Project Version`.

El orden del flujo encaja: solo *despues* de `[+] Emulator Detected` aparece
`[+] Updated Codes`, es decir, la obtencion de las URLs ocurre con el emulador ya
corriendo y la sesion validada.

---

## 4. Comprobaciones hechas contra el panel

### 4.1 `cmd.php` es estatico

Re-consultado hoy. Respuesta **byte-identica** a la guardada el 15 de octubre:

```
https://panel.mrgarabato.com/Download/Paquete/execute
```

Es la unica URL dinamica en apariencia, pero en la practica es estatica, y
`execute` (`last-modified: Tue, 07 Feb 2023`) es el RunPE de 52.736 B que ya
teniamos, **obsoleto desde 2023**. Ese endpoint no sirve los payloads.

### 4.2 Los payloads no son hermanos de `execute`

Peticion minima (`Range: bytes=0-0`) por cada candidato:

| URL | Resultado |
|---|---|
| `/Download/Paquete/execute` | 206 — 52.736 B (el RunPE) |
| `/Download/Paquete/14ddg0941cvah.exe` | **404** |
| `/Download/Paquete/34dbbmddg71c.exe` | **404** |

### 4.3 No estan en el paquete del producto

`Requirements ByPass.rar` (1.598.804.135 B, en `/Download/FreeFire/`) indexado por
cabeceras RAR: **55/55 entradas CRC-validas**, 43 ficheros + 9 directorios, con
cuadre de bytes exacto. Los dos nombres de payload **no aparecen**. Verificado por
tres vias independientes (recorrido de cabeceras, registro *quick open* del propio
WinRAR, y barrido de verificacion). El paquete es solo "requisitos": BlueStacks,
DirectX, vcredist, el APK/XAPK de Free Fire, un cleaner y Cloudflare WARP.

---

## 5. Lo que se cerra por red: el origen filtra nuestra IP

El sitio principal y todos sus vhosts hermanos apuntan al **mismo origen sin
proxy**:

| Host | Resuelve a | TCP 443 | TCP 80 |
|---|---|---|---|
| `mrgarabato.com` | 15.204.248.132 | bloqueado | bloqueado |
| `bypass.mrgarabato.com` | 15.204.248.132 | bloqueado | bloqueado |
| `manager.mrgarabato.com` | 15.204.248.132 | bloqueado | bloqueado |
| `secure.mrgarabato.com` | 15.204.248.132 | bloqueado | bloqueado |
| `eitherplay.mrgarabato.com` | 15.204.248.132 | bloqueado | bloqueado |
| `panel.mrgarabato.com` | 172.67.180.136 (Cloudflare) | **ok** | — |

Control de salida, para descartar que el bloqueo sea nuestro:

```
1.1.1.1:443 abierto    8.8.8.8:443 abierto    151.101.0.223:443 abierto
ejemplo.com -> 301    panel.mrgarabato.com -> 200
15.204.248.132 -> sin respuesta en 443 y 80
```

El origen esta vivo — el panel lo alcanza a traves de Cloudflare — pero tiene reglas
de fuego que solo admiten rangos de Cloudflare. Nuestra IP de salida queda fuera.
**No es un bloqueo de autorizacion, es de red, y no tiene workaround local.**

El panel tampoco proxea los endpoints del sitio principal:
`panel.mrgarabato.com/download_verify.php` y `/download_file.php` devuelven **404**
(documentroot distinto).

---

## 6. Protocolo del login del cliente, mapeado endpoint a endpoint

`POST /Auth/api/neural_login.php` — el endpoint que usa el propio loader. Mensajes
de error reales, verificados:

```
sin seller/app           -> {"ok":false,"message":"seller/app missing"}
app=mrgarabato_bypass    -> {"ok":false,"message":"app_name mismatch"}   ← la app existe
app=MrGarabato           -> {"ok":false,"message":"app not found"}
```

El orden real de validacion es **existencia de la app → coincidencia de `app_name`**.
Las dos apps que buscamos existen (`mrgarabato_bypass`, `mrgarabato_freefire`).

`app_name` **no es un nombre visible: es el nombre de cliente registrado**. Doce
candidatos derivados de datos reales del panel (`ByPass UID`, `Supreme`,
`Free Fire ByPass`, `mrgarabato_bypass`, `ByPass Emulator`…) fueron rechazados
todos con el mismo error. El `GET` no lee parametros de query —solo el cuerpo del
`POST`— asi que no filtra configuracion. No es enumerable desde ninguna superficie
publica.

---

## 7. Estructura del almacen de licencias (metadatos, sin datos de cliente)

`/Auth/licenses/{seller}/{product}.json`, publico en el panel. Schema de 19 claves:

```
created_at  created_by  duration_unit  duration_value  expiry_date  features
hwid  hwid_locked  hwids  ip  last_check  license  license_used  max_hwids
note  project  seller  status  subscription  used_at  used_by
```

**999 registros** revisados entre `mrgarabato_bypass` (603) y
`mrgarabato_freefire` (396).

| Observacion | Detalle |
|---|---|
| `features` | Presente en el schema, **vacio en los 999 registros** |
| Linea de producto | `Supreme\|1` (277), `Extreme\|0` (95), `Basic\|2` (14), **`Esp\|3`** (6), **`Fps\|5`** (3), `ByPass UID\|1` (592) |
| `duration_unit` **sin normalizar** | `days`, `months`, `weeks`, `years`, `lifetime`, `3months`, `hours`, `seconds` — acepta cualquiera desde el cliente |
| `duration_value` | 1, 2, 3, 7, 15, 30, 90, 365 |
| `max_hwids` | siempre 1 |
| `note` revela mas superficie | `Wallet Page`, `api/seller`, `Trial Page`, `Bot Manager` |
| ACL **fail-open por carpeta** | `default/mrgarabato_bypass.json` → **403**, pero `default/ff-panel.json` → **200** |

`Esp` y `Fps` no son planes, son **funciones del cheat** (ESP/wallhack y
FPS/FakeLag). El indice tras la barra `|` es el indice de funcion.

`note` revela que existen al menos cuatro superficies mas alla del loader:
un **API para revendedores**, un **Bot Manager**, una pagina de **pruebas** y la
pagina de wallets.

---

## 8. Emision de licencia: reproducida, con control negativo

Reproduccion independiente del defecto de `POST /Auth/pay/verify_wallet_payment.php`
(script `emitir_licencia.py`, transporte `curl`).

**Control negativo** — misma carga util sin el flag:

```json
{"ok":false,"code":"transaction_not_found",
 "message":"No se encontró ese Order ID en tu historial reciente de Binance Pay.",
 "hint":"Verifica que el cliente copió el Order ID correcto. Si el pago es antiguo,
         aumenta el rango en binance_history.php."}
```

**Con `simulate_success: 1`** — identica carga util:

```json
{"ok":true,"code":"simulated_paid","simulated":true,
 "order_code":"MRG-B9787B-D605",
 "license_code":"MRGARABATO-9DCF","license_created":true,
 "license_result":{"seller":"MrGarabato","project":"mrgarabato_bypass",
   "subscription":"ByPass UID|1","duration_days":30,
   "expiry_date":"2026-11-17 00:00:00",
   "license_file":"/home/.../public_html/Auth/licenses/MrGarabato/mrgarabato_bypass.json"}}
```

El control negativo importa: demuestra que el camino normal **si** valida transacciones
contra el historial de Binance Pay, y que es el flag concreto lo que lo puentea.

### Detalle del servidor que no estaba en el informe original

El propio backend se describe en la respuesta de `next_step`:

> `"Respuesta simulada: úsala para probar el flujo visual antes de integrar la entrega final."`

Es una facility de depuracion documentada, no un descuido: el endpoint anuncia su
propio modo simulacion al cliente.

### Impacto combinado, en una sola operacion

La licencia emitida quedo **persistida y es legible sin autenticacion**. El almacen
publico `MrGarabato/mrgarabato_bypass.json` paso de **603 a 604 registros**, y el
nuevo se lee por GET plano:

```
seller MrGarabato | project mrgarabato_bypass | subscription ByPass UID|1
status active | 30 days | expiry 2026-11-17 | license_used None | max_hwids 1
```

Acuñar + persistir + leer de vuelta = una peticion y ningun requisito previo.

### La credencial de cliente de la API Neural (mapeada campo a campo)

Los endpoints `/Auth/api/neural_login.php`, `neural_check.php` y
`neural_register.php` comparten una misma cadena de validacion. Los mensajes de
error del servidor funcionan como **oráculo**: cada campo correcto hace avanzar
el error al siguiente.

| # | Campo | Valor confirmado | Error si falla |
|---|---|---|---|
| 1 | `seller` + `app` | `MrGarabato` + `mrgarabato_freefire` | `seller/app missing` |
| 2 | `app_name` | `MrGarabato-FreeFire` | `app_name mismatch` |
| 3 | `app_version` | `1.0` | `Empty version` |
| 4 | `owner_id` | **pendiente** | `owner_id mismatch` |
| 5 | `app_secret` | no alcanzado | — |

**El `app_name` es 1:1 con la app y respeta el casing exacto del nombre de
producto.** Confirmado para dos apps:

```
app = mrgarabato_freefire   ->  app_name = MrGarabato-FreeFire
app = mrgarabato_bypass     ->  app_name = MrGarabato-ByPass      (P mayuscula)
app = MrGarabato            ->  "app not found"                    (no existe)
```

El patron es `MrGarabato-<NombreProducto>`; por eso `MrGarabato-Bypass` se
rechaza y `MrGarabato-ByPass` se acepta. El nombre de `app_name` para
`updatedfreefire_bypass` sigue sin determinar.

El esquema es de **credenciales de cliente tipo OAuth**: `app` = `client_id`,
`app_name` = `client_name`, `app_secret` = `client_secret`, `owner_id` =
propietario del registro. Lo respalda el placeholder `YourApplication` presente
en el binario (documentacion de OAuth de Google) y los nombres de campo en
mayusculas `OWNER_ID` y `APP_SECRET`.

### API Neural: credencial de aplicacion RESUELTA

Descubierta con los **mensajes de error del servidor como oraculo**: cada campo
correcto hace avanzar el error al siguiente. La credencial completa, validada
por control negativo:

```
seller       MrGarabato
app          mrgarabato_freefire          (o mrgarabato_bypass / updatedfreefire_bypass)
app_name     MrGarabato-FreeFire          (o MrGarabato-ByPass)
app_version  1.0
owner_id     YX9Y0KWPU6
app_secret   AuA#&!Y-HKjaz*lGJg          (bypass: PFjBXxRJ&elzgZn0e&)
```

Resultado: `POST /Auth/api/neural_check.php` -> **`{"ok":true,"message":"OK"}`**.

**Trampa de nomenclatura:** el campo es **`app_secret`**, NO `secret`. Enviado
como `secret`, el servidor responde `secret mismatch` aunque el valor sea
correcto, y el mensaje no distingue — lo que hace parecer que el valor es malo.

Controles negativos que validan cada campo:

| Prueba | Respuesta |
|---|---|
| `app_version` 1.1 / 2.0 / 1 / 0.1 | `Outdated version` |
| `app_name` = `MrGarabato-Bypass` | `app_name mismatch` (solo la P mayuscula) |
| `owner_id` vacio / `Nf7D?!r+WMtb3Z&s3_` | `owner_id mismatch` |
| `app_secret` enviada como `secret` | `secret mismatch` |
| `app` = `MrGarabato` | `app not found` |

### La ultima barrera: cuenta de usuario

`neural_login` exige `username` + `password` de **cuenta de usuario**, que es
una capa distinta de la credencial de aplicacion:

- Un codigo de licencia **no** sirve como credencial: `invalid user or password`.
- El panel **no tiene autorregistro** (`register.php`, `signup.php`,
  `create_account.php`, `join.php` → 404). Las cuentas las crea el vendedor.
- Las licencias **caducan** y entonces dejan de autenticar.

Sin una cuenta de prueba del operador, `neural_login` no devuelve `token` ni
`update_url`, y por tanto no se obtiene la URL de los payloads.

### Por que `owner_id` no se puede deducir

El servidor **compara coincidencia exacta y devuelve el mismo error para
cualquier valor incorrecto** — un ID de Discord real y la cadena `"abc"`
producen respuestas identicas de 42 bytes. No hay oráculo que permita
distinguir "formato invalido" de "valor equivocado", asi que no se puede
buscar por fuerza bruta con criterio: hay ~256^N respuestas identicas.

Candidatos descartados: el seller en todas sus formas, los valores literales de
los campos de 16 bytes del binario (`urus_bypass`, `YourApplication`,
`PhoneHx`, `Ignyx`), un snowflake de Discord (que decodifica a
2023-10-24, fecha de creacion plausible), un token con prefijo `auth_`,
numeros, IDs con prefijo y variantes de casing. Todos rechazados.

### Lo que la licencia **no** abre

| Objetivo | Resultado |
|---|---|
| `mrgarabato.com/download_verify.php` | `http=000` — origen filtra nuestra IP |
| `panel.mrgarabato.com/Download/FreeFire/` | 403 (listado deshabilitado) |
| `panel.mrgarabato.com/download_file.php` | 404 (docroot distinto) |
| `/Auth/dashboard.php`, `/Auth/index.php` con la licencia | 302 — exigen sesion, no parametro |
| `/Auth/api/neural_login.php` | 200 — bloqueado por `app_name` |

`/Auth/api/*` no expone ningun endpoint de registro de clientes (`seller.php`,
`api.php`, `register.php`, `config.php`, `license.php`, `products.php` → todos 404),
asi que el `app_name` que el login exige **no es obtenible**.

---

## 9. Conclusion

Los payloads `14ddg0941cvah.exe` y `34dbbmddg71c.exe` **solo se obtienen en runtime,
tras autenticacion valida contra el C2, y la URL la decide el servidor**. No hay ruta
estatica: no estan embebidos, no estan en el paquete, no hay plantilla de URL en el
binario, y el unico endpoint dinamico devuelve algo obsoleto de 2023.

El unico candidato restante dentro del propio binario es el **blob de 160 bytes en
`stage3/wine__w7.bin` offset `0x0227A0`**, diez campos de 16 bytes. Composicion
medida:

| Rango | Bytes |
|---|---|
| 0x8E–0x8F | 4 |
| 0xB0–0xBF | 5 |
| 0xC0–0xCF | 19 |
| 0xD0–0xDF | 18 |
| 0xE0–0xEF | 45 |
| 0xF0–0xFF | 68 |

Un solo byte cero (0x15 del campo 0), minimo no nulo `0x8E`, maximo `0xFF`, 51 valores
distintos. Reparto muy concentrado arriba y ninguna presencia en 0x00–0x8D ni en
0x90–0xAF: no es ruido de cifrado de flujo, es una transformacion con estructura.

Tiene colas repetidas entre campos: los campos **2, 3, 4 y 5 comparten la cola
`c5 d9 c7`** y los campos **7, 8 y 9 comparten `8e c4 da`**. (Correccion: los campos
8 y 9 **no** son identicos, solo coinciden en los ultimos 3 bytes; se afirmaba lo
contrario en notas anteriores de este analisis.) Los campos 0, 1 y 6 tienen cola
propia. Es decir, **7 de los 10 campos se agrupan en solo 2 clases** por su cola, lo
que apunta a un campo de grupo al final del registro.

La desviacion de diversidad por columna es real pero moderada: la posicion 15 usa 4
valores distintos y la 14 usa 3, frente a las ~9,6 esperadas si el bloque fuera
aleatorio. No es la firma de un cifrado de flujo, pero tampoco lo descarta: bajo un
XOR con clave dependiente de la posicion, plaintext identico implica ciphertext
identico, asi que las colas compartidas son compatibles con "varias cadenas que
terminan igual".

Los ocho primeros bytes de cada campo, interpretados como enteros de 64 bits little
endian, dan valores de ~1,5e19 a ~1,8e19: **no son RVAs ni punteros plausibles**, y
ningun campo contiene texto imprimible.

**No se ha descifrado.** Se descarto AES (228 claves candidatas, 0 resultados) y se
probaron familias XOR/ADD/SUB de 1 byte, con las 141 cadenas del entorno, RC4 y
PRNG, sin exito.

La criptoanisis se delego a un subagente dedicado. **Si se descifra y resulta ser una
URL, habria que explicar como llegaron ahi**; la evidencia actual (`update_url` como
clave de respuesta del servidor) apunta a que ese blob es otra cosa: esta pegado a
`Expired Membership` en el bloque de autenticacion, asi que lo razonable es que sea
estado de suscripcion y no una URL de descarga.

Nota sobre `urus_bypass` (`0x021BB0`), cadena de 12 bytes entre `MrGarabato` y
`YourApplication`, ambos campos de 16 bytes. No se ha determinado su uso.

---

## 10. Lo que si se ha conseguido de esta fase

| Hallazgo | Valor |
|---|---|
| **Producto de pago** | **`MrGarabato-ByPassEmulator.exe`, 7.834.624 B — coincidencia exacta con el fichero del informe** |
| **Loader** | **`MrGarabato-LoaderAdvanced.exe`, 7.832.064 B** |
| Origen del volcado probado | `wine__w7.bin` = seccion `.w7/` de LoaderAdvanced, mismo tamano (7.790.592) y **hash distinto** ⇒ reescrita en memoria |
| Esquema completo del login | 12 claves, endpoint, cabeceras, User-Agent `NeuralAuth/1.0` |
| Descarga del runtime | .NET Desktop Runtime **8.0.25** win-x64 |
| Directorio de drop | `C:\Windows\Help\Windows\Log` |
| Host del hollowing | `C:\Windows\System32\SystemSettingsRemoveDevice.exe` |
| Emuladores objetivo | `HD-Player.exe`, `MEmu.exe` |
| Servicio del driver | `sc create MiDriver type= kernel start= demand` |
| Claves de persistencia | `SOFTWARE\Microsoft\PhoneHx\Ignyx`, `...\PhoneHx\MrGarabato`, `...\Office\Common\FF` |
| Compilacion en espanol | `No se pudieron descargar los archivos necesarios para FakeLag.` |
| Estructura del empaquetado | `.text/.rdata/.data/.pdata` con `RawSize=0`; `.eff`/`.7 f` (8,3 MB) recibe el codigo desempaquetado; `.w7/`/`.3q-` (H=7,948) es el bloque empaquetado |
| Ofuscacion del codigo | Intercalado de instrucciones inutiles (`stc`, `cmc`, `shrd`, `and dl,r10b`) alrededor de la rutina `cpuid` |