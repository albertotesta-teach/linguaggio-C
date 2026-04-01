/*
 * 040-problema-scambio-valori.c
 *
 * Scambio del valore di due variabili
 *
 * Un sistema di ordinamento ha bisogno di scambiare il contenuto di due
 * variabili intere. La funzione scambia() riceve gli indirizzi delle due
 * variabili e ne scambia i valori usando una variabile temporanea.
 * Questo è l'esempio classico che dimostra perché il passaggio per
 * riferimento è indispensabile: con il passaggio per valore sarebbe
 * impossibile modificare entrambe le variabili del chiamante.
 *
 * Il programma mostra anche un caso reale: ordinare tre numeri interi
 * in ordine crescente usando ripetute chiamate a scambia().
 */

#include <stdio.h>

/* Prototipi */
void scambia(int *a, int *b);
void ordina_tre(int *x, int *y, int *z);
void stampa_tre(int x, int y, int z);

/* --- Definizioni --- */

/* Scambia i valori delle due variabili puntate da a e b.
 * Usa una variabile temporanea per evitare di perdere un valore
 * durante lo scambio. */
void scambia(int *a, int *b)
{
    int temp;
    temp = *a;   /* salva il valore originale di *a */
    *a   = *b;   /* copia *b in *a */
    *b   = temp; /* copia il valore salvato in *b */
}

/* Ordina tre interi in ordine crescente usando bubble sort a tre elementi.
 * Confronta coppie adiacenti e scambia se fuori ordine. */
void ordina_tre(int *x, int *y, int *z)
{
    /* Primo passaggio: porta il massimo in fondo */
    if (*x > *y) { scambia(x, y); }
    if (*y > *z) { scambia(y, z); }
    /* Secondo passaggio: sistema il primo e il secondo */
    if (*x > *y) { scambia(x, y); }
}

void stampa_tre(int x, int y, int z)
{
    printf("  %d  %d  %d\n", x, y, z);
}

int main(void)
{
    int primo, secondo, terzo;

    /* --- Dimostrazione scambio base --- */
    printf("=== Scambio di due variabili ===\n\n");

    primo  = 42;
    secondo = 7;

    printf("Prima dello scambio:  primo=%d  secondo=%d\n", primo, secondo);
    scambia(&primo, &secondo);
    printf("Dopo  lo scambio:     primo=%d  secondo=%d\n\n", primo, secondo);

    /* --- Tentativo errato (commento didattico) ---
     *
     * void scambia_sbagliata(int a, int b) {
     *     int temp = a; a = b; b = temp;
     * }
     * Questa versione NON funziona: a e b sono copie locali.
     * Quando la funzione termina le modifiche vengono perse
     * e le variabili del chiamante rimangono invariate.
     */

    /* --- Ordinamento di tre numeri --- */
    printf("=== Ordinamento di tre numeri ===\n\n");

    primo  = 9;
    secondo = 3;
    terzo  = 6;
    printf("Prima: "); stampa_tre(primo, secondo, terzo);
    ordina_tre(&primo, &secondo, &terzo);
    printf("Dopo:  "); stampa_tre(primo, secondo, terzo);

    printf("\n");

    primo  = 1;
    secondo = 1;
    terzo  = 1;
    printf("Prima: "); stampa_tre(primo, secondo, terzo);
    ordina_tre(&primo, &secondo, &terzo);
    printf("Dopo:  "); stampa_tre(primo, secondo, terzo);

    printf("\n");

    primo  = 100;
    secondo = -5;
    terzo  = 42;
    printf("Prima: "); stampa_tre(primo, secondo, terzo);
    ordina_tre(&primo, &secondo, &terzo);
    printf("Dopo:  "); stampa_tre(primo, secondo, terzo);

    return 0;
}
