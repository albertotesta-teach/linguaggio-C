/*
 * 020-quanto-costa-crescere.c
 *
 * Quanto costa far crescere un blocco un po' alla volta
 *
 * Quando realloc non può allungare il blocco sul posto, ne alloca uno
 * nuovo e copia tutti gli elementi. Nel caso peggiore ogni realloc copia
 * tutto quello che c'era già.
 *
 * Se un elenco cresce di UN elemento alla volta, per arrivare a n
 * elementi si fanno n realloc e, nel caso peggiore, si copiano
 *
 *     0 + 1 + 2 + ... + (n - 1)  =  n (n - 1) / 2  elementi
 *
 * cioè un numero che cresce come n²: con 10 000 elementi, circa 50
 * milioni di copie. Crescendo a blocchi di 16 elementi le realloc sono
 * 16 volte meno e anche le copie si riducono di circa 16 volte, ma
 * crescono ancora come n².
 *
 * Il programma fa crescere davvero un blocco di int nei due modi,
 * contando le realloc e le copie del caso peggiore (la somma degli
 * elementi presenti a ogni realloc). Quante volte il blocco si sposta
 * davvero dipende dalla libreria, per questo non si stampa.
 *
 * Il sottocapitolo 03-array-dinamici mostra una strategia di crescita
 * con un costo molto più basso.
 */

#include <stdio.h>
#include <stdlib.h>

#define PROVE 3

int cresci(int totale, int passo, long *realloc_fatte, long *copie);

int main(void)
{
    int dimensioni[PROVE] = {100, 1000, 10000};
    long realloc_fatte;
    long copie;
    int k;

    printf("%8s  %-10s %10s %14s\n", "elementi", "crescita", "realloc", "copie (max)");
    for (k = 0; k < PROVE; k++) {
        if (cresci(dimensioni[k], 1, &realloc_fatte, &copie)) {
            printf("%8d  %-10s %10ld %14ld\n", dimensioni[k], "+1", realloc_fatte, copie);
        }
        if (cresci(dimensioni[k], 16, &realloc_fatte, &copie)) {
            printf("%8d  %-10s %10ld %14ld\n", dimensioni[k], "+16", realloc_fatte, copie);
        }
    }

    return 0;
}

/*
 * Riempie un blocco con totale int facendolo crescere di passo elementi
 * alla volta. Restituisce 0 se una realloc fallisce.
 */
int cresci(int totale, int passo, long *realloc_fatte, long *copie)
{
    int *v = NULL;
    int *tmp;
    int capienza = 0;
    int n = 0;
    int ok = 1;

    *realloc_fatte = 0;
    *copie = 0;
    while (n < totale && ok) {
        if (n == capienza) {
            tmp = realloc(v, (capienza + passo) * sizeof *tmp);
            if (tmp == NULL) {
                ok = 0;
            } else {
                v = tmp;
                *copie = *copie + n;
                capienza = capienza + passo;
                (*realloc_fatte)++;
            }
        }
        if (ok) {
            v[n] = n;
            n++;
        }
    }
    free(v);
    return ok;
}
