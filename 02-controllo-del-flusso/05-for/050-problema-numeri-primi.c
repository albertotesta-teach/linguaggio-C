/*
 * 050-problema-numeri-primi.c
 *
 * Numeri primi: verifica di un numero ed elenco fino a un limite
 *
 * Un numero intero n >= 2 è PRIMO se è divisibile solo per 1 e per se
 * stesso. Per verificarlo si cercano divisori tra 2 e la radice quadrata
 * di n: se n = a * b, almeno uno dei due fattori è <= sqrt(n).
 * La condizione d <= sqrt(n) si scrive senza radice come d * d <= n.
 *
 * Appena si trova un divisore la ricerca può fermarsi. Nel corso non si
 * usa break: la condizione del for contiene anche il flag "primo",
 * quindi il ciclo continua solo finché non è stato trovato un divisore.
 *
 *     for (d = 2; d * d <= n && primo; d++)
 *
 * Parte 1: verifica di un numero inserito, con il primo divisore trovato.
 * Parte 2: elenco dei primi fino a un limite (cicli annidati: il ciclo
 *          esterno scorre i numeri, quello interno cerca i divisori).
 */

#include <stdio.h>

#define PRIMI_PER_RIGA 10

int main(void)
{
    int n;
    int d;
    int primo;
    int divisore_trovato = 0;
    int limite;
    int numero;
    int conta_primi = 0;

    printf("=== NUMERI PRIMI ===\n\n");

    /* ── Parte 1: verifica di un numero ────────────────────────────── */
    do {
        printf("Numero da verificare (>= 2): ");
        scanf("%d", &n);
    } while (n < 2);

    primo = 1;          /* ipotesi: è primo finché non si trova un divisore */
    for (d = 2; d * d <= n && primo; d++) {
        if (n % d == 0) {
            primo = 0;
            divisore_trovato = d;
        }
    }

    if (primo) {
        printf("%d e' primo.\n\n", n);
    } else {
        printf("%d non e' primo: e' divisibile per %d (%d = %d x %d).\n\n",
               n, divisore_trovato, n, divisore_trovato, n / divisore_trovato);
    }

    /* ── Parte 2: elenco dei primi fino a un limite ───────────────── */
    do {
        printf("Elenca i primi fino a (>= 2): ");
        scanf("%d", &limite);
    } while (limite < 2);

    printf("\n");
    for (numero = 2; numero <= limite; numero++) {
        primo = 1;
        for (d = 2; d * d <= numero && primo; d++) {
            if (numero % d == 0) {
                primo = 0;
            }
        }

        if (primo) {
            printf("%6d", numero);
            conta_primi++;
            if (conta_primi % PRIMI_PER_RIGA == 0) {
                printf("\n");       /* a capo ogni 10 numeri */
            }
        }
    }
    if (conta_primi % PRIMI_PER_RIGA != 0) {
        printf("\n");
    }

    printf("\nTra 2 e %d ci sono %d numeri primi.\n", limite, conta_primi);

    /*
     * VERSIONE DA EVITARE (con break)
     *
     *     for (d = 2; d * d <= n; d++) {
     *         if (n % d == 0) {
     *             primo = 0;
     *             break;
     *         }
     *     }
     *
     * Funziona, ma la riga del for non dice più tutta la verità su quando
     * il ciclo termina. Vedi 06-break-continue.
     */

    return 0;
}
