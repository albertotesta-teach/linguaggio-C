/*
 * 050-problema-filtro-misure.c
 *
 * Rumore in mensa: misure filtrate con criteri diversi
 *
 * Un fonometro misura ogni 10 minuti il livello di rumore (in decibel)
 * nella mensa della scuola durante la pausa pranzo. Il referente per la
 * sicurezza vuole sapere quante misure superano la soglia di attenzione,
 * quante sono nella fascia "normale" e quanti momenti di quiete ci sono
 * stati, e vederle elencate.
 *
 * Due funzioni generali ricevono la CONDIZIONE come puntatore a funzione:
 *     int conta_se(const int *v, int n, int (*condizione)(int));
 *     void elenca_se(const int *v, int n, int (*condizione)(int));
 * Ogni condizione è una piccola funzione che riceve una misura e
 * restituisce 1 se la misura va considerata.
 */

#include <stdio.h>

#define MISURE 12
#define ATTENZIONE 80
#define QUIETE     60

int conta_se(const int *v, int n, int (*condizione)(int));
void elenca_se(const int *v, int n, int (*condizione)(int));
int rumorosa(int db);
int normale(int db);
int tranquilla(int db);

int main(void)
{
    int db[MISURE] = {62, 71, 78, 84, 88, 82, 76, 69, 58, 55, 66, 73};
    int n;

    printf("=== RUMORE IN MENSA (una misura ogni 10 minuti dalle 12:30) ===\n");
    n = conta_se(db, MISURE, rumorosa);
    printf("Oltre %d dB:   %2d %s ->", ATTENZIONE, n, n == 1 ? "misura" : "misure");
    elenca_se(db, MISURE, rumorosa);
    n = conta_se(db, MISURE, normale);
    printf("Da %d a %d dB: %2d %s ->", QUIETE, ATTENZIONE, n, n == 1 ? "misura" : "misure");
    elenca_se(db, MISURE, normale);
    n = conta_se(db, MISURE, tranquilla);
    printf("Sotto %d dB:   %2d %s ->", QUIETE, n, n == 1 ? "misura" : "misure");
    elenca_se(db, MISURE, tranquilla);

    return 0;
}

/* Numero di elementi per cui condizione restituisce 1. */
int conta_se(const int *v, int n, int (*condizione)(int))
{
    const int *p;
    int conteggio = 0;

    for (p = v; p < v + n; p++) {
        if (condizione(*p)) {
            conteggio++;
        }
    }
    return conteggio;
}

/* Stampa orario e valore degli elementi che soddisfano la condizione. */
void elenca_se(const int *v, int n, int (*condizione)(int))
{
    int i;
    int minuti;

    for (i = 0; i < n; i++) {
        if (condizione(v[i])) {
            minuti = 12 * 60 + 30 + i * 10;
            printf("  %02d:%02d %d", minuti / 60, minuti % 60, v[i]);
        }
    }
    printf("\n");
}

int rumorosa(int db)
{
    return db > ATTENZIONE;
}

int normale(int db)
{
    return db >= QUIETE && db <= ATTENZIONE;
}

int tranquilla(int db)
{
    return db < QUIETE;
}
