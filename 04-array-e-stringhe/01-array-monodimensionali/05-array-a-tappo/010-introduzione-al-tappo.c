/*
 * 010-introduzione-al-tappo.c
 *
 * Array a tappo: confronto con array a dimensione fissa.
 *
 * Un array a tappo (o array con sentinella) è un array in cui un valore
 * speciale — detto tappo o sentinella — segnala la fine dei dati validi.
 * Non serve conoscere o passare esplicitamente la dimensione: il ciclo
 * si ferma quando incontra il tappo.
 *
 * Il valore scelto come tappo deve essere:
 *  - impossibile o illegale come dato valido nel contesto del problema
 *  - facilmente riconoscibile nel codice
 *
 * Esempi comuni:
 *  - -1   per array di interi non negativi (indici, contatori, prezzi)
 *  - 0    per array di interi positivi (codici, ID)
 *  - '\0' per array di char (ed è esattamente ciò che fa una stringa C)
 *
 * Questo file confronta le due tecniche sullo stesso problema: sommare
 * gli elementi di un array.
 */

#include <stdio.h>

#define TAPPO -1
#define MAX   20   /* capacità massima dell'array incluso il tappo */

/* ------------------------------------------------------------------ */
/* Versione con dimensione esplicita: il chiamante deve passare n */
int somma_con_n(const int arr[], int n) {
    int i;
    int totale = 0;
    for (i = 0; i < n; i++) {
        totale = totale + arr[i];
    }
    return totale;
}

/* Versione con tappo: il ciclo si ferma quando trova TAPPO.
 * Non serve il parametro n: la dimensione è implicita nel tappo. */
int somma_con_tappo(const int arr[]) {
    int i = 0;
    int totale = 0;
    while (arr[i] != TAPPO) {
        totale = totale + arr[i];
        i++;
    }
    return totale;
}

/* Conta gli elementi validi (esclude il tappo) */
int lunghezza(const int arr[]) {
    int i = 0;
    while (arr[i] != TAPPO) {
        i++;
    }
    return i;   /* i è l'indice del tappo = numero di elementi validi */
}

/* Stampa gli elementi validi dell'array a tappo */
void stampa(const int arr[]) {
    int i = 0;
    printf("[ ");
    while (arr[i] != TAPPO) {
        printf("%d ", arr[i]);
        i++;
    }
    printf("] (tappo in posizione %d)\n", i);
}

int main(void) {

    /* ---------------------------------------------------------------- */
    /* Array a dimensione fissa: la dimensione va sempre passata */
    int fisso[5] = {10, 20, 30, 40, 50};
    int n = 5;

    printf("=== Array a dimensione fissa ===\n");
    printf("Elementi: %d\n", n);
    printf("Somma: %d\n\n", somma_con_n(fisso, n));

    /* ---------------------------------------------------------------- */
    /* Array a tappo: il valore -1 segna la fine */
    int con_tappo[MAX] = {10, 20, 30, 40, 50, TAPPO};

    printf("=== Array a tappo (TAPPO = %d) ===\n", TAPPO);
    stampa(con_tappo);
    printf("Lunghezza: %d\n", lunghezza(con_tappo));
    printf("Somma: %d\n\n", somma_con_tappo(con_tappo));

    /* ---------------------------------------------------------------- */
    /* Vantaggio del tappo: si può avere un array parzialmente riempito
     * senza dover tenere traccia di quanti elementi sono validi.
     * Aggiungere un elemento significa solo scrivere prima del tappo
     * e spostare il tappo di una posizione. */
    printf("=== Confronto: array con diversi riempimenti ===\n");

    int dati[MAX] = {5, 12, 8, TAPPO};   /* solo 3 elementi per ora */
    printf("Stato iniziale  : ");
    stampa(dati);
    printf("Somma: %d\n\n", somma_con_tappo(dati));

    /* Aggiunta manuale di un elemento: si scrive nella posizione del tappo
     * e si sposta il tappo alla posizione successiva */
    int pos_tappo = lunghezza(dati);   /* trova dove si trova il tappo */
    dati[pos_tappo]     = 25;          /* scrive il nuovo valore */
    dati[pos_tappo + 1] = TAPPO;       /* sposta il tappo */

    printf("Dopo aggiunta 25: ");
    stampa(dati);
    printf("Somma: %d\n\n", somma_con_tappo(dati));

    /* ---------------------------------------------------------------- */
    /* Connessione con le stringhe C: una stringa è un array di char
     * con tappo '\0'. Il pattern è identico a quello degli interi. */
    printf("=== Collegamento con le stringhe C ===\n");
    char parola[] = {'c', 'i', 'a', 'o', '\0'};

    printf("Stringa come array di char con tappo '\\0':\n");
    int j = 0;
    while (parola[j] != '\0') {
        printf("  parola[%d] = '%c'  (ASCII %d)\n", j, parola[j], parola[j]);
        j++;
    }
    printf("  parola[%d] = '\\0' (ASCII 0) <- tappo\n", j);
    printf("Lunghezza: %d caratteri\n", j);

    return 0;
}
