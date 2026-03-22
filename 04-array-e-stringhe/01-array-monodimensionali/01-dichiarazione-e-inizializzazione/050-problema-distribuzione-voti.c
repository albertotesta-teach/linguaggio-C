/*
 * 050-problema-distribuzione-voti.c
 *
 * Problema reale: distribuzione dei voti di una classe per fasce.
 *
 * Scenario: il coordinatore di classe vuole capire come si distribuiscono
 * i voti di un test tra le fasce di rendimento. Il programma legge i voti
 * di 20 studenti e conta quanti cadono in ciascuna fascia usando un unico
 * array di contatori: insufficiente (1-4), mediocre (5), sufficiente (6),
 * discreto (7), buono (8), ottimo (9-10).
 *
 * Struttura dati chiave:
 *  - un solo array di 6 interi, uno per fascia di rendimento.
 *  - La fascia viene determinata con una funzione di mappatura
 *    (voto -> indice) che usa if/else if, senza array paralleli.
 *
 * Concetti applicati:
 *  - array come contatori per categorie
 *  - mappatura valore -> indice con logica condizionale
 *  - calcolo percentuali da contatori
 *  - istogramma testuale proporzionale
 */

#include <stdio.h>

#define NUM_STUDENTI 20
#define NUM_FASCE     6

int main(void) {

    /* Array dei contatori per fascia di rendimento.
     * Indice 0: insufficiente (1-4)
     * Indice 1: mediocre     (5)
     * Indice 2: sufficiente  (6)
     * Indice 3: discreto     (7)
     * Indice 4: buono        (8)
     * Indice 5: ottimo       (9-10) */
    int contatori[NUM_FASCE] = {0};

    /* Etichette delle fasce: array di stringhe parallelo ai contatori.
     * Questo è l'unico array aggiuntivo, necessario solo per la stampa. */
    char etichette[NUM_FASCE][15] = {
        "Insuff. (1-4)",
        "Mediocre (5) ",
        "Suffic.  (6) ",
        "Discreto (7) ",
        "Buono    (8) ",
        "Ottimo (9-10)"
    };

    int voto;
    int indice_fascia;
    int i;
    int j;
    int valido;

    /* ------------------------------------------------------------------ */
    /* Acquisizione dei voti e aggiornamento dei contatori */
    printf("=== DISTRIBUZIONE VOTI CLASSE ===\n");
    printf("Inserisci i voti di %d studenti (da 1 a 10):\n\n", NUM_STUDENTI);

    for (i = 0; i < NUM_STUDENTI; i++) {
        valido = 0;
        while (!valido) {
            printf("  Studente %2d: ", i + 1);
            scanf("%d", &voto);
            if (voto >= 1 && voto <= 10) {
                valido = 1;
            } else {
                printf("  Voto non valido. Inserire un valore da 1 a 10.\n");
            }
        }

        /* Mappatura voto -> indice fascia.
         * La logica if/else if determina in quale cella incrementare.
         * Non si usano array paralleli: il voto viene classificato
         * e si agisce direttamente sull'indice corretto. */
        if (voto <= 4) {
            indice_fascia = 0;
        } else if (voto == 5) {
            indice_fascia = 1;
        } else if (voto == 6) {
            indice_fascia = 2;
        } else if (voto == 7) {
            indice_fascia = 3;
        } else if (voto == 8) {
            indice_fascia = 4;
        } else {
            indice_fascia = 5;   /* voto 9 o 10 */
        }

        contatori[indice_fascia] = contatori[indice_fascia] + 1;
    }

    /* ------------------------------------------------------------------ */
    /* Stampa della distribuzione con percentuale e istogramma */
    printf("\n=== DISTRIBUZIONE ===\n");
    printf("  Fascia          | N. | %%    | Grafico\n");
    printf("  ----------------|----|----- |--------------------\n");

    for (i = 0; i < NUM_FASCE; i++) {
        double percentuale = (double)contatori[i] / NUM_STUDENTI * 100.0;
        printf("  %s |  %2d | %4.1f%% | ",
               etichette[i], contatori[i], percentuale);

        /* Istogramma: un asterisco ogni studente nella fascia */
        for (j = 0; j < contatori[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Riepilogo: quanti studenti sono sotto la sufficienza */
    int insufficienti = contatori[0] + contatori[1];
    int sufficienti   = NUM_STUDENTI - insufficienti;

    printf("Studenti con voto insufficiente: %d su %d (%.0f%%)\n",
           insufficienti, NUM_STUDENTI,
           (double)insufficienti / NUM_STUDENTI * 100.0);
    printf("Studenti con voto sufficiente  : %d su %d (%.0f%%)\n",
           sufficienti, NUM_STUDENTI,
           (double)sufficienti / NUM_STUDENTI * 100.0);

    return 0;
}
