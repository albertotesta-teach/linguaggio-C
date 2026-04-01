/*
 * 040-operatori-bit-a-bit.c
 *
 * Operatori bit a bit in C
 *
 * Introduce gli operatori che agiscono sui singoli bit di un valore intero:
 * AND (&), OR (|), XOR (^), NOT (~), shift sinistro (<<), shift destro (>>).
 * La rappresentazione binaria dei valori è mostrata nei commenti per
 * rendere visibile l'effetto di ciascun operatore.
 * Trattazione introduttiva; usi avanzati (maschere, flag, registri hardware)
 * vengono approfonditi nel capitolo 09 sul preprocessore e nelle librerie.
 */

#include <stdio.h>

int main(void)
{
    /* valori di esempio con rappresentazione binaria nei commenti */
    unsigned int a = 60;    /* 0011 1100 */
    unsigned int b = 15;    /* 0000 1111 */

    printf("=== Valori di partenza ===\n");
    printf("a = %2u  (binario: 0011 1100)\n", a);
    printf("b = %2u  (binario: 0000 1111)\n\n", b);

    /* ── AND bit a bit (&) ──────────────────────────────────────────────── */
    /*   0011 1100
     * & 0000 1111
     * = 0000 1100  ->  12  */
    printf("=== AND bit a bit (a & b) ===\n");
    printf("  0011 1100\n");
    printf("& 0000 1111\n");
    printf("= 0000 1100  ->  %u\n\n", a & b);

    /* ── OR bit a bit (|) ───────────────────────────────────────────────── */
    /*   0011 1100
     * | 0000 1111
     * = 0011 1111  ->  63  */
    printf("=== OR bit a bit (a | b) ===\n");
    printf("  0011 1100\n");
    printf("| 0000 1111\n");
    printf("= 0011 1111  ->  %u\n\n", a | b);

    /* ── XOR bit a bit (^) ──────────────────────────────────────────────── */
    /* XOR: il bit risultante è 1 solo se i due bit sono diversi.
     *   0011 1100
     * ^ 0000 1111
     * = 0011 0011  ->  51  */
    printf("=== XOR bit a bit (a ^ b) ===\n");
    printf("  0011 1100\n");
    printf("^ 0000 1111\n");
    printf("= 0011 0011  ->  %u\n\n", a ^ b);

    /* ── NOT bit a bit (~) ──────────────────────────────────────────────── */
    /* Inverte tutti i bit. Il risultato dipende dalla dimensione del tipo.
     * Per unsigned int a 32 bit: ~60 = 4294967235  */
    printf("=== NOT bit a bit (~a) ===\n");
    printf("~60 (unsigned int) = %u\n\n", ~a);

    /* ── shift sinistro (<<) ────────────────────────────────────────────── */
    /* Sposta i bit verso sinistra di N posizioni.
     * Equivale a moltiplicare per 2^N (se non ci sono overflow).
     *   60 << 1  =  0111 1000  =  120  (60 * 2)
     *   60 << 2  =  1111 0000  =  240  (60 * 4)  */
    printf("=== Shift sinistro (<<) ===\n");
    printf("a << 1 = %u  (equivale a %u * 2)\n",  a << 1, a);
    printf("a << 2 = %u  (equivale a %u * 4)\n",  a << 2, a);
    printf("1 << 0 = %u\n", 1u << 0);
    printf("1 << 1 = %u\n", 1u << 1);
    printf("1 << 2 = %u\n", 1u << 2);
    printf("1 << 3 = %u\n\n", 1u << 3);

    /* ── shift destro (>>) ──────────────────────────────────────────────── */
    /* Sposta i bit verso destra di N posizioni.
     * Per interi senza segno equivale a dividere per 2^N (troncando).
     *   60 >> 1  =  0001 1110  =  30  (60 / 2)
     *   60 >> 2  =  0000 1111  =  15  (60 / 4)  */
    printf("=== Shift destro (>>) ===\n");
    printf("a >> 1 = %u  (equivale a %u / 2)\n", a >> 1, a);
    printf("a >> 2 = %u  (equivale a %u / 4)\n", a >> 2, a);

    /* ── applicazioni pratiche ──────────────────────────────────────────── */
    printf("\n=== Applicazioni pratiche ===\n");

    unsigned int valore  = 0b10110101;   /* C99: notazione binaria */
    unsigned int maschera = (1u << 2);   /* bit 2: 0000 0100 */

    /* test di un bit: il risultato è 0 se il bit è 0, diverso da 0 se è 1 */
    int bit2_attivo = (valore & maschera) != 0;
    printf("valore = 181, bit 2 attivo: %d\n", bit2_attivo);

    /* impostazione di un bit (set): forza il bit a 1 con OR */
    unsigned int con_bit2 = valore | maschera;
    printf("valore con bit 2 forzato a 1: %u\n", con_bit2);

    /* azzeramento di un bit (clear): forza il bit a 0 con AND e NOT */
    unsigned int senza_bit2 = valore & ~maschera;
    printf("valore con bit 2 forzato a 0: %u\n", senza_bit2);

    return 0;
}
