/*
 * 060-problema-noleggio-bici.c
 *
 * Bike sharing comunale: noleggio e restituzione con la tessera studenti
 *
 * Il comune mette a disposizione degli studenti alcune bici. Ogni bici ha
 * un codice, lo stato (libera o noleggiata), la tessera di chi la usa,
 * l'ora di inizio del noleggio e i minuti totali di utilizzo:
 *
 *     typedef struct {
 *         char codice[6];
 *         int noleggiata;
 *         int tessera;
 *         int inizio;              minuti dalla mezzanotte
 *         int minuti_totali;
 *     } Bici;
 *
 *     Bici *prima_libera(Bici b[], int n);
 *     Bici *bici_di(Bici b[], int n, int tessera);
 *     int noleggia(Bici *b, int tessera, int ora);
 *     int restituisci(Bici *b, int ora);         restituisce i minuti di uso
 *
 * Le funzioni di ricerca restituiscono il puntatore all'elemento (o NULL);
 * noleggia e restituisci lavorano su UNA bici tramite il suo indirizzo.
 * Una tessera può avere una sola bici alla volta. Il costo è gratuito per
 * i primi 30 minuti, poi 0.50 euro ogni 30 minuti iniziati.
 *
 * Comandi: N tessera hh:mm, R tessera hh:mm, S (stato), Q.
 */

#include <stdio.h>

#define BICI 4
#define GRATIS 30

typedef struct {
    char codice[6];
    int noleggiata;
    int tessera;
    int inizio;
    int minuti_totali;
} Bici;

Bici *prima_libera(Bici b[], int n);
Bici *bici_di(Bici b[], int n, int tessera);
int noleggia(Bici *b, int tessera, int ora);
int restituisci(Bici *b, int ora);
double costo(int minuti);

int main(void)
{
    Bici parco[BICI] = {
        {"B-01", 0, 0, 0, 0},
        {"B-02", 0, 0, 0, 0},
        {"B-03", 0, 0, 0, 0},
        {"B-04", 0, 0, 0, 0}
    };
    char comando = ' ';
    int tessera;
    int ore;
    int minuti;
    int uso;
    Bici *bici;
    int i;

    while (comando != 'Q') {
        printf("Comando (N tessera hh:mm, R tessera hh:mm, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'N' || comando == 'R') {
            if (scanf("%d %d:%d", &tessera, &ore, &minuti) != 3) {
                comando = 'Q';
            } else if (comando == 'N') {
                if (bici_di(parco, BICI, tessera) != NULL) {
                    printf("  La tessera %d ha gia' una bici.\n", tessera);
                } else {
                    bici = prima_libera(parco, BICI);
                    if (bici == NULL) {
                        printf("  Nessuna bici libera.\n");
                    } else if (noleggia(bici, tessera, ore * 60 + minuti)) {
                        printf("  Bici %s alla tessera %d.\n", bici->codice, tessera);
                    }
                }
            } else {
                bici = bici_di(parco, BICI, tessera);
                if (bici == NULL) {
                    printf("  La tessera %d non ha bici.\n", tessera);
                } else {
                    uso = restituisci(bici, ore * 60 + minuti);
                    if (uso < 0) {
                        printf("  Orario precedente all'inizio del noleggio.\n");
                    } else {
                        printf("  Bici %s restituita: %d minuti, %.2f euro.\n", bici->codice, uso,
                               costo(uso));
                    }
                }
            }
        } else if (comando == 'S') {
            for (i = 0; i < BICI; i++) {
                printf("  %s  %-10s uso totale %d min\n", parco[i].codice,
                       parco[i].noleggiata ? "noleggiata" : "libera", parco[i].minuti_totali);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}

Bici *prima_libera(Bici b[], int n)
{
    Bici *trovata = NULL;
    int i = 0;

    while (i < n && trovata == NULL) {
        if (!b[i].noleggiata) {
            trovata = &b[i];
        }
        i++;
    }
    return trovata;
}

Bici *bici_di(Bici b[], int n, int tessera)
{
    Bici *trovata = NULL;
    int i = 0;

    while (i < n && trovata == NULL) {
        if (b[i].noleggiata && b[i].tessera == tessera) {
            trovata = &b[i];
        }
        i++;
    }
    return trovata;
}

int noleggia(Bici *b, int tessera, int ora)
{
    int riuscito = !b->noleggiata;

    if (riuscito) {
        b->noleggiata = 1;
        b->tessera = tessera;
        b->inizio = ora;
    }
    return riuscito;
}

/* Minuti di utilizzo, oppure -1 se l'ora è precedente all'inizio. */
int restituisci(Bici *b, int ora)
{
    int uso = ora - b->inizio;

    if (uso >= 0) {
        b->noleggiata = 0;
        b->minuti_totali = b->minuti_totali + uso;
    }
    return uso;
}

/* Gratis i primi 30 minuti, poi 0.50 euro per ogni mezz'ora iniziata. */
double costo(int minuti)
{
    double euro = 0;

    if (minuti > GRATIS) {
        euro = 0.50 * ((minuti - GRATIS + 29) / 30);
    }
    return euro;
}
