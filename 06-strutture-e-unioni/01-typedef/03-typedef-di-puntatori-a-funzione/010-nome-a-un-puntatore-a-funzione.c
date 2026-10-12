/*
 * 010-nome-a-un-puntatore-a-funzione.c
 *
 * Un nome per il tipo "puntatore a funzione"
 *
 * Nel capitolo 05 un puntatore a funzione si dichiarava così:
 *
 *     double (*calcolo)(double, double);
 *
 * Con typedef si dà un nome al tipo e poi lo si usa come qualsiasi altro:
 *
 *     typedef double (*Operazione)(double, double);
 *
 *     Operazione calcolo = somma;
 *     calcolo(3, 4);
 *
 * La regola è sempre la stessa: si scrive la dichiarazione di una
 * variabile, double (*Operazione)(double, double), e si mette typedef
 * davanti. Operazione è il tipo "puntatore a una funzione che riceve due
 * double e restituisce un double".
 *
 * Il vantaggio si vede soprattutto nei parametri: un prototipo come
 *
 *     double applica(Operazione op, double a, double b);
 *
 * si legge a colpo d'occhio, mentre senza typedef il parametro
 * double (*op)(double, double) è molto più faticoso.
 *
 * Esempio: il conto dei prezzi alla cassa del bar della scuola.
 */

#include <stdio.h>

typedef double (*Operazione)(double, double);

double somma(double a, double b);
double prodotto(double a, double b);
double applica(Operazione op, double a, double b);

int main(void)
{
    /* la stessa variabile senza typedef e con typedef */
    double (*senza_nome)(double, double) = somma;
    Operazione calcolo = somma;

    printf("Senza typedef:  senza_nome(1.20, 0.90) = %.2f\n", senza_nome(1.20, 0.90));
    printf("Con typedef:    calcolo(1.20, 0.90)    = %.2f\n", calcolo(1.20, 0.90));

    /* una variabile Operazione può puntare a qualsiasi funzione con lo
     * stesso prototipo */
    calcolo = prodotto;
    printf("Dopo calcolo = prodotto: calcolo(3, 1.10) = %.2f\n", calcolo(3, 1.10));

    /* il tipo come parametro */
    printf("\napplica(somma, 2.50, 1.20)    = %.2f\n", applica(somma, 2.50, 1.20));
    printf("applica(prodotto, 4, 0.90)    = %.2f\n", applica(prodotto, 4, 0.90));

    printf("\nsizeof(Operazione) = %zu byte: e' un indirizzo\n", sizeof(Operazione));

    return 0;
}

double somma(double a, double b)
{
    return a + b;
}

double prodotto(double a, double b)
{
    return a * b;
}

/* Chiama la funzione ricevuta: il tipo del parametro è Operazione. */
double applica(Operazione op, double a, double b)
{
    return op(a, b);
}
