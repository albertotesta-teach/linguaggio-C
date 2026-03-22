/*
 * 050-problema-contatore-caratteri.c
 *
 * Problema reale: analisi della frequenza delle lettere in un testo.
 *
 * Scenario: un programma di analisi testuale conta quante volte appare
 * ciascuna lettera dell'alfabeto in un testo fisso. Il risultato serve
 * per capire la distribuzione delle lettere (utile in crittografia,
 * compressione dati, linguistica computazionale).
 *
 * Struttura dati chiave:
 *  - un solo array di 26 interi: frequenze[0] conta le 'a', ...,
 *    frequenze[25] conta le 'z'.
 *  - Il carattere letto viene convertito in indice con: indice = c - 'a'
 *    (sfrutta la consecutività dei codici ASCII delle lettere minuscole).
 *  - Stesso pattern del dado, applicato a dati testuali.
 *
 * Concetti applicati:
 *  - array come tabella di frequenze indicizzata da carattere
 *  - conversione carattere -> indice con aritmetica ASCII
 *  - scorrimento stringa fino al terminatore '\0'
 *  - ricerca di massimo e minimo ignorando le celle a zero
 */

#include <stdio.h>

#define LETTERE 26

int main(void) {

    /* Testo da analizzare. La stringa è su più righe per leggibilità
     * (il compilatore concatena stringhe letterali adiacenti). */
    char testo[] =
        "la lingua italiana e una delle lingue romanze "
        "discendenti dal latino volgare parlato nella penisola italica "
        "dalla caduta dellimpero romano doccidente";

    /* Array delle frequenze: frequenze[i] conta le occorrenze della
     * lettera (char)('a' + i). Inizializzato tutto a zero. */
    int frequenze[LETTERE] = {0};

    int i;
    int totale_lettere = 0;

    /* ------------------------------------------------------------------ */
    /* Scansione del testo: scorre fino al terminatore '\0'.
     * Per ogni carattere, se è una lettera minuscola, calcola l'indice
     * sottraendo il codice ASCII di 'a' e incrementa il contatore. */
    for (i = 0; testo[i] != '\0'; i++) {
        char c = testo[i];

        /* Converte maiuscole in minuscole, se presenti */
        if (c >= 'A' && c <= 'Z') {
            c = c + 32;   /* differenza ASCII tra maiuscolo e minuscolo */
        }

        /* Conta solo le lettere dell'alfabeto, ignora spazi e punteggiatura */
        if (c >= 'a' && c <= 'z') {
            /* La sottrazione 'c' - 'a' converte il carattere in indice:
             * 'a' - 'a' = 0, 'b' - 'a' = 1, ..., 'z' - 'a' = 25 */
            frequenze[c - 'a'] = frequenze[c - 'a'] + 1;
            totale_lettere++;
        }
    }

    /* ------------------------------------------------------------------ */
    /* Stampa della tabella delle frequenze.
     * Si stampano solo le lettere con frequenza > 0. */
    printf("=== ANALISI FREQUENZA LETTERE ===\n\n");
    printf("  Lettera | Freq. | Percentuale | Istogramma\n");
    printf("  --------|-------|-------------|--------------------\n");

    for (i = 0; i < LETTERE; i++) {
        if (frequenze[i] > 0) {
            double perc = (double)frequenze[i] / totale_lettere * 100.0;
            int    barre = frequenze[i];   /* un simbolo per occorrenza */
            int    j;

            printf("    %c     |  %3d  |  %5.1f%%     | ", 'a' + i, frequenze[i], perc);
            for (j = 0; j < barre; j++) {
                printf("*");
            }
            printf("\n");
        }
    }
    printf("\n");
    printf("Totale lettere analizzate: %d\n\n", totale_lettere);

    /* ------------------------------------------------------------------ */
    /* Lettera più frequente e meno frequente (tra quelle presenti).
     * Si ignora il valore 0 nella ricerca del minimo, altrimenti le
     * lettere assenti sarebbero sempre le "meno frequenti". */
    int indice_max = 0;
    int indice_min = -1;   /* -1 finché non si trova la prima lettera presente */

    for (i = 0; i < LETTERE; i++) {
        if (frequenze[i] > frequenze[indice_max]) {
            indice_max = i;
        }
        /* Per il minimo: considera solo le lettere con frequenza > 0 */
        if (frequenze[i] > 0) {
            if (indice_min == -1 || frequenze[i] < frequenze[indice_min]) {
                indice_min = i;
            }
        }
    }

    printf("Lettera piu' frequente : '%c'  (%d occorrenze)\n",
           'a' + indice_max, frequenze[indice_max]);

    if (indice_min != -1) {
        printf("Lettera meno frequente : '%c'  (%d occorrenza/e)\n",
               'a' + indice_min, frequenze[indice_min]);
    }

    /* ------------------------------------------------------------------ */
    /* Conteggio delle lettere distinte presenti nel testo */
    int lettere_distinte = 0;
    for (i = 0; i < LETTERE; i++) {
        if (frequenze[i] > 0) {
            lettere_distinte++;
        }
    }
    printf("Lettere distinte usate : %d su %d\n", lettere_distinte, LETTERE);

    return 0;
}
