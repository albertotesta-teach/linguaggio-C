/*
 * 030-struct-con-array.c
 *
 * Una struct che contiene un array, dentro un array di struct
 *
 * Un campo di una struct può essere un array: per ogni studente i voti
 * delle verifiche di matematica, con il numero di voti effettivamente
 * presenti (non tutti hanno fatto tutte le verifiche).
 *
 *     typedef struct {
 *         char nome[20];
 *         int voti[MAX_VOTI];
 *         int n_voti;
 *     } Registro;
 *
 *     Registro classe[STUDENTI];
 *
 *     classe[s]              lo studente s
 *     classe[s].voti         il suo array di voti
 *     classe[s].voti[v]      il voto v dello studente s
 *     classe[s].n_voti       quanti voti ha
 *
 * Le parentesi quadre e il punto si leggono da sinistra a destra: prima
 * l'elemento dell'array esterno, poi il campo, poi l'elemento del campo.
 *
 * Esempio: il registro dei voti di matematica di una classe.
 */

#include <stdio.h>

#define STUDENTI 4
#define MAX_VOTI 6

typedef struct {
    char nome[20];
    int voti[MAX_VOTI];
    int n_voti;
} Registro;

int main(void)
{
    Registro classe[STUDENTI] = {
        {"Bruno Elisa", {7, 8, 6, 9}, 4},
        {"Conti Paolo", {5, 6, 5}, 3},
        {"De Luca Ilaria", {8, 8, 9, 7, 10}, 5},
        {"Moretti Samuele", {4, 6}, 2}
    };
    int s;
    int v;
    int somma;

    printf("  %-16s Voti              Media\n", "Studente");
    for (s = 0; s < STUDENTI; s++) {
        printf("  %-16s", classe[s].nome);
        somma = 0;
        for (v = 0; v < classe[s].n_voti; v++) {
            printf("%3d", classe[s].voti[v]);
            somma = somma + classe[s].voti[v];
        }
        printf("%*s %5.2f", 3 * (MAX_VOTI - classe[s].n_voti), "", (double) somma / classe[s].n_voti);
        if (classe[s].n_voti < 3) {
            printf("  (pochi voti)");
        }
        printf("\n");
    }

    /* aggiungere un voto: si scrive nella prima posizione libera */
    s = 3;
    if (classe[s].n_voti < MAX_VOTI) {
        classe[s].voti[classe[s].n_voti] = 7;
        classe[s].n_voti++;
        printf("\nAggiunto un 7 a %s: ora ha %d voti\n", classe[s].nome, classe[s].n_voti);
    }

    return 0;
}
