/*
 * 020-accumulatori.c
 *
 * Elaborare n valori letti uno alla volta, senza memorizzarli
 *
 * Le temperature massime di una settimana vengono inserite una alla volta.
 * Senza array (capitolo 04) non si possono conservare tutte: ogni valore
 * viene elaborato appena letto e poi "dimenticato". Bastano poche
 * variabili che riassumono i dati visti finora:
 *
 *   ACCUMULATORE   somma = somma + valore          (inizializzato a 0)
 *   CONTATORE      conta = conta + 1 se ...        (inizializzato a 0)
 *   MASSIMO        se valore > massimo: massimo = valore
 *   MINIMO         se valore < minimo:  minimo  = valore
 *
 * Il massimo e il minimo si inizializzano con il PRIMO valore letto, non
 * con 0: con temperature tutte negative un massimo iniziale 0 sarebbe
 * sbagliato.
 */

#include <stdio.h>

#define GIORNI      7
#define SOGLIA_CALDO 30.0

int main(void)
{
    int giorno;
    double temperatura;
    double somma = 0.0;
    double massima = 0.0;
    double minima = 0.0;
    int giorno_massima = 0;
    int giorni_caldi = 0;

    printf("=== TEMPERATURE DELLA SETTIMANA ===\n");

    for (giorno = 1; giorno <= GIORNI; giorno++) {
        printf("Temperatura massima del giorno %d: ", giorno);
        scanf("%lf", &temperatura);

        /* Accumulatore */
        somma = somma + temperatura;

        /* Massimo e minimo: il primo valore inizializza entrambi */
        if (giorno == 1) {
            massima = temperatura;
            minima = temperatura;
            giorno_massima = 1;
        } else {
            if (temperatura > massima) {
                massima = temperatura;
                giorno_massima = giorno;
            }
            if (temperatura < minima) {
                minima = temperatura;
            }
        }

        /* Contatore condizionato */
        if (temperatura >= SOGLIA_CALDO) {
            giorni_caldi++;
        }
    }

    printf("\n--- Riepilogo ---\n");
    printf("Media della settimana : %.1f gradi\n", somma / GIORNI);
    printf("Massima               : %.1f gradi (giorno %d)\n", massima, giorno_massima);
    printf("Minima                : %.1f gradi\n", minima);
    printf("Escursione            : %.1f gradi\n", massima - minima);
    printf("Giorni con almeno %.0f gradi: %d su %d\n", SOGLIA_CALDO, giorni_caldi, GIORNI);

    /*
     * ERRORE COMUNE: accumulatore inizializzato dentro il ciclo.
     *
     *     for (giorno = 1; giorno <= GIORNI; giorno++) {
     *         somma = 0.0;                    // azzerata a ogni giro
     *         somma = somma + temperatura;
     *     }
     *
     * Alla fine somma contiene solo l'ultima temperatura.
     */

    return 0;
}
