/*
 * 050-problema-normalizza-nome.c
 *
 * Normalizzare nomi e cognomi inseriti in un modulo
 *
 * In un modulo di iscrizione gli utenti scrivono i nomi nei modi più vari:
 *
 *     "  mARIO   de  ROSSI "      ->   "Mario De Rossi"
 *     "anna-maria d'angelo"       ->   "Anna-Maria D'Angelo"
 *
 * Prima di salvarli nell'archivio, la segreteria vuole un formato unico:
 *   - spazi iniziali e finali eliminati;
 *   - un solo spazio tra una parola e l'altra;
 *   - ogni parola con l'iniziale maiuscola e le altre lettere minuscole;
 *   - dopo un apostrofo o un trattino la lettera è di nuovo maiuscola.
 *
 * Il programma legge un nome per riga e si ferma con una riga vuota.
 * La funzione normalizza(dest, sorg) scorre sorg una volta sola usando
 * un flag inizio_parola che dice se il prossimo carattere apre una parola.
 */

#include <stdio.h>

#define DIM 60

int leggi_riga(char s[], int dim);
void normalizza(char dest[], const char sorg[]);
int conta_parole(const char s[]);
char maiuscola(char c);
char minuscola(char c);

int main(void)
{
    char inserito[DIM];
    char corretto[DIM];
    int letta;
    int parole;

    printf("=== NORMALIZZAZIONE DEI NOMI ===\n");
    printf("Nome e cognome (riga vuota per terminare): ");
    letta = leggi_riga(inserito, DIM);

    while (letta && inserito[0] != '\0') {
        normalizza(corretto, inserito);
        printf("  inserito : [%s]\n", inserito);
        parole = conta_parole(corretto);
        printf("  archivio : [%s]  (%d %s)\n", corretto, parole,
               parole == 1 ? "parola" : "parole");
        printf("Nome e cognome (riga vuota per terminare): ");
        letta = leggi_riga(inserito, DIM);
    }
    printf("Fine inserimento.\n");

    return 0;
}

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
            c = getchar();
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }
    }
    return ok;
}

/* Scrive in dest la versione normalizzata di sorg. dest non è mai più
 * lunga di sorg, quindi basta un array della stessa dimensione. */
void normalizza(char dest[], const char sorg[])
{
    int i = 0;
    int j = 0;
    int inizio_parola = 1;
    char c;

    while (sorg[i] != '\0') {
        c = sorg[i];
        if (c == ' ') {
            /* uno spazio si copia solo se separa due parole */
            if (j > 0 && dest[j - 1] != ' ') {
                dest[j] = ' ';
                j++;
            }
            inizio_parola = 1;
        } else {
            if (inizio_parola) {
                dest[j] = maiuscola(c);
            } else {
                dest[j] = minuscola(c);
            }
            j++;
            inizio_parola = (c == '\'' || c == '-');
        }
        i++;
    }
    if (j > 0 && dest[j - 1] == ' ') {
        j--;                            /* spazio finale eliminato */
    }
    dest[j] = '\0';
}

/* Conta le parole di una stringa normalizzata (separate da un solo spazio). */
int conta_parole(const char s[])
{
    int i = 0;
    int parole = 0;

    if (s[0] != '\0') {
        parole = 1;
    }
    while (s[i] != '\0') {
        if (s[i] == ' ') {
            parole++;
        }
        i++;
    }
    return parole;
}

char maiuscola(char c)
{
    char risultato = c;

    if (c >= 'a' && c <= 'z') {
        risultato = c - ('a' - 'A');
    }
    return risultato;
}

char minuscola(char c)
{
    char risultato = c;

    if (c >= 'A' && c <= 'Z') {
        risultato = c + ('a' - 'A');
    }
    return risultato;
}
