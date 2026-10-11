/*
 * 040-problema-palindromo.c
 *
 * Riconoscere le frasi palindrome
 *
 * Una frase è palindroma se si legge allo stesso modo da sinistra a destra
 * e da destra a sinistra, trascurando spazi, punteggiatura e maiuscole:
 *
 *     "I topi non avevano nipoti"   ->  itopinonavevanonipoti   palindroma
 *
 * Il programma legge una frase alla volta (con spazi, quindi con fgets)
 * finché l'utente non scrive "fine". Per ogni frase:
 *   1. pulisci()  tiene solo le lettere e le porta in minuscolo;
 *   2. inverti()  costruisce la stringa al contrario;
 *   3. confronta() verifica se le due stringhe sono uguali.
 *
 * leggi_riga() legge una riga con fgets, toglie il '\n' finale e, se la
 * riga era troppo lunga, scarta i caratteri rimasti nel buffer.
 */

#include <stdio.h>

#define DIM 80

int leggi_riga(char s[], int dim);
int lunghezza(const char s[]);
void pulisci(char dest[], const char sorg[]);
void inverti(char dest[], const char sorg[]);
int confronta(const char a[], const char b[]);
char minuscola(char c);
int e_lettera(char c);

int main(void)
{
    char frase[DIM];
    char pulita[DIM];
    char rovesciata[DIM];
    int letta;
    int palindrome = 0;
    int esaminate = 0;

    printf("=== RICONOSCIMENTO DI PALINDROMI ===\n");
    printf("Frase (\"fine\" per terminare): ");
    letta = leggi_riga(frase, DIM);

    while (letta && confronta(frase, "fine") != 0) {
        pulisci(pulita, frase);
        inverti(rovesciata, pulita);
        esaminate++;

        printf("  solo lettere : %s\n", pulita);
        printf("  al contrario : %s\n", rovesciata);
        if (lunghezza(pulita) == 0) {
            printf("  nessuna lettera da esaminare\n");
        } else if (confronta(pulita, rovesciata) == 0) {
            printf("  -> PALINDROMA\n");
            palindrome++;
        } else {
            printf("  -> non palindroma\n");
        }

        printf("Frase (\"fine\" per terminare): ");
        letta = leggi_riga(frase, DIM);
    }

    printf("\nFrasi esaminate: %d, palindrome: %d\n", esaminate, palindrome);

    return 0;
}

/* Legge una riga in s (al massimo dim - 1 caratteri) e toglie il '\n'.
 * Restituisce 0 se l'input è terminato, 1 altrimenti. */
int leggi_riga(char s[], int dim)
{
    int ok = 0;
    int i = 0;
    int c;

    if (fgets(s, dim, stdin) != NULL) {
        ok = 1;
        while (s[i] != '\0' && s[i] != '\n') {
            i++;
        }
        if (s[i] == '\n') {
            s[i] = '\0';
        } else {
            /* riga troppo lunga: si scartano i caratteri non letti */
            c = getchar();
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }
    }
    return ok;
}

int lunghezza(const char s[])
{
    int n = 0;

    while (s[n] != '\0') {
        n++;
    }
    return n;
}

/* Copia in dest solo le lettere di sorg, in minuscolo. */
void pulisci(char dest[], const char sorg[])
{
    int i = 0;
    int j = 0;

    while (sorg[i] != '\0') {
        if (e_lettera(sorg[i])) {
            dest[j] = minuscola(sorg[i]);
            j++;
        }
        i++;
    }
    dest[j] = '\0';
}

/* Scrive in dest i caratteri di sorg in ordine inverso. */
void inverti(char dest[], const char sorg[])
{
    int n;
    int i;

    n = lunghezza(sorg);
    for (i = 0; i < n; i++) {
        dest[i] = sorg[n - 1 - i];
    }
    dest[n] = '\0';
}

int confronta(const char a[], const char b[])
{
    int i = 0;

    while (a[i] == b[i] && a[i] != '\0') {
        i++;
    }
    return a[i] - b[i];
}

char minuscola(char c)
{
    char risultato = c;

    if (c >= 'A' && c <= 'Z') {
        risultato = c + ('a' - 'A');
    }
    return risultato;
}

/* 1 se c è una lettera dell'alfabeto inglese, 0 altrimenti. */
int e_lettera(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
