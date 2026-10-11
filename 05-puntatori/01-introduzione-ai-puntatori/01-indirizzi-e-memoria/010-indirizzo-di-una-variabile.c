/*
 * 010-indirizzo-di-una-variabile.c
 *
 * Ogni variabile ha un indirizzo
 *
 * La memoria del computer è una lunga sequenza di celle da 1 byte, ognuna
 * con un numero: il suo INDIRIZZO. Quando si dichiara una variabile, il
 * compilatore le riserva alcune celle consecutive; l'indirizzo della
 * variabile è quello della prima cella.
 *
 *   &x        operatore "indirizzo di": restituisce l'indirizzo di x
 *   %p        specifica di printf per stampare un indirizzo
 *             (in esadecimale, il formato dipende dal sistema)
 *
 * printf con %p vuole un indirizzo "generico": per questo l'indirizzo si
 * converte con (void *). È l'unico uso di void * in questo capitolo.
 *
 * Gli indirizzi cambiano a ogni esecuzione: il sistema operativo colloca il
 * programma in posizioni diverse della memoria per motivi di sicurezza.
 * L'output riportato nel README è quindi solo un esempio.
 *
 * L'operatore & è già stato usato con scanf: scanf("%d", &n) passa a scanf
 * l'indirizzo di n, così che scanf possa scrivere il valore letto proprio
 * in quella variabile.
 */

#include <stdio.h>

int main(void)
{
    int eta = 17;
    double media = 7.25;
    char sezione = 'B';

    printf("=== VALORE E INDIRIZZO ===\n");
    printf("  eta     = %-6d  indirizzo %p\n", eta, (void *) &eta);
    printf("  media   = %-6.2f  indirizzo %p\n", media, (void *) &media);
    printf("  sezione = %-6c  indirizzo %p\n", sezione, (void *) &sezione);

    /* cambiare il valore non cambia l'indirizzo */
    eta = 18;
    printf("\nDopo eta = 18:\n");
    printf("  eta     = %-6d  indirizzo %p (lo stesso)\n", eta, (void *) &eta);

    /* scanf scrive all'indirizzo che riceve */
    printf("\nNuova eta': ");
    scanf("%d", &eta);
    printf("  scanf ha scritto %d all'indirizzo %p\n", eta, (void *) &eta);

    return 0;
}
