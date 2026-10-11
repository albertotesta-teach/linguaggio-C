/*
 * 070-problema-trasforma-testo.c
 *
 * Trasformazioni di un messaggio carattere per carattere
 *
 * Il club di informatica prepara un piccolo strumento per i messaggi del
 * giornalino: dato un testo, mostra la versione in maiuscolo per i titoli,
 * la versione cifrata con il cifrario di Cesare (spostamento 3) per il
 * gioco della settimana, e la versione con le cifre oscurate, per non
 * pubblicare numeri di telefono.
 *
 * Tutte le trasformazioni lavorano un carattere alla volta. Una funzione
 * generale scorre la stringa e applica a ogni carattere la funzione
 * ricevuta come parametro:
 *
 *     void trasforma(char *testo, char (*regola)(char));
 *
 * Ogni trasformazione lavora su una COPIA del messaggio originale.
 * Il programma legge un messaggio per riga; una riga vuota termina.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LUNG 100

void trasforma(char *testo, char (*regola)(char));
char maiuscolo(char c);
char cesare(char c);
char oscura_cifre(char c);
void mostra(const char titolo[], const char *originale, char (*regola)(char));

int main(void)
{
    char messaggio[LUNG];
    char *a_capo;
    int continua = 1;

    while (continua) {
        printf("Messaggio (riga vuota per finire): ");
        if (fgets(messaggio, LUNG, stdin) == NULL) {
            continua = 0;
        } else {
            a_capo = strchr(messaggio, '\n');
            if (a_capo != NULL) {
                *a_capo = '\0';
            }
            if (messaggio[0] == '\0') {
                continua = 0;
            } else {
                mostra("maiuscolo", messaggio, maiuscolo);
                mostra("Cesare +3", messaggio, cesare);
                mostra("senza cifre", messaggio, oscura_cifre);
            }
        }
    }

    return 0;
}

/* Sostituisce ogni carattere di testo con regola(carattere). */
void trasforma(char *testo, char (*regola)(char))
{
    char *p;

    for (p = testo; *p != '\0'; p++) {
        *p = regola(*p);
    }
}

/* Copia l'originale, lo trasforma con regola e lo stampa. */
void mostra(const char titolo[], const char *originale, char (*regola)(char))
{
    char copia[LUNG];

    strcpy(copia, originale);
    trasforma(copia, regola);
    printf("  %-12s %s\n", titolo, copia);
}

char maiuscolo(char c)
{
    return (char) toupper((unsigned char) c);
}

/* Sposta le lettere di 3 posizioni nell'alfabeto inglese, ricominciando
 * da capo dopo la z; gli altri caratteri restano uguali. */
char cesare(char c)
{
    char risultato = c;

    if (c >= 'a' && c <= 'z') {
        risultato = (char) ('a' + (c - 'a' + 3) % 26);
    } else if (c >= 'A' && c <= 'Z') {
        risultato = (char) ('A' + (c - 'A' + 3) % 26);
    }
    return risultato;
}

char oscura_cifre(char c)
{
    return isdigit((unsigned char) c) ? '*' : c;
}
