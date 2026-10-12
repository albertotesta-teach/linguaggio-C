/*
 * 070-problema-somma-frazioni.c
 *
 * Laboratorio di cucina: sommare le dosi scritte come frazioni
 *
 * Nelle ricette le dosi sono spesso frazioni: 1/2 tazza di latte più 1/3
 * di tazza per la glassa. Una frazione è una coppia numeratore/denominatore
 * che ha senso solo insieme:
 *
 *     typedef struct {
 *         int num;
 *         int den;
 *     } Frazione;
 *
 *     a/b + c/d = (a*d + c*b) / (b*d)
 *
 * Il risultato si riduce ai minimi termini dividendo numeratore e
 * denominatore per il loro massimo comune divisore (algoritmo di Euclide,
 * su due int). Se il risultato supera l'unità si stampa anche come numero
 * misto: 7/6 = 1 e 1/6.
 *
 * Il programma legge coppie di frazioni nella forma a/b c/d; una riga con
 * 0/0 termina. Un denominatore nullo o negativo, o un numeratore negativo,
 * viene rifiutato.
 */

#include <stdio.h>

typedef struct {
    int num;
    int den;
} Frazione;

int mcd(int a, int b);

int main(void)
{
    Frazione prima = {1, 1};
    Frazione seconda;
    Frazione somma;
    int divisore;

    while (!(prima.num == 0 && prima.den == 0)) {
        printf("Due frazioni (a/b c/d, 0/0 per finire): ");
        if (scanf("%d/%d", &prima.num, &prima.den) != 2) {
            prima.num = 0;
            prima.den = 0;
        }
        if (!(prima.num == 0 && prima.den == 0)) {
            if (scanf("%d/%d", &seconda.num, &seconda.den) != 2) {
                printf("  Seconda frazione mancante.\n");
                prima.num = 0;
                prima.den = 0;
            } else if (prima.den <= 0 || seconda.den <= 0 || prima.num < 0 || seconda.num < 0) {
                printf("  Frazioni non valide.\n");
            } else {
                somma.num = prima.num * seconda.den + seconda.num * prima.den;
                somma.den = prima.den * seconda.den;
                divisore = mcd(somma.num, somma.den);
                somma.num = somma.num / divisore;
                somma.den = somma.den / divisore;
                printf("  %d/%d + %d/%d = %d/%d", prima.num, prima.den, seconda.num, seconda.den,
                       somma.num, somma.den);
                if (somma.num >= somma.den && somma.num % somma.den != 0) {
                    printf("  = %d e %d/%d", somma.num / somma.den, somma.num % somma.den, somma.den);
                } else if (somma.num % somma.den == 0) {
                    printf("  = %d", somma.num / somma.den);
                }
                printf("\n");
            }
        }
    }

    return 0;
}

/* Massimo comune divisore con l'algoritmo di Euclide (b > 0). */
int mcd(int a, int b)
{
    int resto;

    while (b != 0) {
        resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}
