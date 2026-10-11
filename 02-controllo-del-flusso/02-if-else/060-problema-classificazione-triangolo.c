/*
 * 060-problema-classificazione-triangolo.c
 *
 * Classificazione di un triangolo a partire dalla lunghezza dei lati
 *
 * Il programma riceve le lunghezze (intere, in cm) di tre segmenti e:
 *
 *   1. verifica che siano tutte positive;
 *   2. verifica che formino un triangolo: ogni lato deve essere minore
 *      della somma degli altri due (disuguaglianza triangolare);
 *   3. classifica il triangolo rispetto ai lati:
 *        equilatero (3 lati uguali), isoscele (2 uguali), scaleno (tutti diversi);
 *   4. verifica se è rettangolo con il teorema di Pitagora, provando
 *      ciascun lato come possibile ipotenusa.
 *
 * Ogni verifica ha senso solo se la precedente è superata: la struttura
 * è quindi una sequenza di if annidati, con condizioni composte.
 */

#include <stdio.h>

int main(void)
{
    int a;
    int b;
    int c;
    int lati_positivi;
    int triangolo_valido;
    int rettangolo;

    printf("=== CLASSIFICAZIONE DI UN TRIANGOLO ===\n\n");
    printf("Lunghezza dei tre lati in cm (es. 3 4 5): ");
    scanf("%d %d %d", &a, &b, &c);

    lati_positivi = (a > 0 && b > 0 && c > 0);

    if (!lati_positivi) {
        printf("\nErrore: le lunghezze devono essere positive.\n");
    } else {
        /* Disuguaglianza triangolare: vale per TUTTI e tre i lati (AND) */
        triangolo_valido = (a < b + c) && (b < a + c) && (c < a + b);

        if (!triangolo_valido) {
            printf("\nCon i lati %d, %d, %d non si puo' costruire un triangolo:\n", a, b, c);
            printf("un lato e' maggiore o uguale alla somma degli altri due.\n");
        } else {
            printf("\nI lati %d, %d, %d formano un triangolo.\n", a, b, c);

            /* ── Classificazione rispetto ai lati ─────────────────────
             * Prima il caso più restrittivo (tutti uguali), poi
             * "almeno due uguali": una delle tre coppie è uguale (OR). */
            if (a == b && b == c) {
                printf("Classificazione per lati: EQUILATERO\n");
            } else if (a == b || b == c || a == c) {
                printf("Classificazione per lati: ISOSCELE\n");
            } else {
                printf("Classificazione per lati: SCALENO\n");
            }

            /* ── Triangolo rettangolo ─────────────────────────────────
             * Non sappiamo quale lato sia il più lungo: proviamo tutte
             * e tre le possibilità di ipotenusa, unite da OR.            */
            rettangolo = (a * a + b * b == c * c)
                      || (a * a + c * c == b * b)
                      || (b * b + c * c == a * a);

            if (rettangolo) {
                printf("Il triangolo e' RETTANGOLO.\n");
            } else {
                printf("Il triangolo non e' rettangolo.\n");
            }

            printf("Perimetro: %d cm\n", a + b + c);
        }
    }

    /*
     * ERRORE COMUNE: controllare la disuguaglianza su un solo lato.
     *     triangolo_valido = (c < a + b);
     * Con i lati 10, 2, 3 la condizione è vera (3 < 12), ma il triangolo
     * non esiste perché 10 >= 2 + 3. Il controllo va fatto su tutti i lati.
     */

    return 0;
}
