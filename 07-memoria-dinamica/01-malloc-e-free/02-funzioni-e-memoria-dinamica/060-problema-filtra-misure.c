/*
 * 060-problema-filtra-misure.c
 *
 * Il sensore di CO2 dell'aula: tenere solo le letture utili
 *
 * Un sensore misura la CO2 in aula (in ppm, parti per milione) ogni 10
 * minuti. Ogni tanto sbaglia e manda valori impossibili (sotto 300 o
 * sopra 5000 ppm). Da 1000 ppm in su bisogna aprire le finestre.
 *
 * La funzione
 *
 *     double *filtra(const double misure[], int n, double minimo,
 *                    double massimo, int *quante);
 *
 * restituisce un array NUOVO con le sole misure comprese tra minimo e
 * massimo, e scrive in *quante quanti elementi contiene. Un array allocato
 * non dice quanto è lungo: la lunghezza va restituita a parte, qui con
 * un parametro di uscita.
 *
 * filtra fa due passate: la prima conta le misure da tenere, poi alloca
 * un blocco della dimensione giusta, la seconda le copia. Se non c'è
 * nessuna misura da tenere non alloca nulla: *quante vale 0 e il
 * risultato è NULL. Se *quante è positivo e il risultato è NULL, la
 * memoria non bastava.
 *
 * Il programma legge n e le letture, le filtra due volte (letture
 * valide, poi letture valide da 1000 in su) e libera i tre blocchi.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_LETTURE 144
#define MINIMO_VALIDO 300.0
#define MASSIMO_VALIDO 5000.0
#define SOGLIA_FINESTRE 1000.0

double *filtra(const double misure[], int n, double minimo, double massimo, int *quante);
void stampa(const char *titolo, const double v[], int n);

int main(void)
{
    double *letture;
    double *valide = NULL;
    double *alte = NULL;
    int n;
    int n_valide = 0;
    int n_alte = 0;
    int letti = 0;

    printf("Numero di letture (da 1 a %d): ", MAX_LETTURE);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_LETTURE) {
        printf("Numero non valido.\n");
    } else {
        letture = malloc(n * sizeof *letture);
        if (letture == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            printf("Letture in ppm: ");
            while (letti < n && scanf("%lf", &letture[letti]) == 1) {
                letti++;
            }
            if (letti < n) {
                printf("Letture mancanti: ne servono %d.\n", n);
            } else {
                stampa("Tutte le letture", letture, n);
                valide = filtra(letture, n, MINIMO_VALIDO, MASSIMO_VALIDO, &n_valide);
                if (n_valide > 0 && valide == NULL) {
                    printf("Memoria insufficiente.\n");
                } else {
                    stampa("Letture valide", valide, n_valide);
                    printf("Scartate per errore del sensore: %d\n", n - n_valide);
                    alte = filtra(valide, n_valide, SOGLIA_FINESTRE, MASSIMO_VALIDO, &n_alte);
                    if (n_alte > 0 && alte == NULL) {
                        printf("Memoria insufficiente.\n");
                    } else {
                        stampa("Almeno 1000 ppm (aprire le finestre)", alte, n_alte);
                    }
                }
            }
            free(alte);
            free(valide);
            free(letture);
        }
    }

    return 0;
}

double *filtra(const double misure[], int n, double minimo, double massimo, int *quante)
{
    double *risultato = NULL;
    int conta = 0;
    int i;
    int j = 0;

    for (i = 0; i < n; i++) {
        if (misure[i] >= minimo && misure[i] <= massimo) {
            conta++;
        }
    }
    if (conta > 0) {
        risultato = malloc(conta * sizeof *risultato);
    }
    if (risultato != NULL) {
        for (i = 0; i < n; i++) {
            if (misure[i] >= minimo && misure[i] <= massimo) {
                risultato[j] = misure[i];
                j++;
            }
        }
    }
    *quante = conta;
    return risultato;
}

void stampa(const char *titolo, const double v[], int n)
{
    double somma = 0;
    int i;

    printf("%s (%d):", titolo, n);
    for (i = 0; i < n; i++) {
        printf(" %.0f", v[i]);
        somma = somma + v[i];
    }
    if (n > 0) {
        printf("  media %.0f", somma / n);
    } else {
        printf(" nessuna");
    }
    printf("\n");
}
