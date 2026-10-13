/*
 * 060-problema-misure-ridotte.c
 *
 * La stazione meteo della scuola: togliere le letture errate del
 * pluviometro
 *
 * Il pluviometro registra ogni giorno i millimetri di pioggia. Ogni
 * tanto invia valori impossibili: negativi, oppure sopra 300 mm in un
 * giorno. Il programma legge n letture in un blocco, toglie quelle
 * errate SENZA un secondo array e poi riduce il blocco:
 *
 *   1. filtro sul posto: due indici, i legge tutte le letture, j scrive
 *      solo quelle valide; j non supera mai i, quindi nessun valore
 *      viene sovrascritto prima di essere letto;
 *
 *         for (i = 0; i < n; i++)
 *             if (valida(pioggia[i])) { pioggia[j] = pioggia[i]; j++; }
 *
 *   2. riduzione: tmp = realloc(pioggia, j * sizeof *pioggia).
 *
 * Se non resta nessuna lettura valida il blocco si libera con free.
 * Poi il programma stampa le letture valide, il totale, la media e il
 * giorno più piovoso (numerato come nelle letture originali).
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_GIORNI 366
#define MASSIMO_MM 300.0

int main(void)
{
    double *pioggia;
    double *tmp;
    int *giorno;
    int *tmp_giorno;
    int n;
    int letti = 0;
    int j = 0;
    int i;
    int piovoso = 0;
    double totale = 0;

    printf("Numero di giorni (da 1 a %d): ", MAX_GIORNI);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_GIORNI) {
        printf("Numero non valido.\n");
    } else {
        pioggia = malloc(n * sizeof *pioggia);
        giorno = malloc(n * sizeof *giorno);
        if (pioggia == NULL || giorno == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            printf("Millimetri di pioggia: ");
            while (letti < n && scanf("%lf", &pioggia[letti]) == 1) {
                letti++;
            }
            for (i = 0; i < letti; i++) {
                if (pioggia[i] >= 0 && pioggia[i] <= MASSIMO_MM) {
                    pioggia[j] = pioggia[i];
                    giorno[j] = i + 1;
                    j++;
                } else {
                    printf("  giorno %d: %.1f scartato\n", i + 1, pioggia[i]);
                }
            }
            printf("Letture: %d, valide: %d\n", letti, j);

            if (j > 0) {
                tmp = realloc(pioggia, j * sizeof *pioggia);
                tmp_giorno = realloc(giorno, j * sizeof *giorno);
                if (tmp != NULL) {
                    pioggia = tmp;
                }
                if (tmp_giorno != NULL) {
                    giorno = tmp_giorno;
                }
                printf("Blocchi ridotti da %d a %d elementi\n", n, j);
                for (i = 0; i < j; i++) {
                    totale = totale + pioggia[i];
                    if (pioggia[i] > pioggia[piovoso]) {
                        piovoso = i;
                    }
                }
                printf("Totale %.1f mm, media %.1f mm al giorno\n", totale, totale / j);
                printf("Giorno piu' piovoso: %d con %.1f mm\n", giorno[piovoso],
                       pioggia[piovoso]);
            }
        }
        free(pioggia);
        free(giorno);
    }

    return 0;
}
