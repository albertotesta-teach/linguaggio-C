/*
 * 060-problema-temperature-settimana.c
 *
 * Temperature di una settimana rilevate in quattro fasce orarie
 *
 * Una stazione meteo registra la temperatura quattro volte al giorno
 * (notte, mattina, pomeriggio, sera) per sette giorni. Il programma:
 *   - stampa la tabella delle rilevazioni con la media di ogni giorno;
 *   - trova la rilevazione più alta e quella più bassa della settimana,
 *     indicando giorno e fascia;
 *   - calcola la media di ogni fascia oraria su tutta la settimana.
 *
 * Struttura dati:
 *   double temp[GIORNI][FASCE]   la matrice delle rilevazioni
 *   char giorni[GIORNI][LUNG]    i nomi dei giorni: array parallelo alle
 *                                RIGHE di temp (giorni[i] descrive la riga i)
 *   char fasce[FASCE][LUNG]      i nomi delle fasce: array parallelo alle
 *                                COLONNE di temp (fasce[j] descrive la colonna j)
 */

#include <stdio.h>

#define GIORNI 7
#define FASCE  4
#define LUNG   12

int main(void)
{
    double temp[GIORNI][FASCE] = {
        { 8.5, 13.0, 17.5, 12.0},
        { 9.0, 14.5, 18.0, 13.5},
        {10.5, 15.0, 19.5, 14.0},
        { 7.0, 11.5, 15.0, 10.5},
        { 6.5, 10.0, 13.5,  9.0},
        { 8.0, 14.0, 20.5, 15.5},
        {11.0, 16.5, 21.0, 16.0}
    };
    char giorni[GIORNI][LUNG] = {
        "Lunedi'", "Martedi'", "Mercoledi'", "Giovedi'",
        "Venerdi'", "Sabato", "Domenica"
    };
    char fasce[FASCE][LUNG] = {
        "Notte", "Mattina", "Pomeriggio", "Sera"
    };

    int g;
    int f;
    double somma;
    int g_max = 0;
    int f_max = 0;
    int g_min = 0;
    int f_min = 0;

    /* ── 1. Tabella con media giornaliera ─────────────────────────── */
    printf("=== TEMPERATURE DELLA SETTIMANA (gradi C) ===\n\n");
    printf("  %-11s", "Giorno");
    for (f = 0; f < FASCE; f++) {
        printf("%11s", fasce[f]);
    }
    printf("%9s\n", "Media");

    for (g = 0; g < GIORNI; g++) {
        somma = 0.0;
        printf("  %-11s", giorni[g]);
        for (f = 0; f < FASCE; f++) {
            printf("%11.1f", temp[g][f]);
            somma = somma + temp[g][f];
        }
        printf("%9.1f\n", somma / FASCE);
    }

    /* ── 2. Massimo e minimo della settimana con la loro posizione ────
     * Si memorizzano gli INDICI (riga e colonna) dell'estremo, non il
     * valore: dagli indici si ricavano valore, giorno e fascia.         */
    for (g = 0; g < GIORNI; g++) {
        for (f = 0; f < FASCE; f++) {
            if (temp[g][f] > temp[g_max][f_max]) {
                g_max = g;
                f_max = f;
            }
            if (temp[g][f] < temp[g_min][f_min]) {
                g_min = g;
                f_min = f;
            }
        }
    }

    printf("\nTemperatura massima: %.1f (%s, %s)\n",
           temp[g_max][f_max], giorni[g_max], fasce[f_max]);
    printf("Temperatura minima : %.1f (%s, %s)\n",
           temp[g_min][f_min], giorni[g_min], fasce[f_min]);

    /* ── 3. Media per fascia oraria ───────────────────────────────────
     * Ora il ciclo ESTERNO scorre le colonne e quello interno le righe:
     * si somma una colonna alla volta.                                 */
    printf("\n--- Media della settimana per fascia ---\n");
    for (f = 0; f < FASCE; f++) {
        somma = 0.0;
        for (g = 0; g < GIORNI; g++) {
            somma = somma + temp[g][f];
        }
        printf("  %-11s: %5.1f\n", fasce[f], somma / GIORNI);
    }

    return 0;
}
