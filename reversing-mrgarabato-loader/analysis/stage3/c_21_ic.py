#!/usr/bin/env python3
"""
c_21_ic.py -- Test decisivo: indice de coincidencia (IC).
Una sustitucion monoalfabetica conserva el IC del texto plano.
  IC ~ 0.065-0.070  => texto (ingles/espanol) bajo sustitucion
  IC ~ 1/k          => plano distribuido como el alfabeto de la S-box
Ademas: examen de Kasiski (n-gramas repetidos) y esquema de palabras.
"""
import numpy as np, collections, math, random

RUN = "/root/mrgarabato_analysis/run/"
raw = open(RUN+"stage3/wine__w7.bin","rb").read()
B1 = raw[0x227A0:0x22840]
B2 = raw[0x22A50:0x22BE0]

def ic(b):
    n=len(b); c=collections.Counter(b)
    if n<2: return 0.0
    return sum(v*(v-1) for v in c.values())/(n*(n-1))

def ic_mean(b, trials=4000):
    ks = len(set(b))
    r = [ic(bytes(random.randrange(256) for _ in range(len(b)))) for _ in range(200)]
    return sum(r)/len(r)

print("="*78); print("A. INDICE DE COINCIDENCIA"); print("="*78)
print(f"{'dato':28s} {'n':>5s} {'distintos':>9s} {'IC':>8s}")
for nm, b in (("BLOB1 (160)", B1), ("BLOB2 (400)", B2),
              ("BLOB1 pares", B1[0::2]), ("BLOB1 impares", B1[1::2])):
    print(f"{nm:28s} {len(b):5d} {len(set(b)):9d} {ic(b):8.4f}")
print(f"{'texto ingles (ref)':28s} {160:5d} {'~50':>9s} {ic(b'The quick brown fox jumps over the lazy dog. Pack my box with five dozen liquor jugs. '*2):8.4f}")
print(f"{'random 0..255 (ref)':28s} {160:5d} {len(set(random.randrange(256) for _ in range(160))):9d} {ic(bytes(random.randrange(256) for _ in range(160))):8.4f}")
# referencia: distribucion sobre 52 simbolos aleatorios
r=[ic(bytes(random.randrange(52) for _ in range(160))) for _ in range(400)]
print(f"{'random sobre 52 simbolos':28s} {160:5d} {52:9d} {sum(r)/len(r):8.4f}")

print("\n"+"="*78); print("B. EXAMEN DE KASISKI: n-gramas repetidos (indicio de cifrado por grupos)"); print("="*78)
for n in (2,3,4):
    seen = collections.defaultdict(list)
    for i in range(len(B1)-n+1):
        seen[B1[i:i+n]].append(i)
    rep = {k:v for k,v in seen.items() if len(v)>1}
    print(f"  {n}-gramas de BLOB1 repetidos: {len(rep)}")
    for k,v in list(rep.items())[:10]:
        dists=[v[i+1]-v[i] for i in range(len(v)-1)]
        print(f"    {k.hex()} en {v}  gaps={dists}")

print("\n  ¿repite algun bloque de 16 bytes completo?")
blocks = collections.Counter(B1[i:i+16] for i in range(0,160,16))
for k,v in blocks.items():
    if v>1: print(f"    {k.hex()} x{v}")
print("    (f8==f9 es el unico caso)")

print("\n"+"="*78); print("C. SOLVER DE SUSTITUCION MONOALFABETICA (hill climbing, ingles)"); print("="*78)
# Si BLOB1 = sustitucion de un texto, probamos todas las asignaciones por hill-climbing
# sobre n-gramas de un modelo de referencia.
import string
ENG = np.array([8.167,1.492,2.782,4.253,12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,
                2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,
                1.974,0.074,6.0,2.0,0.5])  # a-z + espacio + , .
ALPH = string.ascii_lowercase + " ,."
logf = np.log(np.concatenate([ENG/100, [0.004]]))
# bigramas aproximados (26x26) a partir de un corpus sintetico
def build_bi():
    # matriz de bigramas ingleses normalizada (suficiente para hill climbing)
    import textwrap
    txt = ("the of and to a in that is was he for it with as his on be at by not this had but "
           "from they she which or an were her all we there been has when who will more no if out "
           "so said what up its about into than them can only other new some could time these two "
           "may then do first any my now such like our over man me even most made after also did "
           "many before must through back years where much your way well down should because each "
           "just those people mr how too little state good very make world still own see men work "
           "long get here between both life being under never day same another know while last "
           "might us great old year off come since against go came right used take three states "
           "himself few house use during without again place american around however home small "
           "found thought went say part once general high upon school every don does got united "
           "left number course war until always away something fact though water less public put "
           "think almost hand enough far took head yet government system better set told nothing "
           "night end why called didnt eyes find going look asked later knew point next city "
           "business give group toward young days let room president side social four whether "
           "called upon hard five begin once white "")
    x = np.full((27,27), 1e-6)
    for a,b in zip(txt, txt[1:]):
        if a in ALPH and b in ALPH:
            x[ALPH.index(a), ALPH.index(b)] += 1
    x /= x.sum(1, keepdims=True)
    return np.log(x)
LOGBI = build_bi()

cipher_syms = sorted(set(B1))
print(f"  simbolos distintos en BLOB1: {len(cipher_syms)}")
mapping = {s: i for i, s in enumerate(cipher_syms)}

def score(perm):  # perm: lista len(cipher_syms) -> indice en ALPH
    idx = [perm[mapping[s]] for s in B1]
    tot = 0.0
    for i in range(len(idx)-1):
        tot += LOGBI[idx[i], idx[i+1]]
    return tot

best_overall = None
random.seed(1234)
for restart in range(60):
    # inicializacion por frecuencia inversa
    cnt = collections.Counter(B1)
    order = [s for s,_ in cnt.most_common()]
    perm = list(np.random.permutation(len(ALPH))[:len(cipher_syms)])
    cur = score(perm); improved=True
    while improved:
        improved=False
        for i in range(len(perm)):
            for j in range(len(perm)):
                if i==j: continue
                perm[i],perm[j]=perm[j],perm[i]
                v=score(perm)
                if v>cur: cur=v; improved=True
                else: perm[i],perm[j]=perm[j],perm[i]
    txt = "".join(ALPH[perm[mapping[s]]] for s in B1)
    if best_overall is None or cur>best_overall[0]:
        best_overall=(cur,txt,perm[:])
print(f"  mejor hill-climbing tras 60 reinicios: score={best_overall[0]:.1f}")
print(f"  texto: {best_overall[1]!r}")
print("  (si esto fuera una sustitucion de ingles, saldrian palabras legibles)")

# referencia: score de un texto ingles real y de uno aleatorio con la misma longitud
t = b'The quick brown fox jumps over the lazy dog and then some more text for scoring purposes here'
idx=[ALPH.index(chr(c)) for c in t.decode().lower() if chr(c) in ALPH]
s=sum(LOGBI[idx[i],idx[i+1]] for i in range(len(idx)-1))
print(f"  referencia texto ingles real: score={s:.1f}  (n={len(idx)})")
