/*
 * 030-matrici-con-nome.c
 *
 * Matrici con un nome: typedef costruite su altre typedef
 *
 * Un tipo definito con typedef si può usare come elemento di un altro
 * array, e quindi anche in una nuova typedef:
 *
 *     typedef int Settimana[7];
 *     typedef Settimana Prestiti[SEZIONI];      come int[SEZIONI][7]
 *
 *     typedef char Targa[8];
 *     Targa riservati[4];                        come char[4][8]
 *
 * Ogni riga di una variabile Prestiti è una Settimana: si può passare
 * direttamente a una funzione scritta per Settimana. Allo stesso modo
 * riservati[i] è una Targa, da usare con strcmp o printf("%s").
 *
 * Esempio: i prestiti giornalieri delle tre sezioni della biblioteca e le
 * targhe dei posti auto riservati ai volontari.
 */

#include <stdio.h>
#include <string.h>

#define GIORNI   7
#define SEZIONI  3
#define RISERVATI 4

typedef int Settimana[GIORNI];
typedef Settimana Prestiti[SEZIONI];
typedef char Targa[8];

int totale(const Settimana s);

int main(void)
{
    const char *sezioni[SEZIONI] = {"Narrativa", "Saggistica", "Fumetti"};
    Prestiti prestiti = {
        {12, 15, 9, 14, 18, 22, 0},
        {4, 6, 3, 5, 7, 8, 0},
        {9, 11, 8, 12, 15, 25, 0}
    };
    Targa riservati[RISERVATI] = {"EK301TZ", "DM774PA", "FH052LC", "GB918RN"};
    Targa cercata = "DM774PA";
    int s;
    int r;
    int trovata = 0;

    printf("=== PRESTITI DELLA SETTIMANA ===\n");
    printf("  sizeof(Settimana) = %zu, sizeof(Prestiti) = %zu byte\n",
           sizeof(Settimana), sizeof(Prestiti));
    for (s = 0; s < SEZIONI; s++) {
        /* prestiti[s] è una Settimana: va bene per totale() */
        printf("  %-11s %3d prestiti\n", sezioni[s], totale(prestiti[s]));
    }

    printf("\n=== POSTI RISERVATI ===\n");
    for (r = 0; r < RISERVATI; r++) {
        printf("  posto %d: %s\n", r + 1, riservati[r]);
        if (strcmp(riservati[r], cercata) == 0) {
            trovata = r + 1;
        }
    }
    if (trovata) {
        printf("  %s ha il posto %d\n", cercata, trovata);
    } else {
        printf("  %s non ha un posto riservato\n", cercata);
    }

    return 0;
}

int totale(const Settimana s)
{
    int somma = 0;
    int g;

    for (g = 0; g < GIORNI; g++) {
        somma = somma + s[g];
    }
    return somma;
}
