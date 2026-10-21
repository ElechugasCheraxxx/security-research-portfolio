#!/usr/bin/env bash
# hexrays_dump.sh — extrae pseudocode de Hex-Rays (cloud) como TEXTO exacto.
#
# Por qué texto y no capturas: la vista Pseudocode de IDA permite Ctrl+A / Ctrl+C,
# y el portapapeles X devuelve el pseudocode literal. Una captura obliga a leer
# la imagen y se pierde texto; el portapapeles no.
#
# Uso:  ./hexrays_dump.sh <DIRECCION_HEX> <etiqueta> [directorio_salida]
# Env:  DISPLAY (:99 por defecto), MAIN (id de la ventana principal de IDA)
set -u

export DISPLAY="${DISPLAY:-:99}"
ADDR="${1:?falta la direccion}"
LABEL="${2:?falta la etiqueta}"
OUTDIR="${3:-/root/mrgarabato_analysis/run/hexrays}"
mkdir -p "$OUTDIR"
TXT="$OUTDIR/${LABEL}_${ADDR}.c"
PNG="/tmp/opencode/hrx_${LABEL}_${ADDR}.png"

CONSENT_X=1049; CONSENT_Y=652      # "Yes" del consentimiento del decompilador cloud

main_win() { xdotool search --onlyvisible --name "^IDA - " 2>/dev/null | head -1; }
click_ok_of() {                     # posicion del boton OK segun la geometria real
  eval "$(xdotool getwindowgeometry "$1" 2>/dev/null | awk '
    /Position:/ {split($2,p,","); x=p[1]; y=p[2]}
    /Geometry:/ {split($2,g,"x"); w=g[1]; h=g[2]}
    END {printf "JX=%d JY=%d\n", x+int(w*0.30), y+int(h*0.68)}')"
  echo "$JX $JY"
}

MAIN="${MAIN:-$(main_win)}"
[ -z "$MAIN" ] && { echo "ERROR: IDA no esta abierta en $DISPLAY"; exit 1; }

# --- 1) saltar a la direccion (G -> dialogo -> OK con raton) ---
xdotool windowactivate --sync "$MAIN" 2>/dev/null; sleep 0.6
xdotool key --clearmodifiers g; sleep 1.5
DLG=$(xdotool search --onlyvisible --name "Jump to address" 2>/dev/null | head -1)
if [ -n "$DLG" ]; then
  xdotool windowactivate --sync "$DLG" 2>/dev/null; sleep 0.4
  xdotool key --clearmodifiers ctrl+a; sleep 0.2
  xdotool type --delay 40 "$ADDR"; sleep 0.6
  read -r JX JY <<< "$(click_ok_of "$DLG")"
  xdotool mousemove "$JX" "$JY"; sleep 0.3; xdotool click 1; sleep 1.5
fi

# --- 2) decompilar (F5) y liquidar dialogos ---
xdotool windowactivate --sync "$MAIN" 2>/dev/null; sleep 0.4
xdotool key --clearmodifiers F5; sleep 3
C=$(xdotool search --onlyvisible --name "Please confirm" 2>/dev/null | head -1)
[ -n "$C" ] && { xdotool windowactivate --sync "$C" 2>/dev/null; sleep 0.3
                 xdotool mousemove $CONSENT_X $CONSENT_Y; sleep 0.3; xdotool click 1; }
I=$(xdotool search --onlyvisible --name "Information" 2>/dev/null | head -1)
[ -n "$I" ] && { xdotool windowactivate --sync "$I" 2>/dev/null; sleep 0.3
                 xdotool key --window "$I" Return; }
sleep 7

# --- 3) copiar el pseudocode del portapapeles ---
xdotool windowactivate --sync "$MAIN" 2>/dev/null; sleep 0.6
xdotool mousemove 1100 400; sleep 0.3; xdotool click 1; sleep 0.8
xdotool key --clearmodifiers ctrl+a; sleep 0.8
xdotool key --clearmodifiers ctrl+c; sleep 1.5
xsel -b -o > "$TXT" 2>/dev/null
import -window root "$PNG" 2>/dev/null

N=$(wc -c < "$TXT")
printf '%-28s %-10s %6s B  %s\n' "$LABEL" "$ADDR" "$N" "$TXT"
[ "$N" -lt 40 ] && { echo "   [aviso] pseudocode vacio o demasiado corto"; exit 2; }
exit 0