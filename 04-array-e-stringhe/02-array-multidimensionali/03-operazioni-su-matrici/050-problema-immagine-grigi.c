/*
 * 050-problema-immagine-grigi.c
 *
 * Elaborazione di una piccola immagine in scala di grigi
 *
 * Un'immagine digitale in scala di grigi è una matrice di PIXEL: ogni
 * cella contiene la luminosità del punto, da 0 (nero) a 255 (bianco).
 * I programmi di fotoritocco applicano a questa matrice operazioni come:
 *
 *   NEGATIVO        ogni pixel diventa 255 - valore
 *   SOGLIA          bianco se il valore supera una soglia, nero altrimenti
 *   SPECCHIO        ribaltamento orizzontale: si scambiano le colonne
 *                   simmetriche di ogni riga
 *   LUMINOSITÀ      media di tutti i pixel
 *
 * Per vedere il risultato a schermo ogni pixel viene disegnato con un
 * carattere più o meno "pieno": la luminosità 0-255 viene ridotta a un
 * livello da 0 a 4 (valore / 52), e a ogni livello corrisponde un carattere.
 *
 * L'immagine originale non viene modificata: ogni operazione lavora su
 * una matrice risultato.
 */

#include <stdio.h>

#define ALTEZZA   6
#define LARGHEZZA 10
#define BIANCO    255
#define NERO      0
#define SOGLIA    128

int main(void)
{
    /* Una freccia che punta a destra: sfondo scuro, asta grigia,
     * punta chiara. */
    int originale[ALTEZZA][LARGHEZZA] = {
        { 20,  20,  20,  20,  20, 200,  20,  20,  20,  20},
        { 20,  20,  20,  20,  20, 220, 200,  20,  20,  20},
        {100, 100, 100, 100, 100, 250, 250, 220,  20,  20},
        {100, 100, 100, 100, 100, 250, 250, 220,  20,  20},
        { 20,  20,  20,  20,  20, 220, 200,  20,  20,  20},
        { 20,  20,  20,  20,  20, 200,  20,  20,  20,  20}
    };
    int risultato[ALTEZZA][LARGHEZZA];
    int r;
    int c;
    int livello;
    long somma = 0;
    int appoggio;

    /* ── Originale ────────────────────────────────────────────────────
     * Il livello si traduce in un carattere con uno switch:
     *   0 ' '   1 '.'   2 'o'   3 'O'   4 '@'                          */
    printf("Originale:\n");
    for (r = 0; r < ALTEZZA; r++) {
        printf("  |");
        for (c = 0; c < LARGHEZZA; c++) {
            livello = originale[r][c] / 52;
            switch (livello) {
                case 0:
                    printf("  ");
                    break;
                case 1:
                    printf("..");
                    break;
                case 2:
                    printf("oo");
                    break;
                case 3:
                    printf("OO");
                    break;
                default:
                    printf("@@");
                    break;
            }
            somma = somma + originale[r][c];
        }
        printf("|\n");
    }
    printf("Luminosita' media: %.1f\n\n", (double) somma / (ALTEZZA * LARGHEZZA));

    /* ── Negativo ─────────────────────────────────────────────────── */
    for (r = 0; r < ALTEZZA; r++) {
        for (c = 0; c < LARGHEZZA; c++) {
            risultato[r][c] = BIANCO - originale[r][c];
        }
    }
    printf("Negativo:\n");
    for (r = 0; r < ALTEZZA; r++) {
        printf("  |");
        for (c = 0; c < LARGHEZZA; c++) {
            livello = risultato[r][c] / 52;
            switch (livello) {
                case 0:
                    printf("  ");
                    break;
                case 1:
                    printf("..");
                    break;
                case 2:
                    printf("oo");
                    break;
                case 3:
                    printf("OO");
                    break;
                default:
                    printf("@@");
                    break;
            }
        }
        printf("|\n");
    }
    printf("\n");

    /* ── Soglia: solo due valori possibili ────────────────────────── */
    for (r = 0; r < ALTEZZA; r++) {
        for (c = 0; c < LARGHEZZA; c++) {
            if (originale[r][c] > SOGLIA) {
                risultato[r][c] = BIANCO;
            } else {
                risultato[r][c] = NERO;
            }
        }
    }
    printf("Soglia %d (bianco/nero):\n", SOGLIA);
    for (r = 0; r < ALTEZZA; r++) {
        printf("  |");
        for (c = 0; c < LARGHEZZA; c++) {
            if (risultato[r][c] == BIANCO) {
                printf("@@");
            } else {
                printf("  ");
            }
        }
        printf("|\n");
    }
    printf("\n");

    /* ── Specchio: copia, poi scambio delle colonne simmetriche ───────
     * In ogni riga la colonna c si scambia con LARGHEZZA - 1 - c, solo
     * per la prima metà delle colonne (come l'inversione di un array):
     * la freccia passa a puntare verso sinistra.                       */
    for (r = 0; r < ALTEZZA; r++) {
        for (c = 0; c < LARGHEZZA; c++) {
            risultato[r][c] = originale[r][c];
        }
    }
    for (r = 0; r < ALTEZZA; r++) {
        for (c = 0; c < LARGHEZZA / 2; c++) {
            appoggio = risultato[r][c];
            risultato[r][c] = risultato[r][LARGHEZZA - 1 - c];
            risultato[r][LARGHEZZA - 1 - c] = appoggio;
        }
    }
    printf("Specchio orizzontale:\n");
    for (r = 0; r < ALTEZZA; r++) {
        printf("  |");
        for (c = 0; c < LARGHEZZA; c++) {
            livello = risultato[r][c] / 52;
            switch (livello) {
                case 0:
                    printf("  ");
                    break;
                case 1:
                    printf("..");
                    break;
                case 2:
                    printf("oo");
                    break;
                case 3:
                    printf("OO");
                    break;
                default:
                    printf("@@");
                    break;
            }
        }
        printf("|\n");
    }

    /*
     * NOTA: il codice di stampa si ripete quasi identico più volte.
     * Nella sezione 04 (matrici e funzioni) lo si raccoglierà in una
     * funzione stampa_immagine(), chiamata dopo ogni operazione.
     */

    return 0;
}
