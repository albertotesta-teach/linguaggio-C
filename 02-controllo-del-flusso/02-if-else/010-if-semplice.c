/*
 * 010-if-semplice.c
 *
 * L'istruzione if: eseguire un blocco solo se una condizione è vera
 *
 * Finora le istruzioni di un programma venivano eseguite tutte, una dopo
 * l'altra (struttura SEQUENZIALE). Con if il programma può SALTARE un
 * blocco di istruzioni quando una condizione è falsa:
 *
 *     if (condizione) {
 *         istruzioni eseguite solo se la condizione è vera
 *     }
 *     istruzioni eseguite in ogni caso
 *
 * Nota: un if/else è già comparso nel capitolo 01, in
 * 01-introduzione/02-variabili-e-tipi/060-problema-calcolo-area.c,
 * per scegliere la figura geometrica. Qui il costrutto viene presentato
 * in modo completo.
 */

#include <stdio.h>

#define SOGLIA_CALDO     30
#define SPESA_MIN_SCONTO 50.0

int main(void)
{
    int temperatura = 33;
    double spesa = 64.80;
    double sconto = 0.0;
    int punti = 120;
    int livello_oro;

    /* ── 1. if con un solo ramo ───────────────────────────────────────
     * Il messaggio di allerta viene stampato solo se fa molto caldo;
     * l'ultima printf viene eseguita sempre.                            */
    printf("=== Allerta caldo ===\n");
    printf("Temperatura: %d gradi\n", temperatura);

    if (temperatura > SOGLIA_CALDO) {
        printf("ATTENZIONE: temperatura sopra i %d gradi, bere molta acqua.\n",
               SOGLIA_CALDO);
    }

    printf("Fine del bollettino.\n\n");

    /* ── 2. if che modifica una variabile ─────────────────────────────
     * Caso tipico: il valore di partenza (sconto = 0) vale "di default"
     * e l'if lo cambia solo quando serve.                               */
    printf("=== Sconto sulla spesa ===\n");
    printf("Spesa: %.2f euro\n", spesa);

    if (spesa >= SPESA_MIN_SCONTO) {
        sconto = spesa * 0.10;
    }

    printf("Sconto: %.2f euro\n", sconto);
    printf("Da pagare: %.2f euro\n\n", spesa - sconto);

    /* ── 3. Condizione salvata in una variabile booleana ──────────────
     * Una condizione complessa si può calcolare prima e dare un nome:
     * l'if diventa leggibile come una frase.                            */
    printf("=== Programma fedelta' ===\n");
    printf("Punti accumulati: %d\n", punti);

    livello_oro = (punti >= 100);

    if (livello_oro) {
        printf("Livello ORO raggiunto: spedizione gratuita.\n");
    }

    /* if (livello_oro) equivale a if (livello_oro != 0):
     * qualunque valore diverso da 0 è vero (vedi 01-logica-booleana). */

    /*
     * ERRORI COMUNI
     *
     * 1) Punto e virgola dopo la condizione:
     *        if (temperatura > SOGLIA_CALDO);
     *        {
     *            printf("ATTENZIONE...");
     *        }
     *    Il ";" chiude un if con istruzione VUOTA: il blocco tra graffe
     *    viene eseguito sempre. gcc con -Wextra lo segnala.
     *
     * 2) Omettere le graffe:
     *        if (spesa >= SPESA_MIN_SCONTO)
     *            sconto = spesa * 0.10;
     *            printf("Sconto applicato\n");   // eseguita SEMPRE
     *    Senza graffe l'if controlla solo la prima istruzione:
     *    l'indentazione non conta per il compilatore.
     *    Nel corso le graffe si scrivono sempre, anche per una sola istruzione.
     *
     * 3) Assegnazione al posto del confronto:
     *        if (punti = 100)    // assegna 100 e la condizione è sempre vera
     *        if (punti == 100)   // corretto
     */

    return 0;
}
