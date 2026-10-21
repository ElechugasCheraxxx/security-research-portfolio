#!/usr/bin/env python3
"""Recorrido dinamico de los sub-identificadores del IOCTL 0x80862007.

Para cada FunctionId se despacha un IRP_MJ_DEVICE_CONTROL real a traves del
MajorFunction[14] que el propio driver registro durante DriverEntry, y se registra
que APIs de ntoskrnl invoca y desde que RVA del driver. Ese RVA del llamante es la
"hoja" que consume ese sub-identificador.

Herramienta: speakeasy-emulator 1.6.1 (Mandiant), venv /tmp/opencode/speakeasy2.
"""
import re
import sys
import speakeasy


import os
DRIVER = os.path.abspath(os.path.join(os.path.dirname(__file__), "c2_descargas/payload_embebido.exe"))
IMGBASE = 0x10000
HANDLER_RVA = 0x1150
HANDLER_VA = IMGBASE + HANDLER_RVA
IRP_MJ_DEVICE_CONTROL = 14

SUBIDS = {
    0x80862007: list(range(1, 60)),      # handler 0x13C0 : 59 FunctionIds
    0x8086200F: list(range(1, 4)),       # handler 0x1330 : 3
    0x80862013: list(range(1, 9)),       # handler 0x3FA0 : 8
    0x8086200B: list(range(1, 8)),       # handler 0x1A60 : 7
}

trace = []        # RVAs del driver ejecutados en el dispatch actual


class Rec:
    def __init__(self):
        self.lines = []

    def info(self, m, *a):
        self.lines.append(str(m) % a if a else str(m))

    debug = error = warning = info

    def take(self):
        o = self.lines
        self.lines = []
        return o


