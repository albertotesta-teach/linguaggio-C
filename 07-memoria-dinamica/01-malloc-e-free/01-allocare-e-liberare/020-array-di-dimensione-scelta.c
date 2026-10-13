/*
 * 020-array-di-dimensione-scelta.c
 *
 * Un array la cui dimensione si conosce solo durante l'esecuzione
 *
 * Un array normale ha una dimensione fissata quando si compila: per
 * essere sicuri si sceglie un massimo (int voti[100]) e si spreca il
 * resto. Con malloc si chiede un blocco grande esattamente quanto serve:
 *
 *     int *v = malloc(n * sizeof *v);       n int consecutivi
 *
 *     v[0] ... v[n - 1]                      si usa come un array
 *
 * Il blocco contiene n elementi uno dopo l'altro, quindi v[i] funziona
 * come per un array (è *(v + i), visto nel capitolo dei puntatori). La
 * differenza è che sizeof v è la dimensione del puntatore, non del
 * blocco: il numero di elementi va tenuto in una variabile.
 *
 * Prima della malloc si controlla n: con n <= 0 non ha senso allocare,
 * e un n enorme farebbe fallire la richiesta.
 *
 * Esempio: le ore di sonno di ogni giorno di un periodo scelto da chi
 * usa il programma.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_GIORNI 366

int main(void)
{
    double *ore;
    int n;
    int i;
    int letto = 0;
    double totale = 0;

    printf("Quanti giorni (da 1 a %d)? ", MAX_GIORNI);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_GIORNI) {
        printf("Numero di giorni non valido.\n");
    } else {
        ore = malloc(n * sizeof *ore);
        if (ore == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            printf("Blocco di %d x %zu = %zu byte (sizeof ore = %zu)\n", n,
                   sizeof *ore, n * sizeof *ore, sizeof ore);
            i = 0;
            while (i < n && letto != EOF) {
                printf("Ore di sonno del giorno %d: ", i + 1);
                letto = scanf("%lf", &ore[i]);
                if (letto == 1 && ore[i] >= 0 && ore[i] <= 24) {
                    totale = totale + ore[i];
                    i++;
                } else if (letto != EOF) {
                    printf("  valore non valido (da 0 a 24)\n");
                }
                if (letto == 0) {
                    scanf("%*s");
                }
            }

            if (i < n) {
                printf("\nInput terminato prima del giorno %d.\n", i + 1);
            } else {
                printf("\nMedia: %.1f ore\n", totale / n);
                for (i = 0; i < n; i++) {
                    if (ore[i] < 8) {
                        printf("  giorno %d: %.1f ore, sotto le 8\n", i + 1, ore[i]);
                    }
                }
            }
            free(ore);
        }
    }

    return 0;
}
