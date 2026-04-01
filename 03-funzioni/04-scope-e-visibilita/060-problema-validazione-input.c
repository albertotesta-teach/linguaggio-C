/*
 * 060-problema-validazione-input.c
 *
 * Validazione di un modulo di registrazione con stato globale
 *
 * Un modulo di registrazione raccoglie nome, eta' e codice cliente.
 * Ogni campo viene validato da una funzione dedicata. Un contatore
 * globale tiene traccia degli errori trovati: se al termine il contatore
 * è zero il modulo è accettato, altrimenti viene rifiutato.
 *
 * Il contatore degli errori è una variabile globale perché deve essere
 * aggiornato da funzioni diverse (una per campo) e letto alla fine
 * dal main per la decisione finale.
 */

#include <stdio.h>

/* --- Stato globale di validazione --- */
int errori_trovati = 0;   /* incrementato da ogni funzione di validazione */

/* Prototipi */
int  valida_eta(int eta);
int  valida_codice(int codice);
void segnala_errore(const char *messaggio);
void stampa_esito(void);

/* Segnala un errore: stampa il messaggio e incrementa il contatore globale */
void segnala_errore(const char *messaggio)
{
    printf("  ERRORE: %s\n", messaggio);
    errori_trovati = errori_trovati + 1;
}

/* Valida l'eta': deve essere compresa tra 18 e 120.
 * Restituisce 1 se valida, 0 altrimenti. */
int valida_eta(int eta)
{
    int valida;
    valida = (eta >= 18 && eta <= 120);
    if (!valida) {
        segnala_errore("eta' non valida (deve essere compresa tra 18 e 120)");
    }
    return valida;
}

/* Valida il codice cliente: deve essere un numero a 5 cifre (10000-99999).
 * Restituisce 1 se valido, 0 altrimenti. */
int valida_codice(int codice)
{
    int valido;
    valido = (codice >= 10000 && codice <= 99999);
    if (!valido) {
        segnala_errore("codice cliente non valido (deve essere a 5 cifre)");
    }
    return valido;
}

/* Stampa l'esito finale della validazione basandosi sul contatore globale */
void stampa_esito(void)
{
    printf("\n");
    if (errori_trovati == 0) {
        printf("Modulo ACCETTATO. Nessun errore rilevato.\n");
    } else {
        printf("Modulo RIFIUTATO. Errori rilevati: %d\n", errori_trovati);
    }
}

int main(void)
{
    int eta, codice;

    printf("=== Validazione modulo di registrazione ===\n\n");

    /* Caso 1: modulo corretto */
    printf("--- Caso 1: dati corretti ---\n");
    errori_trovati = 0;   /* reset prima di ogni nuovo modulo */
    eta    = 35;
    codice = 47231;
    printf("  Eta':    %d\n", eta);
    printf("  Codice:  %d\n", codice);
    valida_eta(eta);
    valida_codice(codice);
    stampa_esito();

    printf("\n");

    /* Caso 2: eta' non valida */
    printf("--- Caso 2: eta' non valida ---\n");
    errori_trovati = 0;
    eta    = 15;
    codice = 83400;
    printf("  Eta':    %d\n", eta);
    printf("  Codice:  %d\n", codice);
    valida_eta(eta);
    valida_codice(codice);
    stampa_esito();

    printf("\n");

    /* Caso 3: tutti i campi errati */
    printf("--- Caso 3: tutti i campi errati ---\n");
    errori_trovati = 0;
    eta    = 200;
    codice = 999;
    printf("  Eta':    %d\n", eta);
    printf("  Codice:  %d\n", codice);
    valida_eta(eta);
    valida_codice(codice);
    stampa_esito();

    return 0;
}
