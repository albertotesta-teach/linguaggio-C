/*
 * 070-problema-campo-minato.c
 *
 * Campo minato: preparazione del campo e partita
 *
 * Il campo è descritto da due griglie:
 *   mine[][]      '*' = mina, '.' = cella sicura (segreta)
 *   scoperte[][]  1 se la cella è stata scoperta dal giocatore, 0 altrimenti
 * e da una matrice di numeri calcolata all'inizio:
 *   numeri[][]    per ogni cella sicura, quante mine ci sono intorno (0-8)
 *
 * Il giocatore scopre una cella alla volta indicando riga e colonna (1-6 e
 * 1-8). Se scopre una mina perde; se scopre tutte le celle sicure vince.
 * Le celle coperte sono mostrate con '#', quelle scoperte con il numero di
 * mine vicine (o uno spazio se 0).
 *
 * La matrice numeri[][] è un esempio di "matrice calcolata da un'altra":
 * si ottiene contando i vicini (020) una sola volta, invece di ricontarli
 * a ogni stampa.
 */

#include <stdio.h>

#define RIGHE   6
#define COLONNE 8
#define MINA    '*'

int conta_mine_vicine(const char m[][COLONNE + 1], int r, int c);
void stampa_campo(const char m[][COLONNE + 1], const int numeri[][COLONNE],
                  const int scoperte[][COLONNE], int mostra_mine);

int main(void)
{
    char mine[RIGHE][COLONNE + 1] = {
        "......*.",
        ".*......",
        "........",
        "...*..*.",
        "........",
        "*......."
    };
    int numeri[RIGHE][COLONNE];
    int scoperte[RIGHE][COLONNE] = {{0}};
    int r;
    int c;
    int riga_utente;
    int colonna_utente;
    int letti;          /* valori convertiti da scanf */
    int scarta;         /* carattere scartato da una riga non valida */
    int fine_input = 0; /* 1 se l'input termina durante la partita */
    int celle_sicure = 0;
    int scoperte_sicure = 0;
    int esplosa = 0;

    /* ── 1. Preparazione: numeri e conteggio delle celle sicure ───── */
    for (r = 0; r < RIGHE; r++) {
        for (c = 0; c < COLONNE; c++) {
            numeri[r][c] = conta_mine_vicine(mine, r, c);
            if (mine[r][c] != MINA) {
                celle_sicure++;
            }
        }
    }

    printf("=== CAMPO MINATO ===\n");
    printf("Celle sicure da scoprire: %d\n", celle_sicure);
    stampa_campo(mine, numeri, scoperte, 0);

    /* ── 2. Partita ───────────────────────────────────────────────── */
    while (!esplosa && scoperte_sicure < celle_sicure && !fine_input) {
        printf("Riga e colonna (es. 3 4): ");
        letti = scanf("%d %d", &riga_utente, &colonna_utente);
        if (letti == EOF) {
            fine_input = 1;
        } else if (letti != 2) {
            /* non è un numero: si scarta il resto della riga */
            scarta = getchar();
            while (scarta != '\n' && scarta != EOF) {
                scarta = getchar();
            }
            riga_utente = 0;    /* cella non letta: risulterà inesistente */
        }
        r = riga_utente - 1;
        c = colonna_utente - 1;

        if (fine_input) {
            printf("\n\nInput terminato: partita interrotta.\n");
        } else if (r < 0 || r >= RIGHE || c < 0 || c >= COLONNE) {
            printf("  Cella inesistente.\n");
        } else if (scoperte[r][c]) {
            printf("  Cella gia' scoperta.\n");
        } else {
            scoperte[r][c] = 1;
            if (mine[r][c] == MINA) {
                esplosa = 1;
            } else {
                scoperte_sicure++;
                stampa_campo(mine, numeri, scoperte, 0);
            }
        }
    }

    if (!fine_input) {
        if (esplosa) {
            printf("BOOM! Hai trovato una mina. Il campo era:\n");
        } else {
            printf("Complimenti, campo sminato!\n");
        }
        stampa_campo(mine, numeri, scoperte, 1);
    }

    return 0;
}

/* Mine nelle 8 celle intorno a [r][c] (la cella stessa non conta). */
int conta_mine_vicine(const char m[][COLONNE + 1], int r, int c)
{
    int dr;
    int dc;
    int rv;
    int cv;
    int n = 0;

    for (dr = -1; dr <= 1; dr++) {
        for (dc = -1; dc <= 1; dc++) {
            rv = r + dr;
            cv = c + dc;
            if (!(dr == 0 && dc == 0)
                && rv >= 0 && rv < RIGHE && cv >= 0 && cv < COLONNE
                && m[rv][cv] == MINA) {
                n++;
            }
        }
    }
    return n;
}

/* Stampa il campo. Con mostra_mine = 1 rivela anche mine e celle coperte. */
void stampa_campo(const char m[][COLONNE + 1], const int numeri[][COLONNE],
                  const int scoperte[][COLONNE], int mostra_mine)
{
    int r;
    int c;

    printf("\n    ");
    for (c = 0; c < COLONNE; c++) {
        printf("%d ", c + 1);
    }
    printf("\n");
    for (r = 0; r < RIGHE; r++) {
        printf("  %d ", r + 1);
        for (c = 0; c < COLONNE; c++) {
            if (m[r][c] == MINA && (mostra_mine || scoperte[r][c])) {
                printf("* ");
            } else if (scoperte[r][c] || mostra_mine) {
                if (numeri[r][c] == 0) {
                    printf("  ");
                } else {
                    printf("%d ", numeri[r][c]);
                }
            } else {
                printf("# ");
            }
        }
        printf("\n");
    }
    printf("\n");
}
