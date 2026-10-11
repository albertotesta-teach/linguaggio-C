/*
 * 050-problema-posti-cinema.c
 *
 * Mappa dei posti di una sala cinematografica
 *
 * Una piccola sala ha 6 file (A-F) da 10 posti. Lo stato di ogni posto è
 * memorizzato in una matrice: 0 = libero, 1 = occupato. La matrice è
 * inizializzata con la situazione a dieci minuti dall'inizio dello
 * spettacolo.
 *
 * Il programma:
 *   - disegna la mappa della sala (O = libero, X = occupato);
 *   - conta i posti liberi di ogni fila e quelli totali;
 *   - calcola la percentuale di riempimento;
 *   - indica la fila con più posti liberi;
 *   - verifica se esistono 4 posti liberi consecutivi nella stessa fila
 *     (una famiglia vuole sedersi vicina).
 *
 * La lettera della fila si ottiene dall'indice di riga: 'A' + riga.
 */

#include <stdio.h>

#define FILE_SALA 6
#define POSTI     10
#define LIBERO    0
#define OCCUPATO  1
#define GRUPPO    4      /* posti vicini richiesti */

int main(void)
{
    int sala[FILE_SALA][POSTI] = {
        {1, 1, 1, 0, 0, 1, 1, 1, 1, 0},     /* A */
        {1, 1, 1, 1, 1, 1, 1, 0, 1, 1},     /* B */
        {0, 1, 1, 0, 0, 0, 0, 1, 1, 0},     /* C */
        {0, 0, 1, 1, 0, 1, 0, 0, 1, 0},     /* D */
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},     /* E */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}      /* F */
    };
    int fila;
    int posto;
    int liberi_fila;
    int liberi_totali = 0;
    int max_liberi = -1;
    int fila_max = 0;
    int consecutivi;
    int trovato_gruppo = 0;
    int fila_gruppo = 0;
    int posto_gruppo = 0;

    /* ── 1. Mappa della sala ──────────────────────────────────────── */
    printf("=== SALA 2 - SPETTACOLO DELLE 21:00 ===\n\n");
    printf("              SCHERMO\n");
    printf("      1  2  3  4  5  6  7  8  9 10   liberi\n");

    for (fila = 0; fila < FILE_SALA; fila++) {
        liberi_fila = 0;
        printf("  %c  ", 'A' + fila);
        for (posto = 0; posto < POSTI; posto++) {
            if (sala[fila][posto] == LIBERO) {
                printf(" O ");
                liberi_fila++;
            } else {
                printf(" X ");
            }
        }
        printf("   %2d\n", liberi_fila);

        liberi_totali = liberi_totali + liberi_fila;
        if (liberi_fila > max_liberi) {
            max_liberi = liberi_fila;
            fila_max = fila;
        }
    }

    printf("\nPosti liberi : %d su %d\n", liberi_totali, FILE_SALA * POSTI);
    printf("Riempimento  : %.1f%%\n",
           100.0 * (FILE_SALA * POSTI - liberi_totali) / (FILE_SALA * POSTI));
    printf("Fila piu' libera: %c (%d posti)\n", 'A' + fila_max, max_liberi);

    /* ── 2. Ricerca di GRUPPO posti liberi consecutivi ────────────────
     * Si scorre una fila alla volta contando i posti liberi di seguito;
     * un posto occupato riporta il conteggio a zero. La ricerca si ferma
     * al primo gruppo trovato grazie al flag nella condizione dei cicli
     * (nessun break). La ricerca parte dalla fila A.                   */
    for (fila = 0; fila < FILE_SALA && !trovato_gruppo; fila++) {
        consecutivi = 0;
        for (posto = 0; posto < POSTI && !trovato_gruppo; posto++) {
            if (sala[fila][posto] == LIBERO) {
                consecutivi++;
                if (consecutivi == GRUPPO) {
                    trovato_gruppo = 1;
                    fila_gruppo = fila;
                    posto_gruppo = posto - GRUPPO + 1;   /* primo posto del gruppo */
                }
            } else {
                consecutivi = 0;
            }
        }
    }

    if (trovato_gruppo) {
        printf("\n%d posti vicini disponibili: fila %c, posti da %d a %d\n",
               GRUPPO, 'A' + fila_gruppo, posto_gruppo + 1, posto_gruppo + GRUPPO);
    } else {
        printf("\nNessun gruppo di %d posti vicini disponibile.\n", GRUPPO);
    }

    /*
     * NOTA: i posti sono numerati da 1 per lo spettatore, ma gli indici
     * della matrice partono da 0. La conversione (+1) avviene solo nella
     * stampa.
     */

    return 0;
}
