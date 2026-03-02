/*
 * 060-problema-codice-prodotto.c
 *
 * Problema reale: analisi e confronto di codici prodotto in un magazzino.
 *
 * Scenario: un sistema di magazzino utilizza codici prodotto nel formato
 * CAT-NNN-XX dove:
 *   CAT → categoria merceologica (3 lettere maiuscole), es. "ELE", "ALI", "ABB"
 *   NNN → numero progressivo (3 cifre), es. "001", "042", "128"
 *   XX  → variante o colore (2 lettere maiuscole), es. "RO", "BL", "VE"
 *
 * Il programma dichiara alcuni codici, ne estrae le componenti accedendo
 * ai caratteri per indice e verifica se due prodotti appartengono
 * alla stessa categoria confrontando i caratteri uno a uno con un ciclo while.
 *
 * Struttura del codice (indici):
 *   0,1,2   → categoria  (CAT)
 *   3       → separatore '-'
 *   4,5,6   → progressivo (NNN)
 *   7       → separatore '-'
 *   8,9     → variante (XX)
 *   10      → '\0'
 *
 * Concetti applicati:
 *   - dichiarazione e inizializzazione di stringhe
 *   - accesso ai caratteri tramite indice
 *   - ciclo while per confronto carattere per carattere
 *   - uso di variabili flag per il risultato del confronto
 */

#include <stdio.h>

int main(void) {

    /* Codici prodotto del magazzino.
     * Formato fisso: CAT-NNN-XX = 10 caratteri + '\0' = 11 celle. */
    char prodotto1[11] = "ELE-042-BL";
    char prodotto2[11] = "ELE-107-RO";
    char prodotto3[11] = "ALI-003-VE";

    /* Array per le componenti estratte dal primo prodotto */
    char categoria[4];   /* 3 lettere + '\0' */
    char progressivo[4]; /* 3 cifre   + '\0' */
    char variante[3];    /* 2 lettere + '\0' */

    /* Indice per scorrere i caratteri nei cicli */
    int i;

    /* Flag per il confronto tra categorie (0 = diversa, 1 = stessa) */
    int stessa_categoria;

    /* --- VISUALIZZAZIONE PRODOTTI ---
     * Stampa i codici prodotto presenti in magazzino. */
    printf("=== SISTEMA DI GESTIONE MAGAZZINO ===\n\n");
    printf("Prodotti in archivio:\n");
    printf("  Prodotto 1: %s\n", prodotto1);
    printf("  Prodotto 2: %s\n", prodotto2);
    printf("  Prodotto 3: %s\n", prodotto3);
    printf("\n");

    /* --- ESTRAZIONE COMPONENTI DEL PRODOTTO 1 ---
     * Le posizioni sono fisse e note dal formato del codice.
     * I separatori '-' si trovano agli indici 3 e 7 e vengono ignorati. */

    /* Categoria: caratteri agli indici 0, 1, 2 */
    categoria[0] = prodotto1[0];
    categoria[1] = prodotto1[1];
    categoria[2] = prodotto1[2];
    categoria[3] = '\0'; /* terminatore obbligatorio */

    /* Progressivo: caratteri agli indici 4, 5, 6 */
    progressivo[0] = prodotto1[4];
    progressivo[1] = prodotto1[5];
    progressivo[2] = prodotto1[6];
    progressivo[3] = '\0'; /* terminatore obbligatorio */

    /* Variante: caratteri agli indici 8, 9 */
    variante[0] = prodotto1[8];
    variante[1] = prodotto1[9];
    variante[2] = '\0'; /* terminatore obbligatorio */

    printf("Analisi Prodotto 1 (%s):\n", prodotto1);
    printf("  Categoria   : %s\n", categoria);
    printf("  Progressivo : %s\n", progressivo);
    printf("  Variante    : %s\n", variante);
    printf("\n");

    /* --- CONFRONTO CATEGORIE: PRODOTTO 1 vs PRODOTTO 2 ---
     * Confronta i caratteri della categoria (indici 0, 1, 2) uno a uno
     * usando un ciclo while. Non si usa strcmp per mostrare il confronto
     * manuale carattere per carattere.
     * Il ciclo si ferma quando trova una differenza oppure ha controllato
     * tutti e 3 i caratteri della categoria (indice 3 = separatore '-'). */

    printf("Confronto categorie:\n");

    i = 0;
    stessa_categoria = 1; /* assume stessa categoria, falsifica se trova differenza */

    while (i < 3 && stessa_categoria) {
        /* Se il carattere in posizione i è diverso tra i due prodotti,
         * i prodotti appartengono a categorie diverse */
        if (prodotto1[i] != prodotto2[i]) {
            stessa_categoria = 0;
        }
        i++;
    }

    printf("  %s e %s: ", prodotto1, prodotto2);
    if (stessa_categoria) {
        printf("STESSA categoria (%s)\n", categoria);
    } else {
        printf("categorie DIVERSE\n");
    }

    /* --- CONFRONTO CATEGORIE: PRODOTTO 1 vs PRODOTTO 3 ---
     * Stesso algoritmo applicato alla coppia prodotto1/prodotto3. */
    i = 0;
    stessa_categoria = 1;

    while (i < 3 && stessa_categoria) {
        if (prodotto1[i] != prodotto3[i]) {
            stessa_categoria = 0;
        }
        i++;
    }

    printf("  %s e %s: ", prodotto1, prodotto3);
    if (stessa_categoria) {
        printf("STESSA categoria (%s)\n", categoria);
    } else {
        printf("categorie DIVERSE\n");
    }

    printf("\n");

    /* --- VERIFICA FORMATO DEL SEPARATORE ---
     * Controlla che i caratteri agli indici 3 e 7 siano effettivamente '-'.
     * È una verifica di integrità del codice prodotto. */
    printf("Verifica integrità formato %s:\n", prodotto1);

    if (prodotto1[3] == '-' && prodotto1[7] == '-') {
        printf("  Separatori '-' in posizione corretta: formato VALIDO\n");
    } else {
        printf("  ERRORE: separatori mancanti o in posizione errata\n");
    }

    printf("\n=== FINE ANALISI ===\n");

    return 0;
}
