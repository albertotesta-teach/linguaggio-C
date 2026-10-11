/*
 * 020-if-else.c
 *
 * L'istruzione if-else: scegliere tra due alternative
 *
 * Con if-else il programma esegue esattamente UNO dei due blocchi:
 *
 *     if (condizione) {
 *         blocco eseguito se la condizione è vera
 *     } else {
 *         blocco eseguito se la condizione è falsa
 *     }
 *
 * Non esiste un caso in cui vengano eseguiti entrambi, né un caso in cui
 * non ne venga eseguito nessuno.
 */

#include <stdio.h>

int main(void)
{
    int numero = 37;
    int a = 14;
    int b = 21;
    int maggiore;
    double saldo = 120.00;
    double prelievo = 200.00;
    int eta = 16;

    /* ── 1. Pari o dispari ────────────────────────────────────────────
     * Un numero è pari se il resto della divisione per 2 è zero.       */
    printf("=== Pari o dispari ===\n");
    if (numero % 2 == 0) {
        printf("%d e' pari\n", numero);
    } else {
        printf("%d e' dispari\n", numero);
    }
    printf("\n");

    /* ── 2. Il maggiore tra due numeri ────────────────────────────────
     * Entrambi i rami assegnano la stessa variabile: dopo l'if-else
     * "maggiore" ha sicuramente un valore.                             */
    printf("=== Maggiore tra due numeri ===\n");
    if (a > b) {
        maggiore = a;
    } else {
        maggiore = b;
    }
    printf("Tra %d e %d il maggiore e' %d\n\n", a, b, maggiore);

    /* ── 3. Operazione consentita o rifiutata ─────────────────────────
     * Il ramo else gestisce il caso "anomalo" con un messaggio.        */
    printf("=== Prelievo ===\n");
    printf("Saldo: %.2f euro, prelievo richiesto: %.2f euro\n", saldo, prelievo);
    if (prelievo <= saldo) {
        saldo = saldo - prelievo;
        printf("Prelievo eseguito. Nuovo saldo: %.2f euro\n", saldo);
    } else {
        printf("Prelievo rifiutato: saldo insufficiente.\n");
    }
    printf("\n");

    /* ── 4. if-else e operatore ternario ──────────────────────────────
     * Quando l'unico scopo è scegliere tra due VALORI, il ternario
     * (capitolo 01) è più compatto. Quando si devono eseguire
     * ISTRUZIONI diverse, si usa if-else.                              */
    printf("=== Ternario e if-else a confronto ===\n");
    printf("Con il ternario: %s\n", eta >= 18 ? "maggiorenne" : "minorenne");

    if (eta >= 18) {
        printf("Con if-else:     maggiorenne, puo' votare.\n");
    } else {
        printf("Con if-else:     minorenne, potra' votare tra %d anni.\n", 18 - eta);
    }

    /*
     * ERRORE COMUNE: due if separati al posto di un if-else.
     *
     *     if (prelievo <= saldo) {
     *         saldo = saldo - prelievo;
     *     }
     *     if (prelievo > saldo) {        // valutato DOPO aver cambiato saldo
     *         printf("Prelievo rifiutato\n");
     *     }
     *
     * Con saldo 300 e prelievo 200: il primo if porta il saldo a 100,
     * poi il secondo if trova 200 > 100 e stampa "rifiutato" anche se il
     * prelievo è avvenuto. Con else le due alternative si escludono.
     */

    return 0;
}
