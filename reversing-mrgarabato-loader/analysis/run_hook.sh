#!/bin/bash
# Lanza el sample dentro del namespace con DMI falso + builtins de Wine parcheados.
#
#   ./run_hook.sh                 -> parche minimo (triada de aborto)
#   ./run_hook.sh full            -> ademas neutraliza los checks anti-debug/anti-VM
#   ./run_hook.sh ... --dump out.bin   -> ademas vuelca la imagen del proceso
#
# Variable de entorno:
#   WINEPREFIX   prefix de Wine (desechable)
#   WINEDEBUG    por defecto "-all"
set -u
HERE="$(cd "$(dirname "$0")" && pwd)"
PROFILE="${WINEPREFIX:-$HERE/wineprefix}"
BUILTIN="${BUILTIN_OVERRIDE:-$HERE/wine_hooks/builtin}"
EXE="$HERE/wineprefix/drive_c/work/MrGarabato-ByPassEmulator.exe"
MODE="${1:-min}"; shift || true
DUMP=""; [ "${1:-}" = "--dump" ] && DUMP="${2:-}"

export WINEPREFIX="$PROFILE"
export WINEDEBUG="${WINEDEBUG:--all}"
export DISPLAY="${DISPLAY:-}"

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

echo "[*] modo=$MODE  prefix=$PROFILE  builtins=$BUILTIN"
echo "[*] patched:"; python3 - "$BUILTIN" <<'EOF'
import sys, os, pefile
bd = sys.argv[1]
marked = {("kernelbase.dll","ExitProcess"),("user32.dll","MessageBoxW"),
          ("ntdll.dll","NtRaiseHardError"),("ntdll.dll","NtQueryInformationProcess"),
          ("ntdll.dll","RtlUnwindEx"),("ntdll.dll","NtSetInformationThread"),
          ("kernelbase.dll","GetSystemFirmwareTable"),("setupapi.dll","SetupDiGetDeviceRegistryPropertyW"),
          ("advapi32.dll","RegOpenKeyA"),("advapi32.dll","RegGetValueA")}
for dll,fn in sorted(marked):
    p=os.path.join(bd,dll)
    if not os.path.exists(p): continue
    pe=pefile.PE(p,fast_load=True)
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_EXPORT"]])
    for e in getattr(pe,"DIRECTORY_ENTRY_EXPORT",[]).symbols:
        if e.name and e.name.decode(errors="replace")==fn:
            off=pe.get_offset_from_rva(e.address); print(f"      {dll}!{fn} -> {open(p,'rb').read()[off:off+4].hex()}")
            break
EOF

INNER=$(cat <<'EOS'
FAKE="$1"; BUILTIN="$2"; shift 2
for f in "$FAKE"/*; do
  b=$(basename "$f")
  [ -e "/sys/class/dmi/id/$b" ] && mount --bind "$f" "/sys/class/dmi/id/$b" 2>/dev/null
done
# Los builtins PE de Wine se cargan SIEMPRE de /usr/lib/wine/x86_64-windows
# (WINEDLLPATH solo afecta al ntdll.so unix).  Los sustituimos con un
# bind-mount dentro de este namespace: el host no se toca.
mount --bind "$BUILTIN" /usr/lib/wine/x86_64-windows 2>/dev/null \
  && echo "[*] builtins parcheados montados" || echo "[!] bind-mount de builtins FALLO"
echo "[*] sanity: $(md5sum /usr/lib/wine/x86_64-windows/ntdll.dll 2>/dev/null | cut -c1-8)"
exec "$@"
EOS
)

timeout "${RUNTIMEOUT:-60}" unshare -m bash -c "$INNER" _ "$FAKE" "$BUILTIN" \
   wine "$EXE" "$@" > "$HERE/last_run.out" 2> "$HERE/last_run.err"
rc=$?
echo "[*] exit=$rc"
tail -5 "$HERE/last_run.err" 2>/dev/null
exit $rc