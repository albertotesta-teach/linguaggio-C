/*
 * 070-problema-direzioni-robot.c
 *
 * Laboratorio di robotica: il robot sulla griglia del pavimento
 *
 * Il robot del laboratorio si muove su una griglia 8 x 8. Parte dalla
 * casella (0, 0), nell'angolo in basso a sinistra, rivolto verso nord.
 *
 *     typedef enum { NORD, EST, SUD, OVEST, NUM_DIREZIONI } Direzione;
 *
 *     typedef struct {
 *         int x;
 *         int y;
 *         Direzione verso;
 *     } Robot;
 *
 * Le direzioni sono in ordine orario, così girare è un calcolo:
 *     a destra     (verso + 1) % NUM_DIREZIONI
 *     a sinistra   (verso + NUM_DIREZIONI - 1) % NUM_DIREZIONI
 * Uno switch sulla direzione dice di quanto cambiano x e y per ogni
 * passo in avanti.
 *
 * Comandi:
 *     A n    avanti di n caselle; il robot si ferma contro il bordo
 *     S      gira a sinistra
 *     D      gira a destra
 *     P      posizione
 *     Q      fine
 */

#include <stdio.h>

#define LATO 8

typedef enum {
    NORD, EST, SUD, OVEST, NUM_DIREZIONI
} Direzione;

typedef struct {
    int x;
    int y;
    Direzione verso;
} Robot;

int avanza(Robot *r, int passi);
void gira(Robot *r, char lato);
const char *nome(Direzione d);

int main(void)
{
    Robot robot = {0, 0, NORD};
    char comando = ' ';
    int passi;
    int fatti;

    while (comando != 'Q') {
        printf("Comando (A n, S, D, P, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'A') {
            if (scanf("%d", &passi) != 1 || passi < 0) {
                comando = 'Q';
            } else {
                fatti = avanza(&robot, passi);
                if (fatti < passi) {
                    printf("  Bordo raggiunto dopo %d passi.\n", fatti);
                }
            }
        } else if (comando == 'S' || comando == 'D') {
            gira(&robot, comando);
        } else if (comando != 'P' && comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q') {
            printf("  Robot in (%d, %d) verso %s\n", robot.x, robot.y, nome(robot.verso));
        }
    }

    return 0;
}

/* Avanza al massimo di passi caselle; restituisce i passi fatti. */
int avanza(Robot *r, int passi)
{
    int dx = 0;
    int dy = 0;
    int fatti = 0;

    switch (r->verso) {
    case NORD:
        dy = 1;
        break;
    case EST:
        dx = 1;
        break;
    case SUD:
        dy = -1;
        break;
    case OVEST:
        dx = -1;
        break;
    case NUM_DIREZIONI:
        break;
    }
    while (fatti < passi && r->x + dx >= 0 && r->x + dx < LATO && r->y + dy >= 0 &&
           r->y + dy < LATO) {
        r->x = r->x + dx;
        r->y = r->y + dy;
        fatti++;
    }
    return fatti;
}

void gira(Robot *r, char lato)
{
    if (lato == 'D') {
        r->verso = (r->verso + 1) % NUM_DIREZIONI;
    } else {
        r->verso = (r->verso + NUM_DIREZIONI - 1) % NUM_DIREZIONI;
    }
}

const char *nome(Direzione d)
{
    const char *nomi[NUM_DIREZIONI] = {[NORD] = "nord", [EST] = "est", [SUD] = "sud",
                                       [OVEST] = "ovest"};

    return nomi[d];
}
