#!/usr/bin/env python3
"""Parchea funciones exportadas de las DLL builtin de Wine (copia local).

El sample resuelve APIs por hash FNV-1a sobre los exports del PEB, asi que
un shim con WINEDLLOVERRIDES no sirve (el kernel32 de Wineloadena el primero
en InLoadOrderModuleList). Lo que si funciona es parchear la implementacion
real de la builtin: el hash resuelva al mismo codigo que estamos parcheando.

Uso:  wine_patch.py <builtin_dir> [nombre_funcion=dll:byteshex] ...
"""
import sys, os, pefile

# stubs x86-64 (Win64: rcx,rdx,r8,r9 -> rax)
STUBS = {
    # nombre: (dll, bytes)
    "ExitProcess":        ("kernelbase.dll", bytes.fromhex("31c0c3")),                  # xor eax,eax; ret
    "TerminateProcess":   ("kernelbase.dll", bytes.fromhex("31c0c3")),                  # xor eax,eax; ret
    "FatalAppExitA":      ("kernelbase.dll", bytes.fromhex("31c0c3")),
    "MessageBoxW":        ("user32.dll",    bytes.fromhex("b801000000c3")),            # mov eax,1(IDOK); ret
    "MessageBoxA":        ("user32.dll",    bytes.fromhex("b801000000c3")),
    "MessageBoxExW":      ("user32.dll",    bytes.fromhex("b801000000c3")),
    # ntdll: STATUS_SUCCESS y buffer de salida (r8) a cero
    "NtRaiseHardError":   ("ntdll.dll",     bytes.fromhex("31c04d85c07402498900c3")),    # *r8=0; return 0
    "NtQueryInformationProcess":
                          ("ntdll.dll",     bytes.fromhex("31c04d85c07402498900c3")),    # *r8=0; return 0
    "NtSetInformationThread":
                          ("ntdll.dll",     bytes.fromhex("31c0c3")),                  # no-op, return 0
    "NtSetInformationProcess":
                          ("ntdll.dll",     bytes.fromhex("31c0c3")),
    "RtlUnwindEx":        ("ntdll.dll",     bytes.fromhex("31c0c3")),                  # ExceptionContinueExecution
    "NtRaiseException":   ("ntdll.dll",     bytes.fromhex("31c0c3")),
    # Win32 con buffer de salida en 2o argumento (rdx)
    "CheckRemoteDebuggerPresent":
                          ("kernelbase.dll",bytes.fromhex("31c04885d274028902c3")),
    "GetThreadContext":   ("kernelbase.dll",bytes.fromhex("31c04885d274028902c3")),
    "SetupDiGetDeviceRegistryPropertyW":
                          ("setupapi.dll",  bytes.fromhex("31c04885d274028902c3")),
    "DeviceIoControl":    ("kernelbase.dll",bytes.fromhex("31c04885d274028902c3")),
    "GetAdaptersInfo":    ("iphlpapi.dll",  bytes.fromhex("31c04885d274028902c3")),
    "IsDebuggerPresent":  ("kernelbase.dll",bytes.fromhex("31c0c3")),
    "OutputDebugStringA": ("kernelbase.dll",bytes.fromhex("31c0c3")),
    "GetSystemFirmwareTable":
                          ("kernelbase.dll",bytes.fromhex("31c0c3")),                  # SMBIOS vacio
    "RegOpenKeyA":        ("advapi32.dll",  bytes.fromhex("b802000000c3")),            # ERROR_FILE_NOT_FOUND
    "RegGetValueA":       ("advapi32.dll",  bytes.fromhex("b802000000c3")),
    "RegOpenKeyW":        ("advapi32.dll",  bytes.fromhex("b802000000c3")),
    "RegGetValueW":       ("advapi32.dll",  bytes.fromhex("b802000000c3")),
}


def _exports(path):
    pe = pefile.PE(path, fast_load=True)
    pe.parse_data_directories(
        directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_EXPORT"]])
    return pe, {e.name.decode(errors="replace"): e
                for e in getattr(pe, "DIRECTORY_ENTRY_EXPORT", []).symbols if e.name}


def resolve(builtin_dir, dll, name, _depth=0):
    """Sigue la cadena de forwarders hasta la funcion real que hay que
    parchear. En Wine, ExitProcess etc. son forwarders a ntdll!RtlExitUserProcess."""
    path = os.path.join(builtin_dir, dll)
    if not os.path.exists(path):
        return None, f"no existe {path}"
    if _depth > 8:
        return None, "cadena de forwarders demasiado larga"
    pe, exp = _exports(path)
    e = exp.get(name)
    if e is None:
        return None, f"export {name} no encontrado en {dll}"
    if getattr(e, "forwarder", None):
        fwd = e.forwarder.decode() if isinstance(e.forwarder, bytes) else e.forwarder
        fdll, _, fname = fwd.partition(".")
        if not fname:                       # reenvio por ordinal
            fdll, fname = "ntdll.dll", None
        if not fdll.endswith(".dll"):
            fdll += ".dll"
        res, err = resolve(builtin_dir, fdll.lower(), fname, _depth + 1)
        chain = f"{dll}!{name} --forward--> {fwd}"
        return (res, chain + (err or "")) if res else (None, chain + " :: " + str(err))
    return (path, pe, e), None


def patch(builtin_dir, name, dll=None, stub=None):
    if dll is not None and stub is not None:
        code = bytes.fromhex(stub)
    else:
        dll, code = STUBS[name]
    res, info = resolve(builtin_dir, dll, name)
    if not res:
        print(f"  [!] {dll}!{name}: {info}")
        return False
    path, pe, hit = res
    rva = hit.address
    off = pe.get_offset_from_rva(rva)
    with open(path, "r+b") as f:
        f.seek(off); old = f.read(len(code))
        f.seek(off); f.write(code)
    msg = (f"  [+] {dll}!{name} @ RVA 0x{rva:X} (file 0x{off:X}) "
           f"{old.hex()} -> {code.hex()}")
    if info:
        msg += "\n        " + info
    print(msg)
    return True


if __name__ == "__main__":
    bd = sys.argv[1]
    args = sys.argv[2:] or ["ExitProcess", "MessageBoxW", "NtRaiseHardError",
                            "NtQueryInformationProcess", "RtlUnwindEx"]
    ok = True
    for a in args:
        # sintaxis explicita:  dll.so!Funcion:hexbytes
        m = a.split("!")
        if len(m) == 2:
            dll, rest = m[0], m[1]
            fname, _, hexs = rest.partition(":")
            ok &= patch(bd, fname, dll, hexs)
        else:
            ok &= patch(bd, a)
    sys.exit(0 if ok else 1)