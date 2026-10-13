/*
 * 080-problema-copia-di-una-stringa.c
 *
 * Elenco dei nomi per i diplomi: ogni nome nella memoria che gli serve
 *
 * La segreteria scrive i nomi dei diplomati come capita ("mARTA  bassi",
 * "LUCA FERRI"). Il programma li legge uno per riga in un buffer di 80
 * caratteri e conserva una copia di ognuno nello heap, grande
 * esattamente quanto il nome:
 *
 *     copia = malloc(strlen(riga) + 1);     + 1 per il '\0' finale
 *     strcpy(copia, riga);
 *     elenco[n] = copia;
 *
 * elenco è un array di puntatori: ogni elemento punta a un blocco
 * diverso, della lunghezza del suo nome. Con una matrice char[50][80]
 * ogni nome occuperebbe 80 byte, anche se è lungo 10.
 *
 * Prima della copia la funzione normalizza sistema il nome nel buffer:
 * toglie gli spazi in più e scrive ogni parola con l'iniziale maiuscola
 * e il resto minuscolo. Così il blocco ha la lunghezza del nome finale.
 * Alla fine il programma stampa l'elenco, confronta i byte usati con
 * quelli di una matrice e libera i blocchi uno per uno.
 *
 * Una riga vuota (o di soli spazi) viene ignorata; FINE termina.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOMI 50
#define LUNG 80

void normalizza(char *testo);

int main(void)
{
    char *elenco[MAX_NOMI];
    char riga[LUNG];
    char *copia;
    int n = 0;
    int i;
    int finito = 0;
    size_t byte_usati = 0;

    printf("Nomi dei diplomati (FINE per terminare):\n");
    while (!finito && n < MAX_NOMI) {
        if (fgets(riga, LUNG, stdin) == NULL) {
            finito = 1;
        } else {
            riga[strcspn(riga, "\n")] = '\0';
            if (strcmp(riga, "FINE") == 0) {
                finito = 1;
            } else {
                normalizza(riga);
            }
            if (!finito && riga[0] != '\0') {
                copia = malloc(strlen(riga) + 1);
                if (copia == NULL) {
                    printf("Memoria insufficiente.\n");
                    finito = 1;
                } else {
                    strcpy(copia, riga);
                    elenco[n] = copia;
                    byte_usati = byte_usati + strlen(riga) + 1;
                    n++;
                }
            }
        }
    }

    printf("\nElenco per i diplomi:\n");
    for (i = 0; i < n; i++) {
        printf("  %2d. %-24s (%zu byte)\n", i + 1, elenco[i], strlen(elenco[i]) + 1);
    }
    printf("Byte nello heap: %zu (con una matrice char[%d][%d]: %d)\n", byte_usati, n, LUNG,
           n * LUNG);

    for (i = 0; i < n; i++) {
        free(elenco[i]);
    }

    return 0;
}

/*
 * Toglie gli spazi all'inizio, alla fine e quelli ripetuti; ogni parola
 * con l'iniziale maiuscola. Il testo può solo accorciarsi, quindi si
 * riscrive nello stesso blocco: j (scrittura) non supera mai i (lettura).
 */
void normalizza(char *testo)
{
    int i = 0;
    int j = 0;
    int inizio_parola = 1;

    while (testo[i] != '\0') {
        if (testo[i] == ' ') {
            inizio_parola = 1;
        } else {
            if (inizio_parola && j > 0) {
                testo[j] = ' ';
                j++;
            }
            if (inizio_parola) {
                testo[j] = (char) toupper((unsigned char) testo[i]);
            } else {
                testo[j] = (char) tolower((unsigned char) testo[i]);
            }
            j++;
            inizio_parola = 0;
        }
        i++;
    }
    testo[j] = '\0';
}
