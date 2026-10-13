/*
 * 030-vedere-i-byte.c
 *
 * Vedere i byte di un numero attraverso una union
 *
 * Un uso classico delle union è guardare lo stesso valore in due modi:
 * come numero e come sequenza di byte.
 *
 *     typedef union {
 *         uint32_t valore;
 *         uint8_t byte[4];
 *     } Parola;
 *
 * uint32_t e uint8_t vengono da <stdint.h>: interi senza segno di
 * esattamente 32 e 8 bit, così la dimensione non dipende dal compilatore.
 *
 * In memoria i 4 byte di un numero possono stare in due ordini:
 *   - little-endian: prima il byte meno significativo (PC x86, Mac con
 *     Apple Silicon, quasi tutti i processori di oggi);
 *   - big-endian: prima il più significativo (alcuni processori, e
 *     l'ordine usato per i numeri nei protocolli di rete).
 *
 * Con valore = 0x0A0B0C0D, su una macchina little-endian byte[0] vale
 * 0x0D e byte[3] vale 0x0A. Il programma lo mostra e lo usa per capire
 * su quale tipo di macchina sta girando.
 */

#include <stdio.h>
#include <stdint.h>

typedef union {
    uint32_t valore;
    uint8_t byte[4];
} Parola;

int main(void)
{
    Parola p;
    Parola prova;
    int i;

    p.valore = 0x0A0B0C0D;
    printf("valore = 0x%08lX\n", (unsigned long) p.valore);
    for (i = 0; i < 4; i++) {
        printf("  byte[%d] = 0x%02X\n", i, p.byte[i]);
    }

    prova.valore = 1;
    printf("\nCon valore = 1, byte[0] vale %d: macchina %s.\n", prova.byte[0],
           prova.byte[0] == 1 ? "little-endian" : "big-endian");

    p.byte[3] = 0xFF;
    printf("Dopo byte[3] = 0xFF il valore e' 0x%08lX\n", (unsigned long) p.valore);

    return 0;
}
