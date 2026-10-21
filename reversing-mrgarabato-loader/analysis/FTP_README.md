# Servidor FTP de laboratorio — vsftpd

Servicio **FTP con lectura y escritura**, activo, persistente (systemd) y
verificado con 30 pruebas automáticas.

## Acceso

| Vía | Usuario | Contraseña | Raíz del FTP | Permisos |
|---|---|---|---|---|
| Autenticado | `black` | `1234` | **`/` real del sistema** | lectura + escritura (ACL sobre el árbol del laboratorio) |
| Anónimo | `anonymous` | *(ninguna)* | `/srv/ftp/anon` | lectura en `/`, escritura en `/upload` |

- Dirección: **192.168.64.5:21** (interfaz `enp0s2`) — bind específico, **no**
  escucha en `0.0.0.0` ni en `127.0.0.1`
- Puertos pasivos: 40000-40100; el PASV anuncia `192,168,64,5`
- Config: `/etc/vsftpd.conf`
- Log: `/var/log/vsftpd.log`

```bash
lftp -u black,'1234' 192.168.64.5
curl -u black:'1234' ftp://192.168.64.5/ -o fichero
curl -u black:'1234' -T local.bin ftp://192.168.64.5/root/mrgarabato_analysis/run/
```

## Estructura

### Usuario autenticado — sin chroot

`local_root=/` y `chroot_local_user=NO`: al conectar, `black` cae directamente
en la **raíz real del sistema** y navega el árbol completo.

```
/                          <-- raiz del FTP = raiz del sistema
/root/mrgarabato_analysis/ <-- arbol del laboratorio (R/W para 'black' via ACL)
```

El acceso de escritura no viene del propietario de los ficheros (que sigue
siendo `root`), sino de **ACL POSIX** aplicadas recursivamente:

```
setfacl -R -m u:black:rwX /root/mrgarabato_analysis
setfacl -d -m u:black:rwX /root/mrgarabato_analysis   # hereda a los ficheros nuevos
chmod 715 /root                                          # listar + travesar, sin escribir
```

`/root` queda en `715` a propósito: permite **atravesar** y **listar** hacia
`/root/mrgarabato_analysis`, pero no **escribir** en `/root` ni en `/etc`.
`/root` contiene 39 ficheros ocultos (`.ssh/`, `.gnupg/`, `.claude.json`,
`.bash_history`…) que **no se pueden descargar**: `RETR` responde
`550 Failed to open file.` porque sus permisos siguen siendo `600`/`700`.

### Listado de ficheros ocultos

vsftpd **filtra los dotfiles en el listado** (comportamiento interno de
`dir.c`, sin opción de configuración que lo cambie). El flag `-a` sí lo
desactiva:

| Comando | Resultado |
|---|---|
| `LIST /root` | 25 entradas (solo las no ocultas) |
| `LIST -a /root` | 66 entradas (25 + 39 ocultas + `.` + `..`) |
| `NLST /root` | 25 nombres sin ruta |
| `NLST -a /root` | 66 nombres **con la ruta completa** (`/root/.bashrc`) — rareza de vsftpd |

En un cliente gráfico esto es la casilla "mostrar archivos ocultos", que
traduce a `LIST -a`.

### Anónimo — con chroot

```
/srv/ftp/anon/             root:root 755     <- anon_root
    /srv/ftp/anon/upload/  ftp:ftp 775      <- unica zona escribible por anonimo
```

El anónimo sigue confinado en su propio chroot y no ve el sistema.

### Home de la cuenta

```
/srv/ftp/black/            black:black 755  <- home de la cuenta en /etc/passwd
    README.txt             credenciales de acceso
```

Ya no es la raíz del FTP (eso es `/`), pero se conserva como directorio de
trabajo propio de la cuenta.

## Gestión

```bash
./ftpctl.sh start|stop|restart|status|test|users|logs
```

## Notas de la puesta en marcha (cuatro fallos reales resueltos)

1. **`/etc/pam.d/ftp` no existía.** El default de vsftpd es
   `pam_service_name=ftp` (`tunables.c: install_str_setting("ftp", ...)`), pero
   el paquete de Arch solo instala `/etc/pam.d/vsftpd`. Sin el fichero `ftp`,
   PAM cae en el servicio `other` y **todos** los logins locales devolvían
   `530 Login incorrect.` Creado `/etc/pam.d/ftp` + `pam_service_name=vsftpd`
   explícito en la config.

2. **`allow_writeable_chroot` no aplica a anónimos.** En
   `twoprocess.c:453` la opción solo se activa si `!was_anon`; para el login
   anónimo el check de `secutil.c:138` se aplica siempre. Por eso
   `anon_root` debe ser de `root` (no escribible por `ftp`) y la escritura
   anónima va en el subdirectorio `/upload`, propiedad de `ftp:ftp`.

3. **Opciones inexistentes en vsftpd 3.0.5**: `local_chroot_write_enable`,
   `anon_delete_enable`, `anon_rename_enable` y `anon_write_enable` son
   rechazadas con `500 OOPS: unrecognised variable in config file`. Los
   errores se escriben en **fd 0**, no en stderr — si rediriges stdout a una
   tubería, el mensaje se pierde y parece un cuelgue.

4. **`RNFR` con ruta absoluta falla con vsftpd sin chroot**: el servidor
   resuelve la ruta contra el directorio de trabajo actual de la sesión, así
   que hay que hacer `CWD` al destino y usar nombres **relativos** (es lo que
   hacen los clientes reales). `STOR`/`DELE`/`MKD` sí aceptan ruta absoluta.

## Verificación

```bash
python3 /root/mrgarabato_analysis/run/ftprw_test.py
```

Cubre: login (local y anónimo), `PWD` en la raíz real, `NLST` del árbol del
sistema, STOR, RETR con comparación de SHA-256, MKD, RNFR/RNTO, DELE, RMD,
SIZE, CWD, R/W con ruta absoluta, y el aislamiento por chroot del anónimo.
