/*
 * 080-problema-torneo.c
 *
 * Il torneo di calcetto d'istituto: squadre, risultati e classifica
 *
 * Il numero di squadre cambia ogni anno, quindi il torneo contiene un
 * puntatore a un array di Squadra allocato con la dimensione giusta:
 *
 *     typedef struct {
 *         char nome[24];
 *         int n_squadre;
 *         Squadra *squadre;
 *     } Torneo;
 *
 *     Torneo *crea_torneo(const char *nome, int n_squadre);
 *     void distruggi_torneo(Torneo *t);
 *
 * Una partita aggiorna le due squadre: 3 punti a chi vince, 1 a testa
 * per il pareggio, gol fatti e subiti.
 *
 * Per la classifica non si riordina l'array delle squadre: la funzione
 * classifica alloca un array temporaneo di indici, lo ordina per punti
 * (a parità di punti per differenza reti) con la selection sort, stampa
 * le squadre in quell'ordine e lo libera prima di terminare. Così le
 * squadre restano nell'ordine di iscrizione e la memoria temporanea non
 * esce dalla funzione.
 *
 * Il programma legge il numero di squadre e i loro nomi, poi i comandi:
 *     P squadra1 gol1 squadra2 gol2   risultato di una partita
 *     C                               classifica
 *     Q                               fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SQUADRE 16

typedef struct {
    char nome[16];
    int punti;
    int giocate;
    int fatti;
    int subiti;
} Squadra;

typedef struct {
    char nome[24];
    int n_squadre;
    Squadra *squadre;
} Torneo;

Torneo *crea_torneo(const char *nome, int n_squadre);
void distruggi_torneo(Torneo *t);
int cerca_squadra(const Torneo *t, const char *nome);
void registra(Squadra *s, int fatti, int subiti);
int precede(const Squadra *a, const Squadra *b);
void classifica(const Torneo *t);

int main(void)
{
    Torneo *t = NULL;
    char nome1[16];
    char nome2[16];
    char comando = ' ';
    int n = 0;
    int i;
    int gol1;
    int gol2;
    int a;
    int b;

    printf("Numero di squadre (da 2 a %d): ", MAX_SQUADRE);
    if (scanf("%d", &n) != 1 || n < 2 || n > MAX_SQUADRE) {
        printf("Numero non valido.\n");
    } else {
        t = crea_torneo("Calcetto d'istituto", n);
    }
    if (t == NULL) {
        comando = 'Q';
    }
    for (i = 0; t != NULL && i < n; i++) {
        printf("Squadra %d: ", i + 1);
        if (scanf("%15s", t->squadre[i].nome) != 1 ||
            cerca_squadra(t, t->squadre[i].nome) != i) {
            printf("  nome mancante o ripetuto: uso S%d\n", i + 1);
            snprintf(t->squadre[i].nome, sizeof t->squadre[i].nome, "S%d", i + 1);
        }
    }

    while (comando != 'Q') {
        printf("Comando (P, C, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'P') {
            if (scanf("%15s %d %15s %d", nome1, &gol1, nome2, &gol2) != 4 || gol1 < 0 ||
                gol2 < 0) {
                printf("  Risultato non valido.\n");
            } else {
                a = cerca_squadra(t, nome1);
                b = cerca_squadra(t, nome2);
                if (a == -1 || b == -1 || a == b) {
                    printf("  Squadre non valide.\n");
                } else {
                    registra(&t->squadre[a], gol1, gol2);
                    registra(&t->squadre[b], gol2, gol1);
                    printf("  %s %d - %d %s registrata\n", nome1, gol1, gol2, nome2);
                }
            }
            scanf("%*[^\n]");
        } else if (comando == 'C') {
            classifica(t);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
            scanf("%*[^\n]");
        }
    }

    if (t == NULL && n >= 2 && n <= MAX_SQUADRE) {
        printf("Memoria insufficiente.\n");
    }
    distruggi_torneo(t);

    return 0;
}

Torneo *crea_torneo(const char *nome, int n_squadre)
{
    Torneo *t = malloc(sizeof *t);
    int i;

    if (t != NULL) {
        t->squadre = malloc(n_squadre * sizeof *t->squadre);
        if (t->squadre == NULL) {
            free(t);
            t = NULL;
        } else {
            strcpy(t->nome, nome);
            t->n_squadre = n_squadre;
            for (i = 0; i < n_squadre; i++) {
                t->squadre[i].nome[0] = '\0';
                t->squadre[i].punti = 0;
                t->squadre[i].giocate = 0;
                t->squadre[i].fatti = 0;
                t->squadre[i].subiti = 0;
            }
        }
    }
    return t;
}

void distruggi_torneo(Torneo *t)
{
    if (t != NULL) {
        free(t->squadre);
        free(t);
    }
}

/* Indice della prima squadra con quel nome, -1 se non c'è. */
int cerca_squadra(const Torneo *t, const char *nome)
{
    int trovata = -1;
    int i;

    for (i = 0; i < t->n_squadre && trovata == -1; i++) {
        if (strcmp(t->squadre[i].nome, nome) == 0) {
            trovata = i;
        }
    }
    return trovata;
}

void registra(Squadra *s, int fatti, int subiti)
{
    s->giocate++;
    s->fatti = s->fatti + fatti;
    s->subiti = s->subiti + subiti;
    if (fatti > subiti) {
        s->punti = s->punti + 3;
    } else if (fatti == subiti) {
        s->punti = s->punti + 1;
    }
}

/* 1 se a va prima di b: più punti, a parità migliore differenza reti. */
int precede(const Squadra *a, const Squadra *b)
{
    return a->punti > b->punti ||
           (a->punti == b->punti && a->fatti - a->subiti > b->fatti - b->subiti);
}

void classifica(const Torneo *t)
{
    int *ordine = malloc(t->n_squadre * sizeof *ordine);
    int i;
    int j;
    int scelta;
    int scambio;
    const Squadra *s;

    if (ordine == NULL) {
        printf("  Memoria insufficiente per la classifica.\n");
    } else {
        for (i = 0; i < t->n_squadre; i++) {
            ordine[i] = i;
        }
        for (i = 0; i < t->n_squadre - 1; i++) {
            scelta = i;
            for (j = i + 1; j < t->n_squadre; j++) {
                if (precede(&t->squadre[ordine[j]], &t->squadre[ordine[scelta]])) {
                    scelta = j;
                }
            }
            scambio = ordine[i];
            ordine[i] = ordine[scelta];
            ordine[scelta] = scambio;
        }

        printf("  %s\n", t->nome);
        printf("     squadra       G  GF  GS  DR  punti\n");
        for (i = 0; i < t->n_squadre; i++) {
            s = &t->squadre[ordine[i]];
            printf("  %2d %-12s %2d %3d %3d %+3d  %4d\n", i + 1, s->nome, s->giocate,
                   s->fatti, s->subiti, s->fatti - s->subiti, s->punti);
        }
        free(ordine);
    }
}
