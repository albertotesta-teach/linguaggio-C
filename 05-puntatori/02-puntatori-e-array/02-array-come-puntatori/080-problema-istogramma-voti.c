/*
 * 080-problema-istogramma-voti.c
 *
 * Esiti di una verifica: istogramma per fasce di voto
 *
 * Il docente vuole vedere come si distribuiscono i voti di una verifica
 * in cinque fasce: insufficiente (sotto 6), sufficiente (6), discreto (7),
 * buono (8), ottimo (9 e 10). Per ogni fascia il programma stampa il numero
 * di studenti, la percentuale e una barra di asterischi, poi indica la
 * fascia più numerosa.
 *
 * La funzione conta_fasce riceve l'array dei conteggi come int *: azzera
 * i contatori e incrementa quello giusto con *(conteggi + f), modificando
 * direttamente l'array del chiamante.
 */

#include <stdio.h>

#define STUDENTI 24
#define FASCE    5
#define LUNG     16

int indice_fascia(int voto);
void conta_fasce(const int *voti, int n, int *conteggi);
int posizione_massimo(const int *v, int n);

int main(void)
{
    int voti[STUDENTI] = {6, 7, 5, 8, 4, 9, 6, 7, 7, 6, 10, 5,
                          6, 8, 7, 3, 6, 7, 8, 5, 9, 6, 7, 6};
    char nomi[FASCE][LUNG] = {"insufficiente", "sufficiente", "discreto",
                              "buono", "ottimo"};
    int conteggi[FASCE];
    int f;
    int k;
    int prevalente;

    conta_fasce(voti, STUDENTI, conteggi);

    printf("=== ESITI DELLA VERIFICA (%d studenti) ===\n", STUDENTI);
    for (f = 0; f < FASCE; f++) {
        printf("  %-14s %2d  %3d%%  ", nomi[f], conteggi[f], conteggi[f] * 100 / STUDENTI);
        for (k = 0; k < conteggi[f]; k++) {
            printf("*");
        }
        printf("\n");
    }

    prevalente = posizione_massimo(conteggi, FASCE);
    printf("\nFascia piu' numerosa: %s (%d studenti)\n", nomi[prevalente], conteggi[prevalente]);
    printf("Sufficienti o meglio: %d su %d\n", STUDENTI - conteggi[0], STUDENTI);

    return 0;
}

/* Fascia del voto: 0 insufficiente, 1-3 per 6, 7, 8, 4 per 9 e 10. */
int indice_fascia(int voto)
{
    int f;

    if (voto < 6) {
        f = 0;
    } else if (voto >= 9) {
        f = 4;
    } else {
        f = voto - 5;
    }
    return f;
}

/* Azzera i FASCE contatori e conta i voti di ogni fascia. */
void conta_fasce(const int *voti, int n, int *conteggi)
{
    const int *p;
    int f;

    for (f = 0; f < FASCE; f++) {
        *(conteggi + f) = 0;
    }
    for (p = voti; p < voti + n; p++) {
        f = indice_fascia(*p);
        *(conteggi + f) = *(conteggi + f) + 1;
    }
}

/* Posizione (da 0) dell'elemento maggiore. */
int posizione_massimo(const int *v, int n)
{
    const int *p;
    const int *migliore = v;

    for (p = v + 1; p < v + n; p++) {
        if (*p > *migliore) {
            migliore = p;
        }
    }
    return migliore - v;
}
