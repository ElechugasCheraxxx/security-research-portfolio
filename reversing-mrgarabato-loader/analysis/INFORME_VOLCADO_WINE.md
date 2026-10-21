# El volcado de Wine: lo que revelaba el payload desempaquetado

## El error que cometí antes

Extraje 1,33 MB de "código claro" del **fichero en disco**, donde la región
desempaquetada está al final de la sección. Los **volcados de memoria del
proceso Wine** (`mem_loader.bin`, `mem_check.bin`) contienen la sección
`.w7/`/`.3q-` **íntegramente desempaquetada desde el offset 0**.

Comparación con χ²/255 (≈1 = uniforme/cifrado, >5 = estructura):

| Artefacto | 1er bloque | 2º | 3º |
|---|---|---|---|
| `mem_loader.bin` `.w7/` | **4.890,97** | 55,56 | 38,04 |
| `mem_check.bin` `.3q-` | **6.144,76** | 67,35 | 50,05 |
| fichero en disco `.w7/` | 3,66 | 0,98 | 5,37 |

**5,8× más payload** del que estaba analizando. Perfil de densidad del volcado,
bloques de 512 KB:

```
0M: 15635   0,5M: 74   1M: 221   1,5M: 221   2M: 220   2,5M: 222
3M:   219   3,5M: 218   4M: 216   4,5M: 147   5M: 243   5,5M: 293
6M:    74   6,5M: 1510   7M: 5207
```

Ghidra sobre los primeros 512 KB (`stage3/chunk0.exe`): **629 procedimientos y
273 cadenas**, frente a **1 solo procedimiento** en los 1,33 MB del disco.

---

## 1. speakeasy no supera la protección

Intentado antes de encontrar los volcados:

```
2.364.640 instrucciones ejecutadas
PC 0x140d88535 (EP) -> 0x140eb9a25 (región clara)
APIs chamadas: 0            ← NINGUNA
escrituras: 1.187.561 B, todas a 0x12f0000 (stack, 99 % ceros)
Δ χ²/255 en las zonas cifradas: +0,000 en todas
```

El stub entra en la región clara y **se queda girando sin llegar nunca a la
frontera del SO**. speakeasy no emula lo que el stub necesita (probablemente
alguna API, excepción o chequeo de hardware). **Resultado negativo y firme.**

Los ficheros con `*.py` quedan en `se_unpack.py`, `se_where.py`, `se_trace.py`.

---

## 2. Identidad del producto

```
MRGARABATO - THE BEST ADVANCED CHEAT <<
```

---

## 3. Flujo de consola completo

Las cadenas aparecen **en orden** en el binario (offset ~0x22629):

```
[+] Checking Update.....
        \14ddg0941cvah.exe
        \34dbbmddg71c.exe
[!] Waiting for emulator........
        HD-Player.exe
        MEmu.exe
[-] Tiempo de espe...                      ← mensaje en ESPAÑOL
    ...tected...
[+] Updated Codes.......
C:\Windows\System32\SystemSettingsRemoveDevice.exe
        \34dbbmddg71c.exe
        \14ddg0941cvah.exe
[+] Injection Process...
[+] Success
Expired Membership
```

Orden operativo: **comprobar actualización → descargar los dos payloads →
esperar al emulador → comprobar si está detected → actualizar codes → instalar →
inyectar → verificar membresía**.

Que haya un mensaje en español (`Tiempo de espe…`) encaja con la locale que ya
encontramos en la ruta de compilación del driver: `C:\Aplicaciones\...`.

---

## 4. Autenticación — endpoint nuevo

```
https://panel.mrgarabato.com/Auth/api/neural_login.php
User-Agent: NeuralAuth/1.0
Accept: application/json
Content-Type: application/json
```

Campos JSON presentes en el binario:

| Cadena | Significado |
|---|---|
| `,"app_version":"` | versión del cliente |
| `,"hwid":"` | **HWID de la máquina** |
| `token` | token de sesión |
| `status` | estado |
| `last_login` | último acceso |
| `hwid_affected` | **el HWID cambió** (típico de máquina clonada / VM) |
| `expired` | suscripción caducada |
| `Empty response` | gestión de respuesta vacía |

