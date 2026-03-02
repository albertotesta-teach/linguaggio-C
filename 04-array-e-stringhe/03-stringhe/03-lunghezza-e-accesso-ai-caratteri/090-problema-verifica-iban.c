/*
 * 090-problema-verifica-iban.c
 *
 * Problema reale: verifica formale di un codice IBAN italiano.
 *
 * Scenario: un'applicazione bancaria deve verificare che un IBAN
 * inserito dall'utente rispetti il formato formale italiano prima
 * di procedere con una transazione. La verifica formale controlla:
 *
 *   1. Lunghezza: esattamente 27 caratteri
 *   2. Posizioni 0-1 (country code): due lettere maiuscole "IT"
 *   3. Posizioni 2-3 (check digits): due cifre numeriche
 *   4. Posizione 4 (CIN): una lettera maiuscola
 *   5. Posizioni 5-9 (ABI): cinque cifre numeriche (codice banca)
 *   6. Posizioni 10-14 (CAB): cinque cifre numeriche (codice agenzia)
 *   7. Posizioni 15-26 (BBAN): dodici caratteri alfanumerici
 *
 * Nota: questa è una verifica FORMALE, non matematica. La verifica
 * matematica del checksum richiederebbe operazioni più avanzate.
 *
 * Concetti applicati:
 *   - lettura con scanf (IBAN senza spazi)
 *   - verifica lunghezza con ciclo while
 *   - accesso per indice per verificare ogni campo
 *   - flag booleani per ogni controllo
 */

#include <stdio.h>

