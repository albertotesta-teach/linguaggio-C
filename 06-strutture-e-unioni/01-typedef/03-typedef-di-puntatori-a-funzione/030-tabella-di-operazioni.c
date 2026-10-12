/*
 * 030-tabella-di-operazioni.c
 *
 * Un array di puntatori a funzione dichiarato con typedef
 *
 * Nel capitolo 05 (04-puntatori-a-puntatori/02-array-di-puntatori) la
 * tabella dei comandi del robot si dichiarava così:
 *
 *     void (*comandi[4])(int *x, int *y, int *dir) = {...};
 *
 * Con un nome per il tipo puntatore a funzione, un array di funzioni si
 * dichiara come un array di int:
 *
 *     typedef double (*Operazione)(double, double);
 *     Operazione tabella[4] = {somma, differenza, prodotto, quoziente};
 *
 * Il simbolo dell'operazione si cerca con strchr nella stringa simboli,
 * che contiene + - * / nello stesso ordine della tabella: la posizione
 * del simbolo è l'indice della funzione da chiamare.
 *
 * Esempio: il quaderno dei conti del tesoriere di classe, con una serie di
 * calcoli scritti come primo numero, simbolo, secondo numero.
 */

#include <stdio.h>
#include <string.h>

#define OPERAZIONI 4
#define CALCOLI    5

typedef double (*Operazione)(double, double);

double somma(double a, double b);
double differenza(double a, double b);
double prodotto(double a, double b);
double quoziente(double a, double b);

int main(void)
{
    Operazione tabella[OPERAZIONI] = {somma, differenza, prodotto, quoziente};
    const char simboli[] = "+-*/";
    double primi[CALCOLI] = {120, 85.5, 24, 300, 18};
    char operatori[CALCOLI] = {'+', '-', '*', '/', '^'};
    double secondi[CALCOLI] = {35, 12.5, 3.5, 25, 2};
    const char *trovato;
    int c;

    printf("La tabella contiene %d operazioni, %zu byte (%d indirizzi)\n\n",
           OPERAZIONI, sizeof(tabella), OPERAZIONI);
    for (c = 0; c < CALCOLI; c++) {
        trovato = strchr(simboli, operatori[c]);
        if (trovato == NULL) {
            printf("  %7.2f %c %6.2f   simbolo sconosciuto\n", primi[c], operatori[c], secondi[c]);
        } else {
            printf("  %7.2f %c %6.2f = %8.2f   (tabella[%d])\n", primi[c], operatori[c], secondi[c],
                   tabella[trovato - simboli](primi[c], secondi[c]), (int) (trovato - simboli));
        }
    }

    return 0;
}

double somma(double a, double b)
{
    return a + b;
}

double differenza(double a, double b)
{
    return a - b;
}

double prodotto(double a, double b)
{
    return a * b;
}

double quoziente(double a, double b)
{
    return a / b;
}
