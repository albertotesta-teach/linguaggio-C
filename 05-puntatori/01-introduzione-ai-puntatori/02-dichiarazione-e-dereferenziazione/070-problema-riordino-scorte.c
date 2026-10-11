/*
 * 070-problema-riordino-scorte.c
 *
 * Rifornire sempre il prodotto più scarso
 *
 * Il distributore automatico della scuola contiene tre prodotti: acqua,
 * succhi e snack. Il tecnico ha a disposizione CONFEZIONI confezioni da
 * DIM_CONFEZIONE pezzi e le distribuisce una alla volta, sempre al
 * prodotto che in quel momento ha la scorta più bassa.
 *
 * Le tre scorte sono variabili separate. La scelta si fa con un puntatore,
 * minimo, che a ogni giro viene fatto puntare alla variabile con il valore
 * più basso; poi si rifornisce la variabile puntata:
 *
 *     minimo = &acqua;
 *     if (succhi < *minimo) minimo = &succhi;
 *     if (snack  < *minimo) minimo = &snack;
 *     *minimo = *minimo + DIM_CONFEZIONE;
 *
 * Per stampare il nome del prodotto scelto si confronta il puntatore con
 * gli indirizzi delle tre variabili.
 */

#include <stdio.h>

#define CONFEZIONI     5
#define DIM_CONFEZIONE 12

int main(void)
{
    int acqua = 14;
    int succhi = 6;
    int snack = 9;
    int *minimo;
    int giro;

    printf("=== RIFORNIMENTO DEL DISTRIBUTORE ===\n");
    printf("Scorte iniziali: acqua %d, succhi %d, snack %d\n\n", acqua, succhi, snack);

    for (giro = 1; giro <= CONFEZIONI; giro++) {
        minimo = &acqua;
        if (succhi < *minimo) {
            minimo = &succhi;
        }
        if (snack < *minimo) {
            minimo = &snack;
        }

        *minimo = *minimo + DIM_CONFEZIONE;

        printf("Confezione %d -> ", giro);
        if (minimo == &acqua) {
            printf("acqua ");
        } else if (minimo == &succhi) {
            printf("succhi");
        } else {
            printf("snack ");
        }
        printf("   scorte: acqua %2d, succhi %2d, snack %2d\n", acqua, succhi, snack);
    }

    printf("\nIn caso di parita' viene rifornito il primo prodotto controllato,\n");
    printf("perche' il confronto usa < e non <=.\n");

    return 0;
}
