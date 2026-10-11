/*
 * 070-problema-inventario-negozi.c
 *
 * Inventario di una catena di negozi e trasferimenti di merce
 *
 * Una catena di 4 negozi di articoli sportivi vende 5 prodotti. La matrice
 * giacenze[NEGOZI][PRODOTTI] contiene i pezzi disponibili. Per ogni
 * prodotto è fissata una scorta minima per negozio (array parallelo alle
 * COLONNE).
 *
 * Il programma:
 *   - stampa l'inventario con il totale di ogni prodotto nella catena;
 *   - elenca, per ogni negozio, i prodotti sotto la scorta minima;
 *   - per ogni prodotto sotto scorta propone un trasferimento dal negozio
 *     che ne ha di più, ed esegue il trasferimento solo se il negozio di
 *     partenza resta almeno alla scorta minima;
 *   - stampa l'inventario aggiornato.
 *
 * Funzioni:
 *   totale_prodotto(g, p)                  somma della colonna p
 *   negozio_piu_fornito(g, p)              indice della riga con il massimo
 *                                          nella colonna p
 *   trasferisci(g, da, a, p, pezzi, minimo) sposta pezzi se possibile;
 *                                          restituisce 1 se eseguito
 *   stampa_inventario(g, negozi, prodotti)
 */

#include <stdio.h>

#define NEGOZI   4
#define PRODOTTI 5
#define LUNG     14

int totale_prodotto(const int g[][PRODOTTI], int p);
int negozio_piu_fornito(const int g[][PRODOTTI], int p);
int trasferisci(int g[][PRODOTTI], int da, int a, int p, int pezzi, int minimo);
void stampa_inventario(const int g[][PRODOTTI],
                       const char negozi[][LUNG], const char prodotti[][LUNG]);

int main(void)
{
    int giacenze[NEGOZI][PRODOTTI] = {
        {12,  3, 25,  8, 40},
        { 2, 15, 30, 12, 35},
        { 9,  6,  4, 10, 18},
        {20,  1, 18,  3, 50}
    };
    char negozi[NEGOZI][LUNG] = {"Alessandria", "Novi", "Tortona", "Acqui"};
    char prodotti[PRODOTTI][LUNG] = {"Palloni", "Racchette", "Borracce", "Zaini", "Calze"};
    int scorta_minima[PRODOTTI] = {5, 4, 8, 5, 15};

    int n;
    int p;
    int fornitore;
    int mancanti;

    printf("=== INVENTARIO INIZIALE ===\n");
    stampa_inventario(giacenze, negozi, prodotti);

    printf("\n=== RIASSORTIMENTO ===\n");
    for (n = 0; n < NEGOZI; n++) {
        for (p = 0; p < PRODOTTI; p++) {
            if (giacenze[n][p] < scorta_minima[p]) {
                mancanti = scorta_minima[p] - giacenze[n][p];
                fornitore = negozio_piu_fornito(giacenze, p);

                printf("%s: %s sotto scorta (%d, minimo %d). ",
                       negozi[n], prodotti[p], giacenze[n][p], scorta_minima[p]);

                if (fornitore != n
                    && trasferisci(giacenze, fornitore, n, p, mancanti, scorta_minima[p])) {
                    printf("Trasferiti %d da %s.\n", mancanti, negozi[fornitore]);
                } else {
                    printf("Nessun negozio puo' cederli: da ordinare.\n");
                }
            }
        }
    }

    printf("\n=== INVENTARIO AGGIORNATO ===\n");
    stampa_inventario(giacenze, negozi, prodotti);

    return 0;
}

/* Somma della colonna p: pezzi del prodotto p in tutta la catena. */
int totale_prodotto(const int g[][PRODOTTI], int p)
{
    int n;
    int totale = 0;

    for (n = 0; n < NEGOZI; n++) {
        totale = totale + g[n][p];
    }
    return totale;
}

/* Indice del negozio con più pezzi del prodotto p (massimo di colonna). */
int negozio_piu_fornito(const int g[][PRODOTTI], int p)
{
    int n;
    int migliore = 0;

    for (n = 1; n < NEGOZI; n++) {
        if (g[n][p] > g[migliore][p]) {
            migliore = n;
        }
    }
    return migliore;
}

/* Sposta "pezzi" del prodotto p dal negozio da al negozio a, solo se al
 * negozio da restano almeno "minimo" pezzi. Restituisce 1 se il
 * trasferimento è avvenuto, 0 altrimenti (matrice invariata). */
int trasferisci(int g[][PRODOTTI], int da, int a, int p, int pezzi, int minimo)
{
    int eseguito = 0;

    if (g[da][p] - pezzi >= minimo) {
        g[da][p] = g[da][p] - pezzi;
        g[a][p] = g[a][p] + pezzi;
        eseguito = 1;
    }
    return eseguito;
}

void stampa_inventario(const int g[][PRODOTTI],
                       const char negozi[][LUNG], const char prodotti[][LUNG])
{
    int n;
    int p;

    printf("  %-12s", "Negozio");
    for (p = 0; p < PRODOTTI; p++) {
        printf("%11s", prodotti[p]);
    }
    printf("\n");

    for (n = 0; n < NEGOZI; n++) {
        printf("  %-12s", negozi[n]);
        for (p = 0; p < PRODOTTI; p++) {
            printf("%11d", g[n][p]);
        }
        printf("\n");
    }

    printf("  %-12s", "Totale");
    for (p = 0; p < PRODOTTI; p++) {
        printf("%11d", totale_prodotto(g, p));
    }
    printf("\n");
}

/*
 * NOTA: anche gli elenchi di nomi sono matrici di caratteri, quindi nel
 * parametro va indicata la seconda dimensione: const char negozi[][LUNG].
 */
