/*
 * 080-problema-scontrino-con-sconto.c
 *
 * Cartoleria: totale, sconto e punti fedeltà
 *
 * La cartoleria vicino alla scuola applica uno sconto del 10% sugli
 * acquisti da almeno 50 euro e assegna un punto fedeltà per ogni euro
 * pagato (dopo lo sconto). Il gestionale ha una sola funzione che calcola
 * i tre valori; non tutte le parti del programma però li usano tutti:
 *   - la cassa vuole totale, sconto e punti;
 *   - il preventivo vuole solo il totale;
 *   - la tessera vuole solo i punti.
 *
 * calcola_scontrino ha tre parametri di USCITA FACOLTATIVI: chi non vuole
 * un risultato passa NULL e la funzione non lo scrive. Restituisce il
 * numero di articoli.
 *
 * Importi in centesimi.
 */

#include <stdio.h>

#define SOGLIA_SCONTO 5000
#define PERCENTUALE   10

int calcola_scontrino(const int *prezzi, const int *quantita, int n,
                      int *totale, int *sconto, int *punti);

int main(void)
{
    int prezzi[4] = {1890, 350, 1240, 990};
    int quantita[4] = {1, 6, 2, 1};
    int totale;
    int sconto;
    int punti;
    int articoli;

    printf("=== CASSA ===\n");
    articoli = calcola_scontrino(prezzi, quantita, 4, &totale, &sconto, &punti);
    printf("  %d articoli, totale %.2f, sconto %.2f, da pagare %.2f euro, %d punti\n",
           articoli, totale / 100.0, sconto / 100.0, (totale - sconto) / 100.0, punti);

    printf("\n=== PREVENTIVO (solo il totale) ===\n");
    calcola_scontrino(prezzi, quantita, 2, &totale, NULL, NULL);
    printf("  primi due articoli: %.2f euro\n", totale / 100.0);

    printf("\n=== TESSERA (solo i punti) ===\n");
    calcola_scontrino(prezzi, quantita, 4, NULL, NULL, &punti);
    printf("  punti caricati: %d\n", punti);

    return 0;
}

/* Calcola totale lordo, sconto e punti degli n articoli; scrive solo nei
 * puntatori diversi da NULL. Restituisce il numero di pezzi. */
int calcola_scontrino(const int *prezzi, const int *quantita, int n,
                      int *totale, int *sconto, int *punti)
{
    int i;
    int lordo = 0;
    int pezzi = 0;
    int riduzione = 0;

    for (i = 0; i < n; i++) {
        lordo = lordo + prezzi[i] * quantita[i];
        pezzi = pezzi + quantita[i];
    }
    if (lordo >= SOGLIA_SCONTO) {
        riduzione = lordo * PERCENTUALE / 100;
    }

    if (totale != NULL) {
        *totale = lordo;
    }
    if (sconto != NULL) {
        *sconto = riduzione;
    }
    if (punti != NULL) {
        *punti = (lordo - riduzione) / 100;
    }
    return pezzi;
}
