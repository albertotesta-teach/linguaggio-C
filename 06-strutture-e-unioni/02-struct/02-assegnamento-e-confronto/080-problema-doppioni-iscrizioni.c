/*
 * 080-problema-doppioni-iscrizioni.c
 *
 * Corsi pomeridiani: le iscrizioni inviate due volte
 *
 * Il modulo online per i corsi pomeridiani a volte invia due volte la
 * stessa iscrizione (doppio clic sul pulsante). Le iscrizioni arrivano
 * una per riga, in ordine di arrivo:
 *
 *     typedef struct {
 *         char cognome[20];
 *         char corso[16];
 *         int giorno;              1 = lunedì ... 5 = venerdì
 *     } Iscrizione;
 *
 * Ogni iscrizione si confronta con la PRECEDENTE (salvata con
 * precedente = corrente):
 *   - tutti i campi uguali      -> doppione, scartato;
 *   - stesso cognome e corso,
 *     giorno diverso            -> correzione: sostituisce la precedente;
 *   - altrimenti                -> nuova iscrizione.
 * La riga FINE termina; il programma stampa i conteggi.
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char cognome[20];
    char corso[16];
    int giorno;
} Iscrizione;

void svuota_riga(void);

int main(void)
{
    const char *giorni[6] = {"", "lun", "mar", "mer", "gio", "ven"};
    Iscrizione precedente = {"", "", 0};
    Iscrizione corrente;
    int nuove = 0;
    int doppioni = 0;
    int correzioni = 0;
    int fine = 0;
    int stessa_persona_corso;
    int letti;

    while (!fine) {
        printf("Iscrizione (cognome corso giorno 1-5, FINE): ");
        if (scanf("%19s", corrente.cognome) != 1) {
            fine = 1;                   /* input terminato: come FINE */
        } else if (strcmp(corrente.cognome, "FINE") == 0) {
            fine = 1;
        } else {
            letti = scanf("%15s %d", corrente.corso, &corrente.giorno);
            if (letti != EOF) {
                svuota_riga();          /* un'iscrizione per riga */
            }
            if (letti == EOF) {
                printf("\n  Iscrizione incompleta.\n");
                fine = 1;
            } else if (letti != 2 || corrente.giorno < 1 || corrente.giorno > 5) {
                printf("  Iscrizione non valida.\n");
            } else {
                stessa_persona_corso = strcmp(corrente.cognome, precedente.cognome) == 0 &&
                                       strcmp(corrente.corso, precedente.corso) == 0;
                if (stessa_persona_corso && corrente.giorno == precedente.giorno) {
                    printf("  Doppione scartato.\n");
                    doppioni++;
                } else if (stessa_persona_corso) {
                    printf("  Correzione: %s passa da %s a %s.\n", corrente.cognome,
                           giorni[precedente.giorno], giorni[corrente.giorno]);
                    correzioni++;
                    precedente = corrente;
                } else {
                    printf("  Nuova iscrizione: %s, %s, %s.\n", corrente.cognome,
                           corrente.corso, giorni[corrente.giorno]);
                    nuove++;
                    precedente = corrente;
                }
            }
        }
    }
    printf("Iscrizioni valide: %d, doppioni scartati: %d, correzioni: %d\n", nuove, doppioni, correzioni);

    return 0;
}

/* Scarta i caratteri rimasti sulla riga. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
