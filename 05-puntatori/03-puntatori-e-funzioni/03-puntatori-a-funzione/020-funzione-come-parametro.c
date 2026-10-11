/*
 * 020-funzione-come-parametro.c
 *
 * Passare una funzione a un'altra funzione
 *
 * Il caso più utile dei puntatori a funzione è il PARAMETRO: una funzione
 * generale riceve, oltre ai dati, la funzione da applicare. Una funzione
 * passata in questo modo si chiama spesso CALLBACK ("richiamata").
 *
 *     void applica(int *v, int n, int (*trasforma)(int));
 *
 *     applica(punti, N, raddoppia);       trasforma = raddoppia
 *     applica(punti, N, minimo_zero);     trasforma = minimo_zero
 *
 * applica scorre l'array una volta sola e per ogni elemento chiama
 * trasforma: il ciclo è scritto una volta, il "che cosa fare" cambia a ogni
 * chiamata.
 *
 * Esempio: i punteggi di una gara di matematica a squadre. Le risposte
 * sbagliate danno punti negativi; il regolamento prevede di raddoppiare il
 * punteggio della prova finale, di non scendere sotto zero e di arrotondare
 * alla decina.
 */

#include <stdio.h>

#define SQUADRE 6

void applica(int *v, int n, int (*trasforma)(int));
int raddoppia(int x);
int minimo_zero(int x);
int alla_decina(int x);
void stampa(const char titolo[], const int *v, int n);

int main(void)
{
    int punti[SQUADRE] = {34, -6, 57, 12, -15, 41};

    stampa("Punteggi grezzi       ", punti, SQUADRE);

    applica(punti, SQUADRE, raddoppia);
    stampa("applica(raddoppia)    ", punti, SQUADRE);

    applica(punti, SQUADRE, minimo_zero);
    stampa("applica(minimo_zero)  ", punti, SQUADRE);

    applica(punti, SQUADRE, alla_decina);
    stampa("applica(alla_decina)  ", punti, SQUADRE);

    return 0;
}

/* Sostituisce ogni elemento con il risultato di trasforma(elemento). */
void applica(int *v, int n, int (*trasforma)(int))
{
    int *p;

    for (p = v; p < v + n; p++) {
        *p = trasforma(*p);
    }
}

int raddoppia(int x)
{
    return 2 * x;
}

int minimo_zero(int x)
{
    return x < 0 ? 0 : x;
}

/* Arrotonda alla decina più vicina (5 si arrotonda per eccesso). */
int alla_decina(int x)
{
    return (x + 5) / 10 * 10;
}

void stampa(const char titolo[], const int *v, int n)
{
    int i;

    printf("%s", titolo);
    for (i = 0; i < n; i++) {
        printf("%5d", v[i]);
    }
    printf("\n");
}
