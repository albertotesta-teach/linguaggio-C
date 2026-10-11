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
 *  - costruzione dell'ordine di arrivo con ricerca ripetuta del minimo
 *    (array di indici + array di flag), senza algoritmi di ordinamento
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

    /* ordine[p] = indice dell'atleta arrivato in posizione p+1.
     * classificato[i] = 1 se l'atleta i è già stato inserito in ordine[]. */
    int ordine[ATLETI];
    int classificato[ATLETI] = {0};

    int i;
    int pos;

    /* ------------------------------------------------------------------ */
    /* Costruzione dell'ordine di arrivo.
     * A ogni passo si cerca il tempo minimo tra gli atleti non ancora
     * classificati: è l'atleta che occupa la posizione successiva.
     * È la stessa idea della ricerca del minimo, ripetuta ATLETI volte. */
    for (pos = 0; pos < ATLETI; pos++) {
        int migliore = -1;   /* nessun candidato ancora trovato */

        for (i = 0; i < ATLETI; i++) {
            if (!classificato[i]) {
                if (migliore == -1 || tempi[i] < tempi[migliore]) {
                    migliore = i;
                }
            }
        }

        ordine[pos] = migliore;
        classificato[migliore] = 1;   /* escluso dalle ricerche successive */
    }

    /* Il vincitore è il primo dell'ordine di arrivo */
    int indice_vincitore = ordine[0];

    /* ------------------------------------------------------------------ */
    /* Stampa della classifica con distacco dal vincitore */
    printf("=== CLASSIFICA GARA ===\n");
    printf("  Pos. | Nome                | Tempo       | Distacco\n");
    printf("  -----|---------------------|-------------|----------\n");

    for (pos = 0; pos < ATLETI; pos++) {
        int atleta   = ordine[pos];
        int minuti   = tempi[atleta] / 60;
        int secondi  = tempi[atleta] % 60;
        int distacco = tempi[atleta] - tempi[indice_vincitore];

        if (pos == 0) {
            printf("   %d°  | %-19s | %d'%02d\"       | --\n",
                   pos + 1, nomi[atleta], minuti, secondi);
        } else {
            printf("   %d°  | %-19s | %d'%02d\"       | +%d\"\n",
                   pos + 1, nomi[atleta], minuti, secondi, distacco);
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
    /* Atleti con tempo sotto la media (più veloci della media),
     * elencati in ordine di arrivo scorrendo ordine[] */
    int sotto_media = 0;
    printf("Atleti sotto la media (piu' veloci di %.1f\"):\n", media);

    for (pos = 0; pos < ATLETI; pos++) {
        int atleta = ordine[pos];
        if ((double)tempi[atleta] < media) {
            printf("  %s: %d\"  (-%.1f\" dalla media)\n",
                   nomi[atleta], tempi[atleta], media - tempi[atleta]);
            sotto_media++;
        }
    }
    printf("Totale: %d atleti su %d\n", sotto_media, ATLETI);

    return 0;
}
