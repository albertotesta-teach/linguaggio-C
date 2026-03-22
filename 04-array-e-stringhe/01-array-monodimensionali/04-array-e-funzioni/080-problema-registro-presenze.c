/*
 * 080-problema-registro-presenze.c
 *
 * Problema reale: analisi delle presenze mensili dei dipendenti.
 *
 * Scenario: un ufficio HR monitora le presenze di 6 dipendenti su 22
 * giorni lavorativi. Il programma calcola la percentuale di presenza
 * di ogni dipendente, identifica il più e meno presente, conta quanti
 * sono sotto la soglia dell'80% e genera un avviso per ciascuno.
 *
 * Concetti applicati:
 *  - funzione che restituisce un valore calcolato da un singolo elemento
 *  - funzione che opera sull'intero array e restituisce un indice
 *  - funzione che conta elementi che soddisfano una condizione
 *  - funzione di stampa con logica di classificazione interna
 */

#include <stdio.h>

#define DIPENDENTI       6
#define GIORNI_LAVORATIVI 22
#define SOGLIA_PRESENZA  80.0   /* percentuale minima accettabile */

/* Restituisce la percentuale di presenza di un singolo dipendente */
double percentuale_presenza(int giorni_presenti, int giorni_totali) {
    return (double)giorni_presenti / giorni_totali * 100.0;
}

/* Restituisce l'indice del dipendente con più presenze */
int dipendente_piu_presente(const int presenze[], int n) {
    int i;
    int idx = 0;
    for (i = 1; i < n; i++) {
        if (presenze[i] > presenze[idx]) {
            idx = i;
        }
    }
    return idx;
}

/* Restituisce l'indice del dipendente con meno presenze */
int dipendente_meno_presente(const int presenze[], int n) {
    int i;
    int idx = 0;
    for (i = 1; i < n; i++) {
        if (presenze[i] < presenze[idx]) {
            idx = i;
        }
    }
    return idx;
}

/* Conta i dipendenti con percentuale di presenza sotto la soglia */
int conta_sotto_soglia(const int presenze[], int n,
                       int giorni_totali, double soglia) {
    int i;
    int contatore = 0;
    for (i = 0; i < n; i++) {
        if (percentuale_presenza(presenze[i], giorni_totali) < soglia) {
            contatore++;
        }
    }
    return contatore;
}

/* Stampa il prospetto presenze con stato e avviso */
void stampa_prospetto(const char nomi[][20], const int presenze[],
                      int n, int giorni_totali, double soglia) {
    int i;
    printf("  %-16s | Giorni | Perc.  | Stato\n", "Dipendente");
    printf("  -----------------|--------|--------|----------\n");

    for (i = 0; i < n; i++) {
        double perc = percentuale_presenza(presenze[i], giorni_totali);
        char avviso[15];

        if (perc >= soglia) {
            avviso[0]='R'; avviso[1]='E'; avviso[2]='G'; avviso[3]='O';
            avviso[4]='L'; avviso[5]='A'; avviso[6]='R'; avviso[7]='E';
            avviso[8]='\0';
        } else {
            avviso[0]='A'; avviso[1]='T'; avviso[2]='T'; avviso[3]='E';
            avviso[4]='N'; avviso[5]='Z'; avviso[6]='I'; avviso[7]='O';
            avviso[8]='N'; avviso[9]='E'; avviso[10]='\0';
        }

        printf("  %-16s |  %3d   | %5.1f%% | %s\n",
               nomi[i], presenze[i], perc, avviso);
    }
}

int main(void) {

    char nomi[DIPENDENTI][20] = {
        "Rossi Anna",
        "Bianchi Carlo",
        "Verdi Elena",
        "Ferrari Marco",
        "Russo Giulia",
        "Conti Pietro"
    };
    int presenze[DIPENDENTI] = {22, 18, 20, 15, 21, 17};

    int idx;

    printf("=== REGISTRO PRESENZE MENSILE ===\n");
    printf("Giorni lavorativi: %d | Soglia: %.0f%%\n\n",
           GIORNI_LAVORATIVI, SOGLIA_PRESENZA);

    stampa_prospetto(nomi, presenze, DIPENDENTI,
                     GIORNI_LAVORATIVI, SOGLIA_PRESENZA);
    printf("\n");

    idx = dipendente_piu_presente(presenze, DIPENDENTI);
    printf("Piu' presente   : %s (%d gg - %.1f%%)\n",
           nomi[idx], presenze[idx],
           percentuale_presenza(presenze[idx], GIORNI_LAVORATIVI));

    idx = dipendente_meno_presente(presenze, DIPENDENTI);
    printf("Meno presente   : %s (%d gg - %.1f%%)\n",
           nomi[idx], presenze[idx],
           percentuale_presenza(presenze[idx], GIORNI_LAVORATIVI));

    printf("Sotto soglia    : %d dipendenti su %d\n",
           conta_sotto_soglia(presenze, DIPENDENTI,
                              GIORNI_LAVORATIVI, SOGLIA_PRESENZA),
           DIPENDENTI);

    return 0;
}
