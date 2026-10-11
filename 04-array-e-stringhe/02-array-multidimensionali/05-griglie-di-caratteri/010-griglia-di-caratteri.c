/*
 * 010-griglia-di-caratteri.c
 *
 * Una mappa rappresentata con una matrice di caratteri
 *
 * Molti giochi e simulazioni usano una griglia in cui ogni cella è un
 * carattere che ne descrive il contenuto:
 *
 *     '.' prato    '^' albero    '~' acqua    '#' roccia    'C' casa
 *
 * Per inizializzare comodamente la griglia si scrive ogni riga come una
 * stringa tra virgolette. Una stringa termina con il carattere '\0', che
 * occupa una cella: per questo la seconda dimensione è COLONNE + 1.
 * I cicli però scorrono solo le COLONNE celle "vere".
 *
 *     char mappa[RIGHE][COLONNE + 1] = { "..^^~~", ... };
 *
 * Il programma stampa la mappa con le coordinate, conta quante celle ci
 * sono di ogni tipo, trova la casa e verifica se nella sua riga o nella
 * sua colonna c'è dell'acqua.
 */

#include <stdio.h>

#define RIGHE   6
#define COLONNE 12

void stampa_mappa(const char m[][COLONNE + 1]);
int conta_simbolo(const char m[][COLONNE + 1], char simbolo);

int main(void)
{
    char mappa[RIGHE][COLONNE + 1] = {
        "..^^^...~~..",
        ".^^^....~~..",
        "......C.~~~.",
        "##.......~~.",
        "###..^^...~.",
        "##..^^^^...."
    };
    int r;
    int c;
    int r_casa = -1;
    int c_casa = -1;
    int acqua_vicina = 0;

    printf("=== MAPPA DEL TERRITORIO ===\n");
    stampa_mappa(mappa);

    /* ── 1. Conteggio dei tipi di terreno ─────────────────────────── */
    printf("\nPrato  ('.'): %2d celle\n", conta_simbolo(mappa, '.'));
    printf("Bosco  ('^'): %2d celle\n", conta_simbolo(mappa, '^'));
    printf("Acqua  ('~'): %2d celle\n", conta_simbolo(mappa, '~'));
    printf("Roccia ('#'): %2d celle\n", conta_simbolo(mappa, '#'));
    printf("Totale      : %2d celle\n\n", RIGHE * COLONNE);

    /* ── 2. Posizione della casa (ricerca con flag) ───────────────── */
    for (r = 0; r < RIGHE && r_casa == -1; r++) {
        for (c = 0; c < COLONNE && r_casa == -1; c++) {
            if (mappa[r][c] == 'C') {
                r_casa = r;
                c_casa = c;
            }
        }
    }

    if (r_casa != -1) {
        printf("Casa in riga %d, colonna %d\n", r_casa, c_casa);

        /* ── 3. Acqua sulla stessa riga o colonna della casa ──────── */
        for (c = 0; c < COLONNE; c++) {
            if (mappa[r_casa][c] == '~') {
                acqua_vicina = 1;
            }
        }
        for (r = 0; r < RIGHE; r++) {
            if (mappa[r][c_casa] == '~') {
                acqua_vicina = 1;
            }
        }
        printf("Acqua raggiungibile in linea retta: %s\n", acqua_vicina ? "si'" : "no");
    } else {
        printf("Nessuna casa sulla mappa.\n");
    }

    return 0;
}

/* Stampa la griglia con il numero di colonna (ultima cifra) e di riga. */
void stampa_mappa(const char m[][COLONNE + 1])
{
    int r;
    int c;

    printf("   ");
    for (c = 0; c < COLONNE; c++) {
        printf("%d", c % 10);
    }
    printf("\n");
    for (r = 0; r < RIGHE; r++) {
        printf("%2d ", r);
        for (c = 0; c < COLONNE; c++) {
            printf("%c", m[r][c]);
        }
        printf("\n");
    }
}

int conta_simbolo(const char m[][COLONNE + 1], char simbolo)
{
    int r;
    int c;
    int conteggio = 0;

    for (r = 0; r < RIGHE; r++) {
        for (c = 0; c < COLONNE; c++) {
            if (m[r][c] == simbolo) {
                conteggio++;
            }
        }
    }
    return conteggio;
}

/*
 * ERRORE COMUNE: dichiarare la seconda dimensione uguale alla lunghezza
 * delle righe.
 *     char mappa[RIGHE][COLONNE] = { "..^^^...~~..", ... };
 * Ogni stringa ha COLONNE caratteri più il '\0' finale, che non trova
 * posto: a seconda del compilatore si ottiene un avviso o un errore.
 */
