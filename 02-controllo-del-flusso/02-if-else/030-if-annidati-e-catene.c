/*
 * 030-if-annidati-e-catene.c
 *
 * Più di due alternative: catene else-if e if annidati
 *
 * 1) CATENA else-if: le condizioni vengono provate dall'alto in basso e
 *    si esegue il PRIMO ramo con condizione vera; gli altri vengono saltati.
 *    L'else finale cattura tutti i casi rimasti.
 *
 *        if (c1) { ... }
 *        else if (c2) { ... }
 *        else if (c3) { ... }
 *        else { ... }
 *
 * 2) IF ANNIDATI: un if dentro il ramo di un altro if. Si usano quando
 *    una seconda domanda ha senso solo dopo aver risposto alla prima.
 *
 * 3) L'ambiguità dell'else (dangling else) e perché nel corso le graffe
 *    si scrivono sempre.
 */

#include <stdio.h>

int main(void)
{
    int punteggio = 78;
    int codice_utente = 1042;
    int pin = 1234;
    int pin_inserito = 1234;
    int saldo_punti = 30;
    int x = 5;

    /* ── 1. Catena else-if: punteggio -> fascia ───────────────────────
     * Grazie all'ordine dei controlli ogni condizione può essere
     * semplice: quando si arriva a "punteggio >= 70" si sa già che
     * il punteggio NON è >= 90.                                         */
    printf("=== Catena else-if ===\n");
    printf("Punteggio: %d/100\n", punteggio);

    if (punteggio >= 90) {
        printf("Fascia: ECCELLENTE\n");
    } else if (punteggio >= 70) {
        printf("Fascia: BUONO\n");
    } else if (punteggio >= 60) {
        printf("Fascia: SUFFICIENTE\n");
    } else {
        printf("Fascia: INSUFFICIENTE\n");
    }
    printf("\n");

    /* ── 2. If annidati: accesso a un'area riservata ──────────────────
     * Il PIN si controlla solo se l'utente esiste; il saldo punti
     * solo se il PIN è corretto. Ogni else risponde al proprio if.    */
    printf("=== If annidati ===\n");

    if (codice_utente == 1042) {
        printf("Utente %d riconosciuto.\n", codice_utente);

        if (pin_inserito == pin) {
            printf("PIN corretto.\n");

            if (saldo_punti >= 50) {
                printf("Premio disponibile.\n");
            } else {
                printf("Mancano %d punti al premio.\n", 50 - saldo_punti);
            }
        } else {
            printf("PIN errato.\n");
        }
    } else {
        printf("Utente sconosciuto.\n");
    }
    printf("\n");

    /* ── 3. Annidamento o condizione composta? ────────────────────────
     * Due if annidati SENZA else equivalgono a un solo if con &&.
     * La versione con && è più compatta e leggibile.                   */
    printf("=== Annidamento e && ===\n");

    if (codice_utente == 1042) {
        if (pin_inserito == pin) {
            printf("Accesso consentito (if annidati)\n");
        }
    }

    if (codice_utente == 1042 && pin_inserito == pin) {
        printf("Accesso consentito (condizione con &&)\n");
    }
    printf("\n");

    /* ── 4. Dangling else ─────────────────────────────────────────────
     * Senza graffe:
     *
     *     if (x > 0)
     *         if (x > 10)
     *             printf("grande\n");
     *     else
     *         printf("negativo o zero\n");
     *
     * L'indentazione fa pensare che l'else appartenga al primo if, ma il
     * C associa ogni else all'if PIÙ VICINO ancora senza else: il
     * secondo. Con x = 5 il programma stampa "negativo o zero"!
     * Le graffe eliminano ogni ambiguità.                               */
    printf("=== Graffe ed else ===\n");
    printf("x = %d\n", x);

    if (x > 0) {
        if (x > 10) {
            printf("grande\n");
        }
    } else {
        printf("negativo o zero\n");
    }
    printf("(con le graffe x = 5 non stampa nulla: e' positivo ma non grande)\n");

    /*
     * ERRORE COMUNE: catena con le condizioni nell'ordine sbagliato.
     *
     *     if (punteggio >= 60) {
     *         printf("SUFFICIENTE\n");
     *     } else if (punteggio >= 90) {     // non viene MAI raggiunto
     *         printf("ECCELLENTE\n");
     *     }
     *
     * Un punteggio di 95 soddisfa già la prima condizione: nella catena
     * si parte dalla condizione più restrittiva.
     */

    return 0;
}
