/*
 * 050-problema-campionato-calcetto.c
 *
 * Torneo di calcetto d'istituto: risultati e classifica
 *
 * Ogni squadra ha nome, punti, partite giocate, gol fatti e subiti:
 *
 *     typedef struct {
 *         char nome[12];
 *         int giocate;
 *         int punti;
 *         int fatti;
 *         int subiti;
 *     } Squadra;
 *
 * Il programma legge i risultati delle partite nella forma
 *     casa gol_casa ospite gol_ospite
 * e una funzione aggiorna le due squadre coinvolte:
 *
 *     Squadra *cerca(Squadra s[], int n, const char *nome);
 *     void registra(Squadra *casa, int gol_casa, Squadra *ospite, int gol_ospite);
 *
 * Vittoria 3 punti, pareggio 1, sconfitta 0. Alla fine stampa la tabella
 * nell'ordine di iscrizione, la capolista e l'ultima in classifica (a
 * parità di punti conta la differenza reti), senza ordinare l'array:
 *
 *     int migliore(const Squadra *a, const Squadra *b);  1 se a precede b
 *
 * Una riga FINE termina l'inserimento.
 */

#include <stdio.h>
#include <string.h>

#define SQUADRE 5

typedef struct {
    char nome[12];
    int giocate;
    int punti;
    int fatti;
    int subiti;
} Squadra;

Squadra *cerca(Squadra s[], int n, const char *nome);
void registra(Squadra *casa, int gol_casa, Squadra *ospite, int gol_ospite);
int migliore(const Squadra *a, const Squadra *b);
void stampa(const Squadra *s);
void svuota_riga(void);

int main(void)
{
    Squadra torneo[SQUADRE] = {
        {"Fulmini", 0, 0, 0, 0},
        {"Tigri", 0, 0, 0, 0},
        {"Squali", 0, 0, 0, 0},
        {"Aquile", 0, 0, 0, 0},
        {"Lupi", 0, 0, 0, 0}
    };
    char nome_casa[12];
    char nome_ospite[12];
    int gol_casa;
    int gol_ospite;
    Squadra *casa;
    Squadra *ospite;
    int prima = 0;
    int ultima = 0;
    int i;
    int fine = 0;
    int letti;

    while (!fine) {
        printf("Risultato (casa gol ospite gol, FINE): ");
        if (scanf("%11s", nome_casa) != 1 || strcmp(nome_casa, "FINE") == 0) {
            fine = 1;                   /* FINE o input terminato */
        } else if ((letti = scanf("%d %11s %d", &gol_casa, nome_ospite, &gol_ospite)) != 3 ||
                   gol_casa < 0 || gol_ospite < 0) {
            if (letti != EOF) {
                svuota_riga();          /* scarta il resto della riga */
            }
            printf("  Risultato non valido.\n");
        } else {
            casa = cerca(torneo, SQUADRE, nome_casa);
            ospite = cerca(torneo, SQUADRE, nome_ospite);
            if (casa == NULL || ospite == NULL || casa == ospite) {
                printf("  Squadre non valide.\n");
            } else {
                registra(casa, gol_casa, ospite, gol_ospite);
            }
        }
    }

    printf("\n  Squadra      G  Pt   GF  GS   DR\n");
    for (i = 0; i < SQUADRE; i++) {
        stampa(&torneo[i]);
        if (migliore(&torneo[i], &torneo[prima])) {
            prima = i;
        }
        if (migliore(&torneo[ultima], &torneo[i])) {
            ultima = i;
        }
    }
    printf("\nCapolista: %s (punti %d)\n", torneo[prima].nome, torneo[prima].punti);
    printf("Ultima:    %s (punti %d)\n", torneo[ultima].nome, torneo[ultima].punti);

    return 0;
}

Squadra *cerca(Squadra s[], int n, const char *nome)
{
    Squadra *trovata = NULL;
    int i = 0;

    while (i < n && trovata == NULL) {
        if (strcmp(s[i].nome, nome) == 0) {
            trovata = &s[i];
        }
        i++;
    }
    return trovata;
}

/* Aggiorna giocate, gol e punti di entrambe le squadre. */
void registra(Squadra *casa, int gol_casa, Squadra *ospite, int gol_ospite)
{
    casa->giocate++;
    ospite->giocate++;
    casa->fatti = casa->fatti + gol_casa;
    casa->subiti = casa->subiti + gol_ospite;
    ospite->fatti = ospite->fatti + gol_ospite;
    ospite->subiti = ospite->subiti + gol_casa;
    if (gol_casa > gol_ospite) {
        casa->punti = casa->punti + 3;
    } else if (gol_casa < gol_ospite) {
        ospite->punti = ospite->punti + 3;
    } else {
        casa->punti++;
        ospite->punti++;
    }
}

/* 1 se a precede strettamente b: più punti, a parità miglior differenza reti. */
int migliore(const Squadra *a, const Squadra *b)
{
    return a->punti > b->punti ||
           (a->punti == b->punti && a->fatti - a->subiti > b->fatti - b->subiti);
}

void stampa(const Squadra *s)
{
    printf("  %-10s %3d %3d  %3d %3d  %+3d\n", s->nome, s->giocate, s->punti, s->fatti, s->subiti,
           s->fatti - s->subiti);
}

/* Scarta i caratteri rimasti sulla riga. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
