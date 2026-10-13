/*
 * 060-problema-storico-dei-prezzi.c
 *
 * Il prezzo del pasto in mensa: variazioni mese per mese
 *
 * Il comitato dei genitori registra ogni mese il prezzo del pasto della
 * mensa e vuole capire quanto e quando è aumentato. Le rilevazioni sono
 * in un vettore dinamico di Rilevazione, nell'ordine in cui arrivano:
 *
 *     typedef struct {
 *         char mese[8];          per esempio "set24"
 *         double prezzo;
 *     } Rilevazione;
 *
 * Per ogni mese dal secondo in poi si calcola la variazione percentuale
 * rispetto al mese prima:
 *
 *     variazione = (prezzo - prezzo_prima) / prezzo_prima * 100
 *
 * I mesi con un aumento si copiano in un SECONDO vettore dinamico,
 * creato dalla funzione aumenti e restituito al chiamante: il risultato
 * non ha una lunghezza nota in anticipo, quindi un vettore che cresce è
 * la scelta naturale. Il chiamante lo stampa e poi lo distrugge.
 *
 * Il programma legge "mese prezzo" fino a FINE (prezzo maggiore di 0) e
 * stampa la tabella delle variazioni, i mesi di aumento con l'aumento
 * più forte e la variazione complessiva dal primo all'ultimo mese.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char mese[8];
    double prezzo;
} Rilevazione;

typedef struct {
    Rilevazione *dati;
    int n;
    int capacita;
} Storico;

Storico *crea_storico(int capacita);
int aggiungi(Storico *s, Rilevazione r);
int lunghezza(const Storico *s);
Rilevazione elemento(const Storico *s, int i);
void distruggi_storico(Storico *s);
double variazione(double prima, double dopo);
double variazione_mese(const Storico *s, int i);
Storico *aumenti(const Storico *s);

int main(void)
{
    Storico *storico = crea_storico(4);
    Storico *mesi_aumento = NULL;
    Rilevazione r;
    Rilevazione prima;
    Rilevazione ultima;
    int massimo;
    int letti;
    int finito = 0;
    int i;

    if (storico == NULL) {
        printf("Memoria insufficiente.\n");
        finito = 1;
    } else {
        printf("Mese e prezzo (FINE per terminare):\n");
    }
    while (!finito) {
        if (scanf("%7s", r.mese) != 1 || strcmp(r.mese, "FINE") == 0) {
            finito = 1;
        } else if ((letti = scanf("%lf", &r.prezzo)) != 1 || r.prezzo <= 0) {
            printf("  prezzo non valido per %s\n", r.mese);
            if (letti == 0) {
                scanf("%*s");
            }
        } else if (!aggiungi(storico, r)) {
            printf("Memoria insufficiente.\n");
            finito = 1;
        }
    }
    if (storico != NULL && lunghezza(storico) < 2) {
        printf("Servono almeno due mesi.\n");
    } else if (storico != NULL) {
        printf("\n%-6s %7s %9s\n", "Mese", "Prezzo", "Var. %");
        for (i = 0; i < lunghezza(storico); i++) {
            r = elemento(storico, i);
            printf("%-6s %7.2f", r.mese, r.prezzo);
            if (i > 0) {
                printf(" %+8.1f%%", variazione_mese(storico, i));
            }
            printf("\n");
        }

        mesi_aumento = aumenti(storico);
        if (mesi_aumento == NULL) {
            printf("Memoria insufficiente.\n");
        } else if (lunghezza(mesi_aumento) == 0) {
            printf("\nNessun aumento.\n");
        } else {
            printf("\nMesi con aumento: %d su %d\n", lunghezza(mesi_aumento),
                   lunghezza(storico) - 1);
            for (i = 0; i < lunghezza(mesi_aumento); i++) {
                printf("  %s\n", elemento(mesi_aumento, i).mese);
            }
            massimo = 1;
            for (i = 2; i < lunghezza(storico); i++) {
                if (variazione_mese(storico, i) > variazione_mese(storico, massimo)) {
                    massimo = i;
                }
            }
            printf("Aumento piu' forte: %s (%+.1f%%)\n", elemento(storico, massimo).mese,
                   variazione_mese(storico, massimo));
        }
        prima = elemento(storico, 0);
        ultima = elemento(storico, lunghezza(storico) - 1);
        printf("Complessivo %s-%s: %.2f -> %.2f euro (%+.1f%%)\n", prima.mese, ultima.mese,
               prima.prezzo, ultima.prezzo, variazione(prima.prezzo, ultima.prezzo));
    }
    distruggi_storico(mesi_aumento);
    distruggi_storico(storico);

    return 0;
}

Storico *crea_storico(int capacita)
{
    Storico *s = malloc(sizeof *s);

    if (s != NULL) {
        s->dati = malloc(capacita * sizeof *s->dati);
        if (s->dati == NULL) {
            free(s);
            s = NULL;
        } else {
            s->n = 0;
            s->capacita = capacita;
        }
    }
    return s;
}

int aggiungi(Storico *s, Rilevazione r)
{
    Rilevazione *tmp;
    int ok = 1;

    if (s->n == s->capacita) {
        tmp = realloc(s->dati, 2 * s->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            s->dati = tmp;
            s->capacita = 2 * s->capacita;
        }
    }
    if (ok) {
        s->dati[s->n] = r;
        s->n++;
    }
    return ok;
}

int lunghezza(const Storico *s)
{
    return s->n;
}

Rilevazione elemento(const Storico *s, int i)
{
    return s->dati[i];
}

void distruggi_storico(Storico *s)
{
    if (s != NULL) {
        free(s->dati);
        free(s);
    }
}

double variazione(double prima, double dopo)
{
    return (dopo - prima) / prima * 100;
}

/* Variazione del mese i (da 1 in poi) rispetto al mese prima. */
double variazione_mese(const Storico *s, int i)
{
    return variazione(elemento(s, i - 1).prezzo, elemento(s, i).prezzo);
}

/* Vettore nuovo con i mesi di aumento; NULL se manca memoria. */
Storico *aumenti(const Storico *s)
{
    Storico *risultato = crea_storico(2);
    int ok = risultato != NULL;
    int i;

    for (i = 1; i < lunghezza(s) && ok; i++) {
        if (elemento(s, i).prezzo > elemento(s, i - 1).prezzo) {
            ok = aggiungi(risultato, elemento(s, i));
        }
    }
    if (!ok) {
        distruggi_storico(risultato);
        risultato = NULL;
    }
    return risultato;
}
