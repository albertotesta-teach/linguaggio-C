/*
 * 050-problema-torneo-a-squadre.c
 *
 * Torneo di calcetto d'istituto: marcatori, rose e capocannoniere
 *
 * Il torneo ha un array di squadre e ogni squadra ha la sua rosa, un
 * array di giocatori:
 *
 *     typedef struct {
 *         char nome[12];
 *         int gol;
 *     } Giocatore;
 *
 *     typedef struct {
 *         char nome[12];
 *         Giocatore rosa[MAX_ROSA];
 *         int n_giocatori;
 *     } Squadra;
 *
 *     typedef struct {
 *         Squadra squadre[MAX_SQUADRE];
 *         int n_squadre;
 *     } Torneo;
 *
 * Le ricerche restituiscono un puntatore, un livello alla volta:
 *     Squadra *cerca_squadra(Torneo *t, const char *nome);
 *     Giocatore *cerca_giocatore(Squadra *s, const char *nome);
 * e il gol si registra con g->gol++ sul giocatore trovato.
 *
 * Comandi:
 *     G squadra giocatore    gol del giocatore
 *     R squadra              rosa con i gol e il totale della squadra
 *     C                      capocannoniere (tutti, se sono a pari gol)
 *     Q                      fine
 */

#include <stdio.h>
#include <string.h>

#define MAX_ROSA 5
#define MAX_SQUADRE 4

typedef struct {
    char nome[12];
    int gol;
} Giocatore;

typedef struct {
    char nome[12];
    Giocatore rosa[MAX_ROSA];
    int n_giocatori;
} Squadra;

typedef struct {
    Squadra squadre[MAX_SQUADRE];
    int n_squadre;
} Torneo;

Squadra *cerca_squadra(Torneo *t, const char *nome);
Giocatore *cerca_giocatore(Squadra *s, const char *nome);
int gol_squadra(const Squadra *s);
void stampa_rosa(const Squadra *s);
void capocannonieri(const Torneo *t);

int main(void)
{
    Torneo torneo = {
        {
            {"Fulmini", {{"Bassi", 2}, {"Conte", 0}, {"Dini", 1}, {"Elia", 0}}, 4},
            {"Tigri", {{"Fumo", 3}, {"Gallo", 1}, {"Leva", 0}, {"Mori", 0}}, 4},
            {"Squali", {{"Neri", 1}, {"Orsi", 2}, {"Pini", 0}, {"Rota", 0}}, 4},
            {"Aquile", {{"Sala", 0}, {"Testa", 2}, {"Ugo", 0}, {"Villa", 1}}, 4}
        },
        4
    };
    Squadra *squadra;
    Giocatore *giocatore;
    char comando = ' ';
    char nome_squadra[12];
    char nome_giocatore[12];

    while (comando != 'Q') {
        printf("Comando (G squadra giocatore, R squadra, C, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'G' || comando == 'R') {
            if (scanf("%11s", nome_squadra) != 1 ||
                (comando == 'G' && scanf("%11s", nome_giocatore) != 1)) {
                comando = 'Q';
            } else {
                squadra = cerca_squadra(&torneo, nome_squadra);
                if (squadra == NULL) {
                    printf("  Squadra %s inesistente.\n", nome_squadra);
                } else if (comando == 'R') {
                    stampa_rosa(squadra);
                } else {
                    giocatore = cerca_giocatore(squadra, nome_giocatore);
                    if (giocatore == NULL) {
                        printf("  %s non e' nella rosa della squadra %s.\n", nome_giocatore,
                               squadra->nome);
                    } else {
                        giocatore->gol++;
                        printf("  Gol di %s (%s): %d in tutto.\n", giocatore->nome, squadra->nome,
                               giocatore->gol);
                    }
                }
            }
        } else if (comando == 'C') {
            capocannonieri(&torneo);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}

Squadra *cerca_squadra(Torneo *t, const char *nome)
{
    Squadra *trovata = NULL;
    int k = 0;

    while (k < t->n_squadre && trovata == NULL) {
        if (strcmp(t->squadre[k].nome, nome) == 0) {
            trovata = &t->squadre[k];
        }
        k++;
    }
    return trovata;
}

Giocatore *cerca_giocatore(Squadra *s, const char *nome)
{
    Giocatore *trovato = NULL;
    int g = 0;

    while (g < s->n_giocatori && trovato == NULL) {
        if (strcmp(s->rosa[g].nome, nome) == 0) {
            trovato = &s->rosa[g];
        }
        g++;
    }
    return trovato;
}

int gol_squadra(const Squadra *s)
{
    int totale = 0;
    int g;

    for (g = 0; g < s->n_giocatori; g++) {
        totale = totale + s->rosa[g].gol;
    }
    return totale;
}

void stampa_rosa(const Squadra *s)
{
    int g;

    printf("  %s\n", s->nome);
    for (g = 0; g < s->n_giocatori; g++) {
        printf("    %-8s %d gol\n", s->rosa[g].nome, s->rosa[g].gol);
    }
    printf("  Totale squadra: %d gol\n", gol_squadra(s));
}

/* Prima trova il massimo, poi stampa tutti quelli che lo raggiungono. */
void capocannonieri(const Torneo *t)
{
    int massimo = 0;
    int k;
    int g;

    for (k = 0; k < t->n_squadre; k++) {
        for (g = 0; g < t->squadre[k].n_giocatori; g++) {
            if (t->squadre[k].rosa[g].gol > massimo) {
                massimo = t->squadre[k].rosa[g].gol;
            }
        }
    }
    printf("  Capocannoniere con %d gol:", massimo);
    for (k = 0; k < t->n_squadre; k++) {
        for (g = 0; g < t->squadre[k].n_giocatori; g++) {
            if (t->squadre[k].rosa[g].gol == massimo) {
                printf(" %s (%s)", t->squadre[k].rosa[g].nome, t->squadre[k].nome);
            }
        }
    }
    printf("\n");
}
