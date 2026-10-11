/*
 * 010-switch-base.c
 *
 * L'istruzione switch: scegliere un ramo in base al valore di un'espressione
 *
 * Quando si deve confrontare UNA variabile intera con una serie di valori
 * costanti, una lunga catena else-if diventa ripetitiva:
 *
 *     if (scelta == 1) { ... }
 *     else if (scelta == 2) { ... }
 *     else if (scelta == 3) { ... }
 *     else { ... }
 *
 * switch esprime la stessa scelta in modo più compatto e leggibile:
 *
 *     switch (espressione) {
 *         case COSTANTE_1:
 *             istruzioni;
 *             break;
 *         case COSTANTE_2:
 *             istruzioni;
 *             break;
 *         default:
 *             istruzioni per tutti gli altri valori;
 *             break;
 *     }
 *
 * Regole:
 *   - l'espressione deve essere di tipo intero (int, char, ...),
 *     non double;
 *   - ogni case vuole una COSTANTE (un numero, un carattere, una #define),
 *     non una variabile né un intervallo;
 *   - break termina lo switch: senza break l'esecuzione prosegue nel
 *     case successivo (vedi 020-casi-raggruppati.c).
 *
 * break dentro lo switch è l'UNICO uso di break ammesso nel corso.
 */

#include <stdio.h>

int main(void)
{
    int giorno = 3;
    int livello = 2;
    int codice_errore = 404;

    /* ── 1. Numero del giorno -> nome ──────────────────────────────── */
    printf("=== Giorno della settimana ===\n");
    printf("giorno = %d -> ", giorno);

    switch (giorno) {
        case 1:
            printf("lunedi'\n");
            break;
        case 2:
            printf("martedi'\n");
            break;
        case 3:
            printf("mercoledi'\n");
            break;
        case 4:
            printf("giovedi'\n");
            break;
        case 5:
            printf("venerdi'\n");
            break;
        case 6:
            printf("sabato\n");
            break;
        case 7:
            printf("domenica\n");
            break;
        default:
            /* default gestisce tutti i valori non previsti: va scritto
             * sempre, anche solo per segnalare un errore */
            printf("valore non valido\n");
            break;
    }
    printf("\n");

    /* ── 2. Più istruzioni in un case ─────────────────────────────────
     * Ogni case può contenere più istruzioni, senza graffe: il ramo
     * va dal case fino al break.                                       */
    printf("=== Livello di difficolta' ===\n");
    printf("livello = %d\n", livello);

    switch (livello) {
        case 1:
            printf("Facile: 5 vite, nemici lenti.\n");
            printf("Suggerimenti attivi.\n");
            break;
        case 2:
            printf("Medio: 3 vite, nemici normali.\n");
            printf("Suggerimenti solo su richiesta.\n");
            break;
        case 3:
            printf("Difficile: 1 vita, nemici veloci.\n");
            printf("Nessun suggerimento.\n");
            break;
        default:
            printf("Livello sconosciuto: si usa il livello medio.\n");
            break;
    }
    printf("\n");

    /* ── 3. I valori dei case non devono essere consecutivi ─────────── */
    printf("=== Codici di stato HTTP ===\n");
    printf("codice %d: ", codice_errore);

    switch (codice_errore) {
        case 200:
            printf("OK\n");
            break;
        case 301:
            printf("risorsa spostata\n");
            break;
        case 404:
            printf("pagina non trovata\n");
            break;
        case 500:
            printf("errore interno del server\n");
            break;
        default:
            printf("codice non gestito\n");
            break;
    }

    /*
     * QUANDO NON SI PUÒ USARE switch
     *
     *   switch (temperatura) {          // con temperatura double: ERRORE
     *   case eta >= 18:                 // condizione: ERRORE, serve una costante
     *   case variabile:                 // variabile: ERRORE
     *
     * Per intervalli e condizioni composte si usa la catena else-if.
     */

    return 0;
}
