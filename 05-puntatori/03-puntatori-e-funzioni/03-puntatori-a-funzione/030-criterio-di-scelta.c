/*
 * 030-criterio-di-scelta.c
 *
 * Il "migliore" secondo un criterio scelto dal chiamante
 *
 * Trovare il migliore di un elenco richiede sempre lo stesso ciclo; cambia
 * solo il modo di confrontare due elementi. Il criterio si passa come
 * puntatore a funzione:
 *
 *     int (*preferisci)(int a, int b)    restituisce 1 se a è preferibile
 *                                        a b, 0 altrimenti
 *
 *     const int *migliore(const int *v, int n, int (*preferisci)(int, int));
 *
 * migliore restituisce il puntatore all'elemento scelto (come nella
 * sezione 02): dal puntatore si ricava anche la posizione.
 *
 * Esempio: i tempi di consegna (in minuti) degli ordini di una pizzeria
 * nel corso di una serata. Il titolare cerca la consegna più rapida, la più
 * lenta e quella più vicina ai 30 minuti promessi ai clienti.
 */

#include <stdio.h>

#define ORDINI 8
#define PROMESSI 30

const int *migliore(const int *v, int n, int (*preferisci)(int, int));
int piu_rapido(int a, int b);
int piu_lento(int a, int b);
int piu_vicino_promessa(int a, int b);
int distanza(int x);

int main(void)
{
    int tempi[ORDINI] = {34, 22, 41, 29, 52, 31, 18, 27};
    const int *scelto;

    scelto = migliore(tempi, ORDINI, piu_rapido);
    printf("Consegna piu' rapida:       ordine %d, %d minuti\n",
           (int) (scelto - tempi) + 1, *scelto);

    scelto = migliore(tempi, ORDINI, piu_lento);
    printf("Consegna piu' lenta:        ordine %d, %d minuti\n",
           (int) (scelto - tempi) + 1, *scelto);

    scelto = migliore(tempi, ORDINI, piu_vicino_promessa);
    printf("Piu' vicina ai %d minuti:   ordine %d, %d minuti\n",
           PROMESSI, (int) (scelto - tempi) + 1, *scelto);

    return 0;
}

/* Restituisce il puntatore all'elemento che preferisci considera migliore
 * di tutti gli altri; a parità resta il primo. */
const int *migliore(const int *v, int n, int (*preferisci)(int, int))
{
    const int *p;
    const int *scelto = v;

    for (p = v + 1; p < v + n; p++) {
        if (preferisci(*p, *scelto)) {
            scelto = p;
        }
    }
    return scelto;
}

int piu_rapido(int a, int b)
{
    return a < b;
}

int piu_lento(int a, int b)
{
    return a > b;
}

int piu_vicino_promessa(int a, int b)
{
    return distanza(a) < distanza(b);
}

/* Minuti di differenza rispetto ai tempi promessi. */
int distanza(int x)
{
    return x > PROMESSI ? x - PROMESSI : PROMESSI - x;
}
