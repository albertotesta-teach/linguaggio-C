/*
 * 060-problema-registro-voti.c
 *
 * Problema reale: registro elettronico dei voti di una classe.
 *
 * Scenario: un insegnante vuole un programma che memorizzi i voti
 * di matematica di 8 studenti, li visualizzi in un registro formattato
 * e calcoli la media della classe, il voto più alto e quello più basso.
 *
 * Concetti applicati:
 *  - dichiarazione e inizializzazione di un array di interi
 *  - scorrimento con ciclo for
 *  - calcolo di somma, minimo e massimo
 *  - stampa formattata con allineamento colonne
 */

#include <stdio.h>

#define NUMERO_STUDENTI 8

int main(void) {

    /* Nomi degli studenti e voti corrispondenti.
     * Gli array sono paralleli: nomi[i] corrisponde a voti[i]. */
    char nomi[NUMERO_STUDENTI][20] = {
        "Rossi Marco",
        "Bianchi Sara",
        "Verdi Luca",
        "Ferrari Anna",
        "Russo Pietro",
        "Colombo Giulia",
        "Marino Davide",
        "Greco Elena"
    };
    int voti[NUMERO_STUDENTI] = {7, 8, 6, 9, 5, 8, 7, 10};

    int i;
    int somma;
    int minimo;
    int massimo;
    int indice_min;
    int indice_max;

    /* ------------------------------------------------------------------ */
    /* Stampa del registro formattato */
    printf("============================================\n");
    printf("      REGISTRO VOTI - MATEMATICA            \n");
    printf("============================================\n");
    printf("  N.  | Nome               | Voto\n");
    printf("------|--------------------|------\n");

    for (i = 0; i < NUMERO_STUDENTI; i++) {
        printf("  %2d  | %-18s | %4d\n", i + 1, nomi[i], voti[i]);
    }
    printf("============================================\n\n");

    /* ------------------------------------------------------------------ */
    /* Calcolo della somma di tutti i voti.
     * Si parte da somma = 0 e si aggiunge ogni elemento. */
    somma = 0;
    for (i = 0; i < NUMERO_STUDENTI; i++) {
        somma = somma + voti[i];
    }

    printf("Media della classe : %.1f\n", (double)somma / NUMERO_STUDENTI);

    /* ------------------------------------------------------------------ */
    /* Ricerca del voto minimo e massimo. */
    minimo = voti[0];
    massimo = voti[0];
    indice_min = 0;
    indice_max = 0;

    for (i = 1; i < NUMERO_STUDENTI; i++) {
        if (voti[i] < minimo) {
            minimo = voti[i];
            indice_min = i;
        }
        if (voti[i] > massimo) {
            massimo = voti[i];
            indice_max = i;
        }
    }

    printf("Voto più basso     : %d (%s)\n", minimo, nomi[indice_min]);
    printf("Voto più alto      : %d (%s)\n", massimo, nomi[indice_max]);
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Conteggio studenti promossi (voto >= 6) e bocciati (voto < 6) */
    int promossi = 0;
    int bocciati = 0;

    for (i = 0; i < NUMERO_STUDENTI; i++) {
        if (voti[i] >= 6) {
            promossi = promossi + 1;
        } else {
            bocciati = bocciati + 1;
        }
    }

    printf("Studenti promossi  : %d su %d\n", promossi, NUMERO_STUDENTI);
    printf("Studenti bocciati  : %d su %d\n", bocciati, NUMERO_STUDENTI);

    return 0;
}
