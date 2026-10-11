/*
 * 060-problema-inverti-percorso.c
 *
 * Gita in bicicletta: il percorso di ritorno
 *
 * Una gita in bicicletta collega 5 località con 4 tratti. Per ogni tratto
 * sono noti la lunghezza (in decimi di km) e il dislivello (in metri,
 * positivo in salita). Il ritorno percorre gli stessi tratti in ordine
 * inverso e ogni salita diventa una discesa.
 *
 * Per preparare la tabella del ritorno il programma inverte gli array sul
 * posto con due puntatori: sinistra parte dal primo elemento, destra
 * dall'ultimo; si scambiano i valori e i puntatori si avvicinano finché
 * sinistra < destra. Poi un terzo scorrimento cambia il segno dei
 * dislivelli.
 *
 * Funzioni:
 *   inverti(inizio, fine)       inverte gli elementi in [inizio, fine)
 *   cambia_segno(inizio, fine)  cambia il segno degli elementi
 *   stampa_tappe(...)           tabella dei tratti
 */

#include <stdio.h>

#define TRATTI  4
#define LUNG    16

void inverti(int *inizio, int *fine);
void cambia_segno(int *inizio, int *fine);
void stampa_tappe(const char localita[][LUNG], const int distanze[],
                  const int dislivelli[], int andata);

int main(void)
{
    char localita[TRATTI + 1][LUNG] = {"Paese", "Mulino", "Cascina", "Belvedere", "Santuario"};
    int distanze[TRATTI] = {52, 38, 61, 27};
    int dislivelli[TRATTI] = {40, -15, 120, 85};

    printf("=== ANDATA ===\n");
    stampa_tappe(localita, distanze, dislivelli, 1);

    inverti(&distanze[0], &distanze[0] + TRATTI);
    inverti(&dislivelli[0], &dislivelli[0] + TRATTI);
    cambia_segno(&dislivelli[0], &dislivelli[0] + TRATTI);

    printf("\n=== RITORNO ===\n");
    stampa_tappe(localita, distanze, dislivelli, 0);

    return 0;
}

/* Inverte l'ordine degli elementi compresi tra inizio (incluso) e fine
 * (escluso), scambiandoli a coppie dagli estremi verso il centro. */
void inverti(int *inizio, int *fine)
{
    int *sinistra = inizio;
    int *destra = fine - 1;
    int scambio;

    while (sinistra < destra) {
        scambio = *sinistra;
        *sinistra = *destra;
        *destra = scambio;
        sinistra++;
        destra--;
    }
}

/* Cambia il segno di ogni elemento in [inizio, fine). */
void cambia_segno(int *inizio, int *fine)
{
    int *p;

    for (p = inizio; p < fine; p++) {
        *p = -*p;
    }
}

/* Stampa i tratti; andata = 1 legge le località in avanti, 0 all'indietro. */
void stampa_tappe(const char localita[][LUNG], const int distanze[],
                  const int dislivelli[], int andata)
{
    int t;
    int da;
    int a;
    int km = 0;
    int salita = 0;

    for (t = 0; t < TRATTI; t++) {
        if (andata) {
            da = t;
            a = t + 1;
        } else {
            da = TRATTI - t;
            a = TRATTI - t - 1;
        }
        printf("  %-10s -> %-10s %5.1f km  %+5d m\n",
               localita[da], localita[a], distanze[t] / 10.0, dislivelli[t]);
        km = km + distanze[t];
        if (dislivelli[t] > 0) {
            salita = salita + dislivelli[t];
        }
    }
    printf("  Totale %.1f km, %d m di salita\n", km / 10.0, salita);
}
