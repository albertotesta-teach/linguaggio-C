/*
 * 010-lunghezza-e-capacita.c
 *
 * Un vettore dinamico: dati, lunghezza e capacità in una struct
 *
 * Un array allocato nello heap non ricorda né quanti posti ha né quanti
 * ne sono usati. Il vettore dinamico tiene le tre informazioni insieme:
 *
 *     typedef struct {
 *         int *dati;         blocco nello heap
 *         int n;             elementi usati (lunghezza)
 *         int capacita;      posti allocati
 *     } Vettore;
 *
 *     dati:  [ 7 | 3 | 9 | 4 |   |   |   |   ]
 *             <---- n = 4 ---->
 *             <-------- capacita = 8 -------->
 *
 * Sempre 0 <= n <= capacita. Finché n < capacita, aggiungere un elemento
 * costa solo una scrittura: dati[n] = valore; n++. Solo quando il vettore
 * è pieno serve una realloc (020-crescita-a-raddoppio).
 *
 * Esempio: un vettore con capacità 8 riceve 6 numeri di maglia della
 * squadra di pallavolo; il programma stampa a ogni passo lunghezza,
 * capacità e posti liberi, senza mai chiamare realloc.
 */

#include <stdio.h>
#include <stdlib.h>

#define CAPACITA_INIZIALE 8
#define GIOCATORI 6

typedef struct {
    int *dati;
    int n;
    int capacita;
} Vettore;

void stampa(const Vettore *v);

int main(void)
{
    int maglie[GIOCATORI] = {7, 3, 9, 4, 12, 1};
    Vettore squadra;
    int i;

    squadra.dati = malloc(CAPACITA_INIZIALE * sizeof *squadra.dati);
    squadra.n = 0;
    squadra.capacita = CAPACITA_INIZIALE;

    if (squadra.dati == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        stampa(&squadra);
        for (i = 0; i < GIOCATORI; i++) {
            squadra.dati[squadra.n] = maglie[i];
            squadra.n++;
            stampa(&squadra);
        }
        printf("Byte allocati: %zu, usati: %zu\n", squadra.capacita * sizeof *squadra.dati,
               squadra.n * sizeof *squadra.dati);
        free(squadra.dati);
    }

    return 0;
}

void stampa(const Vettore *v)
{
    int i;

    printf("n = %d, capacita = %d, liberi = %d  [", v->n, v->capacita, v->capacita - v->n);
    for (i = 0; i < v->capacita; i++) {
        if (i < v->n) {
            printf("%3d", v->dati[i]);
        } else {
            printf("  .");
        }
    }
    printf(" ]\n");
}
