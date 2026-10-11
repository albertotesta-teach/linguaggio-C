/*
 * 080-problema-mappa-del-tesoro.c
 *
 * Seguire le istruzioni di una mappa del tesoro
 *
 * Su un'isola rappresentata da una griglia ('~' mare, '.' spiaggia,
 * '^' bosco, '#' rocce) un pirata ha lasciato le istruzioni per trovare il
 * tesoro, sotto forma di due array paralleli:
 *
 *     direzioni[] = { 'E', 'S', 'E', 'N' }     verso del tratto
 *     passi[]     = {  5,   4,   1,   1  }     lunghezza del tratto
 *
 * Il programma parte dalla posizione 'X' (il relitto), percorre i tratti
 * uno alla volta tracciando il cammino con 'o' e:
 *   - si ferma se il percorso finirebbe in mare o sulle rocce, o uscirebbe
 *     dalla mappa (le istruzioni sono sbagliate);
 *   - al termine verifica se la cella raggiunta contiene il tesoro '$'.
 *
 * Ogni tratto è percorso un passo alla volta: un ciclo esterno sui tratti,
 * uno interno sui passi, entrambi fermati da un flag in caso di errore.
 */

#include <stdio.h>

#define RIGHE   8
#define COLONNE 14
#define TRATTI  4

#define MARE   '~'
#define ROCCIA '#'
#define TESORO '$'
#define TRACCIA 'o'

void stampa_mappa(const char m[][COLONNE + 1]);

int main(void)
{
    char isola[RIGHE][COLONNE + 1] = {
        "~~~~~~~~~~~~~~",
        "~~X......~~~~~",
        "~~...^^^..~~~~",
        "~~..^^#^^..~~~",
        "~~~..^^^$..~~~",
        "~~~.......~~~~",
        "~~~~~...~~~~~~",
        "~~~~~~~~~~~~~~"
    };
    char direzioni[TRATTI] = {'E', 'S', 'E', 'N'};
    int passi[TRATTI]      = { 5,   4,   1,   1 };

    int r = 0;
    int c = 0;
    int trovato_partenza = 0;
    int t;
    int p;
    int dr;
    int dc;
    int bloccato = 0;

    /* ── 1. Posizione di partenza ─────────────────────────────────── */
    for (r = 0; r < RIGHE && !trovato_partenza; r++) {
        for (c = 0; c < COLONNE && !trovato_partenza; c++) {
            if (isola[r][c] == 'X') {
                trovato_partenza = 1;
            }
        }
    }
    /* i for hanno incrementato r e c dopo il ritrovamento: si torna indietro */
    r = r - 1;
    c = c - 1;

    printf("=== ISOLA DEL TESORO ===\n");
    stampa_mappa(isola);
    printf("Partenza dal relitto in riga %d, colonna %d\n\n", r, c);

    /* ── 2. Percorso: un tratto alla volta, un passo alla volta ────── */
    for (t = 0; t < TRATTI && !bloccato; t++) {
        dr = 0;
        dc = 0;
        switch (direzioni[t]) {
            case 'N':
                dr = -1;
                break;
            case 'S':
                dr = 1;
                break;
            case 'E':
                dc = 1;
                break;
            default:            /* 'O' */
                dc = -1;
                break;
        }
        printf("Tratto %d: %d %s verso %c\n", t + 1, passi[t],
               passi[t] == 1 ? "passo" : "passi", direzioni[t]);

        for (p = 0; p < passi[t] && !bloccato; p++) {
            if (r + dr < 0 || r + dr >= RIGHE || c + dc < 0 || c + dc >= COLONNE) {
                bloccato = 1;
                printf("  Fuori dalla mappa!\n");
            } else if (isola[r + dr][c + dc] == MARE || isola[r + dr][c + dc] == ROCCIA) {
                bloccato = 1;
                printf("  Ostacolo in riga %d, colonna %d: istruzioni sbagliate.\n",
                       r + dr, c + dc);
            } else {
                if (isola[r][c] != 'X') {
                    isola[r][c] = TRACCIA;      /* lascia la traccia */
                }
                r = r + dr;
                c = c + dc;
            }
        }
    }

    /* ── 3. Esito ─────────────────────────────────────────────────── */
    printf("\nPosizione finale: riga %d, colonna %d\n", r, c);
    if (!bloccato && isola[r][c] == TESORO) {
        printf("TESORO TROVATO!\n");
    } else if (!bloccato) {
        printf("Qui non c'e' nessun tesoro.\n");
    }
    stampa_mappa(isola);

    return 0;
}

void stampa_mappa(const char m[][COLONNE + 1])
{
    int r;
    int c;

    for (r = 0; r < RIGHE; r++) {
        printf("  ");
        for (c = 0; c < COLONNE; c++) {
            printf("%c", m[r][c]);
        }
        printf("\n");
    }
}
