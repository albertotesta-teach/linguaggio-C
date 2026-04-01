/*
 * 020-modifica-tramite-puntatore.c
 *
 * Passaggio per riferimento: modificare la variabile del chiamante
 *
 * Quando una funzione riceve un PUNTATORE come parametro, può modificare
 * la variabile originale del chiamante. Questo si chiama "passaggio per
 * riferimento" (anche se in C tecnicamente il puntatore stesso è passato
 * per valore — è l'INDIRIZZO a essere copiato, non la variabile puntata).
 *
 * Confronto diretto con il passaggio per valore per evidenziare
 * la differenza nel comportamento.
 */

#include <stdio.h>

/* Prototipi */
void raddoppia_per_valore(int n);
void raddoppia_per_riferimento(int *n);
void incrementa(int *n, int quanto);
void azzera(double *x);

/* --- Definizioni --- */

/* Passaggio PER VALORE: la funzione riceve una copia.
 * La variabile originale nel chiamante NON viene modificata. */
void raddoppia_per_valore(int n)
{
    n = n * 2;   /* modifica solo la copia locale */
    printf("  [per valore]      dentro la funzione: n = %d\n", n);
}

/* Passaggio PER RIFERIMENTO: la funzione riceve l'indirizzo.
 * *n accede direttamente alla variabile originale del chiamante. */
void raddoppia_per_riferimento(int *n)
{
    *n = *n * 2;   /* modifica la variabile all'indirizzo puntato */
    printf("  [per riferimento] dentro la funzione: *n = %d\n", *n);
}

/* Incrementa la variabile puntata di una quantità specificata */
void incrementa(int *n, int quanto)
{
    /* "quanto" è passato per valore (non serve modificarlo)
     * "*n" è passato per riferimento (vogliamo modificare l'originale) */
    *n = *n + quanto;
}

/* Azzera una variabile double */
void azzera(double *x)
{
    *x = 0.0;
}

int main(void)
{
    int valore_a = 10;
    int valore_b = 10;
    int contatore = 0;
    double saldo = 150.75;

    /* --- Confronto per valore vs per riferimento --- */
    printf("=== Confronto: per valore vs per riferimento ===\n\n");

    printf("valore_a prima: %d\n", valore_a);
    raddoppia_per_valore(valore_a);
    printf("valore_a dopo:  %d  ← invariato\n\n", valore_a);

    printf("valore_b prima: %d\n", valore_b);
    raddoppia_per_riferimento(&valore_b);   /* si passa &valore_b, non valore_b */
    printf("valore_b dopo:  %d  ← modificato dalla funzione\n\n", valore_b);

    /* --- Incremento con quantità parametrica --- */
    printf("=== Incremento ===\n\n");

    printf("contatore prima: %d\n", contatore);
    incrementa(&contatore, 5);
    printf("contatore dopo +5: %d\n", contatore);
    incrementa(&contatore, 3);
    printf("contatore dopo +3: %d\n\n", contatore);

    /* --- Azzeramento di un double --- */
    printf("=== Azzeramento ===\n\n");

    printf("saldo prima: %.2f\n", saldo);
    azzera(&saldo);
    printf("saldo dopo:  %.2f\n", saldo);

    return 0;
}
