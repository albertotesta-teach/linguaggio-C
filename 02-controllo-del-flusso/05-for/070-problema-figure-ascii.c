/*
 * 070-problema-figure-ascii.c
 *
 * Disegno di figure con caratteri
 *
 * Un'insegna luminosa a matrice di LED (o un terminale) disegna le figure
 * accendendo punti su una griglia di righe e colonne. Il programma disegna
 * quattro figure di altezza scelta dall'utente:
 *
 *   1. triangolo rettangolo        riga r: r asterischi
 *   2. piramide centrata           riga r: (h - r) spazi e (2r - 1) asterischi
 *   3. quadrato vuoto (cornice)    asterisco solo sul bordo
 *   4. rombo                       piramide + piramide capovolta
 *
 * Il metodo è sempre lo stesso: per ogni riga (ciclo esterno) si calcola
 * QUANTI spazi e QUANTI asterischi servono, in funzione del numero di riga,
 * e li si stampa con cicli interni.
 */

#include <stdio.h>

#define ALTEZZA_MIN 2
#define ALTEZZA_MAX 20

int main(void)
{
    int altezza;
    int riga;
    int colonna;
    int bordo;

    printf("=== FIGURE ASCII ===\n");
    do {
        printf("Altezza delle figure (%d-%d): ", ALTEZZA_MIN, ALTEZZA_MAX);
        scanf("%d", &altezza);
    } while (altezza < ALTEZZA_MIN || altezza > ALTEZZA_MAX);

    /* ── 1. Triangolo rettangolo ──────────────────────────────────── */
    printf("\n1) Triangolo rettangolo\n");
    for (riga = 1; riga <= altezza; riga++) {
        for (colonna = 1; colonna <= riga; colonna++) {
            printf("*");
        }
        printf("\n");
    }

    /* ── 2. Piramide centrata ─────────────────────────────────────────
     * Riga r (da 1 ad altezza): prima (altezza - r) spazi,
     * poi (2r - 1) asterischi: 1, 3, 5, ...                             */
    printf("\n2) Piramide\n");
    for (riga = 1; riga <= altezza; riga++) {
        for (colonna = 1; colonna <= altezza - riga; colonna++) {
            printf(" ");
        }
        for (colonna = 1; colonna <= 2 * riga - 1; colonna++) {
            printf("*");
        }
        printf("\n");
    }

    /* ── 3. Quadrato vuoto ────────────────────────────────────────────
     * Un punto è sul bordo se è nella prima o nell'ultima riga, oppure
     * nella prima o nell'ultima colonna: quattro condizioni unite da OR. */
    printf("\n3) Quadrato vuoto\n");
    for (riga = 1; riga <= altezza; riga++) {
        for (colonna = 1; colonna <= altezza; colonna++) {
            bordo = (riga == 1 || riga == altezza || colonna == 1 || colonna == altezza);
            if (bordo) {
                printf("* ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }

    /* ── 4. Rombo ─────────────────────────────────────────────────────
     * Metà superiore: la piramide. Metà inferiore: la piramide
     * capovolta, senza ripetere la riga centrale (si parte da altezza-1). */
    printf("\n4) Rombo\n");
    for (riga = 1; riga <= altezza; riga++) {
        for (colonna = 1; colonna <= altezza - riga; colonna++) {
            printf(" ");
        }
        for (colonna = 1; colonna <= 2 * riga - 1; colonna++) {
            printf("*");
        }
        printf("\n");
    }
    for (riga = altezza - 1; riga >= 1; riga--) {
        for (colonna = 1; colonna <= altezza - riga; colonna++) {
            printf(" ");
        }
        for (colonna = 1; colonna <= 2 * riga - 1; colonna++) {
            printf("*");
        }
        printf("\n");
    }

    /*
     * METODO PER DISEGNARE UNA NUOVA FIGURA
     * 1. Disegnarla su carta a quadretti per una altezza piccola (es. 4).
     * 2. Per ogni riga contare spazi e asterischi e scriverli in tabella.
     * 3. Trovare la formula che lega quei numeri al numero di riga.
     * 4. Tradurre la formula nelle condizioni dei cicli interni.
     */

    return 0;
}
