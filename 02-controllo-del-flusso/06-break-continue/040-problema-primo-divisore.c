/*
 * 040-problema-primo-divisore.c
 *
 * Primo divisore e scomposizione in fattori primi
 *
 * Parte 1: dato un numero n >= 2, trovare il suo divisore più piccolo
 *          maggiore di 1. Se coincide con n, il numero è primo.
 * Parte 2: scomporre n in fattori primi, dividendo ripetutamente per il
 *          divisore più piccolo (es. 360 = 2^3 x 3^2 x 5).
 *
 * Nella parte 1 la ricerca si ferma appena trova un divisore. È il caso
 * classico in cui si userebbe break: qui la condizione del ciclo contiene
 * il flag "trovato".
 *
 * Nella parte 2 un ciclo interno divide per lo stesso fattore finché è
 * possibile (calcolando l'esponente); il ciclo esterno passa al fattore
 * successivo finché il numero non si riduce a 1.
 */

#include <stdio.h>

int main(void)
{
    int n;
    int d;
    int trovato;
    int divisore;
    int resto_da_scomporre;
    int fattore;
    int esponente;
    int primo_fattore_stampato;

    printf("=== PRIMO DIVISORE E FATTORI PRIMI ===\n\n");

    do {
        printf("Numero intero (>= 2): ");
        scanf("%d", &n);
    } while (n < 2);

    /* ── Parte 1: primo divisore ──────────────────────────────────────
     *
     *   VERSIONE DA EVITARE:
     *       for (d = 2; d <= n; d++) {
     *           if (n % d == 0) {
     *               break;
     *           }
     *       }
     *       divisore = d;
     *
     *   Basta cercare fino alla radice di n (d * d <= n): se non si trova
     *   nessun divisore entro quel limite, il primo divisore è n stesso. */
    trovato = 0;
    divisore = n;
    d = 2;
    while (d * d <= n && !trovato) {
        if (n % d == 0) {
            trovato = 1;
            divisore = d;
        } else {
            d++;
        }
    }

    printf("\nPrimo divisore maggiore di 1: %d\n", divisore);
    if (divisore == n) {
        printf("%d e' un numero primo.\n", n);
    } else {
        printf("%d = %d x %d\n", n, divisore, n / divisore);
    }

    /* ── Parte 2: scomposizione in fattori primi ──────────────────────
     * Si prova ogni fattore a partire da 2. Il ciclo interno divide
     * finché il fattore divide il numero: quando si passa al fattore
     * successivo, il precedente è stato "esaurito", quindi i fattori
     * trovati sono sempre primi.                                         */
    printf("\nScomposizione: %d = ", n);

    resto_da_scomporre = n;
    fattore = 2;
    primo_fattore_stampato = 0;

    while (resto_da_scomporre > 1) {
        esponente = 0;
        while (resto_da_scomporre % fattore == 0) {
            resto_da_scomporre = resto_da_scomporre / fattore;
            esponente++;
        }

        if (esponente > 0) {
            if (primo_fattore_stampato) {
                printf(" x ");
            }
            printf("%d", fattore);
            if (esponente > 1) {
                printf("^%d", esponente);
            }
            primo_fattore_stampato = 1;
        }

        fattore++;
    }
    printf("\n");

    /*
     * Nella parte 2 non serve nessun flag: la condizione naturale del
     * ciclo esterno ("c'è ancora qualcosa da scomporre") e quella del
     * ciclo interno ("il fattore divide ancora") descrivono già
     * esattamente quando fermarsi.
     */

    return 0;
}
