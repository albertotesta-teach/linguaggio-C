/*
 * 050-problema-orario-dei-docenti.c
 *
 * L'orario dei docenti: trovare le ore libere per una riunione
 *
 * Il coordinatore deve fissare una riunione del consiglio di classe e
 * cerca le ore in cui TUTTI i docenti sono liberi. Le lezioni arrivano
 * una alla volta nella forma
 *
 *     Rossi lun 3        Rossi ha lezione lunedì alla terza ora
 *
 * Ogni docente ha un proprio vettore dinamico di ore occupate, che
 * cresce man mano; ogni ora è un codice giorno * 10 + ora:
 *
 *     Docenti
 *       "Rossi"   ore ---> 13 14 22 35             (lun 3, lun 4, ...)
 *       "Bianchi" ore ---> 11 13 21 22 23 41 52
 *
 * Una stessa lezione inserita due volte viene rifiutata (contiene).
 *
 * Un'ora è libera per tutti se nessun docente la contiene:
 *
 *     per ogni giorno da 1 a 5, per ogni ora da 1 a 6:
 *         libera = 1
 *         per ogni docente d (finché libera):
 *             se contiene(ore di d, codice): libera = 0
 *
 * Il programma legge le lezioni fino a FINE, stampa il carico di ogni
 * docente e le ore libere comuni giorno per giorno.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GIORNI 5
#define ORE 6

typedef struct {
    int *dati;
    int n;
    int capacita;
} Ore;

typedef struct {
    char nome[20];
    Ore *ore;
} Docente;

typedef struct {
    Docente *dati;
    int n;
    int capacita;
} Consiglio;

Ore *crea_ore(int capacita);
int aggiungi(Ore *v, int codice);
int lunghezza(const Ore *v);
int capacita(const Ore *v);
int contiene(const Ore *v, int codice);
void distruggi_ore(Ore *v);

Consiglio *crea_consiglio(int capacita);
int cerca_docente(const Consiglio *c, const char *nome);
int aggiungi_docente(Consiglio *c, const char *nome);
int numero_docenti(const Consiglio *c);
const char *nome_docente(const Consiglio *c, int i);
Ore *ore_docente(const Consiglio *c, int i);
void distruggi_consiglio(Consiglio *c);

int numero_giorno(const char *giorno);
int libera_per_tutti(const Consiglio *c, int codice);

int main(void)
{
    const char *nomi_giorni[] = {"", "lun", "mar", "mer", "gio", "ven"};
    Consiglio *consiglio = crea_consiglio(2);
    char nome[20];
    char giorno[8];
    int ora;
    int g;
    int indice;
    int libere;
    int libere_giorno;
    int letti;
    int finito = 0;
    int i;

    if (consiglio == NULL) {
        printf("Memoria insufficiente.\n");
        finito = 1;
    } else {
        printf("Lezioni: docente giorno ora (FINE per terminare)\n");
    }
    while (!finito) {
        if (scanf("%19s", nome) != 1 || strcmp(nome, "FINE") == 0) {
            finito = 1;
        } else if ((letti = scanf("%7s %d", giorno, &ora)) != 2 || numero_giorno(giorno) == 0 ||
                   ora < 1 || ora > ORE) {
            printf("  lezione non valida per %s\n", nome);
            if (letti == 1) {
                scanf("%*s");
            }
        } else {
            indice = cerca_docente(consiglio, nome);
            if (indice == -1) {
                indice = aggiungi_docente(consiglio, nome);
            }
            g = numero_giorno(giorno);
            if (indice == -1) {
                printf("Memoria insufficiente.\n");
                finito = 1;
            } else if (contiene(ore_docente(consiglio, indice), g * 10 + ora)) {
                printf("  %s %s %d gia' inserita\n", nome, giorno, ora);
            } else if (!aggiungi(ore_docente(consiglio, indice), g * 10 + ora)) {
                printf("Memoria insufficiente.\n");
                finito = 1;
            }
        }
    }
    if (consiglio != NULL && numero_docenti(consiglio) > 0) {
        printf("\nCarico dei docenti:\n");
        for (i = 0; i < numero_docenti(consiglio); i++) {
            printf("  %-10s ore %2d  (capacita del vettore %d)\n", nome_docente(consiglio, i),
                   lunghezza(ore_docente(consiglio, i)), capacita(ore_docente(consiglio, i)));
        }
        printf("\nOre libere per tutti:\n");
        libere = 0;
        for (g = 1; g <= GIORNI; g++) {
            printf("  %s:", nomi_giorni[g]);
            libere_giorno = 0;
            for (ora = 1; ora <= ORE; ora++) {
                if (libera_per_tutti(consiglio, g * 10 + ora)) {
                    printf(" %d", ora);
                    libere_giorno++;
                }
            }
            if (libere_giorno == 0) {
                printf(" nessuna");
            }
            printf("\n");
            libere += libere_giorno;
        }
        printf("Totale ore libere comuni: %d su %d\n", libere, GIORNI * ORE);
    } else if (consiglio != NULL) {
        printf("Nessuna lezione inserita.\n");
    }
    distruggi_consiglio(consiglio);

    return 0;
}

Ore *crea_ore(int capacita)
{
    Ore *v = malloc(sizeof *v);

    if (v != NULL) {
        v->dati = malloc(capacita * sizeof *v->dati);
        if (v->dati == NULL) {
            free(v);
            v = NULL;
        } else {
            v->n = 0;
            v->capacita = capacita;
        }
    }
    return v;
}

int aggiungi(Ore *v, int codice)
{
    int *tmp;
    int ok = 1;

    if (v->n == v->capacita) {
        tmp = realloc(v->dati, 2 * v->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            v->dati = tmp;
            v->capacita = 2 * v->capacita;
        }
    }
    if (ok) {
        v->dati[v->n] = codice;
        v->n++;
    }
    return ok;
}

int lunghezza(const Ore *v)
{
    return v->n;
}

int capacita(const Ore *v)
{
    return v->capacita;
}

int contiene(const Ore *v, int codice)
{
    int trovato = 0;
    int i;

    for (i = 0; i < v->n && !trovato; i++) {
        trovato = v->dati[i] == codice;
    }
    return trovato;
}

void distruggi_ore(Ore *v)
{
    if (v != NULL) {
        free(v->dati);
        free(v);
    }
}

Consiglio *crea_consiglio(int capacita)
{
    Consiglio *c = malloc(sizeof *c);

    if (c != NULL) {
        c->dati = malloc(capacita * sizeof *c->dati);
        if (c->dati == NULL) {
            free(c);
            c = NULL;
        } else {
            c->n = 0;
            c->capacita = capacita;
        }
    }
    return c;
}

int cerca_docente(const Consiglio *c, const char *nome)
{
    int trovato = -1;
    int i;

    for (i = 0; i < c->n && trovato == -1; i++) {
        if (strcmp(c->dati[i].nome, nome) == 0) {
            trovato = i;
        }
    }
    return trovato;
}

/* Nuovo docente con un vettore di ore vuoto; indice o -1. */
int aggiungi_docente(Consiglio *c, const char *nome)
{
    Docente *tmp;
    Ore *ore = crea_ore(4);
    int indice = -1;

    if (ore != NULL && c->n == c->capacita) {
        tmp = realloc(c->dati, 2 * c->capacita * sizeof *tmp);
        if (tmp != NULL) {
            c->dati = tmp;
            c->capacita = 2 * c->capacita;
        }
    }
    if (ore != NULL && c->n < c->capacita) {
        strcpy(c->dati[c->n].nome, nome);
        c->dati[c->n].ore = ore;
        indice = c->n;
        c->n++;
    } else {
        distruggi_ore(ore);
    }
    return indice;
}

int numero_docenti(const Consiglio *c)
{
    return c->n;
}

const char *nome_docente(const Consiglio *c, int i)
{
    return c->dati[i].nome;
}

Ore *ore_docente(const Consiglio *c, int i)
{
    return c->dati[i].ore;
}

void distruggi_consiglio(Consiglio *c)
{
    int i;

    if (c != NULL) {
        for (i = 0; i < c->n; i++) {
            distruggi_ore(c->dati[i].ore);
        }
        free(c->dati);
        free(c);
    }
}

/* Da "lun".."ven" a 1..5; 0 se il giorno non è valido. */
int numero_giorno(const char *giorno)
{
    const char *nomi[] = {"lun", "mar", "mer", "gio", "ven"};
    int numero = 0;
    int i;

    for (i = 0; i < GIORNI && numero == 0; i++) {
        if (strcmp(giorno, nomi[i]) == 0) {
            numero = i + 1;
        }
    }
    return numero;
}

int libera_per_tutti(const Consiglio *c, int codice)
{
    int libera = 1;
    int i;

    for (i = 0; i < numero_docenti(c) && libera; i++) {
        if (contiene(ore_docente(c, i), codice)) {
            libera = 0;
        }
    }
    return libera;
}
