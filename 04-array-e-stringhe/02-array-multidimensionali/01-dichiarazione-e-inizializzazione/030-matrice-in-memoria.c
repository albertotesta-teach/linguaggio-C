/*
 * 030-matrice-in-memoria.c
 *
 * Come è disposta una matrice nella memoria
 *
 * La memoria del computer è una sequenza lineare di celle: non esistono
 * "righe" e "colonne". Il C memorizza una matrice RIGA DOPO RIGA
 * (ordine "row-major"): prima tutti gli elementi della riga 0, poi quelli
 * della riga 1, e così via.
 *
 *     int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
 *
 *     memoria:  | 1 | 2 | 3 | 4 | 5 | 6 |
 *                 riga 0      riga 1
 *
 * Una matrice è quindi un "array di array": m[0] e m[1] sono due array
 * di 3 interi messi uno dopo l'altro.
 *
 * Il file mostra anche un caso già incontrato: un elenco di nomi
 * dichiarato come char nomi[N][LEN] è una matrice di caratteri, in cui
 * ogni riga contiene una parola.
 */

#include <stdio.h>

#define RIGHE   2
#define COLONNE 3
#define NUM_NOMI 3
#define LUNG_NOME 8

int main(void)
{
    int m[RIGHE][COLONNE] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    char nomi[NUM_NOMI][LUNG_NOME] = {
        "Anna",
        "Luca",
        "Giulia"
    };
    int riga;
    int colonna;
    int posizione;

    /* ── 1. Dimensioni con sizeof ──────────────────────────────────── */
    printf("=== Dimensioni in byte ===\n");
    printf("sizeof(m)       = %2lu byte (tutta la matrice)\n", (unsigned long) sizeof(m));
    printf("sizeof(m[0])    = %2lu byte (una riga di %d interi)\n",
           (unsigned long) sizeof(m[0]), COLONNE);
    printf("sizeof(m[0][0]) = %2lu byte (un elemento)\n", (unsigned long) sizeof(m[0][0]));
    printf("Righe   = sizeof(m) / sizeof(m[0])       = %lu\n",
           (unsigned long) (sizeof(m) / sizeof(m[0])));
    printf("Colonne = sizeof(m[0]) / sizeof(m[0][0]) = %lu\n\n",
           (unsigned long) (sizeof(m[0]) / sizeof(m[0][0])));

    /* ── 2. Posizione di ogni elemento nella sequenza ──────────────────
     * In una matrice di COLONNE colonne, l'elemento [riga][colonna]
     * si trova nella posizione  riga * COLONNE + colonna
     * contando dall'inizio della matrice.                              */
    printf("=== Ordine in memoria (riga per riga) ===\n");
    printf("  Posizione | Elemento | Valore\n");
    printf("  ----------|----------|-------\n");
    for (riga = 0; riga < RIGHE; riga++) {
        for (colonna = 0; colonna < COLONNE; colonna++) {
            posizione = riga * COLONNE + colonna;
            printf("  %9d | m[%d][%d]  | %5d\n", posizione, riga, colonna, m[riga][colonna]);
        }
    }
    printf("\n");

    /* ── 3. Una matrice di caratteri: l'elenco di nomi ─────────────────
     * nomi[i] è la riga i: un array di LUNG_NOME caratteri che contiene
     * una parola terminata da '\0'. nomi[i][j] è il singolo carattere.  */
    printf("=== Matrice di caratteri char nomi[%d][%d] ===\n", NUM_NOMI, LUNG_NOME);
    for (riga = 0; riga < NUM_NOMI; riga++) {
        printf("  nomi[%d] = %-7s  caratteri:", riga, nomi[riga]);
        colonna = 0;
        while (nomi[riga][colonna] != '\0') {
            printf(" %c", nomi[riga][colonna]);
            colonna++;
        }
        printf("\n");
    }
    printf("  nomi[2][0] = '%c'  (prima lettera della riga 2)\n", nomi[2][0]);

    /*
     * NOTA
     * Poiché le righe sono contigue, la cella che segue m[0][2] in memoria
     * è m[1][0]. Per questo il C ha bisogno di conoscere il numero di
     * COLONNE: senza di esso non saprebbe dove inizia ogni riga
     * (lo si vedrà nel passaggio di una matrice a una funzione, sezione 04).
     */

    return 0;
}
