/*
 * 030-lettura-da-tastiera.c
 *
 * Lettura di valori da tastiera e memorizzazione in un array.
 *
 * Finora gli array sono stati inizializzati con valori statici nel codice.
 * Nella pratica, i dati provengono spesso dall'utente. Questo file mostra
 * come leggere valori da tastiera con scanf e memorizzarli nell'array,
 * e come poi rielaborarli. Mostra anche la validazione dell'input con
 * un ciclo di richiesta finché il valore non è accettabile.
 */

#include <stdio.h>

#define MAX_STUDENTI 5

int main(void) {

    int voti[MAX_STUDENTI];
    int i;
    int somma;
    int valido;

    printf("=== Inserimento voti ===\n");
    printf("Inserisci %d voti (da 1 a 10):\n\n", MAX_STUDENTI);

    /* Ciclo di input: per ogni posizione dell'array si chiede un valore.
     * La validazione usa una variabile booleana 'valido' per ripetere
     * la richiesta senza break o continue. */
    for (i = 0; i < MAX_STUDENTI; i++) {
        valido = 0;

        /* Ripeti la richiesta finché il valore inserito non è valido.
         * Non si usa break: la condizione del while controlla l'uscita. */
        while (!valido) {
            printf("  Voto studente %d: ", i + 1);
            scanf("%d", &voti[i]);

            /* Controlla che il voto sia nel range ammesso [1, 10] */
            if (voti[i] >= 1 && voti[i] <= 10) {
                valido = 1;   /* il valore è accettabile: esci dal while */
            } else {
                printf("  Voto non valido. Inserire un valore tra 1 e 10.\n");
            }
        }
    }

    /* ------------------------------------------------------------------ */
    /* Riepilogo dei dati inseriti */
    printf("\n=== Riepilogo voti inseriti ===\n");
    for (i = 0; i < MAX_STUDENTI; i++) {
        printf("  Studente %d: %d\n", i + 1, voti[i]);
    }

    /* ------------------------------------------------------------------ */
    /* Calcolo della somma e della media */
    somma = 0;
    for (i = 0; i < MAX_STUDENTI; i++) {
        somma = somma + voti[i];
    }

    printf("\nMedia dei voti: %.1f\n", (double)somma / MAX_STUDENTI);

    /* ------------------------------------------------------------------ */
    /* Stampa di una barra visiva proporzionale al voto.
     * Mostra come si può costruire un output grafico semplice con array. */
    printf("\nDistribuzione:\n");
    for (i = 0; i < MAX_STUDENTI; i++) {
        int j;
        printf("  Studente %d [%2d]: ", i + 1, voti[i]);
        for (j = 0; j < voti[i]; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
