/*
 * 050-problema-tabella-dei-voti.c
 *
 * Il tabellone dello scrutinio: studenti per materie in un solo blocco
 *
 * Il tabellone ha una riga per studente e una colonna per materia. Il
 * numero di studenti e di materie si sceglie all'avvio, quindi non si
 * può usare double tab[RIGHE][COLONNE] con dimensioni fisse.
 *
 * Si alloca un unico blocco di righe x colonne double e si mettono le
 * righe una dopo l'altra (come il C fa per le matrici normali):
 *
 *     double *tab = crea_tabella(righe, colonne);
 *
 *     elemento (r, c)  ->  tab[r * colonne + c]
 *
 *     riga 0              riga 1              riga 2
 *     [0,0][0,1][0,2]     [1,0][1,1][1,2]     [2,0][2,1][2,2]
 *
 * La funzione indice(r, c, colonne) calcola la posizione, così la formula
 * si scrive una volta sola. Con una sola malloc basta una sola free.
 *
 * Il programma legge il numero di studenti e di materie (al massimo 6:
 * ITA, MAT, ING, INF, STO, SCI), poi i voti riga per riga, e stampa il
 * tabellone con la media di ogni studente e di ogni materia e lo
 * studente con la media più alta.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTI 30
#define MAX_MATERIE 6

double *crea_tabella(int righe, int colonne);
int indice(int r, int c, int colonne);
int leggi_tabella(double *tab, int righe, int colonne);
void stampa_tabella(const double *tab, int righe, int colonne);

int main(void)
{
    double *tab;
    int righe;
    int colonne;

    printf("Studenti e materie: ");
    if (scanf("%d %d", &righe, &colonne) != 2 || righe < 1 || righe > MAX_STUDENTI ||
        colonne < 1 || colonne > MAX_MATERIE) {
        printf("Dimensioni non valide (studenti 1-%d, materie 1-%d).\n", MAX_STUDENTI,
               MAX_MATERIE);
    } else {
        tab = crea_tabella(righe, colonne);
        if (tab == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            printf("Blocco di %d x %d = %d double (%zu byte)\n", righe, colonne,
                   righe * colonne, righe * colonne * sizeof *tab);
            if (leggi_tabella(tab, righe, colonne)) {
                stampa_tabella(tab, righe, colonne);
            } else {
                printf("Voti mancanti o non validi.\n");
            }
            free(tab);
        }
    }

    return 0;
}

double *crea_tabella(int righe, int colonne)
{
    return malloc(righe * colonne * sizeof(double));
}

int indice(int r, int c, int colonne)
{
    return r * colonne + c;
}

/* Legge i voti riga per riga; 0 se manca un voto o è fuori da 1-10. */
int leggi_tabella(double *tab, int righe, int colonne)
{
    int ok = 1;
    int r;
    int c;

    for (r = 0; r < righe && ok; r++) {
        printf("Voti dello studente %d: ", r + 1);
        for (c = 0; c < colonne && ok; c++) {
            ok = scanf("%lf", &tab[indice(r, c, colonne)]) == 1 &&
                 tab[indice(r, c, colonne)] >= 1 && tab[indice(r, c, colonne)] <= 10;
        }
    }
    return ok;
}

void stampa_tabella(const double *tab, int righe, int colonne)
{
    const char *materie[MAX_MATERIE] = {"ITA", "MAT", "ING", "INF", "STO", "SCI"};
    double somma;
    double media;
    double media_migliore = 0;
    int migliore = 0;
    int r;
    int c;

    printf("\n           ");
    for (c = 0; c < colonne; c++) {
        printf("%5s", materie[c]);
    }
    printf("  media\n");
    for (r = 0; r < righe; r++) {
        somma = 0;
        printf("studente %2d", r + 1);
        for (c = 0; c < colonne; c++) {
            printf("%5.1f", tab[indice(r, c, colonne)]);
            somma = somma + tab[indice(r, c, colonne)];
        }
        media = somma / colonne;
        printf("  %5.2f\n", media);
        if (media > media_migliore) {
            media_migliore = media;
            migliore = r;
        }
    }
    printf("media      ");
    for (c = 0; c < colonne; c++) {
        somma = 0;
        for (r = 0; r < righe; r++) {
            somma = somma + tab[indice(r, c, colonne)];
        }
        printf("%5.1f", somma / righe);
    }
    printf("\n\nMedia piu' alta: studente %d con %.2f\n", migliore + 1, media_migliore);
}
