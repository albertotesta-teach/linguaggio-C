/*
 * 040-problema-classifica-in-ordine.c
 *
 * La corsa campestre: la classifica si tiene in ordine a ogni arrivo
 *
 * Al traguardo un giudice comunica i tempi degli atleti, non sempre
 * nell'ordine di arrivo (i giudici sono più d'uno). La classifica è un
 * vettore dinamico di Arrivo, tenuto SEMPRE ordinato per tempo:
 *
 *     typedef struct {
 *         char nome[20];
 *         int secondi;
 *     } Arrivo;
 *
 * Ogni nuovo tempo si inserisce nella posizione giusta: si cerca il
 * primo atleta con un tempo maggiore e si inserisce lì (gli altri
 * scalano di un posto). Con tempi uguali il nuovo arrivato va dopo gli
 * altri. Così la classifica è pronta in ogni momento, senza ordinarla.
 *
 * Un atleta squalificato si toglie con rimuovi: chi lo seguiva sale di
 * una posizione.
 *
 * Comandi:
 *     A nome mm:ss     arrivo
 *     S nome           squalifica
 *     C                classifica
 *     Q                fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nome[20];
    int secondi;
} Arrivo;

typedef struct {
    Arrivo *dati;
    int n;
    int capacita;
} Classifica;

Classifica *crea_classifica(int capacita);
int inserisci(Classifica *c, int posizione, Arrivo a);
int rimuovi(Classifica *c, int posizione);
int lunghezza(const Classifica *c);
Arrivo elemento(const Classifica *c, int i);
void distruggi_classifica(Classifica *c);
int posizione_per_tempo(const Classifica *c, int secondi);
int cerca(const Classifica *c, const char *nome);

int main(void)
{
    Classifica *classifica = crea_classifica(4);
    Arrivo a;
    Arrivo primo;
    char comando = ' ';
    char nome[20];
    int minuti;
    int secondi;
    int posizione;
    int i;

    if (classifica == NULL) {
        printf("Memoria insufficiente.\n");
        comando = 'Q';
    }
    while (comando != 'Q') {
        printf("Comando (A, S, C, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'A') {
            if (scanf("%19s %d:%d", a.nome, &minuti, &secondi) != 3 || minuti < 0 ||
                secondi < 0 || secondi > 59) {
                printf("  Dati non validi.\n");
            } else if (cerca(classifica, a.nome) != -1) {
                printf("  %s ha gia' un tempo.\n", a.nome);
            } else {
                a.secondi = minuti * 60 + secondi;
                posizione = posizione_per_tempo(classifica, a.secondi);
                if (inserisci(classifica, posizione, a)) {
                    printf("  %s in posizione %d\n", a.nome, posizione + 1);
                } else {
                    printf("  Memoria insufficiente.\n");
                }
            }
        } else if (comando == 'S') {
            posizione = -1;
            if (scanf("%19s", nome) == 1) {
                posizione = cerca(classifica, nome);
            }
            if (posizione == -1) {
                printf("  Atleta non in classifica.\n");
            } else {
                rimuovi(classifica, posizione);
                printf("  squalifica di %s: chi seguiva sale di una posizione\n", nome);
            }
        } else if (comando == 'C') {
            for (i = 0; i < lunghezza(classifica); i++) {
                a = elemento(classifica, i);
                primo = elemento(classifica, 0);
                printf("  %2d. %-10s %2d:%02d  +%d s\n", i + 1, a.nome, a.secondi / 60,
                       a.secondi % 60, a.secondi - primo.secondi);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q') {
            scanf("%*[^\n]");          /* un comando per riga */
        }
    }
    distruggi_classifica(classifica);

    return 0;
}

Classifica *crea_classifica(int capacita)
{
    Classifica *c = malloc(sizeof *c);

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

int inserisci(Classifica *c, int posizione, Arrivo a)
{
    Arrivo *tmp;
    int ok = posizione >= 0 && posizione <= c->n;
    int i;

    if (ok && c->n == c->capacita) {
        tmp = realloc(c->dati, 2 * c->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            c->dati = tmp;
            c->capacita = 2 * c->capacita;
        }
    }
    if (ok) {
        for (i = c->n - 1; i >= posizione; i--) {
            c->dati[i + 1] = c->dati[i];
        }
        c->dati[posizione] = a;
        c->n++;
    }
    return ok;
}

int rimuovi(Classifica *c, int posizione)
{
    int ok = posizione >= 0 && posizione < c->n;
    int i;

    if (ok) {
        for (i = posizione; i < c->n - 1; i++) {
            c->dati[i] = c->dati[i + 1];
        }
        c->n--;
    }
    return ok;
}

int lunghezza(const Classifica *c)
{
    return c->n;
}

Arrivo elemento(const Classifica *c, int i)
{
    return c->dati[i];
}

void distruggi_classifica(Classifica *c)
{
    if (c != NULL) {
        free(c->dati);
        free(c);
    }
}

/* Primo atleta con tempo maggiore: lì va il nuovo arrivo. */
int posizione_per_tempo(const Classifica *c, int secondi)
{
    int posizione = 0;

    while (posizione < lunghezza(c) && elemento(c, posizione).secondi <= secondi) {
        posizione++;
    }
    return posizione;
}

int cerca(const Classifica *c, const char *nome)
{
    int trovato = -1;
    int i;

    for (i = 0; i < lunghezza(c) && trovato == -1; i++) {
        if (strcmp(elemento(c, i).nome, nome) == 0) {
            trovato = i;
        }
    }
    return trovato;
}
