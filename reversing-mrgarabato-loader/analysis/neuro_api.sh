#!/usr/bin/env bash
# API Neural del panel MrGarabato -- credencial de cliente, forma validada.
#
# DESCUBIERTO con los mensajes de error del servidor como oraculo: cada campo
# correcto hace avanzar el error al siguiente.
#
#   seller + app    MrGarabato / mrgarabato_freefire  -> "seller/app missing"
#   app_name        MrGarabato-FreeFire               -> "app_name mismatch"
#   app_version     1.0                               -> "Empty"/"Outdated version"
#   owner_id        YX9Y0KWPU6                        -> "owner_id mismatch"
#   app_secret      AuA#&!Y-HKjaz*lGJg                -> "secret mismatch"  (si se manda como "secret")
#
# TRAMPA IMPORTANTE: el campo se llama **app_secret**, NO "secret".
# Enviandolo como "secret" el servidor responde "secret mismatch" indefinidamente,
# aunque el valor sea correcto. Con "app_secret" responde {"ok":true,"message":"OK"}.
#
# Verificado por control negativo:
#   app_version 1.1 / 2.0 / 1 / 0.1  -> "Outdated version"
#   app_name "MrGarabato-Bypass"     -> "app_name mismatch"  (solo la P mayuscula vale)
#   owner_id vacio / otro            -> "owner_id mismatch"
#   secret en vez de app_secret      -> "secret mismatch"
#
# ESTADO: la credencial de aplicacion esta COMPLETA y VALIDADA (neural_check -> OK).
# Falta una cuenta de usuario (username/password) para que neural_login devuelva
# el token y el update_url. El panel no tiene autorregistro.
#
# Uso: neuro_api.sh [usuario] [password]
set -u
USER="${1:-}"; PASS="${2:-}"
python3 - "$USER" "$PASS" > /tmp/neuro_req.json <<'PY'
import json,sys
print(json.dumps({
  "seller":"MrGarabato","app":"mrgarabato_freefire",
  "app_name":"MrGarabato-FreeFire","app_version":"1.0",
  "owner_id":"YX9Y0KWPU6","app_secret":"AuA#&!Y-HKjaz*lGJg",
  "license":"MRGARABATO-9DCF","hwid":"ANALISIS-HWID",
  "username":sys.argv[1],"password":sys.argv[2]}))
PY
for ep in neural_check neural_login; do
  echo "--- $ep ---"
  timeout 40 curl -sk --max-time 35 -X POST "https://panel.mrgarabato.com/Auth/api/$ep.php" \
    -H "Content-Type: application/json" -H "Accept: application/json" \
    -H "User-Agent: NeuralAuth/1.0" -H "X-App-Version: 1.0" \
    --data-binary @/tmp/neuro_req.json 2>/dev/null | python3 -m json.tool 2>/dev/null | head -40
  echo
done
