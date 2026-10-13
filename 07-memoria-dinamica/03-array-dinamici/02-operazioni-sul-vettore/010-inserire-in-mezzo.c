/*
 * 010-inserire-in-mezzo.c
 *
 * Inserire un elemento in una posizione qualsiasi
 *
 * Aggiungere in fondo costa una scrittura. Inserire nella posizione p
 * richiede di fare spazio: gli elementi da p in poi si spostano di un
 * posto verso destra, partendo dall'ULTIMO (altrimenti ognuno
 * sovrascriverebbe il successivo prima che sia spostato).
 *
 *     inserisci(v, 2, 50):
 *
 *     prima:  [10 20 30 40 __]
 *     sposta: [10 20 30 30 40]    i = n - 1 ... p
 *     scrive: [10 20 50 30 40]
 *
 *     int inserisci(Vettore *v, int posizione, int valore);
 *
 * La posizione può andare da 0 (in testa) a n (in fondo, come
 * aggiungi). Se il vettore è pieno la capacità raddoppia prima dello
 * spostamento. Restituisce 0 se la posizione non è valida o se manca
 * memoria; in quel caso il vettore non cambia.
 *
 * Inserire in testa sposta tutti gli n elementi: più il vettore è lungo,
 * più l'inserimento costa.
 *
 * Esempio: l'ordine di uscita degli studenti per l'interrogazione;
 * l'insegnante inserisce gli studenti (numeri di registro) in posizioni
 * diverse.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *dati;
    int n;
    int capacita;
} Vettore;

Vettore *crea_vettore(int capacita);
int inserisci(Vettore *v, int posizione, int valore);
int lunghezza(const Vettore *v);
void stampa(const char *azione, const Vettore *v);
void distruggi_vettore(Vettore *v);

int main(void)
{
    Vettore *ordine = crea_vettore(2);
    int posizioni[6] = {0, 1, 0, 3, 2, 9};
    int numeri[6] = {12, 5, 20, 8, 17, 3};
    char azione[40];
    int k;

    if (ordine == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        stampa("inizio", ordine);
        for (k = 0; k < 6; k++) {
            snprintf(azione, sizeof azione, "inserisci(%d, %d)", posizioni[k], numeri[k]);
            if (inserisci(ordine, posizioni[k], numeri[k])) {
                stampa(azione, ordine);
            } else {
                printf("%-18s posizione non valida (da 0 a %d)\n", azione, lunghezza(ordine));
            }
        }
        distruggi_vettore(ordine);
    }

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

int inserisci(Vettore *v, int posizione, int valore)
{
    int *tmp;
    int ok = posizione >= 0 && posizione <= v->n;
    int i;

    if (ok && v->n == v->capacita) {
        tmp = realloc(v->dati, 2 * v->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            v->dati = tmp;
            v->capacita = 2 * v->capacita;
        }
    }
    if (ok) {
        for (i = v->n - 1; i >= posizione; i--) {
            v->dati[i + 1] = v->dati[i];
        }
        v->dati[posizione] = valore;
        v->n++;
    }
    return ok;
}

int lunghezza(const Vettore *v)
{
    return v->n;
}

void stampa(const char *azione, const Vettore *v)
{
    int i;

    printf("%-18s [", azione);
    for (i = 0; i < v->n; i++) {
        printf("%3d", v->dati[i]);
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
