/*
 * 020-valore-di-ritorno.c
 *
 * Il valore di ritorno delle funzioni
 *
 * Una funzione può restituire al chiamante un valore calcolato.
 * Il tipo del valore è dichiarato prima del nome della funzione.
 * L'istruzione "return espressione;" conclude la funzione e consegna
 * il risultato. Il chiamante può usare il valore ritornato in
 * un'espressione, in un'assegnazione o in una printf.
 *
 * Regola del progetto: una sola "return" per funzione, alla fine.
 */

#include <stdio.h>

/* Prototipi */
int somma(int a, int b);
double media(double a, double b, double c);
int valore_assoluto(int n);
char maiuscolo(char c);

/* --- Definizioni --- */

/* Funzione che restituisce un intero.
 * Il risultato viene calcolato in una variabile locale
 * e restituito con l'unica return alla fine. */
int somma(int a, int b)
{
    int risultato;
    risultato = a + b;
    return risultato;
}

/* Funzione che restituisce un double.
 * La variabile locale "media_val" accumula il risultato. */
double media(double a, double b, double c)
{
    double media_val;
    media_val = (a + b + c) / 3.0;
    return media_val;
}

/* Il valore assoluto si calcola senza break/continue:
 * usiamo una variabile "risultato" e l'if/else per scegliere il valore. */
int valore_assoluto(int n)
{
    int risultato;
    if (n >= 0) {
        risultato = n;
    } else {
        risultato = -n;
    }
    return risultato;
}

/* Funzione che restituisce un char.
 * Converte un carattere minuscolo in maiuscolo usando la codifica ASCII:
 * la differenza tra 'a' e 'A' è costante (32 posizioni). */
char maiuscolo(char c)
{
    char risultato;
    if (c >= 'a' && c <= 'z') {
        /* Il carattere è una lettera minuscola: lo convertiamo */
        risultato = c - 'a' + 'A';
    } else {
        /* Non è una minuscola: lo restituiamo invariato */
        risultato = c;
    }
    return risultato;
}

int main(void)
{
    int s;
    double m;
    int ass;
    char lettera;

    /* Il valore di ritorno può essere assegnato a una variabile... */
    s = somma(7, 3);
    printf("somma(7, 3) = %d\n", s);

    /* ...oppure usato direttamente in una printf... */
    printf("somma(100, 250) = %d\n", somma(100, 250));

    /* ...oppure usato come argomento di un'altra espressione */
    printf("somma(1,2) + somma(3,4) = %d\n", somma(1, 2) + somma(3, 4));

    printf("\n");

    m = media(7.5, 8.0, 6.5);
    printf("media(7.5, 8.0, 6.5) = %.2f\n", m);
    printf("media(10.0, 5.5, 7.0) = %.2f\n", media(10.0, 5.5, 7.0));

    printf("\n");

    ass = valore_assoluto(-42);
    printf("valore_assoluto(-42) = %d\n", ass);
    printf("valore_assoluto(17)  = %d\n", valore_assoluto(17));
    printf("valore_assoluto(0)   = %d\n", valore_assoluto(0));

    printf("\n");

    lettera = maiuscolo('g');
    printf("maiuscolo('g') = '%c'\n", lettera);
    printf("maiuscolo('A') = '%c'\n", maiuscolo('A'));
    printf("maiuscolo('3') = '%c'\n", maiuscolo('3'));

    return 0;
}
