/*
 * 050-problema-log-eventi.c
 *
 * Problema reale: analisi di un log di eventi di sistema.
 *
 * Scenario: un sistema registra i codici degli eventi in un array a tappo
 * (tappo = 0, poiché i codici validi sono sempre > 0). I codici seguono
 * questa convenzione:
 *   100-199 -> INFO     (operazioni normali)
 *   200-299 -> WARNING  (situazioni anomale non critiche)
 *   300-399 -> ERROR    (errori che richiedono intervento)
 *
 * Concetti applicati:
 *  - tappo = 0 (sentinella per valori positivi)
 *  - scorrimento al contrario dal tappo (ricerca ultimo evento di un tipo)
 *  - conteggio per categoria con classificazione tramite divisione intera
 *  - funzioni su array a tappo senza parametro n
 */

#include <stdio.h>

#define TAPPO    0
#define MAX     25

/* Conta gli eventi registrati (indice del tappo) */
int conta_eventi(const int log[]) {
    int i = 0;
    while (log[i] != TAPPO) {
        i++;
    }
    return i;
}

/* Restituisce la categoria dell'evento: 1=INFO, 2=WARNING, 3=ERROR, 0=sconosciuto */
int categoria(int codice) {
    int cat = codice / 100;   /* 1xx->1, 2xx->2, 3xx->3 */
    int risultato = 0;
    if (cat >= 1 && cat <= 3) {
        risultato = cat;
    }
    return risultato;
}

/* Conta gli eventi di una categoria specifica (1, 2 o 3) */
int conta_per_categoria(const int log[], int cat) {
    int i = 0;
    int contatore = 0;
    while (log[i] != TAPPO) {
        if (categoria(log[i]) == cat) {
            contatore++;
        }
        i++;
    }
    return contatore;
}

/* Cerca l'ULTIMO evento di una categoria: scorre al contrario dal tappo.
 * Restituisce l'indice o -1 se nessun evento di quella categoria è presente. */
int ultimo_per_categoria(const int log[], int cat) {
    int fine = conta_eventi(log) - 1;   /* indice dell'ultimo evento valido */
    int i = fine;
    int trovato = 0;
    int risultato = -1;

    while (i >= 0 && !trovato) {
        if (categoria(log[i]) == cat) {
            trovato = 1;
            risultato = i;
        }
        i--;
    }
    return risultato;
}

/* Stampa il log con etichetta di categoria */
void stampa_log(const int log[]) {
    int i = 0;
    char *etichette[] = {"???", "INFO   ", "WARNING", "ERROR  "};
    printf("  Pos. | Codice | Categoria\n");
    printf("  -----|--------|----------\n");
    while (log[i] != TAPPO) {
        int cat = categoria(log[i]);
        printf("   %2d  |  %3d   | %s\n",
               i + 1, log[i], (cat >= 1 && cat <= 3) ? etichette[cat] : etichette[0]);
        i++;
    }
}

int main(void) {

    /* Log di eventi: codici > 0, terminati da 0 (TAPPO) */
    int log_eventi[MAX] = {
        101, 102, 201, 103, 301, 202, 104,
        302, 105, 203, 303, 106, TAPPO
    };

    printf("=== ANALISI LOG DI SISTEMA ===\n\n");

    stampa_log(log_eventi);
    printf("\n");

    /* ---------------------------------------------------------------- */
    /* Statistiche per categoria */
    int totale  = conta_eventi(log_eventi);
    int n_info  = conta_per_categoria(log_eventi, 1);
    int n_warn  = conta_per_categoria(log_eventi, 2);
    int n_err   = conta_per_categoria(log_eventi, 3);

    printf("Totale eventi : %d\n", totale);
    printf("INFO          : %d  (%.0f%%)\n",
           n_info, (double)n_info / totale * 100.0);
    printf("WARNING       : %d  (%.0f%%)\n",
           n_warn, (double)n_warn / totale * 100.0);
    printf("ERROR         : %d  (%.0f%%)\n\n",
           n_err,  (double)n_err  / totale * 100.0);

    /* ---------------------------------------------------------------- */
    /* Ricerca ultimo evento per categoria */
    int idx;

    idx = ultimo_per_categoria(log_eventi, 3);
    if (idx != -1) {
        printf("Ultimo ERROR  : posizione %d, codice %d\n",
               idx + 1, log_eventi[idx]);
    } else {
        printf("Nessun ERROR nel log.\n");
    }

    idx = ultimo_per_categoria(log_eventi, 2);
    if (idx != -1) {
        printf("Ultimo WARNING: posizione %d, codice %d\n",
               idx + 1, log_eventi[idx]);
    } else {
        printf("Nessun WARNING nel log.\n");
    }

    /* ---------------------------------------------------------------- */
    /* Verifica: gli ERROR sono sotto controllo? */
    printf("\n");
    if (n_err == 0) {
        printf("Sistema OK: nessun errore nel log.\n");
    } else if ((double)n_err / totale < 0.20) {
        printf("Attenzione: %d errori presenti (%.0f%% del totale).\n",
               n_err, (double)n_err / totale * 100.0);
    } else {
        printf("CRITICO: errori superiori al 20%% del log.\n");
    }

    return 0;
}