`hwid_affected` es relevante para nuestra línea de VM: **el producto detecta que
el HWID no corresponde** cuando el entorno cambia. Eso es un vector
anti-análisis independiente del CPUID.

Errores del cliente HTTP: `WinHttpOpen failed`, `WinHttpConnect failed`,
`WinHttpOpenRequest failed`, `WinHttpSendRequest failed: `,
`WinHttpReceiveResponse failed: `.

---

## 5. Persistencia

```
sc create MiDriver type= kernel start= demand binPath= "
sc start MiDriver
sc stop MiDriver
sc delete MiDriver
```

Claves de registro:

```
SOFTWARE\Microsoft\PhoneHx\MrGarabato      ← NUEVA (ya teníamos ...\Ignyx)
SOFTWARE\Microsoft\PhoneHx\Ignyx
SOFTWARE\Policies\Microsoft\Windows\System
\REGISTRY\MACHINE\SOFTWARE\Classes
\Registry\Machine\Software\Classes\
```

Errores: `RegCreateKeyExW failed.`,
`Cannot write DWORD value: RegSetValueExW failed.`,
`Cannot write string value: RegSetValueExW failed.`

---

## 6. Descargas

```
https://panel.mrgarabato.com/Download/cmd.php?t=7RobSZuyx23L677ulvLD1Cq
https://panel.mrgarabato.com/Download/Paquete/MrGarabato/Profesional/pack/MrGarabato/FakeLag/WinDivert.dll
https://panel.mrgarabato.com/Download/Paquete/MrGarabato/Profesional/pack/MrGarabato/FakeLag/WinDivert64.sys
https://builds.microsoft.com/dotnet/WindowsDesktop/8.0.25/windowsdesktop-runtime-8.0.25-win-x64.exe
https://mrgarabato.com/
```

**Nuevo y relevante: descarga el runtime .NET 8 Desktop.** Eso explica los
nombres de payload `14ddg0941cvah.exe` y `34dbbmddg71c.exe` — probablemente
ensamblados .NET, lo que concuerda con las cadenas RTTI de .NET encontradas:

```
.?AV?$_Iosb@H@std@@
.?AV?$basic_ios@DU?$char_traits@D@std@@@std@@
.?AVRegException@winreg@@
.?AV?$exception@std@@
.?AV?$runtime_error@std@@
mscoree.dll
DllRegisterServer
```

---

## 7. Los nombres de payload NO son generados en runtime — corrección

El subagente del RAR concluyó que `14ddg0941cvah.exe` y `34dbbmddg71c.exe`
"son nombres generados en runtime, no ficheros empaquetados". **Es incorrecto.**
Están como **cadenas literales** en el payload, con el prefijo `\` de ruta:

```
...\14ddg0941cvah.exe......\34dbbmddg71c.exe.......
```

Lo que el subagente sí acertó es que **no están dentro del paquete RAR**: se
descargan en runtime desde el C2. Las dos cosas son ciertas a la vez.

---

## 8. Anti-análisis observado

`GetActiveWindow` y `GetLastActivePopup` aparecen juntas — es el patrón clásico
para **detectar si hay un MessageBox abierto**, que es como un protector o un
analista se delata. Junto con `hwid_affected` (HWID cambia entre ejecuciones) y
`Expired Membership`, son tres vectores anti-análisis distintos:

1. HWID inconsistente entre sesiones
2. Detección de diálogos de depurador
3. Verificación de suscripción (implica conexión al C2 antes de operar)

---

## 9. Cuantificación de cadenas

```
ASCII  >=5 : 17.040
UTF-16 >=5 :    105
total       : 17.121   -> stage3/wine_strings.txt
```

Incluye además strings del CRT de MSVC (`- not enough space for locale
information`, `pure virtual function call`), lo que confirma la compilación con
Microsoft Visual C++.

---

## 10. Pendiente

- Localizar las funciones que referencian estas cadenas (en curso, subagente)
- Los 6,2 MB que speakeasy no Achievé a descifrar **ya no son necesarios**: los
  volcados de Wine los tienen
- Queda por determinar si el runtime .NET implica que los payloads son
  ensamblados gestionados — muy relevante para el análisis de la cadena completa