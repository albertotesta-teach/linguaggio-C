/*
 * 030-const-per-leggere.c
 *
 * const Tipo *: passare l'indirizzo per leggere senza copiare
 *
 * Una funzione che deve solo LEGGERE una struct grande può ricevere il
 * suo indirizzo invece di una copia. Con const il compilatore garantisce
 * che la funzione non la modifichi:
 *
 *     double media(const Registro *r);
 *     media(&registro);
 *
 *     dentro la funzione:   r->voti[i]         lettura permessa
 *                           r->n_voti = 0;     errore: r punta a dati const
 *
 * Il prototipo dice tutto: Tipo t (copia, solo per struct piccole),
 * const Tipo *t (lettura senza copia), Tipo *t (lettura e modifica).
 *
 * Esempio: lo stesso registro di 030-costo-della-copia (sezione
 * 01-struct-per-valore), con le funzioni riscritte con const Registro *:
 * si passano 8 byte invece di 808 a ogni chiamata.
 */

#include <stdio.h>

#define MAX_VOTI 200

typedef struct {
    char classe[4];
    int voti[MAX_VOTI];
    int n_voti;
} Registro;

double media(const Registro *r);
int massimo(const Registro *r);
int insufficienze(const Registro *r);
void aggiungi_voto(Registro *r, int voto);

int main(void)
{
    Registro registro = {"3B", {7, 6, 8, 5, 9, 6, 7, 4, 8, 6, 7, 5}, 12};

    printf("Registro della %s: %d voti\n", registro.classe, registro.n_voti);
    printf("  media %.2f, massimo %d, insufficienze %d\n", media(&registro), massimo(&registro),
           insufficienze(&registro));

    /* solo questa funzione modifica il registro: riceve Registro *, senza const */
    aggiungi_voto(&registro, 10);
    printf("Dopo aggiungi_voto(&registro, 10): media %.2f, massimo %d\n", media(&registro),
           massimo(&registro));

    printf("\nByte passati a ogni chiamata: %zu invece di %zu\n", sizeof(&registro), sizeof(registro));

    return 0;
}

double media(const Registro *r)
{
    int somma = 0;
    int i;

    for (i = 0; i < r->n_voti; i++) {
        somma = somma + r->voti[i];
    }
    /* r->n_voti = 0;   errore: assignment of member in read-only object */
    return (double) somma / r->n_voti;
}

int massimo(const Registro *r)
{
    int piu_alto = r->voti[0];
    int i;

    for (i = 1; i < r->n_voti; i++) {
        if (r->voti[i] > piu_alto) {
            piu_alto = r->voti[i];
        }
    }
    return piu_alto;
}

int insufficienze(const Registro *r)
{
    int conteggio = 0;
    int i;

    for (i = 0; i < r->n_voti; i++) {
        if (r->voti[i] < 6) {
            conteggio++;
        }
    }
    return conteggio;
}

/* Aggiunge un voto se c'è posto. */
void aggiungi_voto(Registro *r, int voto)
{
    if (r->n_voti < MAX_VOTI) {
        r->voti[r->n_voti] = voto;
        r->n_voti++;
    }
}
