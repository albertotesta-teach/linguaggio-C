/*
 * 030-copiare-e-confrontare.c
 *
 * Copiare un vettore dinamico e confrontare due vettori
 *
 * Copiare il PUNTATORE non copia il vettore:
 *
 *     Vettore *alias = originale;
 *
 *     originale ---+
 *                  +--> [Vettore] --> 12 7 9 15
 *     alias -------+
 *
 * Due nomi per lo stesso vettore: una modifica fatta tramite alias si
 * vede anche da originale, e si distrugge una volta sola.
 *
 * Neanche copiare la struct basta (copia superficiale): la nuova struct
 * avrebbe lo stesso puntatore dati, quindi lo stesso blocco di elementi.
 *
 * La copia profonda crea un vettore nuovo con un blocco nuovo e copia
 * gli elementi uno a uno:
 *
 *     originale --> [Vettore] --> 12 7 9 15
 *     copia     --> [Vettore] --> 12 7 9 15     blocco distinto
 *
 * Ora i due vettori sono indipendenti e vanno distrutti entrambi.
 *
 * Anche il confronto ha due significati:
 *     originale == copia            confronta gli indirizzi: falso
 *     prima_differenza(a, b) == -1  confronta il contenuto: vero
 *
 * prima_differenza scorre i due vettori finché trova un elemento
 * diverso; restituisce la sua posizione, oppure -1 se i vettori hanno
 * stessa lunghezza e stessi elementi.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *dati;
    int n;
    int capacita;
} Vettore;

Vettore *crea_vettore(int capacita);
int aggiungi(Vettore *v, int valore);
int lunghezza(const Vettore *v);
int elemento(const Vettore *v, int i);
void imposta(Vettore *v, int i, int valore);
void distruggi_vettore(Vettore *v);
Vettore *copia(const Vettore *v);
int prima_differenza(const Vettore *a, const Vettore *b);
void stampa(const char *nome, const Vettore *v);
void confronta(const char *nome_a, const Vettore *a, const char *nome_b, const Vettore *b);

int main(void)
{
    int punteggi[] = {12, 7, 9, 15};
    Vettore *originale = crea_vettore(2);
    Vettore *alias;
    Vettore *doppione = NULL;
    int ok = originale != NULL;
    int i;

    for (i = 0; i < 4 && ok; i++) {
        ok = aggiungi(originale, punteggi[i]);
    }
    if (ok) {
        doppione = copia(originale);
        ok = doppione != NULL;
    }
    if (!ok) {
        printf("Memoria insufficiente.\n");
    } else {
        alias = originale;
        printf("Partenza:\n");
        stampa("originale", originale);
        stampa("alias", alias);
        stampa("copia", doppione);
        printf("originale == alias: %s\n", originale == alias ? "si'" : "no");
        printf("originale == copia: %s\n", originale == doppione ? "si'" : "no");
        confronta("originale", originale, "copia", doppione);

        printf("\nimposta(alias, 0, 99):\n");
        imposta(alias, 0, 99);
        stampa("originale", originale);
        stampa("copia", doppione);

        printf("\nimposta(copia, 2, 40) e aggiungi(copia, 3):\n");
        imposta(doppione, 2, 40);
        if (aggiungi(doppione, 3)) {
            stampa("originale", originale);
            stampa("copia", doppione);
        }
        confronta("originale", originale, "copia", doppione);
    }
    distruggi_vettore(originale);
    distruggi_vettore(doppione);

    return 0;
}

Vettore *crea_vettore(int capacita)
{
    Vettore *v = malloc(sizeof *v);

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

int aggiungi(Vettore *v, int valore)
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
        v->dati[v->n] = valore;
        v->n++;
    }
    return ok;
}

int lunghezza(const Vettore *v)
{
    return v->n;
}

int elemento(const Vettore *v, int i)
{
    return v->dati[i];
}

void imposta(Vettore *v, int i, int valore)
{
    v->dati[i] = valore;
}

void distruggi_vettore(Vettore *v)
{
    if (v != NULL) {
        free(v->dati);
        free(v);
    }
}

/* Copia profonda: vettore nuovo, blocco nuovo; NULL se manca memoria. */
Vettore *copia(const Vettore *v)
{
    Vettore *c = crea_vettore(v->capacita);
    int i;

    if (c != NULL) {
        for (i = 0; i < v->n; i++) {
            c->dati[i] = v->dati[i];
        }
        c->n = v->n;
    }
    return c;
}

/* Posizione del primo elemento diverso, -1 se i vettori sono uguali. */
int prima_differenza(const Vettore *a, const Vettore *b)
{
    int i = 0;
    int risultato = -1;

    while (i < lunghezza(a) && i < lunghezza(b) && elemento(a, i) == elemento(b, i)) {
        i++;
    }
    if (i < lunghezza(a) || i < lunghezza(b)) {
        risultato = i;
    }
    return risultato;
}

void stampa(const char *nome, const Vettore *v)
{
    int i;

    printf("  %-10s", nome);
    for (i = 0; i < lunghezza(v); i++) {
        printf(" %3d", elemento(v, i));
    }
    printf("\n");
}

void confronta(const char *nome_a, const Vettore *a, const char *nome_b, const Vettore *b)
{
    int posizione = prima_differenza(a, b);

    if (posizione == -1) {
        printf("%s e %s hanno lo stesso contenuto\n", nome_a, nome_b);
    } else {
        printf("%s e %s differiscono dalla posizione %d\n", nome_a, nome_b, posizione);
    }
}
