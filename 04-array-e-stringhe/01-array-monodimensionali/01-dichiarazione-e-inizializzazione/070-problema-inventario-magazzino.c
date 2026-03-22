/*
 * 070-problema-inventario-magazzino.c
 *
 * Problema reale: inventario di un piccolo magazzino.
 *
 * Scenario: un negozio gestisce un magazzino con 6 prodotti. Il programma
 * memorizza le quantità disponibili, stampa l'inventario completo,
 * identifica i prodotti in esaurimento (quantità <= soglia) e calcola
 * la giacenza totale e il valore complessivo del magazzino.
 *
 * Concetti applicati:
 *  - array paralleli (codici, nomi, quantità, prezzi)
 *  - scorrimento e confronto con soglia
 *  - calcolo di totali su array di valori diversi
 */

#include <stdio.h>

#define NUM_PRODOTTI  6
#define SOGLIA_MINIMA 10

int main(void) {

    /* Dati del magazzino: array paralleli indicizzati da 0 a NUM_PRODOTTI-1.
     * Ogni indice i rappresenta lo stesso prodotto in tutti gli array. */
    char codici[NUM_PRODOTTI][8]  = {"P001", "P002", "P003", "P004", "P005", "P006"};
    char nomi[NUM_PRODOTTI][25]   = {
        "Penna blu",
        "Quaderno A4",
        "Matita HB",
        "Gomma bianca",
        "Righello 30cm",
        "Temperamatite"
    };
    int  quantita[NUM_PRODOTTI]   = {45, 8, 120, 6, 30, 15};
    double prezzi[NUM_PRODOTTI]   = {0.80, 1.50, 0.40, 0.60, 1.20, 0.90};

    int i;

    /* ------------------------------------------------------------------ */
    /* Stampa dell'inventario completo */
    printf("==========================================================\n");
    printf("                  INVENTARIO MAGAZZINO                   \n");
    printf("==========================================================\n");
    printf("  Cod.  | Prodotto               | Qtà  | Prezzo | Valore\n");
    printf("--------|------------------------|------|--------|--------\n");

    for (i = 0; i < NUM_PRODOTTI; i++) {
        double valore_riga = quantita[i] * prezzi[i];
        printf("  %s | %-22s | %4d | %5.2f€ | %6.2f€\n",
               codici[i], nomi[i], quantita[i], prezzi[i], valore_riga);
    }
    printf("==========================================================\n\n");

    /* ------------------------------------------------------------------ */
    /* Prodotti in esaurimento: quantità sotto la soglia minima */
    printf("Prodotti in esaurimento (quantita <= %d):\n", SOGLIA_MINIMA);
    int trovati = 0;

    for (i = 0; i < NUM_PRODOTTI; i++) {
        if (quantita[i] <= SOGLIA_MINIMA) {
            printf("  [!] %s - %s: solo %d pezzi\n",
                   codici[i], nomi[i], quantita[i]);
            trovati = trovati + 1;
        }
    }

    if (trovati == 0) {
        printf("  Nessun prodotto in esaurimento.\n");
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Calcolo della giacenza totale (somma di tutti i pezzi) */
    int giacenza_totale = 0;
    double valore_totale = 0.0;

    for (i = 0; i < NUM_PRODOTTI; i++) {
        giacenza_totale = giacenza_totale + quantita[i];
        valore_totale = valore_totale + quantita[i] * prezzi[i];
    }

    printf("Giacenza totale    : %d pezzi\n", giacenza_totale);
    printf("Valore magazzino   : %.2f euro\n", valore_totale);

    return 0;
}
