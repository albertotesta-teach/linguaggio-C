/*
 * 060-problema-campionato.c
 *
 * Classifica di un torneo di calcio a 5
 *
 * Sei squadre giocano un torneo; dopo 5 giornate la matrice punti
 * contiene i punti ottenuti da ogni squadra in ogni giornata
 * (3 = vittoria, 1 = pareggio, 0 = sconfitta). Il programma:
 *   - stampa il prospetto con i risultati (V, P, S) e il totale punti;
 *   - stampa la classifica in ordine di punti, costruita con la ricerca
 *     ripetuta del massimo tra le squadre non ancora classificate;
 *   - indica le squadre imbattute (nessuna sconfitta);
 *   - per ogni giornata conta le vittorie e i pareggi.
 *
 * Struttura dati:
 *   int punti[SQUADRE][GIORNATE]
 *   char squadre[SQUADRE][LUNG]   nomi, paralleli alle righe
 *   int totale[SQUADRE]           calcolato: totale punti per squadra
 *   int classificata[SQUADRE]     flag per la costruzione della classifica
 */

#include <stdio.h>

#define SQUADRE  6
#define GIORNATE 5
#define LUNG     16

#define VITTORIA  3
#define PAREGGIO  1
#define SCONFITTA 0

int main(void)
{
    int punti[SQUADRE][GIORNATE] = {
        {3, 1, 3, 0, 3},
        {1, 1, 3, 3, 0},
        {0, 3, 0, 1, 0},
        {3, 3, 1, 3, 3},
        {0, 0, 1, 0, 3},
        {1, 0, 0, 1, 0}
    };
    char squadre[SQUADRE][LUNG] = {
        "Atletico Volta", "Real Tortona", "Sporting Novi",
        "Dinamo Acqui", "Olimpia Ovada", "Union Casale"
    };
    int totale[SQUADRE];
    int classificata[SQUADRE] = {0};

    int s;
    int g;
    int posizione;
    int migliore;
    int imbattuta;
    int vittorie_giornata;
    int pareggi_giornata;

    /* ── 1. Prospetto dei risultati e totale punti per squadra ─────── */
    printf("=== TORNEO CALCIO A 5 - DOPO %d GIORNATE ===\n\n", GIORNATE);
    printf("  %-16s G1 G2 G3 G4 G5   Punti\n", "Squadra");
    for (s = 0; s < SQUADRE; s++) {
        totale[s] = 0;
        printf("  %-16s", squadre[s]);
        for (g = 0; g < GIORNATE; g++) {
            switch (punti[s][g]) {
                case VITTORIA:
                    printf("  V");
                    break;
                case PAREGGIO:
                    printf("  P");
                    break;
                default:
                    printf("  S");
                    break;
            }
            totale[s] = totale[s] + punti[s][g];
        }
        printf("   %5d\n", totale[s]);
    }

    /* ── 2. Classifica ────────────────────────────────────────────────
     * Per ogni posizione si cerca la squadra con più punti tra quelle
     * non ancora classificate (stessa tecnica di
     * 01-array-monodimensionali/03-operazioni-su-array/060).           */
    printf("\n--- Classifica ---\n");
    for (posizione = 1; posizione <= SQUADRE; posizione++) {
        migliore = -1;
        for (s = 0; s < SQUADRE; s++) {
            if (!classificata[s]) {
                if (migliore == -1 || totale[s] > totale[migliore]) {
                    migliore = s;
                }
            }
        }
        classificata[migliore] = 1;
        printf("  %d. %-16s %3d punti\n", posizione, squadre[migliore], totale[migliore]);
    }

    /* ── 3. Squadre imbattute: nessuno 0 nella riga ───────────────── */
    printf("\n--- Squadre imbattute ---\n");
    for (s = 0; s < SQUADRE; s++) {
        imbattuta = 1;
        for (g = 0; g < GIORNATE && imbattuta; g++) {
            if (punti[s][g] == SCONFITTA) {
                imbattuta = 0;
            }
        }
        if (imbattuta) {
            printf("  %s\n", squadre[s]);
        }
    }

    /* ── 4. Vittorie e pareggi per giornata (per colonne) ─────────────
     * Ogni partita pareggiata compare due volte (una per squadra), ogni
     * vittoria una volta sola.                                         */
    printf("\n--- Esiti per giornata ---\n");
    for (g = 0; g < GIORNATE; g++) {
        vittorie_giornata = 0;
        pareggi_giornata = 0;
        for (s = 0; s < SQUADRE; s++) {
            if (punti[s][g] == VITTORIA) {
                vittorie_giornata++;
            } else if (punti[s][g] == PAREGGIO) {
                pareggi_giornata++;
            }
        }
        printf("  Giornata %d: %d %s, %d %s\n", g + 1,
               vittorie_giornata, vittorie_giornata == 1 ? "vittoria" : "vittorie",
               pareggi_giornata / 2, pareggi_giornata / 2 == 1 ? "pareggio" : "pareggi");
    }

    return 0;
}
