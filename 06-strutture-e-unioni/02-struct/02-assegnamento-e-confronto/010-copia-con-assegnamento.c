/*
 * 010-copia-con-assegnamento.c
 *
 * Una struct si copia con =, anche se contiene un array
 *
 * Due struct dello stesso tipo si possono assegnare con =: tutti i campi
 * vengono copiati, uno per uno, compresi gli array contenuti nella struct.
 *
 *     Pagella copia = originale;      copia di nome, classe e di tutti i voti
 *
 * Dopo la copia le due variabili sono indipendenti: modificare un voto
 * della copia non cambia l'originale.
 *
 * Con un array "nudo" questo non si può fare: v2 = v1 è un errore di
 * compilazione, e la copia si fa con un ciclo (o con strcpy per le
 * stringhe). Racchiudere l'array in una struct è un modo per poterlo
 * copiare con un solo assegnamento.
 *
 * Esempio: il coordinatore prepara una simulazione dei voti di fine anno
 * partendo dalla pagella del primo quadrimestre, senza toccarla.
 */

#include <stdio.h>

#define MATERIE 4

typedef struct {
    char nome[20];
    char classe[4];
    int voti[MATERIE];
} Pagella;

int main(void)
{
    const char *materie[MATERIE] = {"italiano", "matematica", "inglese", "informatica"};
    Pagella primo_quadrimestre = {"Elena Costa", "4A", {6, 5, 7, 8}};
    Pagella simulazione;
    int voti[MATERIE] = {6, 5, 7, 8};
    int copia_voti[MATERIE];
    int m;

    /* una sola istruzione copia nome, classe e i quattro voti */
    simulazione = primo_quadrimestre;

    /* la simulazione prevede il recupero di matematica e un voto in più in inglese */
    simulazione.voti[1] = 6;
    simulazione.voti[2] = 8;

    printf("  %-12s %8s %12s\n", "Materia", "Pagella", "Simulazione");
    for (m = 0; m < MATERIE; m++) {
        printf("  %-12s %8d %12d\n", materie[m], primo_quadrimestre.voti[m], simulazione.voti[m]);
    }
    printf("La pagella di %s (%s) non e' cambiata.\n", primo_quadrimestre.nome, primo_quadrimestre.classe);

    /* con un array semplice l'assegnamento non è permesso:
     * copia_voti = voti;      errore: assignment to expression with array type */
    for (m = 0; m < MATERIE; m++) {
        copia_voti[m] = voti[m];
    }
    printf("\nUn array semplice si copia elemento per elemento: copia_voti[3] = %d\n", copia_voti[3]);

    return 0;
}
