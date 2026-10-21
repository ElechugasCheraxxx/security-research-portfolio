#!/bin/bash
# Ejecuta el sample dentro de un mount namespace con DMI falso (hardware realista).
# Los bind-mounts viven solo en el namespace: el host no se modifica.
set -u
EXE="$1"
FAKE=/tmp/opencode/fakedmi
mkdir -p "$FAKE"
w() { printf '%s' "$2" > "$FAKE/$1"; }

w sys_vendor "Dell Inc.";        w product_name "XPS 8960"
w product_version "01.0.0";       w product_family "XPS"
w product_sku "0B98-3D";          w product_serial "DL7K92QX"
w bios_vendor "Dell Inc.";        w bios_version "2.14.1"
w bios_date "03/21/2024";         w bios_release "2.14.1"
w chassis_vendor "Dell Inc.";     w chassis_type "3"
w chassis_version "A01";          w chassis_serial "DL7K92QX"
w board_vendor "Dell Inc.";       w board_name "0DTG8T"
w board_version "A01"

INNER=$(cat <<'EOS'
FAKE="$1"; shift
for f in "$FAKE"/*; do
  b=$(basename "$f")
  [ -e "/sys/class/dmi/id/$b" ] && mount --bind "$f" "/sys/class/dmi/id/$b" 2>/dev/null
done
echo "--- DMI en el namespace ---"
for k in sys_vendor product_name bios_vendor bios_version chassis_vendor; do
  printf "  %-16s: %s\n" "$k" "$(cat /sys/class/dmi/id/$k 2>/dev/null)"
done
echo "--- ejecutando: $* ---"
exec "$@"
EOS
)

# EXE contiene "wine RUTA_WIN"; se pasa con word splitting intencional
exec unshare -m bash -c "$INNER" _ "$FAKE" $EXE