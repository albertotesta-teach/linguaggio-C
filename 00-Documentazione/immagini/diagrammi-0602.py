"""Diagrammi per la presentazione 0602 - Struct.

Uso: python3 diagrammi-0602.py <cartella-di-uscita>
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




PADDING = "#E6E6E6"


def byte_riga(ax, x0, y, n, w, h, colori, etichette=None):
    for i in range(n):
        cella(ax, x0 + i * w, y, w - 0.3, h, colori[i][0], colori[i][1], lw=1.0, r=0.2)
        if etichette and etichette[i]:
            testo(ax, x0 + i * w + w / 2 - 0.15, y + h / 2, etichette[i], 8.5, MONO, VERDE_SCURO, "bold")


# ── 1. una struct in memoria ──────────────────────────────────────────
def struct_in_memoria():
    fig, ax = tela(8, 3.6)
    testo(ax, 2, 35, "struct studente s;", 12, MONO, VERDE_SCURO, "bold", ha="left")
    x0 = 2
    y = 18
    h = 8
    campi = [("nome", "char[20]", 20, "\"Giulia Ferri\""), ("classe", "char[4]", 4, "\"3B\""), ("media", "double", 8, "7.8")]
    scala = 2.3
    x = x0
    colori = [VERDE_CHIARO, "#C3E2C3", VERDE_CHIARO]
    for k, (nome, tipo, byte, valore) in enumerate(campi):
        w = byte * scala
        cella(ax, x, y, w - 0.4, h, colori[k], VERDE, lw=1.6, r=0.4)
        testo(ax, x + w / 2, y + h / 2, valore, 11, MONO, VERDE_SCURO, "bold")
        testo(ax, x + w / 2, y + h + 2.8, f"s.{nome}", 11.5, MONO, TESTO, "bold")
        testo(ax, x + w / 2, y - 2.6, f"{tipo}, {byte} byte", 9, MONO, TESTO_TENUE)
        x = x + w
    # graffa totale
    ax.plot([x0, x0, x - 0.4, x - 0.4], [y - 6, y - 7.5, y - 7.5, y - 6], color=TESTO_TENUE, lw=1.2)
    testo(ax, (x0 + x) / 2, y - 10, "sizeof(struct studente) = 32 byte: i campi uno dopo l'altro", 10, SANS, TESTO_TENUE)
    salva(fig, "0602-struct-in-memoria.png")


# ── 2. copia con assegnamento ─────────────────────────────────────────
def pagella(ax, x, y, nome_var, voti, evidenzia=None):
    testo(ax, x, y + 15, nome_var, 11.5, MONO, VERDE_SCURO, "bold", ha="left")
    cella(ax, x, y, 34, 12, "white", VERDE, lw=1.8, r=0.6)
    testo(ax, x + 2, y + 9, "nome   \"Elena Costa\"", 9.5, MONO, TESTO, ha="left")
    testo(ax, x + 2, y + 5.5, "voti", 9.5, MONO, TESTO, ha="left")
    for i, v in enumerate(voti):
        fc = "#F8D9A8" if evidenzia is not None and i in evidenzia else VERDE_CHIARO
        cella(ax, x + 9 + i * 5.5, y + 2, 5, 5, fc, VERDE, lw=1.0, r=0.2)
        testo(ax, x + 9 + i * 5.5 + 2.5, y + 4.5, str(v), 10, MONO, VERDE_SCURO, "bold")


def copia():
    fig, ax = tela(9, 4.2)
    testo(ax, 2, 41, "simulazione = primo_quadrimestre;   /* copia di tutti i campi, array compreso */", 10, MONO, VERDE_SCURO, "bold", ha="left")
    pagella(ax, 2, 18, "primo_quadrimestre", [6, 5, 7, 8])
    pagella(ax, 44, 18, "simulazione", [6, 6, 8, 8], evidenzia=[1, 2])
    freccia(ax, 36.5, 24, 43.5, 24, color=VERDE, lw=2.4, ms=16)
    testo(ax, 40, 27, "=", 14, MONO, VERDE_SCURO, "bold")
    testo(ax, 61, 13, "simulazione.voti[1] = 6;  simulazione.voti[2] = 8;", 9, MONO, TESTO_TENUE)
    testo(ax, 19, 13, "non cambia", 9.5, SANS, TESTO_TENUE)
    testo(ax, 2, 4, "Dopo la copia le due struct sono indipendenti.", 10.5, SANS, TESTO, ha="left")
    testo(ax, 2, 0, "Con due array:  w = v;  non compila.", 10.5, SANS, TESTO, ha="left")
    salva(fig, "0602-copia-struct.png")


# ── 3. padding ────────────────────────────────────────────────────────
def padding():
    fig, ax = tela(8, 4.0)
    w = 5.6
    h = 6
    def riga(y, titolo, campi, totale):
        testo(ax, 2, y + h + 7, titolo, 11, MONO, VERDE_SCURO, "bold", ha="left")
        x = 2
        for nome, n, tipo in campi:
            larghezza = n * w
            if tipo == "pad":
                cella(ax, x, y, larghezza - 0.3, h, PADDING, GRIGIO_BORDO, lw=0.8, r=0.2)
                for i in range(n):
                    ax.plot([x + i * w + 0.5, x + (i + 1) * w - 0.8], [y + 0.5, y + h - 0.5],
                            color=GRIGIO_BORDO, lw=0.8)
            else:
                cella(ax, x, y, larghezza - 0.3, h, VERDE_CHIARO, VERDE, lw=1.4, r=0.3)
                for i in range(1, n):
                    ax.plot([x + i * w - 0.15, x + i * w - 0.15], [y + 0.6, y + h - 0.6],
                            color=VERDE, lw=0.5, ls=":")
                testo(ax, x + larghezza / 2 - 0.15, y + h / 2, tipo, 9.5, MONO, VERDE_SCURO, "bold")
                testo(ax, x + larghezza / 2 - 0.15, y + h + 2.2, nome, 9.5, MONO, TESTO)
            x = x + larghezza
        testo(ax, x + 2, y + h / 2, totale, 10.5, MONO, TESTO, "bold", ha="left")
        for k in range(0, int(round((x - 2) / w)) + 1, 4):
            testo(ax, 2 + k * w, y - 2.2, str(k), 8.5, MONO, TESTO_TENUE, ha="left")
    riga(24, "typedef struct { char stanza; int valore; char unita; } Lettura;",
         [("stanza", 1, "char"), ("", 3, "pad"), ("valore", 4, "int"), ("unita", 1, "char"), ("", 3, "pad")], "12 byte")
    riga(4, "typedef struct { int valore; char stanza; char unita; } LetturaCompatta;",
         [("valore", 4, "int"), ("stanza", 1, "char"), ("unita", 1, "char"), ("", 2, "pad")], "8 byte")
    cella(ax, 50, -5, 4, 3, PADDING, GRIGIO_BORDO, lw=0.8, r=0.2)
    testo(ax, 55.5, -3.5, "padding: byte non usati", 9.5, SANS, TESTO_TENUE, ha="left")
    salva(fig, "0602-padding.png")


# ── 4. array di struct ────────────────────────────────────────────────
def array_struct():
    fig, ax = tela(9, 4.6)
    testo(ax, 2, 45, "Studente classe[5];", 12, MONO, VERDE_SCURO, "bold", ha="left")
    righe = [("Bianchi Sara", "16", "7.8"), ("Colombo Luca", "17", "6.2"), ("Esposito Anna", "16", "8.4"),
             ("Ferrari Marco", "16", "5.9"), ("Galli Irene", "17", "7.1")]
    colonne = [(".nome", 28), (".eta", 10), (".media", 12)]
    x0 = 18
    y0 = 33
    h = 5.5
    x = x0
    for nome, w in colonne:
        testo(ax, x + w / 2, y0 + h + 2.5, nome, 10, MONO, TESTO_TENUE, "bold")
        x = x + w
    for r, valori in enumerate(righe):
        y = y0 - r * (h + 0.6)
        x = x0
        for c, (nome, w) in enumerate(colonne):
            evid = r == 2 and c == 2
            fc = "#F8D9A8" if evid else ("#C3E2C3" if r == 2 else VERDE_CHIARO)
            cella(ax, x, y, w - 0.4, h, fc, VERDE, lw=1.6 if evid else 1.0, r=0.3)
            testo(ax, x + w / 2, y + h / 2, valori[c], 10, MONO, VERDE_SCURO, "bold")
            x = x + w
        testo(ax, x0 - 2, y + h / 2, f"classe[{r}]", 10, MONO, TESTO_TENUE, ha="right")
    freccia(ax, 75, 22.5, 68.6, 22.5, color="#C77700", lw=2, ms=14)
    testo(ax, 76, 22.5, "classe[2].media", 10.5, MONO, "#9A5B00", "bold", ha="left")
    testo(ax, 2, -1, "Ogni elemento è una struct completa: i dati dello stesso studente restano insieme.",
          10.5, SANS, TESTO, ha="left")
    salva(fig, "0602-array-di-struct.png")


struct_in_memoria()
copia()
padding()
array_struct()
