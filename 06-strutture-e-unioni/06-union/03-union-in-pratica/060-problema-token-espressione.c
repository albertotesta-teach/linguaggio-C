/*
 * 060-problema-token-espressione.c
 *
 * Calcolatrice per le verifiche di matematica: espressioni con
 * precedenza e parentesi
 *
 * Il programma legge un'espressione (per esempio 2 * (3 + 4.5) - 1) e
 * la divide in token. Ogni token è un numero, un operatore o una
 * parentesi:
 *
 *     typedef struct {
 *         TipoToken tipo;
 *         union {
 *             double numero;            per NUMERO
 *             char simbolo;             per OPERATORE e PARENTESI
 *         };
 *     } Token;
 *
 * Il calcolo segue le regole dell'aritmetica con tre funzioni
 * ricorsive, una per livello di precedenza:
 *
 *     espressione = termine { (+ | -) termine }
 *     termine     = fattore { (* | /) fattore }
 *     fattore     = numero | ( espressione )
 *
 * Ogni funzione consuma i token che le spettano avanzando l'indice
 * *pos, e azzera *ok se trova un errore (token mancante, parentesi non
 * chiusa, divisione per zero). FINE termina.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_TOKEN 40
#define LUNG 80

typedef enum {
    NUMERO, OPERATORE, PARENTESI
} TipoToken;

typedef struct {
    TipoToken tipo;
    union {
        double numero;
        char simbolo;
    };
} Token;

int dividi_in_token(const char *testo, Token token[], int massimo);
double espressione(const Token t[], int n, int *pos, int *ok);
double termine(const Token t[], int n, int *pos, int *ok);
double fattore(const Token t[], int n, int *pos, int *ok);

int main(void)
{
    Token token[MAX_TOKEN];
    char riga[LUNG];
    int n;
    int pos;
    int ok;
    double risultato;
    int finito = 0;

    while (!finito) {
        printf("Espressione (FINE): ");
        if (fgets(riga, LUNG, stdin) == NULL) {
            finito = 1;
        } else {
            riga[strcspn(riga, "\n")] = '\0';
            if (strcmp(riga, "FINE") == 0) {
                finito = 1;
            } else {
                n = dividi_in_token(riga, token, MAX_TOKEN);
                pos = 0;
                ok = n > 0;
                risultato = espressione(token, n, &pos, &ok);
                if (ok && pos == n) {
                    printf("  = %g  (%d token)\n", risultato, n);
                } else {
                    printf("  Espressione non valida.\n");
                }
            }
        }
    }

    return 0;
}

/* Restituisce il numero di token, -1 per un carattere non ammesso. */
int dividi_in_token(const char *testo, Token token[], int massimo)
{
    char *fine;
    int n = 0;
    int i = 0;

    while (testo[i] != '\0' && n >= 0 && n < massimo) {
        if (isdigit((unsigned char) testo[i]) || testo[i] == '.') {
            token[n].tipo = NUMERO;
            token[n].numero = strtod(testo + i, &fine);
            i = (int) (fine - testo);
            n++;
        } else if (strchr("+-*/", testo[i]) != NULL) {
            token[n].tipo = OPERATORE;
            token[n].simbolo = testo[i];
            n++;
            i++;
        } else if (testo[i] == '(' || testo[i] == ')') {
            token[n].tipo = PARENTESI;
            token[n].simbolo = testo[i];
            n++;
            i++;
        } else if (testo[i] == ' ') {
            i++;
        } else {
            n = -1;
        }
    }
    return n;
}

double espressione(const Token t[], int n, int *pos, int *ok)
{
    double valore = termine(t, n, pos, ok);
    char operatore;

    while (*ok && *pos < n && t[*pos].tipo == OPERATORE &&
           (t[*pos].simbolo == '+' || t[*pos].simbolo == '-')) {
        operatore = t[*pos].simbolo;
        (*pos)++;
        if (operatore == '+') {
            valore = valore + termine(t, n, pos, ok);
        } else {
            valore = valore - termine(t, n, pos, ok);
        }
    }
    return valore;
}

double termine(const Token t[], int n, int *pos, int *ok)
{
    double valore = fattore(t, n, pos, ok);
    double divisore;
    char operatore;

    while (*ok && *pos < n && t[*pos].tipo == OPERATORE &&
           (t[*pos].simbolo == '*' || t[*pos].simbolo == '/')) {
        operatore = t[*pos].simbolo;
        (*pos)++;
        if (operatore == '*') {
            valore = valore * fattore(t, n, pos, ok);
        } else {
            divisore = fattore(t, n, pos, ok);
            if (divisore == 0) {
                *ok = 0;
            } else {
                valore = valore / divisore;
            }
        }
    }
    return valore;
}

double fattore(const Token t[], int n, int *pos, int *ok)
{
    double valore = 0;

    if (*pos >= n) {
        *ok = 0;
    } else if (t[*pos].tipo == NUMERO) {
        valore = t[*pos].numero;
        (*pos)++;
    } else if (t[*pos].tipo == PARENTESI && t[*pos].simbolo == '(') {
        (*pos)++;
        valore = espressione(t, n, pos, ok);
        if (*ok && *pos < n && t[*pos].tipo == PARENTESI && t[*pos].simbolo == ')') {
            (*pos)++;
        } else {
            *ok = 0;
        }
    } else {
        *ok = 0;
    }
    return valore;
}
