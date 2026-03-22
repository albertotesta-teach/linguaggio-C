/*
 * 030-trasformazione-elementi.c
 *
 * Operazioni che modificano il contenuto di un array (trasformazioni in-place).
 *
 * Finora abbiamo solo letto gli elementi di un array. Questo file mostra
 * come modificarli direttamente nella loro posizione in memoria:
 *  - inversione dell'ordine degli elementi (con variabile d'appoggio)
 *  - applicazione di una formula a tutti gli elementi
 *  - azzeramento selettivo degli elementi che soddisfano una condizione
 *
 * La tecnica dello swap (scambio) con variabile d'appoggio è fondamentale
 * e riappare negli algoritmi di ordinamento del capitolo 11.
 */

#include <stdio.h>

#define N 8

/* Funzione di utilità per stampare l'array */
void stampa_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%5d", arr[i]);
    }
    printf("\n");
}

int main(void) {

    int valori[N] = {3, -1, 7, -4, 9, 2, -6, 5};
    int i;
    int temp;

    printf("Array originale   : ");
    stampa_array(valori, N);
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* INVERSIONE degli elementi (reverse in-place).
     * Si scambiano gli elementi simmetrici: [0] con [N-1], [1] con [N-2], ecc.
     * Il ciclo arriva a metà array (i < N/2): ogni coppia viene scambiata
     * una sola volta.
     *
     * Lo SWAP richiede una variabile d'appoggio 'temp':
     *   temp       = valori[i]         salva il valore a sinistra
     *   valori[i]  = valori[N-1-i]     sovrascrive con il valore a destra
     *   valori[N-1-i] = temp           mette il valore salvato a destra
     *
     * Senza temp, uno dei due valori andrebbe perso. */
    for (i = 0; i < N / 2; i++) {
        temp            = valori[i];
        valori[i]       = valori[N - 1 - i];
        valori[N-1-i]   = temp;
    }

    printf("Dopo inversione   : ");
    stampa_array(valori, N);
    printf("\n");

    /* Ripristina l'array originale per le operazioni successive */
    int originale[N] = {3, -1, 7, -4, 9, 2, -6, 5};
    for (i = 0; i < N; i++) {
        valori[i] = originale[i];
    }

    /* ------------------------------------------------------------------ */
    /* APPLICAZIONE DI UNA FORMULA a tutti gli elementi (trasformazione uniforme).
     * Ogni elemento viene sostituito con il suo valore assoluto.
     * L'operatore ternario sceglie il segno: se negativo, cambia segno. */
    for (i = 0; i < N; i++) {
        if (valori[i] < 0) {
            valori[i] = -valori[i];   /* cambia segno ai negativi */
        }
        /* i positivi e lo zero rimangono invariati */
    }

    printf("Valore assoluto   : ");
    stampa_array(valori, N);

    /* Ripristina */
    for (i = 0; i < N; i++) {
        valori[i] = originale[i];
    }

    /* ------------------------------------------------------------------ */
    /* AZZERAMENTO SELETTIVO: porta a zero tutti gli elementi negativi.
     * Utile per "pulire" un array da valori non validi o non desiderati. */
    for (i = 0; i < N; i++) {
        if (valori[i] < 0) {
            valori[i] = 0;
        }
    }

    printf("Negativi azzerati : ");
    stampa_array(valori, N);

    /* Ripristina */
    for (i = 0; i < N; i++) {
        valori[i] = originale[i];
    }

    /* ------------------------------------------------------------------ */
    /* COPIA di un array in un secondo array.
     * In C non esiste l'assegnazione diretta tra array (arr2 = arr1 è illegale).
     * La copia va fatta elemento per elemento con un ciclo. */
    int copia[N];
    for (i = 0; i < N; i++) {
        copia[i] = valori[i];
    }

    /* Modifica la copia per dimostrare che è indipendente dall'originale */
    copia[0] = 999;

    printf("\nOriginale dopo copia : ");
    stampa_array(valori, N);
    printf("Copia modificata     : ");
    stampa_array(copia, N);

    return 0;
}
