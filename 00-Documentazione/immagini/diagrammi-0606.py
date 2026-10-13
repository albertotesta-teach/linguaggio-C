"""Diagrammi per la presentazione 0606 - Union.

Uso: python3 diagrammi-0605.py <cartella-di-uscita>
Richiede matplotlib e Pillow.
"""
import sys
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch, FancyArrowPatch
from matplotlib import font_manager

for f in font_manager.findSystemFonts():
    if "Inter" in f or "DejaVu" in f:
        font_manager.fontManager.addfont(f)

SANS = "Inter"
MONO = "DejaVu Sans Mono"
VERDE_SCURO = "#1b4d24"
VERDE = "#256b2b"
VERDE_CHIARO = "#DCEFDC"
GRIGIO = "#F2F2F2"
GRIGIO_BORDO = "#BDBDBD"
TESTO = "#222222"
TESTO_TENUE = "#6b6b6b"

OUT = sys.argv[1] if len(sys.argv) > 1 else "."


def tela(w, h):
    fig = plt.figure(figsize=(w, h + 1), dpi=200)
    ax = fig.add_axes([0, 0, 1, 1])
    ax.set_xlim(0, w * 10)
    ax.set_ylim(-10, h * 10)
    ax.set_aspect("equal")
    ax.axis("off")
    return fig, ax


def cella(ax, x, y, w, h, colore, bordo, lw=1.6, r=0.6):
    ax.add_patch(FancyBboxPatch((x, y), w, h,
                                boxstyle=f"round,pad=0,rounding_size={r}",
                                fc=colore, ec=bordo, lw=lw))


def testo(ax, x, y, s, size=13, font=SANS, color=TESTO, weight="normal",
          ha="center", va="center"):
    ax.text(x, y, s, fontsize=size, family=font, color=color,
            weight=weight, ha=ha, va=va)


def freccia(ax, x1, y1, x2, y2, color=VERDE, lw=2.2, rad=0.0, ms=18):
    ax.add_patch(FancyArrowPatch((x1, y1), (x2, y2),
                                 connectionstyle=f"arc3,rad={rad}",
                                 arrowstyle="-|>", mutation_scale=ms,
                                 color=color, lw=lw))


def salva(fig, nome):
    from PIL import Image, ImageChops
    percorso = f"{OUT}/{nome}"
    fig.savefig(percorso, facecolor="white")
    plt.close(fig)
    img = Image.open(percorso).convert("RGB")
    sfondo = Image.new("RGB", img.size, (255, 255, 255))
    box = ImageChops.difference(img, sfondo).getbbox()
    m = 40
    box = (max(box[0] - m, 0), max(box[1] - m, 0),
           min(box[2] + m, img.size[0]), min(box[3] + m, img.size[1]))
    img.crop(box).save(percorso)




ARANCIO = "#F8D9A8"
ARANCIO_SCURO = "#9A5B00"
import math
from matplotlib.patches import Circle


