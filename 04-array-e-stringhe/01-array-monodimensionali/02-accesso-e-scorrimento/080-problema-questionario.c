/*
 * 080-problema-questionario.c
 *
 * Problema reale: tabulazione delle risposte a un questionario.
 *
 * Scenario: un questionario a risposta multipla ha 10 domande, ciascuna
 * con opzioni A, B, C, D. Il programma raccoglie le risposte di uno
 * studente, le confronta con la chiave di correzione, calcola il punteggio
 * e mostra un riepilogo dettagliato con le domande corrette ed errate.
 *
 * Concetti applicati:
 *  - array di char per risposta multipla
 *  - scorrimento parallelo (risposte vs. chiave)
 *  - conteggio e classificazione durante lo scorrimento
 *  - validazione dell'input con ciclo while
 */

#include <stdio.h>

#define NUM_DOMANDE 10

int main(void) {

    char chiave[NUM_DOMANDE] = {'A', 'C', 'B', 'D', 'A', 'C', 'B', 'A', 'D', 'C'};
    char risposte[NUM_DOMANDE];
    int i;
    int valido;

    printf("=== QUESTIONARIO A RISPOSTA MULTIPLA ===\n");
    printf("Inserisci la risposta (A/B/C/D) per ciascuna domanda:\n\n");

    for (i = 0; i < NUM_DOMANDE; i++) {
        valido = 0;
        while (!valido) {
            printf("  Domanda %2d: ", i + 1);
            scanf(" %c", &risposte[i]);
            if (risposte[i] >= 'a' && risposte[i] <= 'd') {
                risposte[i] = risposte[i] - 32;
            }
            if (risposte[i]=='A' || risposte[i]=='B' ||
                risposte[i]=='C' || risposte[i]=='D') {
                valido = 1;
            } else {
                printf("  Risposta non valida. Inserire A, B, C o D.\n");
            }
        }
    }

    int corrette = 0;
    int errate   = 0;

    printf("\n=== CORREZIONE ===\n");
    printf("  Dom. | Risposta | Corretta | Esito\n");
    printf("  -----|----------|----------|------\n");

    for (i = 0; i < NUM_DOMANDE; i++) {
        char esito[10];
        if (risposte[i] == chiave[i]) {
            esito[0]='O'; esito[1]='K'; esito[2]='\0';
            corrette++;
        } else {
            esito[0]='E'; esito[1]='R'; esito[2]='R'; esito[3]='A';
            esito[4]='T'; esito[5]='A'; esito[6]='\0';
            errate++;
        }
        printf("   %2d  |    %c     |    %c     | %s\n",
               i + 1, risposte[i], chiave[i], esito);
    }

    double punteggio = (double)corrette / NUM_DOMANDE * 100.0;

    printf("\n=== RISULTATO ===\n");
    printf("  Risposte corrette : %d su %d\n", corrette, NUM_DOMANDE);
    printf("  Risposte errate   : %d su %d\n", errate, NUM_DOMANDE);
    printf("  Punteggio         : %.0f%%\n", punteggio);

    if (punteggio >= 60.0) {
        printf("  Esito             : PROMOSSO\n");
    } else {
        printf("  Esito             : NON PROMOSSO\n");
    }

    return 0;
}
