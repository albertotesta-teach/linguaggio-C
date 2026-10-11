/*
 * 030-switch-su-caratteri.c
 *
 * switch con un carattere: menu a lettere
 *
 * Il tipo char è un tipo intero (ogni carattere corrisponde al suo codice
 * ASCII), quindi può essere usato in uno switch. Le costanti dei case
 * sono caratteri tra apici singoli: 'A', 'b', '+'.
 *
 * Per accettare sia la lettera maiuscola sia la minuscola si
 * raggruppano i due case.
 *
 * Il programma legge una scelta da tastiera: " %c" con lo spazio iniziale
 * salta eventuali spazi e invii rimasti dall'input precedente.
 */

#include <stdio.h>

int main(void)
{
    char scelta;
    double importo = 250.00;

    printf("=== CONTO CORRENTE - MENU ===\n");
    printf("  S - Saldo\n");
    printf("  M - Movimenti\n");
    printf("  B - Bonifico\n");
    printf("  E - Esci\n");
    printf("Scelta: ");
    scanf(" %c", &scelta);

    printf("\n");

    switch (scelta) {
        case 'S':
        case 's':
            printf("Saldo disponibile: %.2f euro\n", importo);
            break;
        case 'M':
        case 'm':
            printf("Ultimi movimenti:\n");
            printf("  03/10  stipendio        +1450.00\n");
            printf("  05/10  bolletta luce      -78.40\n");
            break;
        case 'B':
        case 'b':
            printf("Funzione bonifico: disponibile allo sportello.\n");
            break;
        case 'E':
        case 'e':
            printf("Arrivederci.\n");
            break;
        default:
            printf("Scelta '%c' non valida.\n", scelta);
            break;
    }

    /*
     * ERRORE COMUNE: usare le virgolette doppie.
     *
     *     case "S":      // ERRORE: "S" è una stringa, non un carattere
     *     case 'S':      // corretto
     *
     * Altro errore: dimenticare il case per la minuscola, così l'utente
     * che digita 's' ottiene "Scelta non valida".
     */

    return 0;
}
