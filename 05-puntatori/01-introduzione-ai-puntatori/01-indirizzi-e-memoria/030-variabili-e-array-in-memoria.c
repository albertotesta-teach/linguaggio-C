/*
 * 030-variabili-e-array-in-memoria.c
 *
 * Come sono disposti variabili e array in memoria
 *
 * Variabili diverse occupano zone diverse della memoria, ma il compilatore
 * è libero di disporle nell'ordine che preferisce: non si può fare alcuna
 * ipotesi su quale venga prima.
 *
 * Gli elementi di un ARRAY invece sono sempre CONSECUTIVI: v[1] inizia
 * subito dopo la fine di v[0]. Per un array di int (4 byte) gli indirizzi
 * crescono di 4 in 4, per un array di double (8 byte) di 8 in 8.
 *
 * Per mostrarlo senza fare calcoli sugli indirizzi (argomento della sezione
 * "puntatori e array") il programma stampa gli indirizzi e li confronta
 * con l'operatore <, che per gli elementi di uno stesso array dice quale
 * viene prima in memoria.
 *
 * Gli indirizzi cambiano a ogni esecuzione.
 */

#include <stdio.h>

#define N 5

int main(void)
{
    int voti[N] = {7, 8, 6, 9, 7};
    double pesi[N] = {1.0, 1.5, 1.0, 2.0, 1.0};
    int k;
    int crescenti = 1;

    printf("=== ARRAY DI int (%zu byte per elemento) ===\n", sizeof(voti[0]));
    for (k = 0; k < N; k++) {
        printf("  voti[%d] = %d   indirizzo %p\n", k, voti[k], (void *) &voti[k]);
    }

    printf("\n=== ARRAY DI double (%zu byte per elemento) ===\n", sizeof(pesi[0]));
    for (k = 0; k < N; k++) {
        printf("  pesi[%d] = %.1f indirizzo %p\n", k, pesi[k], (void *) &pesi[k]);
    }

    /* gli elementi sono in ordine crescente di indirizzo */
    for (k = 0; k < N - 1; k++) {
        if (!(&voti[k] < &voti[k + 1])) {
            crescenti = 0;
        }
    }
    printf("\nGli indirizzi di voti[] sono crescenti: %s\n", crescenti ? "si'" : "no");
    printf("L'array occupa %zu byte consecutivi a partire da %p\n",
           sizeof(voti), (void *) &voti[0]);
    printf("Osserva le ultime cifre: crescono di %zu per voti[] e di %zu per pesi[].\n",
           sizeof(voti[0]), sizeof(pesi[0]));

    return 0;
}
