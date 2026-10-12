"""Diagrammi per la presentazione 0605 - Enum.

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


# ── 1. costanti e valori ──────────────────────────────────────────────
def costanti():
    fig, ax = tela(9, 4.4)
    testo(ax, 2, 42, "typedef enum { LUNEDI, MARTEDI, ..., DOMENICA } Giorno;", 10.5, MONO,
          VERDE_SCURO, "bold", ha="left")
    nomi = ["LUNEDI", "MARTEDI", "MERCOLEDI", "GIOVEDI", "VENERDI", "SABATO", "DOMENICA"]
    w = 12
    for i, n in enumerate(nomi):
        x = 2 + i * w
        cella(ax, x, 26, w - 0.8, 9, ARANCIO if n == "VENERDI" else VERDE_CHIARO, VERDE, lw=1.3, r=0.4)
        testo(ax, x + w / 2 - 0.4, 32.5, n, 8.2, MONO, VERDE_SCURO, "bold")
        testo(ax, x + w / 2 - 0.4, 28.5, str(i), 11, MONO, TESTO, "bold")
    testo(ax, 2, 22.5, "Giorno oggi = VENERDI;   /* vale 4 */", 9.5, MONO, ARANCIO_SCURO, "bold",
          ha="left")
    testo(ax, 2, 15, "typedef enum { BASSA = 1, MEDIA, ALTA, URGENTE = 10 } Priorita;", 10.5, MONO,
          VERDE_SCURO, "bold", ha="left")
    valori = [("BASSA", 1), ("MEDIA", 2), ("ALTA", 3), ("URGENTE", 10)]
    x0 = 4
    scala = 7.5
    ax.plot([x0, x0 + 10.5 * scala], [3, 3], color=GRIGIO_BORDO, lw=1.5)
    for v in range(0, 11):
        ax.plot([x0 + v * scala, x0 + v * scala], [2.2, 3.8], color=GRIGIO_BORDO, lw=1)
        testo(ax, x0 + v * scala, 0, str(v), 8.5, MONO, TESTO_TENUE)
    for n, v in valori:
        cella(ax, x0 + v * scala - 3.4, 5.5, 6.8, 4.5, VERDE_CHIARO if v != 10 else ARANCIO, VERDE, lw=1.2,
              r=0.3)
        testo(ax, x0 + v * scala, 7.75, n, 6.8, MONO, VERDE_SCURO, "bold")
    testo(ax, x0 + 6.5 * scala, 8, "salto: URGENTE = 10", 9, SANS, ARANCIO_SCURO, "bold")
    salva(fig, "0605-costanti-e-valori.png")


# ── 2. enum come indice ───────────────────────────────────────────────
def indice():
    fig, ax = tela(9, 4.6)
    testo(ax, 2, 45, "typedef enum { VERDE, GIALLO, ROSSO, NUM_COLORI } Colore;", 10.5, MONO,
          VERDE_SCURO, "bold", ha="left")
    testo(ax, 2, 40, "int durata[NUM_COLORI] = {[VERDE] = 40, [GIALLO] = 5, [ROSSO] = 45};", 9.5, MONO,
          TESTO, ha="left")
    colori = [("VERDE", "40", "#C3E2C3"), ("GIALLO", "5", "#F8E7A8"), ("ROSSO", "45", "#F4C2B8")]
    w = 16
    x0 = 10
    y = 20
    for i, (n, v, fc) in enumerate(colori):
        x = x0 + i * w
        cella(ax, x, y, w - 0.8, 10, fc, VERDE, lw=1.4, r=0.4)
        testo(ax, x + w / 2 - 0.4, y + 5, v, 13, MONO, VERDE_SCURO, "bold")
        testo(ax, x + w / 2 - 0.4, y + 13, f"durata[{n}]", 9, MONO, TESTO_TENUE)
        testo(ax, x + w / 2 - 0.4, y - 3, f"{n} = {i}", 9, MONO, TESTO)
    xf = x0 + 3 * w
    ax.plot([xf, xf], [y - 6, y + 16], color=ARANCIO_SCURO, lw=1.5, ls="--")
    testo(ax, xf + 1.5, y + 5, "NUM_COLORI = 3\nquanti sono i colori,\nnon un colore", 9, MONO,
          ARANCIO_SCURO, "bold", ha="left")
    # ciclo
    for i in range(3):
        xa = x0 + i * w + w / 2
        xb = x0 + ((i + 1) % 3) * w + w / 2
        rad = -0.35 if i < 2 else 0.25
        freccia(ax, xa + (2 if i < 2 else -2), y - 6, xb - (2 if i < 2 else -2), y - 6, color=VERDE,
                lw=1.6, rad=rad if i < 2 else -0.25, ms=12)
    testo(ax, x0 + 1.5 * w, 3, "colore = (colore + 1) % NUM_COLORI;", 10, MONO, VERDE_SCURO, "bold")
    salva(fig, "0605-enum-come-indice.png")


# ── 3. macchina a stati ───────────────────────────────────────────────
def macchina():
    fig, ax = tela(9, 6.0)
    pos = {"CHIUSA": (13, 27), "IN_APERTURA": (45, 47), "APERTA": (77, 27), "IN_CHIUSURA": (45, 7)}
    r = 9
    for n, (x, y) in pos.items():
        fc = ARANCIO if n == "CHIUSA" else VERDE_CHIARO
        ax.add_patch(Circle((x, y), r, fc=fc, ec=VERDE, lw=1.8))
        testo(ax, x, y, n, 8, MONO, VERDE_SCURO, "bold")

    def arco(a, b, etichetta, rad, dx=0, dy=0):
        (x1, y1), (x2, y2) = pos[a], pos[b]
        ang = math.atan2(y2 - y1, x2 - x1)
        p1 = (x1 + r * math.cos(ang + rad), y1 + r * math.sin(ang + rad))
        p2 = (x2 - r * math.cos(ang - rad), y2 - r * math.sin(ang - rad))
        freccia(ax, p1[0], p1[1], p2[0], p2[1], color=VERDE, lw=1.8, rad=rad, ms=14)
        testo(ax, (p1[0] + p2[0]) / 2 + dx, (p1[1] + p2[1]) / 2 + dy, etichetta, 8.5, SANS,
              ARANCIO_SCURO, "bold")

    arco("CHIUSA", "IN_APERTURA", "persona", -0.25, -6, 3)
    arco("IN_APERTURA", "APERTA", "fine corsa", -0.25, 7, 3)
    arco("APERTA", "IN_CHIUSURA", "tempo scaduto", -0.25, 9, -3)
    arco("IN_CHIUSURA", "CHIUSA", "fine corsa", -0.25, -7, -3)
    arco("IN_CHIUSURA", "IN_APERTURA", "persona", 0.0, 6, 0)
    testo(ax, 2, -6, "Gli eventi non disegnati lasciano la porta nello stato in cui si trova.", 9.5,
          SANS, TESTO, ha="left")
    salva(fig, "0605-macchina-a-stati.png")


# ── 4. tabella delle transizioni ──────────────────────────────────────
def tabella():
    fig, ax = tela(9, 4.6)
    eventi = ["PERSONA", "FINE_CORSA", "TEMPO_SCADUTO"]
    stati = ["CHIUSA", "IN_APERTURA", "APERTA", "IN_CHIUSURA"]
    celle = [["IN_APERTURA", "CHIUSA", "CHIUSA"],
             ["IN_APERTURA", "APERTA", "IN_APERTURA"],
             ["APERTA", "APERTA", "IN_CHIUSURA"],
             ["IN_APERTURA", "CHIUSA", "IN_CHIUSURA"]]
    x0 = 22
    w = 20
    h = 6.5
    ytop = 36
    for j, e in enumerate(eventi):
        testo(ax, x0 + j * w + w / 2, ytop + 4.5, e, 8.8, MONO, TESTO_TENUE, "bold")
    for i, s in enumerate(stati):
        y = ytop - (i + 1) * h
        testo(ax, x0 - 2, y + h / 2, f"[{s}]", 8.8, MONO, TESTO_TENUE, "bold", ha="right")
        for j in range(3):
            evid = (s == "APERTA" and j == 2)
            stesso = celle[i][j] == s
            fc = ARANCIO if evid else ("white" if stesso else VERDE_CHIARO)
            cella(ax, x0 + j * w, y, w - 0.6, h - 0.6, fc, VERDE if not stesso else GRIGIO_BORDO,
                  lw=1.6 if evid else 1.0, r=0.3)
            testo(ax, x0 + j * w + w / 2 - 0.3, y + h / 2 - 0.3, celle[i][j], 8.5, MONO,
                  TESTO_TENUE if stesso else VERDE_SCURO, "bold" if not stesso else "normal")
    testo(ax, 2, 3, "stato = transizioni[APERTA][TEMPO_SCADUTO];   /* IN_CHIUSURA */", 10, MONO,
          ARANCIO_SCURO, "bold", ha="left")
    testo(ax, 2, -2, "Le celle bianche lasciano lo stato invariato.", 9.5, SANS, TESTO, ha="left")
    salva(fig, "0605-tabella-transizioni.png")


costanti()
indice()
macchina()
tabella()
