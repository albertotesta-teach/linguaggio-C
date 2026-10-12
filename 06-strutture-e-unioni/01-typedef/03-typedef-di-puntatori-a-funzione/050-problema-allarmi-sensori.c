/*
 * 050-problema-allarmi-sensori.c
 *
 * Laboratorio di chimica: una regola di allarme diversa per ogni sensore
 *
 * Il laboratorio ha quattro sensori, letti ogni ora durante la mattina:
 *   - temperatura: allarme sotto 16 o sopra 28 gradi;
 *   - umidità:     allarme sopra il 70%;
 *   - CO2:         allarme sopra 1000 ppm (bisogna aprire le finestre);
 *   - rumore:      allarme sopra 80 dB.
 *
 * Ogni regola è una funzione che riceve il valore letto e restituisce 1 se
 * è un allarme. Il tipo ha un nome e le regole stanno in un array
 * parallelo ai sensori:
 *
 *     typedef int (*Regola)(double valore);
 *     Regola regole[SENSORI] = {temperatura_fuori, umidita_alta, ...};
 *
 *     int conta_allarmi(const double *serie, int n, Regola r);
 *
 * Le letture sono una matrice letture[SENSORI][ORE]: la riga s è la serie
 * del sensore s e si passa a conta_allarmi insieme alla sua regola. Il
 * programma stampa, ora per ora, i sensori in allarme e, per ogni
 * sensore, quante volte è scattato l'allarme.
 */

#include <stdio.h>

#define SENSORI 4
#define ORE     6

typedef int (*Regola)(double valore);

int temperatura_fuori(double gradi);
int umidita_alta(double percentuale);
int co2_alta(double ppm);
int rumore_alto(double decibel);
int conta_allarmi(const double *serie, int n, Regola r);

int main(void)
{
    const char *nomi[SENSORI] = {"temperatura", "umidita'", "CO2", "rumore"};
    Regola regole[SENSORI] = {temperatura_fuori, umidita_alta, co2_alta, rumore_alto};
    double letture[SENSORI][ORE] = {
        {15.2, 18.5, 21.0, 23.4, 26.1, 28.6},
        {58, 61, 64, 72, 75, 69},
        {620, 840, 1080, 1240, 760, 1050},
        {45, 82, 67, 71, 88, 60}
    };
    int s;
    int h;
    int in_allarme;

    printf("=== ORA PER ORA ===\n");
    for (h = 0; h < ORE; h++) {
        printf("  ore %2d:", h + 8);
        in_allarme = 0;
        for (s = 0; s < SENSORI; s++) {
            if (regole[s](letture[s][h])) {
                printf("  %s (%g)", nomi[s], letture[s][h]);
                in_allarme = 1;
            }
        }
        if (!in_allarme) {
            printf("  tutto regolare");
        }
        printf("\n");
    }

    printf("\n=== ALLARMI PER SENSORE ===\n");
    for (s = 0; s < SENSORI; s++) {
        printf("  %-12s %d su %d letture\n", nomi[s], conta_allarmi(letture[s], ORE, regole[s]), ORE);
    }

    return 0;
}

int temperatura_fuori(double gradi)
{
    return gradi < 16 || gradi > 28;
}

int umidita_alta(double percentuale)
{
    return percentuale > 70;
}

int co2_alta(double ppm)
{
    return ppm > 1000;
}

int rumore_alto(double decibel)
{
    return decibel > 80;
}

/* Quante letture della serie fanno scattare la regola r. */
int conta_allarmi(const double *serie, int n, Regola r)
{
    int i;
    int conteggio = 0;

    for (i = 0; i < n; i++) {
        if (r(serie[i])) {
            conteggio++;
        }
    }
    return conteggio;
}
