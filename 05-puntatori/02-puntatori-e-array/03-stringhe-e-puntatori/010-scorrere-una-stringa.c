/*
 * 010-scorrere-una-stringa.c
 *
 * Scorrere una stringa con un puntatore a char
 *
 * Una stringa è un array di char terminato da '\0'. Invece di usare un
 * indice, si può scorrere con un puntatore che avanza finché il carattere
 * puntato non è il terminatore:
 *
 *     const char *p = testo;
 *     while (*p != '\0') {
 *         ... *p ...
 *         p++;
 *     }
 *
 * Alla fine p punta al '\0' e la lunghezza della stringa è p - testo.
 * Ogni char occupa 1 byte: gli indirizzi crescono di 1.
 *
 * Esempio: il messaggio del tabellone di una stazione.
 */

#include <stdio.h>

int main(void)
{
    char annuncio[] = "Treno 2049 per Torino";
    const char *p;
    int lettere = 0;
    int cifre = 0;
    int spazi = 0;

    printf("=== CARATTERE PER CARATTERE ===\n");
    p = annuncio;
    while (*p != '\0') {
        printf("  %p  '%c'\n", (void *) p, *p);
        if (*p >= '0' && *p <= '9') {
            cifre++;
        } else if (*p == ' ') {
            spazi++;
        } else {
            lettere++;
        }
        p++;
    }
    printf("  %p  '\\0'  <- p si ferma qui\n", (void *) p);

    printf("\nLunghezza: p - annuncio = %d caratteri\n", (int) (p - annuncio));
    printf("Lettere %d, cifre %d, spazi %d\n", lettere, cifre, spazi);

    /* stampare la stringa a partire da un punto qualsiasi */
    printf("\nannuncio + 15 = \"%s\"\n", annuncio + 15);

    /* all'indietro: da p - 1 fino al primo carattere */
    printf("Al contrario:   \"");
    while (p > annuncio) {
        p--;
        printf("%c", *p);
    }
    printf("\"\n");

    return 0;
}