# ── 1. struct e union ─────────────────────────────────────────────────
def struct_union():
    fig, ax = tela(9, 5.0)
    s = 2.6   # unita' per byte
    x0 = 14
    # struct
    testo(ax, 2, 47, "struct: i campi uno dopo l'altro", 11, SANS, VERDE_SCURO, "bold", ha="left")
    yS = 34
    campi = [("intero", 0, 4, VERDE_CHIARO), ("pad", 4, 4, "white"), ("reale", 8, 8, VERDE_CHIARO),
             ("testo[8]", 16, 8, VERDE_CHIARO)]
    for n, a, l, fc in campi:
        cella(ax, x0 + a * s, yS, l * s - 0.5, 7, fc, VERDE if n != "pad" else GRIGIO_BORDO, lw=1.3, r=0.3)
        testo(ax, x0 + a * s + l * s / 2, yS + 3.5, n, 9, MONO, VERDE_SCURO if n != "pad" else TESTO_TENUE,
              "bold" if n != "pad" else "normal")
    testo(ax, x0 + 24 * s + 2, yS + 3.5, "24 byte", 10, MONO, VERDE_SCURO, "bold", ha="left")
    for b in range(0, 25, 4):
        testo(ax, x0 + b * s, yS - 2.5, str(b), 7.5, MONO, TESTO_TENUE)
    # union
    testo(ax, 2, 25, "union: i campi partono tutti dallo stesso indirizzo", 11, SANS, VERDE_SCURO, "bold",
          ha="left")
    righe = [("intero", 4), ("reale", 8), ("testo[8]", 8)]
    for i, (n, l) in enumerate(righe):
        y = 15 - i * 6.5
        cella(ax, x0, y, l * s - 0.5, 5.2, ARANCIO if i == 1 else VERDE_CHIARO, VERDE, lw=1.3, r=0.3)
        testo(ax, x0 + l * s / 2, y + 2.6, n, 9, MONO, VERDE_SCURO, "bold")
    ax.plot([x0, x0], [0, 22], color=ARANCIO_SCURO, lw=1.6, ls="--")
    testo(ax, x0 - 1.5, 11, "stesso\nindirizzo", 8.5, SANS, ARANCIO_SCURO, "bold", ha="right")
    cella(ax, x0, -7.5, 8 * s - 0.5, 4, "white", VERDE_SCURO, lw=1.6, r=0.3)
    testo(ax, x0 + 4 * s, -5.5, "8 byte in tutto", 9, MONO, VERDE_SCURO, "bold")
    testo(ax, x0 + 8 * s + 4, 8.5, "Contiene un solo valore alla volta:\nl'ultimo scritto (qui reale).",
          9.5, SANS, TESTO, ha="left")
    salva(fig, "0606-struct-e-union.png")


# ── 2. ordine dei byte ────────────────────────────────────────────────
def byte_ordine():
    fig, ax = tela(9, 4.6)
    testo(ax, 2, 44, "Parola p;   p.valore = 0x0A0B0C0D;", 10.5, MONO, VERDE_SCURO, "bold", ha="left")
    w = 11
    x0 = 26
    def riga(y, titolo, byte, evid):
        testo(ax, 2, y + 4, titolo, 10, SANS, VERDE_SCURO, "bold", ha="left")
        for i, b in enumerate(byte):
            x = x0 + i * w
            cella(ax, x, y, w - 0.8, 8, ARANCIO if i == evid else VERDE_CHIARO, VERDE, lw=1.3, r=0.4)
            testo(ax, x + w / 2 - 0.4, y + 4, b, 12, MONO, VERDE_SCURO, "bold")
    for i in range(4):
        testo(ax, x0 + i * w + w / 2 - 0.4, 37, f"byte[{i}]", 9, MONO, TESTO_TENUE, "bold")
    riga(25, "little-endian\n(PC, Apple Silicon)", ["0D", "0C", "0B", "0A"], 0)
    riga(11, "big-endian\n(ordine di rete)", ["0A", "0B", "0C", "0D"], 0)
    freccia(ax, x0, 6, x0 + 4 * w - 0.8, 6, color=GRIGIO_BORDO, lw=1.4, ms=12)
    testo(ax, x0 + 2 * w, 3, "indirizzi crescenti", 8.5, SANS, TESTO_TENUE)
    testo(ax, x0 + 4 * w + 2, 29, "byte meno\nsignificativo\nper primo", 8.5, SANS, ARANCIO_SCURO, "bold",
          ha="left")
    testo(ax, x0 + 4 * w + 2, 15, "byte piu'\nsignificativo\nper primo", 8.5, SANS, ARANCIO_SCURO, "bold",
          ha="left")
    testo(ax, 2, -4, "if (p.byte[0] == 0x0D)  /* macchina little-endian */", 10, MONO, ARANCIO_SCURO,
          "bold", ha="left")
    salva(fig, "0606-ordine-dei-byte.png")


