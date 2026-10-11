/*
 * 030-cicli-annidati.c
 *
 * Cicli annidati: un ciclo dentro un altro
 *
 * Quando il corpo di un ciclo contiene un altro ciclo, per OGNI iterazione
 * del ciclo esterno il ciclo interno viene eseguito COMPLETAMENTE.
 *
 *     for (riga = 1; riga <= 3; riga++) {          esterno: 3 volte
 *         for (colonna = 1; colonna <= 4; colonna++) {   interno: 4 volte
 *             ...                                  eseguito 3 x 4 = 12 volte
 *         }
 *     }
 *
 * Schema tipico: il ciclo esterno scorre le RIGHE, quello interno le
 * COLONNE; il "a capo" si stampa alla fine di ogni riga, fuori dal
 * ciclo interno.
 *
 * Le due variabili di controllo devono essere diverse.
 */

#include <stdio.h>

int main(void)
{
    int riga;
    int colonna;
    int esecuzioni = 0;

    /* ── 1. Tavola pitagorica ─────────────────────────────────────── */
    printf("=== Tavola pitagorica ===\n");
    printf("    |");
    for (colonna = 1; colonna <= 10; colonna++) {
        printf("%4d", colonna);
    }
    printf("\n----+");
    for (colonna = 1; colonna <= 10; colonna++) {
        printf("----");
    }
    printf("\n");

    for (riga = 1; riga <= 10; riga++) {
        printf("%3d |", riga);
        for (colonna = 1; colonna <= 10; colonna++) {
            printf("%4d", riga * colonna);
            esecuzioni++;
        }
        printf("\n");           /* a capo: fine della riga */
    }
    printf("Il corpo del ciclo interno e' stato eseguito %d volte (10 x 10).\n\n",
           esecuzioni);

    /* ── 2. Rettangolo di asterischi ──────────────────────────────── */
    printf("=== Rettangolo 3 x 8 ===\n");
    for (riga = 1; riga <= 3; riga++) {
        for (colonna = 1; colonna <= 8; colonna++) {
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

    /* ── 3. Triangolo: il ciclo interno dipende dall'esterno ──────────
     * Nella riga 1 si stampa 1 asterisco, nella riga 2 due, ...
     * La condizione del ciclo interno usa la variabile "riga".         */
    printf("=== Triangolo di altezza 5 ===\n");
    for (riga = 1; riga <= 5; riga++) {
        for (colonna = 1; colonna <= riga; colonna++) {
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

    /* ── 4. Numeri in una griglia ─────────────────────────────────── */
    printf("=== Coordinate (riga, colonna) ===\n");
    for (riga = 1; riga <= 3; riga++) {
        for (colonna = 1; colonna <= 3; colonna++) {
            printf("(%d,%d) ", riga, colonna);
        }
        printf("\n");
    }

    /*
     * ERRORI COMUNI
     *
     * 1) Stessa variabile nei due cicli:
     *        for (i = 1; i <= 3; i++) {
     *            for (i = 1; i <= 4; i++) { ... }   // l'interno modifica i:
     *        }                                       // l'esterno non funziona più
     *
     * 2) "a capo" dentro il ciclo interno: ogni asterisco finisce su una
     *    riga diversa.
     *
     * 3) Dimenticare che le iterazioni si MOLTIPLICANO: due cicli da 1000
     *    annidati eseguono il corpo un milione di volte.
     */

    return 0;
}
