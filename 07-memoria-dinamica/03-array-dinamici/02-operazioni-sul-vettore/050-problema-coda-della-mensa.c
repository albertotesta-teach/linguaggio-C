/*
 * 050-problema-coda-della-mensa.c
 *
 * La fila alla mensa: si entra in fondo, si esce dall'inizio
 *
 * Gli studenti si mettono in fila in fondo e vengono serviti dal primo.
 * La fila è un vettore dinamico di nomi:
 *
 *     entra:   aggiungi in fondo          costo: una scrittura
 *     servito: rimuovi la posizione 0     costo: n - 1 spostamenti
 *
 * Ogni volta che il primo viene servito, tutti gli altri si spostano di
 * un posto. Il programma conta gli spostamenti: con una fila lunga,
 * servire costa molto più che entrare. (Il capitolo 10 mostra la coda
 * circolare, in cui anche l'uscita costa una sola operazione.)
 *
 * Uno studente può anche lasciare la fila prima del suo turno (rimuovi
 * dalla sua posizione).
 *
 * Comandi:
 *     E nome      entra in fondo
 *     S           il primo viene servito
 *     L nome      lascia la fila
 *     F           mostra la fila
 *     Q           fine: quanti serviti e quanti spostamenti
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[20];
} Studente;

typedef struct {
    Studente *dati;
    int n;
    int capacita;
} Fila;

Fila *crea_fila(int capacita);
int aggiungi(Fila *f, Studente s);
int rimuovi(Fila *f, int posizione, Studente *uscito, long *spostamenti);
int lunghezza(const Fila *f);
Studente elemento(const Fila *f, int i);
int cerca(const Fila *f, const char *nome);
void distruggi_fila(Fila *f);

int main(void)
{
    Fila *fila = crea_fila(4);
    Studente s;
    char comando = ' ';
    long spostamenti = 0;
    int serviti = 0;
    int posizione;
    int i;

    if (fila == NULL) {
        printf("Memoria insufficiente.\n");
        comando = 'Q';
    }
    while (comando != 'Q') {
        printf("Comando (E, S, L, F, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'E') {
            if (scanf("%19s", s.nome) != 1) {
                printf("  Nome mancante.\n");
            } else if (!aggiungi(fila, s)) {
                printf("  Memoria insufficiente.\n");
            } else {
                printf("  %s in fila (posizione %d)\n", s.nome, lunghezza(fila));
            }
        } else if (comando == 'S') {
            if (rimuovi(fila, 0, &s, &spostamenti)) {
                serviti++;
                printf("  servito: %s (in fila restano %d)\n", s.nome, lunghezza(fila));
            } else {
                printf("  Fila vuota.\n");
            }
        } else if (comando == 'L') {
            posizione = -1;
            if (scanf("%19s", s.nome) == 1) {
                posizione = cerca(fila, s.nome);
            }
            if (posizione == -1) {
                printf("  Non e' in fila.\n");
            } else {
                rimuovi(fila, posizione, &s, &spostamenti);
                printf("  %s lascia la fila\n", s.nome);
            }
        } else if (comando == 'F') {
            printf("  fila:");
            for (i = 0; i < lunghezza(fila); i++) {
                printf(" %s", elemento(fila, i).nome);
            }
            printf("\n");
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q' && comando != 'F' && comando != 'S') {
            scanf("%*[^\n]");
        }
    }
    if (fila != NULL) {
        printf("Serviti: %d, spostamenti nel vettore: %ld\n", serviti, spostamenti);
    }
    distruggi_fila(fila);

    return 0;
}

Fila *crea_fila(int capacita)
{
    Fila *f = malloc(sizeof *f);

    if (f != NULL) {
        f->dati = malloc(capacita * sizeof *f->dati);
        if (f->dati == NULL) {
            free(f);
            f = NULL;
        } else {
            f->n = 0;
            f->capacita = capacita;
        }
    }
    return f;
}

int aggiungi(Fila *f, Studente s)
{
    Studente *tmp;
    int ok = 1;

    if (f->n == f->capacita) {
        tmp = realloc(f->dati, 2 * f->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            f->dati = tmp;
            f->capacita = 2 * f->capacita;
        }
    }
    if (ok) {
        f->dati[f->n] = s;
        f->n++;
    }
    return ok;
}

/* Toglie la posizione indicata e somma gli spostamenti fatti. */
int rimuovi(Fila *f, int posizione, Studente *uscito, long *spostamenti)
{
    int ok = posizione >= 0 && posizione < f->n;
    int i;

    if (ok) {
        *uscito = f->dati[posizione];
        for (i = posizione; i < f->n - 1; i++) {
            f->dati[i] = f->dati[i + 1];
            (*spostamenti)++;
        }
        f->n--;
    }
    return ok;
}

int lunghezza(const Fila *f)
{
    return f->n;
}

Studente elemento(const Fila *f, int i)
{
    return f->dati[i];
}

int cerca(const Fila *f, const char *nome)
{
    int trovato = -1;
    int i;

    for (i = 0; i < f->n && trovato == -1; i++) {
        if (strcmp(f->dati[i].nome, nome) == 0) {
            trovato = i;
        }
    }
    return trovato;
}

void distruggi_fila(Fila *f)
{
    if (f != NULL) {
        free(f->dati);
        free(f);
    }
}
