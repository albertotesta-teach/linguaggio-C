/*
 * 050-problema-registro-presenze.c
 *
 * Problema reale: registro elettronico delle presenze scolastiche.
 *
 * Scenario: all'ingresso di una scuola, uno studente digita il proprio
 * nome e cognome su un terminale. Il sistema registra la presenza
 * stampando una riga di log formattata con numero progressivo,
 * data preimpostata e nome dello studente.
 *
 * Concetti applicati:
 *   - lettura di stringhe con spazi tramite fgets
 *   - rimozione del '\n' finale lasciato da fgets
 *   - verifica che il campo non sia vuoto prima di registrare
 *   - output formattato con campi a larghezza fissa
 */

#include <stdio.h>

int main(void) {

    /* Data e ora preimpostate (in un sistema reale verrebbero
     * lette dall'orologio di sistema, qui sono costanti didattiche) */
    char data[]  = "2024-11-15";
    char ora[]   = "08:32";

    /* Buffer per il nome completo dello studente */
    char nome_studente[61]; /* max 60 caratteri + '\0' */

    /* Numero progressivo della registrazione (simulato) */
    int numero_registrazione = 142;

    /* Indice per scorrere la stringa e rimuovere '\n' */
    int i;

    /* Flag: 1 se il nome inserito è valido, 0 altrimenti */
    int nome_valido;

    printf("╔════════════════════════════════════════════╗\n");
    printf("║     REGISTRO ELETTRONICO PRESENZE          ║\n");
    printf("║     Istituto Tecnico G. Marconi            ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");

    printf("Data  : %s\n", data);
    printf("Ora   : %s\n\n", ora);

    /* --- LETTURA DEL NOME STUDENTE ---
     * Usiamo fgets perché il nome può contenere spazi
     * (es. "Maria Grazia" o "De Luca Giovanni"). */
    printf("Inserisci nome e cognome: ");
    fgets(nome_studente, 61, stdin);

    /* --- RIMOZIONE DEL '\n' FINALE ---
     * fgets include '\n' nella stringa letta.
     * Scorriamo fino a trovarlo e lo sostituiamo con '\0'. */
    i = 0;
    while (nome_studente[i] != '\n' && nome_studente[i] != '\0') {
        i++;
    }
    nome_studente[i] = '\0';

    /* --- VERIFICA CAMPO NON VUOTO ---
     * Se lo studente ha premuto invio senza digitare nulla,
     * nome_studente[0] sarà '\0' (stringa vuota dopo rimozione '\n').
     * In questo caso non registriamo la presenza. */
    if (nome_studente[0] == '\0') {
        nome_valido = 0;
    } else {
        nome_valido = 1;
    }

    /* --- REGISTRAZIONE E OUTPUT ---
     * Se il nome è valido, stampiamo la riga di registro formattata. */
    printf("\n");

    if (nome_valido) {
        printf("════════════════════════════════════════════════════\n");
        printf("  PRESENZA REGISTRATA\n");
        printf("════════════════════════════════════════════════════\n");
        printf("  N. progressivo : %d\n",   numero_registrazione);
        printf("  Data           : %s\n",   data);
        printf("  Ora            : %s\n",   ora);
        printf("  Studente       : %s\n",   nome_studente);
        printf("════════════════════════════════════════════════════\n");
        printf("\n");
        printf("Presenza di %s registrata correttamente.\n", nome_studente);
    } else {
        printf("ERRORE: nessun nome inserito. Presenza non registrata.\n");
    }

    return 0;
}
