/*
 * 030-mai-indirizzi-locali.c
 *
 * Quale indirizzo si può restituire
 *
 * Le variabili locali di una funzione (parametri compresi) esistono solo
 * finché la funzione è in esecuzione. Restituirne l'indirizzo è un errore:
 * il chiamante riceve un puntatore a memoria che non appartiene più a
 * nessuna variabile.
 *
 *     double *media_sbagliata(const int *voti, int n)
 *     {
 *         double m;
 *         ...
 *         return &m;               ERRORE: m sparisce al return
 *     }
 *
 * Il compilatore lo segnala con un avviso (per questo la funzione è solo
 * in commento). Le alternative corrette:
 *   1. restituire il VALORE                   double media(...)
 *   2. scrivere in un parametro di USCITA     void media_in(..., double *m)
 *   3. restituire un indirizzo DENTRO dati del chiamante, che sopravvivono
 *      alla funzione                          const int *voto_migliore(...)
 *
 * Esempio: i voti di uno studente in una materia.
 */

#include <stdio.h>

#define VOTI 6

double media(const int *voti, int n);
void media_in(const int *voti, int n, double *risultato);
const int *voto_migliore(const int *voti, int n);

int main(void)
{
    int voti[VOTI] = {6, 7, 5, 8, 7, 9};
    double m;
    const int *migliore;

    /* 1. il valore viene copiato al chiamante: nessun indirizzo in gioco */
    printf("1. media(voti, n)          = %.2f\n", media(voti, VOTI));

    /* 2. la variabile m appartiene al main e sopravvive alla funzione */
    media_in(voti, VOTI, &m);
    printf("2. media_in(voti, n, &m)   -> m = %.2f\n", m);

    /* 3. l'indirizzo restituito punta dentro l'array del main */
    migliore = voto_migliore(voti, VOTI);
    printf("3. voto_migliore(voti, n)  -> %d, il %d-esimo voto\n",
           *migliore, (int) (migliore - voti) + 1);

    return 0;
}

double media(const int *voti, int n)
{
    int i;
    int somma = 0;

    for (i = 0; i < n; i++) {
        somma = somma + voti[i];
    }
    return (double) somma / n;
}

void media_in(const int *voti, int n, double *risultato)
{
    *risultato = media(voti, n);
}

/* L'indirizzo restituito è quello di un elemento di voti, cioè di un
 * array del chiamante: rimane valido dopo il return. */
const int *voto_migliore(const int *voti, int n)
{
    const int *p;
    const int *migliore = voti;

    for (p = voti + 1; p < voti + n; p++) {
        if (*p > *migliore) {
            migliore = p;
        }
    }
    return migliore;
}
