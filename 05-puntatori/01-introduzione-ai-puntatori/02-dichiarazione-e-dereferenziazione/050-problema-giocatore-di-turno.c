/*
 * 050-problema-giocatore-di-turno.c
 *
 * Il punteggio del giocatore di turno
 *
 * In un gioco di dadi per due giocatori vince chi arriva per primo a
 * TRAGUARDO punti. A ogni turno il giocatore lancia il dado e somma il
 * risultato; se esce 1 perde invece 3 punti (senza scendere sotto 0).
 *
 * Invece di scrivere due volte le stesse istruzioni (una per giocatore), il
 * programma usa due puntatori che indicano il giocatore di turno:
 *
 *     punti_turno  ->  &punti_1 oppure &punti_2
 *     nome_turno   ->  il primo carattere di nome_1 oppure di nome_2
 *
 * Alla fine di ogni turno i puntatori passano all'altro giocatore.
 * I lanci sono presi da un array fisso, così la partita è ripetibile.
 */

#include <stdio.h>

#define TRAGUARDO 20
#define LANCI     16
#define LUNG      12

int main(void)
{
    char nome_1[LUNG] = "Anna";
    char nome_2[LUNG] = "Bruno";
    int punti_1 = 0;
    int punti_2 = 0;
    int lanci[LANCI] = {4, 6, 5, 1, 6, 3, 2, 5, 1, 6, 4, 4, 6, 2, 3, 5};
    int *punti_turno = &punti_1;
    char *nome_turno = &nome_1[0];
    int k = 0;
    int vincitore = 0;

    printf("=== GARA DI DADI (traguardo %d punti) ===\n", TRAGUARDO);
    while (k < LANCI && !vincitore) {
        printf("Turno %2d - %-6s lancia %d: ", k + 1, nome_turno, lanci[k]);
        if (lanci[k] == 1) {
            *punti_turno = *punti_turno - 3;
            if (*punti_turno < 0) {
                *punti_turno = 0;
            }
        } else {
            *punti_turno = *punti_turno + lanci[k];
        }
        printf("punti %2d   (%s %d - %s %d)\n", *punti_turno, nome_1, punti_1,
               nome_2, punti_2);

        if (*punti_turno >= TRAGUARDO) {
            vincitore = 1;
            printf("\nVince %s con %d punti!\n", nome_turno, *punti_turno);
        } else if (punti_turno == &punti_1) {
            punti_turno = &punti_2;     /* tocca all'altro giocatore */
            nome_turno = &nome_2[0];
        } else {
            punti_turno = &punti_1;
            nome_turno = &nome_1[0];
        }
        k++;
    }

    if (!vincitore) {
        printf("\nLanci finiti: %s %d - %s %d\n", nome_1, punti_1, nome_2, punti_2);
    }

    return 0;
}
