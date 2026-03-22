/*
 * 080-problema-rilevamento-traffico.c
 *
 * Problema reale: analisi del traffico su strade urbane.
 *
 * Scenario: un sistema di rilevamento del traffico monitora 8 strade
 * e conta i veicoli transitati in un'ora. Il programma identifica le
 * strade congestioniate (sopra soglia), trova le tre strade più trafficate
 * tramite ricerca ripetuta del massimo (senza algoritmo di ordinamento
 * formale) e calcola la densità media.
 *
 * Concetti applicati:
 *  - ricerca del massimo con azzeramento temporaneo (top-3 senza sort)
 *  - confronto con soglia e conteggio
 *  - array paralleli (nomi strade e conteggi veicoli)
 *  - calcolo di media su array intero
 */

#include <stdio.h>

#define STRADE        8
#define SOGLIA_CONGESTIONE 800   /* veicoli/ora oltre i quali la strada è congestionata */
#define TOP_N         3          /* numero di strade da mostrare nella classifica */

int main(void) {

    char nomi[STRADE][25] = {
        "Via Roma",
        "Corso Italia",
        "Via Garibaldi",
        "Viale Europa",
        "Via Mazzini",
        "Corso Vittorio",
        "Via Dante",
        "Piazza Duomo"
    };
    int veicoli[STRADE] = {620, 950, 430, 1120, 780, 870, 310, 1050};

    int i;
    int j;

    /* ------------------------------------------------------------------ */
    /* Stampa del riepilogo del traffico */
    printf("=== RILEVAMENTO TRAFFICO URBANO ===\n");
    printf("  %-22s | Veicoli/h | Stato\n", "Strada");
    printf("  -----------------------|-----------|----------\n");

    for (i = 0; i < STRADE; i++) {
        char stato[15];
        if (veicoli[i] > SOGLIA_CONGESTIONE) {
            stato[0]='C'; stato[1]='O'; stato[2]='N'; stato[3]='G';
            stato[4]='E'; stato[5]='S'; stato[6]='T'; stato[7]='A';
            stato[8]='\0';
        } else {
            stato[0]='S'; stato[1]='C'; stato[2]='O'; stato[3]='R';
            stato[4]='R'; stato[5]='E'; stato[6]='V'; stato[7]='O';
            stato[8]='L'; stato[9]='E'; stato[10]='\0';
        }
        printf("  %-22s |    %4d   | %s\n", nomi[i], veicoli[i], stato);
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Strade congestioniate e densità media */
    int somma = 0;
    int congestionate = 0;

    printf("Strade congestioniate (> %d veicoli/h):\n", SOGLIA_CONGESTIONE);
    for (i = 0; i < STRADE; i++) {
        somma = somma + veicoli[i];
        if (veicoli[i] > SOGLIA_CONGESTIONE) {
            printf("  [!] %-22s : %d veicoli/h\n", nomi[i], veicoli[i]);
            congestionate++;
        }
    }
    if (congestionate == 0) {
        printf("  Nessuna strada congestionata.\n");
    }
    printf("\nDensita' media : %.0f veicoli/h\n", (double)somma / STRADE);
    printf("Congestioniate : %d su %d strade\n\n", congestionate, STRADE);

    /* ------------------------------------------------------------------ */
    /* Top-3 strade più trafficate: ricerca ripetuta del massimo.
     * Tecnica: a ogni passaggio si trova il massimo tra i valori non ancora
     * selezionati. Si usa un array booleano 'selezionato' per marcare
     * le strade già inserite nella classifica.
     *
     * Nota didattica: questa tecnica è concettualmente equivalente alla
     * prima fase dell'ordinamento per selezione (selection sort), che
     * verrà trattato formalmente nel capitolo 11. */
    int selezionato[STRADE] = {0};   /* 0 = non ancora selezionata */

    printf("Top-%d strade piu' trafficate:\n", TOP_N);

    for (j = 1; j <= TOP_N; j++) {
        /* Trova il massimo tra le strade non ancora selezionate */
        int indice_max = -1;

        for (i = 0; i < STRADE; i++) {
            if (!selezionato[i]) {
                if (indice_max == -1 || veicoli[i] > veicoli[indice_max]) {
                    indice_max = i;
                }
            }
        }

        /* Segna la strada trovata come selezionata e stampa il risultato */
        selezionato[indice_max] = 1;
        printf("  %d° posto: %-22s (%d veicoli/h)\n",
               j, nomi[indice_max], veicoli[indice_max]);
    }

    return 0;
}
