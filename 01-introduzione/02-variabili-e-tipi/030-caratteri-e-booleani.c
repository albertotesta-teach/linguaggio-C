/*
 * 030-caratteri-e-booleani.c
 *
 * Tipo char e simulazione del tipo booleano
 *
 * Introduce il tipo char come intero a 8 bit e la sua corrispondenza
 * con il codice ASCII. Mostra come stampare un char sia come carattere
 * (%c) sia come numero intero (%d). Introduce la simulazione del tipo
 * booleano con int (0 = falso, qualunque altro valore = vero), tecnica
 * usata nel C classico prima dell'introduzione di <stdbool.h> (C99).
 */

#include <stdio.h>

int main(void)
{
    /* ── tipo char ──────────────────────────────────────────────────────── */
    /* char è un intero a 8 bit: può contenere valori da -128 a 127
     * (signed) oppure da 0 a 255 (unsigned), a seconda del compilatore.
     * Il suo uso principale è contenere un singolo carattere. */
    char lettera   = 'A';   /* i caratteri si scrivono tra apici singoli */
    char cifra     = '7';
    char simbolo   = '+';
    char a_capo    = '\n';  /* sequenza di escape: carattere non stampabile */

    printf("=== Caratteri e codici ASCII ===\n");

    /* %c stampa il carattere, %d stampa il valore numerico corrispondente */
    printf("Carattere 'A':  come char=%c  come intero=%d\n", lettera, lettera);
    printf("Carattere '7':  come char=%c  come intero=%d\n", cifra,   cifra);
    printf("Carattere '+':  come char=%c  come intero=%d\n", simbolo, simbolo);
    printf("Dimensione di char: %zu byte\n", sizeof(char));

    /* ── aritmetica sui char ─────────────────────────────────────────────── */
    /* Poiché char è un intero, si possono fare operazioni aritmetiche.
     * Il codice ASCII di 'A' è 65; aggiungendo un offset si ottengono
     * le lettere successive. Utile per cifrari e conversioni. */
    printf("\n=== Aritmetica sui char ===\n");
    printf("'A' + 1 = '%c'  (codice %d)\n", (char)(lettera + 1), lettera + 1);
    printf("'A' + 2 = '%c'  (codice %d)\n", (char)(lettera + 2), lettera + 2);

    /* ── sequenze di escape più comuni ─────────────────────────────────── */
    printf("\n=== Sequenze di escape ===\n");
    printf("\\n  = a capo          (codice %d)\n", '\n');
    printf("\\t  = tabulazione     (codice %d)\n", '\t');
    printf("\\'  = apice singolo   (codice %d)\n", '\'');
    printf("\\\\  = barra rovescia  (codice %d)\n", '\\');
    printf("\\0  = carattere null  (codice %d)\n", '\0');

    /* ── simulazione del booleano con int ───────────────────────────────── */
    /* In C non esiste un tipo bool nativo fino al C99.
     * La convenzione è: 0 = falso, qualunque valore diverso da 0 = vero.
     * Si usano variabili int con nomi che esprimono una condizione. */
    int maggiorenne = 0;   /* 0 = falso */
    int patente     = 1;   /* 1 = vero  */
    int eta         = 20;

    /* l'operatore di confronto restituisce 0 o 1 */
    maggiorenne = (eta >= 18);

    printf("\n=== Simulazione booleana con int ===\n");
    printf("Eta':         %d\n",   eta);
    printf("Maggiorenne:  %d  (0=falso, 1=vero)\n", maggiorenne);
    printf("Ha la patente: %d\n",  patente);

    /* sopprimiamo il warning su a_capo usata solo per la dichiarazione */
    (void)a_capo;

    return 0;
}
