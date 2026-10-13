/*
 * 080-problema-risultati-misure.c
 *
 * Laboratorio di fisica: una misura può riuscire, uscire di scala o
 * segnalare un guasto
 *
 * Il voltmetro collegato al PC restituisce un valore grezzo. Una
 * funzione lo trasforma in un risultato con tre esiti possibili, ognuno
 * con i suoi dati:
 *   - MISURA_OK: valore e incertezza (1% del valore più 0.01 V);
 *   - FUORI_SCALA: il fondo scala superato, per scegliere una portata più
 *     alta;
 *   - GUASTO: un codice di errore (letture negative: -1 cavo staccato,
 *     -2 batteria scarica, altri valori errore sconosciuto).
 *
 *     typedef struct {
 *         Esito esito;
 *         union {
 *             struct {
 *                 double valore;
 *                 double incertezza;
 *             } ok;
 *             double fondo_scala;
 *             int codice;
 *         } dati;
 *     } Risultato;
 *
 *     Risultato misura(double letto, double fondo_scala);
 *
 * Il programma legge il fondo scala (in volt) e poi le letture fino a
 * FINE; alla fine stampa la media delle sole misure riuscite e il
 * numero di letture per ogni esito.
 */

#include <stdio.h>
#include <string.h>

#define LUNG 16

typedef enum {
    MISURA_OK, FUORI_SCALA, GUASTO, NUM_ESITI
} Esito;

typedef struct {
    Esito esito;
    union {
        struct {
            double valore;
            double incertezza;
        } ok;
        double fondo_scala;
        int codice;
    } dati;
} Risultato;

Risultato misura(double letto, double fondo_scala);
void stampa(const Risultato *r);

int main(void)
{
    int conteggi[NUM_ESITI] = {0};
    char parola[LUNG];
    double fondo_scala;
    double letto;
    double somma = 0;
    Risultato r;
    int finito = 0;

    printf("Fondo scala (V): ");
    if (scanf("%lf", &fondo_scala) != 1 || fondo_scala <= 0) {
        printf("Fondo scala non valido.\n");
        finito = 1;
    }
    while (!finito) {
        printf("Lettura (FINE): ");
        if (scanf("%15s", parola) != 1 || strcmp(parola, "FINE") == 0) {
            finito = 1;
        } else if (sscanf(parola, "%lf", &letto) != 1) {
            printf("  Non e' un numero.\n");
        } else {
            r = misura(letto, fondo_scala);
            stampa(&r);
            conteggi[r.esito]++;
            if (r.esito == MISURA_OK) {
                somma = somma + r.dati.ok.valore;
            }
        }
    }

    if (conteggi[MISURA_OK] > 0) {
        printf("Media delle misure riuscite: %.3f V\n", somma / conteggi[MISURA_OK]);
    }
    printf("Riuscite %d, fuori scala %d, guasti %d\n", conteggi[MISURA_OK], conteggi[FUORI_SCALA],
           conteggi[GUASTO]);

    return 0;
}

Risultato misura(double letto, double fondo_scala)
{
    Risultato r;

    if (letto < 0) {
        r.esito = GUASTO;
        r.dati.codice = (int) letto;
    } else if (letto > fondo_scala) {
        r.esito = FUORI_SCALA;
        r.dati.fondo_scala = fondo_scala;
    } else {
        r.esito = MISURA_OK;
        r.dati.ok.valore = letto;
        r.dati.ok.incertezza = letto * 0.01 + 0.01;
    }
    return r;
}

void stampa(const Risultato *r)
{
    switch (r->esito) {
    case MISURA_OK:
        printf("  (%.3f +/- %.3f) V\n", r->dati.ok.valore, r->dati.ok.incertezza);
        break;
    case FUORI_SCALA:
        printf("  Fuori scala: oltre %.1f V, scegliere una portata piu' alta.\n",
               r->dati.fondo_scala);
        break;
    case GUASTO:
        printf("  Guasto: %s (codice %d)\n",
               r->dati.codice == -1   ? "cavo staccato"
               : r->dati.codice == -2 ? "batteria scarica"
                                      : "errore sconosciuto",
               r->dati.codice);
        break;
    case NUM_ESITI:
        break;
    }
}
