/*
 * 040-problema-validazione-email.c
 *
 * Controllare il formato di un indirizzo email
 *
 * Il modulo di iscrizione a una newsletter deve rifiutare gli indirizzi
 * scritti male. Un controllo semplificato verifica che l'indirizzo:
 *   1. non contenga spazi                           (strchr)
 *   2. contenga esattamente una '@'                 (strchr + conteggio)
 *   3. abbia almeno un carattere prima della '@'
 *   4. abbia almeno un '.' DOPO la '@'              (ultima_posizione)
 *   5. non abbia il '.' subito dopo la '@' né come ultimo carattere
 *
 * La funzione controlla_email() restituisce 0 se l'indirizzo è valido,
 * altrimenti il numero della prima regola violata; il main traduce il
 * numero in un messaggio. Gli indirizzi si leggono finché non si scrive
 * "fine".
 */

#include <stdio.h>
#include <string.h>

#define DIM 60

int leggi_riga(char s[], int dim);
int controlla_email(const char s[]);
int conta_carattere(const char s[], char c);
int prima_posizione(const char s[], char c);
int ultima_posizione(const char s[], char c);

int main(void)
{
    char email[DIM];
    char messaggi[6][44] = {
        "indirizzo valido",
        "contiene spazi",
        "deve contenere una sola '@'",
        "manca il nome prima della '@'",
        "manca il '.' nel dominio dopo la '@'",
        "'.' in posizione non ammessa nel dominio"
    };
    int esito;
    int valide = 0;
    int rifiutate = 0;

    printf("=== ISCRIZIONE ALLA NEWSLETTER ===\n");
    printf("Email (\"fine\" per terminare): ");
    leggi_riga(email, DIM);

    while (strcmp(email, "fine") != 0) {
        esito = controlla_email(email);
        if (esito == 0) {
            valide++;
            printf("  OK: %s\n", messaggi[0]);
        } else {
            rifiutate++;
            printf("  Rifiutato (regola %d): %s\n", esito, messaggi[esito]);
        }
        printf("Email (\"fine\" per terminare): ");
        leggi_riga(email, DIM);
    }
    printf("\nIndirizzi accettati: %d, rifiutati: %d\n", valide, rifiutate);

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
        strcpy(s, "fine");
    }
    return ok;
}

/* 0 se l'indirizzo è valido, altrimenti il numero della prima regola
 * violata (vedi l'elenco in testa al file). */
int controlla_email(const char s[])
{
    int esito = 0;
    int chiocciola;
    int ultimo_punto;
    int lung;

    lung = (int) strlen(s);
    chiocciola = prima_posizione(s, '@');
    ultimo_punto = ultima_posizione(s, '.');

    if (strchr(s, ' ') != NULL) {
        esito = 1;
    } else if (strchr(s, '@') == NULL || conta_carattere(s, '@') > 1) {
        esito = 2;
    } else if (chiocciola == 0) {
        esito = 3;
    } else if (ultimo_punto < chiocciola) {
        esito = 4;                      /* nessun '.' dopo la '@' */
    } else if (s[chiocciola + 1] == '.' || ultimo_punto == lung - 1) {
        esito = 5;
    }
    return esito;
}

int conta_carattere(const char s[], char c)
{
    int i = 0;
    int n = 0;

    while (s[i] != '\0') {
        if (s[i] == c) {
            n++;
        }
        i++;
    }
    return n;
}

int prima_posizione(const char s[], char c)
{
    int i = 0;
    int posizione = -1;

    while (s[i] != '\0' && posizione == -1) {
        if (s[i] == c) {
            posizione = i;
        }
        i++;
    }
    return posizione;
}

int ultima_posizione(const char s[], char c)
{
    int i = 0;
    int posizione = -1;

    while (s[i] != '\0') {
        if (s[i] == c) {
            posizione = i;
        }
        i++;
    }
    return posizione;
}
