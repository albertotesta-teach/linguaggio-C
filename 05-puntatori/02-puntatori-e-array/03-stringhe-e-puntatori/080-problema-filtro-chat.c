/*
 * 080-problema-filtro-chat.c
 *
 * Filtro delle parole vietate nella chat di classe
 *
 * La piattaforma della scuola ha una chat per ogni classe. Prima di
 * pubblicare un messaggio, il filtro sostituisce con asterischi le parole
 * dell'elenco delle parole vietate, senza distinguere maiuscole e
 * minuscole, e conta le sostituzioni.
 *
 * Per cercare senza distinguere maiuscole e minuscole si lavora su una
 * COPIA in minuscolo del messaggio. strstr trova la parola nella copia e
 * restituisce un puntatore; la posizione trovato - copia è la stessa nel
 * messaggio originale, quindi gli asterischi si scrivono a partire da
 * messaggio + (trovato - copia). La ricerca riprende da trovato + lunghezza.
 *
 * Il programma legge un messaggio per riga; una riga vuota termina.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LUNG     120
#define VIETATE  3
#define LUNG_PAROLA 12

int censura(char *messaggio, const char parole[][LUNG_PAROLA], int n);

int main(void)
{
    char vietate[VIETATE][LUNG_PAROLA] = {"scemo", "stupido", "idiota"};
    char messaggio[LUNG];
    char *a_capo;
    int continua = 1;
    int sostituite;
    int totale = 0;

    printf("=== CHAT DELLA 3A ===\n");
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
                sostituite = censura(messaggio, vietate, VIETATE);
                totale = totale + sostituite;
                printf("  pubblicato: %s", messaggio);
                if (sostituite > 0) {
                    printf("   (%d %s)", sostituite,
                           sostituite == 1 ? "parola filtrata" : "parole filtrate");
                }
                printf("\n");
            }
        }
    }
    printf("Parole filtrate nella sessione: %d\n", totale);

    return 0;
}

/* Sostituisce con '*' ogni occorrenza delle n parole vietate, senza
 * distinguere maiuscole e minuscole. Restituisce il numero di occorrenze. */
int censura(char *messaggio, const char parole[][LUNG_PAROLA], int n)
{
    char copia[LUNG];
    char *c;
    const char *m;
    const char *trovato;
    char *q;
    char *fine;
    int lunghezza;
    int i;
    int sostituite = 0;

    /* copia in minuscolo */
    c = copia;
    for (m = messaggio; *m != '\0'; m++) {
        *c = (char) tolower((unsigned char) *m);
        c++;
    }
    *c = '\0';

    for (i = 0; i < n; i++) {
        lunghezza = strlen(parole[i]);
        trovato = strstr(copia, parole[i]);
        while (trovato != NULL) {
            q = messaggio + (trovato - copia);
            fine = q + lunghezza;
            while (q < fine) {
                *q = '*';
                q++;
            }
            sostituite++;
            trovato = strstr(trovato + lunghezza, parole[i]);
        }
    }
    return sostituite;
}
