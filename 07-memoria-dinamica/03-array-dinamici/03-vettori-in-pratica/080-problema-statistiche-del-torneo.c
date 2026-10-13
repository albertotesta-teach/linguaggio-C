/*
 * 080-problema-statistiche-del-torneo.c
 *
 * Il torneo di calcetto d'istituto: risultati, statistiche, classifica
 *
 * Al torneo si iscrivono le squadre delle classi; il numero di squadre
 * e il numero di partite di ciascuna non si conoscono in anticipo. Ogni
 * partita arriva come
 *
 *     4A 3B 2 1          4A - 3B finita 2 a 1
 *
 * e viene registrata DUE volte, una per ciascuna squadra, dal suo punto
 * di vista:
 *
 *     Torneo                         vettore di Squadra
 *       "4A"  risultati --->         (3B, 2, 1) (5C, 0, 0) ...
 *       "3B"  risultati --->         (4A, 1, 2) ...
 *       "5C"  risultati --->         (4A, 0, 0) ...
 *
 *     typedef struct {
 *         char avversario[8];
 *         int fatti;
 *         int subiti;
 *     } Risultato;
 *
 * Dal vettore dei risultati di una squadra si ricava tutto: partite,
 * vittorie, pareggi, sconfitte, gol fatti e subiti, punti (3 per la
 * vittoria, 1 per il pareggio).
 *
 * Per la classifica si ordina il vettore delle squadre con selection
 * sort: punti, a parità differenza reti, poi gol fatti. Scambiare due
 * Squadra scambia anche i puntatori ai loro vettori di risultati, ma i
 * vettori restano dove sono: nessun risultato si perde.
 *
 * Alla fine si stampa la classifica e la sequenza dei risultati della
 * prima squadra (V vittoria, N pareggio, P sconfitta).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char avversario[8];
    int fatti;
    int subiti;
} Risultato;

typedef struct {
    Risultato *dati;
    int n;
    int capacita;
} Risultati;

typedef struct {
    char nome[8];
    Risultati *risultati;
} Squadra;

typedef struct {
    Squadra *dati;
    int n;
    int capacita;
} Torneo;

Risultati *crea_risultati(int capacita);
int aggiungi(Risultati *r, Risultato x);
int lunghezza(const Risultati *r);
Risultato elemento(const Risultati *r, int i);
void distruggi_risultati(Risultati *r);
int punti(const Risultati *r);
int gol_fatti(const Risultati *r);
int gol_subiti(const Risultati *r);
int conta(const Risultati *r, int segno);

Torneo *crea_torneo(int capacita);
int cerca_squadra(const Torneo *t, const char *nome);
int aggiungi_squadra(Torneo *t, const char *nome);
int indice_squadra(Torneo *t, const char *nome);
int numero_squadre(const Torneo *t);
const char *nome_squadra(const Torneo *t, int i);
Risultati *risultati_squadra(const Torneo *t, int i);
int registra(Torneo *t, const char *casa, const char *ospite, int gol_casa, int gol_ospite);
void ordina_classifica(Torneo *t);
void distruggi_torneo(Torneo *t);

int segno(Risultato x);
int prima_in_classifica(const Risultati *a, const Risultati *b);

int main(void)
{
    Torneo *torneo = crea_torneo(2);
    Risultati *r;
    Risultato x;
    char casa[8];
    char ospite[8];
    int gol_casa;
    int gol_ospite;
    int letti;
    int finito = 0;
    int i;

    if (torneo == NULL) {
        printf("Memoria insufficiente.\n");
        finito = 1;
    } else {
        printf("Partite: casa ospite gol gol (FINE per terminare)\n");
    }
    while (!finito) {
        if (scanf("%7s", casa) != 1 || strcmp(casa, "FINE") == 0) {
            finito = 1;
        } else if ((letti = scanf("%7s %d %d", ospite, &gol_casa, &gol_ospite)) != 3 ||
                   gol_casa < 0 || gol_ospite < 0 || strcmp(casa, ospite) == 0) {
            printf("  partita non valida (%s)\n", casa);
            if (letti == 1 || letti == 2) {
                scanf("%*s");
            }
        } else if (!registra(torneo, casa, ospite, gol_casa, gol_ospite)) {
            printf("Memoria insufficiente.\n");
            finito = 1;
        }
    }
    if (torneo != NULL && numero_squadre(torneo) == 0) {
        printf("Nessuna partita registrata.\n");
    } else if (torneo != NULL) {
        ordina_classifica(torneo);
        printf("\n    %-6s %3s %3s %3s %3s %3s %3s %4s %3s\n", "Squadra", "G", "V", "N", "P",
               "GF", "GS", "DR", "Pt");
        for (i = 0; i < numero_squadre(torneo); i++) {
            r = risultati_squadra(torneo, i);
            printf("%2d. %-7s %3d %3d %3d %3d %3d %3d %+4d %3d\n", i + 1, nome_squadra(torneo, i),
                   lunghezza(r), conta(r, 1), conta(r, 0), conta(r, -1), gol_fatti(r),
                   gol_subiti(r), gol_fatti(r) - gol_subiti(r), punti(r));
        }

        r = risultati_squadra(torneo, 0);
        printf("\nIl cammino di %s:\n", nome_squadra(torneo, 0));
        for (i = 0; i < lunghezza(r); i++) {
            x = elemento(r, i);
            printf("  %c  %d-%d con %s\n", "PNV"[segno(x) + 1], x.fatti, x.subiti, x.avversario);
        }
    }
    distruggi_torneo(torneo);

    return 0;
}

Risultati *crea_risultati(int capacita)
{
    Risultati *r = malloc(sizeof *r);

    if (r != NULL) {
        r->dati = malloc(capacita * sizeof *r->dati);
        if (r->dati == NULL) {
            free(r);
            r = NULL;
        } else {
            r->n = 0;
            r->capacita = capacita;
        }
    }
    return r;
}

int aggiungi(Risultati *r, Risultato x)
{
    Risultato *tmp;
    int ok = 1;

    if (r->n == r->capacita) {
        tmp = realloc(r->dati, 2 * r->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            r->dati = tmp;
            r->capacita = 2 * r->capacita;
        }
    }
    if (ok) {
        r->dati[r->n] = x;
        r->n++;
    }
    return ok;
}

int lunghezza(const Risultati *r)
{
    return r->n;
}

Risultato elemento(const Risultati *r, int i)
{
    return r->dati[i];
}

void distruggi_risultati(Risultati *r)
{
    if (r != NULL) {
        free(r->dati);
        free(r);
    }
}

/* 1 vittoria, 0 pareggio, -1 sconfitta. */
int segno(Risultato x)
{
    int s = 0;

    if (x.fatti > x.subiti) {
        s = 1;
    } else if (x.fatti < x.subiti) {
        s = -1;
    }
    return s;
}

