/*
 * 040-problema-istogramma-dei-voti.c
 *
 * L'istogramma dei voti di una verifica, con la scala scelta dal docente
 *
 * Ogni docente usa la sua scala: c'è chi dà voti da 1 a 10 e chi da 3 a
 * 10, sempre con i mezzi voti. Il programma legge il voto minimo e il
 * massimo della scala e alloca un contatore per ogni voto possibile:
 *
 *     categorie = (massimo - minimo) * 2 + 1      da 3 a 10: 15 voti
 *     int *conta = calloc(categorie, sizeof *conta);
 *
 *     voto 6.5  ->  indice (6.5 - minimo) * 2
 *
 * Poi legge i voti fino a FINE (scartando quelli fuori scala o non
 * multipli di 0.5) e stampa l'istogramma dal voto più alto al più basso,
 * il voto più frequente e la percentuale di sufficienze.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int indice(double voto, int minimo);

int main(void)
{
    int *conta;
    int minimo;
    int massimo;
    int categorie;
    int totale = 0;
    int sufficienti = 0;
    int moda = 0;
    int finito = 0;
    int k;
    int i;
    double voto;
    char parola[16];
    char dopo;

    printf("Scala dei voti (minimo massimo): ");
    if (scanf("%d %d", &minimo, &massimo) != 2 || minimo < 1 || massimo > 10 ||
        minimo >= massimo) {
        printf("Scala non valida.\n");
    } else {
        categorie = (massimo - minimo) * 2 + 1;
        conta = calloc(categorie, sizeof *conta);
        if (conta == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            printf("%d contatori azzerati da calloc\n", categorie);
            printf("Voti (FINE per terminare):\n");
            while (!finito) {
                if (scanf("%15s", parola) != 1 || strcmp(parola, "FINE") == 0) {
                    finito = 1;
                } else if (sscanf(parola, "%lf%c", &voto, &dopo) != 1 || voto < minimo ||
                           voto > massimo || voto * 2 != (int) (voto * 2)) {
                    printf("  %s scartato\n", parola);
                } else {
                    conta[indice(voto, minimo)]++;
                    totale++;
                    if (voto >= 6) {
                        sufficienti++;
                    }
                }
            }

            printf("\n");
            for (k = categorie - 1; k >= 0; k--) {
                printf("%4.1f |", minimo + k / 2.0);
                for (i = 0; i < conta[k]; i++) {
                    printf(" *");
                }
                printf("\n");
                if (conta[k] > conta[moda]) {
                    moda = k;
                }
            }
            if (totale > 0) {
                printf("Voti: %d, piu' frequente: %.1f (%d volte), sufficienze: %.0f%%\n",
                       totale, minimo + moda / 2.0, conta[moda], 100.0 * sufficienti / totale);
            }
            free(conta);
        }
    }

    return 0;
}

int indice(double voto, int minimo)
{
    return (int) ((voto - minimo) * 2);
}
