/*
 * 070-problema-serie-di-vittorie.c
 *
 * Campionato di pallavolo: la serie di vittorie più lunga
 *
 * I risultati di una squadra nelle giornate di campionato sono memorizzati
 * in un array di caratteri: 'V' vittoria, 'P' pareggio, 'S' sconfitta.
 * L'allenatore vuole conoscere i punti in classifica (3 per la vittoria,
 * 1 per il pareggio) e la serie più lunga di vittorie consecutive, con la
 * prima e l'ultima giornata.
 *
 * Mentre un puntatore p scorre le giornate, un secondo puntatore,
 * inizio_serie, ricorda dove è cominciata la serie in corso (NULL se non ce
 * n'è una). Quando la serie si interrompe la sua lunghezza è
 * p - inizio_serie; la migliore si conserva in migliore e lunghezza_max.
 * Una serie ancora aperta all'ultima giornata si chiude con fine.
 */

#include <stdio.h>

#define GIORNATE 15

int main(void)
{
    char risultati[GIORNATE] = {'V', 'V', 'P', 'V', 'V', 'V', 'S', 'V',
                                'V', 'V', 'V', 'P', 'S', 'V', 'V'};
    const char *inizio = &risultati[0];
    const char *fine = inizio + GIORNATE;
    const char *p;
    const char *inizio_serie = NULL;
    const char *migliore = NULL;
    int lunghezza_max = 0;
    int punti = 0;

    printf("=== RISULTATI ===\n  ");
    for (p = inizio; p < fine; p++) {
        printf("%c ", *p);

        if (*p == 'V') {
            punti = punti + 3;
            if (inizio_serie == NULL) {
                inizio_serie = p;
            }
        } else {
            if (*p == 'P') {
                punti = punti + 1;
            }
            if (inizio_serie != NULL) {
                if (p - inizio_serie > lunghezza_max) {
                    lunghezza_max = p - inizio_serie;
                    migliore = inizio_serie;
                }
                inizio_serie = NULL;
            }
        }
    }
    printf("\n");

    /* serie ancora aperta dopo l'ultima giornata */
    if (inizio_serie != NULL && fine - inizio_serie > lunghezza_max) {
        lunghezza_max = fine - inizio_serie;
        migliore = inizio_serie;
    }

    printf("\nPunti in classifica: %d in %d giornate\n", punti, GIORNATE);
    if (migliore == NULL) {
        printf("Nessuna vittoria.\n");
    } else {
        printf("Serie piu' lunga: %d vittorie consecutive, dalla giornata %d alla %d\n",
               lunghezza_max, (int) (migliore - inizio) + 1,
               (int) (migliore - inizio) + lunghezza_max);
    }

    return 0;
}
