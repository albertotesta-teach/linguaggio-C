/*
 * 060-problema-coppia-piu-vicina.c
 *
 * Arrivo della campestre: il fotofinish
 *
 * Alla corsa campestre d'istituto i tempi di arrivo (in decimi di secondo)
 * sono registrati nell'ordine dei pettorali, non in ordine di arrivo. Il
 * giudice vuole sapere quali due atleti sono arrivati più vicini tra loro,
 * per controllare il fotofinish.
 *
 * coppia_piu_vicina restituisce con return la distanza minima e, tramite
 * due parametri di uscita di tipo const int **, i PUNTATORI ai due tempi:
 *
 *     int coppia_piu_vicina(const int *tempi, int n,
 *                           const int **primo, const int **secondo);
 *
 *     coppia_piu_vicina(tempi, N, &a, &b);    a e b puntano nell'array
 *
 * Dai puntatori ricevuti il main ricava i pettorali (a - tempi + 1).
 */

#include <stdio.h>

#define ATLETI 8

int coppia_piu_vicina(const int *tempi, int n, const int **primo, const int **secondo);
int distanza(int x, int y);

int main(void)
{
    int tempi[ATLETI] = {7342, 7120, 7865, 7343, 7240, 7461, 7228, 7980};
    const int *a;
    const int *b;
    int i;
    int d;

    printf("Pettorale:");
    for (i = 0; i < ATLETI; i++) {
        printf(" %6d", i + 1);
    }
    printf("\nTempo (s):");
    for (i = 0; i < ATLETI; i++) {
        printf(" %6.1f", tempi[i] / 10.0);
    }
    printf("\n\n");

    d = coppia_piu_vicina(tempi, ATLETI, &a, &b);
    printf("Arrivo piu' combattuto: pettorali %d e %d (%.1f s e %.1f s), distacco %.1f s\n",
           (int) (a - tempi) + 1, (int) (b - tempi) + 1, *a / 10.0, *b / 10.0, d / 10.0);
    if (d <= 2) {
        printf("Distacco di 2 decimi o meno: serve il fotofinish.\n");
    }

    return 0;
}

/* Confronta tutte le coppie; scrive in *primo e *secondo gli indirizzi dei
 * due tempi più vicini e restituisce la loro distanza. */
int coppia_piu_vicina(const int *tempi, int n, const int **primo, const int **secondo)
{
    const int *p;
    const int *q;
    int minima = distanza(tempi[0], tempi[1]);

    *primo = tempi;
    *secondo = tempi + 1;
    for (p = tempi; p < tempi + n; p++) {
        for (q = p + 1; q < tempi + n; q++) {
            if (distanza(*p, *q) < minima) {
                minima = distanza(*p, *q);
                *primo = p;
                *secondo = q;
            }
        }
    }
    return minima;
}

int distanza(int x, int y)
{
    return x > y ? x - y : y - x;
}
