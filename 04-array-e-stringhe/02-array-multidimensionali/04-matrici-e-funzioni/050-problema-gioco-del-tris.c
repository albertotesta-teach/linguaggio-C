/*
 * 050-problema-gioco-del-tris.c
 *
 * Il gioco del tris (filetto) per due giocatori
 *
 * La griglia 3 x 3 è una matrice di caratteri: ' ' casella vuota,
 * 'X' e 'O' le mosse dei due giocatori. I giocatori si alternano
 * inserendo riga e colonna (da 1 a 3). La partita termina quando un
 * giocatore allinea tre simboli (riga, colonna o diagonale) oppure quando
 * la griglia è piena (pareggio).
 *
 * Ogni compito è una funzione:
 *   svuota(griglia)               tutte le caselle a ' '
 *   stampa(griglia)               disegno della griglia
 *   mossa_valida(griglia, r, c)   1 se la casella esiste ed è vuota
 *   vincitore(griglia)            'X', 'O' oppure ' ' se nessuno ha vinto
 *   griglia_piena(griglia)        1 se non ci sono caselle vuote
 *
 * Il ciclo della partita non usa break: continua finché non c'è un
 * vincitore e la griglia non è piena.
 */

#include <stdio.h>

#define LATO 3
#define VUOTA ' '

void svuota(char g[][LATO]);
void stampa(const char g[][LATO]);
int mossa_valida(const char g[][LATO], int r, int c);
char vincitore(const char g[][LATO]);
int griglia_piena(const char g[][LATO]);

int main(void)
{
    char griglia[LATO][LATO];
    char giocatore = 'X';
    char vince = VUOTA;
    int riga;
    int colonna;

    svuota(griglia);
    printf("=== TRIS ===\n");
    stampa(griglia);

    while (vince == VUOTA && !griglia_piena(griglia)) {
        printf("Giocatore %c, riga e colonna (1-3): ", giocatore);
        scanf("%d %d", &riga, &colonna);

        if (mossa_valida(griglia, riga - 1, colonna - 1)) {
            griglia[riga - 1][colonna - 1] = giocatore;
            stampa(griglia);
            vince = vincitore(griglia);

            /* cambio di turno con il ternario */
            giocatore = (giocatore == 'X') ? 'O' : 'X';
        } else {
            printf("Mossa non valida: casella inesistente o occupata.\n");
        }
    }

    if (vince != VUOTA) {
        printf("Vince il giocatore %c!\n", vince);
    } else {
        printf("Pareggio.\n");
    }

    return 0;
}

void svuota(char g[][LATO])
{
    int r;
    int c;

    for (r = 0; r < LATO; r++) {
        for (c = 0; c < LATO; c++) {
            g[r][c] = VUOTA;
        }
    }
}

void stampa(const char g[][LATO])
{
    int r;
    int c;

    printf("\n     1   2   3\n");
    for (r = 0; r < LATO; r++) {
        printf("  %d ", r + 1);
        for (c = 0; c < LATO; c++) {
            printf(" %c ", g[r][c]);
            if (c < LATO - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (r < LATO - 1) {
            printf("    ---+---+---\n");
        }
    }
    printf("\n");
}

/* Prima si controllano gli indici, poi la casella: grazie al corto
 * circuito di &&, g[r][c] viene letta solo se gli indici sono validi. */
int mossa_valida(const char g[][LATO], int r, int c)
{
    return r >= 0 && r < LATO && c >= 0 && c < LATO && g[r][c] == VUOTA;
}

/* Controlla righe, colonne e diagonali. Restituisce il simbolo
 * vincente oppure VUOTA. Una sola return: il risultato si accumula
 * nella variabile esito e i controlli si fermano appena è trovato. */
char vincitore(const char g[][LATO])
{
    char esito = VUOTA;
    int i;

    for (i = 0; i < LATO && esito == VUOTA; i++) {
        if (g[i][0] != VUOTA && g[i][0] == g[i][1] && g[i][1] == g[i][2]) {
            esito = g[i][0];                    /* tris sulla riga i */
        } else if (g[0][i] != VUOTA && g[0][i] == g[1][i] && g[1][i] == g[2][i]) {
            esito = g[0][i];                    /* tris sulla colonna i */
        }
    }

    if (esito == VUOTA && g[1][1] != VUOTA) {
        if ((g[0][0] == g[1][1] && g[1][1] == g[2][2])
            || (g[0][2] == g[1][1] && g[1][1] == g[2][0])) {
            esito = g[1][1];
        }
    }

    return esito;
}

int griglia_piena(const char g[][LATO])
{
    int r;
    int c;
    int piena = 1;

    for (r = 0; r < LATO && piena; r++) {
        for (c = 0; c < LATO && piena; c++) {
            if (g[r][c] == VUOTA) {
                piena = 0;
            }
        }
    }
    return piena;
}
