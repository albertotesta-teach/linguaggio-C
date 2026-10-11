/*
 * 040-problema-media-mobile.c
 *
 * Qualità dell'aria in aula: media mobile della CO2
 *
 * Un sensore misura la concentrazione di anidride carbonica in un'aula ogni
 * 5 minuti, a partire dalle 8:00. Una singola lettura può essere disturbata
 * (qualcuno passa vicino al sensore), quindi si ragiona sulla MEDIA MOBILE:
 * la media di 3 letture consecutive. Quando la media supera SOGLIA ppm
 * bisogna aprire le finestre.
 *
 * Un puntatore, finestra, indica la prima delle 3 letture; le altre due sono
 * *(finestra + 1) e *(finestra + 2). Ad ogni passo finestra++ fa scorrere
 * il gruppo di una lettura. L'ultima posizione valida è fine - LARGHEZZA:
 * oltre, il gruppo uscirebbe dall'array.
 *
 * L'orario si ricava dall'indice della lettura, cioè finestra - &letture[0].
 */

#include <stdio.h>

#define LETTURE   12
#define LARGHEZZA 3
#define SOGLIA    1000                  /* ppm */
#define INTERVALLO 5                    /* minuti tra due letture */

void stampa_orario(int indice);

int main(void)
{
    int letture[LETTURE] = {620, 700, 790, 880, 960, 1050,
                            1120, 1080, 870, 760, 820, 910};
    const int *fine = &letture[0] + LETTURE;
    const int *finestra;
    const int *primo_allarme = NULL;
    int media;
    int allarmi = 0;

    printf("=== MEDIA MOBILE DELLA CO2 (gruppi di %d letture) ===\n", LARGHEZZA);
    for (finestra = &letture[0]; finestra <= fine - LARGHEZZA; finestra++) {
        media = (*finestra + *(finestra + 1) + *(finestra + 2)) / LARGHEZZA;

        printf("  ");
        stampa_orario(finestra - &letture[0]);
        printf("-");
        stampa_orario(finestra - &letture[0] + LARGHEZZA - 1);
        printf("   %4d %4d %4d   media %4d ppm",
               *finestra, *(finestra + 1), *(finestra + 2), media);
        if (media > SOGLIA) {
            printf("   <- aprire le finestre");
            allarmi++;
            if (primo_allarme == NULL) {
                primo_allarme = finestra;
            }
        }
        printf("\n");
    }

    if (primo_allarme == NULL) {
        printf("\nAria sempre sotto i %d ppm.\n", SOGLIA);
    } else {
        printf("\nPrimo allarme sul gruppo che inizia alle ");
        stampa_orario(primo_allarme - &letture[0]);
        printf(" (%d gruppi oltre soglia).\n", allarmi);
    }

    return 0;
}

/* Stampa l'orario hh:mm della lettura di indice dato. */
void stampa_orario(int indice)
{
    int minuti = 8 * 60 + indice * INTERVALLO;

    printf("%02d:%02d", minuti / 60, minuti % 60);
}
