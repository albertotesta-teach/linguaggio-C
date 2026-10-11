/*
 * 020-sizeof-e-tipi.c
 *
 * Quanti byte occupa ogni tipo
 *
 * Una variabile occupa un numero di byte che dipende dal suo tipo.
 * L'operatore sizeof restituisce questa dimensione (di tipo size_t, si
 * stampa con %zu):
 *
 *     sizeof(int)       dimensione del tipo
 *     sizeof(x)         dimensione della variabile x
 *     sizeof(v)         dimensione di un intero array (N elementi)
 *
 * Le dimensioni NON sono fissate dal linguaggio: lo standard garantisce
 * solo che sizeof(char) vale 1 e alcuni valori minimi. I valori stampati
 * sono quelli tipici di un computer a 64 bit.
 *
 * Anche un indirizzo occupa memoria: sui sistemi a 64 bit un indirizzo è
 * lungo 8 byte, qualunque sia il tipo della variabile a cui si riferisce.
 */

#include <stdio.h>

#define MISURE 10

int main(void)
{
    double temperature[MISURE];
    char sigla[] = "AL";
    int quanti;

    printf("=== DIMENSIONE DEI TIPI ===\n");
    printf("  char        %2zu byte\n", sizeof(char));
    printf("  short       %2zu byte\n", sizeof(short));
    printf("  int         %2zu byte\n", sizeof(int));
    printf("  long        %2zu byte\n", sizeof(long));
    printf("  long long   %2zu byte\n", sizeof(long long));
    printf("  float       %2zu byte\n", sizeof(float));
    printf("  double      %2zu byte\n", sizeof(double));

    printf("\n=== DIMENSIONE DI ARRAY E STRINGHE ===\n");
    printf("  double temperature[%d]  %3zu byte (%d x %zu)\n", MISURE,
           sizeof(temperature), MISURE, sizeof(temperature[0]));
    printf("  char sigla[] = \"AL\"     %3zu byte (2 lettere + '\\0')\n", sizeof(sigla));

    /* il numero di elementi si ricava dividendo le due dimensioni */
    quanti = (int) (sizeof(temperature) / sizeof(temperature[0]));
    printf("  elementi di temperature: %d\n", quanti);

    printf("\n=== DIMENSIONE DI UN INDIRIZZO ===\n");
    printf("  &quanti         %zu byte\n", sizeof(&quanti));
    printf("  &temperature[0] %zu byte\n", sizeof(&temperature[0]));
    printf("  Un indirizzo ha la stessa dimensione qualunque sia il tipo.\n");

    return 0;
}
