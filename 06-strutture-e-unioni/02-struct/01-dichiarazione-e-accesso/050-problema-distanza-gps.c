/*
 * 050-problema-distanza-gps.c
 *
 * Uscita didattica: la distanza tra due punti GPS
 *
 * Per l'uscita didattica la classe ha segnato sul telefono le coordinate
 * dei luoghi da visitare. Un punto GPS è formato da latitudine e
 * longitudine in gradi decimali: due numeri che hanno senso solo insieme.
 *
 *     typedef struct {
 *         double latitudine;
 *         double longitudine;
 *     } Punto;
 *
 * Il programma legge i punti di partenza e di arrivo e calcola la distanza
 * in linea d'aria con la formula dell'emisenoverso (haversine), che tiene
 * conto della forma sferica della Terra (raggio 6371 km). Stima poi il
 * tempo a piedi, contando il 30% in più per le strade non rettilinee e
 * una velocità di 4.5 km/h.
 *
 * Un punto non valido (latitudine fuori da -90..90 o longitudine fuori da
 * -180..180) viene rifiutato.
 */

#include <stdio.h>
#include <math.h>

#define RAGGIO_TERRA  6371.0
#define PI            3.14159265358979
#define VELOCITA      4.5
#define FATTORE_STRADA 1.3

typedef struct {
    double latitudine;
    double longitudine;
} Punto;

double radianti(double gradi);

int main(void)
{
    Punto partenza;
    Punto arrivo;
    double dlat;
    double dlon;
    double a;
    double km;
    int minuti;

    printf("Partenza (latitudine longitudine): ");
    if (scanf("%lf %lf", &partenza.latitudine, &partenza.longitudine) != 2) {
        partenza.latitudine = 100;
    }
    printf("Arrivo   (latitudine longitudine): ");
    if (scanf("%lf %lf", &arrivo.latitudine, &arrivo.longitudine) != 2) {
        arrivo.latitudine = 100;
    }

    if (partenza.latitudine < -90 || partenza.latitudine > 90 ||
        partenza.longitudine < -180 || partenza.longitudine > 180 ||
        arrivo.latitudine < -90 || arrivo.latitudine > 90 ||
        arrivo.longitudine < -180 || arrivo.longitudine > 180) {
        printf("Coordinate non valide.\n");
    } else {
        dlat = radianti(arrivo.latitudine - partenza.latitudine);
        dlon = radianti(arrivo.longitudine - partenza.longitudine);
        a = sin(dlat / 2) * sin(dlat / 2) +
            cos(radianti(partenza.latitudine)) * cos(radianti(arrivo.latitudine)) *
            sin(dlon / 2) * sin(dlon / 2);
        km = 2 * RAGGIO_TERRA * asin(sqrt(a));
        minuti = (int) (km * FATTORE_STRADA / VELOCITA * 60 + 0.5);

        printf("\nDa (%.4f, %.4f) a (%.4f, %.4f)\n", partenza.latitudine, partenza.longitudine,
               arrivo.latitudine, arrivo.longitudine);
        printf("Distanza in linea d'aria: %.2f km\n", km);
        printf("Tempo a piedi stimato:    %d h %02d min\n", minuti / 60, minuti % 60);
    }

    return 0;
}

double radianti(double gradi)
{
    return gradi * PI / 180;
}
