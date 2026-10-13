/*
 * 050-problema-testo-che-si-allunga.c
 *
 * Il verbale del consiglio di classe, scritto una frase alla volta
 *
 * Il segretario scrive il verbale una frase per riga. Il testo completo
 * sta in un unico blocco che a ogni frase si allunga esattamente di
 * quanto serve: la frase, uno spazio di separazione e il '\0'.
 *
 *     nuova = strlen(verbale) + 1 + strlen(frase) + 1;
 *     tmp = realloc(verbale, nuova);
 *     if (tmp != NULL) {
 *         verbale = tmp;
 *         strcat(verbale, " ");
 *         strcat(verbale, frase);
 *     }
 *
 * Il blocco parte da 1 byte, una stringa vuota. Per la prima frase non
 * serve lo spazio. Una frase che non finisce con un punto riceve il
 * punto finale.
 *
 * Alla fine il verbale si stampa andando a capo prima di superare 60
 * caratteri per riga, senza spezzare le parole, con il numero di
 * caratteri e di frasi.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNG 200
#define LARGHEZZA 60

void stampa_a_righe(const char *testo, int larghezza);

int main(void)
{
    char *verbale = malloc(1);
    char *tmp;
    char frase[LUNG];
    size_t lunghezza;
    size_t nuova;
    int frasi = 0;
    int finito = 0;

    if (verbale == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        verbale[0] = '\0';
        printf("Frasi del verbale (FINE per terminare):\n");
        while (!finito) {
            if (fgets(frase, LUNG - 1, stdin) == NULL) {
                finito = 1;
            } else {
                frase[strcspn(frase, "\n")] = '\0';
                lunghezza = strlen(frase);
                if (strcmp(frase, "FINE") == 0) {
                    finito = 1;
                } else if (lunghezza > 0) {
                    if (frase[lunghezza - 1] != '.') {
                        strcat(frase, ".");
                        lunghezza++;
                    }
                    nuova = strlen(verbale) + (frasi > 0 ? 1 : 0) + lunghezza + 1;
                    tmp = realloc(verbale, nuova);
                    if (tmp == NULL) {
                        printf("Memoria insufficiente: frase non aggiunta.\n");
                    } else {
                        verbale = tmp;
                        if (frasi > 0) {
                            strcat(verbale, " ");
                        }
                        strcat(verbale, frase);
                        frasi++;
                        printf("  blocco di %zu byte\n", nuova);
                    }
                }
            }
        }

        printf("\nVERBALE (%d frasi, %zu caratteri)\n", frasi, strlen(verbale));
        stampa_a_righe(verbale, LARGHEZZA);
        free(verbale);
    }

    return 0;
}

/* Va a capo prima della parola che farebbe superare la larghezza. */
void stampa_a_righe(const char *testo, int larghezza)
{
    int colonna = 0;
    int inizio;
    int lunghezza;
    int i = 0;

    while (testo[i] != '\0') {
        inizio = i;
        while (testo[i] != '\0' && testo[i] != ' ') {
            i++;
        }
        lunghezza = i - inizio;
        if (colonna > 0 && colonna + 1 + lunghezza > larghezza) {
            printf("\n");
            colonna = 0;
        } else if (colonna > 0) {
            printf(" ");
            colonna++;
        }
        printf("%.*s", lunghezza, testo + inizio);
        colonna = colonna + lunghezza;
        while (testo[i] == ' ') {
            i++;
        }
    }
    printf("\n");
}
