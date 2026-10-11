/*
 * 080-problema-gruppi-di-lavoro.c
 *
 * Progetto di classe: voti di gruppi di dimensioni diverse
 *
 * Per il progetto di tecnologia la classe è divisa in quattro gruppi, con
 * un numero diverso di studenti. Ogni gruppo ha il proprio array di voti.
 * Una matrice 4 x 5 sprecherebbe spazio e richiederebbe un valore
 * speciale per le celle vuote; si usa invece un ARRAY DI PUNTATORI agli
 * array dei gruppi, con un secondo array per le dimensioni:
 *
 *     int *gruppi[4] = {rossi, blu, verdi, gialli};
 *     int studenti[4] = {3, 5, 4, 2};
 *
 *     gruppi[g][i]       voto dello studente i del gruppo g
 *     gruppi[g]          array del gruppo g, da passare alle funzioni
 *
 * Il programma stampa i voti e la media di ogni gruppo, il gruppo migliore
 * e il voto più alto della classe con il gruppo di appartenenza.
 */

#include <stdio.h>

#define GRUPPI 4

double media(const int *voti, int n);

int main(void)
{
    int rossi[3] = {7, 8, 6};
    int blu[5] = {9, 7, 8, 8, 6};
    int verdi[4] = {6, 6, 7, 5};
    int gialli[2] = {10, 8};
    int *gruppi[GRUPPI] = {rossi, blu, verdi, gialli};
    int studenti[GRUPPI] = {3, 5, 4, 2};
    const char *nomi[GRUPPI] = {"Rossi", "Blu", "Verdi", "Gialli"};
    int g;
    int i;
    int migliore = 0;
    const int *voto_max = &gruppi[0][0];
    int gruppo_max = 0;

    for (g = 0; g < GRUPPI; g++) {
        printf("  %-7s (%d)  voti:", nomi[g], studenti[g]);
        for (i = 0; i < studenti[g]; i++) {
            printf(" %2d", gruppi[g][i]);
            if (gruppi[g][i] > *voto_max) {
                voto_max = &gruppi[g][i];
                gruppo_max = g;
            }
        }
        printf("%*s media %.2f\n", 3 * (5 - studenti[g]), "", media(gruppi[g], studenti[g]));
        if (media(gruppi[g], studenti[g]) > media(gruppi[migliore], studenti[migliore])) {
            migliore = g;
        }
    }

    printf("\nGruppo con la media piu' alta: %s (%.2f)\n",
           nomi[migliore], media(gruppi[migliore], studenti[migliore]));
    printf("Voto piu' alto della classe: %d, nel gruppo %s\n", *voto_max, nomi[gruppo_max]);

    return 0;
}

double media(const int *voti, int n)
{
    int i;
    int somma = 0;

    for (i = 0; i < n; i++) {
        somma = somma + voti[i];
    }
    return (double) somma / n;
}
