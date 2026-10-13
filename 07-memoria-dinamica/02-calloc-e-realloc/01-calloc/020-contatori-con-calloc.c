/*
 * 020-contatori-con-calloc.c
 *
 * Contatori che partono da zero: le lettere più frequenti in un testo
 *
 * Un array di contatori deve partire da zero. Con calloc l'azzeramento è
 * compreso nell'allocazione:
 *
 *     int *conta = calloc(LETTERE, sizeof *conta);    26 contatori a 0
 *
 *     conta[c - 'a']++;              un contatore per lettera
 *
 * Il programma legge righe di testo fino a una riga vuota, conta le
 * lettere (maiuscole e minuscole insieme) e stampa quelle presenti con
 * una barra proporzionale, e la lettera più frequente.
 *
 * Esempio: le frasi di un esercizio di crittografia (nel cifrario di
 * Cesare la lettera più frequente del testo cifrato corrisponde spesso
 * alla E o alla A del testo in chiaro).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LETTERE 26
#define LUNG 100

int main(void)
{
    int *conta = calloc(LETTERE, sizeof *conta);
    char riga[LUNG];
    int finito = 0;
    int totale = 0;
    int massimo = 0;
    int i;
    int k;

    if (conta == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        printf("Testo (riga vuota per terminare):\n");
        while (!finito) {
            if (fgets(riga, LUNG, stdin) == NULL || riga[0] == '\n') {
                finito = 1;
            } else {
                for (i = 0; riga[i] != '\0'; i++) {
                    if (isalpha((unsigned char) riga[i])) {
                        conta[tolower((unsigned char) riga[i]) - 'a']++;
                        totale++;
                    }
                }
            }
        }

        printf("\nLettere: %d\n", totale);
        for (k = 0; k < LETTERE; k++) {
            if (conta[k] > 0) {
                printf("  %c %3d ", 'a' + k, conta[k]);
                for (i = 0; i < conta[k]; i++) {
                    printf("#");
                }
                printf("\n");
            }
            if (conta[k] > conta[massimo]) {
                massimo = k;
            }
        }
        if (totale > 0) {
            printf("Piu' frequente: %c (%d volte)\n", 'a' + massimo, conta[massimo]);
        }
        free(conta);
    }

    return 0;
}
