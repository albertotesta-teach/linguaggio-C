/*
 * 020-variabili-globali.c
 *
 * Variabili globali: condivisione tra funzioni
 *
 * Una variabile globale è dichiarata fuori da qualsiasi funzione.
 * Essa è visibile e modificabile da tutte le funzioni del file,
 * per tutta la durata del programma.
 *
 * Le variabili globali sono utili quando più funzioni devono condividere
 * uno stato comune. Vanno però usate con cautela: rendono il codice più
 * difficile da leggere e da testare, perché qualsiasi funzione può
 * modificarle in qualsiasi momento.
 */

#include <stdio.h>

/* --- Variabili globali ---
 * Dichiarate fuori da main e da qualsiasi funzione.
 * Vengono inizializzate a zero automaticamente dal compilatore
 * se non viene fornito un valore esplicito. */
int numero_operazioni = 0;   /* conta quante operazioni sono state eseguite */
double totale = 0.0;         /* accumula la somma di tutti i valori aggiunti */

/* Prototipi */
void aggiungi(double valore);
void sottrai(double valore);
void stampa_stato(void);
void azzera(void);

/* Ogni funzione legge e/o modifica le variabili globali direttamente,
 * senza riceverle come parametri. */

void aggiungi(double valore)
{
    totale = totale + valore;
    numero_operazioni = numero_operazioni + 1;
}

void sottrai(double valore)
{
    totale = totale - valore;
    numero_operazioni = numero_operazioni + 1;
}

void stampa_stato(void)
{
    printf("Operazioni eseguite: %d\n", numero_operazioni);
    printf("Totale corrente:     %.2f\n", totale);
}

void azzera(void)
{
    totale = 0.0;
    numero_operazioni = 0;
    printf("(stato azzerato)\n");
}

int main(void)
{
    printf("=== Registro operazioni ===\n\n");

    stampa_stato();   /* stato iniziale: tutto a zero */
    printf("\n");

    aggiungi(100.0);
    aggiungi(50.0);
    aggiungi(25.0);
    stampa_stato();
    printf("\n");

    sottrai(30.0);
    stampa_stato();
    printf("\n");

    azzera();
    stampa_stato();

    return 0;
}
