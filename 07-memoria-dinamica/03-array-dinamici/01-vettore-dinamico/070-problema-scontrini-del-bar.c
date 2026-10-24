/*
 * 070-problema-scontrini-del-bar.c
 *
 * Il bar della scuola: le vendite della giornata e il riepilogo
 *
 * Ogni vendita è una riga "prodotto prezzo quantità". Le vendite della
 * giornata vanno in un vettore dinamico di struct Voce:
 *
 *     typedef struct {
 *         char prodotto[20];
 *         double prezzo;
 *         int quantita;
 *     } Voce;
 *
 *     typedef struct {
 *         Voce *dati;
 *         int n;
 *         int capacita;
 *     } Elenco;
 *
 * A fine giornata il programma costruisce un SECONDO elenco con una voce
 * per prodotto (quantità sommate, incasso nel campo prezzo), usando le
 * stesse funzioni: cerca il prodotto, se c'è aggiorna la voce, altrimenti
 * la aggiunge. Poi stampa il riepilogo, l'incasso totale e il prodotto
 * più venduto. Alla fine libera entrambi gli elenchi.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char prodotto[20];
    double prezzo;
    int quantita;
} Voce;

typedef struct {
    Voce *dati;
    int n;
    int capacita;
} Elenco;

Elenco *crea_elenco(int capacita);
int aggiungi(Elenco *e, Voce v);
int lunghezza(const Elenco *e);
Voce *elemento(Elenco *e, int i);
int cerca(const Elenco *e, const char *prodotto);
void distruggi_elenco(Elenco *e);

int main(void)
{
    Elenco *vendite = crea_elenco(4);
    Elenco *riepilogo = crea_elenco(4);
    Voce v;
    Voce *voce;
    char parola[20];
    int finito = 0;
    int ok = vendite != NULL && riepilogo != NULL;
    int posizione;
    int migliore = 0;
    double incasso = 0;
    int i;

    if (!ok) {
        printf("Memoria insufficiente.\n");
        finito = 1;
    } else {
        printf("Vendite (prodotto prezzo quantita', FINE per terminare):\n");
    }
    while (!finito) {
        if (scanf("%19s", parola) != 1 || strcmp(parola, "FINE") == 0) {
            finito = 1;
        } else if (scanf("%lf %d", &v.prezzo, &v.quantita) != 2 || v.prezzo <= 0 ||
                   v.quantita < 1) {
            printf("  vendita non valida\n");
        } else {
            strcpy(v.prodotto, parola);
            ok = aggiungi(vendite, v);
            finito = !ok;
        }
        if (!finito) {
            scanf("%*[^\n]");          /* una vendita per riga */
        }
    }

    for (i = 0; ok && i < lunghezza(vendite); i++) {
        v = *elemento(vendite, i);
        posizione = cerca(riepilogo, v.prodotto);
        if (posizione == -1) {
            v.prezzo = v.prezzo * v.quantita;
            ok = aggiungi(riepilogo, v);
        } else {
            voce = elemento(riepilogo, posizione);
            voce->quantita = voce->quantita + v.quantita;
            voce->prezzo = voce->prezzo + v.prezzo * v.quantita;
        }
    }

    if (!ok && vendite != NULL && riepilogo != NULL) {
        printf("Memoria insufficiente.\n");
    } else if (ok) {
        printf("\nVendite registrate: %d, prodotti diversi: %d\n", lunghezza(vendite),
               lunghezza(riepilogo));
        for (i = 0; i < lunghezza(riepilogo); i++) {
            voce = elemento(riepilogo, i);
            printf("  %-12s %3d pz  %7.2f euro\n", voce->prodotto, voce->quantita,
                   voce->prezzo);
            incasso = incasso + voce->prezzo;
            if (voce->quantita > elemento(riepilogo, migliore)->quantita) {
                migliore = i;
            }
        }
        printf("Incasso: %.2f euro\n", incasso);
        if (lunghezza(riepilogo) > 0) {
            printf("Piu' venduto: %s\n", elemento(riepilogo, migliore)->prodotto);
        }
    }
    distruggi_elenco(vendite);
    distruggi_elenco(riepilogo);

    return 0;
}

Elenco *crea_elenco(int capacita)
{
    Elenco *e = malloc(sizeof *e);

    if (e != NULL) {
        e->dati = malloc(capacita * sizeof *e->dati);
        if (e->dati == NULL) {
            free(e);
            e = NULL;
        } else {
            e->n = 0;
            e->capacita = capacita;
        }
    }
    return e;
}

int aggiungi(Elenco *e, Voce v)
{
    Voce *tmp;
    int ok = 1;

    if (e->n == e->capacita) {
        tmp = realloc(e->dati, 2 * e->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            e->dati = tmp;
            e->capacita = 2 * e->capacita;
        }
    }
    if (ok) {
        e->dati[e->n] = v;
        e->n++;
    }
    return ok;
}

int lunghezza(const Elenco *e)
{
    return e->n;
}

/*
 * Puntatore alla voce i, per leggerla o modificarla. Vale solo fino alla
 * prossima aggiungi, che può spostare il blocco.
 */
Voce *elemento(Elenco *e, int i)
{
    return &e->dati[i];
}

int cerca(const Elenco *e, const char *prodotto)
{
    int trovata = -1;
    int i;

    for (i = 0; i < e->n && trovata == -1; i++) {
        if (strcmp(e->dati[i].prodotto, prodotto) == 0) {
            trovata = i;
        }
    }
    return trovata;
}

void distruggi_elenco(Elenco *e)
{
    if (e != NULL) {
        free(e->dati);
        free(e);
    }
}
