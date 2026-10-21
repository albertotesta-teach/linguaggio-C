/*
 * 070-problema-scambio-righe.c
 *
 * Torneo di calcetto: aggiornare la classifica scambiando puntatori a righe
 *
 * Nel torneo di calcetto d'istituto ogni squadra ha una riga della matrice
 * risultati[SQUADRE][3] con vittorie, pareggi e sconfitte. La classifica
 * è un array di puntatori alle righe: int *classifica[SQUADRE].
 *
 * Dopo ogni partita si aggiorna la riga della squadra e la si fa salire in
 * classifica finché ha più punti della squadra che la precede: ogni
 * sorpasso scambia due PUNTATORI, le righe della matrice non si spostano.
 *
 * Dal puntatore a una riga si ricava il numero della squadra:
 *     (classifica[k] - risultati[0]) / 3
 *
 * Il programma legge "squadra esito" (esito V, P o S); 0 termina.
 */

#include <stdio.h>

#define SQUADRE 5

int punti(const int *riga);
void stampa(int *classifica[], const int *inizio, const char *nomi[]);
void svuota_riga(void);

int main(void)
{
    const char *nomi[SQUADRE] = {"Fulmini", "Tigri", "Squali", "Aquile", "Lupi"};
    int risultati[SQUADRE][3] = {
        {3, 1, 0},
        {2, 2, 0},
        {2, 0, 2},
        {1, 2, 1},
        {0, 1, 3}
    };
    int *classifica[SQUADRE];
    int *temp;
    int squadra = 1;
    char esito;
    int letti;
    int k;

    for (k = 0; k < SQUADRE; k++) {
        classifica[k] = risultati[k];
    }
    stampa(classifica, risultati[0], nomi);

    while (squadra != 0) {
        printf("Squadra (1-%d) ed esito V/P/S, 0 per finire: ", SQUADRE);
        letti = scanf("%d", &squadra);
        if (letti == EOF) {
            squadra = 0;                /* input terminato: come 0 */
        } else if (letti == 0) {
            svuota_riga();              /* non è un numero */
            squadra = -1;               /* dati non validi */
        }
        esito = ' ';
        if (squadra >= 1 && squadra <= SQUADRE) {
            if (scanf(" %c", &esito) != 1) {
                esito = ' ';            /* esito mancante */
            }
        }
        if (squadra >= 1 && squadra <= SQUADRE &&
            (esito == 'V' || esito == 'P' || esito == 'S')) {
            /* aggiorna la riga della squadra: 0 vittorie, 1 pareggi, 2 sconfitte */
            if (esito == 'V') {
                risultati[squadra - 1][0]++;
            } else if (esito == 'P') {
                risultati[squadra - 1][1]++;
            } else {
                risultati[squadra - 1][2]++;
            }
            /* posizione attuale della squadra in classifica */
            k = 0;
            while (classifica[k] != risultati[squadra - 1]) {
                k++;
            }
            /* sale finché supera chi la precede */
            while (k > 0 && punti(classifica[k]) > punti(classifica[k - 1])) {
                temp = classifica[k];
                classifica[k] = classifica[k - 1];
                classifica[k - 1] = temp;
                k--;
            }
            stampa(classifica, risultati[0], nomi);
        } else if (squadra != 0) {
            if (letti == 1) {
                svuota_riga();          /* scarta il resto della riga */
            }
            printf("  Dati non validi.\n");
        }
    }

    return 0;
}

/* 3 punti per vittoria, 1 per pareggio. */
int punti(const int *riga)
{
    return 3 * riga[0] + riga[1];
}

void stampa(int *classifica[], const int *inizio, const char *nomi[])
{
    int k;

    printf("  Pos Squadra   V P S  Punti\n");
    for (k = 0; k < SQUADRE; k++) {
        printf("  %2d. %-8s %2d %d %d  %3d\n", k + 1, nomi[(classifica[k] - inizio) / 3],
               classifica[k][0], classifica[k][1], classifica[k][2], punti(classifica[k]));
    }
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
