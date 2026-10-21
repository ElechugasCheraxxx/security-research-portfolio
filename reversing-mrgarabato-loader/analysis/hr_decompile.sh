#!/usr/bin/env bash
# hr_decompile.sh — decompila una dirección con Hex-Rays (cloud) vía la GUI de IDA.
# Uso: ./hr_decompile.sh <DIRECCION_HEX> <etiqueta> [captura_extra]
#
# Contexto: IDA corre bajo Xvfb :99 con openbox. La navegación por teclado
# funciona; el despacho de acciones de IDA falla ("Command JumpEnter failed"),
# por eso el salto se hace con el diálogo "Jump to address" (tecla G).
set -u

export DISPLAY=:99
ADDR="${1:?falta la direccion}"
LABEL="${2:?falta la etiqueta}"
OUT="${3:-/tmp/opencode/hr_${LABEL}.png}"
MAIN=2097168
CONSENT_AT="1049 652"     # boton "Yes" del dialogo de consentimiento cloud
JUMP_OK_AT="865 522"      # boton "OK" del dialogo "Jump to address" (423x70 en 739,475)

win_main() { xdotool search --onlyvisible --name "^IDA - " 2>/dev/null | head -1; }

click_yes() {                 # responde "Yes" si aparece el consentimiento cloud
  local w
  for w in $(xdotool search --onlyvisible --name "Please confirm" 2>/dev/null); do
    xdotool windowactivate --sync "$w" 2>/dev/null || true
    sleep 0.3
    xdotool mousemove $CONSENT_AT; sleep 0.3; xdotool click 1
    echo "  [consent cloud] aceptado"
    sleep 2
    return 0
  done
  return 1
}

MAIN=$(win_main)
[ -z "$MAIN" ] && { echo "ERROR: IDA no esta abierta"; exit 1; }

echo "== $LABEL @ $ADDR =="
xdotool windowactivate --sync "$MAIN" 2>/dev/null; sleep 0.6

# 1) Salto a la direccion: G -> dialogo -> escribir -> Enter
xdotool key --clearmodifiers g; sleep 1.5
DLG=$(xdotool search --onlyvisible --name "Jump to address" 2>/dev/null | head -1)
if [ -z "$DLG" ]; then
  echo "  [aviso] no aparecio el dialogo de salto; sigo en la vista actual"
else
  xdotool windowactivate --sync "$DLG" 2>/dev/null; sleep 0.4
  xdotool key --clearmodifiers ctrl+a; sleep 0.2
  xdotool type --delay 40 "$ADDR"; sleep 0.6
  # Return no cierra este dialogo; hay que pulsar OK con el raton.
  # La posicion del dialogo cambia entre invocaciones: se calcula.
  eval "$(xdotool getwindowgeometry "$DLG" 2>/dev/null | awk '
    /Position:/ {split($2,p,","); x=p[1]; y=p[2]}
    /Geometry:/ {split($2,g,"x"); w=g[1]; h=g[2]}
    END {printf "JX=%d JY=%d\n", x+int(w*0.30), y+int(h*0.68)}')"
  xdotool mousemove "$JX" "$JY"; sleep 0.3; xdotool click 1; sleep 1.5
fi

# 2) Decompilar
xdotool key --clearmodifiers F5; sleep 3
click_yes || true
sleep 6

# 3) Captura
import -window root "$OUT" 2>/dev/null
echo "  captura: $OUT ($(stat -c%s "$OUT" 2>/dev/null || echo 0) B)"

# 4) Estado
for w in $(xdotool search --onlyvisible --name "." 2>/dev/null); do
  echo "  win $w: '$(xdotool getwindowname "$w" 2>/dev/null)'"
done