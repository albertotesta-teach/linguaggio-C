/*
 * 050-problema-misure-del-laboratorio.c
 *
 * Laboratorio di fisica: media, scarto e misure anomale del pendolo
 *
 * Ogni gruppo misura più volte il periodo di un pendolo con il
 * cronometro. Il numero di misure cambia da gruppo a gruppo, quindi
 * l'array delle misure si alloca dopo aver letto n.
 *
 * Il programma calcola:
 *   - la media delle misure;
 *   - lo scarto quadratico medio
 *         s = sqrt( somma (x[i] - media)^2 / (n - 1) )
 *     che dice quanto le misure si allontanano in genere dalla media;
 *   - le misure anomale, che distano dalla media più di 2 s (di solito
 *     un errore nel far partire o fermare il cronometro);
 *   - la media ricalcolata senza le misure anomale.
 *
 * Servono almeno 3 misure. Le misure si scrivono in secondi; un valore
 * non positivo o non numerico interrompe l'inserimento.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_MISURE 1000

int main(void)
{
    double *periodo;
    int n;
    int letti = 0;
    int i;
    int valide = 0;
    double somma = 0;
    double somma_quadrati = 0;
    double somma_valide = 0;
    double media;
    double scarto;
    int esito;
    int fine = 0;

    printf("Numero di misure (da 3 a %d): ", MAX_MISURE);
    if (scanf("%d", &n) != 1 || n < 3 || n > MAX_MISURE) {
        printf("Numero non valido.\n");
    } else {
        periodo = malloc(n * sizeof *periodo);
        if (periodo == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            printf("Periodi misurati in secondi:\n");
            while (letti < n && !fine) {
                esito = scanf("%lf", &periodo[letti]);
                if (esito == EOF) {
                    fine = 1;
                } else if (esito == 0 || periodo[letti] <= 0) {
                    if (esito == 0) {
                        scanf("%*s");   /* scarta la parola che non e' un numero */
                    }
                    printf("  misura %d non valida, ripetere\n", letti + 1);
                } else {
                    somma = somma + periodo[letti];
                    letti++;
                }
            }
        }

        if (periodo != NULL && letti < n) {
            printf("Input terminato: %s %d %s.\n", n - letti == 1 ? "manca" : "mancano",
                   n - letti, n - letti == 1 ? "misura" : "misure");
        } else if (periodo != NULL) {
            media = somma / n;
            for (i = 0; i < n; i++) {
                somma_quadrati = somma_quadrati + (periodo[i] - media) * (periodo[i] - media);
            }
            scarto = sqrt(somma_quadrati / (n - 1));
            printf("\nMedia: %.3f s   scarto: %.3f s\n", media, scarto);

            printf("Misure anomale (oltre %.3f s dalla media):\n", 2 * scarto);
            for (i = 0; i < n; i++) {
                if (fabs(periodo[i] - media) > 2 * scarto) {
                    printf("  misura %d: %.3f s\n", i + 1, periodo[i]);
                } else {
                    somma_valide = somma_valide + periodo[i];
                    valide++;
                }
            }
            if (valide == n) {
                printf("  nessuna\n");
            } else {
                printf("Media senza anomalie: %.3f s (%d misure)\n", somma_valide / valide,
                       valide);
            }
        }
        free(periodo);
    }

    return 0;
}
