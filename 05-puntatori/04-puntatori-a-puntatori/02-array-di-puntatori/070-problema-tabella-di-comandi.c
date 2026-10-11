/*
 * 070-problema-tabella-di-comandi.c
 *
 * Robot del laboratorio: una tabella di puntatori a funzione
 *
 * Un piccolo robot si muove su una griglia. Riceve una sequenza di lettere
 * e ogni lettera è un comando:
 *     A  avanti di una casella      D  gira a destra
 *     I  indietro di una casella    S  gira a sinistra
 *
 * Le quattro funzioni hanno lo stesso prototipo e sono raccolte in un
 * ARRAY DI PUNTATORI A FUNZIONE. La posizione della lettera nella stringa
 * "AIDS" è l'indice della funzione da chiamare:
 *
 *     void (*comandi[4])(int *x, int *y, int *dir) = {avanti, indietro, destra, sinistra};
 *     comandi[k](&x, &y, &dir);
 *
 * Al posto di una catena di if per ogni lettera c'è una sola chiamata.
 * La direzione è 0 = nord, 1 = est, 2 = sud, 3 = ovest.
 *
 * Il programma legge una sequenza di comandi per riga; una riga vuota
 * termina.
 */

#include <stdio.h>
#include <string.h>

#define COMANDI 4
#define LUNG    80

void avanti(int *x, int *y, int *dir);
void indietro(int *x, int *y, int *dir);
void destra(int *x, int *y, int *dir);
void sinistra(int *x, int *y, int *dir);

int main(void)
{
    void (*comandi[COMANDI])(int *x, int *y, int *dir) = {avanti, indietro, destra, sinistra};
    const char lettere[] = "AIDS";
    const char *direzioni[4] = {"nord", "est", "sud", "ovest"};
    char sequenza[LUNG];
    const char *c;
    const char *trovata;
    char *a_capo;
    int x = 0;
    int y = 0;
    int dir = 0;
    int continua = 1;

    printf("Robot in (%d, %d) verso %s\n", x, y, direzioni[dir]);
    while (continua) {
        printf("Comandi (A I D S, riga vuota per finire): ");
        if (fgets(sequenza, LUNG, stdin) == NULL) {
            continua = 0;
        } else {
            a_capo = strchr(sequenza, '\n');
            if (a_capo != NULL) {
                *a_capo = '\0';
            }
            continua = sequenza[0] != '\0';
            for (c = sequenza; *c != '\0'; c++) {
                trovata = strchr(lettere, *c);
                if (trovata == NULL) {
                    printf("  '%c' ignorato\n", *c);
                } else {
                    comandi[trovata - lettere](&x, &y, &dir);
                }
            }
            if (continua) {
                printf("  Robot in (%d, %d) verso %s\n", x, y, direzioni[dir]);
            }
        }
    }

    return 0;
}

void avanti(int *x, int *y, int *dir)
{
    if (*dir == 0) {
        (*y)++;
    } else if (*dir == 1) {
        (*x)++;
    } else if (*dir == 2) {
        (*y)--;
    } else {
        (*x)--;
    }
}

void indietro(int *x, int *y, int *dir)
{
    if (*dir == 0) {
        (*y)--;
    } else if (*dir == 1) {
        (*x)--;
    } else if (*dir == 2) {
        (*y)++;
    } else {
        (*x)++;
    }
}

/* Le rotazioni non cambiano la posizione: x e y non si usano, ma il
 * prototipo deve essere uguale per tutte le funzioni della tabella. */
void destra(int *x, int *y, int *dir)
{
    (void) x;
    (void) y;
    *dir = (*dir + 1) % 4;
}

void sinistra(int *x, int *y, int *dir)
{
    (void) x;
    (void) y;
    *dir = (*dir + 3) % 4;
}
