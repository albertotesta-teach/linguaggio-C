/*
 * 080-problema-classifica-criterio.c
 *
 * Triathlon scolastico: il vincitore secondo criteri diversi
 *
 * Al triathlon della scuola ogni atleta ottiene un punteggio da 0 a 100 in
 * tre prove: corsa, salto in lungo, lancio del peso. La giuria assegna tre
 * premi con criteri diversi:
 *   - assoluto:     il totale più alto delle tre prove;
 *   - specialista:  la singola prova migliore;
 *   - regolarità:   la prova peggiore più alta (nessun punto debole).
 *
 * I punteggi sono in una matrice punti[ATLETI][PROVE]: la riga punti[i] è
 * un array di PROVE interi e, passata a una funzione, arriva come
 * const int *. Ogni criterio è una funzione che riceve la riga di un
 * atleta e ne calcola il valore:
 *
 *     int (*valuta)(const int *prove)
 *
 * vincitore(punti, ATLETI, valuta) restituisce l'indice dell'atleta con il
 * valore più alto secondo il criterio ricevuto.
 */

#include <stdio.h>

#define ATLETI 5
#define PROVE  3
#define LUNG   12

int vincitore(const int punti[][PROVE], int n, int (*valuta)(const int *));
int totale(const int *prove);
int prova_migliore(const int *prove);
int prova_peggiore(const int *prove);
void premia(const char premio[], const char nomi[][LUNG], const int punti[][PROVE],
            int (*valuta)(const int *));

int main(void)
{
    char nomi[ATLETI][LUNG] = {"Elena", "Davide", "Sara", "Omar", "Giulia"};
    int punti[ATLETI][PROVE] = {
        {72, 65, 80},
        {95, 40, 70},
        {68, 74, 71},
        {60, 88, 79},
        {81, 70, 62}
    };
    int i;

    printf("%-8s %6s %6s %6s %7s\n", "Atleta", "corsa", "salto", "peso", "totale");
    for (i = 0; i < ATLETI; i++) {
        printf("%-8s %6d %6d %6d %7d\n", nomi[i], punti[i][0], punti[i][1], punti[i][2],
               totale(punti[i]));
    }
    printf("\n");

    premia("Assoluto   ", nomi, punti, totale);
    premia("Specialista", nomi, punti, prova_migliore);
    premia("Regolarita'", nomi, punti, prova_peggiore);

    return 0;
}

/* Indice dell'atleta con il valore più alto; a parità il primo. */
int vincitore(const int punti[][PROVE], int n, int (*valuta)(const int *))
{
    int i;
    int migliore = 0;

    for (i = 1; i < n; i++) {
        if (valuta(punti[i]) > valuta(punti[migliore])) {
            migliore = i;
        }
    }
    return migliore;
}

int totale(const int *prove)
{
    return prove[0] + prove[1] + prove[2];
}

int prova_migliore(const int *prove)
{
    const int *p;
    int max = *prove;

    for (p = prove + 1; p < prove + PROVE; p++) {
        if (*p > max) {
            max = *p;
        }
    }
    return max;
}

int prova_peggiore(const int *prove)
{
    const int *p;
    int min = *prove;

    for (p = prove + 1; p < prove + PROVE; p++) {
        if (*p < min) {
            min = *p;
        }
    }
    return min;
}

/* Stampa il vincitore del premio e il suo valore secondo il criterio. */
void premia(const char premio[], const char nomi[][LUNG], const int punti[][PROVE],
            int (*valuta)(const int *))
{
    int v = vincitore(punti, ATLETI, valuta);

    printf("Premio %s: %-7s (valore %d)\n", premio, nomi[v], valuta(punti[v]));
}
