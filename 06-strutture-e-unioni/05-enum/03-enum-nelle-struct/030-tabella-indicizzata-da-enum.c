/*
 * 030-tabella-indicizzata-da-enum.c
 *
 * Un array di struct indicizzato da un enum
 *
 * Quando ogni costante di un enum ha diverse informazioni associate, si
 * raccolgono in una struct e si fa un array di struct indicizzato
 * dall'enum:
 *
 *     typedef enum { STUDENTE, DOCENTE, FAMILIARE, ESTERNO,
 *                    NUM_CATEGORIE } Categoria;
 *
 *     typedef struct {
 *         const char *nome;
 *         double prezzo;
 *         int posti_riservati;
 *     } Tariffa;
 *
 *     Tariffa tariffe[NUM_CATEGORIE] = {
 *         [STUDENTE] = {"studente", 3.00, 6}, ...
 *     };
 *
 *     tariffe[b.categoria].prezzo
 *
 * Al posto di uno switch per il prezzo, uno per il nome e uno per i
 * posti, c'è una sola tabella da leggere e da aggiornare.
 *
 * Esempio: lo spettacolo di fine anno nell'aula magna. Il programma
 * conta i biglietti venduti per categoria, calcola l'incasso e controlla
 * i posti riservati a ogni categoria.
 */

#include <stdio.h>

#define BIGLIETTI 12

typedef enum {
    STUDENTE, DOCENTE, FAMILIARE, ESTERNO, NUM_CATEGORIE
} Categoria;

typedef struct {
    const char *nome;
    double prezzo;
    int posti_riservati;
} Tariffa;

typedef struct {
    int numero;
    Categoria categoria;
} Biglietto;

int main(void)
{
    Tariffa tariffe[NUM_CATEGORIE] = {
        [STUDENTE] = {"studente", 3.00, 6},
        [DOCENTE] = {"docente", 0.00, 2},
        [FAMILIARE] = {"familiare", 5.00, 3},
        [ESTERNO] = {"esterno", 8.00, 1}
    };
    Biglietto venduti[BIGLIETTI] = {
        {1, STUDENTE}, {2, FAMILIARE}, {3, FAMILIARE}, {4, STUDENTE}, {5, DOCENTE},
        {6, ESTERNO}, {7, STUDENTE}, {8, FAMILIARE}, {9, FAMILIARE}, {10, ESTERNO},
        {11, STUDENTE}, {12, DOCENTE}
    };
    int quanti[NUM_CATEGORIE] = {0};
    double incasso = 0;
    Categoria c;
    int i;

    for (i = 0; i < BIGLIETTI; i++) {
        quanti[venduti[i].categoria]++;
        incasso = incasso + tariffe[venduti[i].categoria].prezzo;
    }

    printf("Categoria   Prezzo  Venduti  Riservati\n");
    for (c = STUDENTE; c < NUM_CATEGORIE; c++) {
        printf("%-10s %6.2f %8d %10d%s\n", tariffe[c].nome, tariffe[c].prezzo, quanti[c],
               tariffe[c].posti_riservati,
               quanti[c] > tariffe[c].posti_riservati ? "  OLTRE I POSTI RISERVATI" : "");
    }
    printf("Incasso: %.2f euro\n", incasso);

    return 0;
}
