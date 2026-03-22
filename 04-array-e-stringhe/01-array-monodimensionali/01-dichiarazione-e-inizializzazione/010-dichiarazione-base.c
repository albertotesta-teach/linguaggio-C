/*
 * 010-dichiarazione-base.c
 *
 * Dichiarazione di un array monodimensionale in C.
 *
 * Un array è una sequenza di variabili dello stesso tipo occupate in
 * posizioni di memoria contigue. Si dichiara specificando il tipo degli
 * elementi, il nome dell'array e il numero di elementi tra parentesi
 * quadre. Gli elementi sono accessibili tramite un indice che parte da 0.
 *
 * Questo file mostra la dichiarazione di base, l'accesso in lettura e
 * scrittura e la stampa degli elementi con un ciclo.
 */

#include <stdio.h>

int main(void) {

    /* Dichiarazione di un array di 5 interi.
     * Senza inizializzazione esplicita, le celle contengono valori
     * indeterminati (dipende dal compilatore e dalla piattaforma). */
    int voti[5];

    /* Assegnazione dei valori uno per uno tramite indice.
     * Gli indici validi vanno da 0 a 4 (dimensione - 1). */
    voti[0] = 7;
    voti[1] = 8;
    voti[2] = 6;
    voti[3] = 9;
    voti[4] = 7;

    /* Rappresentazione visiva della struttura in memoria:
     *
     *  Indice:  [0]  [1]  [2]  [3]  [4]
     *  Valore:   7    8    6    9    7
     *
     * Ogni cella occupa sizeof(int) byte (tipicamente 4 byte).
     * Le celle sono contigue in memoria. */

    /* Stampa di ogni elemento accedendo direttamente tramite indice */
    printf("Voti della classe:\n");
    printf("  Studente 1: %d\n", voti[0]);
    printf("  Studente 2: %d\n", voti[1]);
    printf("  Studente 3: %d\n", voti[2]);
    printf("  Studente 4: %d\n", voti[3]);
    printf("  Studente 5: %d\n", voti[4]);
    printf("\n");

    /* Stampa con ciclo for: soluzione più compatta e scalabile.
     * La variabile i scorre tutti gli indici validi dell'array. */
    printf("Stessa stampa con ciclo for:\n");
    int i;
    for (i = 0; i < 5; i++) {
        printf("  voti[%d] = %d\n", i, voti[i]);
    }
    printf("\n");

    /* Dimensione in byte dell'intero array e del singolo elemento */
    printf("Dimensione di un elemento : %lu byte\n", sizeof(voti[0]));
    printf("Dimensione totale array   : %lu byte\n", sizeof(voti));
    printf("Numero di elementi        : %lu\n", sizeof(voti) / sizeof(voti[0]));

    return 0;
}
