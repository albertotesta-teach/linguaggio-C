/*
 * 030-struct-allocata.c
 *
 * Una struct nello heap, raggiunta con l'operatore freccia
 *
 * malloc funziona con qualsiasi tipo: per una struct si chiede un blocco
 * grande quanto la struct e lo si usa tramite il puntatore.
 *
 *     Studente *s = malloc(sizeof *s);
 *
 *     strcpy(s->nome, "Marta Bassi");
 *     s->media = 8.2;
 *
 * s è un puntatore, quindi i campi si raggiungono con la freccia, come
 * per un puntatore a una struct locale (06-strutture-e-unioni). Un'unica
 * free restituisce tutto il blocco, con tutti i campi, compresi gli
 * array che la struct contiene.
 *
 * Anche un array di struct si alloca con una sola malloc:
 *
 *     Studente *classe = malloc(n * sizeof *classe);
 *     classe[i].media              elemento i: si usa il punto
 *
 * classe[i] è una struct (non un puntatore), quindi i suoi campi si
 * raggiungono con il punto.
 *
 * Esempio: il rappresentante di classe in una struct nello heap e i
 * candidati in un array di struct nello heap.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CANDIDATI 3

typedef struct {
    char nome[24];
    char classe[4];
    int voti;
} Studente;

int main(void)
{
    const char *nomi[CANDIDATI] = {"Marta Bassi", "Luca Ferri", "Sara Conti"};
    const char *classi[CANDIDATI] = {"3B", "3A", "3B"};
    int voti[CANDIDATI] = {41, 37, 52};
    Studente *candidati;
    Studente *eletto;
    int migliore = 0;
    int i;

    candidati = malloc(CANDIDATI * sizeof *candidati);
    eletto = malloc(sizeof *eletto);
    if (candidati == NULL || eletto == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        printf("sizeof(Studente) = %zu byte\n", sizeof(Studente));
        printf("candidati: blocco di %zu byte\n\n", CANDIDATI * sizeof *candidati);

        for (i = 0; i < CANDIDATI; i++) {
            strcpy(candidati[i].nome, nomi[i]);
            strcpy(candidati[i].classe, classi[i]);
            candidati[i].voti = voti[i];
            printf("%-12s %-3s %2d voti\n", candidati[i].nome, candidati[i].classe,
                   candidati[i].voti);
            if (candidati[i].voti > candidati[migliore].voti) {
                migliore = i;
            }
        }

        *eletto = candidati[migliore];
        printf("\nEletto: %s (%s) con %d voti\n", eletto->nome, eletto->classe,
               eletto->voti);
    }

    /* free(NULL) non fa nulla: le due free sono corrette anche se una
       sola delle due malloc è riuscita */
    free(candidati);
    free(eletto);

    return 0;
}
