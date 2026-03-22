/*
 * 070-problema-sensori-attivi.c
 *
 * Problema reale: registro dei sensori attivi con array a tappo.
 *
 * Scenario: un sistema di monitoraggio può avere fino a 20 sensori.
 * Solo quelli attivi vengono registrati in due array paralleli a tappo:
 * ID sensore e ultima lettura in gradi Celsius. Il tappo è -1.
 * Il programma conta i sensori attivi, aggiunge e rimuove sensori,
 * e calcola la media delle letture correnti.
 *
 * Concetti applicati:
 *  - array a tappo come registro dinamico di elementi attivi
 *  - ricerca per ID prima di aggiungere (no duplicati)
 *  - rimozione per ID con shift (non per indice)
 *  - media calcolata scorrendo fino al tappo
 */

#include <stdio.h>

#define TAPPO -1
#define MAX   22   /* max 20 sensori + tappo + margine */

/* Conta i sensori attivi */
int conta_sensori(const int id[]) {
    int i = 0;
    while (id[i] != TAPPO) {
        i++;
    }
    return i;
}

/* Cerca un sensore per ID; restituisce l'indice o -1 se non trovato */
int cerca_sensore(const int id[], int id_cercato) {
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

/* Aggiunge un sensore in fondo. Rifiuta se già presente o se pieno.
 * Restituisce: 1=OK, 0=pieno, -1=duplicato */
int aggiungi_sensore(int id[], double letture[], int nuovo_id, double lettura) {
    int risultato;
    if (cerca_sensore(id, nuovo_id) != -1) {
        risultato = -1;   /* già presente */
    } else {
        int pos = conta_sensori(id);
        if (pos + 1 >= MAX) {
            risultato = 0;   /* pieno */
        } else {
            id[pos]        = nuovo_id;
            letture[pos]   = lettura;
            id[pos + 1]    = TAPPO;
            letture[pos + 1] = (double)TAPPO;
            risultato = 1;
        }
    }
    return risultato;
}

/* Rimuove un sensore per ID con shift.
 * Restituisce 1 se trovato e rimosso, 0 se non trovato. */
int rimuovi_sensore(int id[], double letture[], int id_da_rimuovere) {
    int idx = cerca_sensore(id, id_da_rimuovere);
    int esito = 0;
    int len;
    int i;
    if (idx != -1) {
        len = conta_sensori(id);
        for (i = idx; i < len; i++) {
            id[i]      = id[i + 1];
            letture[i] = letture[i + 1];
        }
        esito = 1;
    }
    return esito;
}

/* Calcola la media delle letture correnti */
double media_letture(const double letture[], const int id[]) {
    int i = 0;
    double somma = 0.0;
    int n = 0;
    while (id[i] != TAPPO) {
        somma = somma + letture[i];
        n++;
        i++;
    }
    return (n > 0) ? somma / n : 0.0;
}

/* Stampa il registro sensori */
void stampa_sensori(const int id[], const double letture[]) {
    int i = 0;
    if (id[0] == TAPPO) {
        printf("  (nessun sensore attivo)\n");
    } else {
        printf("  ID    | Lettura\n");
        printf("  ------|--------\n");
        while (id[i] != TAPPO) {
            printf("  S%03d  | %5.1f °C\n", id[i], letture[i]);
            i++;
        }
    }
}

int main(void) {

    int    id[MAX]      = {101, 102, 103, 105, TAPPO};
    double letture[MAX] = {23.5, 31.2, 19.8, 28.4, (double)TAPPO};

    printf("=== REGISTRO SENSORI ATTIVI ===\n\n");

    printf("Stato iniziale (%d sensori):\n", conta_sensori(id));
    stampa_sensori(id, letture);
    printf("Media letture: %.1f °C\n\n", media_letture(letture, id));

    /* ---------------------------------------------------------------- */
    /* Aggiunta di un nuovo sensore */
    printf("Aggiunta sensore S104 (lettura 25.0 °C):\n");
    int esito = aggiungi_sensore(id, letture, 104, 25.0);
    if (esito == 1) {
        printf("  OK -> %d sensori attivi\n\n", conta_sensori(id));
    } else if (esito == -1) {
        printf("  RIFIUTATO: sensore gia' presente\n\n");
    } else {
        printf("  RIFIUTATO: registro pieno\n\n");
    }

    /* ---------------------------------------------------------------- */
    /* Tentativo di aggiunta duplicata */
    printf("Aggiunta sensore S102 (gia' presente):\n");
    esito = aggiungi_sensore(id, letture, 102, 30.0);
    if (esito == 1) {
        printf("  OK\n\n");
    } else if (esito == -1) {
        printf("  RIFIUTATO: sensore gia' presente\n\n");
    } else {
        printf("  RIFIUTATO: registro pieno\n\n");
    }

    /* ---------------------------------------------------------------- */
    /* Rimozione di un sensore */
    printf("Rimozione sensore S103:\n");
    if (rimuovi_sensore(id, letture, 103)) {
        printf("  OK -> %d sensori attivi\n\n", conta_sensori(id));
    } else {
        printf("  NON TROVATO\n\n");
    }

    printf("Stato finale:\n");
    stampa_sensori(id, letture);
    printf("Media letture: %.1f °C\n", media_letture(letture, id));

    return 0;
}
