/*
 * 080-problema-smistamento-messaggi.c
 *
 * Smistare le richieste arrivate allo sportello online della scuola
 *
 * Le richieste dei genitori arrivano tutte allo stesso indirizzo. Per
 * inoltrarle all'ufficio giusto si usano parole chiave: ogni parola è
 * associata a un ufficio tramite due array paralleli
 *
 *     parole[]         "pagell", "iscrizione", "mensa", ...
 *     ufficio_di[]     indice dell'ufficio a cui la parola appartiene
 *
 * Per ogni messaggio (convertito in minuscolo) si contano le parole chiave
 * di ciascun ufficio presenti nel testo (strstr). Il messaggio va
 * all'ufficio con più corrispondenze; se nessuna parola compare, o se due
 * uffici sono a pari merito, va alla segreteria generale, che lo smista a
 * mano.
 *
 * Alcune parole chiave sono solo la radice ("pagell", "assenz"): così
 * strstr le trova sia al singolare sia al plurale (pagella, pagelle).
 *
 * Alla fine si stampa quanti messaggi ha ricevuto ogni ufficio.
 */

#include <stdio.h>
#include <string.h>

#define UFFICI    4
#define PAROLE    11
#define MESSAGGI  6
#define LUNG_MSG  80
#define LUNG_PAR  14
#define GENERALE  (UFFICI - 1)

void in_minuscolo(char dest[], const char sorg[]);
int scegli_ufficio(const int punteggi[], int n);

int main(void)
{
    char uffici[UFFICI][24] = {"Didattica", "Amministrazione", "Servizi", "Segreteria generale"};
    char parole[PAROLE][LUNG_PAR] = {
        "pagell", "voti", "colloquio", "assenz",
        "pagamento", "bonifico", "rimborso",
        "mensa", "trasporto", "scuolabus", "iscrizione"
    };
    int ufficio_di[PAROLE] = {0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 1};
    char messaggi[MESSAGGI][LUNG_MSG] = {
        "Vorrei prenotare un colloquio per parlare dei voti di mio figlio",
        "Ho fatto il bonifico per la gita ma non vedo il pagamento",
        "Lo SCUOLABUS di via Roma passa in ritardo",
        "Chiedo il rimborso della mensa per i giorni di assenza",
        "Quando escono le pagelle del primo quadrimestre?",
        "Buongiorno, a chi posso chiedere informazioni?"
    };
    int ricevuti[UFFICI] = {0};
    int punteggi[UFFICI];
    char testo[LUNG_MSG];
    int m;
    int p;
    int u;

    for (m = 0; m < MESSAGGI; m++) {
        in_minuscolo(testo, messaggi[m]);
        for (u = 0; u < UFFICI; u++) {
            punteggi[u] = 0;
        }
        for (p = 0; p < PAROLE; p++) {
            if (strstr(testo, parole[p]) != NULL) {
                punteggi[ufficio_di[p]]++;
            }
        }
        u = scegli_ufficio(punteggi, UFFICI - 1);
        ricevuti[u]++;

        printf("\"%s\"\n", messaggi[m]);
        printf("   parole trovate: didattica %d, amministrazione %d, servizi %d -> %s\n\n",
               punteggi[0], punteggi[1], punteggi[2], uffici[u]);
    }

    printf("=== MESSAGGI PER UFFICIO ===\n");
    for (u = 0; u < UFFICI; u++) {
        printf("  %-20s %d\n", uffici[u], ricevuti[u]);
    }

    return 0;
}

void in_minuscolo(char dest[], const char sorg[])
{
    int i = 0;

    while (sorg[i] != '\0') {
        if (sorg[i] >= 'A' && sorg[i] <= 'Z') {
            dest[i] = sorg[i] + ('a' - 'A');
        } else {
            dest[i] = sorg[i];
        }
        i++;
    }
    dest[i] = '\0';
}

/* Restituisce l'ufficio (tra i primi n) con il punteggio più alto.
 * Se il massimo è 0 o è raggiunto da più uffici restituisce GENERALE. */
int scegli_ufficio(const int punteggi[], int n)
{
    int u;
    int migliore = 0;
    int pari = 0;
    int scelta;

    for (u = 1; u < n; u++) {
        if (punteggi[u] > punteggi[migliore]) {
            migliore = u;
        }
    }
    for (u = 0; u < n; u++) {
        if (punteggi[u] == punteggi[migliore]) {
            pari++;
        }
    }
    if (punteggi[migliore] == 0 || pari > 1) {
        scelta = GENERALE;
    } else {
        scelta = migliore;
    }
    return scelta;
}
