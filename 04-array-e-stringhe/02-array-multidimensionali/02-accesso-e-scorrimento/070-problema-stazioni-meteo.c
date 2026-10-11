/*
 * 070-problema-stazioni-meteo.c
 *
 * Pioggia rilevata da una rete di stazioni meteo
 *
 * Quattro stazioni della provincia misurano la pioggia caduta (in mm)
 * in sei intervalli di 4 ore (00-04, 04-08, ..., 20-24). Il programma:
 *   - stampa la tabella con il totale giornaliero di ogni stazione;
 *   - per ogni stazione indica l'intervallo più piovoso;
 *   - trova l'intervallo con la pioggia media più alta sulla rete;
 *   - permette di interrogare una singola misura scegliendo stazione e
 *     intervallo da tastiera (indici validati), finché l'utente
 *     inserisce 0 come stazione.
 *
 * Struttura dati:
 *   double pioggia[STAZIONI][INTERVALLI]
 *   char stazioni[STAZIONI][LUNG]   nomi, paralleli alle righe
 *   La sigla dell'intervallo si calcola dall'indice: inizio = i * 4.
 */

#include <stdio.h>

#define STAZIONI   4
#define INTERVALLI 6
#define ORE_INTERVALLO 4
#define LUNG 16

int main(void)
{
    double pioggia[STAZIONI][INTERVALLI] = {
        {0.0, 1.2, 4.8, 6.5, 2.0, 0.4},
        {0.2, 0.8, 3.5, 9.1, 3.3, 1.0},
        {0.0, 0.3, 2.9, 2.1, 0.9, 0.0},
        {1.1, 2.4, 7.2, 12.6, 5.8, 2.2}
    };
    char stazioni[STAZIONI][LUNG] = {
        "Alessandria", "Acqui Terme", "Casale", "Ovada"
    };

    int st;
    int in;
    int in_max;
    double totale;
    double media;
    double media_max = 0.0;
    int in_media_max = 0;
    int scelta_stazione;
    int scelta_intervallo;

    /* ── 1. Tabella con totale e intervallo più piovoso ───────────── */
    printf("=== PIOGGIA DEL 14 OTTOBRE (mm) ===\n\n");
    printf("  %-13s", "Stazione");
    for (in = 0; in < INTERVALLI; in++) {
        printf("  %02d-%02d", in * ORE_INTERVALLO, (in + 1) * ORE_INTERVALLO);
    }
    printf("  Totale  Picco\n");

    for (st = 0; st < STAZIONI; st++) {
        totale = 0.0;
        in_max = 0;
        printf("  %-13s", stazioni[st]);
        for (in = 0; in < INTERVALLI; in++) {
            printf("%7.1f", pioggia[st][in]);
            totale = totale + pioggia[st][in];
            if (pioggia[st][in] > pioggia[st][in_max]) {
                in_max = in;
            }
        }
        printf("%8.1f  %02d-%02d\n", totale,
               in_max * ORE_INTERVALLO, (in_max + 1) * ORE_INTERVALLO);
    }

    /* ── 2. Intervallo più piovoso in media (per colonne) ─────────── */
    for (in = 0; in < INTERVALLI; in++) {
        totale = 0.0;
        for (st = 0; st < STAZIONI; st++) {
            totale = totale + pioggia[st][in];
        }
        media = totale / STAZIONI;
        if (in == 0 || media > media_max) {
            media_max = media;
            in_media_max = in;
        }
    }
    printf("\nIntervallo piu' piovoso sulla rete: %02d-%02d (media %.2f mm)\n\n",
           in_media_max * ORE_INTERVALLO, (in_media_max + 1) * ORE_INTERVALLO,
           media_max);

    /* ── 3. Interrogazione di una singola misura ──────────────────────
     * Stazione e intervallo si inseriscono numerati da 1; gli indici
     * vengono verificati prima dell'accesso alla matrice.             */
    printf("Consultazione (stazione 0 per terminare)\n");
    printf("Stazione (1-%d): ", STAZIONI);
    scanf("%d", &scelta_stazione);

    while (scelta_stazione != 0) {
        printf("Intervallo (1-%d): ", INTERVALLI);
        scanf("%d", &scelta_intervallo);

        st = scelta_stazione - 1;
        in = scelta_intervallo - 1;

        if (st >= 0 && st < STAZIONI && in >= 0 && in < INTERVALLI) {
            printf("  %s, %02d-%02d: %.1f mm\n", stazioni[st],
                   in * ORE_INTERVALLO, (in + 1) * ORE_INTERVALLO, pioggia[st][in]);
        } else {
            printf("  Stazione o intervallo inesistente.\n");
        }

        printf("Stazione (1-%d): ", STAZIONI);
        scanf("%d", &scelta_stazione);
    }

    return 0;
}
