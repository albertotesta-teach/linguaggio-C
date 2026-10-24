/*
 * 080-problema-calcolatrice-unita.c
 *
 * Laboratorio di scienze: conversioni tra unità di misura
 *
 * Una grandezza ha una dimensione (lunghezza, massa o temperatura) e
 * un'unità che dipende dalla dimensione: ogni dimensione ha il suo enum
 * di unità, e una union contiene quello giusto.
 *
 *     typedef enum { MM, CM, M, KM, INCH, MIGLIO } UnitaLunghezza;
 *     typedef enum { G, KG, LB } UnitaMassa;
 *     typedef enum { CELSIUS, FAHRENHEIT, KELVIN } UnitaTemperatura;
 *
 *     typedef struct {
 *         Dimensione dimensione;
 *         union {
 *             UnitaLunghezza lunghezza;
 *             UnitaMassa massa;
 *             UnitaTemperatura temperatura;
 *         };
 *     } Unita;
 *
 * Una tabella associa a ogni sigla (km, lb, F...) la sua Unita e un
 * fattore verso l'unità base (metri, chilogrammi). Le temperature non si
 * convertono con un fattore: passano per i gradi Celsius con le formule.
 *
 * Il programma legge "valore sigla in sigla" (per esempio 12 km in m) e
 * converte solo se le due unità hanno la stessa dimensione. FINE termina.
 */

#include <stdio.h>
#include <string.h>

#define SIGLE 12

typedef enum {
    LUNGHEZZA, MASSA, TEMPERATURA
} Dimensione;

typedef enum {
    MM, CM, M, KM, INCH, MIGLIO
} UnitaLunghezza;

typedef enum {
    G, KG, LB
} UnitaMassa;

typedef enum {
    CELSIUS, FAHRENHEIT, KELVIN
} UnitaTemperatura;

typedef struct {
    Dimensione dimensione;
    union {
        UnitaLunghezza lunghezza;
        UnitaMassa massa;
        UnitaTemperatura temperatura;
    };
} Unita;

typedef struct {
    const char *sigla;
    Unita unita;
    double fattore;
} Voce;

int cerca(const Voce tabella[], const char *sigla);
double in_celsius(double valore, UnitaTemperatura u);
double da_celsius(double valore, UnitaTemperatura u);
void svuota_riga(void);

int main(void)
{
    Voce tabella[SIGLE] = {
        {"mm", {LUNGHEZZA, .lunghezza = MM}, 0.001},
        {"cm", {LUNGHEZZA, .lunghezza = CM}, 0.01},
        {"m", {LUNGHEZZA, .lunghezza = M}, 1},
        {"km", {LUNGHEZZA, .lunghezza = KM}, 1000},
        {"in", {LUNGHEZZA, .lunghezza = INCH}, 0.0254},
        {"mi", {LUNGHEZZA, .lunghezza = MIGLIO}, 1609.344},
        {"g", {MASSA, .massa = G}, 0.001},
        {"kg", {MASSA, .massa = KG}, 1},
        {"lb", {MASSA, .massa = LB}, 0.45359237},
        {"C", {TEMPERATURA, .temperatura = CELSIUS}, 0},
        {"F", {TEMPERATURA, .temperatura = FAHRENHEIT}, 0},
        {"K", {TEMPERATURA, .temperatura = KELVIN}, 0}
    };
    const char *dimensioni[3] = {"lunghezza", "massa", "temperatura"};
    char da[8];
    char a[8];
    char parola[8];
    double valore;
    double risultato = 0;
    int i;
    int j;
    int finito = 0;

    while (!finito) {
        printf("Conversione (valore sigla in sigla, FINE): ");
        if (scanf("%7s", parola) != 1 || strcmp(parola, "FINE") == 0) {
            finito = 1;
        } else if (sscanf(parola, "%lf", &valore) != 1 || scanf("%7s in %7s", da, a) != 2) {
            printf("  Richiesta non valida.\n");
        } else {
            i = cerca(tabella, da);
            j = cerca(tabella, a);
            if (i == -1 || j == -1) {
                printf("  Unita' sconosciuta: %s\n", i == -1 ? da : a);
            } else if (tabella[i].unita.dimensione != tabella[j].unita.dimensione) {
                printf("  Non si converte una %s in una %s.\n",
                       dimensioni[tabella[i].unita.dimensione],
                       dimensioni[tabella[j].unita.dimensione]);
            } else {
                switch (tabella[i].unita.dimensione) {
                case LUNGHEZZA:
                case MASSA:
                    risultato = valore * tabella[i].fattore / tabella[j].fattore;
                    break;
                case TEMPERATURA:
                    risultato = da_celsius(in_celsius(valore, tabella[i].unita.temperatura),
                                           tabella[j].unita.temperatura);
                    break;
                }
                printf("  %g %s = %.6g %s\n", valore, da, risultato, a);
            }
        }
        if (!finito) {
            svuota_riga();              /* una conversione per riga */
        }
    }

    return 0;
}

int cerca(const Voce tabella[], const char *sigla)
{
    int trovata = -1;
    int i = 0;

    while (i < SIGLE && trovata == -1) {
        if (strcmp(tabella[i].sigla, sigla) == 0) {
            trovata = i;
        }
        i++;
    }
    return trovata;
}

double in_celsius(double valore, UnitaTemperatura u)
{
    double c = valore;

    switch (u) {
    case CELSIUS:
        break;
    case FAHRENHEIT:
        c = (valore - 32) * 5 / 9;
        break;
    case KELVIN:
        c = valore - 273.15;
        break;
    }
    return c;
}

double da_celsius(double valore, UnitaTemperatura u)
{
    double risultato = valore;

    switch (u) {
    case CELSIUS:
        break;
    case FAHRENHEIT:
        risultato = valore * 9 / 5 + 32;
        break;
    case KELVIN:
        risultato = valore + 273.15;
        break;
    }
    return risultato;
}

/* Scarta i caratteri rimasti sulla riga. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
