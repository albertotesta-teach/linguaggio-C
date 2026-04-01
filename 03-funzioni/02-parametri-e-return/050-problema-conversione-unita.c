/*
 * 050-problema-conversione-unita.c
 *
 * Convertitore di unità di misura
 *
 * Un programma di utilità propone all'utente un menu di conversioni
 * tra unità di misura comuni: lunghezza, massa e temperatura.
 * Ogni conversione è implementata in una funzione che riceve il valore
 * originale e restituisce il valore convertito. Il main gestisce
 * l'interazione con l'utente e le chiamate alle funzioni appropriate.
 */

#include <stdio.h>

/* Fattori di conversione come costanti */
#define KM_PER_MIGLIO     1.60934
#define CM_PER_POLLICE    2.54
#define KG_PER_LIBBRA     0.453592
#define G_PER_ONCIA       28.3495

/* Prototipi - conversioni di lunghezza */
double km_in_miglia(double km);
double miglia_in_km(double miglia);
double cm_in_pollici(double cm);
double pollici_in_cm(double pollici);

/* Prototipi - conversioni di massa */
double kg_in_libbre(double kg);
double libbre_in_kg(double libbre);
double g_in_once(double g);

/* Prototipi - conversioni di temperatura */
double celsius_in_fahrenheit(double c);
double fahrenheit_in_celsius(double f);
double celsius_in_kelvin(double c);

/* Prototipo - interfaccia */
void stampa_menu(void);

/* --- Conversioni di lunghezza --- */

double km_in_miglia(double km)
{
    double risultato;
    risultato = km / KM_PER_MIGLIO;
    return risultato;
}

double miglia_in_km(double miglia)
{
    double risultato;
    risultato = miglia * KM_PER_MIGLIO;
    return risultato;
}

double cm_in_pollici(double cm)
{
    double risultato;
    risultato = cm / CM_PER_POLLICE;
    return risultato;
}

double pollici_in_cm(double pollici)
{
    double risultato;
    risultato = pollici * CM_PER_POLLICE;
    return risultato;
}

/* --- Conversioni di massa --- */

double kg_in_libbre(double kg)
{
    double risultato;
    risultato = kg / KG_PER_LIBBRA;
    return risultato;
}

double libbre_in_kg(double libbre)
{
    double risultato;
    risultato = libbre * KG_PER_LIBBRA;
    return risultato;
}

double g_in_once(double g)
{
    double risultato;
    risultato = g / G_PER_ONCIA;
    return risultato;
}

/* --- Conversioni di temperatura --- */

double celsius_in_fahrenheit(double c)
{
    double risultato;
    risultato = c * 9.0 / 5.0 + 32.0;
    return risultato;
}

double fahrenheit_in_celsius(double f)
{
    double risultato;
    risultato = (f - 32.0) * 5.0 / 9.0;
    return risultato;
}

double celsius_in_kelvin(double c)
{
    double risultato;
    risultato = c + 273.15;
    return risultato;
}

/* --- Interfaccia --- */

void stampa_menu(void)
{
    printf("\n=== Convertitore di unita' ===\n");
    printf("  1. Chilometri → Miglia\n");
    printf("  2. Miglia → Chilometri\n");
    printf("  3. Centimetri → Pollici\n");
    printf("  4. Pollici → Centimetri\n");
    printf("  5. Chilogrammi → Libbre\n");
    printf("  6. Libbre → Chilogrammi\n");
    printf("  7. Grammi → Once\n");
    printf("  8. Celsius → Fahrenheit\n");
    printf("  9. Fahrenheit → Celsius\n");
    printf(" 10. Celsius → Kelvin\n");
    printf("Scelta: ");
}

int main(void)
{
    int scelta;
    double valore, risultato;

    stampa_menu();
    scanf("%d", &scelta);

    printf("Valore da convertire: ");
    scanf("%lf", &valore);

    if (scelta == 1) {
        risultato = km_in_miglia(valore);
        printf("%.4f km = %.4f miglia\n", valore, risultato);
    } else if (scelta == 2) {
        risultato = miglia_in_km(valore);
        printf("%.4f miglia = %.4f km\n", valore, risultato);
    } else if (scelta == 3) {
        risultato = cm_in_pollici(valore);
        printf("%.4f cm = %.4f pollici\n", valore, risultato);
    } else if (scelta == 4) {
        risultato = pollici_in_cm(valore);
        printf("%.4f pollici = %.4f cm\n", valore, risultato);
    } else if (scelta == 5) {
        risultato = kg_in_libbre(valore);
        printf("%.4f kg = %.4f libbre\n", valore, risultato);
    } else if (scelta == 6) {
        risultato = libbre_in_kg(valore);
        printf("%.4f libbre = %.4f kg\n", valore, risultato);
    } else if (scelta == 7) {
        risultato = g_in_once(valore);
        printf("%.4f g = %.4f once\n", valore, risultato);
    } else if (scelta == 8) {
        risultato = celsius_in_fahrenheit(valore);
        printf("%.2f C = %.2f F\n", valore, risultato);
    } else if (scelta == 9) {
        risultato = fahrenheit_in_celsius(valore);
        printf("%.2f F = %.2f C\n", valore, risultato);
    } else if (scelta == 10) {
        risultato = celsius_in_kelvin(valore);
        printf("%.2f C = %.2f K\n", valore, risultato);
    } else {
        printf("Scelta non valida.\n");
    }

    return 0;
}
