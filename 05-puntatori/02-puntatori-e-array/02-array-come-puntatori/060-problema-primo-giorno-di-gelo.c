/*
 * 060-problema-primo-giorno-di-gelo.c
 *
 * Temperature minime di novembre: il primo giorno di gelo
 *
 * Un'azienda agricola conserva le temperature minime dei 30 giorni di
 * novembre. Per decidere quando proteggere le piante l'agronomo chiede,
 * per un periodo scelto (dal giorno a al giorno b), il primo giorno con
 * temperatura sotto zero, quanti giorni di gelo ci sono stati e la minima
 * più bassa.
 *
 * Il periodo si passa alle funzioni come SOTTOARRAY:
 *     inizio = minime + a - 1     (il giorno a è l'elemento di indice a - 1)
 *     n      = b - a + 1
 * Le funzioni restituiscono posizioni relative al periodo: il chiamante le
 * riporta al giorno del mese aggiungendo a.
 *
 * Il programma legge coppie "a b"; con "0 0" termina.
 */

#include <stdio.h>

#define GIORNI 30

int primo_sotto_zero(const int *t, int n);
int conta_sotto_zero(const int *t, int n);
int minima(const int *t, int n);

int main(void)
{
    int minime[GIORNI] = {8, 7, 9, 6, 5, 4, 3, 2, 1, 0,
                          -1, 2, 3, 1, -2, -3, 0, 1, 4, 5,
                          3, 2, -1, -4, -5, -2, 0, 1, -1, -3};
    int a = 1;
    int b = 1;
    int primo;
    const int *inizio;
    int n;

    printf("=== GELATE DI NOVEMBRE ===\n");
    while (a != 0) {
        printf("\nPeriodo, dal giorno al giorno (0 0 per finire): ");
        if (scanf("%d %d", &a, &b) != 2) {
            a = 0;
        }

        if (a != 0) {
            if (a < 1 || b > GIORNI || a > b) {
                printf("  Periodo non valido: servono 1 <= a <= b <= %d.\n", GIORNI);
            } else {
                inizio = minime + a - 1;
                n = b - a + 1;
                primo = primo_sotto_zero(inizio, n);

                printf("  Giorni %d-%d (%d giorni), minima piu' bassa %d gradi\n",
                       a, b, n, minima(inizio, n));
                if (primo == -1) {
                    printf("  Nessun giorno di gelo.\n");
                } else {
                    printf("  Primo gelo: giorno %d (%d gradi), giorni di gelo: %d\n",
                           a + primo, inizio[primo], conta_sotto_zero(inizio, n));
                }
            }
        }
    }

    return 0;
}

/* Posizione (da 0) della prima temperatura negativa, -1 se non c'è. */
int primo_sotto_zero(const int *t, int n)
{
    const int *p = t;

    while (p < t + n && *p >= 0) {
        p++;
    }
    return p < t + n ? p - t : -1;
}

/* Numero di temperature negative. */
int conta_sotto_zero(const int *t, int n)
{
    const int *p;
    int conteggio = 0;

    for (p = t; p < t + n; p++) {
        if (*p < 0) {
            conteggio++;
        }
    }
    return conteggio;
}

/* Temperatura più bassa. */
int minima(const int *t, int n)
{
    const int *p;
    int min = *t;

    for (p = t + 1; p < t + n; p++) {
        if (*p < min) {
            min = *p;
        }
    }
    return min;
}
