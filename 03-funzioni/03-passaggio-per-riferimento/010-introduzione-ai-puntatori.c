/*
 * 010-introduzione-ai-puntatori.c
 *
 * Introduzione ai puntatori: indirizzo e valore
 *
 * Un puntatore è una variabile che contiene l'INDIRIZZO DI MEMORIA di
 * un'altra variabile. Con i puntatori una funzione può accedere
 * direttamente alla variabile del chiamante e modificarla.
 *
 * Questo file introduce i due operatori fondamentali:
 *   &  (indirizzo-di)      restituisce l'indirizzo di una variabile
 *   *  (dereferenziazione)  accede al valore all'indirizzo puntato
 *
 * Nota: i puntatori vengono trattati in modo completo nel capitolo 05.
 * Qui ne vediamo solo il minimo indispensabile per capire il passaggio
 * per riferimento nelle funzioni.
 */

#include <stdio.h>

int main(void)
{
    int eta = 25;
    int *p;   /* p è un puntatore a int: contiene l'indirizzo di un int */

    /* --- Operatore & : indirizzo di una variabile --- */
    p = &eta;   /* p ora punta a eta: contiene il suo indirizzo in memoria */

    printf("=== Variabile e puntatore ===\n\n");

    printf("Valore di eta:            %d\n",  eta);
    printf("Indirizzo di eta (&eta):  %p\n",  (void *)&eta);

    printf("\n");

    printf("Valore di p (indirizzo):  %p\n",  (void *)p);
    printf("Valore puntato da p (*p): %d\n",  *p);

    /* p e &eta contengono lo stesso indirizzo */
    /* *p e eta leggono lo stesso valore       */

    printf("\n");

    /* --- Operatore * : modifica tramite puntatore --- */
    printf("=== Modifica tramite puntatore ===\n\n");

    printf("Prima della modifica:  eta = %d\n", eta);

    *p = 30;   /* scrive il valore 30 all'indirizzo puntato da p,
                * cioè modifica direttamente la variabile eta */

    printf("Dopo  *p = 30:         eta = %d\n", eta);

    /* eta è cambiato senza scrivere "eta = 30":
     * *p ed eta si riferiscono alla stessa cella di memoria.
     *
     * Schema:
     *
     *  ┌──────────────┐        ┌──────────────┐
     *  │   eta = 30   │◄───────│  p = &eta    │
     *  │  (cella di   │        │  (puntatore) │
     *  │   memoria)   │        └──────────────┘
     *  └──────────────┘
     *
     *  &eta  →  indirizzo della cella
     *  *p    →  valore contenuto nella cella (30)
     */

    printf("\n=== Riepilogo ===\n\n");
    printf("  &eta = %p  (indirizzo della variabile)\n",  (void *)&eta);
    printf("  p    = %p  (stesso indirizzo nel puntatore)\n", (void *)p);
    printf("  eta  = %d            (valore nella cella)\n", eta);
    printf("  *p   = %d            (stesso valore letto via puntatore)\n", *p);

    return 0;
}
