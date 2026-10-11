/*
 * 050-problema-anno-bisestile.c
 *
 * Verifica se un anno è bisestile
 *
 * Nel calendario gregoriano (in uso dal 1582) un anno è bisestile,
 * cioè ha 366 giorni con il 29 febbraio, secondo questa regola:
 *
 *   - è bisestile se è divisibile per 4,
 *   - ma NON se è divisibile per 100 (anni secolari),
 *   - tranne quando è divisibile anche per 400.
 *
 * Esempi: 2024 sì, 2023 no, 1900 no (secolare), 2000 sì (divisibile per 400).
 *
 * Il programma traduce la regola in una sola espressione logica,
 * costruita a partire da tre condizioni elementari, e mostra il valore
 * di ogni passaggio. Non usa if: l'esito viene stampato con l'operatore
 * ternario.
 */

#include <stdio.h>

int main(void)
{
    int anno;

    int divisibile_4;
    int divisibile_100;
    int divisibile_400;
    int bisestile;

    printf("=== ANNO BISESTILE ===\n\n");
    printf("Inserisci un anno (es. 2024): ");
    scanf("%d", &anno);

    /* ── Condizioni elementari ──────────────────────────────────────
     * "x è divisibile per n" si traduce con il resto della divisione:
     *     x % n == 0                                                   */
    divisibile_4   = (anno % 4   == 0);
    divisibile_100 = (anno % 100 == 0);
    divisibile_400 = (anno % 400 == 0);

    /* ── Composizione della regola ──────────────────────────────────
     * "divisibile per 4 ma non per 100"   ->  div4 && !div100
     * "tranne se divisibile per 400"      ->  ... || div400
     * L'eccezione si aggiunge con OR perché rende bisestile un anno
     * che la prima parte escluderebbe.                                 */
    bisestile = (divisibile_4 && !divisibile_100) || divisibile_400;

    printf("\n--- Passaggi della verifica ---\n");
    printf("  divisibile per 4   : %d\n", divisibile_4);
    printf("  divisibile per 100 : %d\n", divisibile_100);
    printf("  divisibile per 400 : %d\n", divisibile_400);
    printf("  (div4 && !div100)  : %d\n", divisibile_4 && !divisibile_100);
    printf("  || div400          : %d\n", bisestile);

    printf("\nIl %d %s bisestile: febbraio ha %d giorni.\n",
           anno,
           bisestile ? "e'" : "non e'",
           28 + bisestile);   /* bisestile vale 0 o 1: si può sommare */

    /*
     * ERRORE COMUNE: fermarsi alla prima parte della regola.
     *   bisestile = (anno % 4 == 0);
     * Questa versione sbaglia sugli anni secolari: 1900 risulterebbe
     * bisestile, ma non lo è.
     */

    return 0;
}
