/*
 * 040-problema-lista-della-spesa.c
 *
 * Problema reale: gestione di una lista della spesa con array a tappo.
 *
 * Scenario: un'applicazione gestisce una lista della spesa memorizzando
 * i prezzi degli articoli in centesimi in un array a tappo (tappo = -1).
 * Il programma calcola il totale, conta gli articoli, trova il più caro
 * e permette di aggiungere nuovi articoli prima del tappo.
 *
 * Struttura dati chiave:
 *  - un solo array di int in centesimi, terminato da -1.
 *  - La "lunghezza" della lista non è memorizzata esplicitamente:
 *    si ricava ogni volta scorrendo fino al tappo.
 *  - Aggiungere un articolo = scrivere prima del tappo e spostarlo.
 *
 * Concetti applicati:
 *  - funzioni su array a tappo che non ricevono n come parametro
 *  - modifica della lista tramite spostamento del tappo
 *  - conversione centesimi ↔ euro per la stampa
 */

#include <stdio.h>

#define TAPPO   -1
#define MAX     20   /* capacità massima incluso tappo */

/* Restituisce il numero di articoli (indice del tappo) */
int conta_articoli(const int prezzi[]) {
    int i = 0;
    while (prezzi[i] != TAPPO) {
        i++;
    }
    return i;
}

/* Restituisce il totale in centesimi */
int totale(const int prezzi[]) {
    int i = 0;
    int somma = 0;
    while (prezzi[i] != TAPPO) {
        somma = somma + prezzi[i];
        i++;
    }
    return somma;
}

/* Restituisce l'indice dell'articolo più caro */
int indice_piu_caro(const int prezzi[]) {
    int i = 0;
    int idx_max = 0;
    while (prezzi[i] != TAPPO) {
        if (prezzi[i] > prezzi[idx_max]) {
            idx_max = i;
        }
        i++;
    }
    return idx_max;
}

/* Aggiunge un articolo in fondo (prima del tappo).
 * Restituisce 1 se riuscito, 0 se lista piena. */
int aggiungi(int prezzi[], int prezzo_centesimi) {
    int pos = conta_articoli(prezzi);
    int esito = 0;
    if (pos + 1 < MAX) {
        prezzi[pos]     = prezzo_centesimi;
        prezzi[pos + 1] = TAPPO;
        esito = 1;
    }
    return esito;
}

/* Stampa la lista con prezzi in formato euro */
void stampa_lista(const int prezzi[]) {
    int i = 0;
    printf("  N. | Prezzo\n");
    printf("  ---|--------\n");
    while (prezzi[i] != TAPPO) {
        printf("  %2d | %3d,%02d euro\n",
               i + 1, prezzi[i] / 100, prezzi[i] % 100);
        i++;
    }
}

int main(void) {

    /* Lista iniziale: prezzi in centesimi, terminata da TAPPO */
    int lista[MAX] = {149, 299, 89, 450, 199, TAPPO};

    printf("=== LISTA DELLA SPESA ===\n\n");

    printf("Lista attuale:\n");
    stampa_lista(lista);
    printf("\n");

    int n   = conta_articoli(lista);
    int tot = totale(lista);
    int idx = indice_piu_caro(lista);

    printf("Articoli     : %d\n", n);
    printf("Totale       : %d,%02d euro\n", tot / 100, tot % 100);
    printf("Articolo piu' caro: n.%d (%d,%02d euro)\n\n",
           idx + 1, lista[idx] / 100, lista[idx] % 100);

    /* ---------------------------------------------------------------- */
    /* Aggiunta di nuovi articoli */
    printf("Aggiunta articolo da 2,50 euro (250 centesimi):\n");
    if (aggiungi(lista, 250)) {
        printf("  OK -> ora %d articoli\n", conta_articoli(lista));
    } else {
        printf("  LISTA PIENA\n");
    }

    printf("Aggiunta articolo da 0,75 euro (75 centesimi):\n");
    if (aggiungi(lista, 75)) {
        printf("  OK -> ora %d articoli\n", conta_articoli(lista));
    } else {
        printf("  LISTA PIENA\n");
    }
    printf("\n");

    printf("Lista aggiornata:\n");
    stampa_lista(lista);
    printf("\n");

    tot = totale(lista);
    printf("Nuovo totale : %d,%02d euro\n", tot / 100, tot % 100);

    return 0;
}
