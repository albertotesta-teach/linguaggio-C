/*
 * 070-problema-registro-che-cresce.c
 *
 * Il registro di classe: studenti che arrivano e che si trasferiscono
 *
 * Il tabellone ha una riga per studente e una colonna per materia (ITA,
 * MAT, ING), in un solo blocco. Durante l'anno arrivano studenti nuovi e
 * altri si trasferiscono.
 *
 * Aggiungere uno studente significa aggiungere una RIGA: le righe sono
 * una dopo l'altra, quindi basta ingrandire il blocco e scrivere la riga
 * nuova in fondo (diverso dall'aggiunta di una colonna, che obbliga a
 * spostare tutti i voti: 02-realloc/070).
 *
 *     tmp = realloc(voti, (studenti + 1) * MATERIE * sizeof *voti);
 *
 * Togliere uno studente: le righe successive salgono di una posizione,
 * poi il blocco si riduce. Se resta vuoto si libera con free.
 *
 * I nomi stanno in un secondo blocco, un array di Nome che cresce e cala
 * insieme ai voti. Il registro parte vuoto (puntatori a NULL).
 *
 * Comandi:
 *     A nome ita mat ing    nuovo studente con i tre voti
 *     T nome                trasferimento: lo studente esce dal registro
 *     S                     stampa con le medie
 *     Q                     fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATERIE 3

typedef struct {
    char testo[20];
} Nome;

int aggiungi(Nome **nomi, double **voti, int studenti, const char *nome, const double v[]);
int togli(Nome **nomi, double **voti, int studenti, int posizione);
int cerca(const Nome nomi[], int studenti, const char *nome);
void stampa(const Nome nomi[], const double voti[], int studenti);

int main(void)
{
    Nome *nomi = NULL;
    double *voti = NULL;
    double v[MATERIE];
    char nome[20];
    char comando = ' ';
    int studenti = 0;
    int posizione;

    while (comando != 'Q') {
        printf("Comando (A, T, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'A') {
            if (scanf("%19s %lf %lf %lf", nome, &v[0], &v[1], &v[2]) != 4) {
                printf("  Dati non validi.\n");
            } else if (cerca(nomi, studenti, nome) != -1) {
                printf("  %s e' gia' nel registro.\n", nome);
            } else if (!aggiungi(&nomi, &voti, studenti, nome, v)) {
                printf("  Memoria insufficiente.\n");
            } else {
                studenti++;
                printf("  ingresso di %s: righe %d, %zu byte di voti\n", nome, studenti,
                       studenti * MATERIE * sizeof *voti);
            }
        } else if (comando == 'T') {
            if (scanf("%19s", nome) != 1) {
                printf("  Nome mancante.\n");
            } else {
                posizione = cerca(nomi, studenti, nome);
                if (posizione == -1) {
                    printf("  %s non e' nel registro.\n", nome);
                } else {
                    studenti = togli(&nomi, &voti, studenti, posizione);
                    printf("  uscita di %s: righe %d\n", nome, studenti);
                }
            }
        } else if (comando == 'S') {
            stampa(nomi, voti, studenti);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q') {
            scanf("%*[^\n]");          /* un comando per riga */
        }
    }

    free(nomi);
    free(voti);

    return 0;
}

/* Una riga in più in fondo ai due blocchi; 0 se una realloc fallisce. */
int aggiungi(Nome **nomi, double **voti, int studenti, const char *nome, const double v[])
{
    Nome *tmp_nomi = realloc(*nomi, (studenti + 1) * sizeof *tmp_nomi);
    double *tmp_voti;
    int ok = tmp_nomi != NULL;
    int c;

    if (ok) {
        *nomi = tmp_nomi;
        tmp_voti = realloc(*voti, (studenti + 1) * MATERIE * sizeof *tmp_voti);
        ok = tmp_voti != NULL;
        if (ok) {
            *voti = tmp_voti;
            strcpy((*nomi)[studenti].testo, nome);
            for (c = 0; c < MATERIE; c++) {
                (*voti)[studenti * MATERIE + c] = v[c];
            }
        }
    }
    return ok;
}

/*
 * Fa salire le righe dopo posizione e riduce i blocchi; restituisce il
 * nuovo numero di studenti. Se una riduzione fallisce il blocco resta
 * più grande del necessario, ma i dati sono corretti.
 */
int togli(Nome **nomi, double **voti, int studenti, int posizione)
{
    Nome *tmp_nomi;
    double *tmp_voti;
    int r;
    int c;

    for (r = posizione; r < studenti - 1; r++) {
        (*nomi)[r] = (*nomi)[r + 1];
        for (c = 0; c < MATERIE; c++) {
            (*voti)[r * MATERIE + c] = (*voti)[(r + 1) * MATERIE + c];
        }
    }
    studenti--;
    if (studenti == 0) {
        free(*nomi);
        free(*voti);
        *nomi = NULL;
        *voti = NULL;
    } else {
        tmp_nomi = realloc(*nomi, studenti * sizeof *tmp_nomi);
        tmp_voti = realloc(*voti, studenti * MATERIE * sizeof *tmp_voti);
        if (tmp_nomi != NULL) {
            *nomi = tmp_nomi;
        }
        if (tmp_voti != NULL) {
            *voti = tmp_voti;
        }
    }
    return studenti;
}

int cerca(const Nome nomi[], int studenti, const char *nome)
{
    int trovato = -1;
    int i;

    for (i = 0; i < studenti && trovato == -1; i++) {
        if (strcmp(nomi[i].testo, nome) == 0) {
            trovato = i;
        }
    }
    return trovato;
}

void stampa(const Nome nomi[], const double voti[], int studenti)
{
    double somma;
    int r;
    int c;

    if (studenti == 0) {
        printf("  registro vuoto\n");
    } else {
        printf("  %-10s  ITA  MAT  ING  media\n", "");
    }
    for (r = 0; r < studenti; r++) {
        somma = 0;
        printf("  %-10s", nomi[r].testo);
        for (c = 0; c < MATERIE; c++) {
            printf("%5.1f", voti[r * MATERIE + c]);
            somma = somma + voti[r * MATERIE + c];
        }
        printf("  %5.2f\n", somma / MATERIE);
    }
}
