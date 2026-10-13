/*
 * 020-puntatore-temporaneo.c
 *
 * Il risultato di realloc va in un puntatore temporaneo
 *
 * Se realloc non trova memoria restituisce NULL e NON libera il blocco
 * vecchio, che resta valido con i suoi dati. Per questo questa forma è
 * SBAGLIATA:
 *
 *     v = realloc(v, nuovi_byte);       se fallisce, v diventa NULL:
 *                                       il blocco vecchio è perso (leak)
 *
 * La forma corretta usa un puntatore temporaneo:
 *
 *     tmp = realloc(v, nuovi_byte);
 *     if (tmp == NULL) {
 *         ... v è ancora valido: si continua con la dimensione vecchia ...
 *     } else {
 *         v = tmp;
 *         n = nuova_n;                  la dimensione si aggiorna solo ora
 *     }
 *
 * Esempio: l'elenco dei libri di una classe, che si prova a portare a
 * dimensioni sempre più grandi. L'ultima richiesta è impossibile
 * (SIZE_MAX / 8 elementi da 4 byte: metà di tutti gli indirizzi
 * possibili, milioni di terabyte): realloc restituisce NULL,
 * il programma lo dice e continua a usare il blocco che aveva, con i
 * suoi dati intatti.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TENTATIVI 3

int main(void)
{
    size_t richieste[TENTATIVI] = {8, 16, SIZE_MAX / 8};
    int *codici = malloc(4 * sizeof *codici);
    int *tmp;
    size_t n = 4;
    size_t i;
    int k;

    if (codici == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        for (i = 0; i < n; i++) {
            codici[i] = 1001 + (int) i;
        }
        for (k = 0; k < TENTATIVI; k++) {
            printf("Richiesta: da %zu a %zu elementi... ", n, richieste[k]);
            tmp = realloc(codici, richieste[k] * sizeof *codici);
            if (tmp == NULL) {
                printf("non riuscita, il blocco vecchio resta valido\n");
            } else {
                codici = tmp;
                for (i = n; i < richieste[k]; i++) {
                    codici[i] = 1001 + (int) i;
                }
                n = richieste[k];
                printf("riuscita\n");
            }
        }

        printf("Elementi disponibili: %zu, primo %d, ultimo %d\n", n, codici[0], codici[n - 1]);
        free(codici);
    }

    return 0;
}
