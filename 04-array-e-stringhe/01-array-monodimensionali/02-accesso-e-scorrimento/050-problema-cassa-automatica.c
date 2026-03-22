/*
 * 050-problema-cassa-automatica.c
 *
 * Problema reale: calcolo del resto con le monete disponibili.
 *
 * Scenario: una cassa automatica deve restituire il resto a un cliente
 * usando il minor numero possibile di monete. Il programma memorizza
 * i tagli disponibili in un unico array (in ordine decrescente), scorre
 * l'array e sottrae il taglio più grande possibile finché il resto
 * non è zero, contando quante monete di ciascun taglio vengono usate.
 *
 * Struttura dati chiave:
 *  - un solo array di int per i tagli disponibili (in centesimi).
 *  - Un secondo array parallelo conta le monete usate per ogni taglio.
 *  - L'algoritmo è "greedy" (goloso): a ogni passo si usa il taglio
 *    più grande che non supera il resto rimanente.
 *
 * Concetti applicati:
 *  - scorrimento con condizione combinata (indice e valore residuo)
 *  - uso dell'indice per collegare taglio e contatore
 *  - aritmetica intera su centesimi per evitare errori floating point
 *  - input con validazione
 */

#include <stdio.h>

#define NUM_TAGLI 8

int main(void) {

    /* Tagli disponibili in centesimi, in ordine decrescente.
     * Lavorare in centesimi (interi) evita errori di arrotondamento
     * tipici della rappresentazione floating point. */
    int tagli[NUM_TAGLI] = {200, 100, 50, 20, 10, 5, 2, 1};

    /* Array parallelo: monete_usate[i] conta le monete del taglio tagli[i]
     * restituite come resto. Inizializzato a zero. */
    int monete_usate[NUM_TAGLI] = {0};

    int prezzo_centesimi;
    int pagato_centesimi;
    int resto;
    int valido;
    int i;

    /* ------------------------------------------------------------------ */
    /* Acquisizione del prezzo e dell'importo pagato */
    printf("=== CASSA AUTOMATICA ===\n\n");

    valido = 0;
    while (!valido) {
        printf("Prezzo articolo (in centesimi, es. 135 per 1,35 euro): ");
        scanf("%d", &prezzo_centesimi);
        if (prezzo_centesimi > 0) {
            valido = 1;
        } else {
            printf("Inserire un prezzo positivo.\n");
        }
    }

    valido = 0;
    while (!valido) {
        printf("Importo pagato  (in centesimi): ");
        scanf("%d", &pagato_centesimi);
        if (pagato_centesimi >= prezzo_centesimi) {
            valido = 1;
        } else {
            printf("Importo insufficiente. Inserire almeno %d centesimi.\n",
                   prezzo_centesimi);
        }
    }

    resto = pagato_centesimi - prezzo_centesimi;
    printf("\nPrezzo  : %d,%02d euro\n",
           prezzo_centesimi / 100, prezzo_centesimi % 100);
    printf("Pagato  : %d,%02d euro\n",
           pagato_centesimi / 100, pagato_centesimi % 100);
    printf("Resto   : %d,%02d euro\n\n",
           resto / 100, resto % 100);

    /* ------------------------------------------------------------------ */
    /* Algoritmo greedy: scorre i tagli dal più grande al più piccolo.
     * Per ogni taglio, calcola quante monete si possono usare senza
     * superare il resto rimanente, poi aggiorna il resto. */
    if (resto == 0) {
        printf("Nessun resto da restituire.\n");
    } else {
        printf("Composizione del resto:\n");

        for (i = 0; i < NUM_TAGLI; i++) {
            /* Quante monete di questo taglio entrano nel resto corrente? */
            monete_usate[i] = resto / tagli[i];

            /* Aggiorna il resto sottraendo le monete appena assegnate */
            resto = resto - monete_usate[i] * tagli[i];

            /* Stampa solo i tagli effettivamente usati */
            if (monete_usate[i] > 0) {
                printf("  %3d cent  x %d moneta/e\n",
                       tagli[i], monete_usate[i]);
            }
        }

        /* ---------------------------------------------------------------- */
        /* Verifica finale: il resto deve essere azzerato.
         * Con i tagli da 1 centesimo sempre disponibili, è garantito. */
        if (resto == 0) {
            printf("\nResto restituito correttamente.\n");
        } else {
            printf("\n[ERRORE] Resto non azzerabile con i tagli disponibili.\n");
        }
    }

    /* ------------------------------------------------------------------ */
    /* Conteggio totale delle monete restituite */
    int totale_monete = 0;
    for (i = 0; i < NUM_TAGLI; i++) {
        totale_monete = totale_monete + monete_usate[i];
    }
    printf("Totale monete restituite: %d\n", totale_monete);

    return 0;
}
