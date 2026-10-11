/*
 * 050-problema-verifica-pin.c
 *
 * Verifica del PIN di una carta con al massimo 3 tentativi
 *
 * Un terminale di pagamento chiede il PIN della carta. Il PIN è di 5 cifre
 * (da 10000 a 99999). Dopo 3 tentativi errati la carta viene bloccata.
 * Un valore che non ha 5 cifre viene segnalato come formato errato e non
 * consuma un tentativo.
 *
 * Il ciclo ha due ragioni per terminare: PIN corretto o tentativi
 * esauriti. Entrambe compaiono nella condizione:
 *
 *     while (!pin_corretto && tentativi < MAX_TENTATIVI)
 *
 * Il formato errato, che con continue verrebbe "saltato", è gestito con
 * un if-else.
 */

#include <stdio.h>

#define PIN_CARTA     27183
#define MAX_TENTATIVI 3
#define PIN_MIN       10000
#define PIN_MAX       99999

int main(void)
{
    int pin_inserito;
    int tentativi = 0;
    int pin_corretto = 0;

    printf("=== TERMINALE POS ===\n");
    printf("Importo: 42,50 euro\n\n");

    while (!pin_corretto && tentativi < MAX_TENTATIVI) {
        printf("Inserire il PIN (5 cifre): ");
        scanf("%d", &pin_inserito);

        if (pin_inserito < PIN_MIN || pin_inserito > PIN_MAX) {
            /* VERSIONE DA EVITARE: printf(...); continue; */
            printf("  Formato non valido: il PIN ha 5 cifre.\n");
        } else {
            tentativi++;

            if (pin_inserito == PIN_CARTA) {
                pin_corretto = 1;
            } else {
                printf("  PIN errato. Tentativi rimasti: %d\n",
                       MAX_TENTATIVI - tentativi);
            }
        }
    }

    /* Il flag dice perché il ciclo è terminato */
    if (pin_corretto) {
        printf("\nPIN corretto. Pagamento autorizzato.\n");
    } else {
        printf("\nCarta BLOCCATA: troppi tentativi errati.\n");
    }

    /*
     * VERSIONE DA EVITARE (con break e continue)
     *
     *     while (tentativi < MAX_TENTATIVI) {
     *         scanf("%d", &pin_inserito);
     *         if (pin_inserito < PIN_MIN || pin_inserito > PIN_MAX) {
     *             continue;
     *         }
     *         tentativi++;
     *         if (pin_inserito == PIN_CARTA) {
     *             break;
     *         }
     *     }
     *
     * Dopo il ciclo non si sa più se si è usciti per il PIN corretto o
     * per i tentativi esauriti. Se l'esito si decidesse controllando
     * tentativi < MAX_TENTATIVI, un PIN corretto inserito al terzo
     * tentativo farebbe risultare la carta bloccata.
     */

    return 0;
}
