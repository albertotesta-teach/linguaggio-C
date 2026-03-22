/*
 * 070-problema-sensori-industriali.c
 *
 * Problema reale: lettura e analisi di sensori industriali.
 *
 * Scenario: un impianto industriale ha 8 sensori di temperatura.
 * Il sistema campiona le letture in un array, le visualizza in una
 * dashboard testuale, segnala i sensori fuori soglia (allarme) e
 * calcola la temperatura media dell'impianto.
 *
 * Concetti applicati:
 *  - array di double con valori letti da tastiera
 *  - scorrimento per rilevare valori fuori intervallo
 *  - uso di soglie come costanti simboliche
 */

#include <stdio.h>

#define NUM_SENSORI    8
#define SOGLIA_MIN    10.0
#define SOGLIA_MAX    80.0

int main(void) {

    double letture[NUM_SENSORI];
    int i;

    printf("=== SISTEMA DI MONITORAGGIO SENSORI ===\n\n");
    printf("Inserisci la temperatura rilevata per ciascun sensore (°C):\n");

    for (i = 0; i < NUM_SENSORI; i++) {
        printf("  Sensore S%02d: ", i + 1);
        scanf("%lf", &letture[i]);
    }

    printf("\n--- DASHBOARD IMPIANTO ---\n");
    printf("  %-10s | %-10s | Stato\n", "Sensore", "Temp (°C)");
    printf("  -----------|------------|-------\n");

    for (i = 0; i < NUM_SENSORI; i++) {
        char stato[10];
        if (letture[i] < SOGLIA_MIN || letture[i] > SOGLIA_MAX) {
            stato[0]='A'; stato[1]='L'; stato[2]='L'; stato[3]='A';
            stato[4]='R'; stato[5]='M'; stato[6]='E'; stato[7]='\0';
        } else {
            stato[0]='O'; stato[1]='K'; stato[2]='\0';
        }
        printf("  S%02d        | %8.1f °C | %s\n", i + 1, letture[i], stato);
    }
    printf("\n");

    int num_allarmi = 0;
    printf("Sensori fuori soglia [%.0f°C - %.0f°C]:\n", SOGLIA_MIN, SOGLIA_MAX);

    for (i = 0; i < NUM_SENSORI; i++) {
        if (letture[i] < SOGLIA_MIN) {
            printf("  [!] S%02d: %.1f°C - TEMPERATURA TROPPO BASSA\n", i+1, letture[i]);
            num_allarmi++;
        } else if (letture[i] > SOGLIA_MAX) {
            printf("  [!] S%02d: %.1f°C - TEMPERATURA TROPPO ALTA\n", i+1, letture[i]);
            num_allarmi++;
        }
    }
    if (num_allarmi == 0) {
        printf("  Tutti i sensori nella norma.\n");
    }
    printf("\n");

    double somma = 0.0;
    for (i = 0; i < NUM_SENSORI; i++) {
        somma = somma + letture[i];
    }
    printf("Temperatura media impianto: %.1f°C\n", somma / NUM_SENSORI);
    printf("Sensori in allarme: %d su %d\n", num_allarmi, NUM_SENSORI);

    return 0;
}
