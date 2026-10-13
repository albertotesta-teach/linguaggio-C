/*
 * 080-problema-crivello-di-eratostene.c
 *
 * Matematica: i numeri primi fino a n con il crivello di Eratostene
 *
 * Il crivello usa un flag per ogni numero da 0 a n: 0 = "forse primo",
 * 1 = "composto". All'inizio nessun numero è stato cancellato, quindi
 * tutti i flag valgono 0: è il caso tipico per calloc.
 *
 *     char *composto = calloc(n + 1, sizeof *composto);
 *
 * Algoritmo: per ogni p da 2 finché p * p <= n, se p non è cancellato
 * è primo, e si cancellano i suoi multipli a partire da p * p (quelli
 * più piccoli sono già stati cancellati da un primo minore).
 *
 * Il programma legge n (fino a un milione: n + 1 byte, circa 1 MB) e
 * stampa quanti primi ci sono, i primi se sono al massimo 30 (altrimenti
 * i primi 10 e gli ultimi 10), e quante coppie di primi gemelli (p e
 * p + 2 entrambi primi).
 */

#include <stdio.h>
#include <stdlib.h>

#define MASSIMO 1000000

int main(void)
{
    char *composto;
    int n;
    int p;
    int m;
    int primi = 0;
    int gemelli = 0;
    int contati = 0;

    printf("Primi fino a (da 2 a %d): ", MASSIMO);
    if (scanf("%d", &n) != 1 || n < 2 || n > MASSIMO) {
        printf("Numero non valido.\n");
    } else {
        composto = calloc(n + 1, sizeof *composto);
        if (composto == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            for (p = 2; p * p <= n; p++) {
                if (!composto[p]) {
                    for (m = p * p; m <= n; m = m + p) {
                        composto[m] = 1;
                    }
                }
            }
            for (p = 2; p <= n; p++) {
                if (!composto[p]) {
                    primi++;
                    if (p + 2 <= n && !composto[p + 2]) {
                        gemelli++;
                    }
                }
            }

            printf("Flag allocati: %d byte\n", n + 1);
            printf("Primi fino a %d: %d\n", n, primi);
            for (p = 2; p <= n; p++) {
                if (!composto[p]) {
                    contati++;
                    if (primi <= 30 || contati <= 10 || contati > primi - 10) {
                        printf(" %d", p);
                    } else if (contati == 11) {
                        printf(" ...");
                    }
                }
            }
            printf("\nCoppie di primi gemelli: %d\n", gemelli);
            free(composto);
        }
    }

    return 0;
}
