/*
 * 050-problema-minmax.c
 *
 * Analisi di una serie di misurazioni: minimo, massimo e media
 *
 * Un laboratorio raccoglie cinque misurazioni di temperatura durante
 * la giornata. Il programma calcola il valore minimo, il massimo e
 * la media. Le funzioni per il minimo e il massimo usano il passaggio
 * per riferimento per "restituire" entrambi i valori in una sola chiamata,
 * evitando di dover eseguire due scansioni separate.
 *
 * Nota: in questo capitolo i cinque valori sono passati esplicitamente
 * come parametri scalari. Nel capitolo 04 (array) impareremo a gestire
 * sequenze di dati in modo più compatto.
 */

#include <stdio.h>

/* Prototipi */
void calcola_minmax(double v1, double v2, double v3, double v4, double v5,
                    double *min, double *max);
double calcola_media(double v1, double v2, double v3, double v4, double v5);
void stampa_report(double v1, double v2, double v3, double v4, double v5);

/* --- Definizioni --- */

/* Trova il minimo e il massimo tra cinque valori.
 * I risultati vengono scritti nelle variabili puntate da min e max. */
void calcola_minmax(double v1, double v2, double v3, double v4, double v5,
                    double *min, double *max)
{
    *min = v1;
    *max = v1;

    if (v2 < *min) { *min = v2; }
    if (v2 > *max) { *max = v2; }
    if (v3 < *min) { *min = v3; }
    if (v3 > *max) { *max = v3; }
    if (v4 < *min) { *min = v4; }
    if (v4 > *max) { *max = v4; }
    if (v5 < *min) { *min = v5; }
    if (v5 > *max) { *max = v5; }
}

double calcola_media(double v1, double v2, double v3, double v4, double v5)
{
    double media;
    media = (v1 + v2 + v3 + v4 + v5) / 5.0;
    return media;
}

/* Stampa il report completo della giornata */
void stampa_report(double v1, double v2, double v3, double v4, double v5)
{
    double min, max, media, escursione;

    printf("Misurazioni: %.1f  %.1f  %.1f  %.1f  %.1f\n",
           v1, v2, v3, v4, v5);
    printf("-------------------------------------------\n");

    /* calcola_minmax scrive direttamente in min e max */
    calcola_minmax(v1, v2, v3, v4, v5, &min, &max);

    media      = calcola_media(v1, v2, v3, v4, v5);
    escursione = max - min;

    printf("Minimo:      %.1f C\n", min);
    printf("Massimo:     %.1f C\n", max);
    printf("Media:       %.1f C\n", media);
    printf("Escursione:  %.1f C\n", escursione);
}

int main(void)
{
    printf("=== Report temperatura giornaliera ===\n\n");

    printf("Stazione A (citta'):\n");
    stampa_report(18.5, 22.0, 24.3, 21.5, 19.0);

    printf("\nStazione B (montagna):\n");
    stampa_report(4.0, 8.5, 11.0, 9.0, 5.5);

    printf("\nStazione C (costa):\n");
    stampa_report(21.0, 23.5, 25.0, 24.0, 22.0);

    return 0;
}
