/*
 * 010-tipo-array.c
 *
 * Un nome per un tipo array
 *
 * typedef può dare un nome anche a un array di dimensione fissa:
 *
 *     typedef char Targa[8];        7 caratteri + '\0'
 *     typedef int Settimana[7];     un valore per ogni giorno
 *
 *     Targa auto_preside = "GA482KM";       come char auto_preside[8]
 *     Settimana ingressi = {...};          come int ingressi[7]
 *
 * La regola della sintassi è la stessa di prima: si scrive la
 * dichiarazione di una variabile (char Targa[8]) e si aggiunge typedef
 * davanti; il nome diventa il nome del tipo, dimensione compresa.
 *
 * Una variabile Targa è un vero array di 8 char: si inizializza con un
 * letterale, si legge con l'indice, sizeof dà 8. Valgono anche i limiti
 * degli array: non si copia con = ma con strcpy (o con un ciclo).
 *
 * Esempio: il parcheggio della scuola, con le targhe dei posti riservati
 * e gli ingressi della settimana.
 */

#include <stdio.h>
#include <string.h>

typedef char Targa[8];
typedef int Settimana[7];

int main(void)
{
    Targa auto_preside = "GA482KM";
    Targa auto_vicepreside;
    Settimana ingressi = {84, 91, 88, 79, 73, 12, 0};
    int g;
    int totale = 0;

    /* auto_vicepreside = auto_preside;   errore: un array non si assegna con = */
    strcpy(auto_vicepreside, "FT109RS");

    printf("=== TARGHE ===\n");
    printf("  Preside:     %s  (prima lettera %c, %zu caratteri)\n",
           auto_preside, auto_preside[0], strlen(auto_preside));
    printf("  Vicepreside: %s\n", auto_vicepreside);
    printf("  sizeof(Targa) = %zu byte\n", sizeof(Targa));

    printf("\n=== INGRESSI DELLA SETTIMANA ===\n  ");
    for (g = 0; g < 7; g++) {
        printf("%4d", ingressi[g]);
        totale = totale + ingressi[g];
    }
    printf("\n  Totale: %d ingressi\n", totale);
    printf("  sizeof(Settimana) = %zu byte = 7 x sizeof(int)\n", sizeof(Settimana));

    return 0;
}
