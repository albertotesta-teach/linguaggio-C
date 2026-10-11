/*
 * 050-problema-parcheggio-multipiano.c
 *
 * Gestione di un parcheggio multipiano
 *
 * Il parcheggio ha 3 piani (0 = terra, 1, 2) da 6 posti. Ogni cella della
 * matrice contiene il numero della tessera dell'auto parcheggiata, oppure
 * 0 se il posto è libero.
 *
 * Menu ripetuto (do-while + switch):
 *   1 - Ingresso: l'auto riceve il PRIMO posto libero, cercando dal piano
 *       terra verso l'alto e, in ogni piano, dal posto 1 in avanti.
 *   2 - Uscita: data la tessera, il posto viene cercato e liberato.
 *   3 - Stato: mappa dei piani e posti liberi per piano.
 *   0 - Fine.
 *
 * Le due ricerche (posto libero, tessera) scorrono la matrice per righe e
 * si fermano al primo risultato grazie a un flag nelle condizioni dei
 * cicli annidati.
 */

#include <stdio.h>

#define PIANI  3
#define POSTI  6
#define LIBERO 0

int main(void)
{
    int parcheggio[PIANI][POSTI] = {
        {1201, 1202, 0, 1210, 1215, 1220},
        {1300, 0, 1302, 0, 0, 1310},
        {0, 0, 0, 0, 0, 0}
    };
    int scelta;
    int tessera;
    int piano;
    int posto;
    int trovato;
    int piano_trovato = 0;
    int posto_trovato = 0;
    int liberi_piano;

    printf("=== PARCHEGGIO CENTRO - CASSA AUTOMATICA ===\n");

    do {
        printf("\n1 - Ingresso   2 - Uscita   3 - Stato   0 - Fine\nScelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                printf("Numero tessera: ");
                scanf("%d", &tessera);

                trovato = 0;
                for (piano = 0; piano < PIANI && !trovato; piano++) {
                    for (posto = 0; posto < POSTI && !trovato; posto++) {
                        if (parcheggio[piano][posto] == LIBERO) {
                            trovato = 1;
                            piano_trovato = piano;
                            posto_trovato = posto;
                        }
                    }
                }

                if (trovato) {
                    parcheggio[piano_trovato][posto_trovato] = tessera;
                    printf("Tessera %d: piano %d, posto %d.\n",
                           tessera, piano_trovato, posto_trovato + 1);
                } else {
                    printf("Parcheggio completo.\n");
                }
                break;

            case 2:
                printf("Numero tessera: ");
                scanf("%d", &tessera);

                trovato = 0;
                for (piano = 0; piano < PIANI && !trovato; piano++) {
                    for (posto = 0; posto < POSTI && !trovato; posto++) {
                        if (parcheggio[piano][posto] == tessera) {
                            trovato = 1;
                            piano_trovato = piano;
                            posto_trovato = posto;
                        }
                    }
                }

                if (trovato && tessera != LIBERO) {
                    parcheggio[piano_trovato][posto_trovato] = LIBERO;
                    printf("Uscita registrata: liberato piano %d, posto %d.\n",
                           piano_trovato, posto_trovato + 1);
                } else {
                    printf("Tessera %d non presente nel parcheggio.\n", tessera);
                }
                break;

            case 3:
                for (piano = PIANI - 1; piano >= 0; piano--) {   /* dall'alto */
                    liberi_piano = 0;
                    printf("  Piano %d |", piano);
                    for (posto = 0; posto < POSTI; posto++) {
                        if (parcheggio[piano][posto] == LIBERO) {
                            printf("  ----");
                            liberi_piano++;
                        } else {
                            printf("  %4d", parcheggio[piano][posto]);
                        }
                    }
                    printf(" | liberi: %d\n", liberi_piano);
                }
                break;

            case 0:
                printf("Chiusura cassa.\n");
                break;

            default:
                printf("Scelta non valida.\n");
                break;
        }
    } while (scelta != 0);

    /*
     * NOTA: il valore 0 indica il posto libero, quindi la tessera 0 non
     * può esistere. Il controllo "tessera != LIBERO" nell'uscita evita
     * che la tessera 0 "liberi" un posto già libero.
     */

    return 0;
}
