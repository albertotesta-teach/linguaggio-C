/*
 * 080-problema-cifrario-vigenere.c
 *
 * Cifrare messaggi con il cifrario di Vigenère
 *
 * Il cifrario di Cesare (array e funzioni, capitolo 04) sposta tutte le
 * lettere dello stesso numero di posizioni. Il cifrario di Vigenère usa
 * invece una PAROLA CHIAVE: ogni lettera del messaggio è spostata del
 * valore della lettera della chiave corrispondente (A = 0, B = 1, ...),
 * e la chiave si ripete ciclicamente.
 *
 *     messaggio   C I A O   M O N D O
 *     chiave      L U N A   L U N A L        (gli spazi non consumano la chiave)
 *     spostamento 11 20 13 0 11 20 13 0 11
 *     cifrato     N C N O   X I A D Z
 *
 * Regole:
 *   - si cifrano solo le lettere (isalpha), che mantengono maiuscola o
 *     minuscola (isupper); gli altri caratteri restano uguali;
 *   - la chiave deve contenere solo lettere e viene portata in maiuscolo;
 *   - per decifrare si sposta all'indietro: (lettera - spostamento + 26) % 26.
 *
 * Il programma chiede la chiave (ripetendo la richiesta se non valida),
 * poi cifra e decifra le frasi inserite fino a una riga vuota.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DIM       80
#define DIM_CHIAVE 20

int leggi_riga(char s[], int dim);
int chiave_valida(const char chiave[]);
void vigenere(char dest[], const char sorg[], const char chiave[], int verso);

int main(void)
{
    char chiave[DIM_CHIAVE];
    char messaggio[DIM];
    char cifrato[DIM];
    char decifrato[DIM];
    int i;
    int letta;

    printf("=== CIFRARIO DI VIGENERE ===\n");
    do {
        printf("Chiave (solo lettere): ");
        leggi_riga(chiave, DIM_CHIAVE);
        if (!chiave_valida(chiave)) {
            printf("  Chiave non valida.\n");
        }
    } while (!chiave_valida(chiave));

    for (i = 0; chiave[i] != '\0'; i++) {
        chiave[i] = (char) toupper((unsigned char) chiave[i]);
    }
    printf("Chiave in uso: %s\n", chiave);

    printf("Messaggio (riga vuota per terminare): ");
    letta = leggi_riga(messaggio, DIM);
    while (letta && messaggio[0] != '\0') {
        vigenere(cifrato, messaggio, chiave, 1);
        vigenere(decifrato, cifrato, chiave, -1);
        printf("  cifrato  : %s\n", cifrato);
        printf("  decifrato: %s  (%s)\n", decifrato,
               strcmp(decifrato, messaggio) == 0 ? "uguale all'originale" : "ERRORE");
        printf("Messaggio (riga vuota per terminare): ");
        letta = leggi_riga(messaggio, DIM);
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
    } else {
        strcpy(s, "");
    }
    return ok;
}

/* 1 se la chiave non è vuota e contiene solo lettere. */
int chiave_valida(const char chiave[])
{
    int i = 0;
    int valida;

    valida = chiave[0] != '\0';
    while (chiave[i] != '\0' && valida) {
        if (!isalpha((unsigned char) chiave[i])) {
            valida = 0;
        }
        i++;
    }
    return valida;
}

/* Cifra (verso = 1) o decifra (verso = -1) sorg in dest con la chiave,
 * che deve essere in maiuscolo. L'indice k della chiave avanza solo
 * quando si cifra una lettera. */
void vigenere(char dest[], const char sorg[], const char chiave[], int verso)
{
    int i = 0;
    int k = 0;
    int lung_chiave;
    int spostamento;
    char base;
    unsigned char c;

    lung_chiave = (int) strlen(chiave);
    while (sorg[i] != '\0') {
        c = (unsigned char) sorg[i];
        if (isalpha(c)) {
            base = isupper(c) ? 'A' : 'a';
            spostamento = (chiave[k % lung_chiave] - 'A') * verso;
            dest[i] = (char) (base + (c - base + spostamento + 26) % 26);
            k++;
        } else {
            dest[i] = sorg[i];
        }
        i++;
    }
    dest[i] = '\0';
}
