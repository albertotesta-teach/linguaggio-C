"""Diagrammi per la presentazione 0701 - malloc e free.

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


# ── 1. stack e heap ───────────────────────────────────────────────────
def stack_heap():
    fig, ax = tela(9, 5.0)
    # stack
    cella(ax, 2, 2, 30, 40, GRIGIO, GRIGIO_BORDO, lw=1.2, r=0.8)
    testo(ax, 17, 45, "stack", 12, SANS, VERDE_SCURO, "bold")
    testo(ax, 17, 39, "variabili locali di main", 9, SANS, TESTO_TENUE)
    righe = [("int n", "5"), ("int i", "3"), ("double *ore", "")]
    for k, (nome, val) in enumerate(righe):
        y = 29 - k * 9
        cella(ax, 5, y, 24, 7, "white" if k < 2 else ARANCIO, VERDE, lw=1.3, r=0.4)
        testo(ax, 7, y + 3.5, nome, 9, MONO, VERDE_SCURO, "bold", ha="left")
        testo(ax, 27, y + 3.5, val, 10, MONO, TESTO, "bold", ha="right")
    # heap
    cella(ax, 40, 2, 48, 40, GRIGIO, GRIGIO_BORDO, lw=1.2, r=0.8)
    testo(ax, 64, 45, "heap", 12, SANS, VERDE_SCURO, "bold")
    testo(ax, 64, 39, "blocchi chiesti con malloc", 9, SANS, TESTO_TENUE)
    valori = ["7.0", "8.5", "9.0", "6.5", "6.0"]
    w = 8
    x0 = 44
    for k, v in enumerate(valori):
        cella(ax, x0 + k * w, 13, w - 0.6, 7, VERDE_CHIARO, VERDE, lw=1.3, r=0.3)
        testo(ax, x0 + k * w + w / 2 - 0.3, 16.5, v, 9, MONO, VERDE_SCURO, "bold")
        testo(ax, x0 + k * w + w / 2 - 0.3, 10.5, f"[{k}]", 8, MONO, TESTO_TENUE)
    testo(ax, x0 + 2.5 * w, 25, "malloc(5 * sizeof *ore)  ->  40 byte", 9, MONO, VERDE_SCURO, "bold")
    freccia(ax, 29.2, 14.5, x0 - 0.5, 16.5, color=ARANCIO_SCURO, lw=2, ms=14)
    testo(ax, 45, -4, "Il blocco resta valido fino a free(ore), anche fuori dalla funzione che lo ha allocato.",
          9, SANS, TESTO, ha="center")
    salva(fig, "0701-stack-e-heap.png")


# ── 2. crea e distruggi ───────────────────────────────────────────────
def crea_distruggi():
    fig, ax = tela(9, 4.8)
    testo(ax, 2, 45, "Registro *r = crea_registro(\"3B\", 4);", 10.5, MONO, VERDE_SCURO, "bold", ha="left")
    cella(ax, 2, 22, 10, 7, ARANCIO, VERDE, lw=1.3, r=0.4)
    testo(ax, 7, 25.5, "r", 11, MONO, VERDE_SCURO, "bold")
    freccia(ax, 12.3, 25.5, 19.5, 25.5, color=ARANCIO_SCURO, lw=2, ms=13)
    campi = [("classe", "\"3B\""), ("capienza", "4"), ("n", "2"), ("voti", "")]
    for k, (c, v) in enumerate(campi):
        y = 33 - k * 6.5
        cella(ax, 20, y, 26, 6, VERDE_CHIARO, VERDE, lw=1.2, r=0.2)
        testo(ax, 22, y + 3, c, 9, MONO, VERDE_SCURO, "bold", ha="left")
        testo(ax, 44, y + 3, v, 9, MONO, TESTO, ha="right")
    testo(ax, 33, 41.5, "struct Registro (malloc 1)", 9, SANS, TESTO_TENUE)
    voti = ["7.5", "6.0", "?", "?"]
    w = 8
    x0 = 56
    for k, v in enumerate(voti):
        cella(ax, x0 + k * w, 11.5, w - 0.6, 6, VERDE_CHIARO if k < 2 else "white", VERDE, lw=1.2, r=0.2)
        testo(ax, x0 + k * w + w / 2 - 0.3, 14.5, v, 9, MONO, VERDE_SCURO, "bold")
    testo(ax, x0 + 2 * w, 21, "array dei voti (malloc 2)", 9, SANS, TESTO_TENUE)
    freccia(ax, 44, 16.5, x0 - 0.5, 14.5, color=ARANCIO_SCURO, lw=2, ms=13)
    cella(ax, 2, 0, 86, 6, "white", VERDE_SCURO, lw=1.4, r=0.5)
    testo(ax, 4, 3, "distruggi_registro(r):   1. free(r->voti)    2. free(r)", 10, MONO, VERDE_SCURO,
          "bold", ha="left")
    salva(fig, "0701-crea-e-distruggi.png")


# ── 3. errori ─────────────────────────────────────────────────────────
def errori():
    fig, ax = tela(9, 5.6)
    # leak
    testo(ax, 2, 52, "Memory leak", 11, SANS, VERDE_SCURO, "bold", ha="left")
    testo(ax, 2, 47, "p = malloc(32);  p = malloc(32);", 9, MONO, TESTO, ha="left")
    cella(ax, 4, 34, 8, 6, ARANCIO, VERDE, lw=1.3, r=0.3)
    testo(ax, 8, 37, "p", 10, MONO, VERDE_SCURO, "bold")
    cella(ax, 18, 38, 10, 5, "white", ARANCIO_SCURO, lw=1.3, r=0.3)
    testo(ax, 23, 40.5, "blocco 1", 8, SANS, ARANCIO_SCURO, "bold")
    cella(ax, 18, 30, 10, 5, VERDE_CHIARO, VERDE, lw=1.3, r=0.3)
    testo(ax, 23, 32.5, "blocco 2", 8, SANS, VERDE_SCURO, "bold")
    freccia(ax, 12.3, 36, 17.6, 32.8, color=ARANCIO_SCURO, lw=1.8, ms=12)
    testo(ax, 23, 26, "il blocco 1 non ha piu'\nun puntatore: perso", 8.5, SANS, ARANCIO_SCURO, "bold")
    # dangling
    testo(ax, 32, 52, "Puntatore pendente", 11, SANS, VERDE_SCURO, "bold", ha="left")
    testo(ax, 32, 47, "free(p);", 9, MONO, TESTO, ha="left")
    cella(ax, 34, 34, 8, 6, ARANCIO, VERDE, lw=1.3, r=0.3)
    testo(ax, 38, 37, "p", 10, MONO, VERDE_SCURO, "bold")
    cella(ax, 48, 34, 11, 6, "white", GRIGIO_BORDO, lw=1.3, r=0.3)
    testo(ax, 53.5, 37, "liberato", 8, SANS, TESTO_TENUE)
    ax.plot([48, 59], [34, 40], color=GRIGIO_BORDO, lw=1)
    freccia(ax, 42.3, 37, 47.6, 37, color=ARANCIO_SCURO, lw=1.8, ms=12)
    testo(ax, 46, 26, "dopo free(p) scrivere\np = NULL;", 8.5, SANS, ARANCIO_SCURO, "bold")
    # fuori dai limiti
    testo(ax, 63, 52, "Fuori dai limiti", 11, SANS, VERDE_SCURO, "bold", ha="left")
    testo(ax, 63, 47, "for (i = 0; i <= n; i++)", 9, MONO, TESTO, ha="left")
    w = 5
    for k in range(4):
        cella(ax, 63 + k * w, 34, w - 0.4, 6, VERDE_CHIARO, VERDE, lw=1.2, r=0.2)
        testo(ax, 63 + k * w + w / 2 - 0.2, 31.5, str(k), 7.5, MONO, TESTO_TENUE)
    cella(ax, 63 + 4 * w, 34, w - 0.4, 6, ARANCIO, ARANCIO_SCURO, lw=1.6, r=0.2)
    testo(ax, 63 + 4 * w + w / 2 - 0.2, 31.5, "n", 7.5, MONO, ARANCIO_SCURO, "bold")
    testo(ax, 75, 26, "v[n] e' memoria di\nqualcun altro", 8.5, SANS, ARANCIO_SCURO, "bold")
    # regole
    cella(ax, 2, 2, 86, 16, GRIGIO, GRIGIO_BORDO, lw=1.0, r=0.6)
    regole = ["free prima di riusare il puntatore",
              "free(p); p = NULL;    free(NULL) non fa nulla",
              "indici da 0 a n - 1, strlen + 1 per le stringhe",
              "gcc -g -fsanitize=address  trova gli errori"]
    for k, r in enumerate(regole):
        testo(ax, 5, 15 - k * 3.6, "- " + r, 9, MONO, TESTO, ha="left")
    salva(fig, "0701-errori-memoria.png")


# ── 4. copia superficiale e profonda ──────────────────────────────────
def copie():
    fig, ax = tela(9, 4.8)
    def struct(x, y, nome):
        cella(ax, x, y, 15, 9, VERDE_CHIARO, VERDE, lw=1.3, r=0.4)
        testo(ax, x + 7.5, y + 6, nome, 9, MONO, VERDE_SCURO, "bold")
        testo(ax, x + 7.5, y + 2.5, "voti", 8.5, MONO, TESTO)
    def array(x, y, valori, fc):
        for k, v in enumerate(valori):
            cella(ax, x + k * 5.5, y, 5.1, 5, fc, VERDE, lw=1.1, r=0.2)
            testo(ax, x + k * 5.5 + 2.55, y + 2.5, v, 8, MONO, VERDE_SCURO, "bold")
    testo(ax, 2, 46, "Superficiale: copia = originale", 10.5, SANS, VERDE_SCURO, "bold", ha="left")
    struct(2, 30, "originale")
    struct(2, 16, "copia")
    array(23, 24, ["6", "5.5", "7"], VERDE_CHIARO)
    freccia(ax, 17.3, 32.5, 22.7, 27, color=ARANCIO_SCURO, lw=1.8, ms=12)
    freccia(ax, 17.3, 18.5, 22.7, 25.5, color=ARANCIO_SCURO, lw=1.8, ms=12)
    testo(ax, 21, 9, "un solo blocco: modifiche\ncondivise e rischio di doppio free", 8.5, SANS, ARANCIO_SCURO,
          "bold")
    testo(ax, 48, 46, "Profonda: duplica(&originale, &copia)", 10.5, SANS, VERDE_SCURO, "bold", ha="left")
    struct(48, 30, "originale")
    struct(48, 16, "copia")
    array(69, 31, ["6", "5.5", "7"], VERDE_CHIARO)
    array(69, 17, ["6", "5.5", "7"], ARANCIO)
    freccia(ax, 63.3, 34.5, 68.7, 33.5, color=ARANCIO_SCURO, lw=1.8, ms=12)
    freccia(ax, 63.3, 20.5, 68.7, 19.5, color=ARANCIO_SCURO, lw=1.8, ms=12)
    testo(ax, 66, 9, "due blocchi: ognuno\nsi libera per conto suo", 8.5, SANS, VERDE_SCURO, "bold")
    salva(fig, "0701-copia-superficiale-e-profonda.png")


stack_heap()
crea_distruggi()
errori()
copie()
