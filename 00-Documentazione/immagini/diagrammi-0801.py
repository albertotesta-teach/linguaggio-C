"""Diagrammi per la presentazione 0801 - apertura e chiusura dei file.

Uso: python3 diagrammi-0801.py <cartella-di-uscita>
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




def documento(ax, x, y, w, h, nome, righe, fc="white", colore=TESTO):
    cella(ax, x, y, w, h, fc, GRIGIO_BORDO, lw=1.4, r=0.4)
    testo(ax, x + w / 2, y + h + 2.2, nome, 9, MONO, VERDE_SCURO, "bold")
    for k, r in enumerate(righe):
        testo(ax, x + 1.5, y + h - 3 - k * 3.6, r, 8, MONO, colore, ha="left")


# ── 1. il puntatore a FILE ────────────────────────────────────────────
def maniglia():
    fig, ax = tela(9, 3.6)
    cella(ax, 2, 6, 24, 24, GRIGIO, GRIGIO_BORDO, lw=1.4)
    testo(ax, 14, 27, "programma", 10, SANS, TESTO_TENUE, "bold")
    cella(ax, 6, 13, 10, 6, ARANCIO, VERDE, lw=1.3, r=0.3)
    testo(ax, 11, 16, "f", 11, MONO, VERDE_SCURO, "bold")
    testo(ax, 11, 9.5, "FILE *f", 8.5, MONO, TESTO_TENUE)
    cella(ax, 34, 8, 20, 20, VERDE_CHIARO, VERDE, lw=1.4, r=0.5)
    testo(ax, 44, 25, "FILE (libreria)", 9, SANS, VERDE_SCURO, "bold")
    testo(ax, 44, 19.5, "buffer", 8.5, MONO, TESTO)
    testo(ax, 44, 15.5, "posizione", 8.5, MONO, TESTO)
    testo(ax, 44, 11.5, "modalita'", 8.5, MONO, TESTO)
    freccia(ax, 16.3, 16, 33.7, 16, color=ARANCIO_SCURO, lw=1.8, ms=13)
    documento(ax, 64, 9, 22, 16, "saluto.txt", ["Benvenuti al", "corso di C!", "..."])
    freccia(ax, 54.3, 18, 63.7, 18, color=VERDE, lw=1.8, ms=13)
    freccia(ax, 63.7, 14, 54.3, 14, color=VERDE, lw=1.8, ms=13)
    testo(ax, 2, 1, "f = fopen(\"saluto.txt\", \"w\");  ...  fclose(f);", 9.5, MONO, VERDE_SCURO,
          "bold", ha="left")
    testo(ax, 2, -3.5, "fopen restituisce NULL se il file non si puo' aprire: il controllo e' obbligatorio.",
          9, SANS, TESTO, ha="left")
    salva(fig, "0801-puntatore-a-file.png")


# ── 2. modalità di apertura ───────────────────────────────────────────
def modalita():
    fig, ax = tela(9, 4.0)
    prima = ["12/10 Museo", "03/11 Lab"]
    casi = [("\"r\"", "lettura", prima, "letto dall'inizio", VERDE_CHIARO),
            ("\"w\"", "scrittura", ["20/11 Biblio"], "contenuto cancellato", ARANCIO),
            ("\"a\"", "aggiunta", prima + ["20/11 Biblio"], "nuove righe in fondo", VERDE_CHIARO)]
    testo(ax, 2, 38, "diario.txt prima:", 9, SANS, TESTO_TENUE, ha="left")
    documento(ax, 2, 18, 20, 13, "", prima)
    for k, (m, nome, righe, nota, fc) in enumerate(casi):
        x = 30 + k * 20
        testo(ax, x + 8, 38, f"fopen(..., {m})", 9, MONO, VERDE_SCURO, "bold")
        documento(ax, x, 18, 17, 13, "", righe, fc=fc)
        testo(ax, x + 8.5, 13.5, nota, 8.5, SANS, ARANCIO_SCURO if m == "\"w\"" else VERDE_SCURO,
              "bold")
    testo(ax, 2, 5, "File inesistente:  \"r\" -> NULL      \"w\" e \"a\" -> lo creano", 9.5, MONO,
          VERDE_SCURO, "bold", ha="left")
    testo(ax, 2, 0.5, "\"w\" svuota senza chiedere: per conservare il contenuto si usa \"a\".", 9, SANS,
          TESTO, ha="left")
    salva(fig, "0801-modalita-di-apertura.png")


# ── 3. flussi standard ────────────────────────────────────────────────
def flussi():
    fig, ax = tela(9, 4.2)
    cella(ax, 33, 14, 22, 16, GRIGIO, GRIGIO_BORDO, lw=1.4)
    testo(ax, 44, 22, "programma", 10, SANS, TESTO, "bold")
    cella(ax, 2, 25, 18, 7, VERDE_CHIARO, VERDE, lw=1.2, r=0.3)
    testo(ax, 11, 28.5, "tastiera", 9, SANS, VERDE_SCURO, "bold")
    cella(ax, 2, 13, 18, 7, "white", GRIGIO_BORDO, lw=1.2, r=0.3)
    testo(ax, 11, 16.5, "< dati.txt", 9, MONO, TESTO_TENUE, "bold")
    freccia(ax, 20.3, 28.5, 32.7, 24, color=VERDE, lw=1.8, ms=12)
    freccia(ax, 20.3, 16.5, 32.7, 21, color=GRIGIO_BORDO, lw=1.5, ms=11)
    testo(ax, 26, 31, "stdin", 9, MONO, VERDE_SCURO, "bold")
    cella(ax, 68, 31, 18, 7, VERDE_CHIARO, VERDE, lw=1.2, r=0.3)
    testo(ax, 77, 34.5, "schermo", 9, SANS, VERDE_SCURO, "bold")
    cella(ax, 68, 19, 18, 7, "white", GRIGIO_BORDO, lw=1.2, r=0.3)
    testo(ax, 77, 22.5, "> risultati.txt", 8.5, MONO, TESTO_TENUE, "bold")
    cella(ax, 68, 5, 18, 7, ARANCIO, VERDE, lw=1.2, r=0.3)
    testo(ax, 77, 8.5, "schermo", 9, SANS, ARANCIO_SCURO, "bold")
    freccia(ax, 55.3, 26, 67.7, 34, color=VERDE, lw=1.8, ms=12)
    freccia(ax, 55.3, 23, 67.7, 22.5, color=GRIGIO_BORDO, lw=1.5, ms=11)
    testo(ax, 61, 33.5, "stdout", 9, MONO, VERDE_SCURO, "bold")
    freccia(ax, 55.3, 17, 67.7, 9, color=ARANCIO_SCURO, lw=1.8, ms=12)
    testo(ax, 58, 10, "stderr", 9, MONO, ARANCIO_SCURO, "bold")
    testo(ax, 2, 2, "I risultati su stdout, i messaggi d'errore su stderr:", 9, SANS, TESTO, ha="left")
    testo(ax, 2, -2.5, "con > nel file va solo stdout, gli errori restano a video.", 9, SANS, TESTO,
          ha="left")
    salva(fig, "0801-flussi-standard.png")


# ── 4. buffer ─────────────────────────────────────────────────────────
def buffer():
    fig, ax = tela(9, 3.6)
    testo(ax, 2, 33, "fprintf(f, ...)", 9.5, MONO, VERDE_SCURO, "bold", ha="left")
    cella(ax, 30, 18, 26, 10, VERDE_CHIARO, VERDE, lw=1.4, r=0.4)
    testo(ax, 43, 25.5, "buffer in memoria", 9, SANS, VERDE_SCURO, "bold")
    testo(ax, 43, 21, "\"Registro del lab...\"", 8.5, MONO, TESTO)
    freccia(ax, 14, 30, 29.7, 24, color=VERDE, lw=1.8, ms=12)
    documento(ax, 66, 15, 20, 13, "buffer.txt", ["(vuoto finche'", "non si svuota", "il buffer)"])
    freccia(ax, 56.3, 23, 65.7, 23, color=ARANCIO_SCURO, lw=2.0, ms=13)
    testo(ax, 61, 30, "fflush(f)\nfclose(f)\nbuffer pieno", 8.5, MONO, ARANCIO_SCURO, "bold")
    testo(ax, 2, 8, "Prima di fflush o fclose un altro lettore non vede i dati;", 9, SANS, TESTO,
          ha="left")
    testo(ax, 2, 3.5, "se il programma si interrompe, il contenuto del buffer si perde.", 9, SANS, TESTO,
          ha="left")
    salva(fig, "0801-buffer.png")


# ── 5. salvataggio sicuro ─────────────────────────────────────────────
def salvataggio():
    fig, ax = tela(9, 4.2)
    passi = [("1. fopen(\"libri.tmp\", \"w\"), scrittura, fclose",
              [("libri.txt", ["vecchio elenco"], "white"), ("libri.tmp", ["nuovo elenco"], ARANCIO)]),
             ("2. remove(\"libri.txt\")",
              [("", [], None), ("libri.tmp", ["nuovo elenco"], ARANCIO)]),
             ("3. rename(\"libri.tmp\", \"libri.txt\")",
              [("libri.txt", ["nuovo elenco"], VERDE_CHIARO), ("", [], None)])]
    for k, (titolo, docs) in enumerate(passi):
        y = 30 - k * 13
        testo(ax, 2, y + 4, titolo, 9.5, MONO, VERDE_SCURO, "bold", ha="left")
        for j, (nome, righe, fc) in enumerate(docs):
            if fc is not None:
                x = 56 + j * 16
                cella(ax, x, y, 14, 7, fc, GRIGIO_BORDO, lw=1.2, r=0.3)
                testo(ax, x + 7, y + 5, nome, 8, MONO, VERDE_SCURO, "bold")
                testo(ax, x + 7, y + 2, righe[0], 7.5, SANS, TESTO)
    testo(ax, 2, -1, "Fino al passo 3 il file originale resta intatto: un'interruzione non lo rovina.",
          9, SANS, TESTO, ha="left")
    salva(fig, "0801-salvataggio-sicuro.png")


maniglia()
modalita()
flussi()
buffer()
salvataggio()
