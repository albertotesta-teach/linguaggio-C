/*
 * 020-struttura-programma.c
 *
 * Anatomia di un programma C
 *
 * Mostra e commenta le parti fondamentali che compongono ogni programma C:
 * le direttive al preprocessore, la funzione main, le dichiarazioni di
 * variabili, le istruzioni e il valore di ritorno. Ogni sezione è spiegata
 * nel dettaglio per aiutare lo studente a riconoscere i blocchi costitutivi
 * del linguaggio.
 */

/* ── 1. DIRETTIVE AL PREPROCESSORE ────────────────────────────────────────
 * Le righe che iniziano con # sono elaborate prima della compilazione.
 * #include inserisce il contenuto di un file di intestazione (header).
 * <stdio.h> contiene le dichiarazioni di printf e scanf.
 * <stdlib.h> contiene costanti utili come EXIT_SUCCESS. */
#include <stdio.h>
#include <stdlib.h>

/* ── 2. COSTANTI SIMBOLICHE ────────────────────────────────────────────────
 * #define associa un nome a un valore. Il preprocessore sostituisce
 * ogni occorrenza del nome con il valore prima della compilazione.
 * Per convenzione i nomi delle costanti sono in MAIUSCOLO. */
#define VERSIONE 1
#define ANNO     2024

/* ── 3. FUNZIONE MAIN ──────────────────────────────────────────────────────
 * Ogni programma C deve avere esattamente una funzione main.
 * L'esecuzione inizia sempre da qui.
 * "int" indica che la funzione restituisce un numero intero al sistema.
 * "void" indica che non riceve argomenti dalla riga di comando. */
int main(void)
{
    /* ── 4. DICHIARAZIONI DI VARIABILI ─────────────────────────────────────
     * Le variabili si dichiarano indicando il tipo seguito dal nome.
     * In C (standard C89/C90) le dichiarazioni vanno all'inizio del blocco,
     * prima di qualsiasi istruzione. */
    int eta;
    double altezza;

    /* ── 5. ISTRUZIONI ─────────────────────────────────────────────────────
     * Ogni istruzione termina con il punto e virgola.
     * L'assegnazione copia il valore a destra nella variabile a sinistra. */
    eta     = 18;
    altezza = 1.75;

    /* ── 6. OUTPUT ─────────────────────────────────────────────────────────
     * printf formatta e stampa dati sullo schermo.
     * %d sostituisce un intero, %f un numero reale, \n va a capo. */
    printf("Programma di esempio - versione %d (%d)\n", VERSIONE, ANNO);
    printf("Eta':     %d anni\n", eta);
    printf("Altezza:  %.2f m\n", altezza);

    /* ── 7. VALORE DI RITORNO ──────────────────────────────────────────────
     * return 0 comunica al sistema operativo che il programma
     * è terminato correttamente (0 = nessun errore). */
    return 0;
}
