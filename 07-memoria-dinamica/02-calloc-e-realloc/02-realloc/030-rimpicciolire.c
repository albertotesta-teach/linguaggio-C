/*
 * 030-rimpicciolire.c
 *
 * realloc per ridurre un blocco alla dimensione davvero usata
 *
 * Quando non si sa quanti dati arriveranno, si può allocare un blocco
 * con un massimo ragionevole, riempirlo e poi restituire la parte non
 * usata:
 *
 *     punteggi = malloc(MASSIMO * sizeof *punteggi);
 *     ... lettura di n valori ...
 *     tmp = realloc(punteggi, n * sizeof *punteggi);
 *     if (tmp != NULL) {
 *         punteggi = tmp;
 *     }
 *
 * Ridurre un blocco di solito riesce sul posto; se per qualche motivo
 * realloc restituisce NULL, il blocco grande resta valido e si continua
 * a usarlo.
 *
 * Con n == 0 non si chiama realloc(punteggi, 0): il suo comportamento
 * dipende dalla libreria (03-realloc-in-pratica). Si libera il blocco
 * con free e si mette il puntatore a NULL.
 *
 * Esempio: i punteggi della gara di matematica a squadre, al massimo
 * 200, letti fino a -1 (gli altri valori negativi si ignorano).
 */

#include <stdio.h>
#include <stdlib.h>

#define MASSIMO 200

int main(void)
{
    int *punteggi = malloc(MASSIMO * sizeof *punteggi);
    int *tmp;
    int n = 0;
    int finito = 0;
    int valore;
    int somma = 0;
    int i;

    if (punteggi == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        printf("Blocco iniziale: %d punteggi, %zu byte\n", MASSIMO, MASSIMO * sizeof *punteggi);
        printf("Punteggi delle squadre (-1 per terminare): ");
        while (!finito && n < MASSIMO) {
            if (scanf("%d", &valore) != 1 || valore == -1) {
                finito = 1;
            } else if (valore >= 0) {
                punteggi[n] = valore;
                somma = somma + valore;
                n++;
            }
        }

        if (n == 0) {
            free(punteggi);
            punteggi = NULL;
            printf("Nessun punteggio: blocco liberato.\n");
        } else {
            tmp = realloc(punteggi, n * sizeof *punteggi);
            if (tmp != NULL) {
                punteggi = tmp;
                printf("Blocco ridotto a %d punteggi, %zu byte (restituiti %zu byte)\n", n,
                       n * sizeof *punteggi, (MASSIMO - n) * sizeof *punteggi);
            }
            printf("Punteggi:");
            for (i = 0; i < n; i++) {
                printf(" %d", punteggi[i]);
            }
            printf("\nMedia: %.1f\n", (double) somma / n);
        }
        free(punteggi);
    }

    return 0;
}
