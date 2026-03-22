/*
 * 010-somma-e-media.c
 *
 * Operazioni di somma e media su un array monodimensionale.
 *
 * Il pattern fondamentale per elaborare un array è l'accumulatore:
 * una variabile inizializzata a zero (o al primo elemento) che viene
 * aggiornata a ogni iterazione del ciclo. Questo file mostra il pattern
 * nella sua forma più semplice (somma totale) e in varianti più complesse
 * (somma parziale per condizione, media pesata).
 */

#include <stdio.h>

#define N 10

int main(void) {

    int valori[N] = {4, -2, 7, 0, 15, -8, 3, 11, -1, 6};
    int i;

    /* ------------------------------------------------------------------ */
    /* Somma di tutti gli elementi: pattern accumulatore base.
     * La variabile somma parte da 0 e accumula ogni elemento. */
    int somma = 0;
    for (i = 0; i < N; i++) {
        somma = somma + valori[i];
    }
    printf("Array: ");
    for (i = 0; i < N; i++) {
        printf("%4d", valori[i]);
    }
    printf("\n\n");
    printf("Somma di tutti gli elementi : %d\n", somma);

    /* La media richiede divisione floating point.
     * Il cast (double) converte somma prima della divisione. */
    printf("Media aritmetica            : %.2f\n\n", (double)somma / N);

    /* ------------------------------------------------------------------ */
    /* Somma parziale: solo gli elementi positivi.
     * Si aggiunge un if all'interno del ciclo per filtrare gli elementi. */
    int somma_positivi  = 0;
    int somma_negativi  = 0;
    int count_positivi  = 0;
    int count_negativi  = 0;

    for (i = 0; i < N; i++) {
        if (valori[i] > 0) {
            somma_positivi = somma_positivi + valori[i];
            count_positivi++;
        } else if (valori[i] < 0) {
            somma_negativi = somma_negativi + valori[i];
            count_negativi++;
        }
        /* valori[i] == 0: non contribuisce né alla somma positiva né a quella negativa */
    }

    printf("Somma elementi positivi     : %d  (count: %d)\n",
           somma_positivi, count_positivi);
    printf("Somma elementi negativi     : %d  (count: %d)\n",
           somma_negativi, count_negativi);
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Somma degli elementi in posizione pari (indice 0, 2, 4, ...).
     * Il ciclo avanza di 2 a ogni iterazione. */
    int somma_pari = 0;
    for (i = 0; i < N; i += 2) {
        somma_pari = somma_pari + valori[i];
    }

    /* Somma degli elementi in posizione dispari (indice 1, 3, 5, ...) */
    int somma_dispari = 0;
    for (i = 1; i < N; i += 2) {
        somma_dispari = somma_dispari + valori[i];
    }

    printf("Somma posizioni pari (0,2,4,...) : %d\n", somma_pari);
    printf("Somma posizioni dispari (1,3,...): %d\n\n", somma_dispari);

    /* ------------------------------------------------------------------ */
    /* Somma cumulativa: ogni elemento mostra il totale fino a quel punto.
     * Utile per capire come varia l'accumulatore a ogni passo. */
    printf("Somma cumulativa:\n");
    int accumulatore = 0;
    for (i = 0; i < N; i++) {
        accumulatore = accumulatore + valori[i];
        printf("  Dopo valori[%d] = %3d : totale = %d\n",
               i, valori[i], accumulatore);
    }

    return 0;
}
