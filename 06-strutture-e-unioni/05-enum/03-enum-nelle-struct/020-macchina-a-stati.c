/*
 * 020-macchina-a-stati.c
 *
 * Macchina a stati: la porta automatica dell'ingresso
 *
 * Una macchina a stati è in un solo stato alla volta; ogni evento la fa
 * passare in un nuovo stato (o la lascia dov'è). Stati ed eventi sono
 * due enum:
 *
 *     typedef enum { CHIUSA, IN_APERTURA, APERTA, IN_CHIUSURA,
 *                    NUM_STATI } Stato;
 *     typedef enum { PERSONA, FINE_CORSA, TEMPO_SCADUTO,
 *                    NUM_EVENTI } Evento;
 *
 * Le regole stanno in una tabella: la riga è lo stato attuale, la
 * colonna l'evento, la cella il nuovo stato.
 *
 *     Stato transizioni[NUM_STATI][NUM_EVENTI];
 *     stato = transizioni[stato][evento];
 *
 * Tutta la logica è nei dati: per cambiare il comportamento si cambia una
 * cella, non il codice. Il ciclo che fa funzionare la porta è una sola
 * riga.
 *
 * Regole della porta:
 *   - CHIUSA: una persona la fa aprire (IN_APERTURA);
 *   - IN_APERTURA: a fine corsa è APERTA;
 *   - APERTA: dopo il tempo di attesa si chiude (IN_CHIUSURA); se passa
 *     una persona resta aperta;
 *   - IN_CHIUSURA: a fine corsa è CHIUSA; se arriva una persona si
 *     riapre (IN_APERTURA), per sicurezza.
 * Gli eventi che non hanno senso in uno stato lo lasciano invariato.
 */

#include <stdio.h>

#define EVENTI 9

typedef enum {
    CHIUSA, IN_APERTURA, APERTA, IN_CHIUSURA, NUM_STATI
} Stato;

typedef enum {
    PERSONA, FINE_CORSA, TEMPO_SCADUTO, NUM_EVENTI
} Evento;

int main(void)
{
    Stato transizioni[NUM_STATI][NUM_EVENTI] = {
        /*                PERSONA      FINE_CORSA  TEMPO_SCADUTO */
        [CHIUSA] =      {IN_APERTURA, CHIUSA,     CHIUSA},
        [IN_APERTURA] = {IN_APERTURA, APERTA,     IN_APERTURA},
        [APERTA] =      {APERTA,      APERTA,     IN_CHIUSURA},
        [IN_CHIUSURA] = {IN_APERTURA, CHIUSA,     IN_CHIUSURA}
    };
    const char *nomi_stati[NUM_STATI] = {[CHIUSA] = "CHIUSA", [IN_APERTURA] = "IN_APERTURA",
                                         [APERTA] = "APERTA", [IN_CHIUSURA] = "IN_CHIUSURA"};
    const char *nomi_eventi[NUM_EVENTI] = {[PERSONA] = "persona", [FINE_CORSA] = "fine corsa",
                                           [TEMPO_SCADUTO] = "tempo scaduto"};
    Evento sequenza[EVENTI] = {TEMPO_SCADUTO, PERSONA,       FINE_CORSA,
                               PERSONA,       TEMPO_SCADUTO, PERSONA,
                               FINE_CORSA,    TEMPO_SCADUTO, FINE_CORSA};
    Stato stato = CHIUSA;
    Stato nuovo;
    int i;

    printf("Stato iniziale: %s\n", nomi_stati[stato]);
    for (i = 0; i < EVENTI; i++) {
        nuovo = transizioni[stato][sequenza[i]];
        printf("  %-14s %-12s -> %s%s\n", nomi_eventi[sequenza[i]], nomi_stati[stato],
               nomi_stati[nuovo], nuovo == stato ? "  (nessun cambiamento)" : "");
        stato = nuovo;
    }

    return 0;
}
