/*
 * 060-problema-calcolatrice-operazioni.c
 *
 * Calcolatrice a parole per il corso di recupero di matematica
 *
 * L'operazione si scrive come parola, seguita dai due numeri interi:
 *
 *     somma 12 30        differenza 5 9        prodotto 7 6
 *     quoziente 17 5     resto 17 5            potenza 2 10
 *
 * La parola diventa un enum con una tabella di nomi, e lo switch sceglie
 * il calcolo:
 *
 *     typedef enum {
 *         SOMMA, DIFFERENZA, PRODOTTO, QUOZIENTE, RESTO, POTENZA,
 *         NUM_OPERAZIONI, NON_VALIDA
 *     } Operazione;
 *
 *     Operazione da_testo(const char *parola);
 *     int calcola(Operazione op, int a, int b, int *risultato);
 *
 * calcola restituisce 0 se l'operazione non si può fare: divisione o
 * resto per zero, esponente negativo. Il quoziente è quello intero.
 * FINE termina.
 */

#include <stdio.h>
#include <string.h>

typedef enum {
    SOMMA, DIFFERENZA, PRODOTTO, QUOZIENTE, RESTO, POTENZA,
    NUM_OPERAZIONI,
    NON_VALIDA
} Operazione;

Operazione da_testo(const char *parola);
int calcola(Operazione op, int a, int b, int *risultato);
void svuota_riga(void);

int main(void)
{
    char parola[16];
    int a;
    int b;
    int risultato;
    Operazione op;
    int finito = 0;

    while (!finito) {
        printf("Operazione e due numeri (FINE): ");
        if (scanf("%15s", parola) != 1 || strcmp(parola, "FINE") == 0) {
            finito = 1;
        } else if (scanf("%d %d", &a, &b) != 2) {
            printf("  Servono due numeri interi.\n");
        } else {
            op = da_testo(parola);
            if (op == NON_VALIDA) {
                printf("  Operazione \"%s\" sconosciuta.\n", parola);
            } else if (!calcola(op, a, b, &risultato)) {
                printf("  %s di %d e %d: impossibile.\n", parola, a, b);
            } else {
                printf("  %s di %d e %d = %d\n", parola, a, b, risultato);
            }
        }
        if (!finito) {
            svuota_riga();              /* un'operazione per riga */
        }
    }

    return 0;
}

Operazione da_testo(const char *parola)
{
    const char *nomi[NUM_OPERAZIONI] = {
        [SOMMA] = "somma", [DIFFERENZA] = "differenza", [PRODOTTO] = "prodotto",
        [QUOZIENTE] = "quoziente", [RESTO] = "resto", [POTENZA] = "potenza"
    };
    Operazione trovata = NON_VALIDA;
    Operazione op = SOMMA;

    while (op < NUM_OPERAZIONI && trovata == NON_VALIDA) {
        if (strcmp(nomi[op], parola) == 0) {
            trovata = op;
        }
        op++;
    }
    return trovata;
}

int calcola(Operazione op, int a, int b, int *risultato)
{
    int possibile = 1;
    int i;

    switch (op) {
    case SOMMA:
        *risultato = a + b;
        break;
    case DIFFERENZA:
        *risultato = a - b;
        break;
    case PRODOTTO:
        *risultato = a * b;
        break;
    case QUOZIENTE:
    case RESTO:
        possibile = b != 0;
        if (possibile) {
            *risultato = op == QUOZIENTE ? a / b : a % b;
        }
        break;
    case POTENZA:
        possibile = b >= 0;
        *risultato = 1;
        for (i = 0; i < b; i++) {
            *risultato = *risultato * a;
        }
        break;
    case NUM_OPERAZIONI:
    case NON_VALIDA:
        possibile = 0;
        break;
    }
    return possibile;
}

/* Scarta i caratteri rimasti sulla riga. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
