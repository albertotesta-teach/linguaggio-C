/*
 * 030-lettura-da-tastiera.c
 *
 * Riempire una matrice con valori letti da tastiera
 *
 * Una giuria di 3 giudici assegna a 4 concorrenti un punteggio da 0 a 10.
 * I punteggi vengono inseriti un giudice alla volta e memorizzati in una
 * matrice punteggi[GIUDICI][CONCORRENTI]: la riga è il giudice, la colonna
 * il concorrente.
 *
 * Ogni valore viene validato con un do-while: la domanda si ripete finché
 * il punteggio non è nell'intervallo [0, 10].
 *
 * Dopo l'inserimento la matrice viene stampata come tabella insieme al
 * totale di ogni concorrente (somma della sua colonna).
 */

#include <stdio.h>

#define GIUDICI      3
#define CONCORRENTI  4
#define PUNTEGGIO_MAX 10

int main(void)
{
    int punteggi[GIUDICI][CONCORRENTI];
    int giudice;
    int concorrente;
    int totale;

    printf("=== GARA DI CUCINA - INSERIMENTO PUNTEGGI ===\n");

    /* ── 1. Lettura: per righe (un giudice alla volta) ────────────────
     * Si passa a scanf l'indirizzo della singola cella:
     *     &punteggi[giudice][concorrente]                               */
    for (giudice = 0; giudice < GIUDICI; giudice++) {
        printf("\nGiudice %d\n", giudice + 1);
        for (concorrente = 0; concorrente < CONCORRENTI; concorrente++) {
            do {
                printf("  Punteggio al concorrente %d (0-%d): ",
                       concorrente + 1, PUNTEGGIO_MAX);
                scanf("%d", &punteggi[giudice][concorrente]);
                if (punteggi[giudice][concorrente] < 0
                    || punteggi[giudice][concorrente] > PUNTEGGIO_MAX) {
                    printf("  Valore non valido.\n");
                }
            } while (punteggi[giudice][concorrente] < 0
                     || punteggi[giudice][concorrente] > PUNTEGGIO_MAX);
        }
    }

    /* ── 2. Stampa della tabella ──────────────────────────────────── */
    printf("\n=== TABELLA DEI PUNTEGGI ===\n");
    printf("              ");
    for (concorrente = 0; concorrente < CONCORRENTI; concorrente++) {
        printf("  Conc.%d", concorrente + 1);
    }
    printf("\n");

    for (giudice = 0; giudice < GIUDICI; giudice++) {
        printf("  Giudice %d   ", giudice + 1);
        for (concorrente = 0; concorrente < CONCORRENTI; concorrente++) {
            printf("%8d", punteggi[giudice][concorrente]);
        }
        printf("\n");
    }

    /* ── 3. Totale per concorrente: somma della colonna ───────────── */
    printf("  Totale      ");
    for (concorrente = 0; concorrente < CONCORRENTI; concorrente++) {
        totale = 0;
        for (giudice = 0; giudice < GIUDICI; giudice++) {
            totale = totale + punteggi[giudice][concorrente];
        }
        printf("%8d", totale);
    }
    printf("\n");

    /*
     * ERRORE COMUNE: dimenticare la & in scanf.
     *     scanf("%d", punteggi[giudice][concorrente]);    // ERRATO
     * scanf vuole l'indirizzo della cella in cui scrivere. Con -Wall gcc
     * segnala che l'argomento ha il tipo sbagliato.
     */

    return 0;
}