def main():
    log = Rec()
    se = speakeasy.Speakeasy(logger=log)
    print("cargando driver con speakeasy-emulator ...")
    mod = se.load_module(path=DRIVER)
    print("  base VA 0x%x" % mod.get_base())
    se.run_module(mod)
    emu = se.emu
    log.take()

    # ---- localizar el DeviceObject de \Device\Nal -------------------------
    dev = None
    for getter in ("get_device_object", "get_dev_by_name", "get_dev_by_addr"):
        fn = getattr(emu, getter, None)
        if not fn:
            continue
        for nm in ("\\Device\\Nal", "Nal", "\\??\\Nal"):
            try:
                d = fn(nm)
                if d is not None:
                    dev = d
                    break
            except Exception:
                pass
        if dev:
            break
    if dev is None:
        for attr in dir(emu):
            if "dev" in attr.lower() and isinstance(getattr(emu, attr, None), (dict, list)):
                coll = getattr(emu, attr)
                try:
                    items = coll.items() if isinstance(coll, dict) else enumerate(coll)
                except Exception:
                    continue
                for _, o in items:
                    if "Nal" in str(getattr(o, "name", "")):
                        dev = o
                        break
            if dev:
                break
    if dev is None:
        # Fallback: el DeviceObject vive en una direccion fija del pool de
        # speakeasy (seccion kernel,observed 0x7f9000 en la traza de descarga).
        dev = type("D", (), {"address": 0x7F9000, "name": "\\Device\\Nal"})()
    print("  DeviceObject -> 0x%x" % dev.address)

    # ---- hook de APIs para saber que llama el driver y desde donde ---------
    # code hook sobre toda la imagen del driver: registro de direcciones
    # ejecutadas. Es independiente del mecanismo de API de speakeasy.
    def code_hook(emu_, addr, size, ctx):
        rva = addr - IMGBASE
        if 0x1000 <= rva < 0x5620:
            trace.append(rva)

    se.add_code_hook(code_hook, begin=IMGBASE + 0x1000, end=IMGBASE + 0x5615)

    results = {}
    print("\n%-10s %-5s %-11s %s" % ("IOCTL", "Fid", "instrucciones", "ruta (RVA)"))
    print("-" * 86)

    # reservar memoria real para el búfer de usuario
    UBUF = None
    for meth, args in (("mem_alloc", (0x1000,)), ("mem_map", (0x1000,)),
                       ("mem_reserve", (0x1000,))):
        fn = getattr(emu, meth, None)
        if fn:
            try:
                UBUF = fn(*args)
                break
            except Exception:
                UBUF = None
    if UBUF is None:
        try:
            UBUF = emu.pool_alloc(emu.get_pool_type(0), 0x1000, "user")
        except Exception:
            UBUF = 0x7F9000 + 0x40000
    print("  búfer de usuario en 0x%x" % UBUF)
    for ioctl in sorted(SUBIDS):
        for fid in SUBIDS[ioctl]:
            results.setdefault("0x%08X" % ioctl, {})[fid] = []
            cur = (ioctl, fid)
            trace.clear()
            irp = emu.new_irp()
            ios = irp.get_curr_stack_loc()
            ios.object.MajorFunction = IRP_MJ_DEVICE_CONTROL
            dio = ios.object.Parameters.DeviceIoControl
            dio.IoControlCode = ioctl
            dio.InputBufferLength = 0x40
            dio.OutputBufferLength = 0x40
            # búfer de entrada del usuario con el FunctionId al principio
            emu.mem_write(UBUF, fid.to_bytes(4, "little") + b"\x00" * 0x3C)
            for attr, val in (("Type3InputBuffer", UBUF),
                              ("Type3InputBufferLength", 0x40),
                              ("UserBuffer", UBUF),
                              ("OutputBufferLength", 0x40)):
                try:
                    setattr(dio, attr, val)
                except Exception:
                    pass
            ios.write_back()
            irp.write_back()

            # El handler exige  [IRP+0xB8] -> contexto, y que contexto+0x20
            # sea != NULL; contexto+0x18 es donde lee el IoControlCode.
            # speakeasy no rellena ese puntero, asi que lo montamos nosotros.
            try:
                ctx = emu.mem_alloc(0x200)
            except Exception:
                ctx = UBUF + 0x100
            emu.mem_write(ctx, b"\x00" * 0x200)
            emu.mem_write(ctx + 0x18, ioctl.to_bytes(4, "little"))
            emu.mem_write(ctx + 0x20, (UBUF).to_bytes(8, "little"))
            emu.mem_write(ctx + 0x28, dev.address.to_bytes(8, "little"))
            emu.mem_write(irp.address + 0xB8, ctx.to_bytes(8, "little"))

            try:
                se.call(HANDLER_VA, [dev.address, irp.address])
            except Exception as ex:
                print("  0x%08X fid=%-3d ERROR: %s" % (ioctl, fid, type(ex).__name__))
                continue

            if not trace:
                print("  0x%08X %-5d %-9s (NO se ejecuto codigo del driver)" % (ioctl, fid, "-"))
                continue
            uniq = []
            for r in trace:
                if r not in uniq:
                    uniq.append(r)
            reached = [r for r in uniq if r not in (0x1150, 0x1154, 0x115b, 0x1160,
                                                     0x1165, 0x1169, 0x116c, 0x116f,
                                                     0x1172, 0x1174, 0x117a, 0x117c,
                                                     0x1182, 0x1184, 0x118a, 0x118c,
                                                     0x1192, 0x119b, 0x11a0, 0x11a5)]
            deep = [r for r in reached if r >= 0x1400 and r not in (0x11de, 0x11e1, 0x11e9,
                                                                     0x11ec, 0x11f2, 0x11f7,
                                                                     0x11f9, 0x11fe, 0x1202)]
            tag = ("-> deepest 0x%x" % deep[-1]) if deep else ("solo prologo")
            print("  0x%08X %-5d %d instr  %-22s %s"
                  % (ioctl, fid, len(trace), tag, " ".join("0x%x" % r for r in deep[:7])))

    import json
    json.dump(results, open("subids_dinamico.json", "w"), indent=1)
    print("\nregistro completo -> subids_dinamico.json")
    return 0


if __name__ == "__main__":
    sys.exit(main())