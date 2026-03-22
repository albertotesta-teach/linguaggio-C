/*
 * 040-problema-normalizzazione-misure.c
 *
 * Problema reale: normalizzazione di misurazioni di tensione elettrica.
 *
 * Scenario: un laboratorio ha acquisito 8 misurazioni di tensione (in Volt).
 * Per confrontarle con un modello teorico è necessario normalizzarle
 * nell'intervallo [0.0, 1.0] dividendo ogni valore per il massimo.
 * Il programma calcola anche la media e lo scarto di ogni valore
 * rispetto al valore atteso fornito dal tecnico.
 *
 * Struttura dati chiave:
 *  - un array di misure originali (double)
 *  - un array di misure normalizzate costruito da una funzione dedicata
 *  - tutto il lavoro di elaborazione avviene dentro funzioni specifiche
 *
 * Concetti applicati:
 *  - funzioni che restituiscono un valore calcolato su array (max, media)
 *  - funzione che costruisce un array di output da un array di input
 *  - separazione tra logica di calcolo e presentazione dei risultati
 */

#include <stdio.h>

#define MISURE 8

/* Restituisce il valore massimo nell'array */
double massimo(const double arr[], int n) {
    int i;
    double max = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/* Restituisce la media dell'array */
double media(const double arr[], int n) {
    int i;
    double somma = 0.0;
    for (i = 0; i < n; i++) {
        somma = somma + arr[i];
    }
    return somma / n;
}

/* Normalizza src in [0,1] e scrive il risultato in dst.
 * Ogni elemento di dst = src[i] / massimo(src).
 * Se il massimo è zero, la normalizzazione non è possibile. */
void normalizza(const double src[], double dst[], int n) {
    int i;
    double max = massimo(src, n);

    if (max == 0.0) {
        /* Caso degenere: tutte le misure sono zero */
        for (i = 0; i < n; i++) {
            dst[i] = 0.0;
        }
    } else {
        for (i = 0; i < n; i++) {
            dst[i] = src[i] / max;
        }
    }
}

/* Calcola lo scarto assoluto di ogni elemento rispetto a un valore atteso
 * e scrive i risultati in scarti[]. */
void calcola_scarti(const double misure[], double scarti[],
                    int n, double valore_atteso) {
    int i;
    double diff;
    for (i = 0; i < n; i++) {
        diff = misure[i] - valore_atteso;
        scarti[i] = (diff >= 0.0) ? diff : -diff;
    }
}

/* Stampa una tabella di due array affiancati */
void stampa_tabella(const double originali[], const double normalizzate[],
                    const double scarti[], int n, double valore_atteso) {
    int i;
    printf("  Mis. | Originale | Normaliz. | Scarto da %.1fV\n", valore_atteso);
    printf("  -----|-----------|-----------|----------------\n");
    for (i = 0; i < n; i++) {
        printf("   %2d  |  %6.3f V |  %6.4f   |  %6.3f V\n",
               i + 1, originali[i], normalizzate[i], scarti[i]);
    }
}

int main(void) {

    double misure[MISURE] = {3.21, 4.85, 2.97, 5.12, 4.43, 3.76, 5.00, 4.18};
    double normalizzate[MISURE];
    double scarti[MISURE];
    double valore_atteso = 4.50;   /* tensione nominale attesa dal tecnico */

    printf("=== ANALISI MISURAZIONI TENSIONE ===\n\n");

    /* Elaborazione: tutte le funzioni ricevono e restituiscono dati */
    normalizza(misure, normalizzate, MISURE);
    calcola_scarti(misure, scarti, MISURE, valore_atteso);

    /* Presentazione: il main si occupa solo di mostrare i risultati */
    stampa_tabella(misure, normalizzate, scarti, MISURE, valore_atteso);
    printf("\n");

    printf("Tensione massima   : %.3f V\n", massimo(misure, MISURE));
    printf("Tensione media     : %.3f V\n", media(misure, MISURE));
    printf("Valore atteso      : %.3f V\n", valore_atteso);

    /* Scarto medio: indica quanto le misure si discostano in media dal nominale */
    printf("Scarto medio       : %.3f V\n", media(scarti, MISURE));

    /* Conta le misure che superano lo scarto massimo accettabile */
    double soglia_scarto = 0.5;
    int i;
    int fuori_tolleranza = 0;

    for (i = 0; i < MISURE; i++) {
        if (scarti[i] > soglia_scarto) {
            fuori_tolleranza++;
        }
    }

    printf("\nMisure fuori tolleranza (scarto > %.1f V): %d su %d\n",
           soglia_scarto, fuori_tolleranza, MISURE);

    return 0;
}
