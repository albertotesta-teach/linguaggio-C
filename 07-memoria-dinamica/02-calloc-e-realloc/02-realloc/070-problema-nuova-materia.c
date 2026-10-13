/*
 * 070-problema-nuova-materia.c
 *
 * Il tabellone dei voti riceve una materia in più a metà anno
 *
 * Il tabellone ha una riga per studente e una colonna per materia, in un
 * solo blocco (elemento (r, c) in tab[r * colonne + c]). A metà anno si
 * aggiunge una materia (per esempio un corso di educazione civica):
 * serve una colonna in più.
 *
 * Aggiungere una colonna non è solo ingrandire il blocco: cambia la
 * lunghezza di ogni riga, quindi ogni voto deve spostarsi.
 *
 *     prima (2 x 3):   a0 a1 a2 | b0 b1 b2
 *     dopo  (2 x 4):   a0 a1 a2 __ | b0 b1 b2 __
 *
 *   1. tmp = realloc(tab, righe * (colonne + 1) * sizeof *tab);
 *   2. si spostano i voti partendo dall'ULTIMO: la posizione nuova di
 *      ogni voto è maggiore o uguale a quella vecchia, quindi procedendo
 *      all'indietro nessun voto viene sovrascritto prima di essere
 *      spostato;
 *   3. si scrivono i voti della nuova colonna.
 *
 * Il programma legge studenti, materie iniziali (nomi di 3 lettere) e
 * voti, poi i comandi:
 *     M nome voto1 voto2 ...   nuova materia con il voto di ogni studente
 *     S                        stampa il tabellone con le medie
 *     Q                        fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTI 10
#define MAX_MATERIE 8

int aggiungi_colonna(double **tab, int righe, int colonne);
void stampa(const double tab[], int righe, int colonne, char materie[][4]);

int main(void)
{
    double *tab = NULL;
    char materie[MAX_MATERIE][4];
    char nome[8];
    char comando = ' ';
    int righe;
    int colonne;
    int ok = 1;
    int r;
    int c;

    printf("Studenti e materie: ");
    if (scanf("%d %d", &righe, &colonne) != 2 || righe < 1 || righe > MAX_STUDENTI ||
        colonne < 1 || colonne > MAX_MATERIE) {
        printf("Dati non validi.\n");
        ok = 0;
    }
    if (ok) {
        tab = malloc(righe * colonne * sizeof *tab);
        ok = tab != NULL;
    }
    if (ok) {
        printf("Materie: ");
        for (c = 0; c < colonne && ok; c++) {
            ok = scanf("%7s", nome) == 1 && strlen(nome) == 3;
            if (ok) {
                strcpy(materie[c], nome);
            }
        }
        for (r = 0; r < righe && ok; r++) {
            printf("Voti dello studente %d: ", r + 1);
            for (c = 0; c < colonne && ok; c++) {
                ok = scanf("%lf", &tab[r * colonne + c]) == 1;
            }
        }
        if (!ok) {
            printf("Dati mancanti o non validi.\n");
        }
    }

    while (ok && comando != 'Q') {
        printf("Comando (M, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'M') {
            if (scanf("%7s", nome) != 1 || strlen(nome) != 3) {
                printf("  Nome della materia: 3 lettere.\n");
            } else if (colonne == MAX_MATERIE) {
                printf("  Al massimo %d materie.\n", MAX_MATERIE);
            } else if (!aggiungi_colonna(&tab, righe, colonne)) {
                printf("  Memoria insufficiente.\n");
            } else {
                colonne++;
                strcpy(materie[colonne - 1], nome);
                for (r = 0; r < righe; r++) {
                    if (scanf("%lf", &tab[r * colonne + colonne - 1]) != 1) {
                        tab[r * colonne + colonne - 1] = 0;
                    }
                }
                printf("  %s aggiunta: tabellone %d x %d\n", nome, righe, colonne);
            }
            scanf("%*[^\n]");
        } else if (comando == 'S') {
            stampa(tab, righe, colonne, materie);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
            scanf("%*[^\n]");
        }
    }
    free(tab);

    return 0;
}

/*
 * Ingrandisce il tabellone di una colonna e sposta i voti nelle nuove
 * posizioni. La nuova colonna resta da scrivere. 0 se realloc fallisce.
 */
int aggiungi_colonna(double **tab, int righe, int colonne)
{
    double *tmp = realloc(*tab, righe * (colonne + 1) * sizeof *tmp);
    int r;
    int c;

    if (tmp != NULL) {
        for (r = righe - 1; r >= 0; r--) {
            for (c = colonne - 1; c >= 0; c--) {
                tmp[r * (colonne + 1) + c] = tmp[r * colonne + c];
            }
        }
        *tab = tmp;
    }
    return tmp != NULL;
}

void stampa(const double tab[], int righe, int colonne, char materie[][4])
{
    double somma;
    int r;
    int c;

    printf("            ");
    for (c = 0; c < colonne; c++) {
        printf("%5s", materie[c]);
    }
    printf("  media\n");
    for (r = 0; r < righe; r++) {
        somma = 0;
        printf("studente %2d ", r + 1);
        for (c = 0; c < colonne; c++) {
            printf("%5.1f", tab[r * colonne + c]);
            somma = somma + tab[r * colonne + c];
        }
        printf("  %5.2f\n", somma / colonne);
    }
}
