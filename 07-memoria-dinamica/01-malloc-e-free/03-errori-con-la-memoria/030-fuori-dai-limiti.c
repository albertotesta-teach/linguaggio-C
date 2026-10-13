/*
 * 030-fuori-dai-limiti.c
 *
 * Scrivere fuori dal blocco: si rovina la memoria vicina
 *
 * Un blocco di n elementi ha gli indici da 0 a n - 1. Il C non controlla
 * gli indici: v[n] = 0 compila e viene eseguito, e scrive nei byte che
 * seguono il blocco. Quei byte possono appartenere a un altro blocco, ai
 * dati con cui malloc tiene traccia della memoria, o a nessuno: il
 * comportamento non è definito.
 *
 * Per vedere che cosa succede senza uscire davvero dalla memoria del
 * programma, qui due array stanno nello STESSO blocco, uno dopo l'altro:
 *
 *     int *blocco = malloc(2 * POSTI * sizeof *blocco);
 *     int *mattina = blocco;              posti da 0 a 3
 *     int *pomeriggio = blocco + POSTI;   subito dopo
 *
 *     mattina[POSTI] = ...;     fuori da mattina: è pomeriggio[0]!
 *
 * Un ciclo con <= al posto di < scrive un elemento di troppo e cambia
 * il primo posto del pomeriggio, senza nessun messaggio di errore.
 *
 * Errori di questo tipo si trovano compilando con
 *
 *     gcc -g -fsanitize=address programma.c
 *
 * (AddressSanitizer, disponibile in gcc e clang): il programma si ferma
 * alla prima scrittura fuori da un blocco e indica la riga.
 *
 * Esempio: le prenotazioni dei 4 computer dell'aula studio, mattina e
 * pomeriggio.
 */

#include <stdio.h>
#include <stdlib.h>

#define POSTI 4

void stampa(const char *turno, const int v[], int n);

int main(void)
{
    int *blocco = malloc(2 * POSTI * sizeof *blocco);
    int *mattina;
    int *pomeriggio;
    int i;

    if (blocco == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        mattina = blocco;
        pomeriggio = blocco + POSTI;
        for (i = 0; i < 2 * POSTI; i++) {
            blocco[i] = 0;
        }
        pomeriggio[0] = 17;                  /* matricola prenotata */
        stampa("mattina   ", mattina, POSTI);
        stampa("pomeriggio", pomeriggio, POSTI);

        printf("\nCiclo sbagliato: i <= POSTI\n");
        for (i = 0; i <= POSTI; i++) {
            mattina[i] = 1;          /* con i == POSTI esce da mattina */
        }
        stampa("mattina   ", mattina, POSTI);
        stampa("pomeriggio", pomeriggio, POSTI);
        printf("La prenotazione 17 del pomeriggio e' stata cancellata.\n");

        free(blocco);
    }

    return 0;
}

void stampa(const char *turno, const int v[], int n)
{
    int i;

    printf("  %s:", turno);
    for (i = 0; i < n; i++) {
        printf(" %3d", v[i]);
    }
    printf("\n");
}
