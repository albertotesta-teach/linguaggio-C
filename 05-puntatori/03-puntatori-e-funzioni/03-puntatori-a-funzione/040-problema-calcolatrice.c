/*
 * 040-problema-calcolatrice.c
 *
 * Calcolatrice da riga di comando
 *
 * Per il laboratorio di fisica serve una piccola calcolatrice che legge
 * espressioni nel formato "numero operatore numero" (ad esempio 12.5 * 4)
 * e stampa il risultato. Operatori: + - * / ^ (potenza intera).
 *
 * Invece di una catena di if che esegue i calcoli, il programma usa
 * scegli_operazione, che dato il carattere dell'operatore restituisce il
 * PUNTATORE alla funzione corrispondente (NULL se l'operatore non esiste).
 * Il calcolo avviene poi con una sola chiamata: operazione(a, b).
 * La divisione per zero si controlla prima della chiamata.
 *
 * Il programma legge un'espressione per riga; un input non valido (ad
 * esempio "q") termina.
 */

#include <stdio.h>

double somma(double a, double b);
double sottrai(double a, double b);
double moltiplica(double a, double b);
double dividi(double a, double b);
double potenza(double a, double b);
double (*scegli_operazione(char simbolo))(double, double);

int main(void)
{
    double a;
    double b;
    char simbolo;
    double (*operazione)(double, double);

    printf("=== CALCOLATRICE (q per finire) ===\n");
    printf("> ");
    while (scanf("%lf %c %lf", &a, &simbolo, &b) == 3) {
        operazione = scegli_operazione(simbolo);
        if (operazione == NULL) {
            printf("  Operatore '%c' sconosciuto.\n", simbolo);
        } else if (operazione == dividi && b == 0) {
            printf("  Divisione per zero.\n");
        } else {
            printf("  %g %c %g = %g\n", a, simbolo, b, operazione(a, b));
        }
        printf("> ");
    }
    printf("\n");

    return 0;
}

/* Restituisce l'indirizzo della funzione per l'operatore dato, NULL se
 * l'operatore non è previsto. La dichiarazione si legge così:
 * scegli_operazione è una funzione (char) che restituisce un puntatore a
 * una funzione (double, double) che restituisce double. */
double (*scegli_operazione(char simbolo))(double, double)
{
    double (*scelta)(double, double) = NULL;

    if (simbolo == '+') {
        scelta = somma;
    } else if (simbolo == '-') {
        scelta = sottrai;
    } else if (simbolo == '*') {
        scelta = moltiplica;
    } else if (simbolo == '/') {
        scelta = dividi;
    } else if (simbolo == '^') {
        scelta = potenza;
    }
    return scelta;
}

double somma(double a, double b)
{
    return a + b;
}

double sottrai(double a, double b)
{
    return a - b;
}

double moltiplica(double a, double b)
{
    return a * b;
}

double dividi(double a, double b)
{
    return a / b;
}

/* a elevato alla parte intera di b (b >= 0). */
double potenza(double a, double b)
{
    double risultato = 1;
    int i;

    for (i = 0; i < (int) b; i++) {
        risultato = risultato * a;
    }
    return risultato;
}
