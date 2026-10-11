/*
 * 050-problema-statistiche-griglia.c
 *
 * Serra didattica: statistiche sulle temperature dei settori
 *
 * La serra dell'istituto agrario è divisa in una griglia di 4 x 5
 * settori, ciascuno con un sensore di temperatura. Il responsabile vuole:
 *   - la media della serra e il settore più caldo (riga e colonna);
 *   - quanti settori superano la soglia di attenzione;
 *   - la media di ogni fila, per decidere quale finestra aprire.
 *
 * Le stesse funzioni lavorano su "un array di double" qualsiasi:
 *   - per tutta la serra ricevono &serra[0][0] e FILE * SETTORI elementi
 *     (la matrice come blocco unico);
 *   - per una fila ricevono serra[f] e SETTORI elementi (una riga).
 * massimo restituisce il puntatore all'elemento più alto; dalla posizione
 * k = p - &serra[0][0] si ricavano fila (k / SETTORI) e settore
 * (k % SETTORI).
 */

#include <stdio.h>

#define FILE_SERRA 4
#define SETTORI    5
#define SOGLIA     28.0

double media(const double *v, int n);
const double *massimo(const double *v, int n);
int conta_oltre(const double *v, int n, double soglia);

int main(void)
{
    double serra[FILE_SERRA][SETTORI] = {
        {24.5, 25.1, 26.0, 26.8, 27.2},
        {25.0, 26.3, 27.9, 28.6, 29.4},
        {24.8, 25.9, 27.1, 28.1, 28.9},
        {23.9, 24.2, 25.0, 25.6, 26.1}
    };
    const double *tutto = &serra[0][0];
    int n = FILE_SERRA * SETTORI;
    const double *caldo = massimo(tutto, n);
    int k = caldo - tutto;
    int f;

    printf("Temperatura media della serra: %.2f gradi\n", media(tutto, n));
    printf("Settore piu' caldo: fila %d, settore %d (%.1f gradi)\n",
           k / SETTORI + 1, k % SETTORI + 1, *caldo);
    printf("Settori oltre %.1f gradi: %d su %d\n\n", SOGLIA, conta_oltre(tutto, n, SOGLIA), n);

    for (f = 0; f < FILE_SERRA; f++) {
        printf("Fila %d: media %.2f, massima %.1f, oltre soglia %d\n", f + 1,
               media(serra[f], SETTORI), *massimo(serra[f], SETTORI),
               conta_oltre(serra[f], SETTORI, SOGLIA));
    }

    return 0;
}

double media(const double *v, int n)
{
    const double *p;
    double somma = 0;

    for (p = v; p < v + n; p++) {
        somma = somma + *p;
    }
    return somma / n;
}

/* Puntatore all'elemento più alto (il primo, a parità). */
const double *massimo(const double *v, int n)
{
    const double *p;
    const double *migliore = v;

    for (p = v + 1; p < v + n; p++) {
        if (*p > *migliore) {
            migliore = p;
        }
    }
    return migliore;
}

int conta_oltre(const double *v, int n, double soglia)
{
    const double *p;
    int conteggio = 0;

    for (p = v; p < v + n; p++) {
        if (*p > soglia) {
            conteggio++;
        }
    }
    return conteggio;
}
