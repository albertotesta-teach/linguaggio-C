"""Diagrammi per la presentazione 0703 - array dinamici.

Uso: python3 diagrammi-0703.py <cartella-di-uscita>
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



# ── 1. lunghezza e capacita ───────────────────────────────────────────
def lunghezza_capacita():
    fig, ax = tela(9, 3.8)
    cella(ax, 2, 8, 22, 27, GRIGIO, GRIGIO_BORDO, lw=1.4)
    testo(ax, 13, 32, "Vettore", 10, SANS, TESTO_TENUE, "bold")
    for k, (nome, val) in enumerate([("dati", ""), ("n", "4"), ("capacita", "8")]):
        y = 26 - k * 6.5
        testo(ax, 4, y, nome, 9.5, MONO, VERDE_SCURO, "bold", ha="left")
        cella(ax, 16.5, y - 2.2, 5.5, 4.4, "white", VERDE, lw=1.2, r=0.3)
        testo(ax, 19.25, y, val, 9.5, MONO, VERDE_SCURO, "bold")
    blocco(ax, 30, 23, ["12", "30", "0", "25", "", "", "", ""],
           [VERDE_CHIARO] * 4 + ["white"] * 4, w=7)
    freccia(ax, 20, 26, 29.8, 26, color=ARANCIO_SCURO, lw=1.8, ms=13)
    ax.plot([30, 57.5], [21, 21], color=VERDE, lw=1.6)
    testo(ax, 43.75, 18.5, "n = 4  elementi usati", 9, SANS, VERDE_SCURO, "bold")
    ax.plot([30, 85.5], [15, 15], color=ARANCIO_SCURO, lw=1.6)
    testo(ax, 57.75, 12.5, "capacita = 8  posti allocati", 9, SANS, ARANCIO_SCURO, "bold")
    testo(ax, 71.75, 31.5, "posti liberi", 9, SANS, TESTO_TENUE)
    testo(ax, 2, 2, "Sempre 0 <= n <= capacita. Con n < capacita aggiungere costa una scrittura:",
          9, SANS, TESTO, ha="left")
    testo(ax, 2, -2.5, "dati[n] = valore;  n++;", 9, MONO, VERDE_SCURO, "bold", ha="left")
    salva(fig, "0703-lunghezza-e-capacita.png")


# ── 2. crescita a raddoppio ───────────────────────────────────────────
def raddoppio():
    fig, ax = tela(9, 4.6)
    testo(ax, 2, 45, "aggiungi con il vettore pieno: realloc a 2 * capacita", 10.5, SANS, VERDE_SCURO,
          "bold", ha="left")
    righe = [(2, 2), (4, 3), (8, 5), (16, 9)]
    for k, (cap, n) in enumerate(righe):
        y = 33 - k * 8.5
        testo(ax, 2, y + 2.5, f"capacita {cap:2d}", 9, MONO, TESTO, ha="left")
        w = 3.6
        for j in range(cap):
            fc = VERDE_CHIARO if j < n - 1 or k == 0 else (ARANCIO if j == n - 1 else "white")
            cella(ax, 20 + j * w, y, w - 0.4, 5, fc, VERDE, lw=1.0, r=0.2)
        if k > 0:
            testo(ax, 20 + cap * w + 2, y + 2.5, "realloc", 8.5, SANS, ARANCIO_SCURO, "bold", ha="left")
    testo(ax, 2, 1, "100000 aggiunte:   +16 alla volta -> 6249 realloc     x2 -> 13 realloc",
          9, MONO, VERDE_SCURO, "bold", ha="left")
    testo(ax, 2, -3.5, "In arancio l'elemento appena aggiunto che ha fatto crescere il blocco.", 9, SANS,
          TESTO_TENUE, ha="left")
    salva(fig, "0703-crescita-a-raddoppio.png")


# ── 3. inserire e rimuovere ───────────────────────────────────────────
def inserire_rimuovere():
    fig, ax = tela(9, 5.6)
    w = 7
    testo(ax, 2, 52, "inserisci(v, 2, 50): spostamento a destra, dall'ultimo", 10, SANS, VERDE_SCURO,
          "bold", ha="left")
    blocco(ax, 6, 36, ["10", "20", "30", "40", ""], [VERDE_CHIARO] * 4 + ["white"], w=w)
    blocco(ax, 52, 36, ["10", "20", "50", "30", "40"], [VERDE_CHIARO] * 2 + [ARANCIO] + [VERDE_CHIARO] * 2,
           w=4.5, size=9)
    for k, (da, a) in enumerate([(3, 4), (2, 3)]):
        freccia(ax, 6 + da * w + 3, 42.5, 6 + a * w + 3, 42.5, color=ARANCIO_SCURO, lw=1.5, rad=-0.6, ms=11)
        testo(ax, 6 + da * w + 6.5, 48 - 0 * k, str(k + 1), 8.5, SANS, ARANCIO_SCURO, "bold")
    testo(ax, 48, 39, "->", 11, MONO, TESTO_TENUE, "bold")
    testo(ax, 2, 25, "rimuovi(v, 1, &valore): spostamento a sinistra, dal primo dopo", 10, SANS,
          VERDE_SCURO, "bold", ha="left")
    blocco(ax, 6, 11, ["10", "20", "30", "40"], [VERDE_CHIARO, ARANCIO, VERDE_CHIARO, VERDE_CHIARO], w=w)
    blocco(ax, 52, 11, ["10", "30", "40"], VERDE_CHIARO, w=4.5, size=9)
    cella(ax, 52 + 3 * 4.5, 11, 4.0, 6, "white", GRIGIO_BORDO, lw=1.0, r=0.3)
    for k, (da, a) in enumerate([(2, 1), (3, 2)]):
        freccia(ax, 6 + da * w + 3, 17.5, 6 + a * w + 3, 17.5, color=ARANCIO_SCURO, lw=1.5, rad=0.6, ms=11)
        testo(ax, 6 + a * w + 6.5, 23, str(k + 1), 8.5, SANS, ARANCIO_SCURO, "bold")
    testo(ax, 48, 14, "->", 11, MONO, TESTO_TENUE, "bold")
    testo(ax, 66, 7, "valore = 20, n = 3", 8.5, MONO, VERDE_SCURO, "bold")
    testo(ax, 2, 0, "Inserire o rimuovere in posizione p sposta n - p elementi; in fondo nessuno.",
          9, SANS, TESTO, ha="left")
    salva(fig, "0703-inserire-e-rimuovere.png")


# ── 4. puntatore a un elemento ────────────────────────────────────────
def puntatore_appeso():
    fig, ax = tela(9, 4.4)
    testo(ax, 2, 37, "Studente *s = elemento(classe, 0);", 10, MONO, VERDE_SCURO, "bold", ha="left")
    cella(ax, 4, 26, 7, 6, ARANCIO, VERDE, lw=1.3, r=0.3)
    testo(ax, 7.5, 29, "s", 11, MONO, VERDE_SCURO, "bold")
    blocco(ax, 20, 26.5, ["Bianchi", "Rossi"], VERDE_CHIARO, w=12, size=8.5)
    freccia(ax, 11.3, 29, 19.8, 29, color=ARANCIO_SCURO, lw=1.8, ms=12)
    testo(ax, 46, 29.5, "capacita 2, pieno", 9, SANS, TESTO_TENUE, ha="left")
    testo(ax, 2, 17, "aggiungi(classe, nuovo);   realloc sposta il blocco", 10, MONO, VERDE_SCURO, "bold",
          ha="left")
    cella(ax, 4, 4, 7, 6, ARANCIO, VERDE, lw=1.3, r=0.3)
    testo(ax, 7.5, 7, "s", 11, MONO, VERDE_SCURO, "bold")
    blocco(ax, 20, 4.5, ["?", "?"], GRIGIO, w=12, colore=TESTO_TENUE)
    testo(ax, 32, 1, "liberato", 8.5, SANS, TESTO_TENUE)
    freccia(ax, 11.3, 7, 19.8, 7, color=ARANCIO_SCURO, lw=1.8, ms=12)
    blocco(ax, 50, 4.5, ["Bianchi", "Rossi", "Verdi", ""], [VERDE_CHIARO] * 3 + ["white"], w=10, size=8)
    testo(ax, 70, 13.5, "nuovo blocco (capacita 4)", 8.5, SANS, VERDE_SCURO, "bold")
    testo(ax, 2, -4, "s punta ancora al vecchio blocco: dopo un'aggiunta si richiede elemento().",
          9, SANS, ARANCIO_SCURO, "bold", ha="left")
    salva(fig, "0703-puntatore-a-un-elemento.png")


# ── 5. vettore di vettori ─────────────────────────────────────────────
def vettore_di_vettori():
    fig, ax = tela(9, 4.4)
    testo(ax, 2, 42, "Scuola: un vettore di Riga, ognuna con il suo vettore di voti", 10.5, SANS,
          VERDE_SCURO, "bold", ha="left")
    righe = [("3A", [7, 8, 6], 4), ("3B", [5, 9], 2), ("3C", [6, 6, 7, 8, 4], 8)]
    for k, (nome, voti, cap) in enumerate(righe):
        y = 28 - k * 10
        cella(ax, 4, y, 9, 6, VERDE_CHIARO, VERDE, lw=1.3, r=0.3)
        testo(ax, 8.5, y + 3, nome, 10, MONO, VERDE_SCURO, "bold")
        cella(ax, 13.5, y, 9, 6, ARANCIO, VERDE, lw=1.3, r=0.3)
        testo(ax, 18, y + 3, "voti", 9, MONO, VERDE_SCURO, "bold")
        w = 5
        for j in range(cap):
            fc = VERDE_CHIARO if j < len(voti) else "white"
            cella(ax, 32 + j * w, y + 0.5, w - 0.4, 5, fc, VERDE, lw=1.0, r=0.2)
            if j < len(voti):
                testo(ax, 32 + j * w + 2.3, y + 3, str(voti[j]), 9, MONO, VERDE_SCURO, "bold")
        freccia(ax, 22.8, y + 3, 31.7, y + 3, color=ARANCIO_SCURO, lw=1.6, ms=11)
        testo(ax, 32 + cap * w + 2, y + 3, f"{len(voti)} su {cap}", 8.5, SANS, TESTO_TENUE, ha="left")
    testo(ax, 2, 2, "Distruzione dal basso: i voti di ogni riga, poi il blocco delle righe, poi la Scuola.",
          9, SANS, TESTO, ha="left")
    salva(fig, "0703-vettore-di-vettori.png")


lunghezza_capacita()
raddoppio()
inserire_rimuovere()
puntatore_appeso()
vettore_di_vettori()
