/*
 * 010-for-base.c
 *
 * Il ciclo for: ripetere un numero noto di volte
 *
 * Il for riunisce in una sola riga i tre elementi di ogni ciclo:
 *
 *     for (inizializzazione; condizione; aggiornamento) {
 *         corpo
 *     }
 *
 * ed è equivalente a:
 *
 *     inizializzazione;
 *     while (condizione) {
 *         corpo
 *         aggiornamento;
 *     }
 *
 * Si usa quando il numero di ripetizioni è noto (o calcolabile) prima di
 * iniziare: "per i che va da 1 a 10". Quando invece il ciclo dipende da
 * un evento (un dato letto, un obiettivo raggiunto) è più chiaro il while.
 *
 * La variabile di controllo è dichiarata all'inizio di main, come tutte le
 * altre variabili del corso (stile C89). Dal C99 si potrebbe dichiararla
 * dentro il for: for (int i = 0; ...), visibile solo nel ciclo.
 */

#include <stdio.h>

int main(void)
{
    int i;
    int contatore;

    /* ── 1. Da 1 a 10 ────────────────────────────────────────────── */
    printf("=== Da 1 a 10 ===\n");
    for (i = 1; i <= 10; i++) {
        printf("%d ", i);
    }
    printf("\n\n");

    /* ── 2. Lo stesso ciclo scritto con while ─────────────────────── */
    printf("=== Lo stesso con while ===\n");
    i = 1;
    while (i <= 10) {
        printf("%d ", i);
        i++;
    }
    printf("\n\n");

    /* ── 3. All'indietro ─────────────────────────────────────────── */
    printf("=== Da 10 a 1 ===\n");
    for (i = 10; i >= 1; i--) {
        printf("%d ", i);
    }
    printf("\n\n");

    /* ── 4. Passo diverso da 1 ───────────────────────────────────── */
    printf("=== Multipli di 5 fino a 50 ===\n");
    for (i = 5; i <= 50; i = i + 5) {
        printf("%d ", i);
    }
    printf("\n\n");

    printf("=== Potenze di 2 minori di 1000 ===\n");
    for (i = 1; i < 1000; i = i * 2) {
        printf("%d ", i);
    }
    printf("\n\n");

    /* ── 5. Quante volte viene eseguito il corpo? ─────────────────────
     *   for (i = 0; i < N; i++)    ->  N volte  (i = 0 ... N-1)
     *   for (i = 1; i <= N; i++)   ->  N volte  (i = 1 ... N)
     *   for (i = 1; i < N; i++)    ->  N-1 volte
     * La forma "da 0 a < N" sarà la più usata con gli array (cap. 04).  */
    printf("=== Conteggio delle iterazioni ===\n");
    contatore = 0;
    for (i = 0; i < 7; i++) {
        contatore++;
    }
    printf("for (i = 0; i < 7; i++)  -> %d iterazioni, alla fine i = %d\n", contatore, i);

    contatore = 0;
    for (i = 1; i <= 7; i++) {
        contatore++;
    }
    printf("for (i = 1; i <= 7; i++) -> %d iterazioni, alla fine i = %d\n", contatore, i);

    contatore = 0;
    for (i = 10; i < 7; i++) {
        contatore++;
    }
    printf("for (i = 10; i < 7; i++) -> %d iterazioni (condizione falsa subito)\n", contatore);

    /*
     * ERRORI COMUNI
     *
     * 1) Punto e virgola dopo la parentesi:
     *        for (i = 1; i <= 10; i++);      // ciclo con corpo vuoto
     *        {
     *            printf("%d ", i);           // eseguito UNA volta, con i = 11
     *        }
     *
     * 2) Errore di una unità (off-by-one): scrivere <= al posto di < o
     *    viceversa fa eseguire un'iterazione in più o in meno.
     *
     * 3) Modificare la variabile di controllo anche nel corpo:
     *        for (i = 0; i < 10; i++) {
     *            i = i + 2;                  // difficile capire quante volte gira
     *        }
     *    La variabile di un for si aggiorna solo nella terza parte.
     */

    return 0;
}
