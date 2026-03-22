/*
 * 020-minimo-massimo-e-ricerca.c
 *
 * Ricerca del minimo, del massimo e di un valore specifico in un array.
 *
 * Il pattern "ipotesi + smentita" è la tecnica standard per trovare
 * il minimo e il massimo senza conoscere il range dei valori a priori:
 * si ipotizza che il primo elemento sia l'estremo, poi si scorre
 * il resto dell'array cercando elementi che smentiscano l'ipotesi.
 *
 * La ricerca di un valore usa invece una variabile flag (trovato)
 * che interrompe logicamente il ciclo senza usare break.
 */

#include <stdio.h>

#define N 12

int main(void) {

    int misure[N] = {34, 12, 78, 5, 91, 23, 67, 45, 91, 8, 56, 33};
    int i;

    /* Stampa dell'array */
    printf("Array: ");
    for (i = 0; i < N; i++) {
        printf("%4d", misure[i]);
    }
    printf("\n\n");

    /* ------------------------------------------------------------------ */
    /* Ricerca del massimo: pattern "ipotesi + smentita".
     * Si salva l'INDICE (non il valore) così da poter riferire sia
     * la posizione che il valore dell'estremo trovato. */
    int indice_max = 0;   /* ipotesi: il massimo è in posizione 0 */

    for (i = 1; i < N; i++) {
        /* Smentita: se trovo un valore maggiore, aggiorno l'ipotesi */
        if (misure[i] > misure[indice_max]) {
            indice_max = i;
        }
    }

    printf("Massimo: %d  (posizione %d)\n", misure[indice_max], indice_max);

    /* ------------------------------------------------------------------ */
    /* Ricerca del minimo: stesso pattern, condizione invertita */
    int indice_min = 0;

    for (i = 1; i < N; i++) {
        if (misure[i] < misure[indice_min]) {
            indice_min = i;
        }
    }

    printf("Minimo : %d  (posizione %d)\n\n", misure[indice_min], indice_min);

    /* ------------------------------------------------------------------ */
    /* Ricerca del secondo massimo (massimo escludendo il primo).
     * Si scorre cercando il massimo tra i valori diversi dal primo massimo.
     * Attenzione: se ci sono duplicati del massimo, il secondo massimo
     * potrebbe avere lo stesso valore. */
    int indice_max2 = (indice_max == 0) ? 1 : 0;   /* parte da un indice != max */

    for (i = 0; i < N; i++) {
        if (i != indice_max && misure[i] > misure[indice_max2]) {
            indice_max2 = i;
        }
    }

    printf("Secondo massimo: %d  (posizione %d)\n\n",
           misure[indice_max2], indice_max2);

    /* ------------------------------------------------------------------ */
    /* Ricerca di un valore specifico con variabile flag.
     * La condizione del for include !trovato: il ciclo si ferma
     * logicamente alla prima occorrenza, senza usare break. */
    int cercato = 91;
    int trovato = 0;
    int posizione = -1;   /* -1 = valore sentinella "non trovato" */

    for (i = 0; i < N && !trovato; i++) {
        if (misure[i] == cercato) {
            trovato = 1;
            posizione = i;
        }
    }

    printf("Ricerca valore %d:\n", cercato);
    if (trovato) {
        printf("  Trovato in posizione %d\n\n", posizione);
    } else {
        printf("  Non presente nell'array\n\n");
    }

    /* ------------------------------------------------------------------ */
    /* Conteggio delle occorrenze di un valore.
     * A differenza della ricerca (che si ferma alla prima), il conteggio
     * percorre tutto l'array senza condizione di uscita anticipata. */
    int valore_da_contare = 91;
    int occorrenze = 0;

    for (i = 0; i < N; i++) {
        if (misure[i] == valore_da_contare) {
            occorrenze++;
        }
    }

    printf("Occorrenze di %d nell'array: %d\n", valore_da_contare, occorrenze);

    return 0;
}
