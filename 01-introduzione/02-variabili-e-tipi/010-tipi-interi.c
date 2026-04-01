/*
 * 010-tipi-interi.c
 *
 * Tipi interi in C
 *
 * Presenta i tipi interi fondamentali del C: short, int, long, long long,
 * nelle varianti con segno (signed) e senza segno (unsigned).
 * Mostra la dimensione in byte di ciascun tipo con sizeof e i valori
 * limite definiti in <limits.h>. Discute in commento il fenomeno
 * dell'overflow, cioè cosa succede quando si supera il valore massimo.
 */

#include <stdio.h>
#include <limits.h>   /* contiene le costanti INT_MAX, INT_MIN, ecc. */

int main(void)
{
    /* dichiarazione di variabili di tipo intero */
    short          valore_short  = 30000;
    int            valore_int    = 2000000000;
    long           valore_long   = 2000000000L;   /* suffisso L per long */
    long long      valore_llong  = 9000000000LL;  /* suffisso LL per long long */
    unsigned int   valore_uint   = 4000000000U;   /* suffisso U per unsigned */

    /* ── dimensioni in byte ─────────────────────────────────────────────── */
    /* sizeof restituisce il numero di byte occupati dal tipo o dalla
     * variabile. Il risultato è di tipo size_t, stampato con %zu. */
    printf("=== Dimensioni dei tipi interi ===\n");
    printf("short:         %zu byte\n", sizeof(short));
    printf("int:           %zu byte\n", sizeof(int));
    printf("long:          %zu byte\n", sizeof(long));
    printf("long long:     %zu byte\n", sizeof(long long));
    printf("unsigned int:  %zu byte\n", sizeof(unsigned int));

    /* ── valori limite (da <limits.h>) ──────────────────────────────────── */
    printf("\n=== Valori limite ===\n");
    printf("short:      da %d  a %d\n",  SHRT_MIN,  SHRT_MAX);
    printf("int:        da %d  a %d\n",  INT_MIN,   INT_MAX);
    printf("long:       da %ld a %ld\n", LONG_MIN,  LONG_MAX);
    printf("long long:  da %lld a %lld\n", LLONG_MIN, LLONG_MAX);
    printf("uint max:   %u\n", UINT_MAX);

    /* ── valori delle variabili dichiarate ─────────────────────────────── */
    printf("\n=== Valori di esempio ===\n");
    printf("short:      %d\n",   valore_short);
    printf("int:        %d\n",   valore_int);
    printf("long:       %ld\n",  valore_long);
    printf("long long:  %lld\n", valore_llong);
    printf("uint:       %u\n",   valore_uint);

    /* ── nota sull'overflow (solo in commento, non eseguita) ────────────── */
    /*
     * Se si assegna a una variabile un valore oltre il suo limite,
     * si verifica un OVERFLOW: il valore "ricomincia" dall'estremo opposto.
     *
     *   short x = 32767;   // SHRT_MAX
     *   x = x + 1;         // overflow! x diventa -32768 (SHRT_MIN)
     *
     * Per i tipi unsigned l'overflow è definito dal linguaggio (comportamento
     * a modulo). Per i tipi con segno è comportamento indefinito (UB).
     * Morale: scegliere sempre il tipo adatto all'intervallo di valori atteso.
     */

    return 0;
}
