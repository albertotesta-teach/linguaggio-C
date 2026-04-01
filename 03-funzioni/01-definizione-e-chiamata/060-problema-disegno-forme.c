/*
 * 060-problema-disegno-forme.c
 *
 * Disegno di forme geometriche in ASCII art
 *
 * Un programma didattico mostra tre forme geometriche disegnate
 * con caratteri ASCII: un rettangolo, un triangolo rettangolo
 * e una cornice decorativa. Ogni forma è responsabilità di una
 * funzione dedicata. Le dimensioni sono fisse (definite con #define)
 * ma il codice mostra come organizzare il disegno in modo modulare.
 *
 * Nota: nel capitolo sui parametri impareremo a rendere le dimensioni
 * configurabili dall'esterno della funzione.
 */

#include <stdio.h>

/* Dimensioni delle forme - modificando queste costanti
 * si cambiano tutte le forme contemporaneamente */
#define LARGHEZZA  8
#define ALTEZZA    5

/* Prototipi */
void disegna_rettangolo(void);
void disegna_triangolo(void);
void disegna_cornice(void);
void disegna_tutte_le_forme(void);

/* --- Implementazioni --- */

/* Rettangolo pieno: ALTEZZA righe, ciascuna di LARGHEZZA asterischi */
void disegna_rettangolo(void)
{
    int riga;
    int colonna;

    printf("Rettangolo (%dx%d):\n", LARGHEZZA, ALTEZZA);

    riga = 0;
    while (riga < ALTEZZA) {
        colonna = 0;
        while (colonna < LARGHEZZA) {
            printf("*");
            colonna++;
        }
        printf("\n");
        riga++;
    }
}

/* Triangolo rettangolo: la riga i ha i asterischi (i da 1 ad ALTEZZA) */
void disegna_triangolo(void)
{
    int riga;
    int colonna;

    printf("Triangolo rettangolo (base %d):\n", ALTEZZA);

    riga = 1;
    while (riga <= ALTEZZA) {
        colonna = 1;
        while (colonna <= riga) {
            printf("*");
            colonna++;
        }
        printf("\n");
        riga++;
    }
}

/* Cornice: solo il bordo esterno del rettangolo è disegnato.
 * La prima e l'ultima riga sono piene, le righe intermedie hanno
 * solo il primo e l'ultimo carattere. */
void disegna_cornice(void)
{
    int riga;
    int colonna;

    printf("Cornice (%dx%d):\n", LARGHEZZA, ALTEZZA);

    riga = 0;
    while (riga < ALTEZZA) {
        colonna = 0;
        while (colonna < LARGHEZZA) {
            /* Riga superiore o inferiore: tutta piena */
            if (riga == 0 || riga == ALTEZZA - 1) {
                printf("*");
            } else {
                /* Righe intermedie: solo bordo sinistro e destro */
                if (colonna == 0 || colonna == LARGHEZZA - 1) {
                    printf("*");
                } else {
                    printf(" ");
                }
            }
            colonna++;
        }
        printf("\n");
        riga++;
    }
}

/* Funzione che stampa tutte le forme con una riga vuota di separazione */
void disegna_tutte_le_forme(void)
{
    disegna_rettangolo();
    printf("\n");
    disegna_triangolo();
    printf("\n");
    disegna_cornice();
}

int main(void)
{
    printf("=== Galleria di forme ASCII ===\n\n");
    disegna_tutte_le_forme();
    return 0;
}
