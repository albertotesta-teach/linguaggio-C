/*
 * 030-parametri-misti.c
 *
 * Parametri per valore e per riferimento nella stessa funzione
 *
 * Una funzione può ricevere alcuni parametri per valore (dati di input
 * che non devono essere modificati) e altri per riferimento (variabili
 * di output che la funzione deve popolare). Questo schema permette a
 * una funzione di "restituire" più risultati contemporaneamente, cosa
 * impossibile con il solo valore di ritorno.
 *
 * Convenzione usata in questo file:
 *   - parametri IN  (solo lettura):  passati per valore
 *   - parametri OUT (solo scrittura): passati per riferimento (puntatore)
 */

#include <stdio.h>

/* Prototipi */
void dividi(int dividendo, int divisore, int *quoziente, int *resto);
void minimo_e_massimo(int a, int b, int c, int *min, int *max);
void celsius_in_fahrenheit_e_kelvin(double c, double *f, double *k);

/* --- Definizioni --- */

/* Calcola quoziente e resto di una divisione intera.
 * dividendo, divisore: parametri IN (per valore)
 * quoziente, resto:    parametri OUT (per riferimento) */
void dividi(int dividendo, int divisore, int *quoziente, int *resto)
{
    *quoziente = dividendo / divisore;
    *resto     = dividendo % divisore;
}

/* Trova il valore minimo e massimo tra tre interi.
 * a, b, c:   parametri IN
 * min, max:  parametri OUT */
void minimo_e_massimo(int a, int b, int c, int *min, int *max)
{
    /* Inizializziamo min e max con il primo valore */
    *min = a;
    *max = a;

    if (b < *min) { *min = b; }
    if (b > *max) { *max = b; }
    if (c < *min) { *min = c; }
    if (c > *max) { *max = c; }
}

/* Converte Celsius in Fahrenheit E in Kelvin contemporaneamente.
 * c:  parametro IN
 * f, k: parametri OUT */
void celsius_in_fahrenheit_e_kelvin(double c, double *f, double *k)
{
    *f = c * 9.0 / 5.0 + 32.0;
    *k = c + 273.15;
}

int main(void)
{
    int q, r;
    int minimo, massimo;
    double fahrenheit, kelvin;

    /* --- Divisione intera --- */
    printf("=== Divisione intera ===\n\n");

    dividi(17, 5, &q, &r);
    printf("17 / 5 = %d  (resto %d)\n", q, r);

    dividi(100, 7, &q, &r);
    printf("100 / 7 = %d  (resto %d)\n", q, r);

    dividi(36, 6, &q, &r);
    printf("36 / 6 = %d  (resto %d)\n\n", q, r);

    /* --- Minimo e massimo --- */
    printf("=== Minimo e massimo ===\n\n");

    minimo_e_massimo(8, 3, 11, &minimo, &massimo);
    printf("Valori: 8, 3, 11  →  min=%d  max=%d\n", minimo, massimo);

    minimo_e_massimo(-5, 0, -2, &minimo, &massimo);
    printf("Valori: -5, 0, -2  →  min=%d  max=%d\n\n", minimo, massimo);

    /* --- Conversione temperatura doppia --- */
    printf("=== Conversione temperatura ===\n\n");

    celsius_in_fahrenheit_e_kelvin(0.0, &fahrenheit, &kelvin);
    printf("0 C  →  %.2f F  /  %.2f K\n", fahrenheit, kelvin);

    celsius_in_fahrenheit_e_kelvin(100.0, &fahrenheit, &kelvin);
    printf("100 C  →  %.2f F  /  %.2f K\n", fahrenheit, kelvin);

    celsius_in_fahrenheit_e_kelvin(-273.15, &fahrenheit, &kelvin);
    printf("-273.15 C  →  %.2f F  /  %.2f K\n", fahrenheit, kelvin);

    return 0;
}
