/*
 * 060-problema-anatomia-float.c
 *
 * Laboratorio di informatica: com'è fatto un float
 *
 * Un float occupa 32 bit divisi in tre parti (standard IEEE 754):
 *
 *     segno (1 bit) | esponente (8 bit) | mantissa (23 bit)
 *
 *     valore = (-1)^segno x 1.mantissa x 2^(esponente - 127)
 *
 * Con una union si leggono i bit del float come intero senza segno, e da
 * lì si estraggono le tre parti con spostamenti e maschere:
 *
 *     typedef union {
 *         float reale;
 *         uint32_t bit;
 *     } Float;
 *
 *     segno     = f.bit >> 31;
 *     esponente = (f.bit >> 23) & 0xFF;
 *     mantissa  = f.bit & 0x7FFFFF;
 *
 * Il programma legge numeri reali fino a FINE e per ognuno stampa i 32
 * bit separati nelle tre parti, il segno, l'esponente vero (meno 127) e
 * la mantissa. Lo zero ha esponente e mantissa nulli. Si vede anche che
 * 0.1 non si rappresenta esattamente: la mantissa è periodica.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LUNG 32

typedef union {
    float reale;
    uint32_t bit;
} Float;

void stampa_bit(uint32_t bit);

int main(void)
{
    char parola[LUNG];
    Float f;
    uint32_t segno;
    uint32_t esponente;
    uint32_t mantissa;
    int finito = 0;

    while (!finito) {
        printf("Numero (FINE): ");
        if (scanf("%31s", parola) != 1 || strcmp(parola, "FINE") == 0) {
            finito = 1;
        } else if (sscanf(parola, "%f", &f.reale) != 1) {
            printf("  Non e' un numero.\n");
        } else {
            segno = f.bit >> 31;
            esponente = (f.bit >> 23) & 0xFF;
            mantissa = f.bit & 0x7FFFFF;
            printf("  %.9g\n  ", f.reale);
            stampa_bit(f.bit);
            printf("\n  segno %lu (%s), esponente %lu", (unsigned long) segno,
                   segno ? "negativo" : "positivo", (unsigned long) esponente);
            if (esponente == 0 && mantissa == 0) {
                printf(" (zero)");
            } else {
                printf(" - 127 = %ld", (long) esponente - 127);
            }
            printf(", mantissa 0x%06lX\n", (unsigned long) mantissa);
        }
    }

    return 0;
}

/* I 32 bit con uno spazio dopo il segno e dopo l'esponente. */
void stampa_bit(uint32_t bit)
{
    int i;

    for (i = 31; i >= 0; i--) {
        printf("%lu", (unsigned long) ((bit >> i) & 1));
        if (i == 31 || i == 23) {
            printf(" ");
        }
    }
}
