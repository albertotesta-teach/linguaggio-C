/*
 * 040-problema-riga-di-lunghezza-qualsiasi.c
 *
 * Le risposte aperte del questionario: righe di lunghezza qualsiasi
 *
 * Nel questionario di fine anno le risposte aperte possono essere di
 * poche parole o di un paragrafo intero. Con un buffer fisso le risposte
 * lunghe verrebbero tagliate. La funzione
 *
 *     char *leggi_riga(int *ingrandimenti);
 *
 * legge un carattere alla volta con getchar in un blocco che parte da 16
 * byte e cresce di 16 quando è pieno; alla fine riduce il blocco alla
 * lunghezza esatta (strlen + 1). Restituisce NULL a fine input (o se la
 * memoria non basta) e conta in *ingrandimenti quante realloc di
 * crescita sono servite.
 *
 * Il programma legge le risposte fino a una riga con FINE, le conserva
 * in un array di puntatori (al massimo 10), poi stampa per ognuna la
 * lunghezza e le prime parole, e la risposta più lunga per intero.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSO 16
#define MAX_RISPOSTE 10
#define ANTEPRIMA 30

char *leggi_riga(int *ingrandimenti);

int main(void)
{
    char *risposte[MAX_RISPOSTE];
    char *riga;
    int n = 0;
    int finito = 0;
    int ingrandimenti;
    int piu_lunga = 0;
    int i;

    printf("Risposte (FINE per terminare):\n");
    while (!finito && n < MAX_RISPOSTE) {
        riga = leggi_riga(&ingrandimenti);
        if (riga == NULL) {
            finito = 1;
        } else if (strcmp(riga, "FINE") == 0) {
            free(riga);
            finito = 1;
        } else if (riga[0] == '\0') {
            free(riga);
        } else {
            printf("  %zu caratteri, ingrandimenti del blocco: %d\n", strlen(riga),
                   ingrandimenti);
            risposte[n] = riga;
            if (strlen(riga) > strlen(risposte[piu_lunga])) {
                piu_lunga = n;
            }
            n++;
        }
    }

    printf("\nRisposte raccolte: %d\n", n);
    for (i = 0; i < n; i++) {
        printf("  %d. (%3zu) %.*s%s\n", i + 1, strlen(risposte[i]), ANTEPRIMA, risposte[i],
               strlen(risposte[i]) > ANTEPRIMA ? "..." : "");
    }
    if (n > 0) {
        printf("La piu' lunga per intero:\n  %s\n", risposte[piu_lunga]);
    }
    for (i = 0; i < n; i++) {
        free(risposte[i]);
    }

    return 0;
}

char *leggi_riga(int *ingrandimenti)
{
    char *testo = malloc(PASSO * sizeof *testo);
    char *tmp;
    int capienza = PASSO;
    int lunghezza = 0;
    int c = 0;
    int ok = testo != NULL;

    *ingrandimenti = 0;
    if (ok) {
        c = getchar();
    }
    while (ok && c != '\n' && c != EOF) {
        if (lunghezza + 1 == capienza) {
            tmp = realloc(testo, (capienza + PASSO) * sizeof *tmp);
            if (tmp == NULL) {
                ok = 0;
            } else {
                testo = tmp;
                capienza = capienza + PASSO;
                (*ingrandimenti)++;
            }
        }
        if (ok) {
            testo[lunghezza] = (char) c;
            lunghezza++;
            c = getchar();
        }
    }

    if (!ok || (c == EOF && lunghezza == 0)) {
        free(testo);
        testo = NULL;
    } else {
        testo[lunghezza] = '\0';
        tmp = realloc(testo, (lunghezza + 1) * sizeof *tmp);
        if (tmp != NULL) {
            testo = tmp;
        }
    }
    return testo;
}
