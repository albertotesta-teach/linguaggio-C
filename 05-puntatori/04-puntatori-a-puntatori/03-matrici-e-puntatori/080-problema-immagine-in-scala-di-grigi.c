/*
 * 080-problema-immagine-in-scala-di-grigi.c
 *
 * Laboratorio di grafica: capovolgere e invertire una piccola immagine
 *
 * Nel laboratorio di grafica un'immagine in scala di grigi è una matrice
 * di livelli da 0 (nero) a 9 (bianco). Per vederla a terminale ogni
 * livello diventa un carattere, dal più vuoto al più pieno.
 *
 * Due operazioni:
 *   - capovolgi: scambia la prima riga con l'ultima, la seconda con la
 *     penultima, ... usando due PUNTATORI A RIGA, alto e basso, che si
 *     avvicinano finché alto < basso; ogni scambio di righe scambia gli
 *     elementi con due puntatori a int;
 *   - negativo: ogni livello v diventa 9 - v; non serve sapere in quale
 *     riga sia l'elemento, quindi l'immagine si scorre come blocco unico.
 */

#include <stdio.h>

#define RIGHE   6
#define COLONNE 10
#define LIVELLI " .:-=+*#%@"

void stampa(const int (*img)[COLONNE], int righe);
void capovolgi(int (*img)[COLONNE], int righe);
void negativo(int *p, int n);

int main(void)
{
    int immagine[RIGHE][COLONNE] = {
        {0, 0, 0, 0, 9, 9, 0, 0, 0, 0},
        {0, 0, 0, 9, 9, 9, 9, 0, 0, 0},
        {0, 0, 9, 9, 9, 9, 9, 9, 0, 0},
        {0, 0, 0, 0, 6, 6, 0, 0, 0, 0},
        {0, 0, 0, 0, 6, 6, 0, 0, 0, 0},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
    };

    printf("Originale:\n");
    stampa(immagine, RIGHE);

    capovolgi(immagine, RIGHE);
    printf("\nCapovolta:\n");
    stampa(immagine, RIGHE);

    negativo(&immagine[0][0], RIGHE * COLONNE);
    printf("\nNegativo:\n");
    stampa(immagine, RIGHE);

    return 0;
}

/* Stampa ogni livello con il carattere corrispondente di LIVELLI. */
void stampa(const int (*img)[COLONNE], int righe)
{
    const int (*riga)[COLONNE];
    int c;

    for (riga = img; riga < img + righe; riga++) {
        printf("  |");
        for (c = 0; c < COLONNE; c++) {
            printf("%c", LIVELLI[(*riga)[c]]);
        }
        printf("|\n");
    }
}

/* Scambia le righe dagli estremi verso il centro. */
void capovolgi(int (*img)[COLONNE], int righe)
{
    int (*alto)[COLONNE] = img;
    int (*basso)[COLONNE] = img + righe - 1;
    int *a;
    int *b;
    int temp;

    while (alto < basso) {
        a = *alto;
        b = *basso;
        while (a < *alto + COLONNE) {
            temp = *a;
            *a = *b;
            *b = temp;
            a++;
            b++;
        }
        alto++;
        basso--;
    }
}

/* Inverte i livelli di n elementi consecutivi. */
void negativo(int *p, int n)
{
    int *fine = p + n;

    while (p < fine) {
        *p = 9 - *p;
        p++;
    }
}
