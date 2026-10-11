/*
 * 040-problema-orario-scolastico.c
 *
 * Orario settimanale di una classe
 *
 * L'orario di una classe è una tabella: 5 giorni (righe) per 6 ore
 * (colonne). Ogni cella contiene il codice della materia svolta in
 * quell'ora:
 *
 *   1 = Italiano   2 = Matematica   3 = Inglese   4 = Informatica
 *   5 = Sistemi    6 = Storia       7 = Scienze motorie
 *
 * Il programma stampa l'orario con le sigle delle materie, calcola le
 * ore settimanali di ogni materia e indica il giorno con più ore di
 * Informatica.
 *
 * Struttura dati: una sola matrice int orario[GIORNI][ORE], inizializzata
 * con graffe annidate (una riga per giorno). Le sigle vengono stampate con
 * uno switch sul codice: gli array di stringhe saranno trattati più avanti.
 */

#include <stdio.h>

#define GIORNI 5
#define ORE    6
#define NUM_MATERIE 7

#define INFORMATICA 4

int main(void)
{
    int orario[GIORNI][ORE] = {
        {1, 1, 2, 4, 4, 6},     /* lunedì    */
        {2, 3, 5, 5, 1, 7},     /* martedì   */
        {4, 4, 4, 2, 6, 3},     /* mercoledì */
        {1, 2, 2, 5, 3, 7},     /* giovedì   */
        {5, 4, 4, 1, 2, 6}      /* venerdì   */
    };
    int giorno;
    int ora;
    int materia;
    int ore_materia;
    int ore_info_giorno;
    int max_ore_info = 0;
    int giorno_max_info = 0;
    int totale_ore = 0;

    /* ── 1. Stampa dell'orario ────────────────────────────────────── */
    printf("=== ORARIO SETTIMANALE 3A INFORMATICA ===\n\n");
    printf("          1a    2a    3a    4a    5a    6a\n");

    for (giorno = 0; giorno < GIORNI; giorno++) {
        switch (giorno) {
            case 0:
                printf("  Lun   ");
                break;
            case 1:
                printf("  Mar   ");
                break;
            case 2:
                printf("  Mer   ");
                break;
            case 3:
                printf("  Gio   ");
                break;
            default:
                printf("  Ven   ");
                break;
        }

        for (ora = 0; ora < ORE; ora++) {
            switch (orario[giorno][ora]) {
                case 1:
                    printf("  ITA ");
                    break;
                case 2:
                    printf("  MAT ");
                    break;
                case 3:
                    printf("  ING ");
                    break;
                case 4:
                    printf("  INF ");
                    break;
                case 5:
                    printf("  SIS ");
                    break;
                case 6:
                    printf("  STO ");
                    break;
                case 7:
                    printf("  MOT ");
                    break;
                default:
                    printf("  ??? ");
                    break;
            }
        }
        printf("\n");
    }

    /* ── 2. Ore settimanali per materia ───────────────────────────────
     * Per ogni codice di materia si scorre TUTTA la matrice e si contano
     * le celle che lo contengono: due cicli annidati dentro un terzo.  */
    printf("\n--- Ore settimanali per materia ---\n");
    for (materia = 1; materia <= NUM_MATERIE; materia++) {
        ore_materia = 0;
        for (giorno = 0; giorno < GIORNI; giorno++) {
            for (ora = 0; ora < ORE; ora++) {
                if (orario[giorno][ora] == materia) {
                    ore_materia++;
                }
            }
        }
        totale_ore = totale_ore + ore_materia;

        switch (materia) {
            case 1:
                printf("  Italiano        ");
                break;
            case 2:
                printf("  Matematica      ");
                break;
            case 3:
                printf("  Inglese         ");
                break;
            case 4:
                printf("  Informatica     ");
                break;
            case 5:
                printf("  Sistemi         ");
                break;
            case 6:
                printf("  Storia          ");
                break;
            default:
                printf("  Scienze motorie ");
                break;
        }
        printf(": %d ore\n", ore_materia);
    }
    printf("  Totale          : %d ore (%d giorni x %d ore)\n",
           totale_ore, GIORNI, ORE);

    /* ── 3. Giorno con più ore di Informatica ────────────────────────
     * Qui si lavora una riga alla volta: il ciclo esterno sceglie il
     * giorno, quello interno scorre le sue ore.                        */
    for (giorno = 0; giorno < GIORNI; giorno++) {
        ore_info_giorno = 0;
        for (ora = 0; ora < ORE; ora++) {
            if (orario[giorno][ora] == INFORMATICA) {
                ore_info_giorno++;
            }
        }
        if (ore_info_giorno > max_ore_info) {
            max_ore_info = ore_info_giorno;
            giorno_max_info = giorno;
        }
    }

    printf("\nGiorno con piu' ore di Informatica: ");
    switch (giorno_max_info) {
        case 0:
            printf("lunedi'");
            break;
        case 1:
            printf("martedi'");
            break;
        case 2:
            printf("mercoledi'");
            break;
        case 3:
            printf("giovedi'");
            break;
        default:
            printf("venerdi'");
            break;
    }
    printf(" (%d ore)\n", max_ore_info);

    return 0;
}
