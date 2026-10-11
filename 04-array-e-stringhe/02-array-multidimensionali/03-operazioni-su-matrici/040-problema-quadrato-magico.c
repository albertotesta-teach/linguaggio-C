/*
 * 040-problema-quadrato-magico.c
 *
 * Verifica di un quadrato magico
 *
 * Un quadrato magico di ordine N è una matrice N x N che contiene tutti
 * i numeri da 1 a N*N, ciascuno una sola volta, disposti in modo che la
 * somma di ogni riga, di ogni colonna e delle due diagonali sia la stessa:
 * la COSTANTE MAGICA, che vale N * (N*N + 1) / 2 (per N = 4 vale 34).
 *
 * Il quadrato verificato è quello inciso da Albrecht Dürer nel 1514 nella
 * stampa "Melencolia I" (le due celle centrali dell'ultima riga formano
 * proprio l'anno: 15 14). Il programma verifica anche un secondo quadrato,
 * ottenuto scambiando due numeri, che non è più magico.
 *
 * Controlli:
 *   1. ogni numero da 1 a N*N compare una sola volta (array di contatori
 *      indicizzato dal valore, come la tabella delle frequenze);
 *   2. tutte le righe, colonne e diagonali hanno somma uguale alla costante.
 * Il programma stampa le somme sbagliate per far capire DOVE fallisce.
 */

#include <stdio.h>

#define N 4
#define MAX_VALORE (N * N)

int main(void)
{
    int quadrati[2][N][N] = {
        {
            {16,  3,  2, 13},
            { 5, 10, 11,  8},
            { 9,  6,  7, 12},
            { 4, 15, 14,  1}
        },
        {
            {16,  3,  2, 13},
            { 5, 10, 11,  8},
            { 9,  7,  6, 12},       /* 6 e 7 scambiati */
            { 4, 15, 14,  1}
        }
    };
    int conteggio[MAX_VALORE + 1];      /* indice = valore, da 1 a N*N */
    int k;
    int i;
    int j;
    int valore;
    int costante = N * (N * N + 1) / 2;
    int somma;
    int numeri_validi;
    int somme_corrette;

    for (k = 0; k < 2; k++) {
        printf("=== Quadrato %d ===\n", k + 1);
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf("%4d", quadrati[k][i][j]);
            }
            printf("\n");
        }

        /* ── 1. Numeri da 1 a N*N, ciascuno una volta ─────────────── */
        for (valore = 0; valore <= MAX_VALORE; valore++) {
            conteggio[valore] = 0;
        }
        numeri_validi = 1;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                valore = quadrati[k][i][j];
                if (valore < 1 || valore > MAX_VALORE) {
                    numeri_validi = 0;
                } else {
                    conteggio[valore]++;
                }
            }
        }
        for (valore = 1; valore <= MAX_VALORE; valore++) {
            if (conteggio[valore] != 1) {
                numeri_validi = 0;
            }
        }
        printf("Numeri da 1 a %d presenti una volta: %s\n",
               MAX_VALORE, numeri_validi ? "si'" : "no");

        /* ── 2. Somme ────────────────────────────────────────────── */
        printf("Costante magica attesa: %d\n", costante);
        somme_corrette = 1;

        for (i = 0; i < N; i++) {
            somma = 0;
            for (j = 0; j < N; j++) {
                somma = somma + quadrati[k][i][j];
            }
            if (somma != costante) {
                printf("  riga %d: somma %d\n", i + 1, somma);
                somme_corrette = 0;
            }
        }

        for (j = 0; j < N; j++) {
            somma = 0;
            for (i = 0; i < N; i++) {
                somma = somma + quadrati[k][i][j];
            }
            if (somma != costante) {
                printf("  colonna %d: somma %d\n", j + 1, somma);
                somme_corrette = 0;
            }
        }

        somma = 0;
        for (i = 0; i < N; i++) {
            somma = somma + quadrati[k][i][i];
        }
        if (somma != costante) {
            printf("  diagonale principale: somma %d\n", somma);
            somme_corrette = 0;
        }

        somma = 0;
        for (i = 0; i < N; i++) {
            somma = somma + quadrati[k][i][N - 1 - i];
        }
        if (somma != costante) {
            printf("  diagonale secondaria: somma %d\n", somma);
            somme_corrette = 0;
        }

        if (numeri_validi && somme_corrette) {
            printf("Esito: QUADRATO MAGICO\n\n");
        } else {
            printf("Esito: non e' un quadrato magico\n\n");
        }
    }

    /*
     * NOTA: quadrati[2][N][N] è un array a TRE dimensioni: due matrici
     * 4 x 4 una dopo l'altra. quadrati[k] è la matrice k, quadrati[k][i]
     * la sua riga i. Serve solo a verificare due esempi con lo stesso
     * codice; le matrici a più di due dimensioni seguono le stesse regole.
     */

    return 0;
}