/* Quante partite con quel segno (1, 0 o -1). */
int conta(const Risultati *r, int s)
{
    int quante = 0;
    int i;

    for (i = 0; i < lunghezza(r); i++) {
        if (segno(elemento(r, i)) == s) {
            quante++;
        }
    }
    return quante;
}

int punti(const Risultati *r)
{
    return 3 * conta(r, 1) + conta(r, 0);
}

int gol_fatti(const Risultati *r)
{
    int totale = 0;
    int i;

    for (i = 0; i < lunghezza(r); i++) {
        totale += elemento(r, i).fatti;
    }
    return totale;
}

int gol_subiti(const Risultati *r)
{
    int totale = 0;
    int i;

    for (i = 0; i < lunghezza(r); i++) {
        totale += elemento(r, i).subiti;
    }
    return totale;
}

Torneo *crea_torneo(int capacita)
{
    Torneo *t = malloc(sizeof *t);

    if (t != NULL) {
        t->dati = malloc(capacita * sizeof *t->dati);
        if (t->dati == NULL) {
            free(t);
            t = NULL;
        } else {
            t->n = 0;
            t->capacita = capacita;
        }
    }
    return t;
}

int cerca_squadra(const Torneo *t, const char *nome)
{
    int trovato = -1;
    int i;

    for (i = 0; i < t->n && trovato == -1; i++) {
        if (strcmp(t->dati[i].nome, nome) == 0) {
            trovato = i;
        }
    }
    return trovato;
}

