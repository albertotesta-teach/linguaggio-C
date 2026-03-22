/*
 * 060-problema-coda-prenotazioni.c
 *
 * Problema reale: coda di prenotazioni mediche con array a tappo.
 *
 * Scenario: uno studio medico gestisce le prenotazioni del giorno come
 * due array paralleli a tappo: ID paziente e orario di visita (in minuti
 * dall'inizio della giornata, es. 540 = 9:00). Il tappo è -1 in entrambi.
 * Il programma aggiunge prenotazioni in fondo, rimuove la prima (FIFO),
 * e stampa la coda in formato leggibile.
 *
 * Concetti applicati:
 *  - array paralleli a tappo: entrambi gli array condividono la stessa
 *    posizione del tappo, che va mantenuta sincronizzata
 *  - aggiunta in fondo (il tappo avanza)
 *  - rimozione in testa con shift (il tappo si sposta indietro)
 *  - conversione minuti -> formato HH:MM per la stampa
 */

#include <stdio.h>

#define TAPPO -1
#define MAX   12   /* max prenotazioni + tappo */

/* Conta le prenotazioni presenti (indice del tappo) */
int conta(const int id[]) {
    int i = 0;
    while (id[i] != TAPPO) {
        i++;
    }
    return i;
}

/* Aggiunge una prenotazione in fondo.
 * Restituisce 1 se OK, 0 se la coda è piena. */
int aggiungi(int id[], int orari[], int nuovo_id, int nuovo_orario) {
    int pos = conta(id);
    int esito = 0;
    if (pos + 1 < MAX) {
        id[pos]       = nuovo_id;
        orari[pos]    = nuovo_orario;
        id[pos + 1]   = TAPPO;
        orari[pos + 1] = TAPPO;
        esito = 1;
    }
    return esito;
}

/* Rimuove la prima prenotazione (testa della coda) con shift.
 * Restituisce 1 se OK, 0 se la coda è vuota. */
int rimuovi_primo(int id[], int orari[]) {
    int len = conta(id);
    int esito = 0;
    int i;
    if (len > 0) {
        /* Sposta tutti gli elementi di una posizione a sinistra,
         * incluso il tappo (i <= len porta il tappo alla posizione corretta) */
        for (i = 0; i < len; i++) {
            id[i]    = id[i + 1];
            orari[i] = orari[i + 1];
        }
        esito = 1;
    }
    return esito;
}

/* Stampa la coda in formato leggibile con orario HH:MM */
void stampa_coda(const int id[], const int orari[]) {
    int i = 0;
    if (id[0] == TAPPO) {
        printf("  (coda vuota)\n");
    } else {
        printf("  Pos. | ID paz. | Orario\n");
        printf("  -----|---------|-------\n");
        while (id[i] != TAPPO) {
            int ore     = orari[i] / 60;
            int minuti  = orari[i] % 60;
            printf("   %2d  |  %5d  | %02d:%02d\n",
                   i + 1, id[i], ore, minuti);
            i++;
        }
    }
}

int main(void) {

    /* Prenotazioni iniziali: ID paziente e orario in minuti dall'inizio giornata
     * 540 = 9:00,  570 = 9:30,  600 = 10:00, ecc. */
    int id_pazienti[MAX]  = {1042, 2387, 1905, 3201, TAPPO};
    int orari_visita[MAX] = { 540,  570,  600,  630, TAPPO};

    printf("=== CODA PRENOTAZIONI MEDICHE ===\n\n");

    printf("Stato iniziale (%d prenotazioni):\n", conta(id_pazienti));
    stampa_coda(id_pazienti, orari_visita);
    printf("\n");

    /* ---------------------------------------------------------------- */
    /* Aggiunta di una nuova prenotazione */
    printf("Aggiunta paziente 4455 alle 11:00 (660 minuti):\n");
    if (aggiungi(id_pazienti, orari_visita, 4455, 660)) {
        printf("  OK -> %d prenotazioni in coda\n\n", conta(id_pazienti));
    } else {
        printf("  CODA PIENA\n\n");
    }

    /* ---------------------------------------------------------------- */
    /* Rimozione della prima prenotazione (paziente visitato) */
    printf("Paziente %d visitato - rimozione dalla coda:\n", id_pazienti[0]);
    if (rimuovi_primo(id_pazienti, orari_visita)) {
        printf("  OK -> %d prenotazioni rimanenti\n\n", conta(id_pazienti));
    } else {
        printf("  CODA VUOTA\n\n");
    }

    printf("Stato finale:\n");
    stampa_coda(id_pazienti, orari_visita);

    return 0;
}
