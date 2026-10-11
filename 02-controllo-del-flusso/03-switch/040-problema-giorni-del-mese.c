/*
 * 040-problema-giorni-del-mese.c
 *
 * Quanti giorni ha un mese?
 *
 *   "Trenta giorni ha novembre, con april, giugno e settembre;
 *    di ventotto ce n'è uno, tutti gli altri ne han trentuno."
 *
 * Il programma riceve mese e anno e stampa il nome del mese e il numero
 * dei suoi giorni. La filastrocca si traduce direttamente in uno switch
 * con casi raggruppati: un gruppo per i mesi da 31 giorni, uno per quelli
 * da 30 e un caso a parte per febbraio, che dipende dall'anno.
 */

#include <stdio.h>

int main(void)
{
    int mese;
    int anno;
    int giorni;
    int bisestile;
    int mese_valido;

    printf("=== GIORNI DEL MESE ===\n\n");
    printf("Mese (1-12): ");
    scanf("%d", &mese);
    printf("Anno: ");
    scanf("%d", &anno);

    /* Regola dell'anno bisestile (vedi 01-logica-booleana) */
    bisestile = (anno % 4 == 0 && anno % 100 != 0) || anno % 400 == 0;

    mese_valido = 1;
    giorni = 0;

    printf("\n");

    /* ── 1. Nome del mese ─────────────────────────────────────────── */
    switch (mese) {
        case 1:
            printf("Gennaio");
            break;
        case 2:
            printf("Febbraio");
            break;
        case 3:
            printf("Marzo");
            break;
        case 4:
            printf("Aprile");
            break;
        case 5:
            printf("Maggio");
            break;
        case 6:
            printf("Giugno");
            break;
        case 7:
            printf("Luglio");
            break;
        case 8:
            printf("Agosto");
            break;
        case 9:
            printf("Settembre");
            break;
        case 10:
            printf("Ottobre");
            break;
        case 11:
            printf("Novembre");
            break;
        case 12:
            printf("Dicembre");
            break;
        default:
            printf("Mese %d", mese);
            break;
    }

    /* ── 2. Numero di giorni ──────────────────────────────────────── */
    switch (mese) {
        case 11:
        case 4:
        case 6:
        case 9:
            /* "trenta giorni ha novembre, con april, giugno e settembre" */
            giorni = 30;
            break;
        case 2:
            /* "di ventotto ce n'è uno", 29 negli anni bisestili */
            if (bisestile) {
                giorni = 29;
            } else {
                giorni = 28;
            }
            break;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            /* "tutti gli altri ne han trentuno" */
            giorni = 31;
            break;
        default:
            mese_valido = 0;
            break;
    }

    if (mese_valido) {
        printf(" %d ha %d giorni.\n", anno, giorni);
    } else {
        printf(": non e' un mese valido (inserire un numero da 1 a 12).\n");
    }

    /*
     * ERRORE COMUNE: dimenticare il break dopo il caso di febbraio.
     * L'esecuzione proseguirebbe nel gruppo successivo e giorni verrebbe
     * sovrascritto con 31.
     */

    return 0;
}
