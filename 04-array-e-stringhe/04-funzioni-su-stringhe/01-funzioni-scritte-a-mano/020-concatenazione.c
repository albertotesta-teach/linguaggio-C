/*
 * 020-concatenazione.c
 *
 * Concatenare due stringhe con una funzione scritta a mano
 *
 * Concatenare significa aggiungere una stringa in coda a un'altra:
 *
 *     dest = "Buon"      sorg = "giorno"     ->   dest = "Buongiorno"
 *
 * Il procedimento ha due fasi:
 *   1. trovare la fine di dest, cioè la posizione del suo '\0';
 *   2. copiare da lì i caratteri di sorg, terminatore compreso.
 * Il vecchio '\0' di dest viene sovrascritto dal primo carattere di sorg.
 *
 *   concatena(dest, sorg)            versione semplice
 *   concatena_limitata(dest, sorg, dim)
 *                                    non supera la dimensione di dest
 *
 * Esempio: un sistema di prenotazione compone un messaggio di conferma
 * a partire da più pezzi.
 */

#include <stdio.h>

#define DIM_MESSAGGIO 60
#define DIM_SMS       25

int lunghezza(const char s[]);
void copia(char dest[], const char sorg[]);
void concatena(char dest[], const char sorg[]);
void concatena_limitata(char dest[], const char sorg[], int dim);

int main(void)
{
    char messaggio[DIM_MESSAGGIO];
    char sms[DIM_SMS];
    char nome[] = "Giulia";
    char giorno[] = "venerdi'";
    char ora[] = "20:30";

    /* ── 1. Composizione per passi ────────────────────────────────── */
    printf("=== COMPOSIZIONE DEL MESSAGGIO ===\n");
    copia(messaggio, "Ciao ");
    printf("  passo 1: \"%s\"\n", messaggio);
    concatena(messaggio, nome);
    printf("  passo 2: \"%s\"\n", messaggio);
    concatena(messaggio, ", tavolo prenotato per ");
    printf("  passo 3: \"%s\"\n", messaggio);
    concatena(messaggio, giorno);
    concatena(messaggio, " alle ");
    concatena(messaggio, ora);
    printf("  finale : \"%s\"\n", messaggio);
    printf("  lunghezza %d, spazio disponibile %d celle\n\n",
           lunghezza(messaggio), DIM_MESSAGGIO);

    /* ── 2. Concatenazione limitata ───────────────────────────────── */
    printf("=== VERSIONE BREVE (massimo %d caratteri) ===\n", DIM_SMS - 1);
    copia(sms, "Ciao ");
    concatena_limitata(sms, nome, DIM_SMS);
    concatena_limitata(sms, ", tavolo prenotato per ", DIM_SMS);
    concatena_limitata(sms, giorno, DIM_SMS);
    printf("  \"%s\" (%d caratteri)\n", sms, lunghezza(sms));
    printf("  Il testo e' stato troncato: concatena() avrebbe scritto\n");
    printf("  oltre la fine dell'array sms.\n");

    return 0;
}

int lunghezza(const char s[])
{
    int n = 0;

    while (s[n] != '\0') {
        n++;
    }
    return n;
}

void copia(char dest[], const char sorg[])
{
    int i = 0;

    while (sorg[i] != '\0') {
        dest[i] = sorg[i];
        i++;
    }
    dest[i] = '\0';
}

/* Aggiunge sorg in coda a dest. dest deve avere spazio per
 * lunghezza(dest) + lunghezza(sorg) + 1 caratteri. */
void concatena(char dest[], const char sorg[])
{
    int fine;
    int i = 0;

    fine = lunghezza(dest);             /* 1. posizione del '\0' di dest */
    while (sorg[i] != '\0') {           /* 2. copia di sorg da quel punto */
        dest[fine + i] = sorg[i];
        i++;
    }
    dest[fine + i] = '\0';
}

/* Come concatena, ma il risultato non supera dim - 1 caratteri
 * (dim = dimensione dell'array dest). */
void concatena_limitata(char dest[], const char sorg[], int dim)
{
    int fine;
    int i = 0;

    fine = lunghezza(dest);
    while (sorg[i] != '\0' && fine + i < dim - 1) {
        dest[fine + i] = sorg[i];
        i++;
    }
    dest[fine + i] = '\0';
}
