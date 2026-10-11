/*
 * 020-massimo-minimo-e-ricerca.c
 *
 * Estremi, ricerca e conteggio in una matrice
 *
 * Gli stessi pattern visti sugli array, estesi alle due dimensioni:
 *
 *   MASSIMO/MINIMO   ipotesi sul primo elemento [0][0], smentita scorrendo
 *                    tutta la matrice; si memorizzano RIGA e COLONNA
 *   RICERCA          con un flag nella condizione di ENTRAMBI i cicli,
 *                    così si esce da tutti e due appena trovato (senza break)
 *   CONTEGGIO        di quante celle soddisfano una condizione
 *   ESTREMO DI RIGA  il massimo di ogni riga: l'ipotesi si riparte per
 *                    ogni riga dal suo primo elemento
 *
 * Esempio: punteggi di 4 squadre in 6 prove di un torneo di giochi logici.
 */

#include <stdio.h>

#define SQUADRE 4
#define PROVE   6

int main(void)
{
    int punti[SQUADRE][PROVE] = {
        {12, 15,  9, 18, 14, 11},
        { 8, 20, 13, 10, 16, 20},
        {17, 11, 19,  7, 12, 15},
        {10, 14, 16, 13,  9, 18}
    };
    int s;
    int p;
    int s_max = 0;
    int p_max = 0;
    int s_min = 0;
    int p_min = 0;
    int cercato = 13;
    int trovato = 0;
    int s_trovato = -1;
    int p_trovato = -1;
    int soglia = 15;
    int sopra_soglia = 0;
    int max_riga;

    printf("=== TORNEO DI GIOCHI LOGICI ===\n");
    printf("             P1  P2  P3  P4  P5  P6\n");
    for (s = 0; s < SQUADRE; s++) {
        printf("  Squadra %d", s + 1);
        for (p = 0; p < PROVE; p++) {
            printf("%4d", punti[s][p]);
        }
        printf("\n");
    }
    printf("\n");

    /* ── 1. Massimo e minimo con posizione ────────────────────────────
     * In caso di parità resta il primo trovato (confronto stretto):
     * il 20 della squadra 2 in P2 viene prima di quello in P6.         */
    for (s = 0; s < SQUADRE; s++) {
        for (p = 0; p < PROVE; p++) {
            if (punti[s][p] > punti[s_max][p_max]) {
                s_max = s;
                p_max = p;
            }
            if (punti[s][p] < punti[s_min][p_min]) {
                s_min = s;
                p_min = p;
            }
        }
    }
    printf("Punteggio piu' alto : %d (squadra %d, prova %d)\n",
           punti[s_max][p_max], s_max + 1, p_max + 1);
    printf("Punteggio piu' basso: %d (squadra %d, prova %d)\n\n",
           punti[s_min][p_min], s_min + 1, p_min + 1);

    /* ── 2. Ricerca della prima occorrenza ────────────────────────────
     * Il flag "trovato" compare in entrambe le condizioni: quando
     * diventa 1 si fermano sia il ciclo interno sia quello esterno.    */
    for (s = 0; s < SQUADRE && !trovato; s++) {
        for (p = 0; p < PROVE && !trovato; p++) {
            if (punti[s][p] == cercato) {
                trovato = 1;
                s_trovato = s;
                p_trovato = p;
            }
        }
    }
    if (trovato) {
        printf("Primo punteggio %d: squadra %d, prova %d\n",
               cercato, s_trovato + 1, p_trovato + 1);
    } else {
        printf("Nessun punteggio uguale a %d\n", cercato);
    }

    /* ── 3. Conteggio con condizione ──────────────────────────────── */
    for (s = 0; s < SQUADRE; s++) {
        for (p = 0; p < PROVE; p++) {
            if (punti[s][p] >= soglia) {
                sopra_soglia++;
            }
        }
    }
    printf("Prove con almeno %d punti: %d su %d\n\n",
           soglia, sopra_soglia, SQUADRE * PROVE);

    /* ── 4. Massimo di ogni riga ──────────────────────────────────────
     * L'ipotesi riparte per ogni riga: max_riga = punti[s][0].         */
    printf("Miglior prova di ogni squadra:\n");
    for (s = 0; s < SQUADRE; s++) {
        max_riga = punti[s][0];
        for (p = 1; p < PROVE; p++) {
            if (punti[s][p] > max_riga) {
                max_riga = punti[s][p];
            }
        }
        printf("  Squadra %d: %d\n", s + 1, max_riga);
    }

    /*
     * ERRORE COMUNE: inizializzare il massimo di riga una sola volta,
     * prima del ciclo esterno. Dalla seconda riga in poi il confronto
     * partirebbe dal massimo delle righe precedenti.
     */

    return 0;
}
