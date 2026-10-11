/*
 * 010-puntatore-a-puntatore.c
 *
 * Un puntatore che contiene l'indirizzo di un altro puntatore
 *
 * Anche un puntatore è una variabile e ha un indirizzo. Un PUNTATORE A
 * PUNTATORE (doppio puntatore) contiene l'indirizzo di un puntatore:
 *
 *     int x = 42;
 *     int *p = &x;          p contiene l'indirizzo di x
 *     int **pp = &p;        pp contiene l'indirizzo di p
 *
 *     pp      indirizzo di p
 *     *pp     il valore di p, cioè l'indirizzo di x
 *     **pp    il valore di x
 *
 * Con **pp si legge e si scrive x; con *pp si legge e si cambia p, cioè
 * si decide a quale variabile punta p.
 *
 * Esempio: il piano a cui si trova l'ascensore della scuola e quello del
 * montacarichi; un puntatore indica l'impianto selezionato sul pannello.
 */

#include <stdio.h>

int main(void)
{
    int ascensore = 2;
    int montacarichi = 0;
    int *selezionato = &ascensore;
    int **pannello = &selezionato;

    printf("=== TRE LIVELLI ===\n");
    printf("  ascensore    = %d          &ascensore    = %p\n", ascensore, (void *) &ascensore);
    printf("  selezionato  = %p   &selezionato  = %p\n", (void *) selezionato, (void *) &selezionato);
    printf("  pannello     = %p\n", (void *) pannello);
    printf("\n  *pannello    = %p   (il valore di selezionato)\n", (void *) *pannello);
    printf("  **pannello   = %d                (il valore di ascensore)\n", **pannello);

    /* scrivere con ** modifica la variabile finale */
    **pannello = 4;
    printf("\nDopo **pannello = 4:  ascensore = %d\n", ascensore);

    /* scrivere con * cambia il puntatore intermedio */
    *pannello = &montacarichi;
    printf("Dopo *pannello = &montacarichi: selezionato punta al montacarichi\n");
    **pannello = 1;
    printf("Dopo **pannello = 1:  ascensore = %d, montacarichi = %d\n", ascensore, montacarichi);

    printf("\nOgni livello occupa %zu byte: sizeof(int *) = sizeof(int **)\n", sizeof(pannello));

    return 0;
}
