/*
 * 050-problema-temperatura-giornaliera.c
 *
 * Stazione meteorologica: rilevazione min e max giornalieri
 *
 * Una stazione meteorologica registra le temperature rilevate durante
 * la giornata. Le variabili globali conservano il minimo e il massimo
 * osservati fino a quel momento, aggiornate a ogni nuova rilevazione.
 * Al termine viene stampato il report completo della giornata.
 *
 * Le variabili globali sono appropriate qui perché rappresentano uno
 * stato che deve persistere tra chiamate successive a funzioni diverse
 * e che sarebbe artificioso passare come parametro avanti e indietro.
 */

#include <stdio.h>

/* Valore sentinella: indica che nessuna rilevazione è ancora avvenuta.
 * Usiamo un valore fisicamente impossibile per la temperatura terrestre. */
#define NESSUNA_RILEVAZIONE -999.0

/* --- Stato globale della stazione --- */
double temp_minima      = NESSUNA_RILEVAZIONE;
double temp_massima     = NESSUNA_RILEVAZIONE;
double temp_somma       = 0.0;
int    num_rilevazioni  = 0;

/* Prototipi */
void registra_temperatura(double temp);
void stampa_report(void);
void stampa_rilevazione(int ora, double temp);

/* Aggiorna lo stato globale con una nuova rilevazione */
void registra_temperatura(double temp)
{
    num_rilevazioni = num_rilevazioni + 1;
    temp_somma      = temp_somma + temp;

    if (temp_minima == NESSUNA_RILEVAZIONE || temp < temp_minima) {
        temp_minima = temp;
    }
    if (temp_massima == NESSUNA_RILEVAZIONE || temp > temp_massima) {
        temp_massima = temp;
    }
}

void stampa_rilevazione(int ora, double temp)
{
    printf("  %02d:00  %+6.1f C\n", ora, temp);
    registra_temperatura(temp);
}

void stampa_report(void)
{
    double media;

    printf("\n--- Report giornaliero ---\n");

    if (num_rilevazioni == 0) {
        printf("Nessuna rilevazione disponibile.\n");
    } else {
        media = temp_somma / num_rilevazioni;
        printf("Rilevazioni:   %d\n",    num_rilevazioni);
        printf("Temperatura minima:  %+.1f C\n", temp_minima);
        printf("Temperatura massima: %+.1f C\n", temp_massima);
        printf("Temperatura media:   %+.1f C\n", media);
        printf("Escursione termica:  %.1f C\n",
               temp_massima - temp_minima);
    }
}

int main(void)
{
    printf("=== Stazione meteorologica - 20/03/2024 ===\n\n");
    printf("Ora     Temperatura\n");
    printf("-------------------\n");

    /* Rilevazioni ogni due ore */
    stampa_rilevazione( 0,  4.2);
    stampa_rilevazione( 2,  3.8);
    stampa_rilevazione( 4,  3.1);
    stampa_rilevazione( 6,  4.5);
    stampa_rilevazione( 8,  7.3);
    stampa_rilevazione(10, 11.8);
    stampa_rilevazione(12, 14.2);
    stampa_rilevazione(14, 15.6);
    stampa_rilevazione(16, 13.9);
    stampa_rilevazione(18, 10.4);
    stampa_rilevazione(20,  7.8);
    stampa_rilevazione(22,  5.9);

    stampa_report();

    return 0;
}
