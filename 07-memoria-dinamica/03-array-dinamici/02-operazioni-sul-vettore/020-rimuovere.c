/*
 * 020-rimuovere.c
 *
 * Togliere un elemento: da una posizione qualsiasi o dal fondo
 *
 * Rimuovere l'elemento in posizione p lascia un buco: gli elementi
 * successivi si spostano di un posto verso sinistra, partendo dal PRIMO
 * dopo p (il contrario dell'inserimento).
 *
 *     rimuovi(v, 1, &valore):
 *
 *     prima:  [10 20 30 40]       valore = 20
 *     sposta: [10 30 40 40]       i = p ... n - 2
 *     dopo:   [10 30 40]          n = 3
 *
 *     int rimuovi(Vettore *v, int posizione, int *valore);
 *     int togli_ultimo(Vettore *v, int *valore);
 *
 * L'elemento tolto viene restituito nel parametro di uscita valore; la
 * funzione restituisce 0 se la posizione non è valida (o il vettore è
 * vuoto). togli_ultimo non sposta niente: costa una sola lettura.
 *
 * La capacità non cambia: i posti liberati restano pronti per le
 * aggiunte successive (030-ridurre-la-capacita).
 *
 * Esempio: i codici dei libri in prestito alla classe; alcuni vengono
 * restituiti in mezzo all'elenco, poi dall'ultimo.
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
int rimuovi(Vettore *v, int posizione, int *valore);
int togli_ultimo(Vettore *v, int *valore);
void stampa(const Vettore *v);
void distruggi_vettore(Vettore *v);

int main(void)
{
    int codici[6] = {101, 205, 309, 412, 518, 623};
    Vettore *prestiti = crea_vettore(8);
    int valore;
    int k;
    int ok = prestiti != NULL;

    for (k = 0; k < 6 && ok; k++) {
        ok = aggiungi(prestiti, codici[k]);
    }
    if (!ok) {
        printf("Memoria insufficiente.\n");
    } else {
        stampa(prestiti);
        if (rimuovi(prestiti, 1, &valore)) {
            printf("restituito il libro in posizione 1: %d\n", valore);
            stampa(prestiti);
        }
        if (rimuovi(prestiti, 0, &valore)) {
            printf("restituito il primo libro: %d\n", valore);
            stampa(prestiti);
        }
        if (!rimuovi(prestiti, 7, &valore)) {
            printf("posizione 7 non valida: nessuna modifica\n");
        }
        while (togli_ultimo(prestiti, &valore)) {
            printf("restituito l'ultimo: %d\n", valore);
        }
        stampa(prestiti);
        if (!togli_ultimo(prestiti, &valore)) {
            printf("vettore vuoto: niente da togliere\n");
        }
    }
    distruggi_vettore(prestiti);

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

int rimuovi(Vettore *v, int posizione, int *valore)
{
    int ok = posizione >= 0 && posizione < v->n;
    int i;

    if (ok) {
        *valore = v->dati[posizione];
        for (i = posizione; i < v->n - 1; i++) {
            v->dati[i] = v->dati[i + 1];
        }
        v->n--;
    }
    return ok;
}

int togli_ultimo(Vettore *v, int *valore)
{
    int ok = v->n > 0;

    if (ok) {
        v->n--;
        *valore = v->dati[v->n];
    }
    return ok;
}

void stampa(const Vettore *v)
{
    int i;

    printf("  [");
    for (i = 0; i < v->n; i++) {
        printf(" %d", v->dati[i]);
    }
    printf(" ]  n = %d, capacita' = %d\n", v->n, v->capacita);
}

void distruggi_vettore(Vettore *v)
{
    if (v != NULL) {
        free(v->dati);
        free(v);
    }
}
