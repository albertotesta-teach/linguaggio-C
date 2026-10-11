/*
 * 060-problema-gioco-della-vita.c
 *
 * Il "gioco della vita" di John Conway (1970)
 *
 * È una simulazione su una griglia: ogni cella è viva ('#') o morta ('.').
 * A ogni generazione tutte le celle cambiano INSIEME secondo queste regole,
 * basate sul numero di vicine vive (nelle 8 direzioni):
 *
 *   - una cella viva con 2 o 3 vicine vive sopravvive;
 *   - una cella viva con meno di 2 vicine muore (isolamento) e con più
 *     di 3 muore (sovraffollamento);
 *   - una cella morta con esattamente 3 vicine vive nasce.
 *
 * Da regole così semplici nascono comportamenti complessi. Il programma
 * parte da due figure classiche:
 *   - un "lampeggiatore" (tre celle in riga che ruotano di 90 gradi a ogni
 *     generazione);
 *   - un "aliante" (glider), che si sposta in diagonale di una cella ogni
 *     4 generazioni.
 *
 * Tecniche: conteggio dei vicini con gli spostamenti dr, dc (020) e
 * aggiornamento con due griglie (030).
 */

#include <stdio.h>

#define RIGHE   8
#define COLONNE 12
#define GENERAZIONI 4
#define VIVA  '#'
#define MORTA '.'

int vicine_vive(const char g[][COLONNE + 1], int r, int c);
void prossima_generazione(char attuale[][COLONNE + 1], char nuova[][COLONNE + 1]);
void stampa(const char g[][COLONNE + 1], int generazione);
int conta_vive(const char g[][COLONNE + 1]);

int main(void)
{
    char mondo[RIGHE][COLONNE + 1] = {
        ".#..........",
        "..#.........",
        "###.........",
        "............",
        "............",
        "........###.",
        "............",
        "............"
    };
    char appoggio[RIGHE][COLONNE + 1];
    int generazione;

    printf("=== GIOCO DELLA VITA ===\n");
    stampa(mondo, 0);
    for (generazione = 1; generazione <= GENERAZIONI; generazione++) {
        prossima_generazione(mondo, appoggio);
        stampa(mondo, generazione);
    }
    printf("Dopo %d generazioni l'aliante si e' spostato di una cella\n", GENERAZIONI);
    printf("in basso a destra; il lampeggiatore e' tornato orizzontale.\n");

    return 0;
}

/* Numero di celle vive tra le 8 vicine di [r][c]. */
int vicine_vive(const char g[][COLONNE + 1], int r, int c)
{
    int dr;
    int dc;
    int rv;
    int cv;
    int vive = 0;

    for (dr = -1; dr <= 1; dr++) {
        for (dc = -1; dc <= 1; dc++) {
            rv = r + dr;
            cv = c + dc;
            if (!(dr == 0 && dc == 0)
                && rv >= 0 && rv < RIGHE && cv >= 0 && cv < COLONNE
                && g[rv][cv] == VIVA) {
                vive++;
            }
        }
    }
    return vive;
}

/* Calcola la generazione successiva in "nuova" leggendo da "attuale",
 * poi la copia in "attuale". Il terminatore '\0' di ogni riga viene
 * scritto anche in nuova. */
void prossima_generazione(char attuale[][COLONNE + 1], char nuova[][COLONNE + 1])
{
    int r;
    int c;
    int n;

    for (r = 0; r < RIGHE; r++) {
        for (c = 0; c < COLONNE; c++) {
            n = vicine_vive(attuale, r, c);
            if (attuale[r][c] == VIVA) {
                if (n == 2 || n == 3) {
                    nuova[r][c] = VIVA;
                } else {
                    nuova[r][c] = MORTA;
                }
            } else {
                if (n == 3) {
                    nuova[r][c] = VIVA;
                } else {
                    nuova[r][c] = MORTA;
                }
            }
        }
        nuova[r][COLONNE] = '\0';
    }

    for (r = 0; r < RIGHE; r++) {
        for (c = 0; c < COLONNE; c++) {
            attuale[r][c] = nuova[r][c];
        }
    }
}

void stampa(const char g[][COLONNE + 1], int generazione)
{
    int r;
    int c;

    printf("\nGenerazione %d (celle vive: %d)\n", generazione, conta_vive(g));
    for (r = 0; r < RIGHE; r++) {
        printf("  ");
        for (c = 0; c < COLONNE; c++) {
            printf("%c", g[r][c]);
        }
        printf("\n");
    }
}

int conta_vive(const char g[][COLONNE + 1])
{
    int r;
    int c;
    int vive = 0;

    for (r = 0; r < RIGHE; r++) {
        for (c = 0; c < COLONNE; c++) {
            if (g[r][c] == VIVA) {
                vive++;
            }
        }
    }
    return vive;
}
