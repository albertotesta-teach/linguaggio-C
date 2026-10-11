"""Diagrammi per la presentazione 0502 - Puntatori e array.

Uso: python3 diagrammi-0502.py <cartella-di-uscita>
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



def fila(ax, x0, y, w, h, valori, colori=None, font=MONO, size=15):
    """Fila di celle affiancate con un valore ciascuna."""
    for i, v in enumerate(valori):
        fc = VERDE_CHIARO if colori is None else colori[i]
        cella(ax, x0 + i * w + 0.25, y, w - 0.5, h, fc, VERDE, r=0.4)
        testo(ax, x0 + i * w + w / 2, y + h / 2, v, size, font, VERDE_SCURO, "bold")


def puntatore_su(ax, x, y_testa, y_coda, etichetta, colore=TESTO, size=12):
    """Freccia verticale dall'etichetta (sotto) alla cella (sopra)."""
    freccia(ax, x, y_coda, x, y_testa, color=colore, lw=2.0, ms=14)
    testo(ax, x, y_coda - 2.4, etichetta, size, MONO, colore, "bold")


# ── 1. p + i e fine ───────────────────────────────────────────────────
def aritmetica():
    fig, ax = tela(8, 3.8)
    x0 = 4
    w = 12
    y = 20
    h = 9
    valori = ["12", "0", "7", "25", "3"]
    testo(ax, x0, y + h + 7, "int v[5]", 14, MONO, VERDE_SCURO, "bold", ha="left")
    fila(ax, x0, y, w, h, valori)
    for i in range(5):
        testo(ax, x0 + i * w + 0.3, y + h + 2.5, f"...{0xa0 + 4 * i:x}", 10.5, MONO, TESTO, ha="left")
        testo(ax, x0 + i * w + w / 2, y - 2.2, f"v[{i}]", 10, MONO, TESTO_TENUE)
    # cella fantasma "fine"
    xf = x0 + 5 * w
    ax.add_patch(FancyBboxPatch((xf + 0.25, y), w - 0.5, h,
                                boxstyle="round,pad=0,rounding_size=0.4",
                                fc="white", ec=GRIGIO_BORDO, lw=1.6, ls=(0, (4, 3))))
    testo(ax, xf + 0.3, y + h + 2.5, "...b4", 10.5, MONO, TESTO_TENUE, ha="left")
    testo(ax, xf + w / 2, y + h / 2, "?", 15, MONO, GRIGIO_BORDO, "bold")
    # puntatori sotto
    for i, et in [(0, "p"), (1, "p + 1"), (2, "p + 2")]:
        puntatore_su(ax, x0 + i * w + w / 2, y - 4.0, y - 9, et, VERDE)
    puntatore_su(ax, xf + w / 2, y - 4.0, y - 9, "fine = p + 5", TESTO_TENUE)
    # note
    testo(ax, x0 + 2 * w + w / 2, y - 15, "*(p + 2) vale 7", 12, MONO, VERDE_SCURO)
    testo(ax, xf + w / 2, y - 15, "non si dereferenzia", 10.5, SANS, TESTO_TENUE)
    ax.text(x0, -1, "Ogni passo p + 1 avanza di sizeof(int) = 4 byte: ...a0, ...a4, ...a8 (indirizzi esadecimali abbreviati).",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0502-aritmetica.png")


# ── 2. due puntatori agli estremi ─────────────────────────────────────
def due_puntatori():
    fig, ax = tela(8, 3.8)
    x0 = 4
    w = 14.5
    y = 14
    h = 9
    valori = ["52", "38", "61", "27"]
    colori = [VERDE_CHIARO, "white", "white", VERDE_CHIARO]
    testo(ax, x0, y + h + 13, "inverti(&distanze[0], &distanze[0] + 4)", 12.5, MONO, VERDE_SCURO, "bold", ha="left")
    fila(ax, x0, y, w, h, valori, colori)
    # arco di scambio sopra le celle
    ax.add_patch(FancyArrowPatch((x0 + w / 2, y + h + 1), (x0 + 3 * w + w / 2, y + h + 1),
                                 connectionstyle="arc3,rad=-0.22", arrowstyle="<|-|>",
                                 mutation_scale=14, color=VERDE, lw=1.8))
    testo(ax, x0 + 2 * w, y + h + 8.6, "scambio", 11, SANS, VERDE, "bold")
    puntatore_su(ax, x0 + w / 2, y - 1, y - 8, "sinistra", VERDE)
    puntatore_su(ax, x0 + 3 * w + w / 2, y - 1, y - 8, "destra", VERDE)
    freccia(ax, x0 + w / 2 + 6, y - 10.4, x0 + w + w / 2 - 1, y - 10.4, color=TESTO_TENUE, lw=1.4, ms=11)
    freccia(ax, x0 + 3 * w + w / 2 - 6, y - 10.4, x0 + 2 * w + w / 2 + 1, y - 10.4, color=TESTO_TENUE, lw=1.4, ms=11)
    testo(ax, x0 + w + w / 2 + 2, y - 13.5, "sinistra++", 10, MONO, TESTO_TENUE)
    testo(ax, x0 + 2 * w + w / 2 - 2, y - 13.5, "destra--", 10, MONO, TESTO_TENUE)
    ax.text(x0, -4, "Si scambiano *sinistra e *destra, poi i puntatori si avvicinano finché sinistra < destra.",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0502-due-puntatori.png")


# ── 3. sottoarray ─────────────────────────────────────────────────────
def sottoarray():
    fig, ax = tela(8, 3.8)
    x0 = 4
    w = 10
    y = 18
    h = 9
    valori = ["640", "585", "710", "690", "980", "1420", "1260"]
    giorni = ["lun", "mar", "mer", "gio", "ven", "sab", "dom"]
    colori = [VERDE_CHIARO] * 5 + ["#C3E2C3"] * 2
    testo(ax, x0, y + h + 6, "int incassi[7]", 13, MONO, VERDE_SCURO, "bold", ha="left")
    fila(ax, x0, y, w, h, valori, colori, size=12.5)
    for i, g in enumerate(giorni):
        testo(ax, x0 + i * w + w / 2, y + h + 2.2, g, 10.5, SANS, TESTO_TENUE)
    # parentesi feriali
    yb = y - 2.5
    ax.plot([x0 + 0.4, x0 + 0.4, x0 + 5 * w - 0.4, x0 + 5 * w - 0.4], [yb + 1.2, yb, yb, yb + 1.2], color=VERDE, lw=1.6)
    testo(ax, x0 + 2.5 * w, yb - 3.2, "totale(incassi, 5)", 12, MONO, VERDE, "bold")
    ax.plot([x0 + 5 * w + 0.4, x0 + 5 * w + 0.4, x0 + 7 * w - 0.4, x0 + 7 * w - 0.4], [yb + 1.2, yb, yb, yb + 1.2], color=VERDE_SCURO, lw=1.6)
    testo(ax, x0 + 6 * w, yb - 3.2, "totale(incassi + 5, 2)", 12, MONO, VERDE_SCURO, "bold")
    ax.text(x0, 4, "La funzione riceve solo un indirizzo e un numero di elementi: lavora su qualsiasi parte dell'array.",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    ax.text(x0, 0.5, "Dentro totale(incassi + 5, 2) gli indici ripartono da 0: v[0] è il sabato, v[1] la domenica.",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0502-sottoarray.png")


# ── 4. scorrere una stringa ───────────────────────────────────────────
def stringa():
    fig, ax = tela(8, 3.8)
    x0 = 4
    w = 9.5
    y = 18
    h = 9
    car = ["'T'", "'o'", "'r'", "'i'", "'n'", "'o'", "'\\0'"]
    colori = [VERDE_CHIARO] * 6 + [GRIGIO]
    testo(ax, x0, y + h + 9, 'char citta[] = "Torino";', 13, MONO, VERDE_SCURO, "bold", ha="left")
    fila(ax, x0, y, w, h, car, colori, size=12.5)
    for i in range(7):
        testo(ax, x0 + i * w + w / 2, y + h + 2.5, f"...{0xf0 + i:x}", 10, MONO, TESTO)
    puntatore_su(ax, x0 + w / 2, y - 1, y - 8, "citta", TESTO_TENUE)
    puntatore_su(ax, x0 + 6 * w + w / 2, y - 1, y - 8, "p", VERDE)
    freccia(ax, x0 + w + 1, y - 5, x0 + 6 * w - 1, y - 5, color=VERDE, lw=1.6, ms=13)
    testo(ax, x0 + 3.5 * w, y - 2.6, "p++ finché *p != '\\0'", 11, MONO, VERDE, "bold")
    testo(ax, x0 + 3.5 * w, y - 12, "lunghezza = p - citta = 6", 12.5, MONO, VERDE_SCURO, "bold")
    ax.text(x0, -5, "Un char occupa 1 byte: gli indirizzi (esadecimali) crescono di 1, da ...f0 a ...f6.",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0502-stringa.png")


# ── 5. lettura e scrittura sulla stessa stringa ───────────────────────
def lettura_scrittura():
    fig, ax = tela(8, 4.4)
    x0 = 4
    w = 7.6
    h = 7.5
    prima = list("  Ma   ri")
    y1 = 30
    testo(ax, x0, y1 + h + 3.5, "prima:  \"  Ma   ri\"", 11.5, MONO, TESTO_TENUE, ha="left")
    colori = [GRIGIO if c == " " else VERDE_CHIARO for c in prima]
    fila(ax, x0, y1, w, h, ["·" if c == " " else c for c in prima], colori, size=13)
    y2 = 12
    testo(ax, x0, y2 + h + 3.5, "durante la correzione, nello stesso array", 11.5, SANS, TESTO_TENUE, ha="left")
    stato = ["M", "a", " ", "r", "a", " ", " ", "r", "i"]
    colori2 = [VERDE_CHIARO] * 4 + [GRIGIO] * 5
    fila(ax, x0, y2, w, h, ["·" if c == " " else c for c in stato], colori2, size=13)
    puntatore_su(ax, x0 + 4 * w + w / 2, y2 - 1, y2 - 7.5, "scrittura", VERDE)
    puntatore_su(ax, x0 + 8 * w + w / 2, y2 - 1, y2 - 7.5, "lettura", TESTO)
    ax.text(x0, -1.5, "· = spazio.  Le celle verdi sono il testo già corretto (\"Ma r\"); il resto verrà sovrascritto.",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    ax.text(x0, -5, "scrittura non supera mai lettura: si copia solo verso sinistra.",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0502-lettura-scrittura.png")


aritmetica()
due_puntatori()
sottoarray()
stringa()
lettura_scrittura()
