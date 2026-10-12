/*
 * 020-funzione-che-restituisce-un-operazione.c
 *
 * Una funzione che restituisce un puntatore a funzione, con e senza typedef
 *
 * Nella calcolatrice del capitolo 05 (05-puntatori/03-puntatori-e-funzioni)
 * la funzione che sceglie l'operazione aveva questo prototipo:
 *
 *     double (*scegli_operazione(char simbolo))(double, double);
 *
 * Il nome della funzione e i suoi parametri sono "chiusi" dentro il tipo
 * restituito: si legge dall'interno verso l'esterno, ed è facile
 * sbagliare. Con typedef lo stesso prototipo diventa:
 *
 *     typedef double (*Operazione)(double, double);
 *     Operazione scegli(char simbolo);
 *
 * cioè "scegli riceve un char e restituisce un'Operazione". Il programma
 * contiene entrambe le versioni, che fanno la stessa cosa: se il simbolo
 * non corrisponde a nessuna operazione restituiscono NULL.
 */

#include <stdio.h>

typedef double (*Operazione)(double, double);

double somma(double a, double b);
double differenza(double a, double b);
double prodotto(double a, double b);
double quoziente(double a, double b);

Operazione scegli(char simbolo);
double (*scegli_senza_typedef(char simbolo))(double, double);

int main(void)
{
    const char simboli[] = "+-*/%";
    double a = 12;
    double b = 4;
    Operazione op;
    int i;

    for (i = 0; simboli[i] != '\0'; i++) {
        op = scegli(simboli[i]);
        if (op == NULL) {
            printf("  %.0f %c %.0f   operazione non disponibile\n", a, simboli[i], b);
        } else {
            printf("  %.0f %c %.0f = %g   (senza typedef: %g)\n", a, simboli[i], b, op(a, b),
                   scegli_senza_typedef(simboli[i])(a, b));
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

/* Con typedef: il tipo restituito si legge per primo. */
Operazione scegli(char simbolo)
{
    Operazione scelta = NULL;

    if (simbolo == '+') {
        scelta = somma;
    } else if (simbolo == '-') {
        scelta = differenza;
    } else if (simbolo == '*') {
        scelta = prodotto;
    } else if (simbolo == '/') {
        scelta = quoziente;
    }
    return scelta;
}

/* Senza typedef: stessa funzione, prototipo da leggere dall'interno. */
double (*scegli_senza_typedef(char simbolo))(double, double)
{
    double (*scelta)(double, double) = NULL;

    if (simbolo == '+') {
        scelta = somma;
    } else if (simbolo == '-') {
        scelta = differenza;
    } else if (simbolo == '*') {
        scelta = prodotto;
    } else if (simbolo == '/') {
        scelta = quoziente;
    }
    return scelta;
}
