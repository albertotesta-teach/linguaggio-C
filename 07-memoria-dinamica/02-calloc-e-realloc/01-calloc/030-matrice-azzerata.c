/*
 * 030-matrice-azzerata.c
 *
 * Una matrice in un solo blocco, azzerata da calloc
 *
 * Una matrice di righe x colonne si alloca in un unico blocco, con le
 * righe una dopo l'altra (01-malloc-e-free). Con calloc tutte le celle
 * partono da zero:
 *
 *     double *punti = calloc(n * n, sizeof *punti);
 *
 *     punti[i * n + j]      punti ottenuti da i nella partita contro j
 *
 * calloc mette a zero i BYTE. Per gli interi questo significa 0. Per i
 * double e per i puntatori lo standard non lo garantisce, ma su tutte le
 * macchine di uso comune (che usano IEEE 754 e un NULL fatto di soli
 * zeri) i byte a zero valgono 0.0 e NULL. In questo corso si conta su
 * questo comportamento, scrivendolo in un commento quando serve.
 *
 * Esempio: il torneo di scacchi tra 4 studenti, tutti contro tutti. Ogni
 * partita dà 1 punto a chi vince, 0.5 a testa per la patta. La tabella
 * parte vuota (tutti zeri) e si riempie con i risultati; alla fine si
 * stampano la tabella e i totali.
 */

#include <stdio.h>
#include <stdlib.h>

#define GIOCATORI 4
#define PARTITE 6

int main(void)
{
    const char *nomi[GIOCATORI] = {"Marta", "Luca", "Sara", "Paolo"};
    /* bianco, nero, risultato: 1 vince il bianco, 0 patta, -1 vince il nero */
    int partite[PARTITE][3] = {{0, 1, 1}, {2, 3, 0}, {0, 2, -1}, {1, 3, 1}, {0, 3, 0}, {1, 2, 0}};
    double *punti = calloc(GIOCATORI * GIOCATORI, sizeof *punti);
    double totale;
    int a;
    int b;
    int i;
    int j;
    int k;

    if (punti == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        for (k = 0; k < PARTITE; k++) {
            a = partite[k][0];
            b = partite[k][1];
            if (partite[k][2] == 1) {
                punti[a * GIOCATORI + b] = 1;
            } else if (partite[k][2] == -1) {
                punti[b * GIOCATORI + a] = 1;
            } else {
                punti[a * GIOCATORI + b] = 0.5;
                punti[b * GIOCATORI + a] = 0.5;
            }
        }

        printf("%-7s", "");
        for (j = 0; j < GIOCATORI; j++) {
            printf("%7s", nomi[j]);
        }
        printf("  totale\n");
        for (i = 0; i < GIOCATORI; i++) {
            totale = 0;
            printf("%-7s", nomi[i]);
            for (j = 0; j < GIOCATORI; j++) {
                if (i == j) {
                    printf("%7s", "-");
                } else {
                    printf("%7.1f", punti[i * GIOCATORI + j]);
                }
                totale = totale + punti[i * GIOCATORI + j];
            }
            printf("  %6.1f\n", totale);
        }
        free(punti);
    }

    return 0;
}
