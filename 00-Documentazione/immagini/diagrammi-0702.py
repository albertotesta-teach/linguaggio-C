"""Diagrammi per la presentazione 0702 - calloc e realloc.

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


def blocco(ax, x, y, valori, fc, w=6, h=6, size=10, colore=VERDE_SCURO):
    for k, v in enumerate(valori):
        cella(ax, x + k * w, y, w - 0.5, h, fc if not isinstance(fc, list) else fc[k], VERDE, lw=1.3,
              r=0.3)
        testo(ax, x + k * w + w / 2 - 0.25, y + h / 2, v, size, MONO, colore, "bold")


# ── 1. malloc e calloc ────────────────────────────────────────────────
def malloc_calloc():
    fig, ax = tela(9, 3.6)
    testo(ax, 2, 33, "int *a = malloc(n * sizeof *a);", 10.5, MONO, VERDE_SCURO, "bold", ha="left")
    blocco(ax, 4, 21, ["?"] * 6, "white", colore=ARANCIO_SCURO)
    testo(ax, 44, 24, "contenuto non definito:\nva scritto prima di leggerlo", 9, SANS, ARANCIO_SCURO,
          "bold", ha="left")
    testo(ax, 2, 13, "int *b = calloc(n, sizeof *b);", 10.5, MONO, VERDE_SCURO, "bold", ha="left")
    blocco(ax, 4, 1, ["0"] * 6, VERDE_CHIARO)
    testo(ax, 44, 4, "tutti i byte a zero:\ncontatori, flag, celle vuote", 9, SANS, VERDE_SCURO, "bold",
          ha="left")
    salva(fig, "0702-malloc-e-calloc.png")


# ── 2. i due casi di realloc ──────────────────────────────────────────
def realloc_casi():
    fig, ax = tela(9, 5.2)
    testo(ax, 2, 49, "nuovo = realloc(v, 6 * sizeof *v);", 10.5, MONO, VERDE_SCURO, "bold", ha="left")
    testo(ax, 2, 41, "1. c'e' spazio dopo il blocco: lo allunga sul posto", 10, SANS, VERDE_SCURO,
          "bold", ha="left")
    blocco(ax, 4, 30, ["7", "8", "6", "9"], VERDE_CHIARO)
    blocco(ax, 4 + 4 * 6, 30, ["", ""], ARANCIO)
    testo(ax, 4 + 6 * 6 + 3, 33, "stesso indirizzo", 9, SANS, TESTO, ha="left")
    testo(ax, 2, 25, "2. non c'e' spazio: alloca altrove, copia, libera il vecchio", 10, SANS,
          VERDE_SCURO, "bold", ha="left")
    blocco(ax, 4, 9, ["7", "8", "6", "9"], "white", colore=TESTO_TENUE)
    cella(ax, 4 + 4 * 6, 9, 11.5, 6, GRIGIO, GRIGIO_BORDO, lw=1.2, r=0.3)
    testo(ax, 4 + 5 * 6 - 0.25, 12, "occupato", 8.5, SANS, TESTO_TENUE)
    testo(ax, 4 + 12, 5, "vecchio blocco: liberato", 8.5, SANS, TESTO_TENUE)
    blocco(ax, 50, 9, ["7", "8", "6", "9"], VERDE_CHIARO)
    blocco(ax, 50 + 4 * 6, 9, ["", ""], ARANCIO)
    freccia(ax, 28, 16.5, 50, 16.5, color=ARANCIO_SCURO, lw=1.8, rad=-0.15, ms=13)
    testo(ax, 39, 21.5, "copia", 9, SANS, ARANCIO_SCURO, "bold")
    testo(ax, 68, 5, "indirizzo nuovo", 8.5, SANS, TESTO)
    testo(ax, 2, -4, "In entrambi i casi si usa solo il puntatore restituito; i posti nuovi non sono inizializzati.",
          9, SANS, TESTO, ha="left")
    salva(fig, "0702-realloc-due-casi.png")


# ── 3. puntatore temporaneo ───────────────────────────────────────────
def temporaneo():
    fig, ax = tela(9, 4.4)
    testo(ax, 2, 41, "SBAGLIATO:  v = realloc(v, ...);", 10, MONO, ARANCIO_SCURO, "bold", ha="left")
    cella(ax, 4, 24, 9, 7, ARANCIO, VERDE, lw=1.3, r=0.3)
    testo(ax, 8.5, 27.5, "v", 11, MONO, VERDE_SCURO, "bold")
    testo(ax, 8.5, 20, "NULL", 9, MONO, ARANCIO_SCURO, "bold")
    blocco(ax, 20, 25, ["7", "8", "6", "9"], "white", w=5, h=5, size=9, colore=TESTO_TENUE)
    testo(ax, 30, 20, "blocco ancora allocato,\nnessuno lo raggiunge: perso", 8.5, SANS, ARANCIO_SCURO,
          "bold")
    ax.plot([46, 46], [2, 42], color=GRIGIO_BORDO, lw=1)
    testo(ax, 49, 41, "CORRETTO:  tmp = realloc(v, ...);", 10, MONO, VERDE_SCURO, "bold", ha="left")
    cella(ax, 50, 26, 9, 6, ARANCIO, VERDE, lw=1.3, r=0.3)
    testo(ax, 54.5, 29, "v", 11, MONO, VERDE_SCURO, "bold")
    cella(ax, 50, 16, 9, 6, "white", GRIGIO_BORDO, lw=1.3, r=0.3)
    testo(ax, 54.5, 19, "tmp", 10, MONO, TESTO_TENUE, "bold")
    testo(ax, 54.5, 13.5, "NULL", 9, MONO, ARANCIO_SCURO, "bold")
    blocco(ax, 65, 26.5, ["7", "8", "6", "9"], VERDE_CHIARO, w=5, h=5, size=9)
    freccia(ax, 59.3, 29, 64.6, 29, color=ARANCIO_SCURO, lw=1.8, ms=12)
    testo(ax, 49, 3, "if (tmp == NULL)  ... v e' ancora valido\nelse { v = tmp; n = nuova_n; }", 8.5, MONO,
          VERDE_SCURO, "bold", ha="left")
    ax.plot([0, 0], [0, 0])
    salva(fig, "0702-puntatore-temporaneo.png")


# ── 4. aggiungere una colonna ─────────────────────────────────────────
def colonna():
    fig, ax = tela(9, 4.2)
    testo(ax, 2, 39, "tabellone 2 x 3 in un blocco, poi una colonna in piu'", 10.5, SANS, VERDE_SCURO,
          "bold", ha="left")
    testo(ax, 2, 31, "prima", 9, SANS, TESTO_TENUE, ha="left")
    blocco(ax, 12, 27, ["a0", "a1", "a2"], VERDE_CHIARO, w=7)
    blocco(ax, 12 + 21, 27, ["b0", "b1", "b2"], ARANCIO, w=7)
    testo(ax, 2, 13, "dopo", 9, SANS, TESTO_TENUE, ha="left")
    blocco(ax, 12, 9, ["a0", "a1", "a2", "__"], [VERDE_CHIARO] * 3 + ["white"], w=7)
    blocco(ax, 12 + 28, 9, ["b0", "b1", "b2", "__"], [ARANCIO] * 3 + ["white"], w=7)
    for k, (da, a) in enumerate([(5, 6), (4, 5), (3, 4)]):
        x1 = 12 + da * 7 + 3
        x2 = 12 + a * 7 + 3
        freccia(ax, x1, 26.5, x2, 15.5, color=ARANCIO_SCURO, lw=1.5, ms=11)
        testo(ax, (x1 + x2) / 2 + 2.5, 21, str(k + 1), 8.5, SANS, ARANCIO_SCURO, "bold")
    testo(ax, 2, 2, "Si sposta partendo dall'ultimo: la nuova posizione non e' mai prima della vecchia.",
          9, SANS, TESTO, ha="left")
    testo(ax, 2, -2.5, "tmp[r * (colonne + 1) + c] = tmp[r * colonne + c];   r e c decrescenti", 9, MONO,
          VERDE_SCURO, "bold", ha="left")
    salva(fig, "0702-aggiungere-una-colonna.png")


malloc_calloc()
realloc_casi()
temporaneo()
colonna()
