/*
 * 040-problema-codice-fiscale.c
 *
 * Problema reale: gestione di dati anagrafici in un sistema di registrazione.
 *
 * Scenario: una scuola raccoglie i dati degli studenti al momento
 * dell'iscrizione. Il programma dichiara e inizializza le stringhe
 * che rappresentano nome, cognome, codice fiscale e classe,
 * poi le visualizza in una scheda formattata.
 *
 * Concetti applicati:
 *  - dichiarazione di stringhe con dimensione appropriata
 *  - inizializzazione con valori predefiniti (dati di esempio)
 *  - accesso a singoli caratteri per estrarre informazioni
 *  - importanza di dimensionare correttamente gli array
 */

#include <stdio.h>

int main(void) {

    /* Dati dello studente: dimensioni scelte in base ai limiti reali.
     * Nome e cognome: max 30 caratteri (limite anagrafico comune).
     * Codice fiscale: esattamente 16 caratteri + '\0' = 17 celle.
     * Classe: formato "5A", "3B", ecc. → max 4 caratteri + '\0'. */
    char nome[31]          = "Giovanni";
    char cognome[31]       = "Ferrero";
    char codice_fiscale[17] = "FRRGNN05A15L219X";
    char classe[5]         = "4B";
    char indirizzo[51]     = "Via Roma 12, Torino";

    /* Stampa della scheda studente formattata */
    printf("========================================\n");
    printf("        SCHEDA STUDENTE                 \n");
    printf("========================================\n");
    printf("Nome             : %s\n", nome);
    printf("Cognome          : %s\n", cognome);
    printf("Codice fiscale   : %s\n", codice_fiscale);
    printf("Classe           : %s\n", classe);
    printf("Indirizzo        : %s\n", indirizzo);
    printf("========================================\n");
    printf("\n");

    /* Estrazione di informazioni dal codice fiscale.
     * Il codice fiscale italiano ha una struttura precisa:
     * posizioni 0-2  → prime tre consonanti del cognome
     * posizioni 3-5  → prime tre consonanti del nome
     * posizioni 6-7  → ultime due cifre dell'anno di nascita
     * posizione  8   → lettera del mese di nascita
     * posizioni 9-10 → giorno di nascita (+ 40 per le donne)
     * posizioni 11-14 → codice comune di nascita
     * posizione  15  → carattere di controllo */
    printf("Informazioni estratte dal codice fiscale:\n");

    /* Estrae le iniziali del cognome (prime 3 lettere del CF) */
    printf("  Sigla cognome  : %c%c%c\n",
           codice_fiscale[0], codice_fiscale[1], codice_fiscale[2]);

    /* Estrae le ultime due cifre dell'anno di nascita */
    printf("  Anno di nascita: 20%c%c\n",
           codice_fiscale[6], codice_fiscale[7]);

    /* Estrae il giorno di nascita */
    printf("  Giorno nascita : %c%c\n",
           codice_fiscale[9], codice_fiscale[10]);

    /* Estrae il codice comune */
    printf("  Codice comune  : %c%c%c%c\n",
           codice_fiscale[11], codice_fiscale[12],
           codice_fiscale[13], codice_fiscale[14]);

    printf("\n");

    /* Verifica che il codice fiscale abbia la lunghezza corretta (16 caratteri).
     * Contiamo manualmente i caratteri fino a '\0'. */
    int lunghezza = 0;
    while (codice_fiscale[lunghezza] != '\0') {
        lunghezza++; /* Incrementa il contatore per ogni carattere trovato */
    }

    printf("Lunghezza codice fiscale: %d caratteri ", lunghezza);
    if (lunghezza == 16) {
        printf("(corretta)\n");
    } else {
        printf("(ERRORE: dovrebbe essere 16)\n");
    }

    return 0;
}
