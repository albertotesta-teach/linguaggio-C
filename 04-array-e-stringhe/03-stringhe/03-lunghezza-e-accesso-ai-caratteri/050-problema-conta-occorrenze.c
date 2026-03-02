/*
 * 050-problema-conta-occorrenze.c
 *
 * Problema reale: contare le occorrenze di una lettera in un testo.
 *
 * Scenario: un correttore ortografico di base deve analizzare un testo
 * inserito dall'utente e contare quante volte compare una determinata
 * lettera, distinguendo tra maiuscole e minuscole.
 *
 * Il programma legge una stringa con spazi (fgets) e una lettera
 * (scanf), poi scorre la stringa con un ciclo while confrontando
 * ogni carattere con la lettera cercata.
 *
 * Concetti applicati:
 *   - lettura di stringhe con spazi tramite fgets
 *   - lettura di un singolo carattere con scanf
 *   - scansione con ciclo while e confronto carattere per carattere
 *   - conteggio con variabile intera
 */

#include <stdio.h>

int main(void) {

    /* Buffer per il testo da analizzare */
    char testo[201]; /* max 200 caratteri + '\0' */

    /* Lettera da cercare */
    char lettera;

    /* Contatori: occorrenze esatte e occorrenze case-insensitive */
    int occorrenze_esatte     = 0;
    int occorrenze_maiuscola  = 0;
    int occorrenze_minuscola  = 0;

    /* Carattere corrente durante la scansione */
    char c;

    /* Versione maiuscola e minuscola della lettera cercata */
    char lettera_maiuscola;
    char lettera_minuscola;

    /* Indice per scorrere il testo e per rimuovere '\n' */
    int i;

    printf("=== CONTATORE DI OCCORRENZE ===\n\n");

    /* --- LETTURA DEL TESTO ---
     * fgets per permettere spazi nel testo. */
    printf("Inserisci il testo da analizzare:\n> ");
    fgets(testo, 201, stdin);

    /* Rimozione '\n' lasciato da fgets */
    i = 0;
    while (testo[i] != '\n' && testo[i] != '\0') {
        i++;
    }
    testo[i] = '\0';

    /* --- LETTURA DELLA LETTERA DA CERCARE ---
     * scanf con %c legge un singolo carattere.
     * Lo spazio prima di %c scarta eventuali caratteri bianchi
     * rimasti nel buffer (incluso '\n'). */
    printf("Inserisci la lettera da cercare: ");
    scanf(" %c", &lettera);

    /* Calcolo della versione maiuscola e minuscola della lettera.
     * La differenza ASCII tra maiuscola e minuscola è sempre 32
     * per le lettere dell'alfabeto latino.
     * Es: 'a'(97) - 32 = 'A'(65) */
    if (lettera >= 'a' && lettera <= 'z') {
        /* la lettera è minuscola: la maiuscola è 32 posizioni prima */
        lettera_minuscola = lettera;
        lettera_maiuscola = lettera - 32;
    } else if (lettera >= 'A' && lettera <= 'Z') {
        /* la lettera è maiuscola: la minuscola è 32 posizioni dopo */
        lettera_maiuscola = lettera;
        lettera_minuscola = lettera + 32;
    } else {
        /* carattere non alfabetico: maiuscola e minuscola coincidono */
        lettera_maiuscola = lettera;
        lettera_minuscola = lettera;
    }

    /* --- SCANSIONE E CONTEGGIO ---
     * Scorriamo il testo un carattere alla volta.
     * Contiamo le occorrenze esatte e quelle case-insensitive. */
    i = 0;
    while (testo[i] != '\0') {
        c = testo[i];

        /* Occorrenza esatta (stesso case della lettera inserita) */
        if (c == lettera) {
            occorrenze_esatte++;
        }

        /* Occorrenze per maiuscola e minuscola separatamente */
        if (c == lettera_maiuscola) {
            occorrenze_maiuscola++;
        }
        if (c == lettera_minuscola) {
            occorrenze_minuscola++;
        }

        i++;
    }

    /* --- OUTPUT RISULTATI --- */
    printf("\n");
    printf("════════════════════════════════════\n");
    printf("  RISULTATI ANALISI\n");
    printf("════════════════════════════════════\n");
    printf("  Testo     : \"%s\"\n", testo);
    printf("  Lettera   : '%c'\n", lettera);
    printf("────────────────────────────────────\n");
    printf("  Occorrenze esatte ('%c')   : %d\n",
           lettera, occorrenze_esatte);
    printf("  Occorrenze maiuscola ('%c'): %d\n",
           lettera_maiuscola, occorrenze_maiuscola);
    printf("  Occorrenze minuscola ('%c'): %d\n",
           lettera_minuscola, occorrenze_minuscola);
    printf("  Totale (case-insensitive)  : %d\n",
           occorrenze_maiuscola + occorrenze_minuscola);
    printf("════════════════════════════════════\n");

    return 0;
}
