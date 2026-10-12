/*
 * 020-struct-restituita.c
 *
 * Una funzione che restituisce una struct
 *
 * Con return una funzione restituisce un solo valore. Se il valore è una
 * struct, la funzione restituisce in un colpo solo tutti i suoi campi:
 *
 *     Frazione somma(Frazione a, Frazione b);
 *     Frazione semplifica(Frazione f);
 *
 *     Frazione r = semplifica(somma(a, b));
 *
 * È il modo più naturale per un tipo che si comporta come un numero: le
 * operazioni ricevono valori e producono un valore nuovo, senza
 * modificare gli operandi. Le chiamate si possono annidare, come per le
 * funzioni matematiche.
 *
 * Esempio: le dosi di una ricetta scritte come frazioni di tazza.
 */

#include <stdio.h>

typedef struct {
    int num;
    int den;
} Frazione;

Frazione crea(int num, int den);
Frazione somma(Frazione a, Frazione b);
Frazione prodotto(Frazione a, Frazione b);
Frazione semplifica(Frazione f);
int mcd(int a, int b);
void stampa(Frazione f);

int main(void)
{
    Frazione latte = crea(1, 2);
    Frazione panna = crea(1, 3);
    Frazione totale;
    Frazione doppia_dose;

    totale = semplifica(somma(latte, panna));
    doppia_dose = semplifica(prodotto(totale, crea(2, 1)));

    printf("Latte ");
    stampa(latte);
    printf(" + panna ");
    stampa(panna);
    printf(" = ");
    stampa(totale);
    printf(" di tazza\nDose doppia: ");
    stampa(doppia_dose);
    printf(" di tazza\n");

    return 0;
}

Frazione crea(int num, int den)
{
    Frazione f;

    f.num = num;
    f.den = den;
    return f;
}

Frazione somma(Frazione a, Frazione b)
{
    return crea(a.num * b.den + b.num * a.den, a.den * b.den);
}

Frazione prodotto(Frazione a, Frazione b)
{
    return crea(a.num * b.num, a.den * b.den);
}

/* Divide numeratore e denominatore per il loro MCD. */
Frazione semplifica(Frazione f)
{
    int d = mcd(f.num, f.den);

    return crea(f.num / d, f.den / d);
}

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

void stampa(Frazione f)
{
    printf("%d/%d", f.num, f.den);
}
