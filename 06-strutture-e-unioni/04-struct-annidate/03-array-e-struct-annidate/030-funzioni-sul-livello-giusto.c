/*
 * 030-funzioni-sul-livello-giusto.c
 *
 * Una funzione per ogni livello, chiamate in cascata
 *
 * La catena scuola.classi[c].alunni[s].voti[v] è lunga da scrivere e da
 * leggere. Si spezza con una funzione per ogni livello, che riceve solo
 * il suo pezzo:
 *
 *     double media_studente(const Studente *s);      voti di uno studente
 *     double media_classe(const Classe *c);          chiama media_studente
 *     const Classe *migliore(const Scuola *sc);      chiama media_classe
 *
 *     media_classe chiama  media_studente(&c->alunni[s])
 *     migliore chiama      media_classe(&sc->classi[k])
 *
 * Dentro ogni funzione c'è un solo livello di indici: media_studente
 * conosce i voti, media_classe gli studenti, migliore le classi. Nessuna
 * funzione deve sapere come sono fatti i livelli più interni.
 *
 * Esempio: il premio per la classe con la media più alta del biennio.
 */

#include <stdio.h>

#define MAX_VOTI 4
#define MAX_ALUNNI 3
#define MAX_CLASSI 3

typedef struct {
    char nome[16];
    int voti[MAX_VOTI];
    int n_voti;
} Studente;

typedef struct {
    char nome[4];
    Studente alunni[MAX_ALUNNI];
    int n_alunni;
} Classe;

typedef struct {
    Classe classi[MAX_CLASSI];
    int n_classi;
} Scuola;

double media_studente(const Studente *s);
double media_classe(const Classe *c);
const Classe *migliore(const Scuola *sc);

int main(void)
{
    Scuola biennio = {
        {
            {"1A", {{"Bassi Rita", {7, 8, 6, 9}, 4}, {"Corti Ugo", {6, 5, 7}, 3}}, 2},
            {"1B", {{"Dini Ada", {8, 9, 8}, 3}, {"Elia Gino", {6, 6}, 2},
                    {"Fumo Pia", {7, 7, 8, 7}, 4}}, 3},
            {"2A", {{"Gallo Ivo", {9, 8, 9, 7}, 4}, {"Leva Teo", {5, 6, 5}, 3}}, 2}
        },
        3
    };
    const Classe *prima;
    int c;
    int s;

    for (c = 0; c < biennio.n_classi; c++) {
        printf("%s  media %.2f\n", biennio.classi[c].nome, media_classe(&biennio.classi[c]));
        for (s = 0; s < biennio.classi[c].n_alunni; s++) {
            printf("    %-12s %.2f\n", biennio.classi[c].alunni[s].nome,
                   media_studente(&biennio.classi[c].alunni[s]));
        }
    }

    prima = migliore(&biennio);
    printf("\nPremio alla %s con media %.2f\n", prima->nome, media_classe(prima));

    return 0;
}

double media_studente(const Studente *s)
{
    int somma = 0;
    int v;

    for (v = 0; v < s->n_voti; v++) {
        somma = somma + s->voti[v];
    }
    return s->n_voti > 0 ? (double) somma / s->n_voti : 0;
}

/* Media delle medie degli studenti. */
double media_classe(const Classe *c)
{
    double somma = 0;
    int s;

    for (s = 0; s < c->n_alunni; s++) {
        somma = somma + media_studente(&c->alunni[s]);
    }
    return c->n_alunni > 0 ? somma / c->n_alunni : 0;
}

const Classe *migliore(const Scuola *sc)
{
    const Classe *prima = &sc->classi[0];
    int k;

    for (k = 1; k < sc->n_classi; k++) {
        if (media_classe(&sc->classi[k]) > media_classe(prima)) {
            prima = &sc->classi[k];
        }
    }
    return prima;
}
