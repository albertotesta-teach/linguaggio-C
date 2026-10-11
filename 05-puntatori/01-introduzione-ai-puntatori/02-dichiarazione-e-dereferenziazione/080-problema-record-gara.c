/*
 * 080-problema-record-gara.c
 *
 * Il miglior tempo di una gara di nuoto
 *
 * Nella finale dei 50 metri stile libero dei giochi studenteschi ci sono
 * CORSIE corsie. I tempi (in centesimi di secondo) sono in un array; il
 * valore 0 indica un atleta squalificato o assente.
 *
 * Il programma usa un puntatore, migliore, che punta all'elemento
 * dell'array con il tempo migliore:
 *   - all'inizio vale NULL (nessun tempo valido trovato);
 *   - ogni tempo valido viene confrontato con *migliore;
 *   - alla fine, se migliore è ancora NULL, nessun atleta ha concluso.
 *
 * La corsia del vincitore si ricava cercando k tale che &tempi[k] == migliore.
 * Il programma verifica anche se il record dei giochi è stato battuto: in
 * quel caso il nuovo tempo viene scritto nella variabile record tramite un
 * secondo puntatore.
 *
 * Il programma esamina due finali: nella seconda tutti gli atleti sono
 * stati squalificati.
 */

#include <stdio.h>

#define CORSIE 6

void esamina_finale(const char titolo[], int tempi[], int *record);
void stampa_tempo(int centesimi);

int main(void)
{
    int finale_a[CORSIE] = {3125, 2987, 0, 3010, 2955, 3102};
    int finale_b[CORSIE] = {0, 0, 0, 0, 0, 0};
    int record = 2970;

    printf("Record dei giochi: ");
    stampa_tempo(record);
    printf("\n\n");

    esamina_finale("Finale maschile", finale_a, &record);
    esamina_finale("Finale di recupero", finale_b, &record);

    printf("Record aggiornato: ");
    stampa_tempo(record);
    printf("\n");

    return 0;
}

/* Trova il tempo migliore con un puntatore e aggiorna *record se battuto. */
void esamina_finale(const char titolo[], int tempi[], int *record)
{
    int *migliore = NULL;
    int k;
    int corsia = -1;

    printf("=== %s ===\n", titolo);
    for (k = 0; k < CORSIE; k++) {
        printf("  corsia %d: ", k + 1);
        if (tempi[k] == 0) {
            printf("squalificato\n");
        } else {
            stampa_tempo(tempi[k]);
            printf("\n");
            if (migliore == NULL || tempi[k] < *migliore) {
                migliore = &tempi[k];
            }
        }
    }

    if (migliore == NULL) {
        printf("  Nessun atleta ha concluso la gara.\n\n");
    } else {
        for (k = 0; k < CORSIE; k++) {
            if (&tempi[k] == migliore) {
                corsia = k + 1;
            }
        }
        printf("  Vince la corsia %d con ", corsia);
        stampa_tempo(*migliore);
        if (*migliore < *record) {
            *record = *migliore;
            printf(": NUOVO RECORD!");
        }
        printf("\n\n");
    }
}

void stampa_tempo(int centesimi)
{
    printf("%d\"%02d", centesimi / 100, centesimi % 100);
}
