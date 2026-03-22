/*
 * 020-operazioni-con-tappo.c
 *
 * Operazioni fondamentali su array a tappo.
 *
 * Questo file mostra come le operazioni classiche sugli array
 * (lunghezza, scorrimento, ricerca, inserimento, rimozione)
 * si riscrivono quando la fine dell'array è segnata da un tappo
 * anziché da un parametro n.
 *
 * Il pattern del ciclo cambia:
 *   PRIMA (dimensione fissa):  for (i = 0; i < n; i++)
 *   ORA   (array a tappo):     while (arr[i] != TAPPO) { ... i++; }
 *
 * ATTENZIONE: l'array deve sempre avere spazio sufficiente per
 * contenere tutti gli elementi validi PIÙ il tappo. La costante
 * MAX definisce la capacità totale incluso il tappo.
 */

#include <stdio.h>

#define TAPPO -1
#define MAX   15

/* Restituisce il numero di elementi validi (indice del tappo) */
int lunghezza(const int arr[]) {
    int i = 0;
    while (arr[i] != TAPPO) {
        i++;
    }
    return i;
}

/* Stampa tutti gli elementi validi */
void stampa(const int arr[]) {
    int i = 0;
    printf("[ ");
    while (arr[i] != TAPPO) {
        printf("%d ", arr[i]);
        i++;
    }
    printf("]\n");
}

/* Cerca un valore; restituisce l'indice o -1 se non trovato.
 * Nota: -1 come "non trovato" è diverso da TAPPO = -1 come sentinella.
 * Qui non c'è ambiguità perché la ricerca si ferma prima di raggiungere
 * il tappo (condizione del while). */
int cerca(const int arr[], int valore) {
    int i = 0;
    int trovato = 0;
    int risultato = -1;
    while (arr[i] != TAPPO && !trovato) {
        if (arr[i] == valore) {
            trovato = 1;
            risultato = i;
        }
        i++;
    }
    return risultato;
}

/* Inserisce un valore in fondo (prima del tappo).
 * Restituisce 1 se riuscito, 0 se l'array è pieno (no spazio per il tappo). */
int inserisci_in_fondo(int arr[], int valore) {
    int pos = lunghezza(arr);
    int esito = 0;

    /* Controlla che ci sia spazio: pos è l'indice del tappo attuale.
     * Dopo l'inserimento, il tappo si sposta a pos+1, che deve essere < MAX. */
    if (pos + 1 < MAX) {
        arr[pos]     = valore;   /* sovrascrive il tappo con il nuovo valore */
        arr[pos + 1] = TAPPO;    /* posiziona il nuovo tappo */
        esito = 1;
    }
    return esito;
}

/* Rimuove l'elemento in posizione idx spostando tutti gli elementi
 * successivi di una posizione verso sinistra (il tappo si sposta anch'esso).
 * Restituisce 1 se riuscito, 0 se l'indice non è valido. */
int rimuovi(int arr[], int idx) {
    int len = lunghezza(arr);
    int esito = 0;
    int i;

    if (idx >= 0 && idx < len) {
        /* Sposta ogni elemento di una posizione a sinistra.
         * Il ciclo include la posizione del tappo (i <= len)
         * così il tappo viene spostato anch'esso. */
        for (i = idx; i < len; i++) {
            arr[i] = arr[i + 1];
        }
        esito = 1;
    }
    return esito;
}

int main(void) {

    int dati[MAX] = {7, 3, 15, 9, 22, 5, TAPPO};

    printf("=== OPERAZIONI SU ARRAY A TAPPO ===\n\n");

    printf("Array iniziale : ");
    stampa(dati);
    printf("Lunghezza      : %d elementi\n\n", lunghezza(dati));

    /* ---------------------------------------------------------------- */
    /* Ricerca */
    int val_cercato = 9;
    int pos = cerca(dati, val_cercato);
    if (pos != -1) {
        printf("Ricerca %d: trovato in posizione %d\n", val_cercato, pos);
    } else {
        printf("Ricerca %d: non trovato\n", val_cercato);
    }

    val_cercato = 99;
    pos = cerca(dati, val_cercato);
    if (pos != -1) {
        printf("Ricerca %d: trovato in posizione %d\n\n", val_cercato, pos);
    } else {
        printf("Ricerca %d: non trovato\n\n", val_cercato);
    }

    /* ---------------------------------------------------------------- */
    /* Inserimento in fondo */
    printf("Inserimento di 42 in fondo:\n");
    if (inserisci_in_fondo(dati, 42)) {
        printf("  OK -> ");
        stampa(dati);
    } else {
        printf("  FALLITO: array pieno\n");
    }
    printf("\n");

    /* ---------------------------------------------------------------- */
    /* Rimozione per indice */
    printf("Rimozione dell'elemento in posizione 2 (valore %d):\n", dati[2]);
    if (rimuovi(dati, 2)) {
        printf("  OK -> ");
        stampa(dati);
    } else {
        printf("  FALLITO: indice non valido\n");
    }
    printf("\n");

    /* ---------------------------------------------------------------- */
    /* Riempimento progressivo: mostra come il tappo avanza */
    printf("Riempimento progressivo di un array vuoto:\n");
    int vuoto[MAX] = {TAPPO};
    int valori_da_aggiungere[] = {10, 20, 30, 40, 50};
    int k;

    for (k = 0; k < 5; k++) {
        inserisci_in_fondo(vuoto, valori_da_aggiungere[k]);
        printf("  Dopo inserimento %d: ", valori_da_aggiungere[k]);
        stampa(vuoto);
    }

    return 0;
}
