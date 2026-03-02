/*
 * 040-input-output-combinati.c
 *
 * Lettura e visualizzazione combinata di più campi stringa.
 *
 * Questo esempio mostra come gestire una sessione di input completa:
 * lettura di più campi con fgets, rimozione del '\n', e
 * visualizzazione formattata in una scheda riepilogativa.
 *
 * È il pattern base per qualsiasi form di inserimento dati
 * in un programma C a riga di comando.
 */

#include <stdio.h>

int main(void) {

    /* Campi della scheda contatto */
    char nome[31];
    char cognome[31];
    char citta[51];
    char email[101];
    char telefono[16];

    /* Indice per la rimozione del '\n' */
    int i;

    printf("=== INSERIMENTO NUOVO CONTATTO ===\n\n");

    /* --- LETTURA DEI CAMPI ---
     * Per ogni campo: fgets + rimozione '\n'.
     * Il pattern si ripete identico per ogni campo. */

    /* Nome */
    printf("Nome: ");
    fgets(nome, 31, stdin);
    i = 0;
    while (nome[i] != '\n' && nome[i] != '\0') {
        i++;
    }
    nome[i] = '\0';

    /* Cognome */
    printf("Cognome: ");
    fgets(cognome, 31, stdin);
    i = 0;
    while (cognome[i] != '\n' && cognome[i] != '\0') {
        i++;
    }
    cognome[i] = '\0';

    /* Città */
    printf("Città: ");
    fgets(citta, 51, stdin);
    i = 0;
    while (citta[i] != '\n' && citta[i] != '\0') {
        i++;
    }
    citta[i] = '\0';

    /* Email */
    printf("Email: ");
    fgets(email, 101, stdin);
    i = 0;
    while (email[i] != '\n' && email[i] != '\0') {
        i++;
    }
    email[i] = '\0';

    /* Telefono: usiamo scanf perché non contiene spazi */
    printf("Telefono (senza spazi): ");
    scanf("%15s", telefono);

    /* --- VISUALIZZAZIONE SCHEDA ---
     * I dati vengono presentati in una scheda formattata
     * con larghezze fisse per l'allineamento. */
    printf("\n");
    printf("╔══════════════════════════════════════╗\n");
    printf("║         SCHEDA CONTATTO              ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║ %-10s: %-25s║\n", "Nome",     nome);
    printf("║ %-10s: %-25s║\n", "Cognome",  cognome);
    printf("║ %-10s: %-25s║\n", "Città",    citta);
    printf("║ %-10s: %-25s║\n", "Email",    email);
    printf("║ %-10s: %-25s║\n", "Telefono", telefono);
    printf("╚══════════════════════════════════════╝\n");

    return 0;
}
