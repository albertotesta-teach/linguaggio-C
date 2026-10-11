/*
 * 030-evitare-continue.c
 *
 * Come scrivere i cicli senza continue
 *
 * continue serve a "saltare" il resto del corpo per alcuni valori.
 * Lo stesso effetto si ottiene, in modo esplicito, racchiudendo la parte
 * da eseguire in un if con la condizione OPPOSTA:
 *
 *   CON continue (da evitare)        SENZA continue
 *   -------------------------        ------------------------------
 *   for (...) {                      for (...) {
 *       if (da_scartare) {               if (!da_scartare) {
 *           continue;                        elaborazione;
 *       }                                }
 *       elaborazione;                }
 *   }
 *
 * Con l'if è evidente, dall'indentazione, quali istruzioni vengono
 * eseguite e in quali casi. Se per i valori scartati serve fare qualcosa
 * (contarli, segnalarli), lo si mette nel ramo else.
 *
 * La condizione opposta si ricava con De Morgan (01-logica-booleana).
 */

#include <stdio.h>

int main(void)
{
    int i;
    int somma;
    int stampati;
    int esclusi;

    /* ── 1. Somma dei soli dispari da 1 a 10 ──────────────────────────
     *
     *   CON continue:
     *       for (i = 1; i <= 10; i++) {
     *           if (i % 2 == 0) {
     *               continue;
     *           }
     *           somma = somma + i;
     *       }
     */
    printf("=== 1. Somma dei dispari da 1 a 10 ===\n");
    somma = 0;
    for (i = 1; i <= 10; i++) {
        if (i % 2 != 0) {
            somma = somma + i;
        }
    }
    printf("Somma: %d\n\n", somma);

    /* ── 2. Più condizioni di scarto ──────────────────────────────────
     * Numeri da 1 a 30 che NON sono multipli di 3 e NON finiscono per 5.
     *
     *   CON continue:
     *       if (i % 3 == 0) continue;
     *       if (i % 10 == 5) continue;
     *       stampa i;
     *
     *   SENZA continue: si scarta se (multiplo di 3) OR (finisce per 5);
     *   si tiene quando la condizione è falsa. Per De Morgan:
     *       !(i % 3 == 0 || i % 10 == 5)  =  i % 3 != 0 && i % 10 != 5
     */
    printf("=== 2. Da 1 a 30, esclusi multipli di 3 e numeri che finiscono per 5 ===\n");
    stampati = 0;
    esclusi = 0;
    for (i = 1; i <= 30; i++) {
        if (i % 3 != 0 && i % 10 != 5) {
            printf("%d ", i);
            stampati++;
        } else {
            esclusi++;          /* il ramo else gestisce gli scartati */
        }
    }
    printf("\nStampati: %d, esclusi: %d\n\n", stampati, esclusi);

    /* ── 3. Elaborazioni diverse invece di saltare ────────────────────
     * Spesso continue nasconde un if-else: qui i multipli di 10 vengono
     * segnalati invece di essere semplicemente saltati.               */
    printf("=== 3. Conteggio da 1 a 20 con segnalazione delle decine ===\n");
    for (i = 1; i <= 20; i++) {
        if (i % 10 == 0) {
            printf("[%d] ", i);
        } else {
            printf("%d ", i);
        }
    }
    printf("\n");

    /*
     * ATTENZIONE: continue in un while può creare cicli infiniti.
     *
     *     i = 0;
     *     while (i < 10) {
     *         if (i % 2 == 0) {
     *             continue;        // salta anche l'i++ che sta più sotto:
     *         }                    // i resta 0 per sempre
     *         i++;
     *     }
     *
     * Nel for il problema non c'è perché l'aggiornamento è
     * nell'intestazione: è un altro motivo per non affidarsi a continue.
     */

    return 0;
}
