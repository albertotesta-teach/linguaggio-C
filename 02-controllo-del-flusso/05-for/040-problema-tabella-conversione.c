/*
 * 040-problema-tabella-conversione.c
 *
 * Tabella di conversione delle temperature
 *
 * Un laboratorio deve affiggere una tabella che converta le temperature da
 * gradi Celsius a Fahrenheit e Kelvin. L'utente sceglie la temperatura
 * iniziale, quella finale e il passo (es. da -20 a 100 ogni 10 gradi).
 *
 *     F = C * 9 / 5 + 32
 *     K = C + 273.15
 *
 * Il numero di righe è noto prima di iniziare, una volta letti i tre dati:
 * il for è la struttura adatta. I dati vengono validati con do-while
 * (sezione 04): il passo deve essere positivo e la temperatura finale non
 * può essere minore di quella iniziale.
 *
 * La riga che corrisponde al punto di congelamento dell'acqua (0 °C) e
 * quella dell'ebollizione (100 °C) vengono evidenziate.
 */

#include <stdio.h>

int main(void)
{
    int inizio;
    int fine;
    int passo;
    int celsius;
    int righe = 0;
    double fahrenheit;
    double kelvin;

    printf("=== TABELLA DI CONVERSIONE TEMPERATURE ===\n\n");

    printf("Temperatura iniziale (gradi C, intero): ");
    scanf("%d", &inizio);

    do {
        printf("Temperatura finale (>= %d): ", inizio);
        scanf("%d", &fine);
    } while (fine < inizio);

    do {
        printf("Passo (positivo): ");
        scanf("%d", &passo);
    } while (passo <= 0);

    printf("\n   Celsius | Fahrenheit |   Kelvin\n");
    printf("  ---------|------------|----------\n");

    for (celsius = inizio; celsius <= fine; celsius = celsius + passo) {
        fahrenheit = celsius * 9.0 / 5.0 + 32.0;   /* 9.0: divisione reale */
        kelvin = celsius + 273.15;

        printf("  %8d | %10.1f | %8.2f", celsius, fahrenheit, kelvin);

        if (celsius == 0) {
            printf("   <- l'acqua gela");
        } else if (celsius == 100) {
            printf("   <- l'acqua bolle");
        }
        printf("\n");

        righe++;
    }

    printf("\nRighe stampate: %d\n", righe);

    /*
     * ERRORE COMUNE: divisione intera nella formula.
     *     fahrenheit = celsius * 9 / 5 + 32;
     * Con celsius = 1 si calcola 1 * 9 = 9 e poi 9 / 5 = 1 (divisione tra
     * interi, parte decimale troncata): il risultato è 33 invece di 33.8.
     * Basta un operando reale (9.0) per avere la divisione reale.
     */

    return 0;
}
