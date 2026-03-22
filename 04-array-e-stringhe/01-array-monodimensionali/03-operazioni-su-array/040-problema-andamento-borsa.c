/*
 * 040-problema-andamento-borsa.c
 *
 * Problema reale: analisi dell'andamento di un titolo azionario.
 *
 * Scenario: un investitore vuole analizzare i prezzi giornalieri
 * di un titolo registrati negli ultimi 10 giorni. Il programma
 * calcola la variazione giornaliera rispetto al giorno precedente,
 * identifica il giorno con il guadagno e la perdita massima, e
 * segnala i giorni in cui il prezzo è sceso sotto la media del periodo.
 *
 * Struttura dati chiave:
 *  - un solo array di double: prezzi[i] è il prezzo del giorno i+1.
 *  - Tutte le elaborazioni (variazione, media, estremi) vengono
 *    ricavate scorrendo questo unico array in modi diversi.
 *
 * Concetti applicati:
 *  - differenza tra elementi consecutivi (variazione giornaliera)
 *  - ricerca di massimo e minimo su valori calcolati (non memorizzati)
 *  - confronto con media calcolata in anticipo
 *  - classificazione dei giorni con contatore
 */

#include <stdio.h>

#define GIORNI 10

int main(void) {

    /* Prezzi di chiusura in euro per 10 giorni consecutivi */
    double prezzi[GIORNI] = {
        142.50,   /* giorno  1 */
        145.20,   /* giorno  2 */
        143.80,   /* giorno  3 */
        148.60,   /* giorno  4 */
        151.30,   /* giorno  5 */
        149.70,   /* giorno  6 */
        147.20,   /* giorno  7 */
        152.40,   /* giorno  8 */
        155.10,   /* giorno  9 */
        153.80    /* giorno 10 */
    };

    int i;

    /* ------------------------------------------------------------------ */
    /* Stampa dell'andamento con variazione rispetto al giorno precedente.
     * La variazione non esiste per il giorno 1 (nessun precedente). */
    printf("=== ANDAMENTO TITOLO ===\n");
    printf("  Giorno | Prezzo   | Variazione\n");
    printf("  -------|----------|------------\n");
    printf("     1   | %7.2f€ | --\n", prezzi[0]);

    for (i = 1; i < GIORNI; i++) {
        double variazione = prezzi[i] - prezzi[i - 1];
        double perc       = variazione / prezzi[i - 1] * 100.0;

        if (variazione > 0.0) {
            printf("     %2d  | %7.2f€ | +%.2f€ (+%.2f%%)\n",
                   i + 1, prezzi[i], variazione, perc);
        } else if (variazione < 0.0) {
            printf("     %2d  | %7.2f€ | %.2f€ (%.2f%%)\n",
                   i + 1, prezzi[i], variazione, perc);
        } else {
            printf("     %2d  | %7.2f€ | invariato\n", i + 1, prezzi[i]);
        }
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Calcolo della media del periodo */
    double somma = 0.0;
    for (i = 0; i < GIORNI; i++) {
        somma = somma + prezzi[i];
    }
    double media = somma / GIORNI;
    printf("Prezzo medio del periodo: %.2f€\n\n", media);

    /* ------------------------------------------------------------------ */
    /* Giorno con il guadagno massimo e la perdita massima.
     * Si confrontano le variazioni giornaliere senza memorizzarle in array:
     * si calcola la variazione al volo e si aggiorna il massimo/minimo. */
    double guadagno_max = prezzi[1] - prezzi[0];   /* prima variazione disponibile */
    double perdita_max  = prezzi[1] - prezzi[0];
    int    giorno_max   = 2;
    int    giorno_min   = 2;

    for (i = 2; i < GIORNI; i++) {
        double var = prezzi[i] - prezzi[i - 1];

        if (var > guadagno_max) {
            guadagno_max = var;
            giorno_max   = i + 1;
        }
        if (var < perdita_max) {
            perdita_max = var;
            giorno_min  = i + 1;
        }
    }

    printf("Giorno con guadagno massimo: giorno %d (+%.2f€)\n",
           giorno_max, guadagno_max);
    printf("Giorno con perdita massima : giorno %d (%.2f€)\n\n",
           giorno_min, perdita_max);

    /* ------------------------------------------------------------------ */
    /* Giorni sotto la media del periodo */
    int sotto_media = 0;
    printf("Giorni con prezzo sotto la media (%.2f€):\n", media);

    for (i = 0; i < GIORNI; i++) {
        if (prezzi[i] < media) {
            printf("  Giorno %2d: %.2f€ (-%0.2f€ dalla media)\n",
                   i + 1, prezzi[i], media - prezzi[i]);
            sotto_media++;
        }
    }

    printf("Totale giorni sotto media: %d su %d\n", sotto_media, GIORNI);

    return 0;
}
