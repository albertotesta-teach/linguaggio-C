/*
 * 050-problema-termostato-aule.c
 *
 * Riscaldamento della scuola: il termostato di ogni aula
 *
 * Ogni aula ha un termostato che riceve una misura di temperatura ogni
 * 15 minuti e decide se accendere o spegnere il termosifone. Per non
 * accendere e spegnere di continuo usa un'isteresi di mezzo grado:
 *   - si accende se la temperatura scende sotto obiettivo - 0.5;
 *   - si spegne se sale sopra obiettivo + 0.5;
 *   - tra le due soglie mantiene lo stato precedente.
 *
 *     typedef struct {
 *         char aula[8];
 *         double obiettivo;
 *         double ultima;
 *         double minima;
 *         double massima;
 *         int acceso;
 *         int accensioni;
 *     } Termostato;
 *
 *     void aggiorna(Termostato *t, double misura);   modifica il termostato
 *     void riepilogo(const Termostato *t);            lo legge soltanto
 *
 * Il programma simula due aule con le misure di una mattina; la stessa
 * funzione aggiorna lavora su entrambe, ricevendo di volta in volta
 * l'indirizzo di una o dell'altra.
 */

#include <stdio.h>

#define MISURE 8
#define ISTERESI 0.5

typedef struct {
    char aula[8];
    double obiettivo;
    double ultima;
    double minima;
    double massima;
    int acceso;
    int accensioni;
} Termostato;

void aggiorna(Termostato *t, double misura);
void riepilogo(const Termostato *t);

int main(void)
{
    Termostato a12 = {"A1-12", 20.0, 0, 100, -100, 0, 0};
    Termostato lab = {"Lab-B", 19.0, 0, 100, -100, 0, 0};
    double misure_a12[MISURE] = {17.8, 18.6, 19.4, 20.1, 20.6, 20.2, 19.6, 19.3};
    double misure_lab[MISURE] = {18.9, 18.7, 18.4, 18.8, 19.3, 19.6, 19.1, 18.6};
    int m;

    printf("  Ora    %-14s %-14s\n", a12.aula, lab.aula);
    for (m = 0; m < MISURE; m++) {
        aggiorna(&a12, misure_a12[m]);
        aggiorna(&lab, misure_lab[m]);
        printf("  %02d:%02d  %4.1f %-9s %4.1f %-9s\n", 8 + m / 4, m % 4 * 15, a12.ultima,
               a12.acceso ? "acceso" : "spento", lab.ultima, lab.acceso ? "acceso" : "spento");
    }
    printf("\n");
    riepilogo(&a12);
    riepilogo(&lab);

    return 0;
}

/* Registra la misura e decide lo stato con l'isteresi. */
void aggiorna(Termostato *t, double misura)
{
    t->ultima = misura;
    if (misura < t->minima) {
        t->minima = misura;
    }
    if (misura > t->massima) {
        t->massima = misura;
    }
    if (!t->acceso && misura < t->obiettivo - ISTERESI) {
        t->acceso = 1;
        t->accensioni++;
    } else if (t->acceso && misura > t->obiettivo + ISTERESI) {
        t->acceso = 0;
    }
}

void riepilogo(const Termostato *t)
{
    printf("  %s: obiettivo %.1f, minima %.1f, massima %.1f, accensioni %d\n", t->aula,
           t->obiettivo, t->minima, t->massima, t->accensioni);
}
