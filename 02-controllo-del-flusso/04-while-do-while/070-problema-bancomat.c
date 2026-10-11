/*
 * 070-problema-bancomat.c
 *
 * Simulazione di uno sportello bancomat
 *
 * Il menu viene mostrato almeno una volta e ripetuto finché l'utente non
 * sceglie di uscire: è lo schema tipico del do-while con uno switch
 * all'interno.
 *
 *   1 - Saldo        mostra il saldo disponibile
 *   2 - Prelievo     importi multipli di 10 euro, non oltre il saldo
 *                    e non oltre il limite giornaliero di 500 euro
 *   3 - Versamento   importo positivo
 *   0 - Esci         stampa il riepilogo delle operazioni
 *
 * Il break presente nel codice è quello dello switch: termina il case,
 * non il ciclo. Il ciclo termina solo tramite la sua condizione.
 */

#include <stdio.h>

#define LIMITE_GIORNALIERO 500
#define TAGLIO_MINIMO       10

int main(void)
{
    int saldo = 1250;            /* euro interi: il bancomat eroga banconote */
    int prelevato_oggi = 0;
    int scelta;
    int importo;
    int operazioni = 0;

    printf("=== BANCOMAT ===\n");

    do {
        printf("\n1 - Saldo   2 - Prelievo   3 - Versamento   0 - Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                printf("Saldo disponibile: %d euro\n", saldo);
                operazioni++;
                break;

            case 2:
                printf("Importo da prelevare: ");
                scanf("%d", &importo);

                /* Controlli in ordine: ognuno ha un messaggio specifico */
                if (importo <= 0 || importo % TAGLIO_MINIMO != 0) {
                    printf("Importo non valido: multipli di %d euro.\n", TAGLIO_MINIMO);
                } else if (importo > saldo) {
                    printf("Saldo insufficiente.\n");
                } else if (prelevato_oggi + importo > LIMITE_GIORNALIERO) {
                    printf("Limite giornaliero superato: puoi prelevare ancora %d euro.\n",
                           LIMITE_GIORNALIERO - prelevato_oggi);
                } else {
                    saldo = saldo - importo;
                    prelevato_oggi = prelevato_oggi + importo;
                    operazioni++;
                    printf("Ritirare %d euro. Nuovo saldo: %d euro\n", importo, saldo);
                }
                break;

            case 3:
                printf("Importo da versare: ");
                scanf("%d", &importo);
                if (importo > 0) {
                    saldo = saldo + importo;
                    operazioni++;
                    printf("Versamento eseguito. Nuovo saldo: %d euro\n", saldo);
                } else {
                    printf("Importo non valido.\n");
                }
                break;

            case 0:
                printf("Operazioni eseguite: %d. Saldo finale: %d euro. Arrivederci.\n",
                       operazioni, saldo);
                break;

            default:
                printf("Scelta non valida.\n");
                break;
        }

    } while (scelta != 0);

    /*
     * Perché do-while e non while?
     * Il menu va mostrato almeno una volta e la condizione dipende dalla
     * scelta dell'utente, che si conosce solo DOPO averlo mostrato.
     * Con un while servirebbe inizializzare scelta con un valore fittizio
     * (es. -1) solo per entrare nel ciclo la prima volta.
     */

    return 0;
}
