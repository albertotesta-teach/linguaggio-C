/*
 * 080-problema-log-sistema.c
 *
 * Problema reale: sistema di logging per applicazioni.
 *
 * Scenario: un'applicazione software registra gli eventi di sistema
 * in un file di log. Ogni riga ha un formato preciso:
 *
 *   [TIMESTAMP] [LIVELLO] CODICE: descrizione
 *
 * Il programma legge da tastiera il codice evento (senza spazi, con scanf)
 * e la descrizione dell'evento (con spazi, con fgets), poi compone
 * e stampa la riga di log formattata, mostrando come combinare
 * i due metodi di input nella stessa sessione.
 *
 * Concetti applicati:
 *   - uso combinato di scanf e fgets nella stessa sessione
 *   - gestione del buffer residuo dopo scanf
 *   - rimozione del '\n' da fgets
 *   - output formattato con campi a larghezza fissa
 *   - uso di #define per costanti (livelli di log)
 */

#include <stdio.h>

/* Livelli di severità del log (standard comune nei sistemi reali) */
#define LIVELLO_INFO  "INFO "
#define LIVELLO_WARN  "WARN "
#define LIVELLO_ERROR "ERROR"

int main(void) {

    /* Timestamp preimpostato (in un sistema reale verrebbe generato
     * automaticamente dall'orologio di sistema) */
    char timestamp[] = "2024-11-15 08:45:22";

    /* Nome dell'applicazione che genera il log */
    char applicazione[] = "GestMagazzino";

    /* Codice evento: identificatore breve senza spazi
     * (es. "DB_CONN_ERR", "FILE_NOT_FOUND", "AUTH_OK") */
    char codice_evento[21]; /* max 20 caratteri + '\0' */

    /* Descrizione estesa dell'evento: può contenere spazi */
    char descrizione[201]; /* max 200 caratteri + '\0' */

    /* Livello di severità scelto dall'utente */
    int scelta_livello;

    /* Puntatore al livello selezionato (stringa costante) */
    char livello[6]; /* 5 caratteri + '\0' */

    /* Indice per rimozione '\n' */
    int i;

    printf("╔══════════════════════════════════════════╗\n");
    printf("║      SISTEMA DI LOGGING - INSERIMENTO    ║\n");
    printf("║      Applicazione: %-22s║\n", applicazione);
    printf("╚══════════════════════════════════════════╝\n\n");

    printf("Timestamp: %s\n\n", timestamp);

    /* --- SCELTA DEL LIVELLO DI SEVERITÀ ---
     * Lettura di un intero con scanf. */
    printf("Livello di severità:\n");
    printf("  1 = INFO  (evento informativo normale)\n");
    printf("  2 = WARN  (attenzione, potenziale problema)\n");
    printf("  3 = ERROR (errore che richiede intervento)\n");
    printf("Scelta: ");
    scanf("%d", &scelta_livello);

    /* Assegna il livello in base alla scelta.
     * Copia il livello scelto nel buffer locale carattere per carattere.
     * Per ora usiamo questa tecnica; le funzioni su stringhe
     * saranno introdotte nella sezione 04-funzioni-su-stringhe. */
    if (scelta_livello == 1) {
        livello[0]='I'; livello[1]='N'; livello[2]='F';
        livello[3]='O'; livello[4]=' '; livello[5]='\0';
    } else if (scelta_livello == 2) {
        livello[0]='W'; livello[1]='A'; livello[2]='R';
        livello[3]='N'; livello[4]=' '; livello[5]='\0';
    } else {
        /* Qualsiasi altro valore viene trattato come ERROR */
        livello[0]='E'; livello[1]='R'; livello[2]='R';
        livello[3]='O'; livello[4]='R'; livello[5]='\0';
    }

    /* --- LETTURA CODICE EVENTO ---
     * Il codice non contiene spazi: scanf è appropriato.
     * Prima svuotiamo il buffer dal '\n' lasciato dalla scanf precedente. */
    {
        int c;
        c = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }

    printf("\nCodice evento (es. DB_CONN_ERR): ");
    scanf("%20s", codice_evento);

    /* Svuota il buffer dopo scanf prima di fgets */
    {
        int c;
        c = getchar();
        while (c != '\n' && c != EOF) {
            c = getchar();
        }
    }

    /* --- LETTURA DESCRIZIONE ---
     * La descrizione può contenere spazi: usiamo fgets. */
    printf("Descrizione evento: ");
    fgets(descrizione, 201, stdin);

    /* Rimozione '\n' dalla descrizione */
    i = 0;
    while (descrizione[i] != '\n' && descrizione[i] != '\0') {
        i++;
    }
    descrizione[i] = '\0';

    /* --- COMPOSIZIONE E STAMPA DELLA RIGA DI LOG ---
     * Formato standard: [TIMESTAMP] [LIVELLO] APP CODICE: descrizione */
    printf("\n");
    printf("════════════════════════════════════════════════════════════\n");
    printf("  RIGA DI LOG GENERATA\n");
    printf("════════════════════════════════════════════════════════════\n");
    printf("[%s] [%s] %s %s: %s\n",
           timestamp, livello, applicazione, codice_evento, descrizione);
    printf("════════════════════════════════════════════════════════════\n");
    printf("\n");

    /* Riepilogo dei campi per verifica */
    printf("Dettaglio campi:\n");
    printf("  Timestamp    : %s\n", timestamp);
    printf("  Livello      : %s\n", livello);
    printf("  Applicazione : %s\n", applicazione);
    printf("  Codice       : %s\n", codice_evento);
    printf("  Descrizione  : %s\n", descrizione);

    return 0;
}
