/*
 * 050-problema-targa.c
 *
 * Problema reale: analisi di una targa automobilistica italiana.
 *
 * Scenario: un sistema di gestione di un parcheggio deve analizzare
 * le targhe dei veicoli in ingresso per estrarne le componenti
 * e verificare se il veicolo è immatricolato nel formato attuale
 * (introdotto nel 1994) o nel vecchio formato provinciale.
 *
 * Formato targa attuale (dal 1994):
 *   posizioni 0-1  → due lettere iniziali
 *   posizioni 2-4  → tre cifre
 *   posizioni 5-6  → due lettere finali
 *   esempio: FL519RX
 *
 * Concetti applicati:
 *   - dichiarazione e inizializzazione di stringhe
 *   - accesso ai caratteri tramite indice
 *   - ciclo while con condizione sul terminatore
 *   - verifica di caratteri con confronto diretto
 */

#include <stdio.h>

int main(void) {

    /* Targa del veicolo in ingresso al parcheggio.
     * Il formato italiano prevede esattamente 7 caratteri + '\0'. */
    char targa[8] = "FL519RX";

    /* Variabili di supporto per le componenti estratte */
    char lettere_iniziali[3]; /* prime due lettere + '\0' */
    char cifre[4];            /* tre cifre centrali + '\0' */
    char lettere_finali[3];   /* ultime due lettere + '\0' */

    /* Contatore per la verifica della lunghezza */
    int lunghezza = 0;

    /* Flags per la verifica del formato (0 = falso, 1 = vero) */
    int formato_valido  = 1; /* assume valido, falsifica se trova errori */
    int cifre_valide    = 1;
    int lettere_valide  = 1;

    /* Stampa la targa ricevuta */
    printf("=== SISTEMA DI GESTIONE PARCHEGGIO ===\n");
    printf("Targa rilevata: %s\n\n", targa);

    /* --- VERIFICA LUNGHEZZA ---
     * Conta i caratteri fino al terminatore '\0'.
     * Una targa italiana moderna ha sempre 7 caratteri. */
    while (targa[lunghezza] != '\0') {
        lunghezza++;
    }
    printf("Lunghezza targa: %d caratteri\n", lunghezza);

    if (lunghezza != 7) {
        /* Lunghezza errata: formato non riconosciuto */
        formato_valido = 0;
        printf("ERRORE: la targa non ha il formato corretto (attesi 7 caratteri).\n");
    }

    /* --- ESTRAZIONE COMPONENTI ---
     * Accesso diretto tramite indice: ogni componente
     * viene copiata carattere per carattere nel proprio array. */
    if (formato_valido) {

        /* Estrazione delle due lettere iniziali (indici 0 e 1) */
        lettere_iniziali[0] = targa[0];
        lettere_iniziali[1] = targa[1];
        lettere_iniziali[2] = '\0'; /* terminatore obbligatorio */

        /* Estrazione delle tre cifre centrali (indici 2, 3, 4) */
        cifre[0] = targa[2];
        cifre[1] = targa[3];
        cifre[2] = targa[4];
        cifre[3] = '\0'; /* terminatore obbligatorio */

        /* Estrazione delle due lettere finali (indici 5 e 6) */
        lettere_finali[0] = targa[5];
        lettere_finali[1] = targa[6];
        lettere_finali[2] = '\0'; /* terminatore obbligatorio */

        printf("\nComponenti estratte:\n");
        printf("  Lettere iniziali : %s\n", lettere_iniziali);
        printf("  Cifre centrali   : %s\n", cifre);
        printf("  Lettere finali   : %s\n", lettere_finali);
    }

    /* --- VERIFICA FORMATO ---
     * Il formato attuale prevede:
     * - posizioni 0,1,5,6 → lettere maiuscole (ASCII 65-90)
     * - posizioni 2,3,4   → cifre (ASCII 48-57) */
    if (formato_valido) {

        /* Verifica che le posizioni 0, 1, 5, 6 siano lettere maiuscole */
        if (targa[0] < 'A' || targa[0] > 'Z' ||
            targa[1] < 'A' || targa[1] > 'Z' ||
            targa[5] < 'A' || targa[5] > 'Z' ||
            targa[6] < 'A' || targa[6] > 'Z') {
            lettere_valide = 0;
        }

        /* Verifica che le posizioni 2, 3, 4 siano cifre */
        if (targa[2] < '0' || targa[2] > '9' ||
            targa[3] < '0' || targa[3] > '9' ||
            targa[4] < '0' || targa[4] > '9') {
            cifre_valide = 0;
        }

        printf("\nVerifica formato:\n");

        if (lettere_valide && cifre_valide) {
            printf("  Formato: VALIDO (targa italiana standard dal 1994)\n");
        }
        if (!lettere_valide) {
            printf("  ERRORE: le lettere non sono tutte maiuscole.\n");
        }
        if (!cifre_valide) {
            printf("  ERRORE: le cifre centrali non sono tutte numeriche.\n");
        }
    }

    /* --- INFORMAZIONI AGGIUNTIVE ---
     * Alcune combinazioni di lettere iniziali sono riservate
     * e non compaiono sulle targhe civili italiane. */
    if (formato_valido && lettere_valide && cifre_valide) {

        printf("\nInformazioni aggiuntive:\n");

        /* Le targhe che iniziano con FA-FZ sono assegnate alle forze armate */
        if (targa[0] == 'F' && targa[1] >= 'A' && targa[1] <= 'Z') {
            printf("  Serie %c%c: sequenza civile normale.\n",
                   targa[0], targa[1]);
        }

        /* Stampa il valore ASCII delle lettere iniziali a scopo didattico */
        printf("  Valore ASCII '%c': %d\n", targa[0], (int)targa[0]);
        printf("  Valore ASCII '%c': %d\n", targa[1], (int)targa[1]);
    }

    printf("\n=== FINE ANALISI ===\n");

    return 0;
}
