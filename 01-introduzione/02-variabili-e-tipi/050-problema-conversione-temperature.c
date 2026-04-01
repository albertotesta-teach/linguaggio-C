/*
 * 050-problema-conversione-temperature.c
 *
 * Conversione di temperature
 *
 * L'utente inserisce una temperatura in gradi Celsius. Il programma
 * calcola e stampa la conversione in gradi Fahrenheit e in Kelvin,
 * applicando le formule standard. Mette in pratica i tipi reali,
 * le costanti con #define e la formattazione con %.2f.
 *
 * Formule:
 *   Fahrenheit = Celsius * 9.0 / 5.0 + 32.0
 *   Kelvin     = Celsius + 273.15
 */

#include <stdio.h>

/* costanti per le formule di conversione */
#define FATTORE_F   (9.0 / 5.0)   /* fattore moltiplicativo Celsius->Fahrenheit */
#define OFFSET_F    32.0           /* offset additivo Celsius->Fahrenheit */
#define OFFSET_K    273.15         /* offset additivo Celsius->Kelvin */

int main(void)
{
    double celsius;
    double fahrenheit;
    double kelvin;

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Convertitore di temperature ===\n\n");
    printf("Temperatura in gradi Celsius: ");
    scanf("%lf", &celsius);   /* %lf per leggere un double con scanf */

    /* ── calcolo ────────────────────────────────────────────────────────── */
    /* Nota: si usa 9.0/5.0 e non 9/5 per evitare la divisione intera,
     * che darebbe 1 invece di 1.8 e renderebbe la formula errata. */
    fahrenheit = celsius * FATTORE_F + OFFSET_F;
    kelvin     = celsius + OFFSET_K;

    /* ── output ─────────────────────────────────────────────────────────── */
    printf("\n--- Risultato ---\n");
    printf("Celsius:     %8.2f °C\n", celsius);
    printf("Fahrenheit:  %8.2f °F\n", fahrenheit);
    printf("Kelvin:      %8.2f K\n",  kelvin);

    /* nota sui valori particolari */
    printf("\n--- Valori di riferimento ---\n");
    printf("Acqua: congela a  0 °C = %.2f °F = %.2f K\n",
           0.0 * FATTORE_F + OFFSET_F, 0.0 + OFFSET_K);
    printf("Acqua: bolle  a 100 °C = %.2f °F = %.2f K\n",
           100.0 * FATTORE_F + OFFSET_F, 100.0 + OFFSET_K);

    return 0;
}
