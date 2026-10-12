/*
 * 080-problema-impedenze-circuito.c
 *
 * Laboratorio di elettrotecnica: impedenze di un circuito RLC
 *
 * In corrente alternata resistori, induttori e condensatori hanno
 * un'impedenza, un numero complesso Z = R + jX:
 *   - resistore:      Z = R
 *   - induttore:      Z = j * 2*pi*f*L
 *   - condensatore:   Z = -j / (2*pi*f*C)
 *
 *     typedef struct {
 *         double re;               parte reale (resistenza)
 *         double im;               parte immaginaria (reattanza)
 *     } Complesso;
 *
 * Le operazioni ricevono e restituiscono Complesso per valore:
 *     Complesso somma(Complesso a, Complesso b);       serie
 *     Complesso prodotto(Complesso a, Complesso b);
 *     Complesso quoziente(Complesso a, Complesso b);
 *     Complesso parallelo(Complesso a, Complesso b);   a*b / (a+b)
 *     double modulo(Complesso z);
 *     double fase(Complesso z);                        in gradi
 *
 * Il programma legge R, L e C e la frequenza, calcola l'impedenza del
 * circuito serie RLC e del parallelo tra R e il condensatore, e la
 * corrente con una tensione di 230 V.
 */

#include <stdio.h>
#include <math.h>

#define PI      3.14159265358979
#define TENSIONE 230.0

typedef struct {
    double re;
    double im;
} Complesso;

Complesso crea(double re, double im);
Complesso somma(Complesso a, Complesso b);
Complesso prodotto(Complesso a, Complesso b);
Complesso quoziente(Complesso a, Complesso b);
Complesso parallelo(Complesso a, Complesso b);
double modulo(Complesso z);
double fase(Complesso z);
void stampa(const char *nome, Complesso z);

int main(void)
{
    double r;
    double l;
    double c;
    double f;
    Complesso zr;
    Complesso zl;
    Complesso zc;
    Complesso serie;

    printf("R (ohm), L (H), C (F), frequenza (Hz): ");
    if (scanf("%lf %lf %lf %lf", &r, &l, &c, &f) != 4 || r <= 0 || l <= 0 || c <= 0 || f <= 0) {
        printf("Valori non validi.\n");
    } else {
        zr = crea(r, 0);
        zl = crea(0, 2 * PI * f * l);
        zc = crea(0, -1 / (2 * PI * f * c));
        stampa("Resistore", zr);
        stampa("Induttore", zl);
        stampa("Condensatore", zc);
        serie = somma(somma(zr, zl), zc);
        stampa("Serie RLC", serie);
        printf("  corrente serie: %.3f A\n", TENSIONE / modulo(serie));
        stampa("R parallelo C", parallelo(zr, zc));
    }

    return 0;
}

Complesso crea(double re, double im)
{
    Complesso z;

    z.re = re;
    z.im = im;
    return z;
}

Complesso somma(Complesso a, Complesso b)
{
    return crea(a.re + b.re, a.im + b.im);
}

/* (a + jb)(c + jd) = (ac - bd) + j(ad + bc) */
Complesso prodotto(Complesso a, Complesso b)
{
    return crea(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
}

/* Moltiplica per il coniugato del denominatore. */
Complesso quoziente(Complesso a, Complesso b)
{
    double d = b.re * b.re + b.im * b.im;
    Complesso n = prodotto(a, crea(b.re, -b.im));

    return crea(n.re / d, n.im / d);
}

Complesso parallelo(Complesso a, Complesso b)
{
    return quoziente(prodotto(a, b), somma(a, b));
}

double modulo(Complesso z)
{
    return sqrt(z.re * z.re + z.im * z.im);
}

double fase(Complesso z)
{
    return atan2(z.im, z.re) * 180 / PI;
}

void stampa(const char *nome, Complesso z)
{
    printf("  %-14s Z = %9.2f %c j%9.2f   |Z| = %9.2f ohm   fase %7.2f gradi\n", nome, z.re,
           z.im < 0 ? '-' : '+', fabs(z.im), modulo(z), fase(z));
}
