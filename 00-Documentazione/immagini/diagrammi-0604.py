"""Diagrammi per la presentazione 0604 - Struct annidate.

Uso: python3 diagrammi-0604.py <cartella-di-uscita>
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
VERDE_MEDIO = "#C3E2C3"


def campo(ax, x, y, w, h, valore, nome=None, fc=VERDE_CHIARO, size=9.5):
    cella(ax, x, y, w - 0.4, h, fc, VERDE, lw=1.3, r=0.3)
    testo(ax, x + w / 2 - 0.2, y + h / 2, valore, size, MONO, VERDE_SCURO, "bold")
    if nome:
        testo(ax, x + w / 2 - 0.2, y + h + 2, nome, 8.5, MONO, TESTO_TENUE)


# ── 1. struct dentro struct ───────────────────────────────────────────
def struct_in_struct():
    fig, ax = tela(9, 4.2)
    testo(ax, 2, 41, "Studente s = {\"Rossi Elena\", \"2A\", {12, 3, 2010}};", 11, MONO, VERDE_SCURO,
          "bold", ha="left")
    y = 18
    h = 8
    # contenitore Studente
    cella(ax, 2, y - 4, 84, h + 14, "white", VERDE, lw=1.8, r=0.8)
    testo(ax, 4, y + h + 7.5, "s", 11, MONO, TESTO, "bold", ha="left")
    campo(ax, 4, y, 30, h, "\"Rossi Elena\"", "nome")
    campo(ax, 34, y, 10, h, "\"2A\"", "classe")
    # Data interna
    cella(ax, 45, y - 2, 39, h + 9.5, VERDE_MEDIO, VERDE, lw=1.4, r=0.6)
    testo(ax, 46.5, y + h + 5.3, "nascita (Data)", 9, MONO, VERDE_SCURO, "bold", ha="left")
    campo(ax, 46.5, y, 11.5, h, "12", "giorno", fc="white")
    campo(ax, 58, y, 11.5, h, "3", "mese", fc="white")
    campo(ax, 69.5, y, 14, h, "2010", "anno", fc=ARANCIO)
    # offset
    for xo, et in [(4, "0"), (34, "20"), (46.5, "24"), (58, "28"), (69.5, "32"), (84, "36")]:
        testo(ax, xo, y - 6.5, et, 8, MONO, TESTO_TENUE, ha="left")
    # etichetta catena
    freccia(ax, 76.5, 6.5, 76.5, 13.5, color=ARANCIO_SCURO, lw=2.0, ms=13)
    testo(ax, 74.5, 7.5, "s.nascita.anno", 10.5, MONO, ARANCIO_SCURO, "bold", ha="right")
    testo(ax, 2, 1, "sizeof(Studente) = 20 + 4 + sizeof(Data) = 36 byte: la Data sta dentro lo Studente.",
          9.5, SANS, TESTO, ha="left")
    salva(fig, "0604-struct-in-struct.png")


# ── 2. passare una parte ──────────────────────────────────────────────
def passare_una_parte():
    fig, ax = tela(9, 5.0)
    # studente a sinistra
    testo(ax, 2, 46, "Studente s", 11, MONO, VERDE_SCURO, "bold", ha="left")
    cella(ax, 2, 8, 34, 35, "white", VERDE, lw=1.8, r=0.8)
    campo(ax, 4, 33, 30, 6, "\"Neri Luca\"", None)
    testo(ax, 5, 40.5, "nome", 8.5, MONO, TESTO_TENUE, ha="left")
    cella(ax, 4, 21, 30, 9, VERDE_MEDIO, VERDE, lw=1.3, r=0.4)
    testo(ax, 5.5, 27.3, "nascita", 9, MONO, VERDE_SCURO, "bold", ha="left")
    testo(ax, 19, 23.5, "{4, 6, 2008}", 9, MONO, VERDE_SCURO)
    cella(ax, 4, 10, 30, 9, ARANCIO, ARANCIO_SCURO, lw=1.3, r=0.4)
    testo(ax, 5.5, 16.3, "residenza", 9, MONO, ARANCIO_SCURO, "bold", ha="left")
    testo(ax, 19, 12.5, "via Roma 77, Ovada", 8.5, MONO, ARANCIO_SCURO)
    # funzione per valore
    cella(ax, 50, 30, 38, 13, GRIGIO, GRIGIO_BORDO, lw=1.2, r=0.8)
    testo(ax, 51.5, 40, "int eta(Data nascita, Data oggi)", 8.5, MONO, TESTO, "bold", ha="left")
    cella(ax, 52, 31.5, 22, 6, VERDE_MEDIO, VERDE, lw=1.2, r=0.3)
    testo(ax, 63, 34.5, "copia: 12 byte", 8.5, MONO, VERDE_SCURO, "bold")
    freccia(ax, 34.4, 25.5, 51.6, 34.5, color=VERDE, lw=2.0, ms=14)
    testo(ax, 37.5, 23.3, "eta(s.nascita, gita)", 8.5, MONO, VERDE_SCURO, "bold", ha="left")
    # funzione per indirizzo
    cella(ax, 50, 6, 38, 15, GRIGIO, GRIGIO_BORDO, lw=1.2, r=0.8)
    testo(ax, 51.5, 18, "void cambia_indirizzo(Indirizzo *i, ...)", 7.6, MONO, TESTO, "bold", ha="left")
    cella(ax, 52, 8, 8, 6, "white", GRIGIO_BORDO, lw=1.2, r=0.3)
    testo(ax, 56, 11, "i", 9.5, MONO, TESTO, "bold")
    freccia(ax, 51.6, 11, 34.4, 14, color=ARANCIO_SCURO, lw=2.0, ms=14)
    testo(ax, 62, 11, "punta dentro s", 8.5, SANS, ARANCIO_SCURO, "bold", ha="left")
    testo(ax, 2, 1, "cambia_indirizzo(&s.residenza, ...);   da un puntatore p: &p->residenza", 9.5, MONO,
          TESTO, ha="left")
    salva(fig, "0604-passare-una-parte.png")


# ── 3. catena di accessi ──────────────────────────────────────────────
def catena():
    fig, ax = tela(9, 5.0)
    passi = [("scuola", "Scuola"),
             (".classi", "array di Classe"),
             ("[1]", "una Classe"),
             (".alunni", "array di Studente"),
             ("[0]", "uno Studente"),
             (".nascita", "una Data"),
             (".anno", "un int")]
    x = 2
    y = 44
    for i, (pezzo, tipo) in enumerate(passi):
        precedente = "".join(p for p, _ in passi[:i])
        yy = y - i * 6.4
        t = ax.text(2, yy, precedente, fontsize=10, family=MONO, color=TESTO_TENUE, ha="left",
                    va="center")
        larg = 0
        if precedente:
            bb = t.get_window_extent(renderer=fig.canvas.get_renderer())
            larg = ax.transData.inverted().transform((bb.x1, 0))[0] - 2
        colore = ARANCIO_SCURO if i == len(passi) - 1 else VERDE_SCURO
        testo(ax, 2 + larg, yy, pezzo, 10, MONO, colore, "bold", ha="left")
        testo(ax, 62, yy, tipo, 10, SANS, colore, "bold" if i == len(passi) - 1 else "normal", ha="left")
        ax.plot([56, 60], [yy, yy], color=GRIGIO_BORDO, lw=1)
    testo(ax, 2, -1, "Dopo un array viene [ ], dopo una struct viene il punto.", 10.5, SANS, TESTO,
          ha="left")
    salva(fig, "0604-catena-di-accessi.png")


# ── 4. funzioni a livelli ─────────────────────────────────────────────
def livelli():
    fig, ax = tela(9, 4.4)
    righe = [("migliore(const Scuola *sc)", "scorre sc->classi[k]", "media_classe(&sc->classi[k])"),
             ("media_classe(const Classe *c)", "scorre c->alunni[s]", "media_studente(&c->alunni[s])"),
             ("media_studente(const Studente *s)", "scorre s->voti[v]", "")]
    for i, (firma, vede, chiama) in enumerate(righe):
        x = 2 + i * 9
        y = 34 - i * 14
        cella(ax, x, y, 58, 9, VERDE_CHIARO if i < 2 else ARANCIO, VERDE if i < 2 else ARANCIO_SCURO,
              lw=1.5, r=0.6)
        testo(ax, x + 2, y + 6, firma, 9.5, MONO, VERDE_SCURO, "bold", ha="left")
        testo(ax, x + 2, y + 2.4, vede, 9, MONO, TESTO_TENUE, ha="left")
        if chiama:
            freccia(ax, x + 6, y - 0.3, x + 6, y - 4.6, color=VERDE, lw=2.0, ms=13)
            testo(ax, x + 8, y - 2.6, chiama, 8.5, MONO, VERDE_SCURO, ha="left")
    testo(ax, 2, -1, "Ogni funzione conosce un solo livello di indici.", 10.5, SANS, TESTO, ha="left")
    salva(fig, "0604-funzioni-a-livelli.png")


struct_in_struct()
passare_una_parte()
catena()
livelli()
