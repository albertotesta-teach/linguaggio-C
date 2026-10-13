/*
 * 030-ridurre-la-capacita.c
 *
 * Restituire memoria quando il vettore si svuota, senza altalena
 *
 * Dopo molte rimozioni un vettore può avere una capacità molto più
 * grande della lunghezza. Si può dimezzare la capacità, ma bisogna
 * scegliere bene QUANDO.
 *
 * Regola sbagliata: dimezzare appena n scende a capacita / 2. Con
 * capacità 16 e n = 9:
 *
 *     togli -> n = 8  = 16/2  : dimezza a 8   (vettore pieno)
 *     aggiungi -> n = 9       : raddoppia a 16
 *     togli -> n = 8          : dimezza a 8
 *     ...                       una realloc a ogni operazione (altalena)
 *
 * Regola corretta: dimezzare solo quando n scende a capacita / 4. Dopo
 * il dimezzamento il vettore è pieno per metà: servono molte operazioni
 * prima della prossima realloc, in un senso o nell'altro.
 *
 * Il programma riempie un vettore con 9 elementi, poi alterna 20 volte
 * "togli l'ultimo" e "aggiungi", con le due regole, e conta le realloc.
 * Poi svuota il vettore e mostra come scende la capacità (minimo 4).
 */

#include <stdio.h>
#include <stdlib.h>

#define MINIMO 4

typedef struct {
    int *dati;
    int n;
    int capacita;
    int riallocazioni;
} Vettore;

int inizializza(Vettore *v);
int cambia_capacita(Vettore *v, int nuova);
int aggiungi(Vettore *v, int valore);
int togli_ultimo(Vettore *v, int *valore, int divisore);

int main(void)
{
    Vettore v;
    int divisori[2] = {2, 4};
    int valore;
    int k;
    int i;

    for (k = 0; k < 2; k++) {
        if (inizializza(&v)) {
            for (i = 0; i < 9; i++) {
                aggiungi(&v, i);
            }
            v.riallocazioni = 0;
            for (i = 0; i < 20; i++) {
                togli_ultimo(&v, &valore, divisori[k]);
                aggiungi(&v, valore);
            }
            printf("dimezza quando n = capacita / %d: %2d realloc in 40 operazioni\n",
                   divisori[k], v.riallocazioni);
            free(v.dati);
        }
    }

    printf("\nSvuotamento con la regola capacita / 4:\n");
    if (inizializza(&v)) {
        for (i = 0; i < 32; i++) {
            aggiungi(&v, i);
        }
        printf("  n = %2d, capacita' = %2d\n", v.n, v.capacita);
        while (togli_ultimo(&v, &valore, 4)) {
            if (v.n == v.capacita / 2 || v.n == 0) {
                printf("  n = %2d, capacita' = %2d\n", v.n, v.capacita);
            }
        }
        free(v.dati);
    }

    return 0;
}

int inizializza(Vettore *v)
{
    v->dati = malloc(MINIMO * sizeof *v->dati);
    v->n = 0;
    v->capacita = MINIMO;
    v->riallocazioni = 0;
    return v->dati != NULL;
}

/* realloc a nuova capacità; 0 se fallisce (il vettore non cambia). */
int cambia_capacita(Vettore *v, int nuova)
{
    int *tmp = realloc(v->dati, nuova * sizeof *tmp);

    if (tmp != NULL) {
        v->dati = tmp;
        v->capacita = nuova;
        v->riallocazioni++;
    }
    return tmp != NULL;
}

int aggiungi(Vettore *v, int valore)
{
    int ok = 1;

    if (v->n == v->capacita) {
        ok = cambia_capacita(v, 2 * v->capacita);
    }
    if (ok) {
        v->dati[v->n] = valore;
        v->n++;
    }
    return ok;
}

/*
 * Toglie l'ultimo; se n scende a capacita / divisore dimezza la
 * capacità (mai sotto MINIMO). Se il dimezzamento fallisce il vettore
 * resta solo più grande del necessario.
 */
int togli_ultimo(Vettore *v, int *valore, int divisore)
{
    int ok = v->n > 0;

    if (ok) {
        v->n--;
        *valore = v->dati[v->n];
        if (v->n == v->capacita / divisore && v->capacita / 2 >= MINIMO) {
            cambia_capacita(v, v->capacita / 2);
        }
    }
    return ok;
}
