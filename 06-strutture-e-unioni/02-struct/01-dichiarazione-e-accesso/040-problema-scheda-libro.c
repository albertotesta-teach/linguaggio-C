/*
 * 040-problema-scheda-libro.c
 *
 * Biblioteca scolastica: la scheda di un libro con le copie disponibili
 *
 * La biblioteca tiene per ogni titolo una scheda con titolo, autore, anno,
 * numero di copie possedute e numero di copie in prestito. Il bibliotecario
 * apre la scheda di un libro e registra i movimenti:
 *     P   prestito di una copia (solo se ce n'è una disponibile)
 *     R   restituzione di una copia (solo se ce n'è una in prestito)
 *     S   stampa della scheda
 *     Q   fine
 *
 *     typedef struct {
 *         char titolo[40];
 *         char autore[30];
 *         int anno;
 *         int copie;
 *         int in_prestito;
 *     } Libro;
 *
 * Tutti i dati del libro stanno in una sola variabile: per sapere quante
 * copie sono disponibili si usano due campi della stessa scheda,
 * libro.copie - libro.in_prestito.
 */

#include <stdio.h>

typedef struct {
    char titolo[40];
    char autore[30];
    int anno;
    int copie;
    int in_prestito;
} Libro;

int main(void)
{
    Libro libro = {"Il sentiero dei nidi di ragno", "Italo Calvino", 1947, 3, 1};
    char comando = ' ';
    int prestiti_oggi = 0;

    printf("Scheda aperta: %s\n", libro.titolo);
    while (comando != 'Q') {
        printf("Comando (P prestito, R restituzione, S scheda, Q fine): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'P') {
            if (libro.in_prestito < libro.copie) {
                libro.in_prestito++;
                prestiti_oggi++;
                printf("  Prestito registrato. Copie disponibili: %d\n", libro.copie - libro.in_prestito);
            } else {
                printf("  Nessuna copia disponibile.\n");
            }
        } else if (comando == 'R') {
            if (libro.in_prestito > 0) {
                libro.in_prestito--;
                printf("  Restituzione registrata. Copie disponibili: %d\n",
                       libro.copie - libro.in_prestito);
            } else {
                printf("  Nessuna copia risulta in prestito.\n");
            }
        } else if (comando == 'S') {
            printf("  Titolo:      %s\n", libro.titolo);
            printf("  Autore:      %s (%d)\n", libro.autore, libro.anno);
            printf("  Copie:       %d, in prestito %d, disponibili %d\n",
                   libro.copie, libro.in_prestito, libro.copie - libro.in_prestito);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }
    printf("Prestiti registrati in questa sessione: %d\n", prestiti_oggi);

    return 0;
}
