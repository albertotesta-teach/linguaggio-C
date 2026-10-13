/*
 * 060-problema-pagamenti-bar.c
 *
 * Il bar della scuola: pagamenti in contanti, con carta o con buono
 *
 * Ogni pagamento ha un importo e dati diversi secondo il metodo:
 *   - contanti: la somma consegnata (per calcolare il resto);
 *   - carta: le ultime 4 cifre della carta;
 *   - buono pasto: il codice del buono, che vale fino a 5 euro e non dà
 *     resto.
 *
 *     typedef struct {
 *         Metodo metodo;
 *         double importo;
 *         union {
 *             double consegnato;
 *             char ultime_cifre[5];
 *             char codice_buono[8];
 *         } dati;
 *     } Pagamento;
 *
 * Il programma legge i pagamenti fino a FINE:
 *     C importo consegnato        contanti
 *     K importo cifre             carta
 *     B importo codice            buono
 * controlla ognuno (consegnato sufficiente, 4 cifre, importo coperto dal
 * buono), stampa la ricevuta e alla fine il totale per metodo con un
 * array indicizzato dall'enum.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define VALORE_BUONO 5.00

typedef enum {
    CONTANTI, CARTA, BUONO, NUM_METODI
} Metodo;

typedef struct {
    Metodo metodo;
    double importo;
    union {
        double consegnato;
        char ultime_cifre[5];
        char codice_buono[8];
    } dati;
} Pagamento;

int leggi_pagamento(Pagamento *p);
int valido(const Pagamento *p);
void ricevuta(const Pagamento *p);

int main(void)
{
    const char *nomi[NUM_METODI] = {[CONTANTI] = "contanti", [CARTA] = "carta",
                                    [BUONO] = "buono"};
    double totali[NUM_METODI] = {0};
    int quanti[NUM_METODI] = {0};
    Pagamento p;
    int esito = 1;
    Metodo m;

    while (esito != 0) {
        printf("Pagamento (C importo consegnato, K importo cifre, B importo codice, FINE): ");
        esito = leggi_pagamento(&p);
        if (esito == -1) {
            printf("  Pagamento non riconosciuto.\n");
        } else if (esito == 1 && !valido(&p)) {
            printf("  Pagamento rifiutato.\n");
        } else if (esito == 1) {
            ricevuta(&p);
            totali[p.metodo] = totali[p.metodo] + p.importo;
            quanti[p.metodo]++;
        }
    }

    printf("\nIncassi del giorno\n");
    for (m = CONTANTI; m < NUM_METODI; m++) {
        printf("  %-9s pagamenti %2d  %7.2f euro\n", nomi[m], quanti[m], totali[m]);
    }

    return 0;
}

/* 1 letto, 0 FINE o dati mancanti, -1 metodo sconosciuto. */
int leggi_pagamento(Pagamento *p)
{
    char lettera[8];
    char cifre[8];
    int esito = -1;

    if (scanf("%7s", lettera) != 1 || strcmp(lettera, "FINE") == 0) {
        esito = 0;
    } else if (strcmp(lettera, "C") == 0) {
        p->metodo = CONTANTI;
        esito = scanf("%lf %lf", &p->importo, &p->dati.consegnato) == 2;
    } else if (strcmp(lettera, "K") == 0) {
        p->metodo = CARTA;
        esito = scanf("%lf %7s", &p->importo, cifre) == 2;
        if (esito) {
            /* più di 4 caratteri: campo vuoto, il controllo lo rifiuterà */
            strcpy(p->dati.ultime_cifre, strlen(cifre) <= 4 ? cifre : "");
        }
    } else if (strcmp(lettera, "B") == 0) {
        p->metodo = BUONO;
        esito = scanf("%lf %7s", &p->importo, p->dati.codice_buono) == 2;
    }
    return esito;
}

int valido(const Pagamento *p)
{
    int ok = p->importo > 0;
    int i;

    switch (p->metodo) {
    case CONTANTI:
        ok = ok && p->dati.consegnato >= p->importo;
        break;
    case CARTA:
        ok = ok && strlen(p->dati.ultime_cifre) == 4;
        for (i = 0; i < 4 && ok; i++) {
            ok = isdigit((unsigned char) p->dati.ultime_cifre[i]);
        }
        break;
    case BUONO:
        ok = ok && p->importo <= VALORE_BUONO && strncmp(p->dati.codice_buono, "BU-", 3) == 0;
        break;
    case NUM_METODI:
        ok = 0;
        break;
    }
    return ok;
}

void ricevuta(const Pagamento *p)
{
    printf("  %.2f euro ", p->importo);
    switch (p->metodo) {
    case CONTANTI:
        printf("in contanti, resto %.2f\n", p->dati.consegnato - p->importo);
        break;
    case CARTA:
        printf("con carta **** %s\n", p->dati.ultime_cifre);
        break;
    case BUONO:
        printf("con buono %s (non da' resto)\n", p->dati.codice_buono);
        break;
    case NUM_METODI:
        break;
    }
}
