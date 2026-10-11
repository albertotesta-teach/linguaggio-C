/*
 * 050-problema-ora-di-punta.c
 *
 * Consumi elettrici della scuola: l'ora di punta
 *
 * Il contatore della scuola registra i kWh consumati in ognuna delle 24 ore
 * di una giornata. Il responsabile tecnico vuole sapere:
 *   - in quale ora si raggiunge il consumo massimo (ora di punta);
 *   - la fascia di alto consumo: dalla prima all'ultima ora in cui il
 *     consumo supera l'80% del massimo;
 *   - il consumo totale della giornata.
 *
 * Il massimo si cerca con un puntatore, picco, che si sposta sull'elemento
 * maggiore; l'ora è picco - &consumi[0]. La fascia si individua con due
 * puntatori, prima e ultima, e dura ultima - prima + 1 ore.
 */

#include <stdio.h>

#define ORE        24
#define PERCENTUALE 80
#define KWH_PER_SEGNO 5

int main(void)
{
    int consumi[ORE] = {8, 8, 7, 7, 7, 8, 12, 25, 48, 62, 66, 70,
                        58, 52, 64, 61, 45, 30, 18, 14, 12, 10, 9, 8};
    const int *inizio = &consumi[0];
    const int *fine = inizio + ORE;
    const int *p;
    const int *picco = inizio;
    const int *prima = NULL;
    const int *ultima = NULL;
    int soglia;
    int totale = 0;
    int k;

    /* 1. picco e totale */
    for (p = inizio; p < fine; p++) {
        if (*p > *picco) {
            picco = p;
        }
        totale = totale + *p;
    }
    soglia = *picco * PERCENTUALE / 100;

    /* 2. prima e ultima ora oltre la soglia */
    for (p = inizio; p < fine; p++) {
        if (*p >= soglia) {
            if (prima == NULL) {
                prima = p;
            }
            ultima = p;
        }
    }

    printf("=== CONSUMI ORARI (un # ogni %d kWh) ===\n", KWH_PER_SEGNO);
    for (p = inizio; p < fine; p++) {
        printf("  %02d:00 %3d ", (int) (p - inizio), *p);
        for (k = 0; k < *p / KWH_PER_SEGNO; k++) {
            printf("#");
        }
        if (p == picco) {
            printf("  <- ora di punta");
        }
        printf("\n");
    }

    printf("\nConsumo totale: %d kWh\n", totale);
    printf("Ora di punta: %02d:00-%02d:00 con %d kWh\n",
           (int) (picco - inizio), (int) (picco - inizio) + 1, *picco);
    printf("Alto consumo (almeno %d kWh, %d%% del massimo): dalle %02d:00 alle %02d:00, %d ore\n",
           soglia, PERCENTUALE, (int) (prima - inizio), (int) (ultima - inizio) + 1,
           (int) (ultima - prima) + 1);

    return 0;
}
