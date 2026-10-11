/*
 * 060-problema-login.c
 *
 * Accesso al gestionale di un laboratorio
 *
 * Gli account sono memorizzati in due array paralleli di stringhe, utenti
 * e password; un terzo array parallelo, errori[], conta i tentativi
 * sbagliati di ogni account. Dopo MAX_ERRORI password errate consecutive
 * l'account viene bloccato.
 *
 * Il programma ripete la richiesta di accesso finché non si scrive "fine"
 * come nome utente. Per ogni tentativo:
 *   - cerca l'utente con strcmp (cerca_utente restituisce l'indice o -1);
 *   - se l'utente non esiste o la password è sbagliata stampa lo stesso
 *     messaggio "Credenziali non valide": dire quale dei due dati è
 *     sbagliato aiuterebbe chi prova a indovinare gli account;
 *   - un accesso riuscito azzera il contatore degli errori.
 *
 * Al termine viene stampato lo stato di tutti gli account.
 */

#include <stdio.h>
#include <string.h>

#define ACCOUNT    4
#define LUNG       20
#define DIM        40
#define MAX_ERRORI 3

int leggi_riga(char s[], int dim);
int cerca_utente(const char nome[], const char utenti[][LUNG], int n);

int main(void)
{
    char utenti[ACCOUNT][LUNG]   = {"admin", "mrossi", "lbianchi", "gverdi"};
    char password[ACCOUNT][LUNG] = {"Lab!2024", "Rossi#77", "Bianchi.99", "Verdi_2010"};
    int errori[ACCOUNT] = {0};
    char nome[DIM];
    char chiave[DIM];
    int k;
    int accessi = 0;

    printf("=== GESTIONALE DEL LABORATORIO ===\n");
    printf("Utente (\"fine\" per chiudere): ");
    leggi_riga(nome, DIM);

    while (strcmp(nome, "fine") != 0) {
        printf("Password: ");
        leggi_riga(chiave, DIM);
        k = cerca_utente(nome, utenti, ACCOUNT);

        if (k == -1) {
            printf("  Credenziali non valide.\n");
        } else if (errori[k] >= MAX_ERRORI) {
            printf("  Account bloccato: rivolgersi al tecnico.\n");
        } else if (strcmp(chiave, password[k]) == 0) {
            errori[k] = 0;
            accessi++;
            printf("  Benvenuto, %s!\n", utenti[k]);
        } else {
            errori[k]++;
            printf("  Credenziali non valide.\n");
            if (errori[k] == MAX_ERRORI) {
                printf("  Troppi errori: l'account %s e' stato bloccato.\n", utenti[k]);
            }
        }

        printf("Utente (\"fine\" per chiudere): ");
        leggi_riga(nome, DIM);
    }

    printf("\nAccessi riusciti: %d\n", accessi);
    printf("Stato degli account:\n");
    for (k = 0; k < ACCOUNT; k++) {
        printf("  %-9s %s (errori: %d)\n", utenti[k],
               errori[k] >= MAX_ERRORI ? "BLOCCATO" : "attivo  ", errori[k]);
    }

    return 0;
}

/* Legge una riga e toglie il '\n'. A fine input restituisce 0 e scrive
 * "fine" in s, così il ciclo principale termina. */
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

/* Restituisce l'indice di nome nell'elenco utenti, oppure -1. */
int cerca_utente(const char nome[], const char utenti[][LUNG], int n)
{
    int k = 0;
    int trovato = -1;

    while (k < n && trovato == -1) {
        if (strcmp(nome, utenti[k]) == 0) {
            trovato = k;
        }
        k++;
    }
    return trovato;
}
