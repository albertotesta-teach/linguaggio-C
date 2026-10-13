/*
 * 020-switch-sull-etichetta.c
 *
 * Uno switch sull'etichetta per ogni operazione
 *
 * Con una union etichettata ogni operazione ha la stessa forma: uno
 * switch sull'etichetta, con un case per ogni tipo, che usa solo il
 * campo valido.
 *
 *     void stampa(const Dato *d)
 *     {
 *         switch (d->tipo) {
 *         case INTERO:  printf("%d", d->v.intero);   break;
 *         case REALE:   printf("%g", d->v.reale);    break;
 *         case TESTO:   printf("%s", d->v.testo);    break;
 *         }
 *     }
 *
 * Come per ogni switch su un enum (05-enum), con -Wall il compilatore
 * segnala i case mancanti: se si aggiunge un tipo, indica tutte le
 * operazioni da aggiornare.
 *
 * Due dati sono uguali se hanno la stessa etichetta e, per quel tipo,
 * lo stesso valore: il confronto dipende dal tipo (== per i numeri,
 * strcmp per i testi). Confrontare i byte della union non funziona,
 * perché i byte non usati dal campo valido contengono valori casuali.
 *
 * Esempio: le risposte di due studenti allo stesso questionario.
 */

#include <stdio.h>
#include <string.h>

#define DOMANDE 4

typedef enum {
    INTERO, REALE, TESTO
} TipoDato;

typedef struct {
    TipoDato tipo;
    union {
        int intero;
        double reale;
        char testo[16];
    } v;
} Dato;

void stampa(const Dato *d);
int uguali(const Dato *a, const Dato *b);

int main(void)
{
    Dato anna[DOMANDE] = {
        {INTERO, {.intero = 3}}, {REALE, {.reale = 9.81}}, {TESTO, {.testo = "Volta"}},
        {INTERO, {.intero = 1861}}
    };
    Dato luca[DOMANDE] = {
        {INTERO, {.intero = 3}}, {REALE, {.reale = 9.8}}, {TESTO, {.testo = "Volta"}},
        {TESTO, {.testo = "1861"}}
    };
    int i;

    for (i = 0; i < DOMANDE; i++) {
        printf("domanda %d:  ", i + 1);
        stampa(&anna[i]);
        printf("  /  ");
        stampa(&luca[i]);
        printf("  -> %s\n", uguali(&anna[i], &luca[i]) ? "uguali" : "diverse");
    }

    return 0;
}

void stampa(const Dato *d)
{
    switch (d->tipo) {
    case INTERO:
        printf("%d", d->v.intero);
        break;
    case REALE:
        printf("%g", d->v.reale);
        break;
    case TESTO:
        printf("\"%s\"", d->v.testo);
        break;
    }
}

/* Stessa etichetta e stesso valore, confrontato secondo il tipo. */
int uguali(const Dato *a, const Dato *b)
{
    int risultato = a->tipo == b->tipo;

    if (risultato) {
        switch (a->tipo) {
        case INTERO:
            risultato = a->v.intero == b->v.intero;
            break;
        case REALE:
            risultato = a->v.reale == b->v.reale;
            break;
        case TESTO:
            risultato = strcmp(a->v.testo, b->v.testo) == 0;
            break;
        }
    }
    return risultato;
}
