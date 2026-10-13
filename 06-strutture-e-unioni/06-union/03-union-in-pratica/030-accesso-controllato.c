/*
 * 030-accesso-controllato.c
 *
 * Leggere un dato solo attraverso funzioni che controllano l'etichetta
 *
 * Chi legge direttamente d.reale deve ricordarsi di controllare prima
 * d.tipo. Si possono invece scrivere funzioni che fanno il controllo e
 * restituiscono un esito, con il valore in un parametro di uscita:
 *
 *     int come_intero(const Dato *d, int *risultato);
 *     int come_reale(const Dato *d, double *risultato);
 *
 * come_reale accetta anche un INTERO e lo converte: un intero è sempre
 * rappresentabile come reale. come_intero accetta un REALE solo se non
 * ha parte decimale (7.0 sì, 7.5 no). Un TESTO non è mai un numero.
 *
 *     if (come_reale(&d, &x)) {
 *         ... x è valido ...
 *     }
 *
 * Il chiamante non tocca mai la union: non può leggere il campo
 * sbagliato.
 *
 * Esempio: i valori letti da un modulo; il programma prova a usarli come
 * interi e come reali.
 */

#include <stdio.h>

#define VALORI 5

typedef enum {
    INTERO, REALE, TESTO
} TipoDato;

typedef struct {
    TipoDato tipo;
    union {
        int intero;
        double reale;
        char testo[12];
    };
} Dato;

int come_intero(const Dato *d, int *risultato);
int come_reale(const Dato *d, double *risultato);

int main(void)
{
    Dato valori[VALORI] = {
        {.tipo = INTERO, .intero = 12},
        {.tipo = REALE, .reale = 7.0},
        {.tipo = REALE, .reale = 7.5},
        {.tipo = TESTO, .testo = "dodici"},
        {.tipo = INTERO, .intero = -3}
    };
    int intero;
    double reale;
    int i;

    printf("valore  come intero  come reale\n");
    for (i = 0; i < VALORI; i++) {
        printf("  %d     ", i + 1);
        if (come_intero(&valori[i], &intero)) {
            printf("%-12d ", intero);
        } else {
            printf("%-12s ", "no");
        }
        if (come_reale(&valori[i], &reale)) {
            printf("%.2f\n", reale);
        } else {
            printf("no\n");
        }
    }

    return 0;
}

/* 1 se il dato è un intero, o un reale senza parte decimale. */
int come_intero(const Dato *d, int *risultato)
{
    int ok = 0;

    switch (d->tipo) {
    case INTERO:
        *risultato = d->intero;
        ok = 1;
        break;
    case REALE:
        ok = d->reale == (int) d->reale;
        if (ok) {
            *risultato = (int) d->reale;
        }
        break;
    case TESTO:
        break;
    }
    return ok;
}

/* 1 se il dato è un numero, intero o reale. */
int come_reale(const Dato *d, double *risultato)
{
    int ok = 1;

    switch (d->tipo) {
    case INTERO:
        *risultato = d->intero;
        break;
    case REALE:
        *risultato = d->reale;
        break;
    case TESTO:
        ok = 0;
        break;
    }
    return ok;
}
