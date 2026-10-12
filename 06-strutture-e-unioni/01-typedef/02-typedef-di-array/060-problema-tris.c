/*
 * 060-problema-tris.c
 *
 * Club dei giochi: una partita a tris tra due studenti
 *
 * La griglia del tris è una matrice 3 x 3 di caratteri: ' ' per una
 * casella libera, 'X' e 'O' per i due giocatori.
 *
 *     typedef char Griglia[3][3];
 *
 *     void stampa(const Griglia g);
 *     int ha_vinto(const Griglia g, char simbolo);
 *     int piena(const Griglia g);
 *
 * Con il nome Griglia le funzioni non devono ripetere [3][3] in ogni
 * prototipo: la dimensione è scritta una volta sola. Come per ogni
 * matrice passata a una funzione, arriva l'indirizzo della prima riga:
 * le tre funzioni ricevono const Griglia perché la leggono soltanto, le
 * mosse si scrivono nel main.
 *
 * I giocatori scrivono riga e colonna (da 1 a 3). Una mossa fuori dalla
 * griglia o su una casella occupata va ripetuta. La partita finisce con
 * un tris o con la griglia piena; una lettura non riuscita la interrompe.
 */

#include <stdio.h>

#define LATO 3

typedef char Griglia[LATO][LATO];

void stampa(const Griglia g);
int ha_vinto(const Griglia g, char simbolo);
int piena(const Griglia g);

int main(void)
{
    Griglia g = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char giocatore = 'X';
    int riga;
    int colonna;
    int finita = 0;

    stampa(g);
    while (!finita) {
        printf("Giocatore %c, riga e colonna: ", giocatore);
        if (scanf("%d %d", &riga, &colonna) != 2) {
            printf("  Partita interrotta.\n");
            finita = 1;
        } else if (riga < 1 || riga > LATO || colonna < 1 || colonna > LATO) {
            printf("  Fuori dalla griglia, ripetere.\n");
        } else if (g[riga - 1][colonna - 1] != ' ') {
            printf("  Casella occupata, ripetere.\n");
        } else {
            g[riga - 1][colonna - 1] = giocatore;
            stampa(g);
            if (ha_vinto(g, giocatore)) {
                printf("Tris! Vince il giocatore %c.\n", giocatore);
                finita = 1;
            } else if (piena(g)) {
                printf("Griglia piena: pareggio.\n");
                finita = 1;
            } else if (giocatore == 'X') {
                giocatore = 'O';
            } else {
                giocatore = 'X';
            }
        }
    }

    return 0;
}

void stampa(const Griglia g)
{
    int r;

    for (r = 0; r < LATO; r++) {
        printf("   %c | %c | %c\n", g[r][0], g[r][1], g[r][2]);
        if (r < LATO - 1) {
            printf("  ---+---+---\n");
        }
    }
}

/* Tre simboli uguali su una riga, una colonna o una diagonale. */
int ha_vinto(const Griglia g, char simbolo)
{
    int i;
    int vinto = 0;

    for (i = 0; i < LATO; i++) {
        if (g[i][0] == simbolo && g[i][1] == simbolo && g[i][2] == simbolo) {
            vinto = 1;
        }
        if (g[0][i] == simbolo && g[1][i] == simbolo && g[2][i] == simbolo) {
            vinto = 1;
        }
    }
    if (g[0][0] == simbolo && g[1][1] == simbolo && g[2][2] == simbolo) {
        vinto = 1;
    }
    if (g[0][2] == simbolo && g[1][1] == simbolo && g[2][0] == simbolo) {
        vinto = 1;
    }
    return vinto;
}

int piena(const Griglia g)
{
    int r;
    int c;
    int libere = 0;

    for (r = 0; r < LATO; r++) {
        for (c = 0; c < LATO; c++) {
            if (g[r][c] == ' ') {
                libere++;
            }
        }
    }
    return libere == 0;
}
