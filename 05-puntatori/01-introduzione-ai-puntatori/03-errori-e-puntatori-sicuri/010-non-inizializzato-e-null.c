/*
 * 010-non-inizializzato-e-null.c
 *
 * Puntatori non inizializzati e controllo di NULL
 *
 * Gli errori con i puntatori sono pericolosi perché spesso il programma
 * NON si ferma subito: scrive in un punto sbagliato della memoria e il
 * problema si manifesta più tardi, altrove.
 *
 * Errore 1 - puntatore non inizializzato
 *     int *p;
 *     *p = 5;          p contiene un indirizzo casuale: si scrive a caso
 *
 * Errore 2 - dereferenziare NULL
 *     int *p = NULL;
 *     *p = 5;          il programma si interrompe (segmentation fault)
 *
 * Regole che evitano entrambi gli errori:
 *   1. ogni puntatore si inizializza alla dichiarazione, con un indirizzo
 *      valido oppure con NULL;
 *   2. una funzione che riceve un puntatore che potrebbe essere NULL lo
 *      controlla prima di usarlo.
 *
 * Esempio: i tornelli di una scuola registrano ingressi e uscite. Per ogni
 * evento il puntatore selezionato indica il contatore da aggiornare, oppure
 * vale NULL se la lettura del badge non è riuscita. La funzione
 * incrementa(contatore) aggiunge 1 solo se l'indirizzo è valido. I codici errati
 * sono riportati solo nei commenti: eseguirli non sarebbe sicuro.
 */

#include <stdio.h>

int incrementa(int *contatore);

int main(void)
{
    int ingressi = 0;
    int uscite = 0;
    int *selezionato = NULL;            /* regola 1: inizializzato a NULL */
    char eventi[] = "IIUI?IU";          /* I ingresso, U uscita, ? lettura non riuscita */
    int k;

    for (k = 0; eventi[k] != '\0'; k++) {
        selezionato = NULL;
        if (eventi[k] == 'I') {
            selezionato = &ingressi;
        } else if (eventi[k] == 'U') {
            selezionato = &uscite;
        }

        printf("Evento %c: ", eventi[k]);
        if (incrementa(selezionato)) {
            printf("registrato (ingressi %d, uscite %d)\n", ingressi, uscite);
        } else {
            printf("non registrato: puntatore NULL\n");
        }
    }

    printf("\nPresenti nell'edificio: %d\n", ingressi - uscite);

    return 0;
}

/* Regola 2: se contatore è NULL non fa nulla e restituisce 0. */
int incrementa(int *contatore)
{
    int fatto = 0;

    if (contatore != NULL) {
        *contatore = *contatore + 1;
        fatto = 1;
    }
    return fatto;
}
