/*
 * 040-problema-saluto-personalizzato.c
 *
 * Saluto personalizzato con data
 *
 * Il programma chiede all'utente di inserire il giorno, il mese e l'anno
 * di nascita e l'anno corrente, quindi calcola l'età e stampa un messaggio
 * di saluto formattato. Ogni dato è un numero intero: non si usano stringhe
 * né array, coerentemente con i vincoli del capitolo 01-introduzione.
 */

#include <stdio.h>

int main(void)
{
    /* dati inseriti dall'utente */
    int giorno_nascita;
    int mese_nascita;
    int anno_nascita;
    int anno_corrente;

    /* dati calcolati */
    int eta;

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Saluto personalizzato ===\n\n");

    printf("Giorno di nascita (1-31): ");
    scanf("%d", &giorno_nascita);

    printf("Mese di nascita  (1-12): ");
    scanf("%d", &mese_nascita);

    printf("Anno di nascita:         ");
    scanf("%d", &anno_nascita);

    printf("Anno corrente:           ");
    scanf("%d", &anno_corrente);

    /* ── elaborazione ───────────────────────────────────────────────────── */

    /* calcolo approssimato dell'età: non tiene conto del giorno esatto
     * (se il compleanno di quest'anno è già passato o meno).
     * Una stima semplice è sufficiente per questo esempio introduttivo. */
    eta = anno_corrente - anno_nascita;

    /* ── output ─────────────────────────────────────────────────────────── */
    printf("\n--- Riepilogo ---\n");
    printf("Data di nascita: %02d/%02d/%d\n", giorno_nascita, mese_nascita, anno_nascita);
    printf("Anno corrente:   %d\n", anno_corrente);
    printf("Eta' stimata:    %d anni\n", eta);
    printf("\nBenvenuto! Hai circa %d anni.\n", eta);

    return 0;
}
