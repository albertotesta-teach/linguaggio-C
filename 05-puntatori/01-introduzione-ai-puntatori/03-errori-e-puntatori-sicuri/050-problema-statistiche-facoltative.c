/*
 * 050-problema-statistiche-facoltative.c
 *
 * Una funzione con risultati facoltativi
 *
 * Il registro elettronico calcola le statistiche dei voti di una verifica
 * con un'unica funzione:
 *
 *     int statistiche(const int voti[], int n,
 *                     int *minimo, int *massimo, double *media)
 *
 * I tre risultati escono dai parametri OUT. Non tutti i chiamanti però
 * hanno bisogno di tutto: la pagella vuole solo la media, il controllo
 * delle insufficienze solo il minimo. Chi non vuole un risultato passa
 * NULL al posto dell'indirizzo, e la funzione scrive solo nei puntatori
 * diversi da NULL.
 *
 * La funzione restituisce 0 se l'array è vuoto (n == 0): in quel caso non
 * scrive nulla, perché minimo, massimo e media non esistono.
 */

#include <stdio.h>

#define STUDENTI 8

int statistiche(const int voti[], int n, int *minimo, int *massimo, double *media);

int main(void)
{
    int verifica[STUDENTI] = {7, 5, 8, 6, 9, 4, 7, 6};
    int minimo;
    int massimo;
    double media;

    /* ── 1. Tutti i risultati ─────────────────────────────────────── */
    if (statistiche(verifica, STUDENTI, &minimo, &massimo, &media)) {
        printf("Verifica completa: minimo %d, massimo %d, media %.2f\n",
               minimo, massimo, media);
    }

    /* ── 2. Solo la media ─────────────────────────────────────────── */
    media = 0.0;
    if (statistiche(verifica, STUDENTI, NULL, NULL, &media)) {
        printf("Per la pagella serve solo la media: %.2f\n", media);
    }

    /* ── 3. Solo il minimo ────────────────────────────────────────── */
    if (statistiche(verifica, STUDENTI, &minimo, NULL, NULL)) {
        printf("Controllo insufficienze: voto minimo %d -> %s\n", minimo,
               minimo < 6 ? "ci sono insufficienze" : "nessuna insufficienza");
    }

    /* ── 4. Array vuoto ───────────────────────────────────────────── */
    if (!statistiche(verifica, 0, &minimo, &massimo, &media)) {
        printf("Verifica senza voti: statistiche non disponibili\n");
    }

    return 0;
}

/* Calcola minimo, massimo e media dei primi n voti e li scrive solo nei
 * puntatori diversi da NULL. Restituisce 1 se n > 0, altrimenti 0. */
int statistiche(const int voti[], int n, int *minimo, int *massimo, double *media)
{
    int k;
    int min;
    int max;
    int somma = 0;
    int calcolato = 0;

    if (n > 0) {
        min = voti[0];
        max = voti[0];
        for (k = 0; k < n; k++) {
            somma = somma + voti[k];
            if (voti[k] < min) {
                min = voti[k];
            }
            if (voti[k] > max) {
                max = voti[k];
            }
        }
        if (minimo != NULL) {
            *minimo = min;
        }
        if (massimo != NULL) {
            *massimo = max;
        }
        if (media != NULL) {
            *media = (double) somma / n;
        }
        calcolato = 1;
    }
    return calcolato;
}
