/*
 * 020-scorrimento-righe-e-colonne.c
 *
 * Visitare tutti gli elementi di una matrice
 *
 * Per scorrere una matrice servono due cicli annidati. L'ordine dei
 * cicli decide in che ordine vengono visitati gli elementi:
 *
 *   PER RIGHE (esterno sulle righe, interno sulle colonne)
 *       1  2  3  4      la riga 0 da sinistra a destra,
 *       5  6  7  8      poi la riga 1, ...
 *       9 10 11 12      È l'ordine in cui la matrice è in memoria.
 *
 *   PER COLONNE (esterno sulle colonne, interno sulle righe)
 *       1  4  7 10      la colonna 0 dall'alto in basso,
 *       2  5  8 11      poi la colonna 1, ...
 *       3  6  9 12
 *
 * Il file mostra entrambi gli ordini, lo scorrimento all'indietro, la
 * visita di una sola riga o di una sola colonna e il percorso "a serpente"
 * (le righe alternano la direzione), usato per esempio dai plotter.
 */

#include <stdio.h>

#define RIGHE   3
#define COLONNE 4

int main(void)
{
    int m[RIGHE][COLONNE] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12}
    };
    int riga;
    int colonna;

    /* ── 1. Per righe ─────────────────────────────────────────────── */
    printf("Per righe:          ");
    for (riga = 0; riga < RIGHE; riga++) {
        for (colonna = 0; colonna < COLONNE; colonna++) {
            printf("%3d", m[riga][colonna]);
        }
    }
    printf("\n");

    /* ── 2. Per colonne ───────────────────────────────────────────────
     * Gli indici nell'accesso restano m[riga][colonna]: cambia solo
     * quale ciclo sta fuori.                                           */
    printf("Per colonne:        ");
    for (colonna = 0; colonna < COLONNE; colonna++) {
        for (riga = 0; riga < RIGHE; riga++) {
            printf("%3d", m[riga][colonna]);
        }
    }
    printf("\n");

    /* ── 3. All'indietro ──────────────────────────────────────────── */
    printf("All'indietro:       ");
    for (riga = RIGHE - 1; riga >= 0; riga--) {
        for (colonna = COLONNE - 1; colonna >= 0; colonna--) {
            printf("%3d", m[riga][colonna]);
        }
    }
    printf("\n");

    /* ── 4. Una sola riga: basta un ciclo, la riga è fissa ────────── */
    riga = 1;
    printf("Solo la riga %d:     ", riga);
    for (colonna = 0; colonna < COLONNE; colonna++) {
        printf("%3d", m[riga][colonna]);
    }
    printf("\n");

    /* ── 5. Una sola colonna: la colonna è fissa ──────────────────── */
    colonna = 2;
    printf("Solo la colonna %d:  ", colonna);
    for (riga = 0; riga < RIGHE; riga++) {
        printf("%3d", m[riga][colonna]);
    }
    printf("\n");

    /* ── 6. A serpente ────────────────────────────────────────────────
     * Righe pari da sinistra a destra, righe dispari da destra a
     * sinistra: la direzione si sceglie con un if dentro il ciclo
     * esterno.                                                         */
    printf("A serpente:         ");
    for (riga = 0; riga < RIGHE; riga++) {
        if (riga % 2 == 0) {
            for (colonna = 0; colonna < COLONNE; colonna++) {
                printf("%3d", m[riga][colonna]);
            }
        } else {
            for (colonna = COLONNE - 1; colonna >= 0; colonna--) {
                printf("%3d", m[riga][colonna]);
            }
        }
    }
    printf("\n\n");

    /* ── 7. Stampa come tabella: il "a capo" segna la fine di una riga ─ */
    printf("Come tabella:\n");
    for (riga = 0; riga < RIGHE; riga++) {
        for (colonna = 0; colonna < COLONNE; colonna++) {
            printf("%4d", m[riga][colonna]);
        }
        printf("\n");
    }

    /*
     * ERRORE COMUNE: invertire gli indici quando si invertono i cicli.
     *
     *     for (colonna = 0; colonna < COLONNE; colonna++) {
     *         for (riga = 0; riga < RIGHE; riga++) {
     *             printf("%d", m[colonna][riga]);     // ERRATO
     *         }
     *     }
     *
     * Con una matrice 3 x 4, m[3][...] è fuori dai limiti. L'ordine dei
     * cicli si può scegliere liberamente; l'ordine degli indici no:
     * sempre [riga][colonna].
     */

    return 0;
}
