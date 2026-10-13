/*
 * 010-calloc-azzera.c
 *
 * calloc: un blocco con tutti i byte a zero
 *
 * malloc restituisce un blocco con il contenuto che capita: prima di
 * leggerlo bisogna scriverci. calloc riceve il numero di elementi e la
 * dimensione di ciascuno, e azzera tutti i byte del blocco:
 *
 *     int *a = malloc(n * sizeof *a);       contenuto non definito
 *     int *b = calloc(n, sizeof *b);        n int che valgono 0
 *
 * Come malloc, calloc restituisce NULL se la memoria non basta, e il
 * blocco si libera con free.
 *
 * calloc conviene quando il programma parte davvero da zero: contatori,
 * totali, flag "non ancora visto". Se ogni elemento verrà comunque
 * scritto prima di essere letto, l'azzeramento è lavoro inutile e basta
 * malloc.
 *
 * Esempio: il programma alloca due blocchi di 6 int, uno con malloc e
 * uno con calloc. Il blocco di calloc si può stampare subito. Il blocco
 * di malloc no: leggerlo prima di scriverlo darebbe valori casuali, quindi
 * lo si azzera a mano con un ciclo, come si fa sempre dopo malloc.
 */

#include <stdio.h>
#include <stdlib.h>

#define N 6

int tutto_zero(const int v[], int n);
void stampa(const char *nome, const int v[], int n);

int main(void)
{
    int *con_malloc = malloc(N * sizeof *con_malloc);
    int *con_calloc = calloc(N, sizeof *con_calloc);
    int i;

    if (con_malloc == NULL || con_calloc == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        printf("calloc(%d, %zu): %zu byte\n", N, sizeof *con_calloc, N * sizeof *con_calloc);
        stampa("con_calloc", con_calloc, N);

        /* leggere il blocco di malloc prima di scriverlo è un errore:
           qui si mostra solo che non si può contare sugli zeri */
        printf("con_malloc: il contenuto iniziale non e' definito\n");
        for (i = 0; i < N; i++) {
            con_malloc[i] = 0;
        }
        printf("dopo il ciclo di azzeramento: tutto a zero? %s\n",
               tutto_zero(con_malloc, N) ? "si'" : "no");

        con_calloc[2] = 7;
        stampa("con_calloc dopo con_calloc[2] = 7", con_calloc, N);
    }

    free(con_malloc);
    free(con_calloc);

    return 0;
}

int tutto_zero(const int v[], int n)
{
    int zero = 1;
    int i;

    for (i = 0; i < n; i++) {
        if (v[i] != 0) {
            zero = 0;
        }
    }
    return zero;
}

void stampa(const char *nome, const int v[], int n)
{
    int i;

    printf("%s:", nome);
    for (i = 0; i < n; i++) {
        printf(" %d", v[i]);
    }
    printf("\n");
}
