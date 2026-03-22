/*
 * 020-inizializzazione.c
 *
 * Modi di inizializzare un array monodimensionale in C.
 *
 * In C è possibile inizializzare un array in fase di dichiarazione
 * in diversi modi: con lista completa, con lista parziale (il resto
 * viene azzerato automaticamente), oppure lasciando che il compilatore
 * deduca la dimensione dalla lista. Questo file mostra e confronta
 * queste tecniche e spiega le differenze pratiche.
 */

#include <stdio.h>

int main(void) {

    int i;

    /* ------------------------------------------------------------------ */
    /* MODO 1: inizializzazione con lista completa.
     * Tutti gli elementi sono specificati esplicitamente.
     * La dimensione deve corrispondere esattamente al numero di valori. */
    int temperature[7] = {18, 21, 23, 20, 17, 15, 19};

    printf("Modo 1 - lista completa:\n");
    for (i = 0; i < 7; i++) {
        printf("  temperatura[%d] = %d\n", i, temperature[i]);
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* MODO 2: inizializzazione con dimensione dedotta dal compilatore.
     * Si omette il numero tra le parentesi quadre: il compilatore conta
     * gli elementi nella lista e imposta la dimensione di conseguenza. */
    int altitudini[] = {120, 340, 89, 450, 210};
    /* Il compilatore deduce che altitudini ha 5 elementi */

    printf("Modo 2 - dimensione dedotta (5 elementi):\n");
    for (i = 0; i < 5; i++) {
        printf("  altitudini[%d] = %d\n", i, altitudini[i]);
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* MODO 3: inizializzazione parziale.
     * Se si specificano meno valori della dimensione dichiarata,
     * gli elementi rimanenti vengono inizializzati automaticamente a 0.
     * Tecnica utile per inizializzare un array a zero rapidamente. */
    int punteggi[10] = {85, 92, 78};
    /* punteggi[0]=85, punteggi[1]=92, punteggi[2]=78,
     * punteggi[3..9]=0 (automaticamente) */

    printf("Modo 3 - inizializzazione parziale (10 elementi, 3 espliciti):\n");
    for (i = 0; i < 10; i++) {
        printf("  punteggi[%d] = %d\n", i, punteggi[i]);
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* MODO 4: inizializzazione a zero con singolo valore.
     * Specificare solo {0} azzera tutti gli elementi.
     * È il modo più compatto per creare un array tutto a zero. */
    int contatori[8] = {0};

    printf("Modo 4 - tutti a zero ({0}):\n");
    for (i = 0; i < 8; i++) {
        printf("  contatori[%d] = %d\n", i, contatori[i]);
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* MODO 5: uso di una costante simbolica per la dimensione.
     * Usare #define rende il codice più leggibile e facile da modificare:
     * basta cambiare la costante per aggiornare tutta la logica. */
    #define NUMERO_MESI 12
    int precipitazioni[NUMERO_MESI] = {45, 38, 52, 61, 70, 30, 20, 25, 55, 80, 65, 50};

    printf("Modo 5 - dimensione con costante #define (%d mesi):\n", NUMERO_MESI);
    for (i = 0; i < NUMERO_MESI; i++) {
        printf("  mese %2d: %d mm\n", i + 1, precipitazioni[i]);
    }

    return 0;
}
