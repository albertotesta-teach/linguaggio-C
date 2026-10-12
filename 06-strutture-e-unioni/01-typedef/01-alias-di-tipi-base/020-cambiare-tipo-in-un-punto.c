/*
 * 020-cambiare-tipo-in-un-punto.c
 *
 * Con typedef il tipo di un dato si cambia modificando una sola riga
 *
 * La stazione meteo della scuola registra la pioggia ogni 10 minuti, in
 * millimetri. Il programma usa il tipo Misura per tutte le letture, per i
 * parametri e per i risultati delle funzioni:
 *
 *     typedef float Misura;
 *     Misura totale(const Misura *v, int n);
 *
 * Con float, sommando mille letture (quasi tutte da 0.1 mm) il totale si
 * scosta di qualche millesimo dal valore esatto: float ha circa 7 cifre
 * significative e 0.1 non è rappresentabile esattamente, quindi l'errore
 * di ogni somma si accumula.
 * Per avere più precisione basta cambiare UNA riga:
 *
 *     typedef double Misura;
 *
 * e tutte le variabili, i parametri e le funzioni passano a double, senza
 * cercare uno per uno i float nel programma.
 *
 * Attenzione: typedef non aggiorna i formati di scanf (%f per float, %lf
 * per double). printf invece usa %f per entrambi, quindi questo programma
 * funziona senza altre modifiche.
 */

#include <stdio.h>

#define LETTURE 1000

typedef float Misura;           /* provare a cambiare in: typedef double Misura; */

Misura totale(const Misura *v, int n);
Misura massimo(const Misura *v, int n);

int main(void)
{
    Misura pioggia[LETTURE];
    Misura somma;
    int i;

    /* tutte le letture valgono 0.1 mm tranne un acquazzone di 30 minuti */
    for (i = 0; i < LETTURE; i++) {
        pioggia[i] = 0.1;
    }
    pioggia[500] = 2.4;
    pioggia[501] = 3.1;
    pioggia[502] = 1.8;

    somma = totale(pioggia, LETTURE);
    printf("Tipo Misura: %zu byte (%s)\n", sizeof(Misura),
           sizeof(Misura) == sizeof(float) ? "float" : "double");
    printf("Letture: %d, massima %.1f mm in 10 minuti\n", LETTURE, massimo(pioggia, LETTURE));
    printf("Totale calcolato:  %.6f mm\n", somma);
    printf("Totale esatto:     %.6f mm\n", 997 * 0.1 + 2.4 + 3.1 + 1.8);

    return 0;
}

/* Somma di n letture: il tipo dell'accumulatore segue Misura. */
Misura totale(const Misura *v, int n)
{
    Misura somma = 0;
    int i;

    for (i = 0; i < n; i++) {
        somma = somma + v[i];
    }
    return somma;
}

Misura massimo(const Misura *v, int n)
{
    Misura piu_alta = v[0];
    int i;

    for (i = 1; i < n; i++) {
        if (v[i] > piu_alta) {
            piu_alta = v[i];
        }
    }
    return piu_alta;
}
