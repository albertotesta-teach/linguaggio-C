/*
 * 030-diagonali-e-trasposta.c
 *
 * Operazioni tipiche delle matrici quadrate
 *
 * Una matrice è QUADRATA quando ha lo stesso numero di righe e colonne.
 * In una matrice quadrata N x N:
 *
 *   DIAGONALE PRINCIPALE   gli elementi con riga == colonna
 *                          [0][0], [1][1], ..., [N-1][N-1]
 *   DIAGONALE SECONDARIA   gli elementi con riga + colonna == N - 1
 *                          [0][N-1], [1][N-2], ..., [N-1][0]
 *
 * La TRASPOSTA scambia righe e colonne: t[j][i] = m[i][j]. Vale per
 * qualsiasi matrice: una R x C diventa C x R.
 *
 * Una matrice quadrata è SIMMETRICA se coincide con la sua trasposta,
 * cioè se m[i][j] == m[j][i] per ogni coppia di indici.
 *
 * Per una diagonale basta UN ciclo: l'altro indice si ricava dal primo.
 */

#include <stdio.h>

#define N 4
#define RIGHE   2
#define COLONNE 3

int main(void)
{
    int q[N][N] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int s[N][N] = {
        {2, 7, 1, 0},
        {7, 5, 3, 4},
        {1, 3, 9, 6},
        {0, 4, 6, 8}
    };
    int r[RIGHE][COLONNE] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    int t[COLONNE][RIGHE];
    int i;
    int j;
    int somma_principale = 0;
    int somma_secondaria = 0;
    int simmetrica;
    int appoggio;

    /* ── 1. Diagonali: un solo ciclo ──────────────────────────────── */
    printf("=== Diagonali della matrice 4 x 4 ===\n");
    printf("Principale: ");
    for (i = 0; i < N; i++) {
        printf("%3d", q[i][i]);
        somma_principale = somma_principale + q[i][i];
    }
    printf("   somma = %d\n", somma_principale);

    printf("Secondaria: ");
    for (i = 0; i < N; i++) {
        printf("%3d", q[i][N - 1 - i]);
        somma_secondaria = somma_secondaria + q[i][N - 1 - i];
    }
    printf("   somma = %d\n\n", somma_secondaria);

    /* ── 2. Trasposta di una matrice rettangolare (2 x 3 -> 3 x 2) ────
     * Serve una seconda matrice con le dimensioni scambiate.           */
    for (i = 0; i < RIGHE; i++) {
        for (j = 0; j < COLONNE; j++) {
            t[j][i] = r[i][j];
        }
    }
    printf("=== Trasposta ===\n");
    printf("Originale 2 x 3:      Trasposta 3 x 2:\n");
    for (i = 0; i < COLONNE; i++) {
        if (i < RIGHE) {
            for (j = 0; j < COLONNE; j++) {
                printf("%3d", r[i][j]);
            }
        } else {
            printf("         ");
        }
        printf("            ");
        for (j = 0; j < RIGHE; j++) {
            printf("%3d", t[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* ── 3. Verifica di simmetria ─────────────────────────────────────
     * Basta controllare gli elementi SOPRA la diagonale (j > i): ognuno
     * viene confrontato con il suo "speculare" sotto la diagonale.
     * La verifica si ferma alla prima coppia diversa.                  */
    simmetrica = 1;
    for (i = 0; i < N && simmetrica; i++) {
        for (j = i + 1; j < N && simmetrica; j++) {
            if (s[i][j] != s[j][i]) {
                simmetrica = 0;
            }
        }
    }
    printf("=== Simmetria ===\n");
    printf("La matrice s %s simmetrica.\n", simmetrica ? "e'" : "non e'");

    simmetrica = 1;
    for (i = 0; i < N && simmetrica; i++) {
        for (j = i + 1; j < N && simmetrica; j++) {
            if (q[i][j] != q[j][i]) {
                simmetrica = 0;
            }
        }
    }
    printf("La matrice q %s simmetrica.\n\n", simmetrica ? "e'" : "non e'");

    /* ── 4. Trasposta "sul posto" di una matrice quadrata ─────────────
     * Si scambiano le coppie [i][j] e [j][i] con j > i. Se si scambiasse
     * anche con j < i, ogni coppia verrebbe scambiata due volte e la
     * matrice tornerebbe uguale a prima.                               */
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            appoggio = q[i][j];
            q[i][j] = q[j][i];
            q[j][i] = appoggio;
        }
    }
    printf("=== q trasposta sul posto ===\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%4d", q[i][j]);
        }
        printf("\n");
    }

    return 0;
}
