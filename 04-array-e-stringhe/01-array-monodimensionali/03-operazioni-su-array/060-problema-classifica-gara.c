/*
 * 060-problema-classifica-gara.c
 *
 * Problema reale: classifica di una gara sportiva.
 *
 * Scenario: 8 atleti partecipano a una gara di corsa. Il programma
 * memorizza i nomi e i tempi in secondi, stampa la classifica con
 * il distacco dal primo, calcola il tempo medio e conta gli atleti
 * sotto la media.
 *
 * Concetti applicati:
 *  - array paralleli (nomi e tempi)
 *  - ricerca del minimo come riferimento per i distacchi
 *  - calcolo di media e confronto per classificazione
 */

#include <stdio.h>

#define ATLETI 8

int main(void) {

    char nomi[ATLETI][20] = {
        "Rossi Marco",
        "Bianchi Luca",
        "Verdi Paolo",
        "Ferrari Giorgio",
        "Russo Andrea",
        "Conti Matteo",
        "Marino Fabio",
        "Greco Simone"
    };

    /* Tempi in secondi (es. 183 = 3 minuti e 3 secondi) */
    int tempi[ATLETI] = {183, 197, 175, 202, 191, 178, 209, 186};

    int i;

    /* ------------------------------------------------------------------ */
    /* Ricerca del tempo minimo (vincitore) */
    int indice_vincitore = 0;
    for (i = 1; i < ATLETI; i++) {
        if (tempi[i] < tempi[indice_vincitore]) {
            indice_vincitore = i;
        }
    }

    /* ------------------------------------------------------------------ */
    /* Stampa della classifica con distacco dal vincitore */
    printf("=== CLASSIFICA GARA ===\n");
    printf("  Pos. | Nome                | Tempo       | Distacco\n");
    printf("  -----|---------------------|-------------|----------\n");

    for (i = 0; i < ATLETI; i++) {
        int minuti  = tempi[i] / 60;
        int secondi = tempi[i] % 60;
        int distacco = tempi[i] - tempi[indice_vincitore];

        if (i == indice_vincitore) {
            printf("   1°  | %-19s | %d'%02d\"       | --\n",
                   nomi[i], minuti, secondi);
        } else {
            printf("    -  | %-19s | %d'%02d\"       | +%d\"\n",
                   nomi[i], minuti, secondi, distacco);
        }
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Calcolo della media dei tempi */
    int somma = 0;
    for (i = 0; i < ATLETI; i++) {
        somma = somma + tempi[i];
    }
    double media = (double)somma / ATLETI;

    printf("Tempo medio         : %.1f secondi\n", media);
    printf("Vincitore           : %s (%d\")\n\n",
           nomi[indice_vincitore], tempi[indice_vincitore]);

    /* ------------------------------------------------------------------ */
    /* Atleti con tempo sotto la media (più veloci della media) */
    int sotto_media = 0;
    printf("Atleti sotto la media (piu' veloci di %.1f\"):\n", media);

    for (i = 0; i < ATLETI; i++) {
        if ((double)tempi[i] < media) {
            printf("  %s: %d\"  (-%.1f\" dalla media)\n",
                   nomi[i], tempi[i], media - tempi[i]);
            sotto_media++;
        }
    }
    printf("Totale: %d atleti su %d\n", sotto_media, ATLETI);

    return 0;
}
