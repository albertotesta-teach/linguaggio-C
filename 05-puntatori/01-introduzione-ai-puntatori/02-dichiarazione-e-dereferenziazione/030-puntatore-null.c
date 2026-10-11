/*
 * 030-puntatore-null.c
 *
 * Il puntatore NULL: "non punta a nulla"
 *
 * Un puntatore dichiarato e non inizializzato contiene un indirizzo
 * casuale: usarlo (*p) significa leggere o scrivere in un punto qualsiasi
 * della memoria. Per indicare che un puntatore NON punta ancora a nessuna
 * variabile si usa il valore speciale NULL (definito in <stdio.h>):
 *
 *     int *selezionato = NULL;
 *     ...
 *     if (selezionato != NULL) {
 *         *selezionato = ...;      si usa solo se punta a qualcosa
 *     }
 *
 * Regola: un puntatore si inizializza sempre, con un indirizzo valido
 * oppure con NULL, e prima di usarlo si controlla che non sia NULL.
 *
 * Esempio: in una macchinetta del caffè l'utente sceglie una bevanda con
 * un codice; il puntatore indica il contatore della bevanda scelta, oppure
 * vale NULL se il codice non esiste.
 */

#include <stdio.h>

int main(void)
{
    int caffe = 0;
    int cappuccino = 0;
    int te = 0;
    int *scelta;
    char codici[] = "CPTXC";            /* X non esiste */
    int k;

    for (k = 0; codici[k] != '\0'; k++) {
        scelta = NULL;                  /* nessuna bevanda selezionata */
        if (codici[k] == 'C') {
            scelta = &caffe;
        } else if (codici[k] == 'P') {
            scelta = &cappuccino;
        } else if (codici[k] == 'T') {
            scelta = &te;
        }

        printf("Codice %c: ", codici[k]);
        if (scelta != NULL) {
            *scelta = *scelta + 1;
            printf("erogato (contatore %d)\n", *scelta);
        } else {
            printf("codice inesistente, puntatore NULL: nessuna erogazione\n");
        }
    }

    printf("\nTotali: caffe' %d, cappuccino %d, te' %d\n", caffe, cappuccino, te);

    return 0;
}
