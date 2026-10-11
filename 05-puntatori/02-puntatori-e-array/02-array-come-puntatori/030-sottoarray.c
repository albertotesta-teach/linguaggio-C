/*
 * 030-sottoarray.c
 *
 * Passare a una funzione solo una parte di un array
 *
 * Poiché una funzione riceve un indirizzo e un numero di elementi, le si
 * può passare una PARTE dell'array: basta indicare da dove partire.
 *
 *     somma(v, 12)        tutto l'array
 *     somma(v + 3, 3)     i 3 elementi che iniziano da v[3]
 *
 * Dentro la funzione il sottoarray si usa con gli indici da 0: v[0] della
 * funzione è v[3] del chiamante.
 *
 * Un altro modo di indicare un intervallo è con due puntatori, inizio
 * (incluso) e fine (escluso): stampa(v + 6, v + 12).
 *
 * Esempio: gli ingressi mensili in una palestra comunale durante l'anno.
 */

#include <stdio.h>

#define MESI 12
#define LUNG 4

int somma(const int *v, int n);
void stampa(const int *inizio, const int *fine, int primo_mese, const char nomi[][LUNG]);

int main(void)
{
    int ingressi[MESI] = {820, 910, 760, 640, 520, 380,
                          210, 150, 590, 780, 850, 690};
    char nomi[MESI][LUNG] = {"gen", "feb", "mar", "apr", "mag", "giu",
                             "lug", "ago", "set", "ott", "nov", "dic"};
    int t;

    printf("Ingressi nell'anno:   %5d\n", somma(ingressi, MESI));

    printf("\n=== TRIMESTRI: somma(ingressi + 3 * t, 3) ===\n");
    for (t = 0; t < 4; t++) {
        printf("  trimestre %d (%s-%s): %5d\n", t + 1, nomi[3 * t], nomi[3 * t + 2],
               somma(ingressi + 3 * t, 3));
    }

    printf("\nEstate (giu-ago): somma(ingressi + 5, 3) = %d\n", somma(ingressi + 5, 3));

    printf("\n=== SECONDO SEMESTRE: stampa(ingressi + 6, ingressi + 12, ...) ===\n");
    stampa(ingressi + 6, ingressi + MESI, 6, nomi);

    return 0;
}

/* Somma n elementi a partire dall'indirizzo v. */
int somma(const int *v, int n)
{
    int i;
    int totale = 0;

    for (i = 0; i < n; i++) {
        totale = totale + v[i];
    }
    return totale;
}

/* Stampa gli elementi da inizio (incluso) a fine (escluso). La funzione
 * vede solo l'intervallo: il numero del primo mese serve per i nomi. */
void stampa(const int *inizio, const int *fine, int primo_mese, const char nomi[][LUNG])
{
    const int *p;
    int mese = primo_mese;

    for (p = inizio; p < fine; p++) {
        printf("  %s %4d\n", nomi[mese], *p);
        mese++;
    }
}
