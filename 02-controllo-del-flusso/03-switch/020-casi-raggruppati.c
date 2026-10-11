/*
 * 020-casi-raggruppati.c
 *
 * Casi raggruppati e il problema del break dimenticato
 *
 * Quando l'esecuzione entra in un case, prosegue istruzione dopo
 * istruzione fino al primo break (o alla fine dello switch), ATTRAVERSANDO
 * gli eventuali case successivi. Questo comportamento si chiama
 * "fall-through" (caduta).
 *
 * Ha un uso corretto: più case scritti uno sotto l'altro, senza
 * istruzioni in mezzo, condividono lo stesso codice.
 *
 *     case 6:
 *     case 7:
 *         printf("fine settimana\n");
 *         break;
 *
 * E un errore classico: dimenticare un break, così il programma esegue
 * anche il ramo successivo.
 */

#include <stdio.h>

int main(void)
{
    int giorno = 6;
    int mese = 11;
    int voto = 4;

    /* ── 1. Giorni feriali e festivi ──────────────────────────────────
     * Cinque case raggruppati per i feriali, due per il fine settimana. */
    printf("=== Feriale o festivo ===\n");
    printf("giorno = %d -> ", giorno);

    switch (giorno) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            printf("giorno feriale\n");
            break;
        case 6:
        case 7:
            printf("fine settimana\n");
            break;
        default:
            printf("valore non valido\n");
            break;
    }
    printf("\n");

    /* ── 2. Stagione a partire dal mese ───────────────────────────────
     * (semplificata: ogni stagione coincide con tre mesi interi) */
    printf("=== Stagione ===\n");
    printf("mese = %d -> ", mese);

    switch (mese) {
        case 12:
        case 1:
        case 2:
            printf("inverno\n");
            break;
        case 3:
        case 4:
        case 5:
            printf("primavera\n");
            break;
        case 6:
        case 7:
        case 8:
            printf("estate\n");
            break;
        case 9:
        case 10:
        case 11:
            printf("autunno\n");
            break;
        default:
            printf("mese non valido\n");
            break;
    }
    printf("\n");

    /* ── 3. Valutazione con casi raggruppati ─────────────────────────── */
    printf("=== Esito della verifica ===\n");
    printf("voto = %d -> ", voto);

    switch (voto) {
        case 1:
        case 2:
        case 3:
        case 4:
            printf("gravemente insufficiente\n");
            break;
        case 5:
            printf("insufficiente\n");
            break;
        case 6:
        case 7:
            printf("sufficiente/discreto\n");
            break;
        case 8:
        case 9:
        case 10:
            printf("buono/ottimo\n");
            break;
        default:
            printf("voto non valido\n");
            break;
    }

    /*
     * ERRORE COMUNE: break dimenticato.
     *
     *     switch (giorno) {
     *         case 6:
     *             printf("sabato\n");          // manca il break
     *         case 7:
     *             printf("domenica\n");
     *             break;
     *     }
     *
     * Con giorno = 6 il programma stampa "sabato" E "domenica".
     * gcc con l'opzione -Wimplicit-fallthrough (inclusa in -Wextra)
     * segnala un case che "cade" nel successivo dopo aver eseguito
     * istruzioni. I case vuoti raggruppati non generano warning.
     */

    return 0;
}
