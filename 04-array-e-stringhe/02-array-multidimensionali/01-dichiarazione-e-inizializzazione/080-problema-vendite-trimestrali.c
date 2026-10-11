/*
 * 080-problema-vendite-trimestrali.c
 *
 * Vendite del trimestre di un negozio di elettronica
 *
 * Il responsabile commerciale ha i pezzi venduti di 5 prodotti nei tre
 * mesi del trimestre (gennaio, febbraio, marzo) e il prezzo di ciascun
 * prodotto. Il programma:
 *   - stampa la tabella delle vendite con il totale per prodotto;
 *   - calcola il totale per mese (somma delle colonne);
 *   - calcola il fatturato di ogni prodotto e quello complessivo;
 *   - indica il prodotto con il fatturato più alto;
 *   - segnala i prodotti con vendite in crescita ogni mese.
 *
 * Struttura dati:
 *   int vendite[PRODOTTI][MESI]   pezzi venduti
 *   int codici[PRODOTTI]          codice di ogni prodotto (parallelo alle righe)
 *   double prezzi[PRODOTTI]       prezzo unitario (parallelo alle righe)
 */

#include <stdio.h>

#define PRODOTTI 5
#define MESI     3

int main(void)
{
    int vendite[PRODOTTI][MESI] = {
        {42, 38, 51},
        {15, 18, 22},
        {60, 55, 48},
        { 8, 12, 15},
        {25, 25, 30}
    };
    int codici[PRODOTTI] = {1101, 1102, 2201, 3301, 3302};
    double prezzi[PRODOTTI] = {19.90, 149.00, 9.50, 599.00, 79.90};

    int p;
    int m;
    int pezzi_prodotto;
    int pezzi_mese;
    double fatturato;
    double fatturato_totale = 0.0;
    double fatturato_max = 0.0;
    int p_max = 0;
    int in_crescita;

    /* ── 1. Tabella vendite, totali e fatturato per prodotto ──────── */
    printf("=== VENDITE PRIMO TRIMESTRE ===\n\n");
    printf("  Codice |  Gen |  Feb |  Mar | Pezzi |   Prezzo | Fatturato\n");
    printf("  -------|------|------|------|-------|----------|----------\n");

    for (p = 0; p < PRODOTTI; p++) {
        pezzi_prodotto = 0;
        printf("  %6d |", codici[p]);
        for (m = 0; m < MESI; m++) {
            printf(" %4d |", vendite[p][m]);
            pezzi_prodotto = pezzi_prodotto + vendite[p][m];
        }

        fatturato = pezzi_prodotto * prezzi[p];
        fatturato_totale = fatturato_totale + fatturato;
        printf(" %5d | %8.2f | %9.2f\n", pezzi_prodotto, prezzi[p], fatturato);

        if (p == 0 || fatturato > fatturato_max) {
            fatturato_max = fatturato;
            p_max = p;
        }
    }

    /* ── 2. Totale per mese (somma per colonne) ───────────────────── */
    printf("  -------|------|------|------|\n");
    printf("  Totale |");
    for (m = 0; m < MESI; m++) {
        pezzi_mese = 0;
        for (p = 0; p < PRODOTTI; p++) {
            pezzi_mese = pezzi_mese + vendite[p][m];
        }
        printf(" %4d |", pezzi_mese);
    }
    printf("\n\n");

    printf("Fatturato del trimestre: %.2f euro\n", fatturato_totale);
    printf("Prodotto con il fatturato piu' alto: %d (%.2f euro)\n\n",
           codici[p_max], fatturato_max);

    /* ── 3. Prodotti in crescita ──────────────────────────────────────
     * Un prodotto è in crescita se ogni mese vende più del mese prima.
     * Si parte dall'ipotesi "in crescita" e la si smentisce al primo
     * mese che non supera il precedente (il ciclo si ferma grazie al
     * flag nella condizione).                                          */
    printf("--- Prodotti con vendite in crescita ogni mese ---\n");
    for (p = 0; p < PRODOTTI; p++) {
        in_crescita = 1;
        for (m = 1; m < MESI && in_crescita; m++) {
            if (vendite[p][m] <= vendite[p][m - 1]) {
                in_crescita = 0;
            }
        }
        if (in_crescita) {
            printf("  %d: %d -> %d -> %d\n", codici[p],
                   vendite[p][0], vendite[p][1], vendite[p][2]);
        }
    }

    return 0;
}
