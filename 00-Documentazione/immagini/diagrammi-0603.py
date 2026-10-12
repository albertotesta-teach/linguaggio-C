"""Diagrammi per la presentazione 0603 - Struct e funzioni.

Uso: python3 diagrammi-0603.py <cartella-di-uscita>
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


def tessera(ax, x, y, nome_var, credito, evidenzia=False, titolo_col=VERDE_SCURO):
    testo(ax, x, y + 13, nome_var, 11, MONO, titolo_col, "bold", ha="left")
    campi = [("numero", "1024", 9), ("intestatario", "\"Bianchi Sara\"", 17), ("credito", credito, 9)]
    xx = x
    for k, (n, v, w) in enumerate(campi):
        fc = ARANCIO if evidenzia and k == 2 else VERDE_CHIARO
        cella(ax, xx, y, w - 0.4, 7, fc, VERDE, lw=1.3, r=0.3)
        testo(ax, xx + w / 2, y + 3.5, v, 9.5, MONO, VERDE_SCURO, "bold")
        testo(ax, xx + w / 2, y + 9.3, n, 8.5, MONO, TESTO_TENUE)
        xx = xx + w
    return xx


def riquadro(ax, x, y, w, h, titolo):
    cella(ax, x, y, w, h, "white", GRIGIO_BORDO, lw=1.2, r=1.0)
    testo(ax, x + 1.5, y + h - 2.5, titolo, 9.5, SANS, TESTO_TENUE, "bold", ha="left")


# ── 1. il parametro è una copia ───────────────────────────────────────
def copia_parametro():
    fig, ax = tela(9, 5.8)
    testo(ax, 2, 56, "ricarica_sbagliata(tessera, 20.00);", 11, MONO, VERDE_SCURO, "bold", ha="left")
    riquadro(ax, 1, 31, 38, 22, "main")
    tessera(ax, 3, 34, "tessera", "3.50")
    riquadro(ax, 51, 31, 38, 22, "ricarica_sbagliata")
    tessera(ax, 53, 34, "t   (copia)", "23.50", evidenzia=True)
    freccia(ax, 39.5, 37.5, 50.5, 37.5, color=VERDE, lw=2.2, ms=15)
    testo(ax, 45, 40, "copia", 9.5, SANS, VERDE_SCURO, "bold")
    testo(ax, 70, 29, "t.credito = t.credito + euro;   al ritorno t sparisce", 9, MONO, TESTO_TENUE)

    testo(ax, 2, 24, "tessera = ricaricata(tessera, 20.00);", 11, MONO, VERDE_SCURO, "bold", ha="left")
    riquadro(ax, 1, -1, 38, 22, "main")
    tessera(ax, 3, 2, "tessera", "23.50", evidenzia=True)
    riquadro(ax, 51, -1, 38, 22, "ricaricata")
    tessera(ax, 53, 2, "t   (copia)", "23.50", evidenzia=True)
    freccia(ax, 50.5, 5.5, 39.5, 5.5, color=ARANCIO_SCURO, lw=2.2, ms=15)
    testo(ax, 45, 8, "return t", 9.5, MONO, ARANCIO_SCURO, "bold")
    salva(fig, "0603-copia-parametro.png")


# ── 2. operatore freccia ──────────────────────────────────────────────
def operatore_freccia():
    fig, ax = tela(9, 3.8)
    testo(ax, 2, 32, "Studente *eletto = &giulia;", 11.5, MONO, VERDE_SCURO, "bold", ha="left")
    # puntatore
    testo(ax, 3, 27, "eletto", 10.5, MONO, TESTO, "bold", ha="left")
    cella(ax, 3, 16, 14, 7, GRIGIO, GRIGIO_BORDO, lw=1.3, r=0.3)
    testo(ax, 10, 19.5, "&giulia", 10, MONO, TESTO, "bold")
    # struct
    testo(ax, 30, 27, "giulia", 10.5, MONO, TESTO, "bold", ha="left")
    campi = [("nome", "\"Giulia Ferri\"", 22), ("classe", "\"3B\"", 10), ("media", "7.8", 10)]
    x = 30
    centro_media = 0
    for k, (n, v, w) in enumerate(campi):
        fc = ARANCIO if n == "media" else VERDE_CHIARO
        cella(ax, x, 16, w - 0.4, 7, fc, VERDE, lw=1.3, r=0.3)
        testo(ax, x + w / 2, 19.5, v, 9.5, MONO, VERDE_SCURO, "bold")
        testo(ax, x + w / 2, 25, n, 8.5, MONO, TESTO_TENUE)
        if n == "media":
            centro_media = x + w / 2
        x = x + w
    freccia(ax, 17.2, 19.5, 29.6, 19.5, color=VERDE, lw=2.2, ms=15)
    # le tre scritture
    righe = ["giulia.media", "(*eletto).media", "eletto->media"]
    note = ["con la variabile", "prima *eletto, poi .media", "la forma abituale"]
    for i, (r, n) in enumerate(zip(righe, note)):
        yy = 9 - i * 4.5
        testo(ax, 3, yy, r, 10.5, MONO, ARANCIO_SCURO if i == 2 else VERDE_SCURO, "bold", ha="left")
        testo(ax, 24, yy, n, 9.5, SANS, TESTO_TENUE, ha="left")
    ax.plot([centro_media, centro_media], [15.6, 4.5], color=ARANCIO_SCURO, lw=1.2, ls="--")
    testo(ax, centro_media + 1.5, 4.5, "stesso campo", 9.5, SANS, ARANCIO_SCURO, "bold", ha="left")
    salva(fig, "0603-operatore-freccia.png")


# ── 3. valore o indirizzo ─────────────────────────────────────────────
def registro(ax, x, y, nome):
    cella(ax, x, y, 30, 9, VERDE_CHIARO, VERDE, lw=1.4, r=0.4)
    testo(ax, x + 1.5, y + 6.3, nome, 9.5, MONO, VERDE_SCURO, "bold", ha="left")
    for i in range(12):
        cella(ax, x + 1.5 + i * 2.3, y + 1.3, 2.0, 2.8, "white", VERDE, lw=0.6, r=0.1)
    testo(ax, x + 29, y + 6.3, "808 byte", 8.5, MONO, TESTO_TENUE, ha="right")


def valore_o_indirizzo():
    fig, ax = tela(9, 5.0)
    testo(ax, 2, 47, "double media(Registro r);", 10.5, MONO, VERDE_SCURO, "bold", ha="left")
    testo(ax, 48, 47, "double media(const Registro *r);", 10.5, MONO, VERDE_SCURO, "bold", ha="left")
    # sinistra
    testo(ax, 2, 40, "main", 9.5, SANS, TESTO_TENUE, "bold", ha="left")
    registro(ax, 2, 29, "registro")
    testo(ax, 2, 22, "media", 9.5, SANS, TESTO_TENUE, "bold", ha="left")
    registro(ax, 2, 11, "r (copia)")
    freccia(ax, 17, 28.6, 17, 20.6, color=VERDE, lw=2.2, ms=14)
    testo(ax, 19, 24.6, "808 byte copiati", 9, SANS, VERDE_SCURO, "bold", ha="left")
    # destra
    testo(ax, 48, 40, "main", 9.5, SANS, TESTO_TENUE, "bold", ha="left")
    registro(ax, 48, 29, "registro")
    testo(ax, 48, 22, "media", 9.5, SANS, TESTO_TENUE, "bold", ha="left")
    cella(ax, 48, 11, 12, 9, GRIGIO, GRIGIO_BORDO, lw=1.3, r=0.4)
    testo(ax, 54, 17.3, "r", 9.5, MONO, TESTO, "bold")
    testo(ax, 54, 13.5, "8 byte", 8.5, MONO, TESTO_TENUE)
    freccia(ax, 54, 20.4, 58, 28.6, color=ARANCIO_SCURO, lw=2.2, ms=14, rad=-0.2)
    testo(ax, 62, 16, "solo l'indirizzo:\nr->voti[i] legge\nl'originale", 9, MONO, ARANCIO_SCURO, "bold", ha="left")
    testo(ax, 2, 3, "Tre chiamate: 2424 byte copiati a sinistra, 24 byte a destra. const impedisce le modifiche.",
          10, SANS, TESTO, ha="left")
    salva(fig, "0603-valore-o-indirizzo.png")


# ── 4. puntatore che scorre ───────────────────────────────────────────
def puntatore_che_scorre():
    fig, ax = tela(9, 4.4)
    testo(ax, 2, 43, "for (p = arrivi; p < fine; p++)   /* fine = arrivi + 5 */", 10.5, MONO, VERDE_SCURO, "bold", ha="left")
    treni = [("R 10213", "0"), ("R 10215", "7"), ("RV 2131", "15"), ("R 10217", "3"), ("R 10219", "0")]
    w = 14
    x0 = 4
    y = 18
    for i, (num, rit) in enumerate(treni):
        x = x0 + i * w
        fc = ARANCIO if i == 1 else VERDE_CHIARO
        cella(ax, x, y, w - 0.6, 10, fc, VERDE, lw=1.4, r=0.4)
        testo(ax, x + w / 2 - 0.3, y + 6.5, num, 9.5, MONO, VERDE_SCURO, "bold")
        testo(ax, x + w / 2 - 0.3, y + 2.8, f"ritardo {rit}", 8.5, MONO, TESTO)
        testo(ax, x + w / 2 - 0.3, y + 12, f"arrivi[{i}]", 8.5, MONO, TESTO_TENUE)
        testo(ax, x, y - 2.2, f"+{i * 28}", 8, MONO, TESTO_TENUE, ha="left")
    xf = x0 + 5 * w
    cella(ax, xf, y, w - 0.6, 10, "white", GRIGIO_BORDO, lw=1.0, r=0.4)
    ax.patches[-1].set_linestyle("--")
    testo(ax, xf, y - 2.2, "+140", 8, MONO, TESTO_TENUE, ha="left")
    testo(ax, xf + w / 2 - 0.3, y + 5, "fuori", 8.5, SANS, TESTO_TENUE)
    # frecce p, p+1, fine
    for (i, et, col) in [(1, "p", ARANCIO_SCURO), (2, "p + 1", VERDE), (5, "fine", TESTO_TENUE)]:
        xc = x0 + i * w + w / 2 - 0.3
        freccia(ax, xc, 6.5, xc, y - 3.4, color=col, lw=2.0, ms=13)
        testo(ax, xc, 4.5, et, 10, MONO, col, "bold")
    # graffa sizeof
    xa = x0 + w
    xb = x0 + 2 * w - 0.6
    ax.plot([xa, xa, xb, xb], [y + 14.5, y + 16, y + 16, y + 14.5], color=TESTO_TENUE, lw=1.2)
    testo(ax, (xa + xb) / 2, y + 18.5, "sizeof(Treno) = 28 byte", 9, MONO, TESTO_TENUE)
    testo(ax, 2, -1, "p - arrivi == 1 (posizione dell'elemento puntato)   p->ritardo == 7",
          10, MONO, TESTO, ha="left")
    salva(fig, "0603-puntatore-che-scorre.png")


copia_parametro()
operatore_freccia()
valore_o_indirizzo()
puntatore_che_scorre()
