/*
 * 020-inizializzazione.c
 *
 * Tre modi di inizializzare una struct
 *
 * Come un array, una struct si può inizializzare nella dichiarazione con
 * una lista tra graffe:
 *
 *   1. in ordine:     {1024, "Bianchi Sara", 12, 25.50}
 *                     i valori vanno ai campi nell'ordine della dichiarazione;
 *
 *   2. con il nome:   {.numero = 1025, .credito = 10.00}
 *                     ogni valore indica il proprio campo; l'ordine non conta
 *                     e i campi non nominati valgono 0 (stringa vuota per i char[]);
 *
 *   3. tutto a zero:  {0}
 *                     numeri a 0, stringhe vuote.
 *
 * Una struct locale NON inizializzata contiene valori casuali, come una
 * variabile int non inizializzata.
 *
 * Esempio: le tessere della mensa scolastica, con numero, intestatario,
 * pasti già consumati nel mese e credito residuo.
 */

#include <stdio.h>

struct tessera {
    int numero;
    char intestatario[20];
    int pasti;
    double credito;
};

int main(void)
{
    /* 1. in ordine: numero, intestatario, pasti, credito */
    struct tessera sara = {1024, "Bianchi Sara", 12, 25.50};

    /* 2. con il nome dei campi: gli altri sono a zero */
    struct tessera nuova = {.credito = 10.00, .numero = 1025};

    /* 3. tutta a zero */
    struct tessera vuota = {0};

    printf("  Numero  Intestatario    Pasti  Credito\n");
    printf("  %6d  %-14s  %5d  %7.2f\n", sara.numero, sara.intestatario, sara.pasti, sara.credito);
    printf("  %6d  %-14s  %5d  %7.2f   <- intestatario vuoto, pasti 0\n",
           nuova.numero, nuova.intestatario, nuova.pasti, nuova.credito);
    printf("  %6d  %-14s  %5d  %7.2f   <- tutto a zero\n",
           vuota.numero, vuota.intestatario, vuota.pasti, vuota.credito);

    /* la lista tra graffe vale SOLO nella dichiarazione:
     * vuota = {2000, "Neri Luca", 0, 5.0};    errore di compilazione
     * dopo si assegna un campo alla volta */
    vuota.numero = 2000;
    vuota.credito = 5.00;
    printf("\nDopo gli assegnamenti: tessera %d, credito %.2f\n", vuota.numero, vuota.credito);

    return 0;
}
