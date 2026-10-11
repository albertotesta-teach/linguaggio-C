/*
 * 010-accesso-per-indici.c
 *
 * Accedere ai singoli elementi di una matrice
 *
 * Un elemento si legge o si scrive indicando riga e colonna:
 *     valore = m[riga][colonna];      lettura
 *     m[riga][colonna] = valore;      scrittura
 *
 * Gli indici possono essere costanti, variabili o espressioni. Come per
 * gli array, il C NON controlla che siano validi: un accesso fuori dalla
 * matrice produce un comportamento indefinito. Prima di usare indici che
 * arrivano dall'esterno (input, calcoli) va verificato che siano entrambi
 * nell'intervallo corretto:
 *
 *     riga >= 0 && riga < RIGHE && colonna >= 0 && colonna < COLONNE
 *
 * Il file mostra anche come raggiungere le celle VICINE a una cella data
 * (sopra, sotto, a sinistra, a destra), operazione frequente nei giochi
 * su griglia e nell'elaborazione di immagini.
 */

#include <stdio.h>

#define RIGHE   4
#define COLONNE 5

int main(void)
{
    int quote[RIGHE][COLONNE] = {
        {120, 135, 150, 140, 130},
        {125, 160, 180, 170, 145},
        {130, 170, 210, 190, 150},
        {110, 140, 160, 150, 125}
    };
    int riga;
    int colonna;
    int r;
    int c;
    int dentro;

    printf("=== Mappa delle altitudini (metri) ===\n");
    for (riga = 0; riga < RIGHE; riga++) {
        for (colonna = 0; colonna < COLONNE; colonna++) {
            printf("%5d", quote[riga][colonna]);
        }
        printf("\n");
    }
    printf("\n");

    /* ── 1. Indici costanti e variabili ───────────────────────────── */
    printf("=== Accesso diretto ===\n");
    printf("quote[0][0] = %d (angolo in alto a sinistra)\n", quote[0][0]);
    printf("quote[%d][%d] = %d (angolo in basso a destra)\n",
           RIGHE - 1, COLONNE - 1, quote[RIGHE - 1][COLONNE - 1]);

    riga = 2;
    colonna = 2;
    printf("quote[riga][colonna] con riga = %d, colonna = %d: %d\n\n",
           riga, colonna, quote[riga][colonna]);

    /* ── 2. Scrittura ─────────────────────────────────────────────── */
    printf("=== Scrittura ===\n");
    printf("Prima:  quote[1][3] = %d\n", quote[1][3]);
    quote[1][3] = quote[1][3] + 5;          /* lettura e scrittura nella stessa istruzione */
    printf("Dopo +5: quote[1][3] = %d\n\n", quote[1][3]);

    /* ── 3. Celle vicine ──────────────────────────────────────────────
     * Le quattro vicine di [riga][colonna] sono:
     *     sopra    [riga - 1][colonna]
     *     sotto    [riga + 1][colonna]
     *     sinistra [riga][colonna - 1]
     *     destra   [riga][colonna + 1]
     * Per una cella sul bordo alcune vicine non esistono: va controllato. */
    printf("=== Vicine della cella [2][2] (quota %d) ===\n", quote[2][2]);
    riga = 2;
    colonna = 2;
    printf("  sopra    [%d][%d] = %d\n", riga - 1, colonna, quote[riga - 1][colonna]);
    printf("  sotto    [%d][%d] = %d\n", riga + 1, colonna, quote[riga + 1][colonna]);
    printf("  sinistra [%d][%d] = %d\n", riga, colonna - 1, quote[riga][colonna - 1]);
    printf("  destra   [%d][%d] = %d\n\n", riga, colonna + 1, quote[riga][colonna + 1]);

    /* ── 4. Accesso sicuro ────────────────────────────────────────────
     * Per la cella [0][4] (angolo in alto a destra) le vicine "sopra" e
     * "destra" sarebbero fuori dalla matrice: si controllano gli indici
     * prima di leggere.                                                */
    printf("=== Vicine della cella [0][4] con controllo dei limiti ===\n");
    riga = 0;
    colonna = 4;

    r = riga - 1;
    c = colonna;
    dentro = (r >= 0 && r < RIGHE && c >= 0 && c < COLONNE);
    if (dentro) {
        printf("  sopra    = %d\n", quote[r][c]);
    } else {
        printf("  sopra    : fuori dalla mappa\n");
    }

    r = riga + 1;
    dentro = (r >= 0 && r < RIGHE && c >= 0 && c < COLONNE);
    if (dentro) {
        printf("  sotto    = %d\n", quote[r][c]);
    } else {
        printf("  sotto    : fuori dalla mappa\n");
    }

    r = riga;
    c = colonna - 1;
    dentro = (r >= 0 && r < RIGHE && c >= 0 && c < COLONNE);
    if (dentro) {
        printf("  sinistra = %d\n", quote[r][c]);
    } else {
        printf("  sinistra : fuori dalla mappa\n");
    }

    c = colonna + 1;
    dentro = (r >= 0 && r < RIGHE && c >= 0 && c < COLONNE);
    if (dentro) {
        printf("  destra   = %d\n", quote[r][c]);
    } else {
        printf("  destra   : fuori dalla mappa\n");
    }

    /*
     * ERRORE COMUNE: controllare solo un indice.
     *     if (r < RIGHE) { ... quote[r][c] ... }
     * Anche c deve essere nel suo intervallo, e entrambi devono essere
     * >= 0: c = -1 sulla riga 1 leggerebbe in realtà l'ultima cella della
     * riga 0 (le righe sono contigue in memoria), un errore difficile da
     * notare perché il programma non si blocca.
     */

    return 0;
}
