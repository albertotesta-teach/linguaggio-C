/*
 * 030-array-in-memoria.c
 *
 * Visualizzazione della struttura di un array in memoria.
 *
 * Questo file mostra come un array monodimensionale è organizzato
 * in memoria: gli elementi sono contigui, ognuno occupa lo stesso
 * numero di byte, e l'indirizzo di ciascun elemento è calcolabile
 * dall'indirizzo del primo elemento più l'offset dato dall'indice.
 *
 * Conoscere questa struttura è fondamentale per capire il legame
 * tra array e puntatori, trattato in un capitolo successivo.
 */

#include <stdio.h>

int main(void) {

    /* Array di esempio con valori espliciti */
    int misure[5] = {10, 20, 30, 40, 50};
    int i;

    /* Stampa della mappa in memoria: indice, valore e indirizzo.
     * L'operatore & (address-of) restituisce l'indirizzo di una variabile.
     * %p è il formato per stampare un puntatore (indirizzo di memoria). */
    printf("Mappa in memoria dell'array 'misure':\n");
    printf("---------------------------------------------------\n");
    printf("  Indice  | Valore | Indirizzo       | Offset\n");
    printf("---------------------------------------------------\n");

    for (i = 0; i < 5; i++) {
        /* Calcola l'offset in byte rispetto al primo elemento.
         * Ogni int occupa sizeof(int) byte (tipicamente 4).
         * L'elemento i si trova a i * sizeof(int) byte dall'inizio. */
        int offset = i * (int)sizeof(misure[0]);
        printf("  [%d]     |  %3d   | %p | +%d byte\n",
               i, misure[i], (void *)&misure[i], offset);
    }

    printf("---------------------------------------------------\n\n");

    /* Conferma visiva: la differenza tra indirizzi consecutivi
     * deve essere esattamente sizeof(int) byte. */
    printf("Distanza tra elementi consecutivi:\n");
    for (i = 0; i < 4; i++) {
        /* Sottrazione di puntatori: restituisce la differenza in byte */
        long distanza = (long)&misure[i + 1] - (long)&misure[i];
        printf("  &misure[%d] - &misure[%d] = %ld byte\n", i + 1, i, distanza);
    }
    printf("\n");

    /* Dimensione complessiva e numero di elementi */
    printf("Riepilogo:\n");
    printf("  sizeof(int)      = %lu byte\n", sizeof(int));
    printf("  sizeof(misure)   = %lu byte\n", sizeof(misure));
    printf("  Numero elementi  = %lu\n", sizeof(misure) / sizeof(misure[0]));

    return 0;
}
