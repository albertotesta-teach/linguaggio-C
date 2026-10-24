/*
 * 040-problema-unisci-stringhe.c
 *
 * Gli indirizzi email della classe, creati da nome e cognome
 *
 * Il laboratorio di informatica crea gli account degli studenti nuovi.
 * L'indirizzo si forma unendo nome e cognome:
 *
 *     Luca D'Amico      ->   luca.damico@studenti.scuola.it
 *
 * tutto minuscolo e senza i caratteri che non sono lettere. Se
 * l'indirizzo esiste già si aggiunge un numero: marta.bassi2@...
 *
 * La funzione
 *
 *     char *crea_email(const char *nome, const char *cognome, int numero);
 *
 * calcola quanti caratteri servono, alloca un blocco di esattamente
 * quella lunghezza più uno, lo riempie e lo restituisce. Il chiamante
 * conserva i puntatori in un array e alla fine li libera tutti.
 *
 * Per sapere se un indirizzo esiste già, il programma lo crea con
 * numero 0 e lo cerca nell'elenco: se c'è, lo libera e riprova con 2,
 * poi 3, e così via.
 *
 * Il programma legge "nome cognome" fino a FINE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTI 30
#define DOMINIO "@studenti.scuola.it"

char *crea_email(const char *nome, const char *cognome, int numero);
int lettere(const char *testo);
int cifre(int numero);
int presente(char *elenco[], int n, const char *email);

int main(void)
{
    char *elenco[MAX_STUDENTI];
    char nome[24];
    char cognome[24];
    char *email;
    int n = 0;
    int numero;
    int i;
    int finito = 0;

    while (!finito && n < MAX_STUDENTI) {
        printf("Nome e cognome (FINE per terminare): ");
        if (scanf("%23s", nome) != 1 || strcmp(nome, "FINE") == 0 ||
            scanf("%23s", cognome) != 1) {
            finito = 1;
        } else {
            scanf("%*[^\n]");          /* scarta il resto della riga */
            if (lettere(nome) == 0 || lettere(cognome) == 0) {
                printf("  Nome o cognome senza lettere.\n");
            } else {
                numero = 0;
                email = crea_email(nome, cognome, numero);
                while (email != NULL && presente(elenco, n, email)) {
                    free(email);
                    if (numero == 0) {
                        numero = 2;
                    } else {
                        numero++;
                    }
                    email = crea_email(nome, cognome, numero);
                }
                if (email == NULL) {
                    printf("  Memoria insufficiente.\n");
                    finito = 1;
                } else {
                    elenco[n] = email;
                    n++;
                    printf("  %s (%zu caratteri)\n", email, strlen(email));
                }
            }
        }
    }

    printf("\nAccount da creare: %d\n", n);
    for (i = 0; i < n; i++) {
        printf("  %s\n", elenco[i]);
        free(elenco[i]);
    }

    return 0;
}

/* nome.cognome[numero]@dominio, in un blocco della lunghezza giusta. */
char *crea_email(const char *nome, const char *cognome, int numero)
{
    size_t lunghezza = lettere(nome) + 1 + lettere(cognome) + strlen(DOMINIO);
    char *email;
    int j = 0;
    int i;

    if (numero > 0) {
        lunghezza = lunghezza + cifre(numero);
    }
    email = malloc((lunghezza + 1) * sizeof *email);
    if (email != NULL) {
        for (i = 0; nome[i] != '\0'; i++) {
            if (isalpha((unsigned char) nome[i])) {
                email[j] = (char) tolower((unsigned char) nome[i]);
                j++;
            }
        }
        email[j] = '.';
        j++;
        for (i = 0; cognome[i] != '\0'; i++) {
            if (isalpha((unsigned char) cognome[i])) {
                email[j] = (char) tolower((unsigned char) cognome[i]);
                j++;
            }
        }
        email[j] = '\0';
        if (numero > 0) {
            snprintf(email + j, lunghezza + 1 - j, "%d", numero);
        }
        strcat(email, DOMINIO);
    }
    return email;
}

/* Quante lettere contiene il testo. */
int lettere(const char *testo)
{
    int conta = 0;
    int i;

    for (i = 0; testo[i] != '\0'; i++) {
        if (isalpha((unsigned char) testo[i])) {
            conta++;
        }
    }
    return conta;
}

/* Quante cifre ha un numero positivo. */
int cifre(int numero)
{
    int conta = 1;

    while (numero >= 10) {
        numero = numero / 10;
        conta++;
    }
    return conta;
}

int presente(char *elenco[], int n, const char *email)
{
    int trovato = 0;
    int i;

    for (i = 0; i < n && !trovato; i++) {
        trovato = strcmp(elenco[i], email) == 0;
    }
    return trovato;
}
