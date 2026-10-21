#!/usr/bin/env bash
# Ejecuta un comando en un NAMESPACE DE MONTAJE PROPIO con:
#   - DMI falso (Dell XPS 8960) sobre /sys/class/dmi/id
#   - /etc/hosts falso: el panel del C2 resuelve a 127.0.0.1
#
# IMPORTANTE: si se invoca SIN `unshare -m` delante, este script se re-ejecuta
# a si mismo dentro de `unshare -m`. Sin eso, los bind-mount se aplicarian al
# namespace del host (ya paso una vez y dejo /etc/hosts del host redirigido).
set -u
FAKE=/tmp/opencode/fakedmi

if [ "${GARABATO_NS:-}" != "1" ]; then
    exec unshare -m env GARABATO_NS=1 "$0" "$@"
fi

mount --bind "$FAKE/hosts" /etc/hosts 2>/dev/null
mount --bind "$FAKE/nsswitch.conf" /etc/nsswitch.conf 2>/dev/null
for f in "$FAKE"/*; do
  b=$(basename "$f")
  case "$b" in hosts|c2.pem|c2.key|c2-bundle.pem|nsswitch.conf|nsswitch.orig|hosts.bak) continue;; esac
  [ -e "/sys/class/dmi/id/$b" ] && mount --bind "$f" "/sys/class/dmi/id/$b" 2>/dev/null
done
exec "$@"
