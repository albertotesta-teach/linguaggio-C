/*
 * 010-somma-di-un-intero.c
 *
 * Sommare un intero a un puntatore
 *
 * Se p punta a un elemento di un array, p + i punta all'elemento che si
 * trova i posizioni più avanti. L'indirizzo NON cresce di i byte ma di
 * i * sizeof(*p) byte: il compilatore conosce il tipo puntato e fa il
 * calcolo da solo.
 *
 *     p + i        indirizzo dell'elemento i posizioni dopo quello puntato
 *     *(p + i)     l'elemento stesso: si legge e si scrive
 *
 * Le parentesi sono necessarie: *p + i somma i al VALORE puntato.
 *
 * Esempio: i posti liberi ai piani di un parcheggio multipiano (int) e le
 * tariffe orarie dei piani (double).
 */

#include <stdio.h>

#define PIANI 4

int main(void)
{
    int liberi[PIANI] = {12, 0, 7, 25};
    double tariffe[PIANI] = {1.50, 1.80, 2.00, 2.50};
    int *p = &liberi[0];
    double *q = &tariffe[0];
    int i;

    printf("=== p + i CON UN ARRAY DI int (%zu byte per elemento) ===\n", sizeof(*p));
    for (i = 0; i < PIANI; i++) {
        printf("  p + %d = %p   *(p + %d) = %2d posti liberi al piano %d\n",
               i, (void *) (p + i), i, *(p + i), i);
    }

    printf("\n=== q + i CON UN ARRAY DI double (%zu byte per elemento) ===\n", sizeof(*q));
    for (i = 0; i < PIANI; i++) {
        printf("  q + %d = %p   *(q + %d) = %.2f euro/ora\n",
               i, (void *) (q + i), i, *(q + i));
    }

    /* scrivere tramite p + i modifica l'elemento dell'array */
    *(p + 1) = *(p + 1) + 3;
    printf("\nDopo *(p + 1) = *(p + 1) + 3:  liberi[1] = %d\n", liberi[1]);

    /* le parentesi cambiano il significato */
    printf("\n*(p + 2) = %2d   elemento di indice 2\n", *(p + 2));
    printf("*p + 2   = %2d   valore di liberi[0] piu' 2\n", *p + 2);

    return 0;
}
