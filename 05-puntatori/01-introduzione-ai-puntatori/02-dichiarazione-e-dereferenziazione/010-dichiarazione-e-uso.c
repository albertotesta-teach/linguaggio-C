/*
 * 010-dichiarazione-e-uso.c
 *
 * Una variabile che contiene un indirizzo: il puntatore
 *
 * Un PUNTATORE è una variabile il cui valore è un indirizzo. Si dichiara
 * indicando il tipo della variabile a cui punterà, seguito da *:
 *
 *     int *p;          p può contenere l'indirizzo di un int
 *     double *pd;      pd può contenere l'indirizzo di un double
 *
 *     p = &x;          p "punta a" x
 *     *p               la variabile puntata (operatore di DEREFERENZIAZIONE):
 *                      si può leggere (y = *p) e scrivere (*p = 10)
 *
 * Attenzione al doppio significato di *:
 *   - nella DICHIARAZIONE (int *p) indica che p è un puntatore;
 *   - in un'ESPRESSIONE (*p = 10) indica la variabile puntata.
 *
 * Esempio: il livello dell'acqua in un serbatoio, letto e modificato sia
 * direttamente sia tramite un puntatore.
 */

#include <stdio.h>

int main(void)
{
    int livello = 70;                   /* percentuale di riempimento */
    double portata = 2.5;               /* litri al secondo */
    int *p;
    double *pd;

    p = &livello;
    pd = &portata;

    printf("=== VARIABILE E PUNTATORE ===\n");
    printf("  livello  = %d,   &livello = %p\n", livello, (void *) &livello);
    printf("  p        = %p    (contiene l'indirizzo di livello)\n", (void *) p);
    printf("  *p       = %d    (il valore della variabile puntata)\n", *p);
    printf("  &p       = %p    (anche p e' una variabile con un suo indirizzo)\n",
           (void *) &p);

    /* scrivere tramite il puntatore modifica la variabile puntata */
    *p = 85;
    printf("\nDopo *p = 85:      livello = %d\n", livello);

    /* e modificare la variabile cambia ciò che si legge tramite p */
    livello = livello - 10;
    printf("Dopo livello -= 10: *p = %d\n", *p);

    /* lo stesso con un double */
    *pd = *pd * 2;
    printf("\nDopo *pd = *pd * 2: portata = %.1f litri/s\n", portata);
    printf("Un puntatore occupa %zu byte, qualunque sia il tipo puntato.\n", sizeof(p));

    return 0;
}
