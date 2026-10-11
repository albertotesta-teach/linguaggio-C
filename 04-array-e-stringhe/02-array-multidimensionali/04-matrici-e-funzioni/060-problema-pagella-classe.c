/*
 * 060-problema-pagella-classe.c
 *
 * Esiti dello scrutinio finale con funzioni dedicate
 *
 * Il tabellone contiene i voti finali di 6 studenti in 5 materie.
 * Regole dello scrutinio (semplificate):
 *   - nessuna insufficienza (voto < 6)        -> AMMESSO
 *   - 1 o 2 insufficienze                     -> SOSPENSIONE DEL GIUDIZIO
 *   - 3 o più insufficienze                   -> NON AMMESSO
 *
 * Il programma stampa la pagella di ogni studente con media ed esito,
 * poi le statistiche per materia (media e numero di insufficienze) e
 * lo studente con la media più alta.
 *
 * Ogni calcolo è una funzione che lavora su UNA RIGA (uno studente) o su
 * UNA COLONNA (una materia) della matrice:
 *   media_studente(voti, s)                  media della riga s
 *   insufficienze_studente(voti, s)          conteggio nella riga s
 *   media_materia(voti, n, m)                media della colonna m
 *   insufficienze_materia(voti, n, m)        conteggio nella colonna m
 *   stampa_esito(insufficienze)              traduce il numero in esito
 *
 * Array paralleli: studenti[] (righe) e materie[] (colonne).
 */

#include <stdio.h>

#define STUDENTI 6
#define MATERIE  5
#define LUNG     16
#define SUFFICIENZA 6
#define MAX_SOSPENSIONE 2

double media_studente(const int voti[][MATERIE], int s);
int insufficienze_studente(const int voti[][MATERIE], int s);
double media_materia(const int voti[][MATERIE], int n, int m);
int insufficienze_materia(const int voti[][MATERIE], int n, int m);
void stampa_esito(int insufficienze);

int main(void)
{
    int voti[STUDENTI][MATERIE] = {
        {7, 6, 8, 7, 8},
        {5, 4, 6, 6, 7},
        {8, 9, 8, 9, 9},
        {5, 4, 5, 6, 6},
        {6, 6, 7, 5, 7},
        {4, 5, 5, 6, 4}
    };
    char studenti[STUDENTI][LUNG] = {
        "Bianchi Sara", "Colombo Luca", "Esposito Ilaria",
        "Ferri Matteo", "Galli Chiara", "Marini Davide"
    };
    char materie[MATERIE][LUNG] = {
        "Italiano", "Matematica", "Inglese", "Informatica", "Sistemi"
    };
    int s;
    int m;
    int migliore = 0;

    /* ── 1. Pagelle ───────────────────────────────────────────────── */
    printf("=== SCRUTINIO FINALE - CLASSE 4B ===\n\n");
    printf("  %-16s", "Studente");
    for (m = 0; m < MATERIE; m++) {
        printf("%4.3s", materie[m]);        /* prime 3 lettere della materia */
    }
    printf("   Media  Esito\n");

    for (s = 0; s < STUDENTI; s++) {
        printf("  %-16s", studenti[s]);
        for (m = 0; m < MATERIE; m++) {
            printf("%4d", voti[s][m]);
        }
        printf("   %5.2f  ", media_studente(voti, s));
        stampa_esito(insufficienze_studente(voti, s));
        printf("\n");

        if (media_studente(voti, s) > media_studente(voti, migliore)) {
            migliore = s;
        }
    }

    /* ── 2. Statistiche per materia ───────────────────────────────── */
    printf("\n  %-14s  Media  Insufficienze\n", "Materia");
    for (m = 0; m < MATERIE; m++) {
        printf("  %-14s  %5.2f  %13d\n", materie[m],
               media_materia(voti, STUDENTI, m),
               insufficienze_materia(voti, STUDENTI, m));
    }

    printf("\nMedia piu' alta: %s (%.2f)\n",
           studenti[migliore], media_studente(voti, migliore));

    return 0;
}

double media_studente(const int voti[][MATERIE], int s)
{
    int m;
    int somma = 0;

    for (m = 0; m < MATERIE; m++) {
        somma = somma + voti[s][m];
    }
    return (double) somma / MATERIE;
}

int insufficienze_studente(const int voti[][MATERIE], int s)
{
    int m;
    int conteggio = 0;

    for (m = 0; m < MATERIE; m++) {
        if (voti[s][m] < SUFFICIENZA) {
            conteggio++;
        }
    }
    return conteggio;
}

double media_materia(const int voti[][MATERIE], int n, int m)
{
    int s;
    int somma = 0;

    for (s = 0; s < n; s++) {
        somma = somma + voti[s][m];
    }
    return (double) somma / n;
}

int insufficienze_materia(const int voti[][MATERIE], int n, int m)
{
    int s;
    int conteggio = 0;

    for (s = 0; s < n; s++) {
        if (voti[s][m] < SUFFICIENZA) {
            conteggio++;
        }
    }
    return conteggio;
}

void stampa_esito(int insufficienze)
{
    if (insufficienze == 0) {
        printf("AMMESSO");
    } else if (insufficienze <= MAX_SOSPENSIONE) {
        printf("SOSPENSIONE (%d)", insufficienze);
    } else {
        printf("NON AMMESSO");
    }
}

/*
 * NOTA: "%4.3s" stampa al massimo 3 caratteri della stringa, allineati
 * in un campo di 4: è un modo per abbreviare i nomi delle materie senza
 * modificarli.
 */
