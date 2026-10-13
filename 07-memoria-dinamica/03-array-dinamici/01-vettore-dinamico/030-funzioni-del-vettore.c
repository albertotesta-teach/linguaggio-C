/*
 * 030-funzioni-del-vettore.c
 *
 * Il vettore dinamico come tipo: si usa solo con le sue funzioni
 *
 * Chi usa il vettore non tocca mai dati, n e capacita: chiama le
 * funzioni del tipo, che mantengono i campi coerenti.
 *
 *     Vettore *crea_vettore(int capacita);
 *     int aggiungi(Vettore *v, int valore);       0 se manca memoria
 *     int lunghezza(const Vettore *v);
 *     int elemento(const Vettore *v, int i);      0 <= i < lunghezza
 *     void distruggi_vettore(Vettore *v);
 *
 * aggiungi raddoppia la capacità quando il vettore è pieno. Se la
 * realloc fallisce restituisce 0 e il vettore resta com'era: tutti gli
 * elementi già inseriti sono ancora validi.
 *
 * elemento non controlla l'indice (come un array normale): il chiamante
 * deve rispettare 0 <= i < lunghezza(v).
 *
 * Esempio: le pagine lette ogni giorno durante la sfida di lettura della
 * biblioteca, inserite fino a -1. Il vettore parte con 2 posti; il
 * programma segnala ogni raddoppio, poi stampa totale, media e giorni
 * sopra la media.
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
int capacita(const Vettore *v);
void distruggi_vettore(Vettore *v);

int main(void)
{
    Vettore *pagine = crea_vettore(2);
    int valore;
    int vecchia;
    int finito = 0;
    int totale = 0;
    double media;
    int i;

    if (pagine == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        printf("Pagine lette ogni giorno (-1 per terminare): ");
        while (!finito) {
            if (scanf("%d", &valore) != 1 || valore < 0) {
                finito = 1;
            } else {
                vecchia = capacita(pagine);
                if (!aggiungi(pagine, valore)) {
                    printf("\nMemoria insufficiente: lettura interrotta.\n");
                    finito = 1;
                } else if (capacita(pagine) != vecchia) {
                    printf("\n  capacita' da %d a %d", vecchia, capacita(pagine));
                }
            }
        }

        printf("\nGiorni: %d, capacita' finale: %d\n", lunghezza(pagine), capacita(pagine));
        for (i = 0; i < lunghezza(pagine); i++) {
            totale = totale + elemento(pagine, i);
        }
        if (lunghezza(pagine) > 0) {
            media = (double) totale / lunghezza(pagine);
            printf("Totale %d pagine, media %.1f al giorno\nSopra la media:", totale, media);
            for (i = 0; i < lunghezza(pagine); i++) {
                if (elemento(pagine, i) > media) {
                    printf(" giorno %d (%d)", i + 1, elemento(pagine, i));
                }
            }
            printf("\n");
        }
        distruggi_vettore(pagine);
    }

    return 0;
}

/* Struct e blocco dei dati; NULL se una malloc fallisce. */
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

/* Aggiunge in fondo, raddoppiando se pieno; 0 se manca memoria. */
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

int capacita(const Vettore *v)
{
    return v->capacita;
}

void distruggi_vettore(Vettore *v)
{
    if (v != NULL) {
        free(v->dati);
        free(v);
    }
}
