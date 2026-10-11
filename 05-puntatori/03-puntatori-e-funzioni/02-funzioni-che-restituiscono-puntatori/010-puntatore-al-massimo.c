/*
 * 010-puntatore-al-massimo.c
 *
 * Una funzione che restituisce un puntatore
 *
 * Una funzione può restituire un indirizzo. Se cerca un elemento in un
 * array e ne restituisce il PUNTATORE (invece del valore o dell'indice), il
 * chiamante può sia leggere l'elemento sia MODIFICARLO direttamente:
 *
 *     int *massimo(int *v, int n);
 *
 *     int *caldo = massimo(temperature, N);
 *     *caldo = *caldo - 3;          modifica l'elemento dentro l'array
 *     caldo - temperature           posizione dell'elemento
 *
 * Il puntatore restituito è valido perché punta dentro l'array del
 * CHIAMANTE, che esiste anche dopo la fine della funzione.
 *
 * Se il chiamante deve solo leggere si usa la versione con const:
 *     const int *minimo(const int *v, int n);
 *
 * Esempio: le temperature (in decimi di grado) dei frigoriferi della mensa.
 */

#include <stdio.h>

#define FRIGO 5
#define LIMITE 50                       /* 5.0 gradi */

int *massimo(int *v, int n);
const int *minimo(const int *v, int n);
void stampa(const int *v, int n);

int main(void)
{
    int temperature[FRIGO] = {38, 42, 61, 35, 47};
    int *caldo;
    const int *freddo;

    printf("Temperature:");
    stampa(temperature, FRIGO);

    caldo = massimo(temperature, FRIGO);
    printf("Frigo piu' caldo: n. %d con %.1f gradi\n",
           (int) (caldo - temperature) + 1, *caldo / 10.0);

    /* intervento del tecnico: si scrive tramite il puntatore restituito */
    while (*caldo > LIMITE) {
        *caldo = *caldo - 4;
    }
    printf("Dopo l'intervento sul frigo n. %d:", (int) (caldo - temperature) + 1);
    stampa(temperature, FRIGO);

    freddo = minimo(temperature, FRIGO);
    printf("Frigo piu' freddo: n. %d con %.1f gradi\n",
           (int) (freddo - temperature) + 1, *freddo / 10.0);

    /* il risultato si può usare anche direttamente in un'espressione */
    printf("Temperatura massima attuale: %.1f gradi\n", *massimo(temperature, FRIGO) / 10.0);

    return 0;
}

/* Restituisce l'indirizzo dell'elemento maggiore (il primo, a parità). */
int *massimo(int *v, int n)
{
    int *p;
    int *migliore = v;

    for (p = v + 1; p < v + n; p++) {
        if (*p > *migliore) {
            migliore = p;
        }
    }
    return migliore;
}

/* Come massimo, ma in sola lettura: riceve e restituisce const int *. */
const int *minimo(const int *v, int n)
{
    const int *p;
    const int *migliore = v;

    for (p = v + 1; p < v + n; p++) {
        if (*p < *migliore) {
            migliore = p;
        }
    }
    return migliore;
}

void stampa(const int *v, int n)
{
    const int *p;

    for (p = v; p < v + n; p++) {
        printf(" %5.1f", *p / 10.0);
    }
    printf("\n");
}
