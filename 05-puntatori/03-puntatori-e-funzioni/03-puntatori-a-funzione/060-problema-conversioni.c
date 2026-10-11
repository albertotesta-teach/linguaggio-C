/*
 * 060-problema-conversioni.c
 *
 * Stazione meteo didattica: tabelle in più unità di misura
 *
 * La stazione meteo della scuola registra le temperature in gradi Celsius.
 * Per un progetto con una scuola americana e per il laboratorio di fisica
 * servono le stesse misure anche in gradi Fahrenheit e in kelvin.
 *
 * Una sola funzione, converti, produce un array convertito a partire da
 * quello originale; la formula di conversione le viene passata come
 * puntatore a funzione:
 *
 *     void converti(const double *in, double *out, int n,
 *                   double (*formula)(double));
 *
 * Una stessa funzione di stampa mostra la tabella; anche il nome dell'unità
 * arriva come parametro.
 */

#include <stdio.h>

#define ORE 6

void converti(const double *in, double *out, int n, double (*formula)(double));
double in_fahrenheit(double celsius);
double in_kelvin(double celsius);
double identita(double celsius);
void stampa_riga(const char unita[], const double *v, int n);

int main(void)
{
    double celsius[ORE] = {-2.5, 1.0, 6.5, 12.0, 14.5, 9.0};
    double convertite[ORE];

    printf("%-10s  %6s  %6s  %6s  %6s  %6s  %6s\n", "Ore", "08:00", "10:00", "12:00",
           "14:00", "16:00", "18:00");

    converti(celsius, convertite, ORE, identita);
    stampa_riga("Celsius   ", convertite, ORE);

    converti(celsius, convertite, ORE, in_fahrenheit);
    stampa_riga("Fahrenheit", convertite, ORE);

    converti(celsius, convertite, ORE, in_kelvin);
    stampa_riga("Kelvin    ", convertite, ORE);

    return 0;
}

/* out[i] = formula(in[i]) per ogni elemento. */
void converti(const double *in, double *out, int n, double (*formula)(double))
{
    const double *p;
    double *q = out;

    for (p = in; p < in + n; p++) {
        *q = formula(*p);
        q++;
    }
}

double in_fahrenheit(double celsius)
{
    return celsius * 9 / 5 + 32;
}

double in_kelvin(double celsius)
{
    return celsius + 273.15;
}

/* Lascia il valore invariato: permette di usare converti anche per una
 * semplice copia. */
double identita(double celsius)
{
    return celsius;
}

void stampa_riga(const char unita[], const double *v, int n)
{
    int i;

    printf("%s", unita);
    for (i = 0; i < n; i++) {
        printf("  %6.1f", v[i]);
    }
    printf("\n");
}