int main(void) {

    /* Buffer per l'IBAN: 27 caratteri + '\0' = 28 celle */
    char iban[28];

    /* Lunghezza calcolata manualmente */
    int lunghezza = 0;

    /* Flag per ogni controllo formale */
    int lunghezza_ok   = 0;
    int country_ok     = 0; /* posizioni 0-1: "IT" */
    int checkdigit_ok  = 0; /* posizioni 2-3: due cifre */
    int cin_ok         = 0; /* posizione 4:  una lettera */
    int abi_ok         = 0; /* posizioni 5-9: cinque cifre */
    int cab_ok         = 0; /* posizioni 10-14: cinque cifre */
    int bban_ok        = 0; /* posizioni 15-26: alfanumerici */

    /* Contatore degli errori trovati */
    int errori = 0;

    /* Indice per i cicli */
    int i;

    /* Flag temporaneo per i controlli sui segmenti */
    int segmento_ok;

    printf("╔══════════════════════════════════════════╗\n");
    printf("║     VERIFICA FORMALE IBAN ITALIANO       ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");

    printf("Formato IBAN italiano: IT00A00000000000000000000\n");
    printf("  IT  = country code (2 lettere)\n");
    printf("  00  = check digits (2 cifre)\n");
    printf("  A   = CIN (1 lettera)\n");
    printf("  00000 = ABI banca (5 cifre)\n");
    printf("  00000 = CAB agenzia (5 cifre)\n");
    printf("  000000000000 = conto (12 alfanumerici)\n\n");

    /* --- LETTURA IBAN ---
     * scanf senza spazi: l'IBAN non contiene spazi nel formato compatto. */
    printf("Inserisci il codice IBAN (senza spazi): ");
    scanf("%27s", iban);

    /* --- VERIFICA LUNGHEZZA ---
     * Calcoliamo la lunghezza manualmente e verifichiamo che sia 27. */
    i = 0;
    while (iban[i] != '\0') {
        lunghezza++;
        i++;
    }

    if (lunghezza == 27) {
        lunghezza_ok = 1;
    }

    /* Procediamo con gli altri controlli solo se la lunghezza è corretta.
     * Con lunghezza errata, gli accessi per indice potrebbero essere
     * fuori dai limiti del contenuto significativo. */
    if (lunghezza_ok) {

        /* --- VERIFICA COUNTRY CODE (posizioni 0-1) ---
         * Per un IBAN italiano devono essere 'I' e 'T'. */
        if (iban[0] == 'I' && iban[1] == 'T') {
            country_ok = 1;
        }

        /* --- VERIFICA CHECK DIGITS (posizioni 2-3) ---
         * Devono essere due cifre numeriche. */
        if (iban[2] >= '0' && iban[2] <= '9' &&
            iban[3] >= '0' && iban[3] <= '9') {
            checkdigit_ok = 1;
        }

        /* --- VERIFICA CIN (posizione 4) ---
         * Deve essere una lettera maiuscola. */
        if (iban[4] >= 'A' && iban[4] <= 'Z') {
            cin_ok = 1;
        }

        /* --- VERIFICA ABI (posizioni 5-9) ---
         * Cinque cifre numeriche consecutive.
         * Scorriamo le posizioni 5,6,7,8,9 con un ciclo while. */
        segmento_ok = 1;
        i = 5;
        while (i <= 9 && segmento_ok) {
            if (iban[i] < '0' || iban[i] > '9') {
                segmento_ok = 0;
            }
            i++;
        }
        abi_ok = segmento_ok;

        /* --- VERIFICA CAB (posizioni 10-14) ---
         * Cinque cifre numeriche consecutive. */
        segmento_ok = 1;
        i = 10;
        while (i <= 14 && segmento_ok) {
            if (iban[i] < '0' || iban[i] > '9') {
                segmento_ok = 0;
            }
            i++;
        }
        cab_ok = segmento_ok;

        /* --- VERIFICA BBAN (posizioni 15-26) ---
         * Dodici caratteri alfanumerici (lettere maiuscole o cifre). */
        segmento_ok = 1;
        i = 15;
        while (i <= 26 && segmento_ok) {
            if (!((iban[i] >= '0' && iban[i] <= '9') ||
                  (iban[i] >= 'A' && iban[i] <= 'Z'))) {
                segmento_ok = 0;
            }
            i++;
        }
        bban_ok = segmento_ok;
    }

    /* --- OUTPUT RISULTATI --- */
    printf("\n");
    printf("════════════════════════════════════════════\n");
    printf("  RISULTATO VERIFICA: %s\n", iban);
    printf("════════════════════════════════════════════\n");

    /* Lunghezza */
    if (lunghezza_ok) {
        printf("  [OK] Lunghezza    : %d caratteri\n", lunghezza);
    } else {
        printf("  [!!] Lunghezza    : %d caratteri (richiesti 27)\n", lunghezza);
        errori++;
    }

    if (lunghezza_ok) {
        /* Country code */
        if (country_ok) {
            printf("  [OK] Country code : %c%c\n", iban[0], iban[1]);
        } else {
            printf("  [!!] Country code : %c%c (richiesto IT)\n",
                   iban[0], iban[1]);
            errori++;
        }

        /* Check digits */
        if (checkdigit_ok) {
            printf("  [OK] Check digits : %c%c\n", iban[2], iban[3]);
        } else {
            printf("  [!!] Check digits : devono essere due cifre\n");
            errori++;
        }

        /* CIN */
        if (cin_ok) {
            printf("  [OK] CIN          : %c\n", iban[4]);
        } else {
            printf("  [!!] CIN          : deve essere una lettera maiuscola\n");
            errori++;
        }

        /* ABI */
        if (abi_ok) {
            printf("  [OK] ABI          : %c%c%c%c%c\n",
                   iban[5], iban[6], iban[7], iban[8], iban[9]);
        } else {
            printf("  [!!] ABI          : devono essere 5 cifre\n");
            errori++;
        }

        /* CAB */
        if (cab_ok) {
            printf("  [OK] CAB          : %c%c%c%c%c\n",
                   iban[10], iban[11], iban[12], iban[13], iban[14]);
        } else {
            printf("  [!!] CAB          : devono essere 5 cifre\n");
            errori++;
        }

        /* BBAN */
        if (bban_ok) {
            printf("  [OK] Conto (BBAN) : %c%c%c%c%c%c%c%c%c%c%c%c\n",
                   iban[15], iban[16], iban[17], iban[18], iban[19],
                   iban[20], iban[21], iban[22], iban[23], iban[24],
                   iban[25], iban[26]);
        } else {
            printf("  [!!] Conto (BBAN) : devono essere 12 alfanumerici\n");
            errori++;
        }
    }

    printf("────────────────────────────────────────────\n");
    if (errori == 0) {
        printf("  ESITO: FORMATO VALIDO\n");
        printf("  (verifica formale superata, non matematica)\n");
    } else {
        printf("  ESITO: FORMATO NON VALIDO (%d errore/i)\n", errori);
    }
    printf("════════════════════════════════════════════\n");

    return 0;
}
