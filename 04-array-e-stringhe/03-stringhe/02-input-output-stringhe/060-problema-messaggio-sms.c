/*
 * 060-problema-messaggio-sms.c
 *
 * Problema reale: sistema di messaggistica con limite di caratteri.
 *
 * Scenario: un'applicazione di messaggistica permette di inviare
 * messaggi di testo con un limite massimo di 160 caratteri (lo stesso
 * limite storico degli SMS). L'utente digita il messaggio e il sistema
 * mostra quanti caratteri ha usato e quanti ne restano disponibili,
 * senza usare strlen ma scorrendo il buffer con un ciclo while.
 *
 * Concetti applicati:
 *   - lettura con fgets con limite di buffer
 *   - rimozione del '\n' finale
 *   - conteggio manuale dei caratteri con ciclo while
 *   - verifica del limite massimo e output condizionato
 */

#include <stdio.h>

/* Limite massimo di caratteri del messaggio (storico SMS) */
#define LIMITE_CARATTERI 160

int main(void) {

    /* Mittente e destinatario (preimpostati per semplicità) */
    char mittente[]    = "Mario Rossi";
    char destinatario[] = "Anna Bianchi";

    /* Buffer per il testo del messaggio.
     * Dimensione: LIMITE_CARATTERI + 1 per '\n' di fgets + 1 per '\0'
     * = 162 celle totali. */
    char messaggio[162];

    /* Contatore dei caratteri digitati (calcolato senza strlen) */
    int num_caratteri;

    /* Caratteri ancora disponibili */
    int caratteri_rimasti;

    /* Indice per scorrere il buffer */
    int i;

    /* Carattere letto per scartare il testo oltre il buffer */
    int c;

    /* 1 se il messaggio è stato accorciato a LIMITE_CARATTERI */
    int troncato = 0;

    printf("╔══════════════════════════════════════════╗\n");
    printf("║         SISTEMA DI MESSAGGISTICA         ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");

    printf("Da      : %s\n", mittente);
    printf("A       : %s\n\n", destinatario);
    printf("Limite  : %d caratteri\n\n", LIMITE_CARATTERI);

    /* --- LETTURA DEL MESSAGGIO ---
     * fgets legge al massimo 161 caratteri (162 - 1 per '\0'): non supera
     * mai il buffer, ma da sola non basta a rispettare il limite di 160.
     * Se la lettura fallisce (fine dell'input) il messaggio è vuoto. */
    printf("Scrivi il tuo messaggio:\n> ");
    if (fgets(messaggio, 162, stdin) == NULL) {
        messaggio[0] = '\0';
    }

    /* --- RIMOZIONE DEL '\n' E CONTEGGIO SIMULTANEO ---
     * Scorriamo la stringa con un ciclo while per due scopi:
     * 1. trovare '\n' e sostituirlo con '\0'
     * 2. contare i caratteri effettivi del messaggio
     * Usiamo un solo ciclo per entrambe le operazioni. */
    i = 0;
    while (messaggio[i] != '\n' && messaggio[i] != '\0') {
        i++; /* conta i caratteri e avanza */
    }
    /* Se il ciclo si è fermato su '\0' senza trovare '\n' e il buffer è
     * pieno, la riga era più lunga del buffer: i caratteri rimasti
     * nell'input (compreso il '\n') vanno scartati, altrimenti
     * resterebbero per la lettura successiva. */
    if (messaggio[i] == '\0' && i == 161) {
        c = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }

    /* messaggio[i] è ora '\n' oppure '\0': in entrambi i casi
     * lo sostituiamo con '\0' per terminare correttamente la stringa. */
    messaggio[i] = '\0';

    /* Oltre il limite si tronca a LIMITE_CARATTERI caratteri. */
    if (i > LIMITE_CARATTERI) {
        messaggio[LIMITE_CARATTERI] = '\0';
        i = LIMITE_CARATTERI;
        troncato = 1;
    }

    /* Il numero di caratteri è il valore corrente di i
     * (l'indice del terminatore coincide con la lunghezza). */
    num_caratteri = i;

    /* Calcola i caratteri ancora disponibili */
    caratteri_rimasti = LIMITE_CARATTERI - num_caratteri;

    /* --- OUTPUT RIEPILOGATIVO ---
     * Mostra il messaggio formattato e le statistiche di utilizzo. */
    printf("\n");
    printf("══════════════════════════════════════════════\n");
    printf("  ANTEPRIMA MESSAGGIO\n");
    printf("══════════════════════════════════════════════\n");
    printf("  Da  : %s\n",   mittente);
    printf("  A   : %s\n",   destinatario);
    printf("  Msg : %s\n",   messaggio);
    printf("══════════════════════════════════════════════\n\n");

    /* Statistiche caratteri */
    printf("Caratteri usati      : %d / %d\n", num_caratteri, LIMITE_CARATTERI);

    printf("Caratteri rimanenti  : %d\n", caratteri_rimasti);
    if (troncato) {
        printf("Il testo superava il limite: messaggio troncato a %d caratteri.\n",
               LIMITE_CARATTERI);
    }

    /* Barra di utilizzo testuale (ogni '#' = 16 caratteri circa) */
    printf("\nUtilizzo: [");
    i = 0;
    while (i < 10) {
        /* Stampa '#' per le decine usate, '.' per quelle libere */
        if (i < num_caratteri / 16) {
            putchar('#');
        } else {
            putchar('.');
        }
        i++;
    }
    printf("] %d%%\n", (num_caratteri * 100) / LIMITE_CARATTERI);

    /* Messaggio di stato finale */
    printf("\n");
    if (num_caratteri == 0) {
        printf("ATTENZIONE: messaggio vuoto, invio annullato.\n");
    } else {
        printf("Messaggio pronto per l'invio.\n");
    }

    return 0;
}
