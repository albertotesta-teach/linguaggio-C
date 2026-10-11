"""Diagrammi per la presentazione 0504 - Puntatori a puntatori.

Uso: python3 diagrammi-0504.py <cartella-di-uscita>
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



def scatola(ax, x, y, w, h, nome, tipo, valore, indirizzo, verde=False):
    colore = VERDE_SCURO if verde else TESTO
    testo(ax, x + w / 2, y + h + 4.6, nome, 13, MONO, colore, "bold")
    testo(ax, x + w / 2, y + h + 1.8, tipo, 9.5, MONO, TESTO_TENUE)
    cella(ax, x, y, w, h, VERDE_CHIARO if verde else "white", colore, lw=2.0, r=0.6)
    testo(ax, x + w / 2, y + h / 2, valore, 13, MONO, colore, "bold")
    testo(ax, x + w / 2, y - 2.6, indirizzo, 9.5, MONO, TESTO_TENUE)


# ── 1. tre livelli ────────────────────────────────────────────────────
def tre_livelli():
    fig, ax = tela(8, 3.4)
    y = 12
    h = 9
    scatola(ax, 2, y, 20, h, "pannello", "int **", "...e18", "&pannello = ...e20")
    scatola(ax, 30, y, 20, h, "selezionato", "int *", "...e10", "&selezionato = ...e18")
    scatola(ax, 58, y, 20, h, "ascensore", "int", "2", "&ascensore = ...e10", verde=True)
    freccia(ax, 22.5, y + h / 2, 29.5, y + h / 2, color=VERDE, lw=2.4, ms=16)
    freccia(ax, 50.5, y + h / 2, 57.5, y + h / 2, color=VERDE, lw=2.4, ms=16)
    # graffe sotto
    ax.text(2, 1.5, "*pannello  = selezionato (un indirizzo)", fontsize=11, family=MONO, color=TESTO, ha="left", va="center")
    ax.text(2, -2.5, "**pannello = ascensore   (il valore 2)", fontsize=11, family=MONO, color=VERDE_SCURO, weight="bold", ha="left", va="center")
    ax.text(48, 1.5, "**pannello = 4;  cambia ascensore", fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    ax.text(48, -2.5, "*pannello = &altro;  cambia selezionato", fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0504-doppio-puntatore.png")


# ── 2. array di puntatori e matrice di char ───────────────────────────
def array_puntatori():
    fig, ax = tela(8, 4.8)
    giorni = ["lunedi", "martedi", "mercoledi", "giovedi", "venerdi", "sabato", "domenica"]
    brevi = giorni[:4]
    # sinistra: matrice
    testo(ax, 2, 45, "char g[4][10]", 12, MONO, VERDE_SCURO, "bold", ha="left")
    cw = 3.2
    ch = 4.6
    for r, parola in enumerate(brevi):
        yy = 36 - r * 6
        for c in range(10):
            if c < len(parola):
                fc, ec, t = VERDE_CHIARO, VERDE, parola[c]
            elif c == len(parola):
                fc, ec, t = GRIGIO, GRIGIO_BORDO, "\\0"
            else:
                fc, ec, t = "white", GRIGIO_BORDO, ""
            cella(ax, 2 + c * cw, yy, cw - 0.3, ch, fc, ec, lw=1.0, r=0.2)
            testo(ax, 2 + c * cw + cw / 2 - 0.15, yy + ch / 2, t, 8.5, MONO, VERDE_SCURO if c < len(parola) else TESTO_TENUE)
    ax.text(2, 13, "ogni riga occupa 10 char,", fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    ax.text(2, 9.5, "anche quelle più corte", fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    # destra: array di puntatori
    x0 = 42
    testo(ax, x0, 45, "const char *g[4]", 12, MONO, VERDE_SCURO, "bold", ha="left")
    for r, parola in enumerate(brevi):
        yy = 36 - r * 6
        cella(ax, x0, yy, 7, ch, "white", TESTO, lw=1.4, r=0.3)
        ax.plot([x0 + 3.5], [yy + ch / 2], marker="o", ms=4, color=VERDE)
        testo(ax, x0 - 1, yy + ch / 2, f"g[{r}]", 9, MONO, TESTO_TENUE, ha="right")
        xs = x0 + 11
        freccia(ax, x0 + 3.5, yy + ch / 2, xs - 0.4, yy + ch / 2, color=VERDE, lw=1.4, ms=10)
        for c, car in enumerate(parola + "0"):
            t = "\\0" if c == len(parola) else car
            fc = GRIGIO if c == len(parola) else VERDE_CHIARO
            cella(ax, xs + c * 2.5, yy, 2.3, ch, fc, VERDE if c < len(parola) else GRIGIO_BORDO, lw=0.9, r=0.2)
            testo(ax, xs + c * 2.5 + 1.15, yy + ch / 2, t, 7.5, MONO, VERDE_SCURO)
    ax.text(x0, 13, "ogni elemento è un indirizzo (8 byte):", fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    ax.text(x0, 9.5, "i testi occupano solo lo spazio necessario", fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0504-array-di-puntatori.png")


# ── 3. puntatore a riga e blocco unico ────────────────────────────────
def puntatore_riga():
    fig, ax = tela(8, 5.2)
    righe = 3
    col = 4
    cw = 7
    ch = 5
    valori = [[5, 2, 0, 3], [4, 6, 1, 2], [0, 3, 7, 5]]
    x0 = 18
    testo(ax, 2, 50, "int m[3][4]", 12, MONO, VERDE_SCURO, "bold", ha="left")
    for r in range(righe):
        yy = 40 - r * 7
        for c in range(col):
            fc = "#C3E2C3" if r == 1 else VERDE_CHIARO
            cella(ax, x0 + c * cw, yy, cw - 0.4, ch, fc, VERDE, lw=1.2, r=0.3)
            testo(ax, x0 + c * cw + cw / 2, yy + ch / 2, str(valori[r][c]), 11, MONO, VERDE_SCURO, "bold")
        testo(ax, x0 - 2, yy + ch / 2, f"m[{r}]", 10, MONO, TESTO_TENUE, ha="right")
    # puntatore a riga
    variabile_x = 60
    cella(ax, variabile_x, 33, 14, 5, "white", TESTO, lw=1.6, r=0.4)
    testo(ax, variabile_x + 7, 35.5, "riga", 11, MONO, TESTO, "bold")
    testo(ax, variabile_x + 7, 40.5, "int (*riga)[4]", 9.5, MONO, TESTO_TENUE)
    freccia(ax, variabile_x - 0.4, 35.5, x0 + col * cw + 0.2, 35.5, color=VERDE, lw=2.0, ms=14)
    testo(ax, variabile_x + 7, 29, "riga++ : riga successiva", 9.5, SANS, TESTO_TENUE)
    testo(ax, variabile_x + 7, 25.8, "(*riga)[j] : elemento j", 9.5, SANS, TESTO_TENUE)
    # blocco unico
    testo(ax, 2, 15, "in memoria: un unico blocco di 12 int", 11, SANS, TESTO, "bold", ha="left")
    bw = 6.2
    flat = [v for rr in valori for v in rr]
    for k, v in enumerate(flat):
        fc = "#C3E2C3" if 4 <= k < 8 else VERDE_CHIARO
        cella(ax, 2 + k * bw, 4, bw - 0.3, ch, fc, VERDE, lw=1.0, r=0.2)
        testo(ax, 2 + k * bw + bw / 2, 4 + ch / 2, str(v), 10, MONO, VERDE_SCURO, "bold")
    freccia(ax, 2 + bw / 2, -3, 2 + bw / 2, 3.6, color=VERDE, lw=1.6, ms=12)
    ax.text(2 + bw / 2 + 2, -3, "p = &m[0][0]     elemento k:  riga k / 4, colonna k % 4", fontsize=10.5,
            family=MONO, color=VERDE_SCURO, ha="left", va="center")
    salva(fig, "0504-matrice-e-puntatori.png")


# ── 4. righe di lunghezza diversa ─────────────────────────────────────
def righe_diverse():
    fig, ax = tela(8, 4.2)
    nomi = ["righe[0]", "righe[1]", "righe[2]", "righe[3]", "righe[4]"]
    dati = [[], [7], [12, 6], [9, 15, 18], [14, 10, 8, 21]]
    testo(ax, 2, 41, "const int *righe[5] = {NULL, r1, r2, r3, r4};", 11.5, MONO, VERDE_SCURO, "bold", ha="left")
    for r in range(5):
        yy = 31 - r * 7
        testo(ax, 11, yy + 2.5, nomi[r], 10, MONO, TESTO_TENUE, ha="right")
        cella(ax, 12, yy, 7, 5, "white", TESTO, lw=1.4, r=0.3)
        if r == 0:
            testo(ax, 15.5, yy + 2.5, "NULL", 9, MONO, TESTO_TENUE, "bold")
        else:
            ax.plot([15.5], [yy + 2.5], marker="o", ms=4, color=VERDE)
            freccia(ax, 15.5, yy + 2.5, 25.6, yy + 2.5, color=VERDE, lw=1.4, ms=11)
            for c, v in enumerate(dati[r]):
                cella(ax, 26 + c * 8, yy, 7.6, 5, VERDE_CHIARO, VERDE, lw=1.2, r=0.3)
                testo(ax, 26 + c * 8 + 3.8, yy + 2.5, str(v), 10.5, MONO, VERDE_SCURO, "bold")
            testo(ax, 26 + len(dati[r]) * 8 + 2, yy + 2.5, f"r{r}[{r}]", 9.5, MONO, TESTO_TENUE, ha="left")
    ax.text(2, -3, "Riga i: distanze dal paese i ai paesi 0 .. i-1.  righe[3][1] = 15 km.",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0504-righe-diverse.png")


tre_livelli()
array_puntatori()
puntatore_riga()
righe_diverse()
