/*
 * 020-tavole-di-verita.c
 *
 * Gli operatori logici e le loro tavole di verità
 *
 * Una TAVOLA DI VERITÀ elenca tutte le combinazioni possibili dei valori
 * di ingresso (0/1) e, per ciascuna, il risultato dell'operatore.
 * Con due ingressi le combinazioni sono 4: 00, 01, 10, 11.
 *
 *   NOT  !a      vero se a è falso
 *   AND  a && b  vero solo se a e b sono entrambi veri
 *   OR   a || b  vero se almeno uno tra a e b è vero
 *   XOR          vero se esattamente uno tra a e b è vero
 *                (in C non esiste un operatore logico XOR: si costruisce)
 *
 * Ogni riga della tavola viene calcolata davvero dal programma: i valori
 * stampati sono il risultato delle espressioni, non numeri scritti a mano.
 * Le righe sono scritte una per una perché i cicli verranno introdotti
 * più avanti nel capitolo.
 */

#include <stdio.h>

int main(void)
{
    /* ── NOT ─────────────────────────────────────────────────────────── */
    printf("=== NOT (!) ===\n");
    printf("  a | !a\n");
    printf("  --+---\n");
    printf("  %d |  %d\n", 0, !0);
    printf("  %d |  %d\n", 1, !1);
    printf("\n");

    /* ── AND ─────────────────────────────────────────────────────────── */
    /* Basta un solo ingresso falso per rendere falso il risultato. */
    printf("=== AND (&&) ===\n");
    printf("  a b | a && b\n");
    printf("  ----+-------\n");
    printf("  %d %d |   %d\n", 0, 0, 0 && 0);
    printf("  %d %d |   %d\n", 0, 1, 0 && 1);
    printf("  %d %d |   %d\n", 1, 0, 1 && 0);
    printf("  %d %d |   %d\n", 1, 1, 1 && 1);
    printf("\n");

    /* ── OR ──────────────────────────────────────────────────────────── */
    /* Basta un solo ingresso vero per rendere vero il risultato.
     * Attenzione: l'OR logico è "inclusivo", quindi 1 || 1 vale 1. */
    printf("=== OR (||) ===\n");
    printf("  a b | a || b\n");
    printf("  ----+-------\n");
    printf("  %d %d |   %d\n", 0, 0, 0 || 0);
    printf("  %d %d |   %d\n", 0, 1, 0 || 1);
    printf("  %d %d |   %d\n", 1, 0, 1 || 0);
    printf("  %d %d |   %d\n", 1, 1, 1 || 1);
    printf("\n");

    /* ── XOR (OR esclusivo) ──────────────────────────────────────────── */
    /* Corrisponde all'"o... o..." della lingua italiana:
     * "o prendi il primo o il secondo, ma non tutti e due".
     *
     * Due modi per ottenerlo in C:
     *   1) dalla definizione:  (a || b) && !(a && b)
     *      "almeno uno vero, ma non entrambi"
     *   2) su valori booleani (solo 0 o 1):  a != b
     *      "i due valori sono diversi"
     */
    printf("=== XOR (o esclusivo) ===\n");
    printf("  a b | (a||b) && !(a&&b) | a != b\n");
    printf("  ----+--------------------+-------\n");
    printf("  %d %d |         %d          |   %d\n", 0, 0, (0 || 0) && !(0 && 0), 0 != 0);
    printf("  %d %d |         %d          |   %d\n", 0, 1, (0 || 1) && !(0 && 1), 0 != 1);
    printf("  %d %d |         %d          |   %d\n", 1, 0, (1 || 0) && !(1 && 0), 1 != 0);
    printf("  %d %d |         %d          |   %d\n", 1, 1, (1 || 1) && !(1 && 1), 1 != 1);
    printf("\n");

    /* ── Tavola con tre ingressi ─────────────────────────────────────── */
    /* Con n ingressi le combinazioni sono 2^n: con 3 ingressi sono 8.
     * Esempio: un allarme suona se è attivo (a) E
     * c'è movimento (m) OPPURE una porta aperta (p).
     *     allarme = a && (m || p)                                        */
    printf("=== Tre ingressi: a && (m || p) ===\n");
    printf("  a m p | risultato\n");
    printf("  ------+----------\n");
    printf("  %d %d %d |     %d\n", 0, 0, 0, 0 && (0 || 0));
    printf("  %d %d %d |     %d\n", 0, 0, 1, 0 && (0 || 1));
    printf("  %d %d %d |     %d\n", 0, 1, 0, 0 && (1 || 0));
    printf("  %d %d %d |     %d\n", 0, 1, 1, 0 && (1 || 1));
    printf("  %d %d %d |     %d\n", 1, 0, 0, 1 && (0 || 0));
    printf("  %d %d %d |     %d\n", 1, 0, 1, 1 && (0 || 1));
    printf("  %d %d %d |     %d\n", 1, 1, 0, 1 && (1 || 0));
    printf("  %d %d %d |     %d\n", 1, 1, 1, 1 && (1 || 1));

    /*
     * ERRORE COMUNE: usare & e | (operatori BIT A BIT, capitolo 01)
     * al posto di && e || (operatori LOGICI).
     *
     *   2 & 1   vale 0   (nessun bit in comune)
     *   2 && 1  vale 1   (entrambi diversi da zero, quindi veri)
     *
     * Con valori diversi da 0 e 1 i risultati possono essere diversi:
     * nelle condizioni si usano sempre && e ||.
     */

    return 0;
}