/* Nuova squadra con un vettore di risultati vuoto; indice o -1. */
int aggiungi_squadra(Torneo *t, const char *nome)
{
    Squadra *tmp;
    Risultati *risultati = crea_risultati(2);
    int indice = -1;

    if (risultati != NULL && t->n == t->capacita) {
        tmp = realloc(t->dati, 2 * t->capacita * sizeof *tmp);
        if (tmp != NULL) {
            t->dati = tmp;
            t->capacita = 2 * t->capacita;
        }
    }
    if (risultati != NULL && t->n < t->capacita) {
        strcpy(t->dati[t->n].nome, nome);
        t->dati[t->n].risultati = risultati;
        indice = t->n;
        t->n++;
    } else {
        distruggi_risultati(risultati);
    }
    return indice;
}

/* Indice della squadra, creandola se non c'è; -1 se manca memoria. */
int indice_squadra(Torneo *t, const char *nome)
{
    int indice = cerca_squadra(t, nome);

    if (indice == -1) {
        indice = aggiungi_squadra(t, nome);
    }
    return indice;
}

int numero_squadre(const Torneo *t)
{
    return t->n;
}

const char *nome_squadra(const Torneo *t, int i)
{
    return t->dati[i].nome;
}

Risultati *risultati_squadra(const Torneo *t, int i)
{
    return t->dati[i].risultati;
}

/* Registra la partita per entrambe le squadre; 0 se manca memoria. */
int registra(Torneo *t, const char *casa, const char *ospite, int gol_casa, int gol_ospite)
{
    Risultato x;
    int i = indice_squadra(t, casa);
    int j = indice_squadra(t, ospite);
    int ok = i != -1 && j != -1;

    if (ok) {
        strcpy(x.avversario, ospite);
        x.fatti = gol_casa;
        x.subiti = gol_ospite;
        ok = aggiungi(risultati_squadra(t, i), x);
    }
    if (ok) {
        strcpy(x.avversario, casa);
        x.fatti = gol_ospite;
        x.subiti = gol_casa;
        ok = aggiungi(risultati_squadra(t, j), x);
    }
    return ok;
}

/* 1 se a va prima di b: punti, differenza reti, gol fatti. */
int prima_in_classifica(const Risultati *a, const Risultati *b)
{
    int risposta;

    if (punti(a) != punti(b)) {
        risposta = punti(a) > punti(b);
    } else if (gol_fatti(a) - gol_subiti(a) != gol_fatti(b) - gol_subiti(b)) {
        risposta = gol_fatti(a) - gol_subiti(a) > gol_fatti(b) - gol_subiti(b);
    } else {
        risposta = gol_fatti(a) > gol_fatti(b);
    }
    return risposta;
}

/* Selection sort sulle squadre: si scambiano struct, non i risultati. */
void ordina_classifica(Torneo *t)
{
    Squadra temp;
    int migliore;
    int i;
    int j;

    for (i = 0; i < t->n - 1; i++) {
        migliore = i;
        for (j = i + 1; j < t->n; j++) {
            if (prima_in_classifica(t->dati[j].risultati, t->dati[migliore].risultati)) {
                migliore = j;
            }
        }
        if (migliore != i) {
            temp = t->dati[i];
            t->dati[i] = t->dati[migliore];
            t->dati[migliore] = temp;
        }
    }
}

/* Prima il vettore di risultati di ogni squadra, poi il resto. */
void distruggi_torneo(Torneo *t)
{
    int i;

    if (t != NULL) {
        for (i = 0; i < t->n; i++) {
            distruggi_risultati(t->dati[i].risultati);
        }
        free(t->dati);
        free(t);
    }
}
