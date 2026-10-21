"""Shim de compatibilidad: cle 9.2.160 (Arch) no exporta PEStubs, que angr
9.2.194 usa en dos isinstance() para modelar stubs de API de Windows.
No modifica ningun paquete: solo inyecta el simbolo antes de importar angr."""
import logging
for _n in ("angr", "cle", "pyvex", "claripy", "cffi"):
    logging.getLogger(_n).setLevel(logging.ERROR)

import cle
import cle.backends
import cle.backends.pe.pe as _pe


class PEStubs:
    """Marcador para objetos 'PE stubs' de cle. No usado en analisis CFG."""
    def __init__(self, *a, **k):
        self.args = a


_pe.PEStubs = PEStubs
cle.backends.PEStubs = PEStubs
cle.PEStubs = PEStubs


def load(path="unpacked_bypass.exe", **kw):
    import angr
    return angr.Project(path, auto_load_libs=False, **kw)


if __name__ == "__main__":
    import sys
    p = load(sys.argv[1] if len(sys.argv) > 1 else "unpacked_bypass.exe")
    print("angr PROYECTO CARGADO")
    print("  entry = 0x%x" % p.entry)
    print("  base  = 0x%x" % p.loader.main_object.mapped_base)
    print("  rango = 0x%x .. 0x%x" % (p.loader.min_addr, p.loader.max_addr))
    print("  secciones:", [s.name for s in p.loader.main_object.sections])