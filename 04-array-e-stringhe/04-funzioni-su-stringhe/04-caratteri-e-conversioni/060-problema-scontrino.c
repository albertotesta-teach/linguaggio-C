/*
 * 060-problema-scontrino.c
 *
 * Comporre le righe di uno scontrino con snprintf
 *
 * La cassa di una cartoleria prepara lo scontrino in una serie di righe
 * di testo, ciascuna di LARGHEZZA caratteri, che vengono poi inviate alla
 * stampante. I dati sono in tre array paralleli: descrizione, prezzo
 * unitario (in centesimi) e quantità.
 *
 * Ogni riga si compone in una stringa con snprintf, usando le stesse
 * specifiche di printf:
 *
 *     %-18.18s   descrizione allineata a sinistra, al massimo 18 caratteri
 *     %3d        quantità su 3 colonne
 *     %9s        importo, già trasformato in testo da formatta_euro()
 *
 * La precisione .18 tronca le descrizioni troppo lunghe; snprintf con
 * sizeof(riga) garantisce comunque di non superare l'array.
 * formatta_euro(dest, dim, centesimi) trasforma un importo in centesimi
 * nel testo "euro.centesimi", con il segno meno per gli sconti.
 * Le righe composte vengono salvate in una matrice di caratteri e stampate
 * alla fine, come farebbe il programma della cassa.
 */

#include <stdio.h>

#define ARTICOLI    6
#define RIGHE_MAX   (ARTICOLI + 8)
#define LARGHEZZA   36
#define DIM_RIGA    64                  /* margine: le righe usano 36 caratteri */
#define DIM_EURO    16
#define LUNG_DESCR  30
#define SOGLIA_SCONTO 2000              /* sconto del 10% oltre 20 euro */

void formatta_euro(char dest[], int dim, int centesimi);

int main(void)
{
    char descrizioni[ARTICOLI][LUNG_DESCR] = {
        "Quaderno a quadretti A4", "Penna gel blu", "Evidenziatore",
        "Calcolatrice scientifica", "Righello 30 cm", "Colla stick"
    };
    int prezzi[ARTICOLI] = {250, 180, 120, 1590, 140, 95};
    int quantita[ARTICOLI] = {4, 3, 2, 1, 1, 2};

    char righe[RIGHE_MAX][DIM_RIGA];
    char euro[DIM_EURO];
    int n_righe = 0;
    int k;
    int importo;
    int totale = 0;
    int sconto = 0;
    int pezzi = 0;

    snprintf(righe[n_righe], sizeof(righe[n_righe]), "%s", "      CARTOLERIA IL QUADERNO");
    n_righe++;
    snprintf(righe[n_righe], sizeof(righe[n_righe]), "%s", "------------------------------------");
    n_righe++;

    for (k = 0; k < ARTICOLI; k++) {
        importo = prezzi[k] * quantita[k];
        totale = totale + importo;
        pezzi = pezzi + quantita[k];
        formatta_euro(euro, DIM_EURO, importo);
        snprintf(righe[n_righe], sizeof(righe[n_righe]), "%-18.18s %3d x %9s",
                 descrizioni[k], quantita[k], euro);
        n_righe++;
    }

    snprintf(righe[n_righe], sizeof(righe[n_righe]), "%s", "------------------------------------");
    n_righe++;
    formatta_euro(euro, DIM_EURO, totale);
    snprintf(righe[n_righe], sizeof(righe[n_righe]), "%-18s %3d   %9s",
             "SUBTOTALE", pezzi, euro);
    n_righe++;
    if (totale > SOGLIA_SCONTO) {
        sconto = totale / 10;
        formatta_euro(euro, DIM_EURO, -sconto);
        snprintf(righe[n_righe], sizeof(righe[n_righe]), "%-24s %9s",
                 "Sconto 10%", euro);
        n_righe++;
    }
    totale = totale - sconto;
    formatta_euro(euro, DIM_EURO, totale);
    snprintf(righe[n_righe], sizeof(righe[n_righe]), "%-24s %9s",
             "TOTALE EURO", euro);
    n_righe++;

    printf("Righe da stampare: %d (larghezza %d caratteri)\n\n", n_righe, LARGHEZZA);
    for (k = 0; k < n_righe; k++) {
        printf("|%-*s|\n", LARGHEZZA, righe[k]);
    }

    return 0;
}

/* Scrive in dest l'importo in euro con due decimali ("12.50", "-3.70"). */
void formatta_euro(char dest[], int dim, int centesimi)
{
    if (centesimi < 0) {
        snprintf(dest, dim, "-%d.%02d", -centesimi / 100, -centesimi % 100);
    } else {
        snprintf(dest, dim, "%d.%02d", centesimi / 100, centesimi % 100);
    }
}
