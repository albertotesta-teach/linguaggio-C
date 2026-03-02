/*
 * 060-problema-conta-vocali.c
 *
 * Problema reale: analisi fonetica di base di un testo.
 *
 * Scenario: un'applicazione di analisi linguistica riceve in input
 * un testo e ne calcola la distribuzione delle vocali. Questo tipo
 * di analisi è usata in linguistica computazionale, nel riconoscimento
 * vocale e nella generazione automatica di testo.
 *
 * Il programma legge una stringa con spazi (fgets), la scansiona
 * carattere per carattere e conta le occorrenze di ciascuna vocale
 * (a, e, i, o, u) distinguendo maiuscole e minuscole, poi mostra
 * una barra di distribuzione testuale.
 *
 * Concetti applicati:
 *   - lettura di stringa con spazi tramite fgets
 *   - scansione con ciclo while
 *   - confronto multiplo per classificare un carattere
 *   - contatori distinti per ogni vocale
 *   - output con barra di distribuzione testuale
 */

#include <stdio.h>

int main(void) {

    /* Buffer per il testo da analizzare */
    char testo[201]; /* max 200 caratteri + '\0' */

    /* Contatori per ogni vocale (maiuscole + minuscole insieme) */
    int conta_a = 0;
    int conta_e = 0;
    int conta_i = 0;
    int conta_o = 0;
    int conta_u = 0;
    int totale_vocali    = 0;
    int totale_caratteri = 0;

    /* Carattere corrente */
    char c;

    /* Indice per scorrere il testo e rimuovere '\n' */
    int i;

    /* Variabile per la barra di distribuzione */
    int barra;

    printf("=== ANALISI FONETICA - DISTRIBUZIONE VOCALI ===\n\n");

    /* --- LETTURA DEL TESTO ---
     * fgets per permettere spazi e punteggiatura. */
    printf("Inserisci il testo da analizzare:\n> ");
    fgets(testo, 201, stdin);

    /* Rimozione '\n' lasciato da fgets */
    i = 0;
    while (testo[i] != '\n' && testo[i] != '\0') {
        i++;
    }
    testo[i] = '\0';

    /* --- SCANSIONE E CONTEGGIO ---
     * Scorriamo il testo carattere per carattere.
     * Per ogni carattere verifichiamo se è una delle cinque vocali
     * (maiuscola o minuscola) e aggiorniamo il contatore corrispondente. */
    i = 0;
    while (testo[i] != '\0') {
        c = testo[i];
        totale_caratteri++;

        if (c == 'a' || c == 'A') {
            conta_a++;
            totale_vocali++;
        } else if (c == 'e' || c == 'E') {
            conta_e++;
            totale_vocali++;
        } else if (c == 'i' || c == 'I') {
            conta_i++;
            totale_vocali++;
        } else if (c == 'o' || c == 'O') {
            conta_o++;
            totale_vocali++;
        } else if (c == 'u' || c == 'U') {
            conta_u++;
            totale_vocali++;
        }

        i++;
    }

    /* --- OUTPUT RISULTATI ---
     * Mostra i contatori e una barra di distribuzione testuale.
     * Ogni '#' nella barra rappresenta una occorrenza della vocale. */
    printf("\n");
    printf("Testo analizzato: \"%s\"\n\n", testo);
    printf("════════════════════════════════════════════\n");
    printf("  DISTRIBUZIONE VOCALI\n");
    printf("════════════════════════════════════════════\n");
    printf("%-6s %-5s %s\n", "Vocale", "Num.", "Distribuzione");
    printf("--------------------------------------------\n");

    /* Vocale A */
    printf("  A/a : %3d  [", conta_a);
    barra = 0;
    while (barra < conta_a) {
        putchar('#');
        barra++;
    }
    printf("]\n");

    /* Vocale E */
    printf("  E/e : %3d  [", conta_e);
    barra = 0;
    while (barra < conta_e) {
        putchar('#');
        barra++;
    }
    printf("]\n");

    /* Vocale I */
    printf("  I/i : %3d  [", conta_i);
    barra = 0;
    while (barra < conta_i) {
        putchar('#');
        barra++;
    }
    printf("]\n");

    /* Vocale O */
    printf("  O/o : %3d  [", conta_o);
    barra = 0;
    while (barra < conta_o) {
        putchar('#');
        barra++;
    }
    printf("]\n");

    /* Vocale U */
    printf("  U/u : %3d  [", conta_u);
    barra = 0;
    while (barra < conta_u) {
        putchar('#');
        barra++;
    }
    printf("]\n");

    printf("--------------------------------------------\n");
    printf("  Totale vocali    : %d su %d caratteri\n",
           totale_vocali, totale_caratteri);

    if (totale_caratteri > 0) {
        printf("  Densità vocalica : %d%%\n",
               (totale_vocali * 100) / totale_caratteri);
    }

    printf("════════════════════════════════════════════\n");

    return 0;
}
