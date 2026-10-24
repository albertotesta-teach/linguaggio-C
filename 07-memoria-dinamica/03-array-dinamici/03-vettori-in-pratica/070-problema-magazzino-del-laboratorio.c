/*
 * 070-problema-magazzino-del-laboratorio.c
 *
 * Il magazzino del laboratorio di elettronica: carichi, scarichi e scorte
 *
 * Il tecnico di laboratorio tiene il conto del materiale: resistenze,
 * LED, breadboard... Ogni articolo ha una quantità disponibile e una
 * scorta minima, sotto la quale bisogna riordinare:
 *
 *     typedef struct {
 *         char nome[20];
 *         int quantita;
 *         int scorta;
 *     } Articolo;
 *
 * Il magazzino è un vettore dinamico di Articolo. Carico e scarico
 * modificano l'articolo tramite il puntatore restituito da trova (il
 * puntatore si usa subito, prima di altre aggiunte). Uno scarico non può
 * superare la quantità disponibile.
 *
 * L'elenco da riordinare è un SECONDO vettore, creato da sotto_scorta:
 * contiene una copia degli articoli con quantità minore della scorta.
 * È una fotografia del momento: un carico successivo non lo aggiorna, e
 * il chiamante lo distrugge dopo averlo stampato.
 *
 * Comandi:
 *     N nome quantita scorta    nuovo articolo
 *     C nome quantita           carico
 *     S nome quantita           scarico
 *     R                         articoli da riordinare
 *     E                         elenco completo
 *     Q                         fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nome[20];
    int quantita;
    int scorta;
} Articolo;

typedef struct {
    Articolo *dati;
    int n;
    int capacita;
} Magazzino;

Magazzino *crea_magazzino(int capacita);
int aggiungi(Magazzino *m, Articolo a);
int lunghezza(const Magazzino *m);
Articolo *elemento(Magazzino *m, int i);
Articolo *trova(Magazzino *m, const char *nome);
void distruggi_magazzino(Magazzino *m);
Magazzino *sotto_scorta(Magazzino *m);
void stampa(Magazzino *m);

int main(void)
{
    Magazzino *magazzino = crea_magazzino(2);
    Magazzino *riordino;
    Articolo a;
    Articolo *p;
    char comando = ' ';
    int quantita;

    if (magazzino == NULL) {
        printf("Memoria insufficiente.\n");
        comando = 'Q';
    }
    while (comando != 'Q') {
        printf("Comando (N, C, S, R, E, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'N') {
            if (scanf("%19s %d %d", a.nome, &a.quantita, &a.scorta) != 3 || a.quantita < 0 ||
                a.scorta < 0) {
                printf("  Dati non validi.\n");
            } else if (trova(magazzino, a.nome) != NULL) {
                printf("  %s esiste gia'.\n", a.nome);
            } else if (!aggiungi(magazzino, a)) {
                printf("  Memoria insufficiente.\n");
            } else {
                printf("  nuovo articolo: %s\n", a.nome);
            }
        } else if (comando == 'C' || comando == 'S') {
            p = NULL;
            if (scanf("%19s %d", a.nome, &quantita) == 2 && quantita > 0) {
                p = trova(magazzino, a.nome);
            }
            if (p == NULL) {
                printf("  Articolo inesistente o quantita' non valida.\n");
            } else if (comando == 'C') {
                p->quantita += quantita;
                printf("  %s: disponibili %d\n", p->nome, p->quantita);
            } else if (quantita > p->quantita) {
                printf("  %s: disponibili solo %d\n", p->nome, p->quantita);
            } else {
                p->quantita -= quantita;
                printf("  %s: disponibili %d", p->nome, p->quantita);
                if (p->quantita < p->scorta) {
                    printf("  (sotto scorta)");
                }
                printf("\n");
            }
        } else if (comando == 'R') {
            riordino = sotto_scorta(magazzino);
            if (riordino == NULL) {
                printf("  Memoria insufficiente.\n");
            } else if (lunghezza(riordino) == 0) {
                printf("  Niente da riordinare.\n");
            } else {
                printf("  Da riordinare: %d\n", lunghezza(riordino));
                stampa(riordino);
            }
            distruggi_magazzino(riordino);
        } else if (comando == 'E') {
            stampa(magazzino);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q') {
            scanf("%*[^\n]");          /* un comando per riga */
        }
    }
    distruggi_magazzino(magazzino);

    return 0;
}

Magazzino *crea_magazzino(int capacita)
{
    Magazzino *m = malloc(sizeof *m);

    if (m != NULL) {
        m->dati = malloc(capacita * sizeof *m->dati);
        if (m->dati == NULL) {
            free(m);
            m = NULL;
        } else {
            m->n = 0;
            m->capacita = capacita;
        }
    }
    return m;
}

int aggiungi(Magazzino *m, Articolo a)
{
    Articolo *tmp;
    int ok = 1;

    if (m->n == m->capacita) {
        tmp = realloc(m->dati, 2 * m->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            m->dati = tmp;
            m->capacita = 2 * m->capacita;
        }
    }
    if (ok) {
        m->dati[m->n] = a;
        m->n++;
    }
    return ok;
}

int lunghezza(const Magazzino *m)
{
    return m->n;
}

/* Puntatore all'articolo i: valido solo fino alla prossima aggiunta. */
Articolo *elemento(Magazzino *m, int i)
{
    return &m->dati[i];
}

Articolo *trova(Magazzino *m, const char *nome)
{
    Articolo *p = NULL;
    int i;

    for (i = 0; i < m->n && p == NULL; i++) {
        if (strcmp(m->dati[i].nome, nome) == 0) {
            p = &m->dati[i];
        }
    }
    return p;
}

void distruggi_magazzino(Magazzino *m)
{
    if (m != NULL) {
        free(m->dati);
        free(m);
    }
}

/* Vettore nuovo: copie degli articoli sotto scorta; NULL senza memoria. */
Magazzino *sotto_scorta(Magazzino *m)
{
    Magazzino *risultato = crea_magazzino(2);
    int ok = risultato != NULL;
    int i;

    for (i = 0; i < lunghezza(m) && ok; i++) {
        if (elemento(m, i)->quantita < elemento(m, i)->scorta) {
            ok = aggiungi(risultato, *elemento(m, i));
        }
    }
    if (!ok) {
        distruggi_magazzino(risultato);
        risultato = NULL;
    }
    return risultato;
}

void stampa(Magazzino *m)
{
    Articolo *p;
    int i;

    printf("  %-14s %10s %7s\n", "Articolo", "Quantita", "Scorta");
    for (i = 0; i < lunghezza(m); i++) {
        p = elemento(m, i);
        printf("  %-14s %10d %7d\n", p->nome, p->quantita, p->scorta);
    }
}
