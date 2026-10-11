/*
 * 010-while-base.c
 *
 * Il ciclo while: ripetere finché una condizione è vera
 *
 * Una struttura ITERATIVA (ciclo) ripete un blocco di istruzioni.
 * Il ciclo while controlla la condizione PRIMA di ogni ripetizione:
 *
 *     while (condizione) {
 *         corpo del ciclo
 *     }
 *
 *   1. si valuta la condizione
 *   2. se è falsa, il ciclo termina e si prosegue dopo la graffa chiusa
 *   3. se è vera, si esegue il corpo e si torna al punto 1
 *
 * Se la condizione è falsa già la prima volta, il corpo non viene
 * eseguito nemmeno una volta (zero iterazioni).
 *
 * Ogni ciclo while ben scritto ha tre elementi:
 *   - INIZIALIZZAZIONE della variabile di controllo (prima del ciclo)
 *   - CONDIZIONE che la controlla
 *   - AGGIORNAMENTO della variabile nel corpo, che prima o poi rende
 *     falsa la condizione (altrimenti il ciclo non finisce mai)
 */

#include <stdio.h>

int main(void)
{
    int conto;
    int numero;
    int somma;
    double risparmio;
    double obiettivo = 500.0;
    double versamento_settimanale = 35.0;
    int settimane;
    int bottiglie;

    /* ── 1. Conto alla rovescia ────────────────────────────────────── */
    printf("=== Conto alla rovescia ===\n");
    conto = 5;                       /* inizializzazione */
    while (conto > 0) {              /* condizione       */
        printf("%d... ", conto);
        conto--;                     /* aggiornamento    */
    }
    printf("partenza!\n\n");

    /* ── 2. Contatore e accumulatore ──────────────────────────────────
     * Somma dei numeri da 1 a 10: "numero" scorre i valori, "somma"
     * li accumula. Entrambe le variabili si inizializzano prima.      */
    printf("=== Somma dei numeri da 1 a 10 ===\n");
    numero = 1;
    somma = 0;
    while (numero <= 10) {
        somma = somma + numero;
        numero++;
    }
    printf("Somma = %d\n", somma);
    printf("Dopo il ciclo numero vale %d: e' il primo valore che ha reso falsa la condizione.\n\n",
           numero);

    /* ── 3. Numero di ripetizioni non noto in anticipo ────────────────
     * Il caso in cui il while è davvero necessario: non sappiamo quante
     * settimane servono, lo scopre il ciclo.                           */
    printf("=== Obiettivo di risparmio ===\n");
    risparmio = 0.0;
    settimane = 0;
    while (risparmio < obiettivo) {
        risparmio = risparmio + versamento_settimanale;
        settimane++;
    }
    printf("Versando %.2f euro a settimana, per arrivare a %.2f euro\n",
           versamento_settimanale, obiettivo);
    printf("servono %d settimane (risparmio finale: %.2f euro).\n\n",
           settimane, risparmio);

    /* ── 4. Zero iterazioni ───────────────────────────────────────────
     * Se la condizione è falsa subito, il corpo non viene mai eseguito. */
    printf("=== Zero iterazioni ===\n");
    bottiglie = 0;
    while (bottiglie > 0) {
        printf("Prendo una bottiglia.\n");
        bottiglie--;
    }
    printf("Bottiglie disponibili: %d, il ciclo non e' stato eseguito.\n", bottiglie);

    /*
     * ERRORI COMUNI
     *
     * 1) Aggiornamento dimenticato: ciclo infinito.
     *        conto = 5;
     *        while (conto > 0) {
     *            printf("%d\n", conto);     // conto resta 5 per sempre
     *        }
     *    Si interrompe il programma con Ctrl+C (o il tasto Stop di CLion).
     *
     * 2) Punto e virgola dopo la condizione:
     *        while (conto > 0);            // ciclo vuoto, infinito
     *        {
     *            conto--;
     *        }
     *
     * 3) Variabile di controllo non inizializzata:
     *        int somma;                    // valore indefinito
     *        while (...) { somma = somma + numero; ... }
     */

    return 0;
}
