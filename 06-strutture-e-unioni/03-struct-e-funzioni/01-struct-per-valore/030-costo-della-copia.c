/*
 * 030-costo-della-copia.c
 *
 * Passare per valore una struct grande: quanti byte si copiano
 *
 * Una struct con un array grande, come il registro con tutti i voti
 * dell'anno di una classe, occupa molta memoria. Passarla per valore
 * significa copiarla per intero A OGNI CHIAMATA:
 *
 *     double media(Registro r);        copia di sizeof(Registro) byte
 *
 * Il programma fa tre chiamate per valore e stampa quanti byte sono stati
 * copiati in tutto. Per struct piccole (una Frazione, un Orario, un Punto)
 * la copia non è un problema; per struct grandi conviene passare
 * l'indirizzo, che occupa sempre 8 byte: è l'argomento della sezione
 * 02-puntatori-a-struct.
 *
 * Esempio: il registro di una classe con fino a 200 voti, di cui si
 * calcolano la media, il voto massimo e il numero di insufficienze.
 */

#include <stdio.h>

#define MAX_VOTI 200

typedef struct {
    char classe[4];
    int voti[MAX_VOTI];
    int n_voti;
} Registro;

double media(Registro r);
int massimo(Registro r);
int insufficienze(Registro r);

int main(void)
{
    Registro r = {"3B", {7, 6, 8, 5, 9, 6, 7, 4, 8, 6, 7, 5}, 12};
    int chiamate = 3;

    printf("Registro della %s: %d voti\n", r.classe, r.n_voti);
    printf("  media %.2f, massimo %d, insufficienze %d\n", media(r), massimo(r), insufficienze(r));

    printf("\nsizeof(Registro) = %zu byte\n", sizeof(Registro));
    printf("%d chiamate per valore: %zu byte copiati\n", chiamate, chiamate * sizeof(Registro));
    printf("Un indirizzo occupa %zu byte\n", sizeof(&r));

    return 0;
}

/* Ognuna delle tre funzioni riceve una copia completa del registro. */
double media(Registro r)
{
    int somma = 0;
    int i;

    for (i = 0; i < r.n_voti; i++) {
        somma = somma + r.voti[i];
    }
    return (double) somma / r.n_voti;
}

int massimo(Registro r)
{
    int piu_alto = r.voti[0];
    int i;

    for (i = 1; i < r.n_voti; i++) {
        if (r.voti[i] > piu_alto) {
            piu_alto = r.voti[i];
        }
    }
    return piu_alto;
}

int insufficienze(Registro r)
{
    int conteggio = 0;
    int i;

    for (i = 0; i < r.n_voti; i++) {
        if (r.voti[i] < 6) {
            conteggio++;
        }
    }
    return conteggio;
}
