/*
 * 060-problema-triangolo-distanze.c
 *
 * Pulmino scolastico: la tabella triangolare delle distanze
 *
 * Il pulmino della scuola collega cinque paesi. Le distanze stradali sono
 * simmetriche (da A a B come da B ad A) e da un paese a sé stesso sono 0:
 * basta memorizzare la metà della tabella sotto la diagonale. La riga i
 * contiene le distanze dal paese i ai paesi 0 .. i-1, quindi ha i
 * elementi: righe di LUNGHEZZA DIVERSA.
 *
 * Ogni riga è un array a sé; un array di puntatori le raccoglie:
 *
 *     int r1[1], r2[2], r3[3], r4[4];
 *     const int *righe[PAESI] = {NULL, r1, r2, r3, r4};
 *     righe[3][1]     distanza tra il paese 3 e il paese 1
 *
 * distanza(righe, a, b) scambia a e b se serve, perché la tabella contiene
 * solo le coppie con il primo indice maggiore del secondo.
 *
 * Il programma calcola la lunghezza di alcuni giri del pulmino.
 */

#include <stdio.h>

#define PAESI 5
#define TAPPE 5

int distanza(const int *righe[], int a, int b);
int lunghezza_giro(const int *righe[], const int *giro, int tappe);

int main(void)
{
    const char *paesi[PAESI] = {"Scuola", "Borgo", "Collina", "Ponte", "Lago"};
    int r1[1] = {7};
    int r2[2] = {12, 6};
    int r3[3] = {9, 15, 18};
    int r4[4] = {14, 10, 8, 21};
    const int *righe[PAESI] = {NULL, r1, r2, r3, r4};
    int giro_mattina[TAPPE] = {0, 3, 1, 2, 4};
    int giro_alternativo[TAPPE] = {0, 1, 2, 4, 3};
    int i;
    int j;

    printf("Tabella delle distanze (km):\n%10s", "");
    for (j = 0; j < PAESI; j++) {
        printf("%9s", paesi[j]);
    }
    printf("\n");
    for (i = 0; i < PAESI; i++) {
        printf("%-10s", paesi[i]);
        for (j = 0; j < PAESI; j++) {
            printf("%9d", distanza(righe, i, j));
        }
        printf("\n");
    }

    printf("\nGiro del mattino:   ");
    for (i = 0; i < TAPPE; i++) {
        printf("%s%s", paesi[giro_mattina[i]], i < TAPPE - 1 ? " -> " : "");
    }
    printf("  = %d km\n", lunghezza_giro(righe, giro_mattina, TAPPE));

    printf("Giro alternativo:   ");
    for (i = 0; i < TAPPE; i++) {
        printf("%s%s", paesi[giro_alternativo[i]], i < TAPPE - 1 ? " -> " : "");
    }
    printf("  = %d km\n", lunghezza_giro(righe, giro_alternativo, TAPPE));

    return 0;
}

/* Distanza tra i paesi a e b: si legge sempre righe[maggiore][minore]. */
int distanza(const int *righe[], int a, int b)
{
    int d = 0;

    if (a > b) {
        d = righe[a][b];
    } else if (b > a) {
        d = righe[b][a];
    }
    return d;
}

/* Somma delle distanze tra tappe consecutive. */
int lunghezza_giro(const int *righe[], const int *giro, int tappe)
{
    int t;
    int km = 0;

    for (t = 0; t < tappe - 1; t++) {
        km = km + distanza(righe, giro[t], giro[t + 1]);
    }
    return km;
}
