/*
 * 010-prima-malloc.c
 *
 * malloc e free: un intero nello heap
 *
 * Le variabili locali stanno nello stack: nascono quando si entra nel
 * blocco e spariscono quando se ne esce, e la loro dimensione deve essere
 * nota quando si compila. Lo heap è una zona di memoria da cui il
 * programma chiede blocchi mentre è in esecuzione:
 *
 *     #include <stdlib.h>
 *
 *     int *p = malloc(sizeof *p);      un blocco grande quanto un int
 *     if (p == NULL) {                 la richiesta può fallire
 *         ...
 *     }
 *     *p = 42;                         il blocco si usa tramite p
 *     free(p);                         il blocco torna al sistema
 *
 * malloc riceve il numero di byte e restituisce l'indirizzo del blocco,
 * oppure NULL se la memoria non basta. Il contenuto del blocco non è
 * inizializzato. sizeof *p è la dimensione di ciò a cui p punta: se un
 * giorno p diventa un double *, la malloc resta corretta.
 *
 * Ogni blocco ottenuto con malloc va restituito con free, una sola
 * volta. Dopo free il blocco non appartiene più al programma.
 *
 * Esempio: un contatore nello stack e uno nello heap, con i loro
 * indirizzi.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int nello_stack = 7;
    int *nello_heap;

    nello_heap = malloc(sizeof *nello_heap);
    if (nello_heap == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        *nello_heap = 42;
        printf("sizeof *nello_heap = %zu byte\n", sizeof *nello_heap);
        printf("nello_stack = %d   all'indirizzo %p\n", nello_stack,
               (void *) &nello_stack);
        printf("*nello_heap = %d  all'indirizzo %p\n", *nello_heap,
               (void *) nello_heap);
        printf("il puntatore nello_heap sta nello stack: %p\n",
               (void *) &nello_heap);

        *nello_heap = *nello_heap + nello_stack;
        printf("dopo la somma *nello_heap = %d\n", *nello_heap);

        free(nello_heap);
        printf("blocco liberato\n");
    }

    return 0;
}
