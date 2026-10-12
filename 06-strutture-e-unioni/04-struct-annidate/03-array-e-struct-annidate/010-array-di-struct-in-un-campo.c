/*
 * 010-array-di-struct-in-un-campo.c
 *
 * Una struct che contiene un array di struct
 *
 * Una classe è un nome e un elenco di studenti. L'elenco è un array di
 * Studente dentro la struct Classe, con accanto il numero di elementi
 * usati:
 *
 *     typedef struct {
 *         char nome[20];
 *         double media;
 *     } Studente;
 *
 *     typedef struct {
 *         char nome[4];
 *         Studente alunni[MAX_ALUNNI];
 *         int n_alunni;
 *     } Classe;
 *
 *     c.alunni[i]            lo studente i della classe c
 *     c.alunni[i].media      la sua media
 *     p->alunni[i].nome      con un puntatore alla classe
 *
 * L'array e il suo contatore viaggiano insieme: una funzione che riceve
 * la Classe ha già tutto quello che le serve. La struct però è grande
 * (sizeof(Classe) comprende tutto l'array), quindi si passa per
 * indirizzo: Classe * per modificarla, const Classe * per leggerla.
 *
 * Esempio: la 1A del corso serale, con un massimo di 4 posti.
 */

#include <stdio.h>
#include <string.h>

#define MAX_ALUNNI 4

typedef struct {
    char nome[20];
    double media;
} Studente;

typedef struct {
    char nome[4];
    Studente alunni[MAX_ALUNNI];
    int n_alunni;
} Classe;

int aggiungi(Classe *c, const char *nome, double media);
double media_classe(const Classe *c);
void stampa_classe(const Classe *c);

int main(void)
{
    Classe serale = {"1A", {{"", 0}}, 0};
    const char *nomi[5] = {"Bassi Rita", "Corti Ugo", "Dini Ada", "Elia Gino", "Fumo Pia"};
    double medie[5] = {7.5, 6.0, 8.25, 5.5, 7.0};
    int i;

    for (i = 0; i < 5; i++) {
        if (!aggiungi(&serale, nomi[i], medie[i])) {
            printf("Classe piena: %s non inserito/a.\n", nomi[i]);
        }
    }
    stampa_classe(&serale);
    printf("sizeof(Studente) = %zu byte, sizeof(Classe) = %zu byte\n", sizeof(Studente),
           sizeof(Classe));

    return 0;
}

/* Aggiunge in coda; 0 se la classe è piena. */
int aggiungi(Classe *c, const char *nome, double media)
{
    int riuscito = c->n_alunni < MAX_ALUNNI;

    if (riuscito) {
        strcpy(c->alunni[c->n_alunni].nome, nome);
        c->alunni[c->n_alunni].media = media;
        c->n_alunni++;
    }
    return riuscito;
}

double media_classe(const Classe *c)
{
    double somma = 0;
    int i;

    for (i = 0; i < c->n_alunni; i++) {
        somma = somma + c->alunni[i].media;
    }
    return c->n_alunni > 0 ? somma / c->n_alunni : 0;
}

void stampa_classe(const Classe *c)
{
    int i;

    printf("Classe %s (%d/%d posti)\n", c->nome, c->n_alunni, MAX_ALUNNI);
    for (i = 0; i < c->n_alunni; i++) {
        printf("  %-12s %5.2f\n", c->alunni[i].nome, c->alunni[i].media);
    }
    printf("  media della classe %.2f\n", media_classe(c));
}
