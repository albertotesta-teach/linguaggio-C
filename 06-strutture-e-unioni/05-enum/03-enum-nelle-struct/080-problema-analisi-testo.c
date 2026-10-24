/*
 * 080-problema-analisi-testo.c
 *
 * Un automa che conta parole, numeri e segni di punteggiatura
 *
 * Per le statistiche dei temi il programma legge il testo un carattere
 * alla volta e ricorda solo in che stato si trova:
 *
 *     typedef enum { FUORI, IN_PAROLA, IN_NUMERO } Stato;
 *
 *     typedef struct {
 *         int parole;
 *         int numeri;
 *         int punteggiatura;
 *         int righe;
 *     } Conteggi;
 *
 * Regole, scritte come uno switch sullo stato:
 *   - FUORI: una lettera inizia una parola, una cifra inizia un numero;
 *   - IN_PAROLA: lettere e cifre continuano la parola ("3B" dopo la B,
 *     "A4"); qualsiasi altro carattere la chiude;
 *   - IN_NUMERO: le cifre continuano il numero; una lettera lo trasforma
 *     in una parola ("3B": era un numero, è una sigla), gli altri
 *     caratteri lo chiudono.
 * Un segno tra . , ; : ! ? si conta sempre. Una parola o un numero
 * vengono contati quando iniziano; il passaggio da numero a parola toglie
 * un numero e aggiunge una parola.
 *
 * Il programma legge le righe fino a FINE; a ogni riga nuova si riparte
 * da FUORI.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LUNG 120

typedef enum {
    FUORI, IN_PAROLA, IN_NUMERO
} Stato;

typedef struct {
    int parole;
    int numeri;
    int punteggiatura;
    int righe;
} Conteggi;

void analizza(const char riga[], Conteggi *c);

int main(void)
{
    Conteggi conteggi = {0, 0, 0, 0};
    char riga[LUNG];
    int finito = 0;
    int resto;

    printf("Testo (FINE su una riga per terminare):\n");
    while (!finito) {
        if (fgets(riga, LUNG, stdin) == NULL) {
            finito = 1;
        } else {
            if (strchr(riga, '\n') == NULL) {
                resto = getchar();      /* riga troppo lunga: scarta il resto */
                while (resto != '\n' && resto != EOF) {
                    resto = getchar();
                }
            }
            riga[strcspn(riga, "\n")] = '\0';
            if (strcmp(riga, "FINE") == 0) {
                finito = 1;
            } else {
                analizza(riga, &conteggi);
            }
        }
    }

    printf("Righe %d, parole %d, numeri %d, segni di punteggiatura %d\n", conteggi.righe,
           conteggi.parole, conteggi.numeri, conteggi.punteggiatura);

    return 0;
}

void analizza(const char riga[], Conteggi *c)
{
    Stato stato = FUORI;
    unsigned char ch;
    int i;

    c->righe++;
    for (i = 0; riga[i] != '\0'; i++) {
        ch = (unsigned char) riga[i];
        if (strchr(".,;:!?", ch) != NULL) {
            c->punteggiatura++;
        }
        switch (stato) {
        case FUORI:
            if (isalpha(ch)) {
                stato = IN_PAROLA;
                c->parole++;
            } else if (isdigit(ch)) {
                stato = IN_NUMERO;
                c->numeri++;
            }
            break;
        case IN_PAROLA:
            if (!isalnum(ch)) {
                stato = FUORI;
            }
            break;
        case IN_NUMERO:
            if (isalpha(ch)) {
                stato = IN_PAROLA;
                c->numeri--;
                c->parole++;
            } else if (!isdigit(ch)) {
                stato = FUORI;
            }
            break;
        }
    }
}
