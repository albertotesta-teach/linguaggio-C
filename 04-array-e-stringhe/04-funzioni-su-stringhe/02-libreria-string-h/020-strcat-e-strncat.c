/*
 * 020-strcat-e-strncat.c
 *
 * Concatenazione con <string.h>
 *
 *   strcat(dest, sorg)      aggiunge sorg in coda a dest
 *   strncat(dest, sorg, n)  aggiunge AL MASSIMO n caratteri di sorg e
 *                           termina SEMPRE dest con '\0'
 *
 * Come strcpy, strcat non controlla lo spazio disponibile. Con strncat il
 * limite n NON è la dimensione di dest, ma il numero di caratteri che si
 * possono ancora aggiungere:
 *
 *     spazio_libero = sizeof(dest) - strlen(dest) - 1;    (-1 per il '\0')
 *     strncat(dest, sorg, spazio_libero);
 *
 * Per non ripetere il calcolo, il programma usa una piccola funzione
 * aggiungi(dest, dim, sorg) che restituisce 1 se il testo è entrato tutto
 * e 0 se è stato troncato.
 *
 * Esempio: composizione dell'oggetto di un'email di avviso.
 */

#include <stdio.h>
#include <string.h>

#define DIM_OGGETTO 40

int aggiungi(char dest[], int dim, const char sorg[]);

int main(void)
{
    char oggetto[DIM_OGGETTO];
    char classe[] = "3B";
    char materia[] = "Informatica";
    char tipo[] = "verifica scritta";
    int completo;

    /* ── 1. strcat: spazio sufficiente ────────────────────────────── */
    printf("=== strcat ===\n");
    strcpy(oggetto, "Classe ");
    strcat(oggetto, classe);
    strcat(oggetto, ": ");
    strcat(oggetto, materia);
    printf("oggetto = \"%s\" (%d su %d caratteri)\n\n",
           oggetto, (int) strlen(oggetto), DIM_OGGETTO - 1);

    /* ── 2. strncat con il calcolo dello spazio libero ────────────── */
    printf("=== strncat ===\n");
    printf("Spazio libero prima: %d caratteri\n",
           DIM_OGGETTO - (int) strlen(oggetto) - 1);
    completo = aggiungi(oggetto, DIM_OGGETTO, ", ");
    completo = completo && aggiungi(oggetto, DIM_OGGETTO, tipo);
    completo = completo && aggiungi(oggetto, DIM_OGGETTO, " del 15 ottobre");
    printf("oggetto = \"%s\"\n", oggetto);
    printf("lunghezza %d su %d: %s\n", (int) strlen(oggetto), DIM_OGGETTO - 1,
           completo ? "testo completo" : "testo troncato");

    return 0;
}

/* Aggiunge sorg in coda a dest (array di dim celle) senza superarne la
 * dimensione. Restituisce 1 se sorg è entrata tutta, 0 se è stata troncata. */
int aggiungi(char dest[], int dim, const char sorg[])
{
    int spazio_libero;

    spazio_libero = dim - (int) strlen(dest) - 1;
    strncat(dest, sorg, spazio_libero);
    return (int) strlen(sorg) <= spazio_libero;
}
