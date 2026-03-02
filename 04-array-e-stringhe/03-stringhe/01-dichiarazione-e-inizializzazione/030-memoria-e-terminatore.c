/*
 * 03-memoria-e-terminatore.c
 *
 * Come una stringa è organizzata in memoria: visualizzazione cella per cella.
 *
 * Questo esempio mostra cosa succede "sotto il cofano": ogni carattere
 * occupa 1 byte, ed è possibile stampare il valore numerico (ASCII) di
 * ciascuna cella, incluso il terminatore '\0'.
 *
 * Problema reale: capire perché una stringa si comporta in modo strano
 * è spesso questione di esaminare la sua rappresentazione in memoria.
 */

#include <stdio.h>

int main(void) {

    /* Una stringa che rappresenta un codice prodotto di un magazzino */
    char codice[] = "AX-2024";

    /* Stampa la stringa normalmente */
    printf("Codice prodotto: %s\n", codice);
    printf("\n");

    /* Stampa la mappa in memoria: indice, carattere e valore ASCII */
    printf("Mappa in memoria della stringa \"%s\":\n", codice);
    printf("%-10s %-12s %-10s\n", "Indice", "Carattere", "Valore ASCII");
    printf("----------------------------------\n");

    /* Scorre l'array fino al terminatore incluso.
     * codice[i] != '\0' si fermerebbe prima del terminatore,
     * quindi aggiungiamo +1 per visualizzare anche la cella finale. */
    int i = 0;
    while (i <= 7) { /* "AX-2024" ha 7 caratteri + 1 terminatore = 8 celle */

        if (codice[i] == '\0') {
            /* Il terminatore non è stampabile, lo mostriamo come \0 */
            printf("%-10d %-12s %-10d\n", i, "\\0 (fine)", 0);
        } else {
            /* Stampa indice, carattere e suo valore decimale ASCII */
            printf("%-10d %-12c %-10d\n", i, codice[i], (int)codice[i]);
        }
        i++;
    }

    printf("\n");

    /* Dimostrazione: modifica di un singolo carattere nella stringa.
     * Utile ad esempio per correggere un codice prodotto errato. */
    printf("Modifica: cambio il carattere in posizione 1 da '%c' a 'Z'\n", codice[1]);
    codice[1] = 'Z'; /* Modifica diretta del carattere in posizione 1 */
    printf("Codice modificato: %s\n", codice);

    return 0;
}
