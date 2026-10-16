/*
 * 070-problema-numerazione-delle-righe.c
 *
 * Un filtro che numera le righe di un testo
 *
 * Per discutere in classe un programma o una poesia serve poter dire
 * "guardate la riga 12". Il filtro legge stdin e copia su stdout
 * mettendo il numero davanti a ogni riga non vuota; le righe vuote
 * restano vuote e non consumano un numero.
 *
 *     ./070-problema-numerazione-delle-righe < 010-fopen-e-fclose.c
 *
 * Il filtro lavora carattere per carattere, senza sapere quanto sono
 * lunghe le righe. Basta ricordare se il carattere corrente è il primo
 * di una riga:
 *
 *     inizio_riga = 1
 *     per ogni carattere c:
 *         se inizio_riga e c != '\n':  stampa il numero
 *         stampa c
 *         inizio_riga = (c == '\n')
 *
 * Il totale delle righe numerate va su stderr, così non finisce nel
 * file di uscita quando stdout è rediretto.
 */

#include <stdio.h>

int main(void)
{
    int numero = 0;
    int vuote = 0;
    int inizio_riga = 1;
    int c;

    c = fgetc(stdin);
    while (c != EOF) {
        if (inizio_riga && c != '\n') {
            numero++;
            fprintf(stdout, "%4d  ", numero);
        } else if (inizio_riga) {
            vuote++;
        }
        fputc(c, stdout);
        inizio_riga = c == '\n';
        c = fgetc(stdin);
    }
    fprintf(stderr, "[numerazione] righe numerate: %d, righe vuote: %d\n", numero, vuote);

    return 0;
}
