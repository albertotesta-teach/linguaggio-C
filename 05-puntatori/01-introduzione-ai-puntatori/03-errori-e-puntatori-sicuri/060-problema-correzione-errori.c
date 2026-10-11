/*
 * 060-problema-correzione-errori.c
 *
 * Quattro errori con i puntatori e la loro correzione
 *
 * Uno studente ha scritto un programma che calcola lo sconto per i soci di
 * una palestra, ma il programma a volte si blocca e a volte stampa valori
 * assurdi. Il docente individua quattro errori tipici con i puntatori.
 * Per ognuno, nel commento c'è il codice SBAGLIATO (non eseguito, perché
 * il comportamento sarebbe imprevedibile) e sotto la versione CORRETTA.
 *
 *   Errore 1  scanf senza &                (scrive in un punto casuale)
 *   Errore 2  puntatore non inizializzato  (scrive in un punto casuale)
 *   Errore 3  dereferenziazione di NULL    (il programma si interrompe)
 *   Errore 4  puntatore a una variabile che non esiste più: l'indirizzo
 *             di una variabile dichiarata dentro un blocco { } non è più
 *             valido quando il blocco termina
 *
 * Il programma corretto chiede gli anni di iscrizione del socio e calcola
 * il prezzo dell'abbonamento con lo sconto.
 */

#include <stdio.h>

#define PREZZO_BASE 400                 /* euro all'anno */

int main(void)
{
    int anni = 0;
    int sconto = 0;
    int prezzo;
    int *percentuale = NULL;
    int *da_applicare = NULL;

    /* ── Errore 1 ─────────────────────────────────────────────────────
     * SBAGLIATO:  scanf("%d", anni);
     * scanf riceve il valore di anni (0) come se fosse un indirizzo.     */
    printf("Anni di iscrizione: ");
    if (scanf("%d", &anni) != 1 || anni < 0) {
        anni = 0;
    }

    /* ── Errore 2 ─────────────────────────────────────────────────────
     * SBAGLIATO:  int *percentuale;  *percentuale = 10;
     * percentuale non punta a nessuna variabile.                         */
    percentuale = &sconto;
    if (anni >= 5) {
        *percentuale = 20;
    } else if (anni >= 2) {
        *percentuale = 10;
    }

    /* ── Errore 3 ─────────────────────────────────────────────────────
     * SBAGLIATO:  prezzo = PREZZO_BASE - PREZZO_BASE * (*da_applicare) / 100;
     * con da_applicare ancora uguale a NULL.                             */
    if (anni > 0) {
        da_applicare = percentuale;     /* lo sconto vale solo per chi è già socio */
    }
    if (da_applicare != NULL) {
        prezzo = PREZZO_BASE - PREZZO_BASE * (*da_applicare) / 100;
    } else {
        prezzo = PREZZO_BASE;
    }

    /* ── Errore 4 ─────────────────────────────────────────────────────
     * SBAGLIATO:
     *     {
     *         int promozione = 15;
     *         da_applicare = &promozione;
     *     }
     *     prezzo = prezzo - *da_applicare;     promozione non esiste più
     * CORRETTO: la variabile deve esistere finché si usa il puntatore,
     * quindi si dichiara fuori dal blocco (qui basta usare il valore).    */
    if (anni >= 10) {
        prezzo = prezzo - 15;           /* promozione fedeltà */
    }

    printf("Socio da %d anni: sconto %d%%, prezzo %d euro\n", anni, sconto, prezzo);
    if (anni >= 10) {
        printf("(compresa la promozione fedelta' di 15 euro)\n");
    }

    return 0;
}
