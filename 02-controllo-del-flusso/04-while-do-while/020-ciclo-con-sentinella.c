/*
 * 020-ciclo-con-sentinella.c
 *
 * Leggere dati finché l'utente non inserisce un valore di fine
 *
 * Spesso non si sa in anticipo quanti dati verranno inseriti: si chiede
 * all'utente di terminare con un valore speciale, detto SENTINELLA, che
 * non può essere un dato valido (qui lo 0, perché le spese sono positive).
 *
 * Schema della "lettura anticipata":
 *
 *     leggi il primo valore
 *     while (valore != SENTINELLA) {
 *         elabora il valore
 *         leggi il valore successivo
 *     }
 *
 * La prima lettura avviene PRIMA del ciclo e le successive alla FINE del
 * corpo: così la sentinella viene controllata subito dopo essere stata
 * letta e non viene mai elaborata come dato.
 */

#include <stdio.h>

#define SENTINELLA 0

int main(void)
{
    double spesa;
    double totale = 0.0;
    double massima = 0.0;
    int numero_spese = 0;

    printf("=== NOTA SPESE ===\n");
    printf("Inserisci gli importi delle spese (0 per terminare).\n\n");

    /* Lettura anticipata */
    printf("Spesa: ");
    scanf("%lf", &spesa);

    while (spesa != SENTINELLA) {
        if (spesa < 0) {
            printf("  Importo negativo ignorato.\n");
        } else {
            numero_spese++;
            totale = totale + spesa;

            /* Massimo senza array: si confronta ogni nuovo valore con il
             * massimo trovato finora. La prima spesa valida diventa
             * subito il massimo. */
            if (numero_spese == 1 || spesa > massima) {
                massima = spesa;
            }
        }

        /* Lettura successiva, alla fine del corpo */
        printf("Spesa: ");
        scanf("%lf", &spesa);
    }

    printf("\n--- Riepilogo ---\n");
    if (numero_spese > 0) {
        printf("Spese inserite : %d\n", numero_spese);
        printf("Totale         : %.2f euro\n", totale);
        printf("Media          : %.2f euro\n", totale / numero_spese);
        printf("Spesa maggiore : %.2f euro\n", massima);
    } else {
        printf("Nessuna spesa inserita.\n");
    }

    /*
     * ERRORE COMUNE: leggere solo all'inizio del corpo.
     *
     *     while (spesa != SENTINELLA) {
     *         scanf("%lf", &spesa);
     *         totale = totale + spesa;      // somma anche lo 0 finale
     *     }
     *
     * Oltre a elaborare la sentinella, il primo controllo usa una
     * variabile non ancora letta. Nota anche il controllo
     * numero_spese > 0 prima di calcolare la media: evita la divisione
     * per zero quando l'utente inserisce subito la sentinella.
     */

    return 0;
}
