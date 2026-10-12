/*
 * 040-problema-semaforo.c
 *
 * Il semaforo davanti alla scuola: che colore c'è dopo t secondi?
 *
 * Il semaforo pedonale davanti all'ingresso ripete sempre lo stesso
 * ciclo: verde, giallo, rosso, poi di nuovo verde. Ogni colore ha la sua
 * durata:
 *
 *     typedef enum { VERDE, GIALLO, ROSSO, NUM_COLORI } Colore;
 *
 *     int durata[NUM_COLORI] = {[VERDE] = 40, [GIALLO] = 5, [ROSSO] = 45};
 *
 * Il colore successivo si ottiene con (colore + 1) % NUM_COLORI: dopo
 * ROSSO (2) si torna a VERDE (0).
 *
 * Il programma legge un tempo t in secondi (da 1 a 600), stampa tutti i
 * cambi di colore da 0 a t e il colore all'istante t, con i secondi che
 * mancano al cambio successivo.
 */

#include <stdio.h>

#define MASSIMO 600

typedef enum {
    VERDE, GIALLO, ROSSO, NUM_COLORI
} Colore;

int main(void)
{
    const char *nomi[NUM_COLORI] = {[VERDE] = "VERDE", [GIALLO] = "GIALLO", [ROSSO] = "ROSSO"};
    int durata[NUM_COLORI] = {[VERDE] = 40, [GIALLO] = 5, [ROSSO] = 45};
    Colore colore = VERDE;
    int inizio = 0;
    int t;

    printf("Istante (secondi, da 1 a %d): ", MASSIMO);
    if (scanf("%d", &t) != 1 || t < 1 || t > MASSIMO) {
        printf("Istante non valido.\n");
    } else {
        printf("  %3d s  %s\n", inizio, nomi[colore]);
        while (inizio + durata[colore] <= t) {
            inizio = inizio + durata[colore];
            colore = (colore + 1) % NUM_COLORI;
            printf("  %3d s  %s\n", inizio, nomi[colore]);
        }
        printf("A %d s il semaforo e' %s: cambia tra %d s.\n", t, nomi[colore],
               inizio + durata[colore] - t);
    }

    return 0;
}
