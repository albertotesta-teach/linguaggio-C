"""Diagrammi per la presentazione 0601 - Typedef.

Uso: python3 diagrammi-0601.py <cartella-di-uscita>
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




def etichetta_tipo(ax, x, y, w, h, nome, verde=True):
    cella(ax, x, y, w, h, VERDE_CHIARO if verde else "white", VERDE if verde else TESTO, lw=2.0, r=0.8)
    testo(ax, x + w / 2, y + h / 2, nome, 13, MONO, VERDE_SCURO if verde else TESTO, "bold")


# ── 1. un nome nuovo, lo stesso tipo ──────────────────────────────────
def alias():
    fig, ax = tela(8, 4.0)
    testo(ax, 2, 37, "typedef double Euro;", 11.5, MONO, VERDE_SCURO, "bold", ha="left")
    testo(ax, 2, 33, "typedef double Chilometri;", 11.5, MONO, VERDE_SCURO, "bold", ha="left")
    # nomi a sinistra
    etichetta_tipo(ax, 4, 18, 18, 6, "Euro", verde=False)
    etichetta_tipo(ax, 4, 6, 18, 6, "Chilometri", verde=False)
    # tipo reale
    etichetta_tipo(ax, 46, 11, 20, 8, "double")
    testo(ax, 56, 7.5, "8 byte, virgola mobile", 9.5, SANS, TESTO_TENUE)
    freccia(ax, 22.4, 21, 45.6, 16.5, color=VERDE, lw=2.0, ms=15)
    freccia(ax, 22.4, 9, 45.6, 13.5, color=VERDE, lw=2.0, ms=15)
    testo(ax, 34, 24, "nome", 9.5, SANS, TESTO_TENUE)
    testo(ax, 34, 4, "nome", 9.5, SANS, TESTO_TENUE)
    testo(ax, 2, -4, "Due nomi per lo stesso tipo: il compilatore accetta Euro dove serve Chilometri.",
          10.5, SANS, TESTO, ha="left")
    salva(fig, "0601-alias.png")


# ── 2. tipi array ─────────────────────────────────────────────────────
def tipi_array():
    fig, ax = tela(8, 4.2)
    testo(ax, 2, 40, "typedef char Targa[8];", 11.5, MONO, VERDE_SCURO, "bold", ha="left")
    testo(ax, 2, 35.5, "Targa auto_preside = \"GA482KM\";", 10.5, MONO, TESTO, ha="left")
    cw = 7.4
    for i, c in enumerate("GA482KM") :
        cella(ax, 2 + i * cw, 24, cw - 0.4, 6, VERDE_CHIARO, VERDE, lw=1.2, r=0.3)
        testo(ax, 2 + i * cw + cw / 2 - 0.2, 27, c, 12, MONO, VERDE_SCURO, "bold")
        testo(ax, 2 + i * cw + cw / 2 - 0.2, 22, f"[{i}]", 8.5, MONO, TESTO_TENUE)
    cella(ax, 2 + 7 * cw, 24, cw - 0.4, 6, GRIGIO, GRIGIO_BORDO, lw=1.2, r=0.3)
    testo(ax, 2 + 7 * cw + cw / 2 - 0.2, 27, "\\0", 11, MONO, TESTO_TENUE)
    testo(ax, 2 + 7 * cw + cw / 2 - 0.2, 22, "[7]", 8.5, MONO, TESTO_TENUE)
    testo(ax, 64, 27, "sizeof(Targa) = 8", 10, MONO, TESTO_TENUE, ha="left")

    testo(ax, 2, 14, "typedef int Settimana[7];", 11.5, MONO, VERDE_SCURO, "bold", ha="left")
    giorni = ["L", "M", "M", "G", "V", "S", "D"]
    valori = [84, 91, 88, 79, 73, 12, 0]
    for i in range(7):
        cella(ax, 2 + i * cw, 1, cw - 0.4, 6, VERDE_CHIARO, VERDE, lw=1.2, r=0.3)
        testo(ax, 2 + i * cw + cw / 2 - 0.2, 4, str(valori[i]), 11, MONO, VERDE_SCURO, "bold")
        testo(ax, 2 + i * cw + cw / 2 - 0.2, 9, giorni[i], 9, SANS, TESTO_TENUE)
    testo(ax, 56, 4, "sizeof(Settimana) = 28", 10, MONO, TESTO_TENUE, ha="left")
    testo(ax, 2, -5, "Il nome contiene anche la dimensione: Targa è un array di 8 char.",
          10.5, SANS, TESTO, ha="left")
    salva(fig, "0601-tipi-array.png")


# ── 3. un tipo costruito su un altro ──────────────────────────────────
def mese_di_settimane():
    fig, ax = tela(8, 4.6)
    testo(ax, 2, 44, "typedef int Settimana[6];", 11, MONO, VERDE_SCURO, "bold", ha="left")
    testo(ax, 2, 40, "typedef Settimana Mese[4];     /* come int[4][6] */", 11, MONO, VERDE_SCURO, "bold", ha="left")
    dati = [[34, 41, 28, 39, 45, 18], [31, 44, 30, 42, 47, 22], [29, 39, 33, 40, 51, 15], [36, 46, 27, 43, 49, 20]]
    cw = 6.4
    x0 = 18
    for r in range(4):
        yy = 28 - r * 7
        fc = "#C3E2C3" if r == 2 else VERDE_CHIARO
        cella(ax, x0 - 0.8, yy - 0.8, 6 * cw + 0.8, 6.6, "white", VERDE_SCURO if r == 2 else GRIGIO_BORDO, lw=1.6 if r == 2 else 1.0, r=0.5)
        for c in range(6):
            cella(ax, x0 + c * cw, yy, cw - 0.4, 5, fc, VERDE, lw=1.0, r=0.3)
            testo(ax, x0 + c * cw + cw / 2 - 0.2, yy + 2.5, str(dati[r][c]), 10.5, MONO, VERDE_SCURO, "bold")
        testo(ax, x0 - 2, yy + 2.5, f"presenze[{r}]", 9.5, MONO, TESTO_TENUE, ha="right")
    # funzione
    cella(ax, 62, 13, 16, 6, "white", TESTO, lw=1.6, r=0.5)
    testo(ax, 70, 16, "totale(s)", 11, MONO, TESTO, "bold")
    freccia(ax, x0 + 6 * cw + 0.4, 16.5, 61.6, 16, color=VERDE, lw=2.0, ms=14)
    testo(ax, 2, -1, "int totale(const Settimana s);", 10, MONO, TESTO_TENUE, ha="left")
    testo(ax, 2, -5, "Ogni riga di un Mese è una Settimana: totale(presenze[2]) somma la terza settimana.",
          10.5, SANS, TESTO, ha="left")
    salva(fig, "0601-mese-di-settimane.png")


# ── 4. tabella di puntatori a funzione ────────────────────────────────
def tabella_funzioni():
    fig, ax = tela(8, 4.8)
    testo(ax, 2, 46, "typedef double (*Operazione)(double, double);", 11, MONO, VERDE_SCURO, "bold", ha="left")
    testo(ax, 2, 42, "Operazione tabella[4] = {somma, differenza, prodotto, quoziente};", 9.5, MONO, TESTO, ha="left")
    simboli = "+-*/"
    nomi = ["somma", "differenza", "prodotto", "quoziente"]
    corpi = ["a + b", "a - b", "a * b", "a / b"]
    for i in range(4):
        yy = 30 - i * 8
        # simbolo
        cella(ax, 4, yy, 5, 5.5, GRIGIO, GRIGIO_BORDO, lw=1.0, r=0.3)
        testo(ax, 6.5, yy + 2.75, simboli[i], 13, MONO, TESTO, "bold")
        testo(ax, 3, yy + 2.75, f"[{i}]", 9, MONO, TESTO_TENUE, ha="right")
        # elemento della tabella
        cella(ax, 16, yy, 9, 5.5, "white", TESTO, lw=1.5, r=0.3)
        ax.plot([20.5], [yy + 2.75], marker="o", ms=4.5, color=VERDE)
        freccia(ax, 9.4, yy + 2.75, 15.6, yy + 2.75, color=GRIGIO_BORDO, lw=1.2, ms=10)
        freccia(ax, 20.5, yy + 2.75, 39.6, yy + 2.75, color=VERDE, lw=1.8, ms=13)
        # funzione
        cella(ax, 40, yy, 36, 5.5, VERDE_CHIARO, VERDE, lw=1.4, r=0.4)
        testo(ax, 42, yy + 2.75, f"double {nomi[i]}(double a, double b)", 9.5, MONO, VERDE_SCURO, "bold", ha="left")
    testo(ax, 6.5, 38, "simboli", 9.5, SANS, TESTO_TENUE)
    testo(ax, 20.5, 38, "tabella", 9.5, SANS, TESTO_TENUE)
    testo(ax, 58, 38, "funzioni", 9.5, SANS, TESTO_TENUE)
    testo(ax, 2, -1, "La posizione del simbolo in \"+-*/\" è l'indice:  tabella[k](a, b)",
          10.5, SANS, TESTO, ha="left")
    salva(fig, "0601-tabella-di-funzioni.png")


alias()
tipi_array()
mese_di_settimane()
tabella_funzioni()
