/*
 * 020-crescita-a-raddoppio.c
 *
 * Quando il vettore è pieno, la capacità raddoppia
 *
 * Crescere di un posto alla volta costa, nel caso peggiore, circa n²/2
 * copie (02-calloc-e-realloc). Se invece quando il vettore è pieno la
 * capacità RADDOPPIA:
 *
 *     if (v->n == v->capacita) {
 *         nuova = 2 * v->capacita;
 *         tmp = realloc(v->dati, nuova * sizeof *tmp);
 *         ...
 *     }
 *
 * le realloc diventano pochissime (circa log2 n) e le copie del caso
 * peggiore sono meno di 2n in tutto: ogni raddoppio copia la capacità
 * vecchia, e 16 + 32 + ... + c < 2c. In media ogni aggiunta costa meno di
 * due copie, qualunque sia n.
 *
 * Il prezzo è lo spazio: dopo un raddoppio fino a metà dei posti può
 * restare vuota.
 *
 * Il programma aggiunge 1 000, 10 000 e 100 000 elementi con
 * crescita +16 e con raddoppio (capacità iniziale 16), e confronta
 * realloc e copie del caso peggiore.
 */

#include <stdio.h>
#include <stdlib.h>

#define PROVE 3
#define INIZIALE 16

int riempi(int totale, int raddoppio, long *realloc_fatte, long *copie);

int main(void)
{
    int dimensioni[PROVE] = {1000, 10000, 100000};
    long realloc_fatte;
    long copie;
    int k;

    printf("%9s  %-10s %10s %14s\n", "elementi", "crescita", "realloc", "copie (max)");
    for (k = 0; k < PROVE; k++) {
        if (riempi(dimensioni[k], 0, &realloc_fatte, &copie)) {
            printf("%9d  %-10s %10ld %14ld\n", dimensioni[k], "+16", realloc_fatte, copie);
        }
        if (riempi(dimensioni[k], 1, &realloc_fatte, &copie)) {
            printf("%9d  %-10s %10ld %14ld\n", dimensioni[k], "x2", realloc_fatte, copie);
        }
    }

    return 0;
}

/*
 * Aggiunge totale elementi a un vettore che parte da INIZIALE posti e
 * cresce di INIZIALE posti (raddoppio = 0) o raddoppia (raddoppio = 1).
 * Restituisce 0 se una realloc fallisce.
 */
int riempi(int totale, int raddoppio, long *realloc_fatte, long *copie)
{
    int *dati = malloc(INIZIALE * sizeof *dati);
    int *tmp;
    int capacita = INIZIALE;
    int nuova;
    int n = 0;
    int ok = dati != NULL;

    *realloc_fatte = 0;
    *copie = 0;
    while (ok && n < totale) {
        if (n == capacita) {
            nuova = raddoppio ? 2 * capacita : capacita + INIZIALE;
            tmp = realloc(dati, nuova * sizeof *tmp);
            if (tmp == NULL) {
                ok = 0;
            } else {
                dati = tmp;
                capacita = nuova;
                *copie = *copie + n;
                (*realloc_fatte)++;
            }
        }
        if (ok) {
            dati[n] = n;
            n++;
        }
    }
    free(dati);
    return ok;
}
