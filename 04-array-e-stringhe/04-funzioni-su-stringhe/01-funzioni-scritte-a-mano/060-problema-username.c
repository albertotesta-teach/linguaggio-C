/*
 * 060-problema-username.c
 *
 * Generare gli username per la piattaforma della scuola
 *
 * La segreteria deve creare un account per ogni nuovo iscritto. I nomi e i
 * cognomi sono in due array paralleli: la riga k di nomi[] e la riga k di
 * cognomi[] descrivono la stessa persona.
 *
 * Regole per lo username:
 *   - iniziale del nome + cognome, tutto in minuscolo;
 *   - nel cognome si tengono solo le lettere (spazi e apostrofi eliminati):
 *     "De Luca" -> "deluca", "D'Amico" -> "damico";
 *   - al massimo MAX_BASE caratteri: i cognomi lunghi vengono troncati;
 *   - se lo username è già stato assegnato si aggiunge una cifra:
 *     mrossi, mrossi2, mrossi3, ...
 *
 * Gli username assegnati vengono salvati in un terzo array parallelo,
 * usernames[], che serve anche per riconoscere i duplicati.
 */

#include <stdio.h>

#define ISCRITTI 8
#define LUNG     25
#define MAX_BASE 8

void crea_base(char dest[], const char nome[], const char cognome[]);
int gia_presente(const char candidato[], const char elenco[][LUNG], int n);
void copia(char dest[], const char sorg[]);
int lunghezza(const char s[]);
int confronta(const char a[], const char b[]);
char minuscola(char c);
int e_lettera(char c);

int main(void)
{
    char nomi[ISCRITTI][LUNG] = {
        "Mario", "Marco", "Anna Maria", "Giuseppe",
        "Laura", "Francesca", "Mattia", "Mirko"
    };
    char cognomi[ISCRITTI][LUNG] = {
        "Rossi", "Rossi", "De Luca", "D'Amico",
        "Bianchi", "Santangelo", "Santangelini", "Rossi"
    };
    char usernames[ISCRITTI][LUNG];
    char base[LUNG];
    char candidato[LUNG];
    int k;
    int numero;
    int lung_base;
    int con_numero = 0;

    printf("=== CREAZIONE DEGLI ACCOUNT ===\n");
    printf("  %-12s %-14s %s\n", "Nome", "Cognome", "Username");

    for (k = 0; k < ISCRITTI; k++) {
        crea_base(base, nomi[k], cognomi[k]);
        copia(candidato, base);
        numero = 1;
        lung_base = lunghezza(base);

        /* finché il candidato è già usato, si prova la cifra successiva */
        while (gia_presente(candidato, usernames, k)) {
            numero++;
            copia(candidato, base);
            candidato[lung_base] = '0' + numero;
            candidato[lung_base + 1] = '\0';
        }
        if (numero > 1) {
            con_numero++;
        }

        copia(usernames[k], candidato);
        printf("  %-12s %-14s %s\n", nomi[k], cognomi[k], usernames[k]);
    }

    printf("\nAccount creati: %d, di cui %d con cifra aggiunta\n", ISCRITTI, con_numero);

    return 0;
}

/* Iniziale del nome + lettere del cognome, in minuscolo, al massimo
 * MAX_BASE caratteri. */
void crea_base(char dest[], const char nome[], const char cognome[])
{
    int i = 0;
    int j = 0;

    dest[j] = minuscola(nome[0]);
    j++;
    while (cognome[i] != '\0' && j < MAX_BASE) {
        if (e_lettera(cognome[i])) {
            dest[j] = minuscola(cognome[i]);
            j++;
        }
        i++;
    }
    dest[j] = '\0';
}

/* 1 se candidato compare tra le prime n stringhe di elenco. */
int gia_presente(const char candidato[], const char elenco[][LUNG], int n)
{
    int k = 0;
    int trovato = 0;

    while (k < n && !trovato) {
        if (confronta(candidato, elenco[k]) == 0) {
            trovato = 1;
        }
        k++;
    }
    return trovato;
}

void copia(char dest[], const char sorg[])
{
    int i = 0;

    while (sorg[i] != '\0') {
        dest[i] = sorg[i];
        i++;
    }
    dest[i] = '\0';
}

int lunghezza(const char s[])
{
    int n = 0;

    while (s[n] != '\0') {
        n++;
    }
    return n;
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

int e_lettera(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
