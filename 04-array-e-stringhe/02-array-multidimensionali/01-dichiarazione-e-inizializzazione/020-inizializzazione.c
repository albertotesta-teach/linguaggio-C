/*
 * 020-inizializzazione.c
 *
 * Inizializzare una matrice al momento della dichiarazione
 *
 * Come per gli array monodimensionali, una matrice si può inizializzare
 * con una lista di valori tra graffe. Si usano graffe ANNIDATE: una coppia
 * di graffe per ogni riga.
 *
 *     int m[2][3] = {
 *         {1, 2, 3},      riga 0
 *         {4, 5, 6}       riga 1
 *     };
 *
 * Questo file mostra:
 *   1. inizializzazione completa con graffe annidate
 *   2. inizializzazione parziale: le celle non indicate valgono 0
 *   3. azzeramento di tutta la matrice con {0}
 *   4. numero di righe dedotto dal compilatore
 *   5. una sola lista "piatta" senza graffe interne (da evitare)
 */

#include <stdio.h>

#define RIGHE   3
#define COLONNE 4

int main(void)
{
    int riga;
    int colonna;

    /* ── 1. Inizializzazione completa ─────────────────────────────── */
    int completa[RIGHE][COLONNE] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12}
    };

    /* ── 2. Inizializzazione parziale ─────────────────────────────────
     * In ogni riga si indicano solo i primi valori: il resto vale 0.
     * La riga 2 non compare: è tutta a zero.                           */
    int parziale[RIGHE][COLONNE] = {
        {7},
        {1, 2}
    };

    /* ── 3. Tutta a zero ──────────────────────────────────────────── */
    int zeri[RIGHE][COLONNE] = {0};

    /* ── 4. Numero di righe dedotto ───────────────────────────────────
     * La PRIMA dimensione si può omettere: il compilatore conta le
     * righe. La seconda (le colonne) va SEMPRE indicata, perché serve
     * a sapere dove finisce una riga e inizia la successiva.           */
    int dedotta[][COLONNE] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80}
    };
    int righe_dedotte = sizeof(dedotta) / sizeof(dedotta[0]);

    /* ── 5. Lista piatta ──────────────────────────────────────────────
     * Senza graffe interne i valori riempiono la matrice riga per riga.
     * È corretto ma meno leggibile, e gcc con -Wextra segnala
     * "missing braces": nel corso si usano sempre le graffe annidate.
     *
     *     int piatta[2][3] = {1, 2, 3, 4, 5, 6};                       */

    printf("=== 1. Completa ===\n");
    for (riga = 0; riga < RIGHE; riga++) {
        for (colonna = 0; colonna < COLONNE; colonna++) {
            printf("%4d", completa[riga][colonna]);
        }
        printf("\n");
    }

    printf("\n=== 2. Parziale: {7}, {1, 2} ===\n");
    for (riga = 0; riga < RIGHE; riga++) {
        for (colonna = 0; colonna < COLONNE; colonna++) {
            printf("%4d", parziale[riga][colonna]);
        }
        printf("\n");
    }

    printf("\n=== 3. Tutta a zero: {0} ===\n");
    for (riga = 0; riga < RIGHE; riga++) {
        for (colonna = 0; colonna < COLONNE; colonna++) {
            printf("%4d", zeri[riga][colonna]);
        }
        printf("\n");
    }

    printf("\n=== 4. Righe dedotte dal compilatore: %d ===\n", righe_dedotte);
    for (riga = 0; riga < righe_dedotte; riga++) {
        for (colonna = 0; colonna < COLONNE; colonna++) {
            printf("%4d", dedotta[riga][colonna]);
        }
        printf("\n");
    }

    /*
     * ERRORI COMUNI
     *
     * 1) Omettere il numero di colonne:
     *        int m[][] = {{1, 2}, {3, 4}};     // ERRORE di compilazione
     *
     * 2) Più valori delle colonne dichiarate in una riga:
     *        int m[2][3] = {{1, 2, 3, 4}, {5, 6, 7}};   // warning: troppi valori
     *
     * 3) Credere che una matrice dichiarata senza inizializzazione valga 0:
     *        int m[3][4];                       // valori casuali
     *    Solo le matrici inizializzate (anche con {0}) partono da zero.
     */

    return 0;
}