# ── 3. anatomia di un float ───────────────────────────────────────────
def anatomia():
    fig, ax = tela(9, 3.6)
    testo(ax, 2, 33, "Float f;   f.reale = -2.5f;      f.bit = 0xC0200000", 10.5, MONO, VERDE_SCURO,
          "bold", ha="left")
    bit = format(0xC0200000, "032b")
    w = 2.6
    x0 = 4
    y = 20
    for i, b in enumerate(bit):
        fc = ARANCIO if i == 0 else (VERDE_CHIARO if i < 9 else "white")
        gap = (1.2 if i >= 1 else 0) + (1.2 if i >= 9 else 0)
        cella(ax, x0 + i * w + gap, y, w - 0.3, 6, fc, VERDE if i < 9 else GRIGIO_BORDO, lw=1.0, r=0.2)
        testo(ax, x0 + i * w + gap + w / 2 - 0.15, y + 3, b, 9, MONO, VERDE_SCURO, "bold")
    def graffa(a, b, gap, titolo, sotto):
        xa = x0 + a * w + gap
        xb = x0 + b * w + gap - 0.3
        ax.plot([xa, xa, xb, xb], [y - 1.5, y - 3, y - 3, y - 1.5], color=VERDE_SCURO, lw=1.3)
        testo(ax, (xa + xb) / 2, y - 6.5, titolo, 9.5, SANS, VERDE_SCURO, "bold")
        testo(ax, (xa + xb) / 2, y - 11, sotto, 8.8, MONO, TESTO)
    graffa(0, 1, 0, "segno", "1 = negativo")
    graffa(1, 9, 1.2, "esponente (8 bit)", "128 - 127 = 1")
    graffa(9, 32, 2.4, "mantissa (23 bit)", "1.01 binario = 1.25")
    testo(ax, x0 + 16 * w, y + 10, "f.bit >> 31      (f.bit >> 23) & 0xFF      f.bit & 0x7FFFFF", 9.5,
          MONO, ARANCIO_SCURO, "bold")
    testo(ax, 2, 0, "valore = (-1)^1 x 1.25 x 2^1 = -2.5", 10.5, MONO, VERDE_SCURO, "bold", ha="left")
    salva(fig, "0606-anatomia-float.png")


# ── 4. union con etichetta ────────────────────────────────────────────
def etichetta():
    fig, ax = tela(9, 5.2)
    testo(ax, 2, 50, "typedef struct { TipoDato tipo; union { int intero; double reale; char testo[16]; } v; } Dato;",
          8.3, MONO, VERDE_SCURO, "bold", ha="left")
    esempi = [("INTERO", "intero", "17"), ("REALE", "reale", "36.6"), ("TESTO", "testo", "\"rame\"")]
    xe = 4
    xu = 25
    for i, (tag, campo, val) in enumerate(esempi):
        y = 34 - i * 13
        cella(ax, xe, y, 18, 8, ARANCIO, ARANCIO_SCURO, lw=1.4, r=0.4)
        testo(ax, xe + 9, y + 5.2, "tipo", 8, MONO, ARANCIO_SCURO)
        testo(ax, xe + 9, y + 2.4, tag, 10, MONO, ARANCIO_SCURO, "bold")
        cella(ax, xu, y, 30, 8, VERDE_CHIARO, VERDE, lw=1.4, r=0.4)
        testo(ax, xu + 15, y + 5.2, f"v.{campo}", 8.5, MONO, VERDE_SCURO)
        testo(ax, xu + 15, y + 2.4, val, 10.5, MONO, VERDE_SCURO, "bold")
        freccia(ax, xe + 18.3, y + 4, xu - 0.3, y + 4, color=ARANCIO_SCURO, lw=1.5, ms=11)
    testo(ax, xe + 9, 44, "etichetta", 9.5, SANS, ARANCIO_SCURO, "bold")
    testo(ax, xu + 15, 44, "union: il campo valido", 9.5, SANS, VERDE_SCURO, "bold")
    codice = ("switch (d->tipo) {\ncase INTERO: ... d->v.intero ...\ncase REALE:  ... d->v.reale ...\n"
              "case TESTO:  ... d->v.testo ...\n}")
    cella(ax, 59, 14, 30, 22, GRIGIO, GRIGIO_BORDO, lw=1.0, r=0.6)
    testo(ax, 61, 25, codice, 8.2, MONO, TESTO, ha="left")
    testo(ax, 2, -1, "Si scrive campo ed etichetta insieme; si legge il campo solo dopo aver controllato l'etichetta.",
          9, SANS, TESTO, ha="left")
    salva(fig, "0606-union-con-etichetta.png")


struct_union()
byte_ordine()
anatomia()
etichetta()
