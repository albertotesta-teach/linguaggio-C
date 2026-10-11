/*
 * 070-problema-voti-classe.c
 *
 * Tabellone dei voti di fine periodo
 *
 * Il coordinatore di classe prepara il tabellone per lo scrutinio:
 * 6 studenti, 4 materie, un voto intero per ogni coppia studente-materia.
 * Il programma:
 *   - stampa il tabellone con la media di ogni studente;
 *   - conta le insufficienze (voto < 6) di ogni studente e segnala chi
 *     ha almeno un debito;
 *   - per ogni materia indica quanti studenti sono insufficienti.
 *
 * Struttura dati:
 *   int voti[STUDENTI][MATERIE]       la matrice dei voti
 *   char studenti[STUDENTI][LUNG]     parallelo alle righe
 *   char materie[MATERIE][LUNG_MAT]   parallelo alle colonne
 */

#include <stdio.h>

#define STUDENTI 6
#define MATERIE  4
#define LUNG     16
#define LUNG_MAT 12
#define SUFFICIENZA 6

int main(void)
{
    int voti[STUDENTI][MATERIE] = {
        {7, 6, 8, 9},
        {5, 4, 6, 7},
        {8, 9, 7, 8},
        {6, 5, 5, 6},
        {9, 8, 9, 10},
        {6, 6, 4, 7}
    };
    char studenti[STUDENTI][LUNG] = {
        "Bianchi Sara", "Colombo Luca", "Esposito Ilaria",
        "Ferri Matteo", "Galli Chiara", "Marini Davide"
    };
    char materie[MATERIE][LUNG_MAT] = {
        "Italiano", "Matematica", "Inglese", "Informatica"
    };

    int s;
    int m;
    int somma;
    int insufficienze;
    int studenti_con_debito = 0;
    int insufficienti_materia;

    /* ── 1. Tabellone ─────────────────────────────────────────────── */
    printf("=== TABELLONE VOTI - CLASSE 3A ===\n\n");
    printf("  %-16s", "Studente");
    for (m = 0; m < MATERIE; m++) {
        printf("%12s", materie[m]);
    }
    printf("   Media  Insuff.\n");

    for (s = 0; s < STUDENTI; s++) {
        somma = 0;
        insufficienze = 0;
        printf("  %-16s", studenti[s]);
        for (m = 0; m < MATERIE; m++) {
            printf("%12d", voti[s][m]);
            somma = somma + voti[s][m];
            if (voti[s][m] < SUFFICIENZA) {
                insufficienze++;
            }
        }
        printf("   %5.2f  %5d", (double) somma / MATERIE, insufficienze);

        if (insufficienze > 0) {
            printf("   <- debito");
            studenti_con_debito++;
        }
        printf("\n");
    }

    printf("\nStudenti con almeno un'insufficienza: %d su %d\n",
           studenti_con_debito, STUDENTI);

    /* ── 2. Insufficienti per materia (scorrimento per colonne) ───── */
    printf("\n--- Insufficienze per materia ---\n");
    for (m = 0; m < MATERIE; m++) {
        insufficienti_materia = 0;
        for (s = 0; s < STUDENTI; s++) {
            if (voti[s][m] < SUFFICIENZA) {
                insufficienti_materia++;
            }
        }
        printf("  %-12s: %d\n", materie[m], insufficienti_materia);
    }

    /*
     * NOTA: i due array di nomi hanno ruoli diversi. studenti[s] descrive
     * la riga s, materie[m] la colonna m: per stampare l'intestazione si
     * usa materie, per l'inizio di ogni riga si usa studenti.
     */

    return 0;
}
