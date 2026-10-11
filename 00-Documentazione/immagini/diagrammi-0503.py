"""Diagrammi per la presentazione 0503 - Puntatori e funzioni.

Uso: python3 diagrammi-0503.py <cartella-di-uscita>
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



def cornice(ax, x, y, w, h, titolo, colore=GRIGIO_BORDO, tratteggio=False):
    """Riquadro che rappresenta lo spazio delle variabili di una funzione."""
    ax.add_patch(FancyBboxPatch((x, y), w, h, boxstyle="round,pad=0,rounding_size=1.2",
                                fc="#FAFAFA", ec=colore, lw=1.6,
                                ls=(0, (5, 3)) if tratteggio else "solid"))
    testo(ax, x + 1.5, y + h - 2.6, titolo, 12, MONO, TESTO_TENUE, "bold", ha="left")


def variabile(ax, x, y, nome, valore, w=16, h=7, verde=True, nome_size=11):
    testo(ax, x + w / 2, y + h + 2.2, nome, nome_size, MONO, VERDE_SCURO if verde else TESTO, "bold")
    cella(ax, x, y, w, h, VERDE_CHIARO if verde else "white", VERDE_SCURO if verde else TESTO, lw=1.8, r=0.5)
    testo(ax, x + w / 2, y + h / 2, valore, 13, MONO, VERDE_SCURO if verde else TESTO, "bold")


# ── 1. parametri di uscita ────────────────────────────────────────────
def parametri():
    fig, ax = tela(8, 4.0)
    # main
    cornice(ax, 2, 4, 30, 32, "main")
    variabile(ax, 9, 21, "primo", "412")
    variabile(ax, 9, 7, "secondo", "398")
    testo(ax, 17, 19.3, "&primo = ...a10", 9.5, MONO, TESTO_TENUE)
    testo(ax, 17, 5.3, "&secondo = ...a14", 9.5, MONO, TESTO_TENUE)
    # scambia
    cornice(ax, 46, 4, 32, 32, "scambia(int *a, int *b)")
    variabile(ax, 52, 21, "a", "...a10", w=18, verde=False)
    variabile(ax, 52, 7, "b", "...a14", w=18, verde=False)
    freccia(ax, 51.5, 24.5, 25.2, 24.5, color=VERDE, lw=2.2, ms=16)
    freccia(ax, 51.5, 10.5, 25.2, 10.5, color=VERDE, lw=2.2, ms=16)
    testo(ax, 38.5, 27.3, "*a", 12, MONO, VERDE, "bold")
    testo(ax, 38.5, 13.3, "*b", 12, MONO, VERDE, "bold")
    ax.text(2, -0.5, "Chiamata: scambia(&primo, &secondo).  a e b contengono gli indirizzi (esadecimali, abbreviati)",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    ax.text(2, -4, "delle variabili del main: scrivendo *a e *b la funzione modifica primo e secondo.",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0503-parametri-per-riferimento.png")


# ── 2. puntatore restituito ───────────────────────────────────────────
def restituito():
    fig, ax = tela(8, 4.6)
    x0 = 4
    w = 10
    y = 28
    h = 7.5
    valori = ["38", "42", "61", "35", "47"]
    testo(ax, x0, y + h + 6.5, "int temperature[5]  (nel main)", 12, MONO, VERDE_SCURO, "bold", ha="left")
    for i, v in enumerate(valori):
        fc = "#C3E2C3" if i == 2 else VERDE_CHIARO
        cella(ax, x0 + i * w + 0.25, y, w - 0.5, h, fc, VERDE, r=0.4)
        testo(ax, x0 + i * w + w / 2, y + h / 2, v, 13, MONO, VERDE_SCURO, "bold")
    cella(ax, x0 + 2 * w - 4, 9, 18, 7, "white", TESTO, lw=1.8, r=0.5)
    testo(ax, x0 + 2 * w + 5, 12.5, "...a18", 13, MONO, TESTO, "bold")
    testo(ax, x0 + 2 * w - 5.5, 12.5, "caldo", 11, MONO, TESTO, "bold", ha="right")
    freccia(ax, x0 + 2 * w + w / 2, 16.4, x0 + 2 * w + w / 2, y - 0.6, color=VERDE, lw=2.2, ms=16)
    for i in range(5):
        testo(ax, x0 + i * w + w / 2, y + h + 2.2, f"...{0x10 + 4 * i:x}".replace("...", "...a"), 9, MONO, TESTO_TENUE)
    ax.text(x0 + 2 * w + 16, 12.5, "caldo = massimo(temperature, 5);", fontsize=11, family=MONO,
            color=VERDE, weight="bold", ha="left", va="center")
    ax.text(x0 + 2 * w + 16, 8.8, "*caldo = *caldo - 4;   corretto: punta nel main",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    # errore
    cornice(ax, 58, 26, 20, 17, "media_sbagliata", colore="#C0392B", tratteggio=True)
    testo(ax, 68, 38.5, "double m", 11, MONO, "#C0392B", "bold")
    ax.plot([60, 76], [27.5, 37.5], color="#C0392B", lw=2)
    ax.plot([60, 76], [37.5, 27.5], color="#C0392B", lw=2)
    ax.text(58, 21, "return &m;   ERRORE", fontsize=11, family=MONO, color="#C0392B",
            weight="bold", ha="left", va="center")
    ax.text(58, 17.5, "m non esiste più dopo il return", fontsize=10.5, family=SANS,
            color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0503-puntatore-restituito.png")


# ── 3. puntatore a funzione ───────────────────────────────────────────
def puntatore_funzione():
    fig, ax = tela(8, 4.2)
    variabile(ax, 4, 17, "operazione", "→ massimo", w=22, verde=False)
    testo(ax, 15, 31, "int (*operazione)(int, int)", 11.5, MONO, TESTO, "bold")
    funzioni = [("somma", "a + b", 32), ("differenza", "a - b", 19), ("massimo", "a > b ? a : b", 6)]
    for nome, corpo, yy in funzioni:
        scelta = nome == "massimo"
        cella(ax, 46, yy, 30, 9, VERDE_CHIARO if scelta else "white",
              VERDE_SCURO if scelta else GRIGIO_BORDO, lw=2.0 if scelta else 1.4, r=0.8)
        testo(ax, 48, yy + 6, f"int {nome}(int a, int b)", 10, MONO,
              VERDE_SCURO if scelta else TESTO_TENUE, "bold", ha="left")
        testo(ax, 48, yy + 2.6, f"return {corpo};", 10, MONO,
              VERDE_SCURO if scelta else TESTO_TENUE, ha="left")
    freccia(ax, 26.5, 20.5, 45.5, 10.5, color=VERDE, lw=2.4, ms=18)
    for yy in (36.5, 23.5):
        ax.add_patch(FancyArrowPatch((26.5, 20.5), (45.5, yy), arrowstyle="-|>", mutation_scale=12,
                                     color=GRIGIO_BORDO, lw=1.2, ls=(0, (4, 3))))
    ax.text(4, 9, "operazione = massimo;", fontsize=11, family=MONO, color=VERDE, weight="bold", ha="left", va="center")
    ax.text(4, 5, "x = operazione(78, 71);   /* 78 */", fontsize=11, family=MONO, color=TESTO, ha="left", va="center")
    ax.text(4, -2, "Il puntatore contiene l'indirizzo del codice di una funzione con lo stesso prototipo.",
            fontsize=10, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0503-puntatore-a-funzione.png")


# ── 4. callback ───────────────────────────────────────────────────────
def callback():
    fig, ax = tela(8, 4.0)
    cornice(ax, 2, 6, 40, 30, "applica(v, n, trasforma)")
    ax.text(5, 26, "for (p = v; p < v + n; p++) {", fontsize=10.5, family=MONO, color=TESTO, ha="left", va="center")
    ax.text(5, 21.5, "    *p = trasforma(*p);", fontsize=10.5, family=MONO, color=VERDE, weight="bold", ha="left", va="center")
    ax.text(5, 17, "}", fontsize=10.5, family=MONO, color=TESTO, ha="left", va="center")
    ax.text(5, 31, "int (*trasforma)(int)", fontsize=10.5, family=MONO, color=TESTO_TENUE, ha="left", va="center")
    ax.text(5, 10.5, "il ciclo è scritto una volta sola", fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    chiamate = [("applica(punti, N, raddoppia)", "raddoppia", "2 * x", 28),
                ("applica(punti, N, minimo_zero)", "minimo_zero", "x < 0 ? 0 : x", 16.5),
                ("applica(punti, N, alla_decina)", "alla_decina", "(x + 5) / 10 * 10", 5)]
    for chiamata, nome, corpo, yy in chiamate:
        cella(ax, 50, yy, 28, 9, VERDE_CHIARO, VERDE, r=0.8)
        testo(ax, 52, yy + 6, f"int {nome}(int x)", 10, MONO, VERDE_SCURO, "bold", ha="left")
        testo(ax, 52, yy + 2.6, f"return {corpo};", 9.5, MONO, VERDE_SCURO, ha="left")
        ax.add_patch(FancyArrowPatch((35, 21.5), (49.5, yy + 4.5), arrowstyle="-|>", mutation_scale=12,
                                     color=VERDE, lw=1.4, connectionstyle="arc3,rad=0.0"))
    ax.text(2, 1, "Chi chiama applica sceglie la funzione: applica(punti, N, raddoppia), applica(punti, N, minimo_zero), ...",
            fontsize=10.5, family=SANS, color=TESTO_TENUE, ha="left", va="center")
    salva(fig, "0503-callback.png")


parametri()
restituito()
puntatore_funzione()
callback()
