/*
 * 070-problema-paghe-dipendenti.c
 *
 * Problema reale: calcolo delle paghe mensili dei dipendenti.
 *
 * Scenario: un'azienda ha 6 dipendenti. Il programma memorizza il nome,
 * le ore lavorate nel mese e la tariffa oraria di ciascuno, calcola
 * la paga lorda, identifica il dipendente più e meno pagato e confronta
 * ogni paga con la media aziendale.
 *
 * Concetti applicati:
 *  - tre array paralleli (nomi, ore, tariffe) e un array calcolato (paghe)
 *  - costruzione di un array di risultati da due array di input
 *  - ricerca di massimo e minimo su array calcolato
 *  - media e confronto
 */

#include <stdio.h>

#define DIPENDENTI 6

int main(void) {

    char   nomi[DIPENDENTI][20] = {
        "Rossi Anna",
        "Bianchi Carlo",
        "Verdi Elena",
        "Ferrari Marco",
        "Russo Giulia",
        "Conti Pietro"
    };
    int    ore[DIPENDENTI]      = {168, 152, 176, 160, 144, 168};
    double tariffe[DIPENDENTI]  = {12.50, 15.00, 11.80, 18.00, 13.20, 16.50};

    /* Array calcolato: paghe[i] = ore[i] * tariffe[i] */
    double paghe[DIPENDENTI];
    int    i;

    /* ------------------------------------------------------------------ */
    /* Calcolo delle paghe lorde */
    for (i = 0; i < DIPENDENTI; i++) {
        paghe[i] = ore[i] * tariffe[i];
    }

    /* ------------------------------------------------------------------ */
    /* Stampa del prospetto paghe */
    printf("=======================================================\n");
    printf("              PROSPETTO PAGHE MENSILI                  \n");
    printf("=======================================================\n");
    printf("  %-16s | Ore  | Tariffa | Paga lorda\n", "Dipendente");
    printf("  -----------------|------|---------|------------\n");

    for (i = 0; i < DIPENDENTI; i++) {
        printf("  %-16s | %3d  | %6.2f€ | %9.2f€\n",
               nomi[i], ore[i], tariffe[i], paghe[i]);
    }
    printf("=======================================================\n\n");

    /* ------------------------------------------------------------------ */
    /* Totale costo aziendale e paga media */
    double totale = 0.0;
    for (i = 0; i < DIPENDENTI; i++) {
        totale = totale + paghe[i];
    }
    double media = totale / DIPENDENTI;

    printf("Totale costo aziendale : %.2f€\n", totale);
    printf("Paga media mensile     : %.2f€\n\n", media);

    /* ------------------------------------------------------------------ */
    /* Dipendente più e meno pagato */
    int indice_max = 0;
    int indice_min = 0;

    for (i = 1; i < DIPENDENTI; i++) {
        if (paghe[i] > paghe[indice_max]) {
            indice_max = i;
        }
        if (paghe[i] < paghe[indice_min]) {
            indice_min = i;
        }
    }

    printf("Paga piu' alta  : %s (%.2f€)\n", nomi[indice_max], paghe[indice_max]);
    printf("Paga piu' bassa : %s (%.2f€)\n\n", nomi[indice_min], paghe[indice_min]);

    /* ------------------------------------------------------------------ */
    /* Confronto con la media: sopra, sotto o nella media */
    printf("Confronto con la media (%.2f€):\n", media);
    for (i = 0; i < DIPENDENTI; i++) {
        double diff = paghe[i] - media;
        if (diff > 0.0) {
            printf("  %-16s : +%.2f€ sopra la media\n", nomi[i], diff);
        } else if (diff < 0.0) {
            printf("  %-16s : %.2f€ sotto la media\n", nomi[i], diff);
        } else {
            printf("  %-16s : nella media\n", nomi[i]);
        }
    }

    return 0;
}
