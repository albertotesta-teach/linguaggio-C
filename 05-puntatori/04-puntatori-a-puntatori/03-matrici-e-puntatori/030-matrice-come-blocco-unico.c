/*
 * 030-matrice-come-blocco-unico.c
 *
 * Scorrere tutta una matrice con un solo puntatore
 *
 * Poiché le righe di una matrice sono consecutive in memoria, quando non
 * interessa la riga di appartenenza la matrice si può scorrere come un
 * unico array di R * C elementi:
 *
 *     int *p = &m[0][0];                 primo elemento
 *     int *fine = &m[0][0] + R * C;      dopo l'ultimo elemento
 *     for (p = &m[0][0]; p < fine; p++) { ... *p ... }
 *
 * Dalla posizione k = p - &m[0][0] si ricavano riga e colonna:
 *     riga = k / C        colonna = k % C
 *
 * Esempio: il parcheggio della scuola, 4 file da 6 posti; ogni cella
 * contiene i minuti di occupazione del posto nella mattinata.
 */

#include <stdio.h>

#define FILE_POSTI 4
#define POSTI      6
#define SOGLIA     240

int main(void)
{
    int minuti[FILE_POSTI][POSTI] = {
        {300, 285, 0, 120, 310, 295},
        {45, 300, 300, 0, 260, 90},
        {0, 0, 150, 300, 305, 300},
        {280, 60, 0, 0, 30, 300}
    };
    const int *p;
    const int *inizio = &minuti[0][0];
    const int *fine = inizio + FILE_POSTI * POSTI;
    const int *massimo = inizio;
    int totale = 0;
    int liberi = 0;
    int lunghi = 0;
    int k;

    for (p = inizio; p < fine; p++) {
        totale = totale + *p;
        if (*p == 0) {
            liberi++;
        }
        if (*p >= SOGLIA) {
            lunghi++;
        }
        if (*p > *massimo) {
            massimo = p;
        }
    }

    k = massimo - inizio;
    printf("Posti: %d, mai occupati: %d, occupati almeno %d minuti: %d\n",
           (int) (fine - inizio), liberi, SOGLIA, lunghi);
    printf("Occupazione media: %.1f minuti\n", (double) totale / (fine - inizio));
    printf("Posto piu' occupato: fila %d, posto %d (%d minuti)\n",
           k / POSTI + 1, k % POSTI + 1, *massimo);

    return 0;
}
