/*
 * 010-dichiarazione-base.c
 *
 * Dichiarazione di un array bidimensionale (matrice)
 *
 * Un array monodimensionale è una riga di celle; un array bidimensionale
 * è una TABELLA di celle organizzate in righe e colonne, tutte dello
 * stesso tipo. Si dichiara indicando due dimensioni:
 *
 *     tipo nome[RIGHE][COLONNE];
 *
 * Ogni elemento si individua con due indici: prima la riga, poi la colonna.
 * Entrambi partono da 0:
 *
 *                 colonna 0   colonna 1   colonna 2   colonna 3
 *     riga 0   [  m[0][0]     m[0][1]     m[0][2]     m[0][3]  ]
 *     riga 1   [  m[1][0]     m[1][1]     m[1][2]     m[1][3]  ]
 *     riga 2   [  m[2][0]     m[2][1]     m[2][2]     m[2][3]  ]
 *
 * Le dimensioni si definiscono con #define: così i cicli e le
 * dichiarazioni usano lo stesso valore e lo si cambia in un solo punto.
 */

#include <stdio.h>

#define RIGHE   3
#define COLONNE 4

int main(void)
{
    int m[RIGHE][COLONNE];      /* 3 x 4 = 12 interi, valori non inizializzati */
    int riga;
    int colonna;
    int totale_celle;

    /* ── 1. Assegnazione di un valore a ogni cella ────────────────────
     * Il valore di ogni cella è calcolato dai suoi indici:
     *     m[riga][colonna] = riga * 10 + colonna
     * così, leggendo il numero, si capisce in quale cella si trova
     * (es. 23 = riga 2, colonna 3).                                     */
    for (riga = 0; riga < RIGHE; riga++) {
        for (colonna = 0; colonna < COLONNE; colonna++) {
            m[riga][colonna] = riga * 10 + colonna;
        }
    }

    /* ── 2. Stampa come tabella ───────────────────────────────────── */
    printf("=== Matrice %d x %d ===\n", RIGHE, COLONNE);
    printf("          ");
    for (colonna = 0; colonna < COLONNE; colonna++) {
        printf(" col %d", colonna);
    }
    printf("\n");

    for (riga = 0; riga < RIGHE; riga++) {
        printf("  riga %d  ", riga);
        for (colonna = 0; colonna < COLONNE; colonna++) {
            printf("%6d", m[riga][colonna]);
        }
        printf("\n");
    }
    printf("\n");

    /* ── 3. Accesso a singoli elementi ──────────────────────────────── */
    printf("=== Singoli elementi ===\n");
    printf("m[0][0] = %d   (primo elemento)\n", m[0][0]);
    printf("m[1][2] = %d   (riga 1, colonna 2)\n", m[1][2]);
    printf("m[%d][%d] = %d   (ultimo elemento)\n",
           RIGHE - 1, COLONNE - 1, m[RIGHE - 1][COLONNE - 1]);

    m[1][2] = 99;
    printf("Dopo m[1][2] = 99: m[1][2] = %d\n\n", m[1][2]);

    /* ── 4. Numero di elementi ────────────────────────────────────── */
    totale_celle = RIGHE * COLONNE;
    printf("=== Dimensioni ===\n");
    printf("Righe: %d, colonne: %d, elementi: %d\n", RIGHE, COLONNE, totale_celle);
    printf("Indici di riga validi:    da 0 a %d\n", RIGHE - 1);
    printf("Indici di colonna validi: da 0 a %d\n", COLONNE - 1);

    /*
     * ERRORI COMUNI
     *
     * 1) Scrivere gli indici come in altri linguaggi:
     *        m[1, 2] = 5;       // ERRATO in C: la virgola è un operatore,
     *                           // l'espressione vale m[2] (una riga intera)
     *        m[1][2] = 5;       // corretto
     *
     * 2) Scambiare righe e colonne: m[colonna][riga] invece di
     *    m[riga][colonna]. Con matrici non quadrate si esce dai limiti.
     *
     * 3) Usare RIGHE come ultimo indice: m[RIGHE][0] è fuori dalla
     *    matrice, perché l'ultima riga ha indice RIGHE - 1.
     */

    return 0;
}
