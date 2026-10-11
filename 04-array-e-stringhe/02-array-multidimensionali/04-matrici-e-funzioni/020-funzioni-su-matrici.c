/*
 * 020-funzioni-su-matrici.c
 *
 * Funzioni che calcolano un risultato a partire da una matrice
 *
 * Ogni funzione ha un compito solo e non stampa nulla: riceve la matrice
 * (in sola lettura, const) e restituisce un valore. Il main chiama le
 * funzioni e presenta i risultati.
 *
 *   somma_riga(m, r)          totale della riga r
 *   somma_colonna(m, n, c)    totale della colonna c (n = numero di righe)
 *   conta_sopra(m, n, soglia) numero di celle maggiori della soglia
 *   cerca_massimo(m, n, &r, &c)
 *                             restituisce il massimo e, tramite due
 *                             parametri OUT (capitolo 03), la sua posizione
 *
 * Esempio: incassi in euro di 3 casse di un supermercato in 5 fasce orarie.
 */

#include <stdio.h>

#define CASSE 3
#define FASCE 5

int somma_riga(const int m[][FASCE], int r);
int somma_colonna(const int m[][FASCE], int n, int c);
int conta_sopra(const int m[][FASCE], int n, int soglia);
int cerca_massimo(const int m[][FASCE], int n, int *riga_max, int *colonna_max);

int main(void)
{
    int incassi[CASSE][FASCE] = {
        {420, 380, 610, 550, 720},
        {300, 450, 580, 690, 640},
        {150, 220, 400, 380, 510}
    };
    int r;
    int c;
    int massimo;
    int r_max;
    int c_max;

    printf("=== INCASSI PER CASSA E FASCIA ORARIA (euro) ===\n");
    printf("          8-10 10-12 12-14 14-16 16-18   Totale\n");
    for (r = 0; r < CASSE; r++) {
        printf("  Cassa %d", r + 1);
        for (c = 0; c < FASCE; c++) {
            printf("%6d", incassi[r][c]);
        }
        printf("%9d\n", somma_riga(incassi, r));
    }
    printf("  Totale ");
    for (c = 0; c < FASCE; c++) {
        printf("%6d", somma_colonna(incassi, CASSE, c));
    }
    printf("\n\n");

    massimo = cerca_massimo(incassi, CASSE, &r_max, &c_max);
    printf("Incasso massimo: %d euro (cassa %d, fascia %d)\n",
           massimo, r_max + 1, c_max + 1);
    printf("Fasce con incasso oltre 500 euro: %d su %d\n",
           conta_sopra(incassi, CASSE, 500), CASSE * FASCE);

    return 0;
}

/* Restituisce la somma degli elementi della riga r. */
int somma_riga(const int m[][FASCE], int r)
{
    int c;
    int somma = 0;

    for (c = 0; c < FASCE; c++) {
        somma = somma + m[r][c];
    }
    return somma;
}

/* Restituisce la somma degli elementi della colonna c, sulle prime n righe. */
int somma_colonna(const int m[][FASCE], int n, int c)
{
    int r;
    int somma = 0;

    for (r = 0; r < n; r++) {
        somma = somma + m[r][c];
    }
    return somma;
}

/* Restituisce quante celle hanno un valore maggiore di soglia. */
int conta_sopra(const int m[][FASCE], int n, int soglia)
{
    int r;
    int c;
    int conteggio = 0;

    for (r = 0; r < n; r++) {
        for (c = 0; c < FASCE; c++) {
            if (m[r][c] > soglia) {
                conteggio++;
            }
        }
    }
    return conteggio;
}

/* Restituisce il valore massimo e ne scrive la posizione in *riga_max e
 * *colonna_max. Un solo return: la posizione esce dai parametri OUT. */
int cerca_massimo(const int m[][FASCE], int n, int *riga_max, int *colonna_max)
{
    int r;
    int c;

    *riga_max = 0;
    *colonna_max = 0;
    for (r = 0; r < n; r++) {
        for (c = 0; c < FASCE; c++) {
            if (m[r][c] > m[*riga_max][*colonna_max]) {
                *riga_max = r;
                *colonna_max = c;
            }
        }
    }
    return m[*riga_max][*colonna_max];
}
