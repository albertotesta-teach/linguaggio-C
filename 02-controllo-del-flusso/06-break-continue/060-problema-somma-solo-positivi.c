/*
 * 060-problema-somma-solo-positivi.c
 *
 * Letture di un contatore con scarto dei valori anomali
 *
 * Un contatore elettrico invia ogni ora il consumo in wattora (Wh).
 * Per un guasto del sensore alcune letture arrivano negative: vanno
 * scartate, contate e segnalate. La lettura 0 è valida (nessun consumo).
 * L'operatore inserisce le letture della giornata e termina con -999.
 *
 * Il programma calcola:
 *   - il consumo totale e il numero di letture valide;
 *   - il consumo medio orario sulle sole letture valide;
 *   - il numero di letture scartate;
 *   - la lettura valida più alta.
 *
 * Ciclo con sentinella (vedi 04-while-do-while) e nessun continue:
 * la lettura anomala è gestita nel ramo else.
 */

#include <stdio.h>

#define FINE_DATI (-999)

int main(void)
{
    int lettura;
    int numero_lettura = 0;
    int valide = 0;
    int scartate = 0;
    int totale = 0;
    int massima = 0;

    printf("=== CONTATORE ELETTRICO - LETTURE ORARIE ===\n");
    printf("Inserire le letture in Wh (%d per terminare).\n\n", FINE_DATI);

    printf("Lettura %d: ", numero_lettura + 1);
    scanf("%d", &lettura);

    while (lettura != FINE_DATI) {
        numero_lettura++;

        /*   VERSIONE DA EVITARE:
         *       if (lettura < 0) {
         *           scartate++;
         *           (lettura successiva)
         *           continue;
         *       }
         *       elaborazione della lettura valida...
         *
         *   Qui la lettura successiva andrebbe ripetuta prima del
         *   continue: con due punti di lettura è facile dimenticarne uno. */
        if (lettura >= 0) {
            valide++;
            totale = totale + lettura;
            if (valide == 1 || lettura > massima) {
                massima = lettura;
            }
        } else {
            scartate++;
            printf("  Lettura %d anomala (%d Wh): scartata.\n", numero_lettura, lettura);
        }

        printf("Lettura %d: ", numero_lettura + 1);
        scanf("%d", &lettura);
    }

    printf("\n--- Riepilogo ---\n");
    printf("Letture ricevute : %d\n", numero_lettura);
    printf("Letture valide   : %d\n", valide);
    printf("Letture scartate : %d\n", scartate);

    if (valide > 0) {
        printf("Consumo totale   : %d Wh (%.3f kWh)\n", totale, totale / 1000.0);
        printf("Consumo medio    : %.1f Wh per lettura\n", (double)totale / valide);
        printf("Lettura massima  : %d Wh\n", massima);
    } else {
        printf("Nessuna lettura valida: impossibile calcolare i consumi.\n");
    }

    return 0;
}
