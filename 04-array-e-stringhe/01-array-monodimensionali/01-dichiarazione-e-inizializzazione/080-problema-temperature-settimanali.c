/*
 * 080-problema-temperature-settimanali.c
 *
 * Problema reale: analisi delle temperature rilevate in una settimana.
 *
 * Scenario: una centralina meteo registra la temperatura massima
 * giornaliera per 7 giorni. Il programma memorizza i dati in un array,
 * stampa il riepilogo settimanale e calcola la temperatura media,
 * i giorni sopra media e la variazione rispetto al giorno precedente.
 *
 * Concetti applicati:
 *  - array di double per dati in virgola mobile
 *  - confronto con valore calcolato (media)
 *  - differenza tra elementi consecutivi
 *  - uso di costanti simboliche per leggibilità
 */

#include <stdio.h>

#define GIORNI_SETTIMANA 7

int main(void) {

    /* Nomi dei giorni e temperature massime rilevate (in gradi Celsius) */
    char giorni[GIORNI_SETTIMANA][12] = {
        "Lunedi'", "Martedi'", "Mercoledi'", "Giovedi'",
        "Venerdi'", "Sabato", "Domenica"
    };
    double temperature[GIORNI_SETTIMANA] = {18.5, 21.0, 23.4, 22.1, 19.8, 17.5, 16.2};

    int i;
    double somma;
    double media;

    /* ------------------------------------------------------------------ */
    /* Stampa del riepilogo settimanale */
    printf("=================================\n");
    printf("  TEMPERATURE SETTIMANA CORRENTE \n");
    printf("=================================\n");

    for (i = 0; i < GIORNI_SETTIMANA; i++) {
        printf("  %-12s: %5.1f °C\n", giorni[i], temperature[i]);
    }
    printf("=================================\n\n");

    /* ------------------------------------------------------------------ */
    /* Calcolo della temperatura media settimanale */
    somma = 0.0;
    for (i = 0; i < GIORNI_SETTIMANA; i++) {
        somma = somma + temperature[i];
    }
    media = somma / GIORNI_SETTIMANA;

    printf("Temperatura media : %.1f °C\n\n", media);

    /* ------------------------------------------------------------------ */
    /* Giorni con temperatura sopra la media */
    printf("Giorni sopra la media (> %.1f °C):\n", media);
    int sopra_media = 0;

    for (i = 0; i < GIORNI_SETTIMANA; i++) {
        if (temperature[i] > media) {
            printf("  %s: %.1f °C (+%.1f rispetto alla media)\n",
                   giorni[i], temperature[i], temperature[i] - media);
            sopra_media = sopra_media + 1;
        }
    }
    printf("Totale: %d giorni su %d\n\n", sopra_media, GIORNI_SETTIMANA);

    /* ------------------------------------------------------------------ */
    /* Variazione rispetto al giorno precedente */
    printf("Variazione giornaliera:\n");
    for (i = 1; i < GIORNI_SETTIMANA; i++) {
        double variazione = temperature[i] - temperature[i - 1];

        if (variazione > 0.0) {
            printf("  giorno %d -> giorno %d: +%.1f °C (in salita)\n",
                   i, i + 1, variazione);
        } else if (variazione < 0.0) {
            printf("  giorno %d -> giorno %d: %.1f °C (in discesa)\n",
                   i, i + 1, variazione);
        } else {
            printf("  giorno %d -> giorno %d: stabile\n", i, i + 1);
        }
    }

    return 0;
}
