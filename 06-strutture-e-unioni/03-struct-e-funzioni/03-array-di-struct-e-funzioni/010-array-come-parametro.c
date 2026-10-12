/*
 * 010-array-come-parametro.c
 *
 * Passare un array di struct a una funzione
 *
 * Un array di struct si passa come ogni array: la funzione riceve
 * l'indirizzo del primo elemento e il numero di elementi va passato a
 * parte.
 *
 *     double media_classe(const Studente classe[], int n);   sola lettura
 *     void arrotonda(Studente classe[], int n);              modifica gli elementi
 *
 * const Studente classe[] equivale a const Studente *classe: niente copia
 * dell'array e nessuna modifica possibile. Dentro la funzione ogni
 * elemento si raggiunge con classe[i].campo.
 *
 * Un singolo elemento si passa a una funzione che lavora su UNO studente
 * con il suo indirizzo: stampa(&classe[i]).
 *
 * Esempio: le medie di fine anno di una classe, arrotondate al mezzo voto
 * per lo scrutinio.
 */

#include <stdio.h>

#define STUDENTI 5

typedef struct {
    char nome[20];
    double media;
} Studente;

double media_classe(const Studente classe[], int n);
void arrotonda(Studente classe[], int n);
void stampa(const Studente *s);

int main(void)
{
    Studente classe[STUDENTI] = {
        {"Bianchi Sara", 7.82},
        {"Colombo Luca", 6.18},
        {"Esposito Anna", 8.36},
        {"Ferrari Marco", 5.71},
        {"Galli Irene", 6.94}
    };
    int i;

    printf("Medie calcolate:\n");
    for (i = 0; i < STUDENTI; i++) {
        stampa(&classe[i]);
    }
    printf("  media della classe %.2f\n", media_classe(classe, STUDENTI));

    arrotonda(classe, STUDENTI);

    printf("\nMedie arrotondate al mezzo voto:\n");
    for (i = 0; i < STUDENTI; i++) {
        stampa(&classe[i]);
    }
    printf("  media della classe %.2f\n", media_classe(classe, STUDENTI));

    return 0;
}

double media_classe(const Studente classe[], int n)
{
    double somma = 0;
    int i;

    for (i = 0; i < n; i++) {
        somma = somma + classe[i].media;
    }
    return somma / n;
}

/* Modifica gli elementi del chiamante: 7.82 -> 8.0, 6.18 -> 6.0, 5.71 -> 5.5 */
void arrotonda(Studente classe[], int n)
{
    int i;

    for (i = 0; i < n; i++) {
        classe[i].media = (int) (classe[i].media * 2 + 0.5) / 2.0;
    }
}

void stampa(const Studente *s)
{
    printf("  %-14s %5.2f\n", s->nome, s->media);
}
