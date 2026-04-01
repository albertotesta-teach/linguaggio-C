/*
 * 030-commenti.c
 *
 * Tipi di commenti in C
 *
 * Illustra le due sintassi di commento disponibili in C (dal C99 in poi)
 * e le buone pratiche di documentazione del codice. Un codice ben commentato
 * è più facile da leggere, correggere e mantenere nel tempo.
 */

#include <stdio.h>

int main(void)
{
    int valore;   /* commento su riga singola: a fianco del codice */

    /* ── COMMENTO SU PIÙ RIGHE (stile C classico) ─────────────────────────
     * Inizia con  /*  e termina con  */
     * Può estendersi su quante righe si vuole.
     * Usato per intestazioni, spiegazioni lunghe e sezioni di codice. */

    // Commento a doppia barra: dal C99 in poi.
    // Va dalla doppia barra fino alla fine della riga.
    // Utile per note brevi o per commentare temporaneamente una riga.

    /* BUONE PRATICHE:
     * 1. Il commento spiega il PERCHÉ, non il COSA.
     *    Il codice stesso dice già cosa fa; il commento aggiunge il motivo.
     *
     *    Male:   valore = 10;   // assegna 10 a valore
     *    Bene:   valore = 10;   // valore iniziale di default per i nuovi utenti
     *
     * 2. Mantenere i commenti aggiornati: un commento sbagliato
     *    è peggio di nessun commento.
     *
     * 3. Non commentare codice ovvio: appesantisce la lettura.
     *
     * 4. Usare commenti per separare sezioni logiche del codice. */

    valore = 42;   /* valore scelto solo a scopo dimostrativo */

    printf("Il valore e': %d\n", valore);

    // Un commento a doppia barra può stare anche qui, su riga propria.

    return 0;
}
