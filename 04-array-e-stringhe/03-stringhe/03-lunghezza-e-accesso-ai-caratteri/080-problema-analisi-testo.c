/*
 * 080-problema-analisi-testo.c
 *
 * Problema reale: statistiche di un testo per un editor semplice.
 *
 * Scenario: un editor di testo minimalista mostra all'utente le
 * statistiche del testo inserito: numero di caratteri totali,
 * numero di parole, numero di spazi e caratteri rimanenti
 * rispetto a un limite massimo (es. post sui social media).
 *
 * Le parole vengono contate rilevando le transizioni da spazio
 * a non-spazio: ogni volta che un carattere non-spazio segue
 * uno spazio (o è il primo carattere), si conta una nuova parola.
 *
 * Concetti applicati:
 *   - lettura con fgets per testo con spazi
 *   - scansione con ciclo while e variabile di stato
 *   - contatori multipli aggiornati in un singolo ciclo
 *   - calcolo caratteri rimanenti rispetto a un limite
 */

#include <stdio.h>

/* Limite di caratteri (tipico di alcuni social media) */
#define LIMITE_MAX 280

int main(void) {

    /* Buffer per il testo: limite + 2 (per '\n' e '\0') */
    char testo[283];

    /* Contatori */
    int num_caratteri = 0; /* caratteri totali (escluso '\0') */
    int num_parole    = 0; /* parole nel testo */
    int num_spazi     = 0; /* spazi nel testo */

    /* Variabile di stato: 1 se il carattere precedente era uno spazio
     * (o se siamo all'inizio), 0 altrimenti.
     * Serve per rilevare l'inizio di una nuova parola. */
    int precedente_era_spazio;

    /* Carattere corrente */
    char c;

    /* Indice per scorrere il testo */
    int i;

    /* Caratteri rimanenti rispetto al limite */
    int rimanenti;

    printf("╔══════════════════════════════════════════╗\n");
    printf("║      EDITOR - ANALISI TESTO              ║\n");
    printf("║      Limite: %d caratteri               ║\n", LIMITE_MAX);
    printf("╚══════════════════════════════════════════╝\n\n");

    /* --- LETTURA TESTO ---
     * fgets con limite = LIMITE_MAX + 2 per gestire '\n' e '\0'. */
    printf("Inserisci il testo:\n> ");
    fgets(testo, 283, stdin);

    /* Rimozione '\n' */
    i = 0;
    while (testo[i] != '\n' && testo[i] != '\0') {
        i++;
    }
    testo[i] = '\0';

    /* --- SCANSIONE E CALCOLO STATISTICHE ---
     * Un singolo ciclo calcola tutti i contatori.
     *
     * Algoritmo di conteggio parole:
     * - Una parola inizia quando troviamo un carattere non-spazio
     *   preceduto da uno spazio (o all'inizio del testo).
     * - Usiamo la variabile `precedente_era_spazio` come "memoria"
     *   del carattere precedente. */
    precedente_era_spazio = 1; /* all'inizio consideriamo uno spazio virtuale */

    i = 0;
    while (testo[i] != '\0') {
        c = testo[i];
        num_caratteri++;

        if (c == ' ') {
            num_spazi++;
            precedente_era_spazio = 1; /* segnaliamo che c'era uno spazio */
        } else {
            /* Carattere non-spazio: se prima c'era uno spazio,
             * stiamo iniziando una nuova parola. */
            if (precedente_era_spazio) {
                num_parole++;
            }
            precedente_era_spazio = 0; /* segnaliamo che non c'era spazio */
        }

        i++;
    }

    /* --- CALCOLO CARATTERI RIMANENTI --- */
    rimanenti = LIMITE_MAX - num_caratteri;

    /* --- OUTPUT STATISTICHE --- */
    printf("\n");
    printf("════════════════════════════════════════════\n");
    printf("  STATISTICHE TESTO\n");
    printf("════════════════════════════════════════════\n");
    printf("  Caratteri totali  : %d / %d\n", num_caratteri, LIMITE_MAX);
    printf("  Parole            : %d\n", num_parole);
    printf("  Spazi             : %d\n", num_spazi);

    if (rimanenti >= 0) {
        printf("  Caratteri rimasti : %d\n", rimanenti);
    } else {
        printf("  Caratteri in eccesso: %d\n", -rimanenti);
    }

    /* Barra di utilizzo: 20 celle, ognuna = LIMITE_MAX/20 caratteri */
    printf("\n  Utilizzo: [");
    i = 0;
    while (i < 20) {
        if (i < (num_caratteri * 20) / LIMITE_MAX) {
            putchar('#');
        } else {
            putchar('.');
        }
        i++;
    }
    printf("] %d%%\n", (num_caratteri * 100) / LIMITE_MAX);

    printf("════════════════════════════════════════════\n");

    if (rimanenti < 0) {
        printf("\n  ATTENZIONE: testo troppo lungo di %d caratteri.\n",
               -rimanenti);
    } else if (rimanenti == 0) {
        printf("\n  Limite raggiunto esattamente.\n");
    } else {
        printf("\n  Testo nel limite consentito.\n");
    }

    return 0;
}
