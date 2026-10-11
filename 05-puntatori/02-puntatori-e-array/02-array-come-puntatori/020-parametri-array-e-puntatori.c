/*
 * 020-parametri-array-e-puntatori.c
 *
 * Un array passato a una funzione arriva come puntatore
 *
 * Quando si chiama f(v), alla funzione non arriva una copia dell'array ma
 * l'INDIRIZZO del primo elemento. Per questo, come parametro, le due
 * scritture sono equivalenti:
 *
 *     int totale(const int v[], int n)
 *     int totale(const int *v, int n)
 *
 * Conseguenze:
 *   - la funzione può modificare l'array del chiamante (se non è const);
 *   - la funzione non sa quanti elementi ci sono: n va passato a parte;
 *     sizeof del parametro dà la dimensione di un indirizzo, non
 *     dell'array (con la scrittura v[] il compilatore lo segnala).
 *
 * Esempio: i millimetri di pioggia di una settimana registrati da una
 * stazione meteo; -1 indica una misura mancante.
 */

#include <stdio.h>

#define GIORNI 7
#define MANCANTE (-1)

int totale(const int v[], int n);
int massimo(const int *v, int n);
int correggi_mancanti(int *v, int n);

int main(void)
{
    int pioggia[GIORNI] = {0, 12, MANCANTE, 4, 27, MANCANTE, 3};
    int corretti;

    printf("Indirizzo dell'array nel main:  %p\n", (void *) pioggia);
    printf("Dimensione dell'array nel main: %zu byte\n\n", sizeof(pioggia));

    corretti = correggi_mancanti(pioggia, GIORNI);
    printf("\nMisure mancanti sostituite con 0: %d\n", corretti);
    printf("Pioggia totale: %d mm\n", totale(pioggia, GIORNI));
    printf("Giorno piu' piovoso: %d mm\n", massimo(pioggia, GIORNI));

    return 0;
}

/* Parametro scritto come array: v[i]. */
int totale(const int v[], int n)
{
    int i;
    int somma = 0;

    for (i = 0; i < n; i++) {
        somma = somma + v[i];
    }
    return somma;
}

/* Parametro scritto come puntatore: si può usare sia *(v + i) sia v[i]. */
int massimo(const int *v, int n)
{
    int i;
    int max = *v;

    for (i = 1; i < n; i++) {
        if (*(v + i) > max) {
            max = *(v + i);
        }
    }
    return max;
}

/* Sostituisce i valori MANCANTE con 0 nell'array del chiamante e
 * restituisce quante sostituzioni ha fatto. */
int correggi_mancanti(int *v, int n)
{
    int *p;
    int sostituiti = 0;

    printf("Indirizzo ricevuto dalla funzione: %p\n", (void *) v);
    printf("sizeof(v) nella funzione:          %zu byte (solo l'indirizzo)\n", sizeof(v));

    for (p = v; p < v + n; p++) {
        if (*p == MANCANTE) {
            *p = 0;
            sostituiti++;
        }
    }
    return sostituiti;
}
