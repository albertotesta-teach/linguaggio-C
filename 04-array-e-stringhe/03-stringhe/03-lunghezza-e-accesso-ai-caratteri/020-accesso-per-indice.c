/*
 * 020-accesso-per-indice.c
 *
 * Lettura e modifica di singoli caratteri tramite indice.
 *
 * Una stringa in C è un array: ogni carattere è accessibile
 * tramite il suo indice, esattamente come in un array di interi.
 * Questo permette di:
 *   - leggere un carattere specifico: c = s[i]
 *   - modificare un carattere:        s[i] = 'X'
 *   - troncare una stringa:           s[i] = '\0'
 *
 * Nota: modificare il terminatore '\0' è un'operazione potente
 * che cambia la lunghezza logica della stringa senza liberare memoria.
 */

#include <stdio.h>

int main(void) {

    /* Stringa di lavoro su cui eseguire le operazioni */
    char testo[50] = "Programmazione in C";

    /* Indice di lavoro */
    int i;

    printf("=== ACCESSO E MODIFICA PER INDICE ===\n\n");

    /* --- LETTURA DI UN CARATTERE SPECIFICO ---
     * Accesso diretto tramite indice: legge il carattere
     * in una posizione precisa senza scorrere tutta la stringa. */
    printf("Stringa originale: \"%s\"\n\n", testo);
    printf("Lettura caratteri specifici:\n");
    printf("  testo[0]  = '%c'  (primo carattere)\n",  testo[0]);
    printf("  testo[1]  = '%c'  (secondo carattere)\n", testo[1]);
    printf("  testo[13] = '%c'  (quattordicesimo)\n",   testo[13]);
    printf("\n");

    /* --- MODIFICA DI UN CARATTERE ---
     * Sovrascrittura diretta: cambia 'P' in 'p' (minuscolo).
     * L'ASCII di 'P' è 80, di 'p' è 112: differenza di 32. */
    printf("Modifica: testo[0] = 'p' (maiuscola → minuscola)\n");
    testo[0] = 'p';
    printf("Stringa modificata: \"%s\"\n\n", testo);

    /* Ripristino per gli esempi successivi */
    testo[0] = 'P';

    /* --- SCAMBIO DI DUE CARATTERI ---
     * Tecnica classica con variabile di appoggio.
     * Scambia il primo e l'ultimo carattere della stringa. */

    /* Prima troviamo l'ultimo carattere: scorriamo fino a '\0'
     * e poi torniamo indietro di una posizione. */
    i = 0;
    while (testo[i] != '\0') {
        i++;
    }
    i--; /* ora i punta all'ultimo carattere (prima di '\0') */

    printf("Scambio primo e ultimo carattere:\n");
    printf("  Primo   : testo[0] = '%c'\n", testo[0]);
    printf("  Ultimo  : testo[%d] = '%c'\n", i, testo[i]);

    /* Scambio con variabile temporanea */
    {
        char temp;
        temp     = testo[0];
        testo[0] = testo[i];
        testo[i] = temp;
    }
    printf("  Dopo lo scambio: \"%s\"\n\n", testo);

    /* Ripristino */
    {
        char temp;
        temp     = testo[0];
        testo[0] = testo[i];
        testo[i] = temp;
    }

    /* --- TRONCAMENTO TRAMITE '\0' ---
     * Inserire '\0' in posizione i equivale a terminare la stringa
     * in quel punto. I caratteri dopo '\0' rimangono in memoria
     * ma printf non li stampa perché si ferma al primo '\0'. */
    printf("Troncamento: inserisco '\\0' in posizione 13\n");
    printf("  Prima : \"%s\"\n", testo);
    testo[13] = '\0'; /* "Programmazione in C" → "Programmazione" */
    printf("  Dopo  : \"%s\"\n\n", testo);

    printf("Nota: i caratteri dopo la posizione 13 sono ancora\n");
    printf("in memoria ma non vengono stampati da printf.\n");
    printf("Carattere in posizione 14 (ancora in memoria): '%c'\n",
           testo[14]);

    return 0;
}
