/*
 * 040-problema-lancio-dado.c
 *
 * Problema reale: analisi statistica dei lanci di un dado.
 *
 * Scenario: un gioco da tavolo vuole verificare che un dado a sei facce
 * sia equilibrato. Il programma legge da tastiera una serie di lanci,
 * conta le uscite di ciascuna faccia usando un unico array di frequenze,
 * e mostra la distribuzione con un istogramma testuale.
 *
 * Struttura dati chiave:
 *  - un solo array di 6 interi: frequenze[0] conta la faccia 1,
 *    frequenze[1] conta la faccia 2, ..., frequenze[5] conta la faccia 6.
 *  - Il valore letto (1-6) diventa direttamente l'indice (valore - 1):
 *    non servono array paralleli perché il valore stesso è l'indice.
 *
 * Concetti applicati:
 *  - array come tabella di frequenze (contatore per valore)
 *  - accesso diretto per valore: frequenze[lancio - 1]++
 *  - validazione dell'input con ciclo while
 *  - scorrimento per stampa, ricerca di massimo e minimo
 */

#include <stdio.h>

#define NUM_FACCE  6
#define NUM_LANCI 30

int main(void) {

    /* Array delle frequenze: frequenze[i] conta quante volte è uscita
     * la faccia (i + 1). Inizializzato tutto a zero con {0}. */
    int frequenze[NUM_FACCE] = {0};

    int lancio;
    int i;
    int j;
    int valido;

    /* ------------------------------------------------------------------ */
    /* Acquisizione dei lanci con validazione */
    printf("=== ANALISI LANCI DADO ===\n");
    printf("Inserisci %d lanci (valore da 1 a %d):\n\n", NUM_LANCI, NUM_FACCE);

    for (i = 0; i < NUM_LANCI; i++) {
        valido = 0;
        while (!valido) {
            printf("  Lancio %2d: ", i + 1);
            scanf("%d", &lancio);
            if (lancio >= 1 && lancio <= NUM_FACCE) {
                valido = 1;
            } else {
                printf("  Valore non valido. Inserire un numero da 1 a %d.\n", NUM_FACCE);
            }
        }

        /* Il valore letto diventa l'indice: faccia 1 -> indice 0, ecc.
         * Questo è il punto chiave del problema: l'array viene usato
         * come tabella di conteggio indicizzata direttamente dal dato. */
        frequenze[lancio - 1] = frequenze[lancio - 1] + 1;
    }

    /* ------------------------------------------------------------------ */
    /* Stampa della tabella delle frequenze con istogramma */
    printf("\n=== RISULTATI ===\n");
    printf("  Faccia | Conteggio | Istogramma\n");
    printf("  -------|-----------|--------------------\n");

    for (i = 0; i < NUM_FACCE; i++) {
        printf("    %d    |    %3d    | ", i + 1, frequenze[i]);
        for (j = 0; j < frequenze[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Ricerca della faccia uscita più e meno volte */
    int max_freq = frequenze[0];
    int min_freq = frequenze[0];
    int faccia_max = 1;
    int faccia_min = 1;

    for (i = 1; i < NUM_FACCE; i++) {
        if (frequenze[i] > max_freq) {
            max_freq = frequenze[i];
            faccia_max = i + 1;
        }
        if (frequenze[i] < min_freq) {
            min_freq = frequenze[i];
            faccia_min = i + 1;
        }
    }

    printf("Faccia uscita piu' spesso : %d (%d volte)\n", faccia_max, max_freq);
    printf("Faccia uscita meno spesso : %d (%d volte)\n", faccia_min, min_freq);

    /* ------------------------------------------------------------------ */
    /* Frequenza attesa teorica per un dado equilibrato */
    printf("\nFrequenza attesa per dado equilibrato: %.1f volte per faccia\n",
           (double)NUM_LANCI / NUM_FACCE);

    return 0;
}
