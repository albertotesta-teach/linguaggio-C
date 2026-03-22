/*
 * 070-problema-analisi-partita.c
 *
 * Problema reale: analisi statistica dei marcatori di una squadra.
 *
 * Scenario: una squadra di calcio ha 8 giocatori. Il programma memorizza
 * nome e gol segnati nella stagione e organizza tutta l'elaborazione
 * in funzioni riusabili: totale gol, media, capocannoniere, classifica
 * marcatori. Il main si occupa solo di coordinare e presentare.
 *
 * Concetti applicati:
 *  - funzioni che restituiscono valori aggregati (totale, media, indice)
 *  - funzione di stampa che riceve array paralleli
 *  - riuso di funzioni: stampa_classifica usa indice_massimo internamente
 */

#include <stdio.h>

#define GIOCATORI 8

/* Restituisce il totale dei gol segnati dalla squadra */
int totale_gol(const int gol[], int n) {
    int i;
    int tot = 0;
    for (i = 0; i < n; i++) {
        tot = tot + gol[i];
    }
    return tot;
}

/* Restituisce la media gol per giocatore */
double media_gol(const int gol[], int n) {
    return (double)totale_gol(gol, n) / n;
}

/* Restituisce l'indice del capocannoniere (gol massimo) */
int capocannoniere(const int gol[], int n) {
    int i;
    int idx = 0;
    for (i = 1; i < n; i++) {
        if (gol[i] > gol[idx]) {
            idx = i;
        }
    }
    return idx;
}

/* Conta i giocatori con gol > soglia */
int conta_sopra_soglia(const int gol[], int n, int soglia) {
    int i;
    int contatore = 0;
    for (i = 0; i < n; i++) {
        if (gol[i] > soglia) {
            contatore++;
        }
    }
    return contatore;
}

/* Stampa la classifica marcatori in ordine decrescente (top-k).
 * Usa la tecnica della ricerca ripetuta del massimo con array selezionato[]. */
void stampa_classifica(const char nomi[][20], const int gol[], int n, int k) {
    int selezionato[GIOCATORI];
    int i;
    int j;
    int idx_max;

    /* Inizializza i flag a 0 */
    for (i = 0; i < n; i++) {
        selezionato[i] = 0;
    }

    printf("  Pos. | Giocatore          | Gol\n");
    printf("  -----|--------------------|---------\n");

    for (j = 1; j <= k; j++) {
        idx_max = -1;
        for (i = 0; i < n; i++) {
            if (!selezionato[i]) {
                if (idx_max == -1 || gol[i] > gol[idx_max]) {
                    idx_max = i;
                }
            }
        }
        selezionato[idx_max] = 1;
        printf("   %2d  | %-18s | %3d\n", j, nomi[idx_max], gol[idx_max]);
    }
}

int main(void) {

    char nomi[GIOCATORI][20] = {
        "Rossi Marco",
        "Bianchi Luca",
        "Verdi Paolo",
        "Ferrari Giorgio",
        "Russo Andrea",
        "Conti Matteo",
        "Marino Fabio",
        "Greco Simone"
    };
    int gol[GIOCATORI] = {12, 7, 15, 3, 9, 11, 4, 8};

    int idx;

    printf("=== ANALISI MARCATORI STAGIONE ===\n\n");

    idx = capocannoniere(gol, GIOCATORI);
    printf("Capocannoniere      : %s (%d gol)\n", nomi[idx], gol[idx]);
    printf("Totale gol squadra  : %d\n", totale_gol(gol, GIOCATORI));
    printf("Media per giocatore : %.1f\n", media_gol(gol, GIOCATORI));
    printf("Giocatori > 8 gol   : %d su %d\n\n",
           conta_sopra_soglia(gol, GIOCATORI, 8), GIOCATORI);

    printf("--- Classifica marcatori (top 5) ---\n");
    stampa_classifica(nomi, gol, GIOCATORI, 5);

    return 0;
}
