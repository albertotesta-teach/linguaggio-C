/*
 * 060-problema-parole-per-lunghezza.c
 *
 * Leggibilità di un testo: quante parole per ogni lunghezza
 *
 * Per valutare se un testo è adatto a una classe prima si conta quante
 * parole ci sono di ogni lunghezza: un testo con molte parole lunghe è
 * più difficile. L'insegnante sceglie la lunghezza massima da
 * distinguere (per esempio 12): le parole più lunghe finiscono tutte
 * nell'ultimo contatore.
 *
 *     int *conta = calloc(massimo + 1, sizeof *conta);
 *
 *     conta[1] ... conta[massimo - 1]   parole di quella lunghezza
 *     conta[massimo]                    parole di massimo lettere o più
 *     conta[0]                          non usato
 *
 * Una parola è una sequenza di lettere; numeri e punteggiatura la
 * separano. Il programma legge il testo riga per riga fino a una riga
 * con FINE e stampa la distribuzione con le percentuali, la lunghezza
 * media e la parola più lunga.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LUNG 200
#define MAX_PAROLA 40

int main(void)
{
    int *conta;
    int massimo;
    int parole = 0;
    int lettere_totali = 0;
    int lunghezza;
    int finito = 0;
    int i;
    int k;
    char riga[LUNG];
    char piu_lunga[MAX_PAROLA] = "";
    int inizio;

    printf("Lunghezza massima da distinguere (da 2 a 30): ");
    if (scanf("%d", &massimo) != 1 || massimo < 2 || massimo > 30) {
        printf("Valore non valido.\n");
    } else {
        conta = calloc(massimo + 1, sizeof *conta);
        if (conta == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            scanf("%*[^\n]");
            getchar();
            printf("Testo (FINE per terminare):\n");
            while (!finito) {
                if (fgets(riga, LUNG, stdin) == NULL || strncmp(riga, "FINE", 4) == 0) {
                    finito = 1;
                } else {
                    i = 0;
                    while (riga[i] != '\0') {
                        if (isalpha((unsigned char) riga[i])) {
                            inizio = i;
                            while (isalpha((unsigned char) riga[i])) {
                                i++;
                            }
                            lunghezza = i - inizio;
                            parole++;
                            lettere_totali = lettere_totali + lunghezza;
                            conta[lunghezza < massimo ? lunghezza : massimo]++;
                            if (lunghezza > (int) strlen(piu_lunga) && lunghezza < MAX_PAROLA) {
                                strncpy(piu_lunga, riga + inizio, lunghezza);
                                piu_lunga[lunghezza] = '\0';
                            }
                        } else {
                            i++;
                        }
                    }
                }
            }

            printf("\nParole: %d\n", parole);
            for (k = 1; k <= massimo && parole > 0; k++) {
                if (conta[k] > 0) {
                    printf("  %2d%s lettere: %3d  (%4.1f%%)\n", k, k == massimo ? "+" : " ",
                           conta[k], 100.0 * conta[k] / parole);
                }
            }
            if (parole > 0) {
                printf("Lunghezza media: %.1f lettere\n", (double) lettere_totali / parole);
                printf("Parola piu' lunga: %s\n", piu_lunga);
            }
            free(conta);
        }
    }

    return 0;
}
