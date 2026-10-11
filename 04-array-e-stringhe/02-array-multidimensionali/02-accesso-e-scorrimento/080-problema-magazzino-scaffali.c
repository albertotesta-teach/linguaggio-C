/*
 * 080-problema-magazzino-scaffali.c
 *
 * Magazzino a scaffali: giacenze e prelievi
 *
 * Un magazzino di ricambi ha 4 scaffali, ciascuno con 5 ripiani. Ogni
 * ripiano contiene un solo articolo; la matrice memorizza la quantità
 * presente. Ogni scaffale ha un codice (es. "SC-A") e una scorta minima
 * sotto la quale i suoi ripiani vanno riforniti.
 *
 * Il programma:
 *   - stampa la situazione con il totale di ogni scaffale;
 *   - elenca i ripiani sotto la scorta minima del loro scaffale;
 *   - registra una serie di prelievi letti da tastiera (scaffale, ripiano,
 *     quantità), rifiutando quelli non validi o superiori alla giacenza;
 *     la serie termina con scaffale 0;
 *   - stampa i pezzi prelevati in totale.
 *
 * Struttura dati:
 *   int quantita[SCAFFALI][RIPIANI]
 *   char codici[SCAFFALI][6]      paralleli alle righe
 *   int scorta_minima[SCAFFALI]   paralleli alle righe
 */

#include <stdio.h>

#define SCAFFALI 4
#define RIPIANI  5

int main(void)
{
    int quantita[SCAFFALI][RIPIANI] = {
        {40, 12, 35,  8, 50},
        {15, 22,  4, 30, 18},
        {60, 55, 70,  9, 65},
        { 5, 10, 14, 20,  3}
    };
    char codici[SCAFFALI][6] = {"SC-A", "SC-B", "SC-C", "SC-D"};
    int scorta_minima[SCAFFALI] = {10, 10, 20, 6};

    int sc;
    int rp;
    int totale;
    int sotto_scorta = 0;
    int scelta_scaffale;
    int scelta_ripiano;
    int pezzi;
    int prelevati = 0;

    /* ── 1. Situazione del magazzino ──────────────────────────────── */
    printf("=== MAGAZZINO RICAMBI ===\n\n");
    printf("  Scaffale  Rip.1 Rip.2 Rip.3 Rip.4 Rip.5  Totale  Scorta min.\n");
    for (sc = 0; sc < SCAFFALI; sc++) {
        totale = 0;
        printf("  %-8s", codici[sc]);
        for (rp = 0; rp < RIPIANI; rp++) {
            printf("%6d", quantita[sc][rp]);
            totale = totale + quantita[sc][rp];
        }
        printf("%8d%13d\n", totale, scorta_minima[sc]);
    }

    /* ── 2. Ripiani da rifornire ──────────────────────────────────────
     * Il confronto usa la soglia della RIGA: scorta_minima[sc].        */
    printf("\n--- Ripiani sotto la scorta minima ---\n");
    for (sc = 0; sc < SCAFFALI; sc++) {
        for (rp = 0; rp < RIPIANI; rp++) {
            if (quantita[sc][rp] < scorta_minima[sc]) {
                printf("  %s ripiano %d: %d pezzi (minimo %d)\n",
                       codici[sc], rp + 1, quantita[sc][rp], scorta_minima[sc]);
                sotto_scorta++;
            }
        }
    }
    printf("  Totale ripiani da rifornire: %d\n\n", sotto_scorta);

    /* ── 3. Prelievi ──────────────────────────────────────────────── */
    printf("Registrazione prelievi (scaffale 0 per terminare)\n");
    printf("Scaffale (1-%d): ", SCAFFALI);
    scanf("%d", &scelta_scaffale);

    while (scelta_scaffale != 0) {
        printf("Ripiano (1-%d): ", RIPIANI);
        scanf("%d", &scelta_ripiano);
        printf("Pezzi da prelevare: ");
        scanf("%d", &pezzi);

        sc = scelta_scaffale - 1;
        rp = scelta_ripiano - 1;

        if (sc < 0 || sc >= SCAFFALI || rp < 0 || rp >= RIPIANI) {
            printf("  Posizione inesistente.\n");
        } else if (pezzi <= 0) {
            printf("  Quantita' non valida.\n");
        } else if (pezzi > quantita[sc][rp]) {
            printf("  Giacenza insufficiente: disponibili %d.\n", quantita[sc][rp]);
        } else {
            quantita[sc][rp] = quantita[sc][rp] - pezzi;
            prelevati = prelevati + pezzi;
            printf("  Prelievo registrato: %s ripiano %d, rimasti %d",
                   codici[sc], rp + 1, quantita[sc][rp]);
            if (quantita[sc][rp] < scorta_minima[sc]) {
                printf(" (sotto scorta!)");
            }
            printf("\n");
        }

        printf("Scaffale (1-%d): ", SCAFFALI);
        scanf("%d", &scelta_scaffale);
    }

    printf("\nPezzi prelevati in totale: %d\n", prelevati);

    return 0;
}
