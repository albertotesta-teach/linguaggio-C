/*
 * 010-somme-per-riga-e-colonna.c
 *
 * Totali di riga, totali di colonna e totale generale
 *
 * Il pattern accumulatore (array monodimensionali, 03-operazioni-su-array)
 * si applica alle matrici in tre modi:
 *
 *   TOTALE DI RIGA      per ogni riga si somma lungo le colonne
 *   TOTALE DI COLONNA   per ogni colonna si somma lungo le righe
 *   TOTALE GENERALE     somma di tutti gli elementi
 *
 * Esempio: ore di straordinario di 4 reparti nei 5 giorni lavorativi.
 * Il programma stampa la tabella "con i margini", come un foglio di
 * calcolo: una colonna finale con i totali di riga e una riga finale con
 * i totali di colonna. Il totale generale, nell'angolo in basso a destra,
 * deve coincidere sia con la somma dei totali di riga sia con quella dei
 * totali di colonna: è un controllo di correttezza.
 */

#include <stdio.h>

#define REPARTI 4
#define GIORNI  5

int main(void)
{
    int ore[REPARTI][GIORNI] = {
        {2, 0, 3, 1, 4},
        {5, 6, 2, 4, 3},
        {0, 1, 0, 2, 1},
        {3, 2, 4, 5, 6}
    };
    int r;
    int g;
    int totale_riga;
    int totale_colonna;
    int somma_totali_righe = 0;
    int somma_totali_colonne = 0;
    int totale_generale = 0;

    printf("=== ORE DI STRAORDINARIO PER REPARTO ===\n\n");
    printf("              Lun  Mar  Mer  Gio  Ven   Totale\n");

    /* ── 1. Righe con il loro totale ──────────────────────────────── */
    for (r = 0; r < REPARTI; r++) {
        totale_riga = 0;                        /* azzerato per ogni riga */
        printf("  Reparto %d  ", r + 1);
        for (g = 0; g < GIORNI; g++) {
            printf("%5d", ore[r][g]);
            totale_riga = totale_riga + ore[r][g];
        }
        printf("%9d\n", totale_riga);
        somma_totali_righe = somma_totali_righe + totale_riga;
    }

    /* ── 2. Riga finale con i totali di colonna ───────────────────── */
    printf("  ---------------------------------------------\n");
    printf("  Totale     ");
    for (g = 0; g < GIORNI; g++) {
        totale_colonna = 0;                     /* azzerato per ogni colonna */
        for (r = 0; r < REPARTI; r++) {
            totale_colonna = totale_colonna + ore[r][g];
        }
        printf("%5d", totale_colonna);
        somma_totali_colonne = somma_totali_colonne + totale_colonna;
    }

    /* ── 3. Totale generale: un unico accumulatore su tutte le celle ─ */
    for (r = 0; r < REPARTI; r++) {
        for (g = 0; g < GIORNI; g++) {
            totale_generale = totale_generale + ore[r][g];
        }
    }
    printf("%9d\n\n", totale_generale);

    printf("Somma dei totali di riga    : %d\n", somma_totali_righe);
    printf("Somma dei totali di colonna : %d\n", somma_totali_colonne);
    printf("Totale generale             : %d\n", totale_generale);
    printf("Media per reparto al giorno : %.2f ore\n",
           (double) totale_generale / (REPARTI * GIORNI));

    /*
     * ERRORE COMUNE: azzerare l'accumulatore nel posto sbagliato.
     *
     *     totale_riga = 0;                      // prima di TUTTI i cicli
     *     for (r = 0; r < REPARTI; r++) {
     *         for (g = 0; g < GIORNI; g++) { totale_riga += ore[r][g]; }
     *         printf("%d", totale_riga);        // somma cumulativa, non di riga
     *     }
     *
     * L'accumulatore di una riga va azzerato all'inizio di OGNI riga,
     * cioè dentro il ciclo esterno e prima di quello interno.
     */

    return 0;
}
