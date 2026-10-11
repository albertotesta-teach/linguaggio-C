/*
 * 040-problema-robot-magazzino.c
 *
 * Un robot che raccoglie pacchi in un magazzino automatico
 *
 * La pianta del magazzino è una griglia di caratteri:
 *     '#' scaffale (non attraversabile)   '.' corridoio
 *     'P' pacco da raccogliere            'R' posizione del robot
 *
 * L'operatore guida il robot con un comando alla volta:
 *     N (su)  S (giù)  E (destra)  O (sinistra)  Q (fine)
 * Il robot si sposta solo se la cella di arrivo è dentro la mappa e non è
 * uno scaffale. Entrando in una cella con un pacco lo raccoglie.
 * La sessione termina con Q oppure quando tutti i pacchi sono raccolti.
 *
 * Lo spostamento si calcola con due variabili dr, dc (variazione di riga
 * e di colonna) scelte da uno switch sul comando: la verifica della cella
 * di arrivo è la stessa per tutte le direzioni.
 */

#include <stdio.h>

#define RIGHE   6
#define COLONNE 10
#define MURO    '#'
#define PACCO   'P'
#define ROBOT   'R'
#define LIBERO  '.'

void stampa_mappa(const char m[][COLONNE + 1]);
int conta_pacchi(const char m[][COLONNE + 1]);

int main(void)
{
    char mappa[RIGHE][COLONNE + 1] = {
        "R...#....P",
        ".##.#.##..",
        ".#P...#...",
        ".#.##.#.##",
        "...P..#...",
        "####......"
    };
    int r_robot = 0;
    int c_robot = 0;
    int r_nuova;
    int c_nuova;
    int dr;
    int dc;
    char comando;
    int raccolti = 0;
    int mosse = 0;
    int pacchi_rimasti;

    pacchi_rimasti = conta_pacchi(mappa);
    printf("=== MAGAZZINO AUTOMATICO ===\n");
    printf("Pacchi da raccogliere: %d\n", pacchi_rimasti);
    stampa_mappa(mappa);

    printf("Comando (N S E O, Q = fine): ");
    scanf(" %c", &comando);

    while (comando != 'Q' && comando != 'q' && pacchi_rimasti > 0) {
        dr = 0;
        dc = 0;
        switch (comando) {
            case 'N':
            case 'n':
                dr = -1;
                break;
            case 'S':
            case 's':
                dr = 1;
                break;
            case 'E':
            case 'e':
                dc = 1;
                break;
            case 'O':
            case 'o':
                dc = -1;
                break;
            default:
                printf("  Comando sconosciuto.\n");
                break;
        }

        if (dr != 0 || dc != 0) {
            r_nuova = r_robot + dr;
            c_nuova = c_robot + dc;

            if (r_nuova < 0 || r_nuova >= RIGHE || c_nuova < 0 || c_nuova >= COLONNE) {
                printf("  Bordo del magazzino: movimento annullato.\n");
            } else if (mappa[r_nuova][c_nuova] == MURO) {
                printf("  Scaffale: movimento annullato.\n");
            } else {
                if (mappa[r_nuova][c_nuova] == PACCO) {
                    raccolti++;
                    pacchi_rimasti--;
                    printf("  Pacco raccolto! (%d)\n", raccolti);
                }
                mappa[r_robot][c_robot] = LIBERO;
                mappa[r_nuova][c_nuova] = ROBOT;
                r_robot = r_nuova;
                c_robot = c_nuova;
                mosse++;
            }
        }

        if (pacchi_rimasti > 0) {
            printf("Comando (N S E O, Q = fine): ");
            scanf(" %c", &comando);
        }
    }

    stampa_mappa(mappa);
    printf("Mosse eseguite: %d, pacchi raccolti: %d, rimasti: %d\n",
           mosse, raccolti, pacchi_rimasti);
    if (pacchi_rimasti == 0) {
        printf("Missione completata!\n");
    }

    return 0;
}

void stampa_mappa(const char m[][COLONNE + 1])
{
    int r;
    int c;

    printf("\n");
    for (r = 0; r < RIGHE; r++) {
        printf("  ");
        for (c = 0; c < COLONNE; c++) {
            printf("%c", m[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

int conta_pacchi(const char m[][COLONNE + 1])
{
    int r;
    int c;
    int pacchi = 0;

    for (r = 0; r < RIGHE; r++) {
        for (c = 0; c < COLONNE; c++) {
            if (m[r][c] == PACCO) {
                pacchi++;
            }
        }
    }
    return pacchi;
}
