/*
 * 040-problema-rilevazioni-pluviometriche.c
 *
 * Problema reale: analisi delle precipitazioni mensili di una città.
 *
 * Scenario: un ufficio meteorologico ha registrato le precipitazioni
 * mensili (in mm) di una città per un intero anno. Il programma
 * memorizza i 12 valori in un unico array, li scorre per identificare
 * il mese più piovoso e quello più secco, calcola la precipitazione
 * media annua e conta i mesi siccitosi (sotto soglia).
 *
 * Struttura dati chiave:
 *  - un solo array di 12 double: un elemento per mese.
 *  - L'indice i corrisponde al mese i+1 (gennaio = 0, dicembre = 11).
 *  - Non servono array paralleli: i nomi dei mesi vengono ricavati
 *    dall'indice con una funzione di mappatura indice -> stringa.
 *
 * Concetti applicati:
 *  - array di double con un elemento per unità di tempo
 *  - scorrimento per ricerca di minimo e massimo con indice
 *  - conteggio con confronto a soglia
 *  - calcolo di media su array singolo
 */

#include <stdio.h>

#define NUM_MESI      12
#define SOGLIA_SICCITA 30.0   /* mm: sotto questa soglia il mese è siccitoso */

int main(void) {

    /* Precipitazioni mensili in mm.
     * Indice 0 = gennaio, indice 11 = dicembre. */
    double pioggia[NUM_MESI] = {
        42.0,   /* gennaio  */
        35.5,   /* febbraio */
        28.0,   /* marzo    */
        55.0,   /* aprile   */
        68.5,   /* maggio   */
        18.0,   /* giugno   */
        12.5,   /* luglio   */
        22.0,   /* agosto   */
        48.0,   /* settembre*/
        75.0,   /* ottobre  */
        60.5,   /* novembre */
        38.0    /* dicembre */
    };

    /* Nomi dei mesi: array di stringhe parallelo usato solo per la stampa.
     * Alternativa senza array parallelo: si potrebbe usare una catena
     * if/else if per mappare l'indice al nome, ma l'array è più compatto. */
    char mesi[NUM_MESI][12] = {
        "Gennaio", "Febbraio", "Marzo", "Aprile",
        "Maggio", "Giugno", "Luglio", "Agosto",
        "Settembre", "Ottobre", "Novembre", "Dicembre"
    };

    int i;
    double somma;
    double media;
    int mese_max;
    int mese_min;
    int siccitosi;

    /* ------------------------------------------------------------------ */
    /* Stampa del riepilogo annuale */
    printf("=========================================\n");
    printf("   PRECIPITAZIONI ANNUALI - RIEPILOGO    \n");
    printf("=========================================\n");
    for (i = 0; i < NUM_MESI; i++) {
        int j;
        /* Barra proporzionale: un simbolo ogni 5 mm */
        printf("  %-10s | %5.1f mm | ", mesi[i], pioggia[i]);
        for (j = 0; j < (int)(pioggia[i] / 5.0); j++) {
            printf("|");
        }
        printf("\n");
    }
    printf("=========================================\n\n");

    /* ------------------------------------------------------------------ */
    /* Calcolo della media annua */
    somma = 0.0;
    for (i = 0; i < NUM_MESI; i++) {
        somma = somma + pioggia[i];
    }
    media = somma / NUM_MESI;

    printf("Precipitazione totale annua : %.1f mm\n", somma);
    printf("Precipitazione media mensile: %.1f mm\n\n", media);

    /* ------------------------------------------------------------------ */
    /* Ricerca del mese più piovoso e di quello più secco.
     * Si inizializza con il primo elemento e si scorre dal secondo. */
    mese_max = 0;
    mese_min = 0;

    for (i = 1; i < NUM_MESI; i++) {
        if (pioggia[i] > pioggia[mese_max]) {
            mese_max = i;
        }
        if (pioggia[i] < pioggia[mese_min]) {
            mese_min = i;
        }
    }

    printf("Mese piu' piovoso : %s (%.1f mm)\n", mesi[mese_max], pioggia[mese_max]);
    printf("Mese piu' secco   : %s (%.1f mm)\n\n", mesi[mese_min], pioggia[mese_min]);

    /* ------------------------------------------------------------------ */
    /* Conteggio mesi siccitosi (precipitazione sotto soglia) */
    siccitosi = 0;
    printf("Mesi siccitosi (< %.0f mm):\n", SOGLIA_SICCITA);

    for (i = 0; i < NUM_MESI; i++) {
        if (pioggia[i] < SOGLIA_SICCITA) {
            printf("  %s: %.1f mm\n", mesi[i], pioggia[i]);
            siccitosi++;
        }
    }

    if (siccitosi == 0) {
        printf("  Nessun mese siccitoso.\n");
    }
    printf("\nTotale mesi siccitosi: %d su %d\n", siccitosi, NUM_MESI);

    return 0;
}
