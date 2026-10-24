/*
 * 080-problema-vettore-di-parole.c
 *
 * Il glossario di informatica della classe: un vettore di parole
 *
 * Gli studenti raccolgono i termini del glossario di informatica. I
 * termini sono di lunghezza molto diversa (bit, multiprogrammazione) e
 * il loro numero non si conosce prima. Il glossario è un vettore
 * dinamico di puntatori a char, e ogni termine sta in un blocco suo:
 *
 *     typedef struct {
 *         char **dati;       dati[i]: blocco con il termine i
 *         int n;
 *         int capacita;
 *     } Glossario;
 *
 * aggiungi copia il termine in un blocco nuovo di strlen + 1 byte e ne
 * salva l'indirizzo, raddoppiando la capacità quando serve. distruggi
 * libera PRIMA ogni termine e POI l'array di puntatori.
 *
 * Il programma legge i termini fino a FINE (un termine già presente non
 * viene aggiunto due volte), li ordina scambiando i puntatori (le parole
 * non si spostano) e stampa il glossario con la memoria usata.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMINE 40

typedef struct {
    char **dati;
    int n;
    int capacita;
} Glossario;

Glossario *crea_glossario(int capacita);
int aggiungi(Glossario *g, const char *termine);
int lunghezza(const Glossario *g);
int capacita(const Glossario *g);
const char *termine(const Glossario *g, int i);
int cerca(const Glossario *g, const char *parola);
void ordina(Glossario *g);
void distruggi_glossario(Glossario *g);

int main(void)
{
    Glossario *glossario = crea_glossario(2);
    char parola[MAX_TERMINE];
    int finito = 0;
    size_t byte_testi = 0;
    int i;

    if (glossario == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        printf("Termini (FINE per terminare):\n");
        while (!finito) {
            if (scanf("%39s", parola) != 1 || strcmp(parola, "FINE") == 0) {
                finito = 1;
            } else if (cerca(glossario, parola) != -1) {
                printf("  %s gia' presente\n", parola);
            } else if (!aggiungi(glossario, parola)) {
                printf("Memoria insufficiente.\n");
                finito = 1;
            }
        }

        ordina(glossario);
        printf("\nGlossario (%d termini):\n", lunghezza(glossario));
        for (i = 0; i < lunghezza(glossario); i++) {
            printf("  %s\n", termine(glossario, i));
            byte_testi = byte_testi + strlen(termine(glossario, i)) + 1;
        }
        printf("Memoria: %zu byte di testi + %zu byte di puntatori\n", byte_testi,
               capacita(glossario) * sizeof(char *));
        printf("Con una matrice char[%d][%d]: %zu byte\n", lunghezza(glossario), MAX_TERMINE,
               (size_t) lunghezza(glossario) * MAX_TERMINE);
        distruggi_glossario(glossario);
    }

    return 0;
}

Glossario *crea_glossario(int capacita)
{
    Glossario *g = malloc(sizeof *g);

    if (g != NULL) {
        g->dati = malloc(capacita * sizeof *g->dati);
        if (g->dati == NULL) {
            free(g);
            g = NULL;
        } else {
            g->n = 0;
            g->capacita = capacita;
        }
    }
    return g;
}

/* Copia il termine in un blocco nuovo e lo mette in fondo; 0 se manca
   memoria (il glossario resta com'era). */
int aggiungi(Glossario *g, const char *testo)
{
    char **tmp;
    char *copia = malloc((strlen(testo) + 1) * sizeof *copia);
    int ok = copia != NULL;

    if (ok && g->n == g->capacita) {
        tmp = realloc(g->dati, 2 * g->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            g->dati = tmp;
            g->capacita = 2 * g->capacita;
        }
    }
    if (ok) {
        strcpy(copia, testo);
        g->dati[g->n] = copia;
        g->n++;
    } else {
        free(copia);
    }
    return ok;
}

int lunghezza(const Glossario *g)
{
    return g->n;
}

int capacita(const Glossario *g)
{
    return g->capacita;
}

const char *termine(const Glossario *g, int i)
{
    return g->dati[i];
}

int cerca(const Glossario *g, const char *parola)
{
    int trovato = -1;
    int i;

    for (i = 0; i < g->n && trovato == -1; i++) {
        if (strcmp(g->dati[i], parola) == 0) {
            trovato = i;
        }
    }
    return trovato;
}

/* Selection sort sui puntatori: si scambiano gli indirizzi, non i testi. */
void ordina(Glossario *g)
{
    char *scambio;
    int minimo;
    int i;
    int j;

    for (i = 0; i < g->n - 1; i++) {
        minimo = i;
        for (j = i + 1; j < g->n; j++) {
            if (strcmp(g->dati[j], g->dati[minimo]) < 0) {
                minimo = j;
            }
        }
        scambio = g->dati[i];
        g->dati[i] = g->dati[minimo];
        g->dati[minimo] = scambio;
    }
}

/* Prima ogni termine, poi l'array dei puntatori, poi la struct. */
void distruggi_glossario(Glossario *g)
{
    int i;

    if (g != NULL) {
        for (i = 0; i < g->n; i++) {
            free(g->dati[i]);
        }
        free(g->dati);
        free(g);
    }
}
