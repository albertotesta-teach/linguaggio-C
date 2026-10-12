/*
 * 040-problema-registro-temperature.c
 *
 * Laboratorio di scienze: il registro settimanale delle temperature
 *
 * La classe registra ogni giorno la temperatura minima e massima della
 * serra della scuola. A fine settimana vuole sapere:
 *   - l'escursione termica di ogni giorno (massima - minima);
 *   - la media delle minime e delle massime;
 *   - il giorno con l'escursione più ampia;
 *   - i giorni con rischio di gelo (minima sotto 2 gradi).
 *
 * Tutte le temperature hanno il tipo Gradi, un nome per double:
 *
 *     typedef double Gradi;
 *     Gradi media(const Gradi *v, int n);
 *     Gradi escursione(Gradi minima, Gradi massima);
 *
 * Leggendo i prototipi si capisce subito che le funzioni lavorano su
 * temperature, non su un double qualsiasi.
 */

#include <stdio.h>

#define GIORNI 7
#define SOGLIA_GELO 2.0

typedef double Gradi;

Gradi media(const Gradi *v, int n);
Gradi escursione(Gradi minima, Gradi massima);
int giorno_escursione_massima(const Gradi *minime, const Gradi *massime, int n);

int main(void)
{
    const char *giorni[GIORNI] = {"lunedi", "martedi", "mercoledi", "giovedi",
                                  "venerdi", "sabato", "domenica"};
    Gradi minime[GIORNI] = {3.5, 1.2, -0.8, 2.4, 4.1, 5.0, 1.6};
    Gradi massime[GIORNI] = {12.0, 14.5, 11.2, 9.8, 13.3, 15.7, 16.4};
    int g;
    int gelo = 0;
    int ampia;

    printf("  Giorno      Minima  Massima  Escursione\n");
    for (g = 0; g < GIORNI; g++) {
        printf("  %-10s %6.1f  %7.1f  %10.1f%s\n", giorni[g], minime[g], massime[g],
               escursione(minime[g], massime[g]),
               minime[g] < SOGLIA_GELO ? "   rischio gelo" : "");
        if (minime[g] < SOGLIA_GELO) {
            gelo++;
        }
    }

    ampia = giorno_escursione_massima(minime, massime, GIORNI);
    printf("\nMedia delle minime:  %.2f gradi\n", media(minime, GIORNI));
    printf("Media delle massime: %.2f gradi\n", media(massime, GIORNI));
    printf("Escursione piu' ampia: %s (%.1f gradi)\n", giorni[ampia],
           escursione(minime[ampia], massime[ampia]));
    printf("Giorni con rischio di gelo: %d\n", gelo);

    return 0;
}

Gradi media(const Gradi *v, int n)
{
    Gradi somma = 0;
    int i;

    for (i = 0; i < n; i++) {
        somma = somma + v[i];
    }
    return somma / n;
}

Gradi escursione(Gradi minima, Gradi massima)
{
    return massima - minima;
}

/* Indice del giorno con l'escursione più ampia (il primo, a parità). */
int giorno_escursione_massima(const Gradi *minime, const Gradi *massime, int n)
{
    int migliore = 0;
    int i;

    for (i = 1; i < n; i++) {
        if (escursione(minime[i], massime[i]) > escursione(minime[migliore], massime[migliore])) {
            migliore = i;
        }
    }
    return migliore;
}
