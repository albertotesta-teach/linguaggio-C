/*
 * 010-passaggio-array-a-funzione.c
 *
 * Come passare un array a una funzione in C.
 *
 * In C le variabili scalari (int, double, char) vengono passate alle
 * funzioni PER VALORE: la funzione riceve una copia e le modifiche
 * non si propagano al chiamante.
 *
 * Gli array vengono passati PER RIFERIMENTO: la funzione riceve
 * l'indirizzo del primo elemento e lavora direttamente sulla memoria
 * originale. Qualsiasi modifica fatta dentro la funzione è visibile
 * anche fuori.
 *
 * La dimensione dell'array NON viene passata automaticamente: va
 * sempre indicata come parametro separato.
 */

#include <stdio.h>

/* ------------------------------------------------------------------ */
/* Funzione che LEGGE un array senza modificarlo.
 * Il qualificatore 'const' segnala che l'array non verrà modificato:
 * è una garanzia per il chiamante e per chi legge il codice. */
void stampa(const int arr[], int n) {
    int i;
    printf("[ ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

/* ------------------------------------------------------------------ */
/* Funzione che MODIFICA un array: raddoppia ogni elemento.
 * Senza 'const': la funzione ha piena libertà di scrivere sull'array. */
void raddoppia(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = arr[i] * 2;   /* modifica diretta in memoria */
    }
}

/* ------------------------------------------------------------------ */
/* Dimostrazione del passaggio per valore di uno scalare.
 * La modifica dentro la funzione NON si propaga al chiamante. */
void tenta_modifica_scalare(int x) {
    x = 999;   /* modifica solo la copia locale */
}

/* ------------------------------------------------------------------ */
/* Dimostrazione: la dimensione va passata esplicitamente.
 * sizeof(arr) dentro una funzione restituisce la dimensione del
 * PUNTATORE (tipicamente 8 byte), non quella dell'array originale. */
void mostra_dimensione(const int arr[], int n) {
    printf("  n ricevuto come parametro : %d elementi\n", n);
    printf("  sizeof(arr) dentro funzione: %lu byte (dimensione del puntatore)\n",
           sizeof(arr));
}

int main(void) {

    int valori[6] = {3, 7, 1, 9, 4, 6};
    int scalare = 42;

    /* ---------------------------------------------------------------- */
    printf("=== Passaggio per riferimento (array) ===\n");
    printf("Prima di raddoppia(): ");
    stampa(valori, 6);

    raddoppia(valori, 6);   /* modifica l'array originale */

    printf("Dopo  raddoppia(): ");
    stampa(valori, 6);
    printf("\n");

    /* ---------------------------------------------------------------- */
    printf("=== Passaggio per valore (scalare) ===\n");
    printf("Prima di tenta_modifica_scalare(): scalare = %d\n", scalare);
    tenta_modifica_scalare(scalare);
    printf("Dopo  tenta_modifica_scalare(): scalare = %d  (invariato)\n\n", scalare);

    /* ---------------------------------------------------------------- */
    printf("=== Dimensione dell'array ===\n");
    printf("  sizeof(valori) nel main: %lu byte (%lu elementi)\n",
           sizeof(valori), sizeof(valori) / sizeof(valori[0]));
    mostra_dimensione(valori, 6);
    printf("\n");

    /* ---------------------------------------------------------------- */
    /* Passaggio di una PARTE dell'array: si passa l'indirizzo
     * di un elemento interno con &valori[i].
     * La funzione vede solo gli elementi da quell'indice in poi. */
    printf("=== Passaggio di una porzione dell'array ===\n");
    printf("Ultimi 3 elementi: ");
    stampa(&valori[3], 3);   /* passa l'indirizzo di valori[3] */

    return 0;
}
