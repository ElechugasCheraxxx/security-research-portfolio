#!/usr/bin/env python3
"""
decrypt_stack_strings.py -- Descifra las cadenas que el loader esconde en pila.

Mecanismo detectado en el .text desempaquetado:

    mov  dword [rbp+X], <const>     ; bytes cifrados
    ...
    mov  rcx, 0                     (via xor ebx,ebx / mov ecx,ebx)
    loop:
      lea  eax, [rcx - 0x6d]        ; 8D 41 93
      xor  byte [rbp+rcx+X], al     ; 30 44 0D XX
      inc  rcx                      ; 48 FF C1
      cmp  rcx, N
      jb   loop

La clave es i-0x6d, i.e. XOR con (i + 0x93) & 0xff.

Se escanea el .text buscando el patron del bucle, se rastrea hacia atras
hasta 400 bytes las escrituras de constantes al mismo buffer y se descifra.

Uso: decrypt_stack_strings.py <dump_text.bin> <salida.txt>
"""
import re, sys, struct

KEY_DELTA = -0x6d

# lea eax,[rcx-0x6d] ; xor byte [rbp+rcx+disp8], al
LOOP = re.compile(rb'\x8d\x41\x93\x30\x44\x0d(.)', re.S)
# lea eax,[rcx-0x6d] ; xor byte [rsp+rcx+disp8], al   (30 44 0c .)
LOOP_RSP = re.compile(rb'\x8d\x41\x93\x30\x44\x0c(.)', re.S)


def build_reg_map(text, start, base_reg, disp, nbytes):
    """Rastrea hacia atras las escrituras de constantes a [base+disp..+nbytes].

    Reconstruye el buffer cifrado mirando mov dword/word/byte inmediato.
    Devuelve una lista de (offset_text, valor) o None si no encuentra nada.
    """
    buf = bytearray(b'\x00' * nbytes)
    filled = [False] * nbytes
    lo = max(0, start - 500)
    chunk = text[lo:start]
    # mov dword [rbp+disp32/8], imm32 : C7 85 disp32 imm32  |  C7 45 disp8 imm32
    for m in re.finditer(rb'\xc7(?:\x85(.{4})|\x45(.))(.{4})', chunk, re.S):
        d = struct.unpack('<i', m.group(1))[0] if m.group(1) else struct.unpack('<b', m.group(2))[0]
        imm = m.group(3)
        o = m.start() + lo
        if base_reg == 'rbp' and d == disp:
            for k in range(4):
                if k < nbytes:
                    buf[k] = imm[k]; filled[k] = True
    # mov word : 66 C7 85 disp32 imm16 | 66 C7 45 disp8 imm16
    for m in re.finditer(rb'\x66\xc7(?:\x85(.{4})|\x45(.))(.{2})', chunk, re.S):
        d = struct.unpack('<i', m.group(1))[0] if m.group(1) else struct.unpack('<b', m.group(2))[0]
        imm = m.group(3)
        if base_reg == 'rbp' and d == disp:
            for k in range(2):
                if k < nbytes:
                    buf[k] = imm[k]; filled[k] = True
    # mov byte : C6 85 disp32 imm8 | C6 45 disp8 imm8
    for m in re.finditer(rb'\xc6(?:\x85(.{4})|\x45(.))(.)', chunk, re.S):
        d = struct.unpack('<i', m.group(1))[0] if m.group(1) else struct.unpack('<b', m.group(2))[0]
        if base_reg == 'rbp' and d == disp and nbytes > 0:
            buf[0] = m.group(3)[0]; filled[0] = True
    return bytes(buf), filled


def main():
    text = open(sys.argv[1], 'rb').read()      # dump que empieza en RVA 0x1000
    out = open(sys.argv[2], 'w', encoding='utf-8', errors='replace')

    results = {}
    for m in LOOP.finditer(text):
        disp8 = struct.unpack('<b', m.group(1))[0]
        base = 'rbp'
        pos = m.start()
        # N esta en el cmp rcx,N que sigue al bucle: buscar 48 83 F9 XX / 48 81 F9
        tail = text[pos:pos + 40]
        n = None
        mm = re.search(rb'\x48\x83\xf9(.)\x0f\x82', tail, re.S) or \
             re.search(rb'\x48\x83\xf9(.)\x72', tail, re.S)
        if mm:
            n = mm.group(1)[0]
        else:
            mm = re.search(rb'\x48\x81\xf9(....)', tail, re.S)
            if mm:
                n = struct.unpack('<I', mm.group(1))[0]
        if not n or n > 4096:
            continue
        buf, filled = build_reg_map(text, pos, base, disp8, n)
        dec = bytes((b ^ ((i + 0x93) & 0xff)) for i, b in enumerate(buf))
        results[pos] = dec

    for m in LOOP_RSP.finditer(text):
        disp8 = struct.unpack('<b', m.group(1))[0]
        pos = m.start()
        tail = text[pos:pos + 40]
        n = None
        mm = re.search(rb'\x48\x83\xf9(.)\x0f\x82', tail, re.S) or \
             re.search(rb'\x48\x83\xf9(.)\x72', tail, re.S)
        if mm:
            n = mm.group(1)[0]
        if not n or n > 4096:
            continue
        buf = bytearray(b'\x00' * n)
        lo = max(0, pos - 500)
        chunk = text[lo:pos]
        for mm2 in re.finditer(rb'\xc7(?:\x84(.{4})|\x44(.))(.{4})', chunk, re.S):
            d = struct.unpack('<i', mm2.group(1))[0] if mm2.group(1) else struct.unpack('<b', mm2.group(2))[0]
            imm = mm2.group(3)
            if d == disp8:
                for k in range(4):
                    if k < n:
                        buf[k] = imm[k]
        for mm2 in re.finditer(rb'\x66\xc7(?:\x84(.{4})|\x44(.))(.{2})', chunk, re.S):
            d = struct.unpack('<i', mm2.group(1))[0] if mm2.group(1) else struct.unpack('<b', mm2.group(2))[0]
            if d == disp8:
                for k in range(2):
                    if k < n:
                        buf[k] = mm2.group(3)[k]
        dec = bytes((b ^ ((i + 0x93) & 0xff)) for i, b in enumerate(buf))
        results[pos] = dec

    printable = lambda s: sum(1 for c in s if 32 <= c < 127) / max(1, len(s))
    good = 0
    for pos in sorted(results):
        dec = results[pos].rstrip(b'\x00')
        if len(dec) < 3:
            continue
        if printable(dec) < 0.85:
            continue
        try:
            s = dec.decode('ascii')
        except Exception:
            continue
        out.write("0x%06X  %r\n" % (pos + 0x1000, s))
        good += 1
    out.close()
    print("[+] %d cadenas descifradas -> %s" % (good, sys.argv[2]))
    return 0


if __name__ == '__main__':
    sys.exit(main())
