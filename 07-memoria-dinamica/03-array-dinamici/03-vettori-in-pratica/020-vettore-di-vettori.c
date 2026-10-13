/*
 * 020-vettore-di-vettori.c
 *
 * Un vettore di righe, ognuna con il proprio vettore di lunghezza diversa
 *
 * Una scuola registra i voti di una verifica comune a più classi. Le
 * classi non hanno lo stesso numero di studenti e i voti arrivano
 * mescolati: una matrice classi x voti sprecherebbe spazio e servirebbe
 * conoscere in anticipo la classe più numerosa.
 *
 * Si usano due livelli di vettori dinamici:
 *
 *     Scuola                        vettore di Riga, cresce a raddoppio
 *       dati[0]  "3A"  voti --->    Voti: 7 8 6           (3 su cap. 4)
 *       dati[1]  "3B"  voti --->    Voti: 5 9             (2 su cap. 2)
 *       dati[2]  "3C"  voti --->    Voti: 6 6 7 8 4       (5 su cap. 8)
 *
 * Ogni riga ha il suo vettore di voti, con la sua lunghezza e la sua
 * capacità: una classe può crescere senza toccare le altre.
 *
 * La distruzione va fatta dal basso verso l'alto: prima il vettore di
 * voti di ogni riga, poi il blocco delle righe, poi la Scuola. Se si
 * liberasse subito il blocco delle righe, i puntatori ai vettori di voti
 * andrebbero persi (memory leak).
 *
 * Il programma legge coppie "classe voto" fino a FINE e stampa, per ogni
 * classe, quanti voti, la capacità del suo vettore, la media e i voti.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *dati;
    int n;
    int capacita;
} Voti;

typedef struct {
    char classe[8];
    Voti *voti;
} Riga;

typedef struct {
    Riga *dati;
    int n;
    int capacita;
} Scuola;

Voti *crea_voti(int capacita);
int aggiungi(Voti *v, int voto);
int lunghezza(const Voti *v);
int capacita(const Voti *v);
int elemento(const Voti *v, int i);
void distruggi_voti(Voti *v);

Scuola *crea_scuola(int capacita);
int cerca_classe(const Scuola *s, const char *classe);
int aggiungi_classe(Scuola *s, const char *classe);
int numero_classi(const Scuola *s);
const char *nome_classe(const Scuola *s, int i);
Voti *voti_classe(const Scuola *s, int i);
void distruggi_scuola(Scuola *s);

int main(void)
{
    Scuola *scuola = crea_scuola(2);
    Voti *voti;
    char classe[8];
    int voto;
    int letti;
    int indice;
    int somma;
    int finito = 0;
    int i;
    int j;

    if (scuola == NULL) {
        printf("Memoria insufficiente.\n");
        finito = 1;
    } else {
        printf("Classe e voto (FINE per terminare):\n");
    }
    while (!finito) {
        if (scanf("%7s", classe) != 1 || strcmp(classe, "FINE") == 0) {
            finito = 1;
        } else if ((letti = scanf("%d", &voto)) != 1 || voto < 1 || voto > 10) {
            printf("  voto non valido per %s\n", classe);
            if (letti == 0) {
                scanf("%*s");
            }
        } else {
            indice = cerca_classe(scuola, classe);
            if (indice == -1) {
                indice = aggiungi_classe(scuola, classe);
            }
            if (indice == -1 || !aggiungi(voti_classe(scuola, indice), voto)) {
                printf("Memoria insufficiente.\n");
                finito = 1;
            }
        }
    }
    if (scuola != NULL && numero_classi(scuola) == 0) {
        printf("Nessun voto registrato.\n");
    } else if (scuola != NULL) {
        printf("\n%-6s %4s %4s %5s  %s\n", "Classe", "Voti", "Cap.", "Media", "Elenco");
        for (i = 0; i < numero_classi(scuola); i++) {
            voti = voti_classe(scuola, i);
            somma = 0;
            for (j = 0; j < lunghezza(voti); j++) {
                somma += elemento(voti, j);
            }
            printf("%-6s %4d %4d %5.2f ", nome_classe(scuola, i), lunghezza(voti),
                   capacita(voti), (double) somma / lunghezza(voti));
            for (j = 0; j < lunghezza(voti); j++) {
                printf(" %d", elemento(voti, j));
            }
            printf("\n");
        }
    }
    distruggi_scuola(scuola);

    return 0;
}

Voti *crea_voti(int capacita)
{
    Voti *v = malloc(sizeof *v);

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

int aggiungi(Voti *v, int voto)
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
        v->dati[v->n] = voto;
        v->n++;
    }
    return ok;
}

int lunghezza(const Voti *v)
{
    return v->n;
}

int capacita(const Voti *v)
{
    return v->capacita;
}

int elemento(const Voti *v, int i)
{
    return v->dati[i];
}

void distruggi_voti(Voti *v)
{
    if (v != NULL) {
        free(v->dati);
        free(v);
    }
}

Scuola *crea_scuola(int capacita)
{
    Scuola *s = malloc(sizeof *s);

    if (s != NULL) {
        s->dati = malloc(capacita * sizeof *s->dati);
        if (s->dati == NULL) {
            free(s);
            s = NULL;
        } else {
            s->n = 0;
            s->capacita = capacita;
        }
    }
    return s;
}

int cerca_classe(const Scuola *s, const char *classe)
{
    int trovato = -1;
    int i;

    for (i = 0; i < s->n && trovato == -1; i++) {
        if (strcmp(s->dati[i].classe, classe) == 0) {
            trovato = i;
        }
    }
    return trovato;
}

/* Nuova riga con un vettore di voti vuoto; indice della riga o -1. */
int aggiungi_classe(Scuola *s, const char *classe)
{
    Riga *tmp;
    Voti *voti = crea_voti(2);
    int indice = -1;

    if (voti != NULL && s->n == s->capacita) {
        tmp = realloc(s->dati, 2 * s->capacita * sizeof *tmp);
        if (tmp != NULL) {
            s->dati = tmp;
            s->capacita = 2 * s->capacita;
        }
    }
    if (voti != NULL && s->n < s->capacita) {
        strcpy(s->dati[s->n].classe, classe);
        s->dati[s->n].voti = voti;
        indice = s->n;
        s->n++;
    } else {
        distruggi_voti(voti);
    }
    return indice;
}

int numero_classi(const Scuola *s)
{
    return s->n;
}

const char *nome_classe(const Scuola *s, int i)
{
    return s->dati[i].classe;
}

Voti *voti_classe(const Scuola *s, int i)
{
    return s->dati[i].voti;
}

/* Dal basso verso l'alto: voti di ogni riga, blocco delle righe, Scuola. */
void distruggi_scuola(Scuola *s)
{
    int i;

    if (s != NULL) {
        for (i = 0; i < s->n; i++) {
            distruggi_voti(s->dati[i].voti);
        }
        free(s->dati);
        free(s);
    }
}
