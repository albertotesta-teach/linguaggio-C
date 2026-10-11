/*
 * 010-dichiarazione-e-chiamata.c
 *
 * Un puntatore che contiene l'indirizzo di una funzione
 *
 * Anche il codice di una funzione si trova in memoria e ha un indirizzo.
 * Un PUNTATORE A FUNZIONE contiene quell'indirizzo e permette di chiamare
 * la funzione scelta in quel momento.
 *
 *     int (*operazione)(int, int);     puntatore a una funzione che riceve
 *                                      due int e restituisce un int
 *     operazione = somma;              il nome della funzione, senza ()
 *     risultato = operazione(a, b);    chiamata tramite il puntatore
 *
 * Le parentesi intorno a *operazione sono necessarie: senza di esse
 * int *operazione(int, int) dichiarerebbe una FUNZIONE che restituisce un
 * int *. Il puntatore può ricevere solo funzioni con lo stesso prototipo.
 *
 * Esempio: il tabellone di una partita di basket, con i punti delle due
 * squadre combinati in modi diversi.
 */

#include <stdio.h>

int somma(int a, int b);
int differenza(int a, int b);
int massimo(int a, int b);

int main(void)
{
    int casa = 78;
    int ospiti = 71;
    int (*operazione)(int, int);

    printf("Casa %d - Ospiti %d\n\n", casa, ospiti);

    operazione = somma;
    printf("operazione = somma       -> operazione(casa, ospiti) = %3d  (punti totali)\n",
           operazione(casa, ospiti));

    operazione = differenza;
    printf("operazione = differenza  -> operazione(casa, ospiti) = %3d  (scarto)\n",
           operazione(casa, ospiti));

    operazione = massimo;
    printf("operazione = massimo     -> operazione(casa, ospiti) = %3d  (punti vincitrice)\n",
           operazione(casa, ospiti));

    /* forma equivalente, con la dereferenziazione esplicita */
    printf("\n(*operazione)(casa, ospiti) = %d\n", (*operazione)(casa, ospiti));

    /* il puntatore si può confrontare: quale funzione contiene? */
    if (operazione == massimo) {
        printf("Ora operazione punta a massimo.\n");
    }

    return 0;
}

int somma(int a, int b)
{
    return a + b;
}

int differenza(int a, int b)
{
    return a - b;
}

int massimo(int a, int b)
{
    return a > b ? a : b;
}
