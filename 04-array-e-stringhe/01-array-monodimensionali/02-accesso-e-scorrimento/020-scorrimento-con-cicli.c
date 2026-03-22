/*
 * 020-scorrimento-con-cicli.c
 *
 * Scorrimento di un array con diversi tipi di ciclo.
 *
 * Scorrere un array significa visitare sequenzialmente tutti (o alcuni)
 * dei suoi elementi. Il ciclo for è la forma più comune, ma lo stesso
 * risultato si può ottenere con while e do-while. Questo file confronta
 * le tre forme e mostra lo scorrimento parziale e in ordine inverso.
 */

#include <stdio.h>

#define N 8

int main(void) {

    int valori[N] = {5, 12, 3, 18, 7, 25, 9, 14};
    int i;

    /* ------------------------------------------------------------------ */
    /* Scorrimento con for: forma standard e più leggibile.
     * Il for compatta in una riga: inizializzazione, condizione e aggiornamento. */
    printf("Scorrimento con for (da sinistra a destra):\n");
    for (i = 0; i < N; i++) {
        printf("  valori[%d] = %d\n", i, valori[i]);
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Scorrimento con while: utile quando la condizione di uscita
     * è più complessa o non è legata a un semplice contatore. */
    printf("Scorrimento con while:\n");
    i = 0;
    while (i < N) {
        printf("  valori[%d] = %d\n", i, valori[i]);
        i++;   /* aggiornamento manuale dell'indice: non va dimenticato */
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Scorrimento con do-while: il corpo viene eseguito almeno una volta
     * prima di verificare la condizione. Utile quando l'array è garantito
     * non vuoto (come in questo caso). */
    printf("Scorrimento con do-while:\n");
    i = 0;
    do {
        printf("  valori[%d] = %d\n", i, valori[i]);
        i++;
    } while (i < N);
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Scorrimento in ordine inverso: da destra a sinistra.
     * L'indice parte da N-1 (ultimo elemento valido) e scende fino a 0. */
    printf("Scorrimento in ordine inverso:\n");
    for (i = N - 1; i >= 0; i--) {
        printf("  valori[%d] = %d\n", i, valori[i]);
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Scorrimento parziale: solo una porzione dell'array.
     * Utile quando non tutti gli elementi sono stati riempiti. */
    printf("Scorrimento parziale (solo i primi 4 elementi):\n");
    for (i = 0; i < 4; i++) {
        printf("  valori[%d] = %d\n", i, valori[i]);
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Scorrimento con passo 2: ogni secondo elemento.
     * L'incremento i += 2 salta un elemento a ogni iterazione. */
    printf("Scorrimento con passo 2 (elementi pari):\n");
    for (i = 0; i < N; i += 2) {
        printf("  valori[%d] = %d\n", i, valori[i]);
    }

    return 0;
}
