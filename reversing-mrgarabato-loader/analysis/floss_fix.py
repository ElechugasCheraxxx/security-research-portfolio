#!/usr/bin/env python3
"""Wrapper para arrancar FLOSS en este entorno.

FLOSS 3.1.1 -> vivisect 1.3.2 -> vdb 1.3.2.  El paquete `vdb` instalado trae
un `vtrace/__init__.py` recortado que ya no reexporta `Notifier`, pero
`vtrace/platforms/base.py` sigue haciendo `class TracerBase(vtrace.Notifier)`.
Ademas hace falta vstruct 1.x (con `vstruct.cparse`) en lugar del 2.x que hay
instalado en el sistema.

Este script hace el parche en memoria (no toca site-packages) y luego delega en
floss.main.main.
"""
import sys


def _patch_vtrace():
    import vtrace
    import vtrace.notifiers as notifiers
    for name in dir(notifiers):
        if not hasattr(vtrace, name):
            setattr(vtrace, name, getattr(notifiers, name))


def _fix_vstruct():
    """vstruct 2.x se registra como `vstruct` sin `cparse`/`constants`.  Si esta
    la version 1.x (instalada en el venv) no hace falta nada."""
    try:
        import vstruct.cparse  # noqa
    except ImportError:
        import vstruct
        raise SystemExit(
            "ERROR: falta vstruct 1.x (con vstruct.cparse).  Instalar en el venv:\n"
            "  pip install git+https://github.com/williballenthin/vivisect-vstruct.git@v1.0.3\n"
            "  y copiar vstruct/constants y vstruct/defs dentro del venv."
        )


if __name__ == "__main__":
    _patch_vtrace()
    from floss.main import main
    sys.exit(main())