/*
 * 070-problema-gioco-tris.c
 *
 * Tris per la giornata delle STEM: griglia, turni e vincitore
 *
 * Ogni casella della griglia è vuota o contiene il segno di un
 * giocatore; anche il turno è un segno. Il risultato della partita è un
 * altro enum:
 *
 *     typedef enum { VUOTA, CROCE, CERCHIO } Casella;
 *     typedef enum { IN_CORSO, VINCE_CROCE, VINCE_CERCHIO,
 *                    PAREGGIO } Risultato;
 *
 *     typedef struct {
 *         Casella griglia[LATO][LATO];
 *         Casella turno;
 *         int mosse;
 *     } Partita;
 *
 *     int gioca(Partita *p, int riga, int colonna);
 *     Risultato controlla(const Partita *p);
 *
 * gioca mette il segno di turno nella casella, se è libera, e passa il
 * turno all'altro giocatore. controlla cerca tre segni uguali (non vuoti)
 * su una riga, una colonna o una diagonale; se non ce ne sono e la
 * griglia è piena la partita è pari.
 *
 * Il programma legge le mosse "riga colonna" (da 1 a 3) finché la
 * partita è in corso.
 */

#include <stdio.h>

#define LATO 3

typedef enum {
    VUOTA, CROCE, CERCHIO
} Casella;

typedef enum {
    IN_CORSO, VINCE_CROCE, VINCE_CERCHIO, PAREGGIO
} Risultato;

typedef struct {
    Casella griglia[LATO][LATO];
    Casella turno;
    int mosse;
} Partita;

int gioca(Partita *p, int riga, int colonna);
Risultato controlla(const Partita *p);
int tris(Casella a, Casella b, Casella c);
void stampa(const Partita *p);
char simbolo(Casella c);

int main(void)
{
    Partita partita = {{{VUOTA}}, CROCE, 0};
    Risultato risultato = IN_CORSO;
    int riga;
    int colonna;

    while (risultato == IN_CORSO) {
        printf("Mossa di %c (riga colonna): ", simbolo(partita.turno));
        if (scanf("%d %d", &riga, &colonna) != 2) {
            risultato = PAREGGIO;
            printf("Partita interrotta.\n");
        } else if (!gioca(&partita, riga, colonna)) {
            printf("  Casella non valida o gia' occupata.\n");
        } else {
            stampa(&partita);
            risultato = controlla(&partita);
            switch (risultato) {
            case VINCE_CROCE:
                printf("Vince X in %d mosse!\n", partita.mosse);
                break;
            case VINCE_CERCHIO:
                printf("Vince O in %d mosse!\n", partita.mosse);
                break;
            case PAREGGIO:
                printf("Pareggio.\n");
                break;
            case IN_CORSO:
                break;
            }
        }
    }

    return 0;
}

int gioca(Partita *p, int riga, int colonna)
{
    int valida = riga >= 1 && riga <= LATO && colonna >= 1 && colonna <= LATO &&
                 p->griglia[riga - 1][colonna - 1] == VUOTA;

    if (valida) {
        p->griglia[riga - 1][colonna - 1] = p->turno;
        p->turno = p->turno == CROCE ? CERCHIO : CROCE;
        p->mosse++;
    }
    return valida;
}

/* 1 se le tre caselle hanno lo stesso segno, non vuoto. */
int tris(Casella a, Casella b, Casella c)
{
    return a != VUOTA && a == b && b == c;
}

Risultato controlla(const Partita *p)
{
    Casella vincitore = VUOTA;
    Risultato risultato = IN_CORSO;
    int k;

    for (k = 0; k < LATO; k++) {
        if (tris(p->griglia[k][0], p->griglia[k][1], p->griglia[k][2])) {
            vincitore = p->griglia[k][0];
        }
        if (tris(p->griglia[0][k], p->griglia[1][k], p->griglia[2][k])) {
            vincitore = p->griglia[0][k];
        }
    }
    if (tris(p->griglia[0][0], p->griglia[1][1], p->griglia[2][2]) ||
        tris(p->griglia[0][2], p->griglia[1][1], p->griglia[2][0])) {
        vincitore = p->griglia[1][1];
    }

    if (vincitore == CROCE) {
        risultato = VINCE_CROCE;
    } else if (vincitore == CERCHIO) {
        risultato = VINCE_CERCHIO;
    } else if (p->mosse == LATO * LATO) {
        risultato = PAREGGIO;
    }
    return risultato;
}

void stampa(const Partita *p)
{
    int r;
    int c;

    for (r = 0; r < LATO; r++) {
        printf("   ");
        for (c = 0; c < LATO; c++) {
            printf(" %c", simbolo(p->griglia[r][c]));
        }
        printf("\n");
    }
}

char simbolo(Casella c)
{
    char s = '.';

    switch (c) {
    case VUOTA:
        s = '.';
        break;
    case CROCE:
        s = 'X';
        break;
    case CERCHIO:
        s = 'O';
        break;
    }
    return s;
}
