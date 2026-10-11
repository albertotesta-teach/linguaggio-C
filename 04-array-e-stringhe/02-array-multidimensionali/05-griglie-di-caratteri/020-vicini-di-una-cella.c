/*
 * 020-vicini-di-una-cella.c
 *
 * Contare i vicini di una cella in tutte le 8 direzioni
 *
 * Molti giochi su griglia (campo minato, gioco della vita, ...) devono
 * esaminare le 8 celle che circondano una cella:
 *
 *     [r-1][c-1]  [r-1][c]  [r-1][c+1]
 *     [r][c-1]     [r][c]   [r][c+1]
 *     [r+1][c-1]  [r+1][c]  [r+1][c+1]
 *
 * Invece di scrivere 8 controlli si usano due cicli sugli SPOSTAMENTI
 * dr e dc, che valgono -1, 0 e +1. Si esclude lo spostamento (0, 0),
 * che è la cella stessa, e si scartano le celle fuori dalla griglia.
 *
 * Esempio: in un frutteto 'X' indica un albero malato. Per ogni cella il
 * programma conta quanti alberi malati ha intorno e stampa la "mappa del
 * rischio" (0-8).
 */

#include <stdio.h>

#define RIGHE   5
#define COLONNE 8
#define MALATO  'X'

int conta_vicini(const char g[][COLONNE + 1], int r, int c, char simbolo);

int main(void)
{
    char frutteto[RIGHE][COLONNE + 1] = {
        "o.o.o.o.",
        "oXo.o.oX",
        "o.oXo.o.",
        "o.o.o.o.",
        "X.o.o.oX"
    };
    int r;
    int c;

    printf("Frutteto (X = albero malato):    Alberi malati vicini:\n");
    for (r = 0; r < RIGHE; r++) {
        printf("  ");
        for (c = 0; c < COLONNE; c++) {
            printf("%c ", frutteto[r][c]);
        }
        printf("                ");
        for (c = 0; c < COLONNE; c++) {
            printf("%d ", conta_vicini(frutteto, r, c, MALATO));
        }
        printf("\n");
    }

    printf("\nVicini della cella [0][0] (angolo): %d\n",
           conta_vicini(frutteto, 0, 0, MALATO));
    printf("Vicini della cella [2][2]: %d\n", conta_vicini(frutteto, 2, 2, MALATO));

    return 0;
}

/* Restituisce quante delle (al massimo) 8 celle intorno a [r][c]
 * contengono il simbolo. Le celle fuori dalla griglia non si contano. */
int conta_vicini(const char g[][COLONNE + 1], int r, int c, char simbolo)
{
    int dr;
    int dc;
    int rv;
    int cv;
    int conteggio = 0;

    for (dr = -1; dr <= 1; dr++) {
        for (dc = -1; dc <= 1; dc++) {
            rv = r + dr;
            cv = c + dc;
            /* esclude la cella stessa e quelle fuori dalla griglia;
             * il corto circuito evita di leggere g[rv][cv] se fuori */
            if (!(dr == 0 && dc == 0)
                && rv >= 0 && rv < RIGHE && cv >= 0 && cv < COLONNE
                && g[rv][cv] == simbolo) {
                conteggio++;
            }
        }
    }
    return conteggio;
}

/*
 * NOTA: una cella d'angolo ha solo 3 vicini, una di bordo 5, una interna 8.
 * Il controllo dei limiti nella condizione gestisce tutti i casi con lo
 * stesso codice.
 */
