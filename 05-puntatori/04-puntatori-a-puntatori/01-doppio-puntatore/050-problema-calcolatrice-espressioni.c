/*
 * 050-problema-calcolatrice-espressioni.c
 *
 * Calcolatrice per le spese di classe
 *
 * Il tesoriere di classe scrive le entrate e le uscite della cassa come
 * un'unica espressione di somme e sottrazioni, ad esempio
 *     150 + 35 - 48 + 20 - 12
 * Il programma calcola il risultato. Se l'espressione è scritta male
 * indica in che punto si trova l'errore.
 *
 * Due funzioni leggono dalla stessa stringa e fanno avanzare lo stesso
 * puntatore di lettura (const char **):
 *     leggi_numero(&p, &n)      legge un numero
 *     leggi_operatore(&p, &op)  legge + o -
 * valuta alterna le due letture: numero, operatore, numero, ...
 * Restituisce 1 se l'espressione è corretta e scrive il risultato in
 * *risultato; altrimenti restituisce 0 e scrive in *errore la posizione
 * del problema.
 *
 * Il programma legge un'espressione per riga; una riga vuota termina.
 */

#include <stdio.h>
#include <string.h>

#define LUNG 100

int leggi_numero(const char **p, int *numero);
int leggi_operatore(const char **p, char *op);
void salta_spazi(const char **p);
int valuta(const char *testo, int *risultato, int *errore);

int main(void)
{
    char riga[LUNG];
    char *a_capo;
    int risultato;
    int errore;
    int c;
    int continua = 1;

    printf("=== CASSA DI CLASSE ===\n");
    while (continua) {
        printf("Espressione (riga vuota per finire): ");
        if (fgets(riga, LUNG, stdin) == NULL) {
            continua = 0;
        } else {
            a_capo = strchr(riga, '\n');
            if (a_capo != NULL) {
                *a_capo = '\0';
            } else {
                /* riga più lunga del buffer: il resto si scarta */
                c = getchar();
                while (c != '\n' && c != EOF) {
                    c = getchar();
                }
            }
            if (riga[0] == '\0') {
                continua = 0;
            } else if (valuta(riga, &risultato, &errore)) {
                printf("  = %d euro\n", risultato);
            } else {
                printf("  %s\n  %*s^ errore qui\n", riga, errore, "");
            }
        }
    }

    return 0;
}

void salta_spazi(const char **p)
{
    while (**p == ' ') {
        (*p)++;
    }
}

/* Legge un numero intero e sposta *p dopo l'ultima cifra; 1 se riuscita. */
int leggi_numero(const char **p, int *numero)
{
    int letto = 0;

    salta_spazi(p);
    *numero = 0;
    while (**p >= '0' && **p <= '9') {
        *numero = *numero * 10 + (**p - '0');
        (*p)++;
        letto = 1;
    }
    return letto;
}

/* Legge + o - e sposta *p dopo l'operatore; 1 se riuscita. */
int leggi_operatore(const char **p, char *op)
{
    int letto = 0;

    salta_spazi(p);
    if (**p == '+' || **p == '-') {
        *op = **p;
        (*p)++;
        letto = 1;
    }
    return letto;
}

/* Valuta testo: numero (operatore numero)*. In caso di errore scrive in
 * *errore la posizione in cui la lettura si è fermata. */
int valuta(const char *testo, int *risultato, int *errore)
{
    const char *p = testo;
    int valore;
    char op;
    int corretta = leggi_numero(&p, risultato);

    while (corretta && *p != '\0') {
        if (leggi_operatore(&p, &op) && leggi_numero(&p, &valore)) {
            if (op == '+') {
                *risultato = *risultato + valore;
            } else {
                *risultato = *risultato - valore;
            }
            salta_spazi(&p);
        } else {
            corretta = 0;
        }
    }
    *errore = p - testo;
    return corretta;
}
