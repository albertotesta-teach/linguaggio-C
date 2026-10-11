/*
 * 010-matrice-in-memoria.c
 *
 * Come è disposta una matrice in memoria
 *
 * Una matrice int m[3][4] è un array di 3 righe, ciascuna un array di 4
 * int. In memoria le righe sono una dopo l'altra: prima tutta la riga 0,
 * poi tutta la riga 1, e così via (ordine per righe).
 *
 *     m[i]              la riga i: un array di 4 int (indirizzo &m[i][0])
 *     m + i             indirizzo della riga i (avanza di una riga intera)
 *     *(m + i) + j      indirizzo dell'elemento j della riga i
 *     *(*(m + i) + j)   l'elemento: equivale a m[i][j]
 *
 *     &m[0][0] + i * 4 + j     lo stesso elemento contato dall'inizio
 *
 * Esempio: i posti di una piccola aula studio, 3 file da 4 banchi, con il
 * numero di prenotazioni della settimana per ogni banco.
 */

#include <stdio.h>

#define FILE_BANCHI 3
#define BANCHI      4

int main(void)
{
    int prenotazioni[FILE_BANCHI][BANCHI] = {
        {5, 2, 0, 3},
        {4, 6, 1, 2},
        {0, 3, 7, 5}
    };
    int i;
    int j;

    printf("=== INDIRIZZI DEGLI ELEMENTI (ordine per righe) ===\n");
    for (i = 0; i < FILE_BANCHI; i++) {
        printf("  riga %d:", i);
        for (j = 0; j < BANCHI; j++) {
            printf("  %p", (void *) &prenotazioni[i][j]);
        }
        printf("\n");
    }
    printf("Ogni elemento e' 4 byte dopo il precedente, anche da una riga alla successiva.\n");

    printf("\n=== DIMENSIONI ===\n");
    printf("  sizeof(prenotazioni)    = %2zu byte (tutta la matrice)\n", sizeof(prenotazioni));
    printf("  sizeof(prenotazioni[0]) = %2zu byte (una riga)\n", sizeof(prenotazioni[0]));
    printf("  prenotazioni     = %p   (riga 0)\n", (void *) prenotazioni);
    printf("  prenotazioni + 1 = %p   (riga 1: %zu byte dopo)\n",
           (void *) (prenotazioni + 1), sizeof(prenotazioni[0]));

    printf("\n=== TRE MODI DI LEGGERE LA FILA 3, BANCO 3 (indici 2 e 2) ===\n");
    printf("  prenotazioni[2][2]            = %d\n", prenotazioni[2][2]);
    printf("  *(*(prenotazioni + 2) + 2)    = %d\n", *(*(prenotazioni + 2) + 2));
    printf("  *(&prenotazioni[0][0] + 2 * %d + 2) = %d\n", BANCHI,
           *(&prenotazioni[0][0] + 2 * BANCHI + 2));

    return 0;
}
