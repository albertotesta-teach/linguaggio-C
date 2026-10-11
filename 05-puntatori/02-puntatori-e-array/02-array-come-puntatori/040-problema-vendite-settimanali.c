/*
 * 040-problema-vendite-settimanali.c
 *
 * Incassi di un bar: giorni feriali e fine settimana
 *
 * Il gestore di un bar registra l'incasso di ogni giorno della settimana,
 * da lunedì a domenica. Vuole confrontare i giorni feriali con il fine
 * settimana: totale, media e giorno migliore di ciascun gruppo.
 *
 * Le funzioni lavorano su un intervallo qualsiasi (indirizzo di partenza e
 * numero di elementi), quindi servono per entrambi i gruppi senza
 * modifiche:
 *     totale(incassi, 5)       lunedì-venerdì
 *     totale(incassi + 5, 2)   sabato e domenica
 *
 * posizione_massimo restituisce la posizione DENTRO l'intervallo: il
 * chiamante aggiunge lo scostamento (0 o 5) per ottenere il giorno.
 */

#include <stdio.h>

#define GIORNI  7
#define FERIALI 5
#define LUNG    10

int totale(const int *v, int n);
int posizione_massimo(const int *v, int n);
void riepilogo(const char titolo[], const int *v, int n, int primo,
               const char giorni[][LUNG]);

int main(void)
{
    int incassi[GIORNI] = {640, 585, 710, 690, 980, 1420, 1260};
    char giorni[GIORNI][LUNG] = {"lunedi", "martedi", "mercoledi", "giovedi",
                                 "venerdi", "sabato", "domenica"};
    int media_feriali;
    int media_festivi;

    printf("=== INCASSI DELLA SETTIMANA ===\n");
    riepilogo("Feriali", incassi, FERIALI, 0, giorni);
    riepilogo("Fine settimana", incassi + FERIALI, GIORNI - FERIALI, FERIALI, giorni);

    media_feriali = totale(incassi, FERIALI) / FERIALI;
    media_festivi = totale(incassi + FERIALI, GIORNI - FERIALI) / (GIORNI - FERIALI);
    printf("\nUn giorno del fine settimana incassa in media %d euro in piu' (+%d%%).\n",
           media_festivi - media_feriali,
           (media_festivi - media_feriali) * 100 / media_feriali);
    printf("Incasso della settimana: %d euro\n", totale(incassi, GIORNI));

    return 0;
}

/* Somma degli n elementi a partire da v. */
int totale(const int *v, int n)
{
    const int *p;
    int somma = 0;

    for (p = v; p < v + n; p++) {
        somma = somma + *p;
    }
    return somma;
}

/* Posizione (da 0) dell'elemento maggiore tra gli n che partono da v. */
int posizione_massimo(const int *v, int n)
{
    const int *p;
    const int *migliore = v;

    for (p = v + 1; p < v + n; p++) {
        if (*p > *migliore) {
            migliore = p;
        }
    }
    return migliore - v;
}

/* Stampa totale, media e giorno migliore di un gruppo di giorni; primo è
 * l'indice, nella settimana, del primo giorno del gruppo. */
void riepilogo(const char titolo[], const int *v, int n, int primo,
               const char giorni[][LUNG])
{
    int somma = totale(v, n);
    int migliore = posizione_massimo(v, n);

    printf("\n%s (%s-%s)\n", titolo, giorni[primo], giorni[primo + n - 1]);
    printf("  totale %5d euro, media %4d euro\n", somma, somma / n);
    printf("  giorno migliore: %s con %d euro\n", giorni[primo + migliore], v[migliore]);
}
