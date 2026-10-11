/*
 * 040-problema-orario-settimanale.c
 *
 * Orario della classe: il giorno richiesto e le ore per materia
 *
 * L'orario settimanale della 3B è una matrice orario[GIORNI][ORE]: ogni
 * cella contiene il codice della materia (indice nell'array di puntatori
 * materie). Lo studente chiede un giorno e il programma stampa le lezioni;
 * alla fine stampa quante ore settimanali ha ogni materia.
 *
 * Le funzioni lavorano con i puntatori alle righe:
 *   stampa_giorno(orario[g], ORE, materie)
 *       orario[g] è la riga del giorno: arriva come const int *
 *   ore_settimanali(orario, GIORNI, materia)
 *       riceve tutta la matrice come const int (*)[ORE] e la scorre con
 *       un puntatore a riga
 *
 * Il programma legge il numero del giorno (1-5); 0 termina.
 */

#include <stdio.h>

#define GIORNI  5
#define ORE     6
#define MATERIE 7

void stampa_giorno(const int *ore, int n, const char *materie[]);
int ore_settimanali(const int (*orario)[ORE], int giorni, int materia);

int main(void)
{
    const char *materie[MATERIE] = {"Italiano", "Matematica", "Informatica",
                                    "Inglese", "Sistemi", "Ed. fisica", "Storia"};
    const char *giorni[GIORNI] = {"Lunedi", "Martedi", "Mercoledi", "Giovedi", "Venerdi"};
    int orario[GIORNI][ORE] = {
        {0, 0, 1, 2, 2, 3},
        {4, 4, 1, 1, 6, 0},
        {2, 2, 2, 3, 5, 5},
        {1, 0, 0, 4, 4, 6},
        {3, 1, 2, 2, 0, 6}
    };
    int g = 1;
    int m;

    while (g != 0) {
        printf("Giorno (1-5, 0 per finire): ");
        if (scanf("%d", &g) != 1) {
            g = 0;
        }
        if (g < 0 || g > GIORNI) {
            printf("  Giorno non valido.\n");
        } else if (g != 0) {
            printf("  %s:\n", giorni[g - 1]);
            stampa_giorno(orario[g - 1], ORE, materie);
        }
    }

    printf("\nOre settimanali per materia:\n");
    for (m = 0; m < MATERIE; m++) {
        printf("  %-12s %d\n", materie[m], ore_settimanali(orario, GIORNI, m));
    }

    return 0;
}

/* Stampa le n ore di una riga dell'orario. */
void stampa_giorno(const int *ore, int n, const char *materie[])
{
    int h;

    for (h = 0; h < n; h++) {
        printf("    %da ora  %s\n", h + 1, materie[ore[h]]);
    }
}

/* Conta le celle con il codice materia, riga per riga. */
int ore_settimanali(const int (*orario)[ORE], int giorni, int materia)
{
    const int (*riga)[ORE];
    int h;
    int conteggio = 0;

    for (riga = orario; riga < orario + giorni; riga++) {
        for (h = 0; h < ORE; h++) {
            if ((*riga)[h] == materia) {
                conteggio++;
            }
        }
    }
    return conteggio;
}
