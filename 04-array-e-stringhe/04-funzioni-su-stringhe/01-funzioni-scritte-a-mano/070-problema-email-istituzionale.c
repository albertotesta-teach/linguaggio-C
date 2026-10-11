/*
 * 070-problema-email-istituzionale.c
 *
 * Creare gli indirizzi email istituzionali di studenti e docenti
 *
 * Ogni persona ha un nome, un cognome e un ruolo, memorizzati in tre array
 * paralleli: 'S' per gli studenti, 'D' per i docenti. L'indirizzo ha la
 * forma
 *
 *     nome.cognome@dominio
 *
 * con queste regole:
 *   - tutto in minuscolo, senza spazi né apostrofi
 *     ("Maria Grazia" "D'Angelo" -> mariagrazia.dangelo);
 *   - il dominio dipende dal ruolo: studenti.scuola.edu.it oppure
 *     scuola.edu.it;
 *   - se la parte prima della @ supera MAX_LOCALE caratteri, il nome viene
 *     sostituito dalla sola iniziale (m.dellacquabianchi).
 *
 * Il programma stampa l'elenco degli indirizzi e poi le due liste di
 * distribuzione (docenti e studenti). Le stringhe si costruiscono con
 * copia() e concatena(); solo_lettere() prepara i pezzi.
 */

#include <stdio.h>

#define PERSONE    7
#define LUNG       30
#define LUNG_EMAIL 60
#define MAX_LOCALE 25

void crea_email(char email[], const char nome[], const char cognome[], char ruolo);
void solo_lettere(char dest[], const char sorg[]);
void copia(char dest[], const char sorg[]);
void concatena(char dest[], const char sorg[]);
int lunghezza(const char s[]);
char minuscola(char c);
int e_lettera(char c);

int main(void)
{
    char nomi[PERSONE][LUNG] = {
        "Luca", "Maria Grazia", "Paolo", "Maria Vittoria",
        "Sara", "Giovanni", "Elena"
    };
    char cognomi[PERSONE][LUNG] = {
        "Ferrari", "D'Angelo", "Esposito", "Dell'Acqua Bianchi",
        "Colombo", "La Rosa", "Ricci"
    };
    char ruoli[PERSONE] = {'S', 'D', 'S', 'S', 'D', 'S', 'D'};
    char email[PERSONE][LUNG_EMAIL];
    int k;

    printf("=== INDIRIZZI EMAIL ISTITUZIONALI ===\n");
    for (k = 0; k < PERSONE; k++) {
        crea_email(email[k], nomi[k], cognomi[k], ruoli[k]);
        printf("  %-15s %-19s %c  %s\n", nomi[k], cognomi[k], ruoli[k], email[k]);
    }

    printf("\nLista docenti:\n");
    for (k = 0; k < PERSONE; k++) {
        if (ruoli[k] == 'D') {
            printf("  %s\n", email[k]);
        }
    }
    printf("Lista studenti:\n");
    for (k = 0; k < PERSONE; k++) {
        if (ruoli[k] == 'S') {
            printf("  %s\n", email[k]);
        }
    }

    return 0;
}

/* Costruisce l'indirizzo email secondo le regole in testa al file. */
void crea_email(char email[], const char nome[], const char cognome[], char ruolo)
{
    char parte_nome[LUNG];
    char parte_cognome[LUNG];

    solo_lettere(parte_nome, nome);
    solo_lettere(parte_cognome, cognome);

    /* parte locale troppo lunga: del nome resta l'iniziale */
    if (lunghezza(parte_nome) + 1 + lunghezza(parte_cognome) > MAX_LOCALE) {
        parte_nome[1] = '\0';
    }

    copia(email, parte_nome);
    concatena(email, ".");
    concatena(email, parte_cognome);
    if (ruolo == 'D') {
        concatena(email, "@scuola.edu.it");
    } else {
        concatena(email, "@studenti.scuola.edu.it");
    }
}

/* Copia in dest solo le lettere di sorg, in minuscolo. */
void solo_lettere(char dest[], const char sorg[])
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

void copia(char dest[], const char sorg[])
{
    int i = 0;

    while (sorg[i] != '\0') {
        dest[i] = sorg[i];
        i++;
    }
    dest[i] = '\0';
}

void concatena(char dest[], const char sorg[])
{
    int fine;
    int i = 0;

    fine = lunghezza(dest);
    while (sorg[i] != '\0') {
        dest[fine + i] = sorg[i];
        i++;
    }
    dest[fine + i] = '\0';
}

int lunghezza(const char s[])
{
    int n = 0;

    while (s[n] != '\0') {
        n++;
    }
    return n;
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
