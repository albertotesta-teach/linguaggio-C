/*
 * 040-confronto-carattere-per-carattere.c
 *
 * Confronto manuale tra due stringhe senza usare strcmp.
 *
 * In C la funzione strcmp di <string.h> confronta due stringhe.
 * Internamente scorre entrambe le stringhe in parallelo, confrontando
 * i caratteri uno a uno fino a trovare una differenza o '\0'.
 *
 * Il risultato del confronto è:
 *   0  → le stringhe sono uguali
 *  <0  → la prima stringa viene prima lessicograficamente
 *  >0  → la prima stringa viene dopo lessicograficamente
 *
 * Il confronto lessicografico si basa sui valori ASCII:
 *   'A' = 65, 'B' = 66, ... 'Z' = 90
 *   'a' = 97, 'b' = 98, ... 'z' = 122
 *
 * Quindi "Banana" < "banana" perché 'B'(66) < 'b'(98).
 */

#include <stdio.h>

int main(void) {

    /* Coppie di stringhe da confrontare */
    char stringa1[30] = "Mela";
    char stringa2[30] = "Mela";
    char stringa3[30] = "Pera";
    char stringa4[30] = "mela";

    /* Indice per scorrere le due stringhe in parallelo */
    int i;

    /* Risultato del confronto:
     *  0 = uguali
     * -1 = stringa A viene prima
     *  1 = stringa A viene dopo */
    int risultato;

    printf("=== CONFRONTO MANUALE TRA STRINGHE ===\n\n");

    /* --- CONFRONTO 1: stringhe uguali ---
     * Il ciclo scorre finché i caratteri sono uguali E non siamo
     * arrivati alla fine di entrambe le stringhe. */
    printf("Confronto 1: \"%s\" vs \"%s\"\n", stringa1, stringa2);

    i = 0;
    while (stringa1[i] != '\0' && stringa2[i] != '\0' &&
           stringa1[i] == stringa2[i]) {
        i++; /* caratteri uguali: avanza */
    }

    /* Dopo il ciclo, controlliamo perché si è fermato:
     * - entrambi '\0' → stringhe uguali
     * - caratteri diversi → confronto ASCII determina l'ordine */
    if (stringa1[i] == '\0' && stringa2[i] == '\0') {
        risultato = 0;
    } else if (stringa1[i] < stringa2[i]) {
        risultato = -1;
    } else {
        risultato = 1;
    }

    if (risultato == 0) {
        printf("  Risultato: UGUALI\n\n");
    } else if (risultato < 0) {
        printf("  Risultato: \"%s\" viene PRIMA di \"%s\"\n\n",
               stringa1, stringa2);
    } else {
        printf("  Risultato: \"%s\" viene DOPO \"%s\"\n\n",
               stringa1, stringa2);
    }

    /* --- CONFRONTO 2: stringhe diverse ---
     * "Mela" vs "Pera": 'M'(77) < 'P'(80) → "Mela" viene prima */
    printf("Confronto 2: \"%s\" vs \"%s\"\n", stringa1, stringa3);

    i = 0;
    while (stringa1[i] != '\0' && stringa3[i] != '\0' &&
           stringa1[i] == stringa3[i]) {
        i++;
    }

    if (stringa1[i] == '\0' && stringa3[i] == '\0') {
        risultato = 0;
    } else if (stringa1[i] < stringa3[i]) {
        risultato = -1;
    } else {
        risultato = 1;
    }

    printf("  Primo carattere diverso: '%c'(%d) vs '%c'(%d)\n",
           stringa1[i], (int)stringa1[i],
           stringa3[i], (int)stringa3[i]);

    if (risultato == 0) {
        printf("  Risultato: UGUALI\n\n");
    } else if (risultato < 0) {
        printf("  Risultato: \"%s\" viene PRIMA di \"%s\"\n\n",
               stringa1, stringa3);
    } else {
        printf("  Risultato: \"%s\" viene DOPO \"%s\"\n\n",
               stringa1, stringa3);
    }

    /* --- CONFRONTO 3: maiuscolo vs minuscolo ---
     * "Mela" vs "mela": 'M'(77) < 'm'(109) → "Mela" viene prima.
     * Attenzione: il confronto è case-sensitive per default. */
    printf("Confronto 3: \"%s\" vs \"%s\" (case-sensitive)\n",
           stringa1, stringa4);

    i = 0;
    while (stringa1[i] != '\0' && stringa4[i] != '\0' &&
           stringa1[i] == stringa4[i]) {
        i++;
    }

    if (stringa1[i] == '\0' && stringa4[i] == '\0') {
        risultato = 0;
    } else if (stringa1[i] < stringa4[i]) {
        risultato = -1;
    } else {
        risultato = 1;
    }

    printf("  Primo carattere diverso: '%c'(%d) vs '%c'(%d)\n",
           stringa1[i], (int)stringa1[i],
           stringa4[i], (int)stringa4[i]);

    if (risultato == 0) {
        printf("  Risultato: UGUALI\n\n");
    } else if (risultato < 0) {
        printf("  Risultato: \"%s\" viene PRIMA di \"%s\"\n\n",
               stringa1, stringa4);
    } else {
        printf("  Risultato: \"%s\" viene DOPO di \"%s\"\n\n",
               stringa1, stringa4);
    }

    printf("NOTA: strcmp() in <string.h> implementa questo stesso\n");
    printf("algoritmo in modo ottimizzato. Ora sai come funziona!\n");

    return 0;
}
