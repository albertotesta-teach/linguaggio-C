/*
 * 080-problema-distanze-citta.c
 *
 * Tabella delle distanze stradali tra città
 *
 * Nelle vecchie carte stradali c'era una tabella a doppia entrata con le
 * distanze tra le città: è una matrice QUADRATA in cui la cella [i][j]
 * contiene i km tra la città i e la città j. Due proprietà la
 * caratterizzano:
 *   - la diagonale principale è tutta a zero (distanza di una città da sé);
 *   - è SIMMETRICA: [i][j] == [j][i].
 *
 * Le distanze sono approssimate al chilometro.
 *
 * Il programma:
 *   - verifica le due proprietà (un errore di trascrizione le romperebbe);
 *   - per ogni città trova la più vicina (minimo della riga, escludendo
 *     la diagonale);
 *   - trova la coppia di città più lontane (solo sopra la diagonale);
 *   - calcola la lunghezza di un itinerario, dato come sequenza di indici
 *     di città in un array.
 *
 * Struttura dati:
 *   int distanze[CITTA][CITTA]
 *   char citta[CITTA][LUNG]          nomi, paralleli a righe E colonne
 *   int itinerario[TAPPE]            indici delle città da visitare
 */

#include <stdio.h>

#define CITTA 6
#define LUNG  14
#define TAPPE 5

int main(void)
{
    int distanze[CITTA][CITTA] = {
        {  0,  37,  80,  90,  92,  63},
        { 37,   0, 115, 125,  60, 100},
        { 80, 115,   0, 145, 170, 125},
        { 90, 125, 145,   0, 140,  38},
        { 92,  60, 170, 140,   0, 150},
        { 63, 100, 125,  38, 150,   0}
    };
    char citta[CITTA][LUNG] = {
        "Alessandria", "Asti", "Genova", "Milano", "Torino", "Pavia"
    };
    int itinerario[TAPPE] = {0, 5, 3, 1, 4};    /* Al -> Pv -> Mi -> At -> To */

    int i;
    int j;
    int coerente = 1;
    int piu_vicina;
    int i_max = 0;
    int j_max = 1;
    int t;
    int km_totali = 0;

    /* ── 1. Verifica della tabella ────────────────────────────────── */
    for (i = 0; i < CITTA; i++) {
        if (distanze[i][i] != 0) {
            printf("Errore: distanza di %s da se stessa diversa da 0\n", citta[i]);
            coerente = 0;
        }
        for (j = i + 1; j < CITTA; j++) {
            if (distanze[i][j] != distanze[j][i]) {
                printf("Errore: %s-%s = %d ma %s-%s = %d\n",
                       citta[i], citta[j], distanze[i][j],
                       citta[j], citta[i], distanze[j][i]);
                coerente = 0;
            }
        }
    }
    printf("=== TABELLA DISTANZE (km) ===\n");
    printf("Diagonale nulla e simmetria: %s\n\n", coerente ? "verificate" : "ERRORI");

    /* ── 2. Città più vicina a ciascuna ───────────────────────────────
     * Il minimo della riga i va cercato escludendo la colonna i (che
     * vale 0): l'ipotesi iniziale è la prima colonna diversa da i.     */
    printf("--- Citta' piu' vicina ---\n");
    for (i = 0; i < CITTA; i++) {
        if (i == 0) {
            piu_vicina = 1;
        } else {
            piu_vicina = 0;
        }
        for (j = 0; j < CITTA; j++) {
            if (j != i && distanze[i][j] < distanze[i][piu_vicina]) {
                piu_vicina = j;
            }
        }
        printf("  %-12s -> %-12s %4d km\n", citta[i], citta[piu_vicina],
               distanze[i][piu_vicina]);
    }

    /* ── 3. Coppia più lontana: solo la parte sopra la diagonale ──────
     * Ogni coppia compare due volte nella matrice: basta esaminare le
     * celle con j > i.                                                 */
    for (i = 0; i < CITTA; i++) {
        for (j = i + 1; j < CITTA; j++) {
            if (distanze[i][j] > distanze[i_max][j_max]) {
                i_max = i;
                j_max = j;
            }
        }
    }
    printf("\nCoppia piu' lontana: %s - %s (%d km)\n\n",
           citta[i_max], citta[j_max], distanze[i_max][j_max]);

    /* ── 4. Lunghezza di un itinerario ────────────────────────────────
     * Ogni tratto va dalla tappa t alla tappa t + 1: la distanza si
     * legge alla riga itinerario[t] e colonna itinerario[t + 1].       */
    printf("--- Itinerario ---\n");
    for (t = 0; t < TAPPE - 1; t++) {
        printf("  %-12s -> %-12s %4d km\n",
               citta[itinerario[t]], citta[itinerario[t + 1]],
               distanze[itinerario[t]][itinerario[t + 1]]);
        km_totali = km_totali + distanze[itinerario[t]][itinerario[t + 1]];
    }
    printf("  Totale: %d km\n", km_totali);

    return 0;
}
