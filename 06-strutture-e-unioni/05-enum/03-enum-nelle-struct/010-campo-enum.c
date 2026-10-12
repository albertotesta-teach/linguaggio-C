/*
 * 010-campo-enum.c
 *
 * Un campo di tipo enum dentro una struct
 *
 * Lo stato di un oggetto è spesso uno tra pochi valori: è il caso tipico
 * di un campo enum.
 *
 *     typedef enum {
 *         DISPONIBILE, IN_PRESTITO, IN_RIPARAZIONE, NUM_STATI
 *     } Stato;
 *
 *     typedef struct {
 *         char titolo[28];
 *         Stato stato;
 *     } Libro;
 *
 *     libri[i].stato == IN_PRESTITO
 *
 * Rispetto a due campi int (prestato, rovinato) che possono
 * contraddirsi, un solo campo enum ammette un solo stato alla volta.
 * Lo stato è anche un indice: conteggi[libri[i].stato]++ conta i libri
 * di ogni stato in un solo ciclo.
 *
 * Esempio: la biblioteca di classe. Si contano i libri per stato, si
 * elencano quelli disponibili e un libro torna dalla riparazione.
 */

#include <stdio.h>

#define LIBRI 6

typedef enum {
    DISPONIBILE, IN_PRESTITO, IN_RIPARAZIONE, NUM_STATI
} Stato;

typedef struct {
    char titolo[28];
    Stato stato;
} Libro;

void conta_per_stato(const Libro libri[], int n);

int main(void)
{
    Libro libri[LIBRI] = {
        {"Il barone rampante", DISPONIBILE},
        {"Fahrenheit 451", IN_PRESTITO},
        {"Io, robot", IN_RIPARAZIONE},
        {"La luna e i falo'", DISPONIBILE},
        {"Se questo e' un uomo", IN_PRESTITO},
        {"Il sistema periodico", IN_PRESTITO}
    };
    int i;

    conta_per_stato(libri, LIBRI);

    printf("Disponibili:\n");
    for (i = 0; i < LIBRI; i++) {
        if (libri[i].stato == DISPONIBILE) {
            printf("  %s\n", libri[i].titolo);
        }
    }

    libri[2].stato = DISPONIBILE;
    printf("\n\"%s\" torna dalla riparazione.\n", libri[2].titolo);
    conta_per_stato(libri, LIBRI);

    return 0;
}

void conta_per_stato(const Libro libri[], int n)
{
    const char *nomi[NUM_STATI] = {[DISPONIBILE] = "disponibili", [IN_PRESTITO] = "in prestito",
                                   [IN_RIPARAZIONE] = "in riparazione"};
    int conteggi[NUM_STATI] = {0};
    Stato s;
    int i;

    for (i = 0; i < n; i++) {
        conteggi[libri[i].stato]++;
    }
    for (s = DISPONIBILE; s < NUM_STATI; s++) {
        printf("  %-15s %d\n", nomi[s], conteggi[s]);
    }
}
