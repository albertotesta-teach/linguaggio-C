/*
 * 010-lunghezza-manuale.c
 *
 * Calcolo della lunghezza di una stringa senza usare strlen.
 *
 * In C la funzione strlen della libreria <string.h> calcola la lunghezza
 * di una stringa. Ma come funziona internamente? Scorre l'array carattere
 * per carattere finché non trova '\0', contando i passi.
 *
 * Questo esempio mostra come implementare lo stesso meccanismo
 * manualmente, chiarendo la differenza tra:
 *   - lunghezza della stringa: numero di caratteri prima di '\0'
 *   - dimensione dell'array:   numero totale di celle allocate
 *
 * Esempio:
 *   char s[20] = "Ciao";
 *   lunghezza = 4   (i caratteri 'C','i','a','o')
 *   dimensione = 20 (le celle dell'array)
 */

#include <stdio.h>

int main(void) {

    /* Stringhe di esempio con dimensioni sovradimensionate
     * per evidenziare la differenza tra lunghezza e dimensione */
    char saluto[50]   = "Buongiorno";
    char vuota[50]    = "";
    char con_spazi[50] = "Via Roma 12";

    /* Contatore per la lunghezza */
    int lunghezza;

    /* Indice per scorrere la stringa */
    int i;

    printf("=== CALCOLO MANUALE DELLA LUNGHEZZA ===\n\n");

    /* --- ESEMPIO 1: stringa normale ---
     * Il ciclo while incrementa il contatore finché non trova '\0'.
     * L'indice finale corrisponde alla lunghezza della stringa. */
    lunghezza = 0;
    while (saluto[lunghezza] != '\0') {
        lunghezza++; /* ogni carattere trovato prima di '\0' conta 1 */
    }
    printf("Stringa   : \"%s\"\n", saluto);
    printf("Lunghezza : %d caratteri\n", lunghezza);
    printf("Dimensione array: 50 celle\n");
    printf("Celle usate: %d (stringa) + 1 (terminatore) + %d (libere)\n\n",
           lunghezza, 50 - lunghezza - 1);

    /* --- ESEMPIO 2: stringa vuota ---
     * Una stringa vuota ha '\0' in posizione 0: il ciclo
     * non esegue nemmeno un'iterazione, lunghezza rimane 0. */
    lunghezza = 0;
    while (vuota[lunghezza] != '\0') {
        lunghezza++;
    }
    printf("Stringa   : \"%s\" (stringa vuota)\n", vuota);
    printf("Lunghezza : %d caratteri\n\n", lunghezza);

    /* --- ESEMPIO 3: stringa con spazi ---
     * Gli spazi sono caratteri normali (ASCII 32) e vengono contati.
     * Solo '\0' segna la fine della stringa. */
    lunghezza = 0;
    while (con_spazi[lunghezza] != '\0') {
        lunghezza++;
    }
    printf("Stringa   : \"%s\"\n", con_spazi);
    printf("Lunghezza : %d caratteri (spazi inclusi)\n\n", lunghezza);

    /* --- VISUALIZZAZIONE CARATTERE PER CARATTERE ---
     * Mostra ogni carattere con il suo indice per rendere visibile
     * come il ciclo percorre la stringa fino a '\0'. */
    printf("Mappa carattere per carattere di \"%s\":\n", saluto);
    printf("%-6s %-10s %-6s\n", "Indice", "Carattere", "ASCII");
    printf("-------------------------\n");

    i = 0;
    while (saluto[i] != '\0') {
        printf("%-6d %-10c %-6d\n", i, saluto[i], (int)saluto[i]);
        i++;
    }
    printf("%-6d %-10s %-6d  ← terminatore\n", i, "\\0", 0);

    return 0;
}
