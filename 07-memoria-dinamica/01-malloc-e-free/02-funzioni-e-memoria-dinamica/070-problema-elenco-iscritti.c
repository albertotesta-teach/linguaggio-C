/*
 * 070-problema-elenco-iscritti.c
 *
 * Corsi pomeridiani: un elenco di iscritti per ogni corso
 *
 * La scuola organizza due corsi pomeridiani, robotica e teatro. I posti
 * di ciascun corso si decidono all'avvio. Ogni corso è un Elenco:
 *
 *     typedef struct {
 *         char corso[16];
 *         int capienza;
 *         int n;
 *         Iscritto *iscritti;        blocco di capienza Iscritto
 *     } Elenco;
 *
 * Tutto il lavoro sullo heap sta in due funzioni:
 *
 *     Elenco *crea_elenco(const char *corso, int capienza);
 *     void distruggi_elenco(Elenco *e);
 *
 * Le altre funzioni (iscrivi, ritira, stampa) ricevono un Elenco * e non
 * chiamano mai malloc o free. iscrivi restituisce un Esito: iscritto,
 * corso pieno o già iscritto. ritira toglie uno studente e sposta
 * indietro di un posto quelli che lo seguono, così l'ordine di
 * iscrizione resta lo stesso.
 *
 * Comandi:
 *     I corso nome classe    iscrive
 *     R corso nome           ritira
 *     E                      elenco dei due corsi
 *     Q                      fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CORSI 2
#define MAX_POSTI 30

typedef struct {
    char nome[20];
    char classe[4];
} Iscritto;

typedef struct {
    char corso[16];
    int capienza;
    int n;
    Iscritto *iscritti;
} Elenco;

typedef enum {
    ISCRITTO, CORSO_PIENO, GIA_ISCRITTO
} Esito;

Elenco *crea_elenco(const char *corso, int capienza);
void distruggi_elenco(Elenco *e);
int cerca(const Elenco *e, const char *nome);
Esito iscrivi(Elenco *e, const char *nome, const char *classe);
int ritira(Elenco *e, const char *nome);
void stampa(const Elenco *e);
Elenco *trova_corso(Elenco *corsi[], const char *corso);

int main(void)
{
    const char *nomi_corsi[CORSI] = {"robotica", "teatro"};
    Elenco *corsi[CORSI];
    Elenco *e;
    int posti[CORSI];
    char corso[16];
    char nome[20];
    char classe[8];
    char comando = ' ';
    int pronti = 1;
    int k;

    printf("Posti di robotica e di teatro: ");
    if (scanf("%d %d", &posti[0], &posti[1]) != 2 || posti[0] < 1 || posti[1] < 1 ||
        posti[0] > MAX_POSTI || posti[1] > MAX_POSTI) {
        printf("Numero di posti non valido (da 1 a %d).\n", MAX_POSTI);
        comando = 'Q';
    }
    for (k = 0; k < CORSI; k++) {
        corsi[k] = NULL;
        if (comando != 'Q') {
            corsi[k] = crea_elenco(nomi_corsi[k], posti[k]);
            pronti = pronti && corsi[k] != NULL;
        }
    }
    if (comando != 'Q' && !pronti) {
        printf("Memoria insufficiente.\n");
        comando = 'Q';
    }

    while (comando != 'Q') {
        printf("Comando (I, R, E, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'I') {
            if (scanf("%15s %19s %7s", corso, nome, classe) != 3 || strlen(classe) > 3) {
                printf("  Dati non validi.\n");
            } else {
                e = trova_corso(corsi, corso);
                if (e == NULL) {
                    printf("  Corso sconosciuto: %s\n", corso);
                } else {
                    switch (iscrivi(e, nome, classe)) {
                    case ISCRITTO:
                        printf("  Iscrizione di %s a %s (%d/%d)\n", nome, e->corso, e->n,
                               e->capienza);
                        break;
                    case CORSO_PIENO:
                        printf("  Il corso di %s e' pieno.\n", e->corso);
                        break;
                    case GIA_ISCRITTO:
                        printf("  %s e' gia' tra gli iscritti a %s.\n", nome, e->corso);
                        break;
                    }
                }
            }
        } else if (comando == 'R') {
            if (scanf("%15s %19s", corso, nome) != 2) {
                printf("  Dati non validi.\n");
            } else {
                e = trova_corso(corsi, corso);
                if (e == NULL) {
                    printf("  Corso sconosciuto: %s\n", corso);
                } else if (ritira(e, nome)) {
                    printf("  Ritiro di %s da %s.\n", nome, e->corso);
                } else {
                    printf("  %s non e' tra gli iscritti a %s.\n", nome, e->corso);
                }
            }
        } else if (comando == 'E') {
            for (k = 0; k < CORSI; k++) {
                stampa(corsi[k]);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q' && comando != 'E') {
            scanf("%*[^\n]");
        }
    }

    for (k = 0; k < CORSI; k++) {
        distruggi_elenco(corsi[k]);
    }

    return 0;
}

Elenco *crea_elenco(const char *corso, int capienza)
{
    Elenco *e = malloc(sizeof *e);

    if (e != NULL) {
        e->iscritti = malloc(capienza * sizeof *e->iscritti);
        if (e->iscritti == NULL) {
            free(e);
            e = NULL;
        } else {
            strcpy(e->corso, corso);
            e->capienza = capienza;
            e->n = 0;
        }
    }
    return e;
}

void distruggi_elenco(Elenco *e)
{
    if (e != NULL) {
        free(e->iscritti);
        free(e);
    }
}

/* Posizione dello studente nell'elenco, -1 se non c'è. */
int cerca(const Elenco *e, const char *nome)
{
    int posizione = -1;
    int i;

    for (i = 0; i < e->n && posizione == -1; i++) {
        if (strcmp(e->iscritti[i].nome, nome) == 0) {
            posizione = i;
        }
    }
    return posizione;
}

Esito iscrivi(Elenco *e, const char *nome, const char *classe)
{
    Esito esito = ISCRITTO;

    if (cerca(e, nome) != -1) {
        esito = GIA_ISCRITTO;
    } else if (e->n == e->capienza) {
        esito = CORSO_PIENO;
    } else {
        strcpy(e->iscritti[e->n].nome, nome);
        strcpy(e->iscritti[e->n].classe, classe);
        e->n++;
    }
    return esito;
}

/* Toglie lo studente e sposta indietro i successivi; 0 se non c'è. */
int ritira(Elenco *e, const char *nome)
{
    int posizione = cerca(e, nome);
    int i;

    if (posizione != -1) {
        for (i = posizione; i < e->n - 1; i++) {
            e->iscritti[i] = e->iscritti[i + 1];
        }
        e->n--;
    }
    return posizione != -1;
}

void stampa(const Elenco *e)
{
    int i;

    printf("  %s: iscritti %d su %d posti\n", e->corso, e->n, e->capienza);
    for (i = 0; i < e->n; i++) {
        printf("    %d. %-12s %s\n", i + 1, e->iscritti[i].nome, e->iscritti[i].classe);
    }
}

Elenco *trova_corso(Elenco *corsi[], const char *corso)
{
    Elenco *trovato = NULL;
    int k;

    for (k = 0; k < CORSI; k++) {
        if (strcmp(corsi[k]->corso, corso) == 0) {
            trovato = corsi[k];
        }
    }
    return trovato;
}
