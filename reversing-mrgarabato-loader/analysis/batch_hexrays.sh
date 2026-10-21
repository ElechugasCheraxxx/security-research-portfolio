#!/usr/bin/env bash
# batch_hexrays.sh — extrae en lote el pseudocode de Hex-Rays para una lista de
# direcciones. Registra progreso en un log y salta las ya extraidas.
#
# Uso: ./batch_hexrays.sh <fichero_de_direcciones> [etiqueta_prefijo]
set -u
export DISPLAY="${DISPLAY:-:99}"

LIST="${1:?falta la lista de direcciones}"
PREFIX="${2:-FN}"
HERE="$(cd "$(dirname "$0")" && pwd)"
LOG="$HERE/hexrays/batch_${PREFIX}.log"
: > "$LOG"

total=0; ok=0; fail=0; skip=0
while read -r raw; do
  a=$(echo "$raw" | tr 'A-F' 'a-f' | sed 's/^0x0*/0x/')
  [ -z "$a" ] && continue
  case "$a" in 0x*) ;; *) continue;; esac
  total=$((total+1))
  if ls "$HERE"/hexrays/*_"$a".c >/dev/null 2>&1; then
    skip=$((skip+1)); echo "[$total] SKIP $a (ya existe)" >> "$LOG"; continue
  fi
  name="${PREFIX}_$(printf '%s' "$a" | tr -d '0x')"
  out=$(timeout 200 "$HERE/hexrays_dump.sh" "$a" "$name" 2>&1 | tail -1)
  if echo "$out" | grep -qE '\.c$'; then
    ok=$((ok+1)); echo "[$total] OK   $a  -> $(basename "${out##* }")" >> "$LOG"
  else
    fail=$((fail+1)); echo "[$total] FAIL $a  ($out)" >> "$LOG"
  fi
  echo "$out"
done < "$LIST"

{
  echo "──────────────────────────────────────────"
  echo "total=$total  ok=$ok  fail=$fail  skip=$skip"
} >> "$LOG"
echo "LOTE COMPLETO: total=$total ok=$ok fail=$fail skip=$skip"