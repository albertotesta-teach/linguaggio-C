/*
 * 020-tipi-dei-puntatori.c
 *
 * Perché un puntatore ha un tipo
 *
 * Tutti gli indirizzi hanno la stessa dimensione, ma un puntatore deve
 * sapere che cosa c'è all'indirizzo che contiene: quando si scrive *p il
 * compilatore legge sizeof(*p) byte e li interpreta secondo il tipo.
 *
 *     int *pi      *pi legge 4 byte e li interpreta come intero
 *     double *pd   *pd legge 8 byte e li interpreta come numero con virgola
 *
 * Per questo un int * non può puntare a un double: il compilatore lo
 * segnala.
 *
 *     double media = 7.5;
 *     int *p = &media;      avviso: tipi di puntatore incompatibili
 *
 * Copiare un VALORE tra variabili di tipo diverso invece è normale: la
 * conversione avviene come in un'assegnazione.
 *
 *     *pd = *pi;            l'int puntato da pi diventa un double
 */

#include <stdio.h>

int main(void)
{
    int voto = 8;
    double media = 7.5;
    char giudizio = 'B';
    int *pi = &voto;
    double *pd = &media;
    char *pc = &giudizio;

    printf("=== Che cosa legge *p ===\n");
    printf("  *pi = %-5d  legge sizeof(*pi) = %zu byte\n", *pi, sizeof(*pi));
    printf("  *pd = %-5.2f  legge sizeof(*pd) = %zu byte\n", *pd, sizeof(*pd));
    printf("  *pc = %-5c  legge sizeof(*pc) = %zu byte\n", *pc, sizeof(*pc));
    printf("  ma i puntatori occupano tutti %zu byte\n\n", sizeof(pi));

    printf("=== Copiare valori tra tipi diversi ===\n");
    *pd = *pi;                          /* int -> double: 8 diventa 8.0 */
    printf("  *pd = *pi  -> media = %.2f\n", media);
    *pd = 6.75;
    *pi = (int) *pd;                    /* double -> int: la parte decimale si perde */
    printf("  *pi = (int) *pd con *pd = 6.75 -> voto = %d\n", voto);

    return 0;
}
