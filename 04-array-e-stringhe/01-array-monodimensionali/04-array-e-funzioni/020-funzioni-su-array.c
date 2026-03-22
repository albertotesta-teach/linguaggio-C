/*
 * 020-funzioni-su-array.c
 *
 * Funzioni che calcolano un valore aggregato a partire da un array.
 *
 * Il pattern di queste funzioni è sempre lo stesso:
 *  1. ricevono l'array e la sua dimensione come parametri
 *  2. scorrono l'array con un ciclo
 *  3. restituiscono un singolo valore calcolato con return
 *
 * Ogni funzione ha una responsabilità unica e ben definita.
 * Il main si occupa solo di chiamare le funzioni e presentare i risultati.
 */

#include <stdio.h>

/* Restituisce la somma di tutti gli elementi */
int somma(const int arr[], int n) {
    int i;
    int totale = 0;
    for (i = 0; i < n; i++) {
        totale = totale + arr[i];
    }
    return totale;
}

/* Restituisce la media aritmetica come double */
double media(const int arr[], int n) {
    return (double)somma(arr, n) / n;
    /* Nota: media() richiama somma() per evitare duplicazione di codice */
}

/* Restituisce l'INDICE dell'elemento massimo (non il valore) */
int indice_massimo(const int arr[], int n) {
    int i;
    int idx_max = 0;
    for (i = 1; i < n; i++) {
        if (arr[i] > arr[idx_max]) {
            idx_max = i;
        }
    }
    return idx_max;
}

/* Restituisce l'INDICE dell'elemento minimo */
int indice_minimo(const int arr[], int n) {
    int i;
    int idx_min = 0;
    for (i = 1; i < n; i++) {
        if (arr[i] < arr[idx_min]) {
            idx_min = i;
        }
    }
    return idx_min;
}

/* Conta quanti elementi soddisfano la condizione: valore > soglia */
int conta_sopra_soglia(const int arr[], int n, int soglia) {
    int i;
    int contatore = 0;
    for (i = 0; i < n; i++) {
        if (arr[i] > soglia) {
            contatore++;
        }
    }
    return contatore;
}

/* Cerca un valore nell'array; restituisce l'indice oppure -1 se assente */
int cerca(const int arr[], int n, int valore) {
    int i;
    int trovato = 0;
    int risultato = -1;
    for (i = 0; i < n && !trovato; i++) {
        if (arr[i] == valore) {
            trovato = 1;
            risultato = i;
        }
    }
    return risultato;
}

/* Stampa l'array con indici */
void stampa(const int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("  arr[%d] = %d\n", i, arr[i]);
    }
}

int main(void) {

    int dati[8] = {14, 7, 23, 5, 18, 23, 9, 31};
    int n = 8;
    int idx;

    printf("Array:\n");
    stampa(dati, n);
    printf("\n");

    /* Utilizzo delle funzioni: il main legge i risultati e li presenta */
    printf("Somma              : %d\n", somma(dati, n));
    printf("Media              : %.2f\n", media(dati, n));

    idx = indice_massimo(dati, n);
    printf("Massimo            : %d  (posizione %d)\n", dati[idx], idx);

    idx = indice_minimo(dati, n);
    printf("Minimo             : %d  (posizione %d)\n", dati[idx], idx);

    printf("Elementi > 15      : %d\n", conta_sopra_soglia(dati, n, 15));

    idx = cerca(dati, n, 23);
    if (idx != -1) {
        printf("Valore 23 trovato  : posizione %d\n", idx);
    } else {
        printf("Valore 23          : non presente\n");
    }

    idx = cerca(dati, n, 99);
    if (idx != -1) {
        printf("Valore 99 trovato  : posizione %d\n", idx);
    } else {
        printf("Valore 99          : non presente\n");
    }

    return 0;
}
