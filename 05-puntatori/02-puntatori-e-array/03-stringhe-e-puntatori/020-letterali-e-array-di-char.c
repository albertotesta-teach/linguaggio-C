/*
 * 020-letterali-e-array-di-char.c
 *
 * Array di char e puntatore a un letterale
 *
 * Le due dichiarazioni sembrano uguali ma sono molto diverse:
 *
 *     char giorno[] = "lunedi";
 *         un ARRAY di 7 char, inizializzato con una copia del testo:
 *         i caratteri si possono modificare, l'array non si sposta.
 *
 *     const char *stato = "APERTO";
 *         un PUNTATORE al letterale "APERTO", che il compilatore conserva
 *         in una zona di sola lettura: il testo non si modifica (per questo
 *         const), ma il puntatore può puntare a un altro letterale.
 *
 * Un puntatore a letterale è comodo per scegliere un messaggio senza
 * copiarlo: stato = "CHIUSO";
 *
 * Esempio: il cartello di un negozio, con il giorno e lo stato di apertura.
 */

#include <stdio.h>

#define APERTURA 9
#define CHIUSURA 19

int main(void)
{
    char giorno[] = "lunedi";
    const char *stato = "APERTO";
    int ore[4] = {8, 11, 19, 21};
    int i;

    printf("=== ARRAY E PUNTATORE ===\n");
    printf("  sizeof(giorno) = %zu byte  (6 lettere + '\\0')\n", sizeof(giorno));
    printf("  sizeof(stato)  = %zu byte  (un indirizzo)\n", sizeof(stato));

    /* l'array si modifica carattere per carattere */
    giorno[0] = 'L';
    printf("\nDopo giorno[0] = 'L': %s\n", giorno);
    /* stato[0] = 'a';   errore di compilazione: il letterale e' const */

    /* il puntatore si sposta su un altro letterale */
    printf("\n=== CARTELLO (%s) ===\n", giorno);
    for (i = 0; i < 4; i++) {
        if (ore[i] >= APERTURA && ore[i] < CHIUSURA) {
            stato = "APERTO";
        } else {
            stato = "CHIUSO";
        }
        printf("  ore %2d:00  %s   (stato = %p)\n", ore[i], stato, (void *) stato);
    }

    return 0;
}
