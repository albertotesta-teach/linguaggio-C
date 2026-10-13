/*
 * 010-ingrandire-un-blocco.c
 *
 * realloc: cambiare la dimensione di un blocco mantenendo il contenuto
 *
 *     nuovo = realloc(vecchio, nuovi_byte);
 *
 * realloc restituisce un blocco della nuova dimensione che contiene i
 * dati del vecchio (fino alla dimensione minore tra le due). Due casi:
 *
 *   - c'è spazio libero subito dopo il blocco: lo allunga sul posto e
 *     l'indirizzo non cambia;
 *   - non c'è spazio: alloca un blocco nuovo da un'altra parte, copia i
 *     dati e libera il vecchio. L'indirizzo cambia.
 *
 * Il programma non può sapere quale dei due casi capiterà: dopo realloc
 * si usa SOLO il puntatore restituito. Gli elementi aggiunti non sono
 * inizializzati (realloc non azzera come calloc).
 *
 * Esempio: le temperature della prima settimana di un mese, poi il blocco
 * si ingrandisce a 14 giorni per aggiungere la seconda settimana. Prima
 * della realloc il programma alloca un piccolo blocco "di disturbo"
 * subito dopo, così è probabile che la realloc debba spostare i dati.
 * Gli indirizzi stampati cambiano a ogni esecuzione.
 */

#include <stdio.h>
#include <stdlib.h>

#define SETTIMANA 7

void stampa(const double t[], int n);

int main(void)
{
    double prima[SETTIMANA] = {12.5, 13.0, 11.8, 14.2, 15.0, 13.6, 12.9};
    double seconda[SETTIMANA] = {14.1, 15.3, 16.0, 15.8, 14.4, 13.9, 15.2};
    double *temperature = malloc(SETTIMANA * sizeof *temperature);
    double *disturbo = malloc(sizeof *disturbo);
    double *nuovo;
    void *vecchio_indirizzo;
    int i;

    if (temperature == NULL || disturbo == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        for (i = 0; i < SETTIMANA; i++) {
            temperature[i] = prima[i];
        }
        printf("7 giorni in %p:\n", (void *) temperature);
        stampa(temperature, SETTIMANA);

        vecchio_indirizzo = temperature;
        nuovo = realloc(temperature, 2 * SETTIMANA * sizeof *nuovo);
        if (nuovo == NULL) {
            printf("Memoria insufficiente: restano 7 giorni.\n");
        } else {
            temperature = nuovo;
            printf("\n14 giorni in %p (%s)\n", (void *) temperature,
                   (void *) temperature == vecchio_indirizzo ? "stesso indirizzo"
                                                             : "blocco spostato");
            printf("i primi 7 valori sono stati conservati:\n");
            stampa(temperature, SETTIMANA);
            for (i = 0; i < SETTIMANA; i++) {
                temperature[SETTIMANA + i] = seconda[i];
            }
            printf("dopo aver scritto la seconda settimana:\n");
            stampa(temperature, 2 * SETTIMANA);
        }
    }

    free(temperature);
    free(disturbo);

    return 0;
}

void stampa(const double t[], int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf(" %4.1f", t[i]);
    }
    printf("\n");
}
