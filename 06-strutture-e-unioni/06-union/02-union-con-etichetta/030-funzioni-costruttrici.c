/*
 * 030-funzioni-costruttrici.c
 *
 * Funzioni che costruiscono un dato con l'etichetta giusta
 *
 * Scrivere a mano etichetta e campo in due istruzioni separate è un
 * invito all'errore: basta dimenticare una delle due righe, o scrivere
 * l'etichetta sbagliata.
 *
 *     d.tipo = INTERO;
 *     d.v.reale = 2.5;           etichetta e campo non corrispondono
 *
 * Si scrive allora una funzione per ogni tipo, che restituisce un Dato
 * già coerente:
 *
 *     Dato crea_intero(int valore);
 *     Dato crea_reale(double valore);
 *     Dato crea_testo(const char *valore);
 *
 *     elenco[0] = crea_reale(36.6);
 *
 * Fuori da queste funzioni nessuno scrive direttamente nella union.
 * crea_testo copia al massimo 15 caratteri e chiude sempre la stringa,
 * così anche un testo troppo lungo non esce dal campo.
 *
 * Esempio: la scheda di un esperimento di chimica, con valori di tipo
 * diverso.
 */

#include <stdio.h>
#include <string.h>

#define CAMPI 5
#define LUNG_TESTO 16

typedef enum {
    INTERO, REALE, TESTO
} TipoDato;

typedef struct {
    TipoDato tipo;
    union {
        int intero;
        double reale;
        char testo[LUNG_TESTO];
    } v;
} Dato;

Dato crea_intero(int valore);
Dato crea_reale(double valore);
Dato crea_testo(const char *valore);
void stampa(const Dato *d);

int main(void)
{
    const char *etichette[CAMPI] = {"gruppo", "reagente", "temperatura", "provette",
                                    "osservazioni"};
    Dato scheda[CAMPI];
    int i;

    scheda[0] = crea_intero(4);
    scheda[1] = crea_testo("solfato di rame");
    scheda[2] = crea_reale(21.5);
    scheda[3] = crea_intero(6);
    scheda[4] = crea_testo("precipitato azzurro chiaro");

    for (i = 0; i < CAMPI; i++) {
        printf("  %-13s ", etichette[i]);
        stampa(&scheda[i]);
        printf("\n");
    }

    return 0;
}

Dato crea_intero(int valore)
{
    Dato d;

    d.tipo = INTERO;
    d.v.intero = valore;
    return d;
}

Dato crea_reale(double valore)
{
    Dato d;

    d.tipo = REALE;
    d.v.reale = valore;
    return d;
}

/* Copia al massimo LUNG_TESTO - 1 caratteri e termina la stringa. */
Dato crea_testo(const char *valore)
{
    Dato d;

    d.tipo = TESTO;
    strncpy(d.v.testo, valore, LUNG_TESTO - 1);
    d.v.testo[LUNG_TESTO - 1] = '\0';
    return d;
}

void stampa(const Dato *d)
{
    switch (d->tipo) {
    case INTERO:
        printf("(intero) %d", d->v.intero);
        break;
    case REALE:
        printf("(reale)  %.1f", d->v.reale);
        break;
    case TESTO:
        printf("(testo)  \"%s\"", d->v.testo);
        break;
    }
}
