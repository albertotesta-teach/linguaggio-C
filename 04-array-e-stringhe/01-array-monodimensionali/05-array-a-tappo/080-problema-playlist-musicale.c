/*
 * 080-problema-playlist-musicale.c
 *
 * Problema reale: gestione di una playlist musicale con array a tappo.
 *
 * Scenario: una playlist contiene fino a 15 brani, ciascuno con un ID
 * e una durata in secondi, memorizzati in due array paralleli a tappo
 * (tappo = -1). Il programma calcola la durata totale, trova il brano
 * più lungo, inserisce un brano in una posizione specifica (shift in
 * avanti) e rimuove un brano per ID (shift all'indietro).
 *
 * Concetti applicati:
 *  - inserimento in posizione intermedia con shift in avanti
 *  - rimozione per ID con shift all'indietro
 *  - il tappo si sposta di conseguenza in entrambi i casi
 *  - conversione secondi -> MM:SS per la stampa
 */

#include <stdio.h>

#define TAPPO -1
#define MAX   18   /* max 15 brani + tappo + margine */

/* Conta i brani presenti */
int conta_brani(const int id[]) {
    int i = 0;
    while (id[i] != TAPPO) {
        i++;
    }
    return i;
}

/* Restituisce la durata totale in secondi */
int durata_totale(const int durate[], const int id[]) {
    int i = 0;
    int totale = 0;
    while (id[i] != TAPPO) {
        totale = totale + durate[i];
        i++;
    }
    return totale;
}

/* Restituisce l'indice del brano più lungo */
int brano_piu_lungo(const int durate[], const int id[]) {
    int i = 0;
    int idx_max = 0;
    while (id[i] != TAPPO) {
        if (durate[i] > durate[idx_max]) {
            idx_max = i;
        }
        i++;
    }
    return idx_max;
}

/* Cerca un brano per ID; restituisce l'indice o -1 se non trovato */
int cerca_brano(const int id[], int id_cercato) {
    int i = 0;
    int trovato = 0;
    int risultato = -1;
    while (id[i] != TAPPO && !trovato) {
        if (id[i] == id_cercato) {
            trovato = 1;
            risultato = i;
        }
        i++;
    }
    return risultato;
}

/* Inserisce un brano nella posizione pos (0-based), spostando gli altri.
 * Restituisce 1=OK, 0=pieno, -1=posizione non valida. */
int inserisci_in_posizione(int id[], int durate[],
                           int pos, int nuovo_id, int nuova_durata) {
    int len = conta_brani(id);
    int risultato;
    int i;

    if (pos < 0 || pos > len) {
        risultato = -1;   /* posizione fuori range */
    } else if (len + 1 >= MAX) {
        risultato = 0;    /* pieno */
    } else {
        /* Shift in avanti dal fondo fino alla posizione di inserimento.
         * Si parte dal tappo (i = len) e si arriva a i = pos + 1. */
        for (i = len; i >= pos; i--) {
            id[i + 1]     = id[i];
            durate[i + 1] = durate[i];
        }
        /* Scrive il nuovo brano nella posizione liberata */
        id[pos]     = nuovo_id;
        durate[pos] = nuova_durata;
        risultato = 1;
    }
    return risultato;
}

/* Rimuove un brano per ID.
 * Restituisce 1 se trovato e rimosso, 0 se non trovato. */
int rimuovi_per_id(int id[], int durate[], int id_da_rimuovere) {
    int idx = cerca_brano(id, id_da_rimuovere);
    int esito = 0;
    int len;
    int i;
    if (idx != -1) {
        len = conta_brani(id);
        for (i = idx; i < len; i++) {
            id[i]     = id[i + 1];
            durate[i] = durate[i + 1];
        }
        esito = 1;
    }
    return esito;
}

/* Stampa la playlist con durata in MM:SS */
void stampa_playlist(const int id[], const int durate[]) {
    int i = 0;
    int tot;
    printf("  N. | ID    | Durata\n");
    printf("  ---|-------|-------\n");
    while (id[i] != TAPPO) {
        int min = durate[i] / 60;
        int sec = durate[i] % 60;
        printf("  %2d | %5d | %02d:%02d\n", i + 1, id[i], min, sec);
        i++;
    }
    tot = durata_totale(durate, id);
    printf("  Durata totale: %02d:%02d\n", tot / 60, tot % 60);
}

int main(void) {

    /* Playlist iniziale: ID brani e durate in secondi */
    int id[MAX]     = {1001, 1002, 1003, 1004, 1005, TAPPO};
    int durate[MAX] = { 213,  187,  245,  198,  221, TAPPO};

    printf("=== GESTIONE PLAYLIST ===\n\n");

    printf("Playlist iniziale:\n");
    stampa_playlist(id, durate);
    printf("Brano piu' lungo: ID %d (%d secondi)\n\n",
           id[brano_piu_lungo(durate, id)],
           durate[brano_piu_lungo(durate, id)]);

    /* ---------------------------------------------------------------- */
    /* Inserimento in posizione 2 (terzo posto) */
    printf("Inserimento brano 1006 (230 sec) in posizione 2:\n");
    int esito = inserisci_in_posizione(id, durate, 2, 1006, 230);
    if (esito == 1) {
        printf("  OK -> %d brani in playlist\n\n", conta_brani(id));
        stampa_playlist(id, durate);
        printf("\n");
    } else if (esito == -1) {
        printf("  POSIZIONE NON VALIDA\n\n");
    } else {
        printf("  PLAYLIST PIENA\n\n");
    }

    /* ---------------------------------------------------------------- */
    /* Rimozione per ID */
    printf("Rimozione brano 1003:\n");
    if (rimuovi_per_id(id, durate, 1003)) {
        printf("  OK -> %d brani rimanenti\n\n", conta_brani(id));
    } else {
        printf("  BRANO NON TROVATO\n\n");
    }

    printf("Playlist finale:\n");
    stampa_playlist(id, durate);

    return 0;
}
