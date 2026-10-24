/*
 * 040-problema-calcolatrice-frazioni.c
 *
 * Calcolatrice di frazioni per il ripasso di matematica
 *
 * La calcolatrice legge espressioni con due frazioni e un operatore:
 *     3/4 + 1/6        3/4 - 1/6        3/4 * 2/9        3/4 : 1/2
 * e stampa il risultato ridotto ai minimi termini, con il segno davanti.
 *
 * Ogni operazione è una funzione che riceve due Frazione PER VALORE e
 * RESTITUISCE una Frazione nuova; nessuna modifica gli operandi:
 *
 *     Frazione somma(Frazione a, Frazione b);
 *     Frazione differenza(Frazione a, Frazione b);
 *     Frazione prodotto(Frazione a, Frazione b);
 *     Frazione quoziente(Frazione a, Frazione b);
 *     Frazione normalizza(Frazione f);     denominatore positivo, minimi termini
 *
 * Un denominatore nullo, o una divisione per zero, viene segnalato.
 * Una riga con 0/0 termina.
 */

#include <stdio.h>

typedef struct {
    int num;
    int den;
} Frazione;

Frazione crea(int num, int den);
Frazione somma(Frazione a, Frazione b);
Frazione differenza(Frazione a, Frazione b);
Frazione prodotto(Frazione a, Frazione b);
Frazione quoziente(Frazione a, Frazione b);
Frazione normalizza(Frazione f);
int mcd(int a, int b);
void stampa(Frazione f);
void svuota_riga(void);

int main(void)
{
    Frazione a = {1, 1};
    Frazione b;
    Frazione risultato;
    char operatore;
    int continua = 1;
    int letti;

    while (continua) {
        printf("Espressione (a/b op c/d, 0/0 per finire): ");
        letti = scanf("%d/%d", &a.num, &a.den);
        if (letti == EOF) {
            continua = 0;               /* input terminato: come 0/0 */
        } else if (letti != 2) {
            svuota_riga();              /* non e' nella forma a/b */
            printf("  Espressione non valida.\n");
        } else if (a.num == 0 && a.den == 0) {
            continua = 0;
        } else if ((letti = scanf(" %c %d/%d", &operatore, &b.num, &b.den)) == EOF) {
            printf("  Espressione incompleta.\n");
            continua = 0;
        } else if (letti != 3) {
            svuota_riga();              /* operatore o seconda frazione errati */
            printf("  Espressione non valida.\n");
        } else if (a.den == 0 || b.den == 0) {
            printf("  Denominatore nullo.\n");
        } else if (operatore == ':' && b.num == 0) {
            printf("  Divisione per zero.\n");
        } else if (operatore != '+' && operatore != '-' && operatore != '*' && operatore != ':') {
            printf("  Operatore %c non previsto.\n", operatore);
        } else {
            if (operatore == '+') {
                risultato = somma(a, b);
            } else if (operatore == '-') {
                risultato = differenza(a, b);
            } else if (operatore == '*') {
                risultato = prodotto(a, b);
            } else {
                risultato = quoziente(a, b);
            }
            printf("  ");
            stampa(a);
            printf(" %c ", operatore);
            stampa(b);
            printf(" = ");
            stampa(normalizza(risultato));
            printf("\n");
        }
    }

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

Frazione differenza(Frazione a, Frazione b)
{
    return crea(a.num * b.den - b.num * a.den, a.den * b.den);
}

Frazione prodotto(Frazione a, Frazione b)
{
    return crea(a.num * b.num, a.den * b.den);
}

/* Dividere per b significa moltiplicare per il suo reciproco. */
Frazione quoziente(Frazione a, Frazione b)
{
    return prodotto(a, crea(b.den, b.num));
}

/* Porta il segno al numeratore e riduce ai minimi termini. */
Frazione normalizza(Frazione f)
{
    int d;

    if (f.den < 0) {
        f.num = -f.num;
        f.den = -f.den;
    }
    d = mcd(f.num < 0 ? -f.num : f.num, f.den);
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
    if (f.den == 1) {
        printf("%d", f.num);
    } else {
        printf("%d/%d", f.num, f.den);
    }
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
