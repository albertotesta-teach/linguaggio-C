/*
 * 080-problema-anagrammi.c
 *
 * Trovare gli anagrammi in un elenco di parole
 *
 * Due parole sono anagrammi se usano le stesse lettere lo stesso numero di
 * volte, in un ordine diverso: "roma" e "amor", "attore" e "teatro".
 * Maiuscole, spazi e apostrofi non contano.
 *
 * Per confrontare due parole si costruisce la loro "impronta": un array di
 * 26 contatori, uno per ogni lettera dell'alfabeto.
 *
 *     "attore"  ->  a:1 e:1 o:1 r:1 t:2      (tutti gli altri a 0)
 *     "teatro"  ->  a:1 e:1 o:1 r:1 t:2      stessa impronta: anagrammi
 *
 * conta_lettere(parola, contatori) riempie l'impronta usando isalpha e
 * tolower: la lettera c incrementa contatori[c - 'a'].
 * Due parole sono anagrammi se le impronte coincidono cella per cella e le
 * parole non sono identiche.
 *
 * Il programma cerca nell'elenco gli anagrammi di ogni parola inserita,
 * finché non si inserisce una riga vuota.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PAROLE  12
#define LUNG    20
#define LETTERE 26
#define DIM     30

int leggi_riga(char s[], int dim);
void conta_lettere(const char parola[], int contatori[]);
int sono_anagrammi(const char a[], const char b[]);
int uguali_senza_maiuscole(const char a[], const char b[]);

int main(void)
{
    char elenco[PAROLE][LUNG] = {
        "teatro", "amor", "ramo", "latte", "Mora", "tale",
        "orma", "lieto", "rotate", "armo", "tela", "toilette"
    };
    char parola[DIM];
    int letta;
    int k;
    int trovati;

    printf("=== RICERCA DI ANAGRAMMI (%d parole in elenco) ===\n", PAROLE);
    printf("Parola (riga vuota per uscire): ");
    letta = leggi_riga(parola, DIM);

    while (letta && parola[0] != '\0') {
        trovati = 0;
        for (k = 0; k < PAROLE; k++) {
            if (sono_anagrammi(parola, elenco[k])) {
                printf("  %s\n", elenco[k]);
                trovati++;
            }
        }
        printf("  -> %d %s di \"%s\"\n", trovati,
               trovati == 1 ? "anagramma" : "anagrammi", parola);
        printf("Parola (riga vuota per uscire): ");
        letta = leggi_riga(parola, DIM);
    }

    return 0;
}

int leggi_riga(char s[], int dim)
{
    int ok = 0;
    int n;
    int c;

    if (fgets(s, dim, stdin) != NULL) {
        ok = 1;
        n = (int) strlen(s);
        if (n > 0 && s[n - 1] == '\n') {
            s[n - 1] = '\0';
        } else {
            c = getchar();
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }
    }
    return ok;
}

/* Azzera i contatori e conta le lettere di parola (maiuscole comprese). */
void conta_lettere(const char parola[], int contatori[])
{
    int i;
    unsigned char c;

    for (i = 0; i < LETTERE; i++) {
        contatori[i] = 0;
    }
    i = 0;
    while (parola[i] != '\0') {
        c = (unsigned char) parola[i];
        if (isalpha(c)) {
            contatori[tolower(c) - 'a']++;
        }
        i++;
    }
}

/* 1 se a e b hanno le stesse lettere e non sono la stessa parola. */
int sono_anagrammi(const char a[], const char b[])
{
    int conta_a[LETTERE];
    int conta_b[LETTERE];
    int i = 0;
    int uguali = 1;

    conta_lettere(a, conta_a);
    conta_lettere(b, conta_b);
    while (i < LETTERE && uguali) {
        if (conta_a[i] != conta_b[i]) {
            uguali = 0;
        }
        i++;
    }
    return uguali && !uguali_senza_maiuscole(a, b);
}

int uguali_senza_maiuscole(const char a[], const char b[])
{
    int i = 0;

    while (a[i] != '\0' && tolower((unsigned char) a[i]) == tolower((unsigned char) b[i])) {
        i++;
    }
    return tolower((unsigned char) a[i]) == tolower((unsigned char) b[i]);
}
