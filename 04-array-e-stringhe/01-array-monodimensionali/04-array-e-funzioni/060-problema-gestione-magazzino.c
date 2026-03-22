/*
 * 060-problema-gestione-magazzino.c
 *
 * Problema reale: gestione di un magazzino con funzioni dedicate.
 *
 * Scenario: un magazzino tiene traccia di 6 prodotti, ciascuno con
 * un codice numerico e una quantità disponibile. Il programma organizza
 * le operazioni in funzioni distinte: ricerca per codice, aggiornamento
 * della quantità, stampa del prospetto e calcolo della giacenza totale.
 *
 * Concetti applicati:
 *  - funzione di ricerca che restituisce un indice (-1 se non trovato)
 *  - funzione che modifica un elemento dell'array tramite indice
 *  - separazione netta tra logica (funzioni) e presentazione (main)
 *  - array paralleli passati insieme alle funzioni
 */

#include <stdio.h>

#define PRODOTTI 6

/* Cerca il prodotto con il codice dato; restituisce l'indice o -1 */
int trova_prodotto(const int codici[], int n, int codice_cercato) {
    int i;
    int trovato = 0;
    int risultato = -1;
    for (i = 0; i < n && !trovato; i++) {
        if (codici[i] == codice_cercato) {
            trovato = 1;
            risultato = i;
        }
    }
    return risultato;
}

/* Aggiorna la quantità del prodotto all'indice dato.
 * Restituisce 1 se l'operazione è andata a buon fine, 0 altrimenti.
 * Non porta mai la quantità sotto zero. */
int aggiorna_quantita(int quantita[], int n, int indice, int delta) {
    int esito = 0;
    if (indice >= 0 && indice < n) {
        int nuova = quantita[indice] + delta;
        if (nuova >= 0) {
            quantita[indice] = nuova;
            esito = 1;
        }
        /* Se nuova < 0: operazione rifiutata, quantita invariata */
    }
    return esito;
}

/* Restituisce la giacenza totale (somma di tutte le quantità) */
int giacenza_totale(const int quantita[], int n) {
    int i;
    int totale = 0;
    for (i = 0; i < n; i++) {
        totale = totale + quantita[i];
    }
    return totale;
}

/* Stampa il prospetto del magazzino */
void stampa_magazzino(const int codici[], const char nomi[][20],
                      const int quantita[], int n) {
    int i;
    printf("  Cod.  | Prodotto           | Qty\n");
    printf("  ------|--------------------|---------\n");
    for (i = 0; i < n; i++) {
        printf("  %4d  | %-18s | %5d\n",
               codici[i], nomi[i], quantita[i]);
    }
    printf("  Giacenza totale: %d pezzi\n", giacenza_totale(quantita, n));
}

int main(void) {

    int  codici[PRODOTTI]      = {1001, 1002, 1003, 1004, 1005, 1006};
    char nomi[PRODOTTI][20]    = {
        "Vite M4x10",
        "Dado M4",
        "Rondella M4",
        "Vite M6x20",
        "Dado M6",
        "Rondella M6"
    };
    int  quantita[PRODOTTI]    = {500, 480, 600, 320, 310, 400};

    int indice;
    int esito;

    printf("=== GESTIONE MAGAZZINO ===\n\n");

    printf("--- Stato iniziale ---\n");
    stampa_magazzino(codici, nomi, quantita, PRODOTTI);
    printf("\n");

    /* ---------------------------------------------------------------- */
    /* Operazione 1: carico di 200 unità del prodotto 1003 */
    printf("Operazione: carico +200 di codice 1003\n");
    indice = trova_prodotto(codici, PRODOTTI, 1003);
    if (indice != -1) {
        esito = aggiorna_quantita(quantita, PRODOTTI, indice, +200);
        if (esito) {
            printf("  OK: %s -> nuova quantita': %d\n\n",
                   nomi[indice], quantita[indice]);
        }
    } else {
        printf("  ERRORE: prodotto non trovato\n\n");
    }

    /* ---------------------------------------------------------------- */
    /* Operazione 2: scarico di 150 unità del prodotto 1005 */
    printf("Operazione: scarico -150 di codice 1005\n");
    indice = trova_prodotto(codici, PRODOTTI, 1005);
    if (indice != -1) {
        esito = aggiorna_quantita(quantita, PRODOTTI, indice, -150);
        if (esito) {
            printf("  OK: %s -> nuova quantita': %d\n\n",
                   nomi[indice], quantita[indice]);
        } else {
            printf("  RIFIUTATO: quantita' insufficiente\n\n");
        }
    } else {
        printf("  ERRORE: prodotto non trovato\n\n");
    }

    /* ---------------------------------------------------------------- */
    /* Operazione 3: tentativo su codice inesistente */
    printf("Operazione: ricerca codice 9999 (inesistente)\n");
    indice = trova_prodotto(codici, PRODOTTI, 9999);
    if (indice != -1) {
        printf("  Trovato in posizione %d\n\n", indice);
    } else {
        printf("  ERRORE: prodotto non trovato\n\n");
    }

    /* ---------------------------------------------------------------- */
    printf("--- Stato finale ---\n");
    stampa_magazzino(codici, nomi, quantita, PRODOTTI);

    return 0;
}
