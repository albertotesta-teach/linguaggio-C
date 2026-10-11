"""Diagrammi per la presentazione 0501 - Introduzione ai puntatori.

Uso: python3 diagrammi-0501.py <cartella-di-uscita>
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


# ── 1. La memoria e gli indirizzi ─────────────────────────────────────
def memoria():
    fig, ax = tela(8, 3.4)
    indirizzi = ["...6a", "...6b", "...6c", "...6d", "...6e", "...6f", "...70", "...71"]
    x0 = 13
    w = 8.2
    y = 15
    h = 9
    testo(ax, x0 - 1, y + h + 4.5, "indirizzo (hex)", 11, color=TESTO_TENUE, ha="right")
    testo(ax, x0 - 1, y + h / 2, "memoria", 11, color=TESTO_TENUE, ha="right")
    for i, ind in enumerate(indirizzi):
        x = x0 + i * w
        dentro = 2 <= i <= 5
        testo(ax, x + w / 2, y + h + 4.5, ind, 11.5, MONO,
              VERDE_SCURO if dentro else TESTO_TENUE,
              "bold" if dentro else "normal")
        if not dentro:
            cella(ax, x + 0.3, y, w - 0.6, h, GRIGIO, GRIGIO_BORDO, r=0.4)
    # la variabile: un blocco unico di 4 byte, divisori tratteggiati
    xa = x0 + 2 * w
    cella(ax, xa + 0.3, y, 4 * w - 0.6, h, VERDE_CHIARO, VERDE_SCURO, lw=2.4, r=0.5)
    for k in range(1, 4):
        ax.plot([xa + k * w, xa + k * w], [y + 0.8, y + h - 0.8],
                color=VERDE, lw=1.2, ls=(0, (3, 3)), alpha=0.7)
    ax.text(xa + 2 * w, y + h / 2, "17", fontsize=22, family=MONO, color=VERDE_SCURO, weight="bold", ha="center", va="center", bbox=dict(boxstyle="round,pad=0.25", fc=VERDE_CHIARO, ec="none"))
    # parentesi sotto
    yb = y - 3
    ax.plot([xa + 0.3, xa + 0.3, xa + 4 * w - 0.3, xa + 4 * w - 0.3],
            [yb + 1.2, yb, yb, yb + 1.2], color=VERDE_SCURO, lw=1.6)
    testo(ax, xa + 2.6 * w, yb - 2.8, "eta: int, 4 byte", 12.5, MONO, VERDE_SCURO, "bold")
    # freccia indirizzo
    freccia(ax, xa + w / 2, 1.5, xa + w / 2, y - 0.8, color=VERDE)
    testo(ax, xa + w / 2 - 1.5, 3.0, "&eta = ...6c", 13, MONO, VERDE, "bold", ha="right")
    testo(ax, xa + w / 2 + 1.5, 3.0, "indirizzo della prima cella", 11.5, SANS, TESTO_TENUE, ha="left")
    testo(ax, x0 - 1, -3.0, "...6c", 11, MONO, TESTO, "bold", ha="right")
    ax.text(x0 + 0.5, -3.0,
            "ultime cifre esadecimali dell'indirizzo, ad esempio 0x7ffd5e8a2e6c (stampato con %p)",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0501-memoria-e-indirizzi.png")


# ── 2. Array in memoria ───────────────────────────────────────────────
def array():
    fig, ax = tela(8, 5.0)
    x0 = 6
    # int voti[5]: 5 celle da 4 byte
    y = 32
    h = 8
    w4 = 12
    valori = ["7", "8", "6", "9", "7"]
    testo(ax, x0, y + h + 6.5, "int voti[5]", 14, MONO, VERDE_SCURO, "bold", ha="left")
    for i in range(5):
        x = x0 + i * w4
        cella(ax, x + 0.25, y, w4 - 0.5, h, VERDE_CHIARO, VERDE, r=0.4)
        testo(ax, x + w4 / 2, y + h / 2 + 1.2, valori[i], 15, MONO, VERDE_SCURO, "bold")
        testo(ax, x + w4 / 2, y + 1.8, f"voti[{i}]", 9.5, MONO, TESTO_TENUE)
        testo(ax, x + 0.25, y + h + 2.2, f"...{0x550 + 4 * i:x}", 10.5, MONO, TESTO, ha="left")
        if i < 4:
            freccia(ax, x + 3.5, y - 1.3, x + w4 + 3.5, y - 1.3, color=VERDE, lw=1.4,
                    rad=0.45, ms=11)
            testo(ax, x + w4 / 2 + 3.5, y - 6.2, "+4", 11, SANS, VERDE, "bold")
    # double pesi[3]: celle da 8 byte, larghe il doppio
    y = 8
    w8 = 2 * w4
    pesi = ["62.5", "70.0", "58.3"]
    testo(ax, x0, y + h + 6.5, "double pesi[3]", 14, MONO, VERDE_SCURO, "bold", ha="left")
    for i in range(3):
        x = x0 + i * w8
        cella(ax, x + 0.25, y, w8 - 0.5, h, VERDE_CHIARO, VERDE, r=0.4)
        testo(ax, x + w8 / 2, y + h / 2 + 1.2, pesi[i], 15, MONO, VERDE_SCURO, "bold")
        testo(ax, x + w8 / 2, y + 1.8, f"pesi[{i}]", 9.5, MONO, TESTO_TENUE)
        testo(ax, x + 0.25, y + h + 2.2, f"...{0x600 + 8 * i:x}", 10.5, MONO, TESTO, ha="left")
        if i < 2:
            freccia(ax, x + 3.5, y - 1.3, x + w8 + 3.5, y - 1.3, color=VERDE, lw=1.4,
                    rad=0.3, ms=11)
            testo(ax, x + w8 / 2 + 3.5, y - 6.0, "+8", 11, SANS, VERDE, "bold")
    ax.text(x0, -4.0,
            "Indirizzi esadecimali abbreviati alle ultime cifre: ...558 + 4 = ...55c (dopo 9 vengono a, b, c, d, e, f).",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0501-array-in-memoria.png")


# ── 3. Il puntatore ───────────────────────────────────────────────────
def puntatore():
    fig, ax = tela(8, 4.4)
    y = 16
    h = 13
    w = 28
    xp = 2
    xl = 50
    # p
    testo(ax, xp + w / 2, y + h + 4.5, "p", 17, MONO, TESTO, "bold")
    testo(ax, xp + w / 2 + 3, y + h + 4.5, "(int *)", 11, MONO, TESTO_TENUE, ha="left")
    cella(ax, xp, y, w, h, "white", TESTO, lw=2.0)
    testo(ax, xp + w / 2, y + h / 2 + 2, "0x7ffd5e8a2eec", 14, MONO, VERDE, "bold")
    testo(ax, xp + w / 2, y + 3.2, "indirizzo di memoria", 10.5, SANS, TESTO_TENUE)
    testo(ax, xp + w / 2, y - 3.8, "&p = 0x7ffd5e8a2ef8", 11, MONO, TESTO_TENUE)
    # livello
    testo(ax, xl + w / 2, y + h + 4.5, "livello", 17, MONO, VERDE_SCURO, "bold")
    testo(ax, xl + w / 2 + 8, y + h + 4.5, "(int)", 11, MONO, TESTO_TENUE, ha="left")
    cella(ax, xl, y, w, h, VERDE_CHIARO, VERDE_SCURO, lw=2.0)
    testo(ax, xl + w / 2, y + h / 2, "85", 22, MONO, VERDE_SCURO, "bold")
    testo(ax, xl + w / 2, y - 3.8, "&livello = 0x7ffd5e8a2eec", 11, MONO, VERDE, "bold")
    # freccia
    freccia(ax, xp + w + 0.6, y + h / 2, xl - 0.6, y + h / 2, color=VERDE, lw=2.8, ms=22)
    testo(ax, (xp + w + xl) / 2, y + h / 2 + 3.2, "punta a", 12, SANS, VERDE, "bold")
    # legenda
    ax.plot([xp, xl + w], [6.5, 6.5], color=GRIGIO_BORDO, lw=1)
    ax.text(xp, 3.0, "0x7ffd5e8a2eec", fontsize=11, family=MONO, color=TESTO,
            weight="bold", ha="left", va="center")
    ax.text(xp + 15.5, 3.0,
            "indirizzo scritto in esadecimale (prefisso 0x, cifre 0-9 e a-f), come lo stampa %p",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    ax.text(xp, -0.8, "*p", fontsize=11, family=MONO, color=VERDE_SCURO,
            weight="bold", ha="left", va="center")
    ax.text(xp + 15.5, -0.8, "la variabile all'indirizzo contenuto in p, cioè livello",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0501-il-puntatore.png")


memoria()
array()
puntatore()
