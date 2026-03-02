/*
 * 070-problema-validazione-password.c
 *
 * Problema reale: verifica dei requisiti di sicurezza di una password.
 *
 * Scenario: un sistema di autenticazione impone che le password
 * rispettino i seguenti requisiti minimi di sicurezza:
 *   1. Lunghezza minima di 8 caratteri
 *   2. Almeno una lettera maiuscola (A-Z)
 *   3. Almeno una lettera minuscola (a-z)
 *   4. Almeno una cifra numerica (0-9)
 *   5. Almeno un carattere speciale (!, @, #, $, %, &, *)
 *
 * Il programma legge la password, la analizza carattere per carattere
 * con flag booleani e comunica all'utente quali requisiti sono
 * soddisfatti e quali no.
 *
 * Concetti applicati:
 *   - lettura con scanf (password senza spazi)
 *   - scansione con ciclo while e flag booleani
 *   - verifica di intervalli ASCII per classificare i caratteri
 *   - output dettagliato dei requisiti soddisfatti/non soddisfatti
 */

#include <stdio.h>

int main(void) {

    /* Buffer per la password: max 50 caratteri + '\0' */
    char password[51];

    /* Lunghezza calcolata manualmente */
    int lunghezza = 0;

    /* Flag per ogni requisito: 0 = non soddisfatto, 1 = soddisfatto */
    int ha_maiuscola = 0;
    int ha_minuscola = 0;
    int ha_cifra     = 0;
    int ha_speciale  = 0;

    /* Carattere corrente durante la scansione */
    char c;

    /* Indice per scorrere la password */
    int i;

    /* Contatore dei requisiti soddisfatti */
    int requisiti_ok;

    printf("╔══════════════════════════════════════════╗\n");
    printf("║     SISTEMA DI VERIFICA PASSWORD         ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");

    printf("Requisiti minimi:\n");
    printf("  ✓ Almeno 8 caratteri\n");
    printf("  ✓ Almeno una maiuscola (A-Z)\n");
    printf("  ✓ Almeno una minuscola (a-z)\n");
    printf("  ✓ Almeno una cifra (0-9)\n");
    printf("  ✓ Almeno un carattere speciale (!@#$%%&*)\n\n");

    /* --- LETTURA PASSWORD ---
     * scanf senza spazi: le password non contengono spazi per convenzione. */
    printf("Inserisci la password: ");
    scanf("%50s", password);

    /* --- SCANSIONE E ANALISI ---
     * Un unico ciclo che conta la lunghezza e verifica tutti i requisiti
     * contemporaneamente, senza scorrere la stringa più volte. */
    i = 0;
    while (password[i] != '\0') {
        c = password[i];
        lunghezza++;

        /* Verifica maiuscola: ASCII 65 ('A') - 90 ('Z') */
        if (c >= 'A' && c <= 'Z') {
            ha_maiuscola = 1;
        }

        /* Verifica minuscola: ASCII 97 ('a') - 122 ('z') */
        if (c >= 'a' && c <= 'z') {
            ha_minuscola = 1;
        }

        /* Verifica cifra: ASCII 48 ('0') - 57 ('9') */
        if (c >= '0' && c <= '9') {
            ha_cifra = 1;
        }

        /* Verifica carattere speciale: confronto con i simboli ammessi */
        if (c == '!' || c == '@' || c == '#' || c == '$' ||
            c == '%' || c == '&' || c == '*') {
            ha_speciale = 1;
        }

        i++;
    }

    /* --- VALUTAZIONE REQUISITI ---
     * Contiamo quanti requisiti sono soddisfatti. */
    requisiti_ok = 0;

    if (lunghezza >= 8) {
        requisiti_ok++;
    }
    if (ha_maiuscola) {
        requisiti_ok++;
    }
    if (ha_minuscola) {
        requisiti_ok++;
    }
    if (ha_cifra) {
        requisiti_ok++;
    }
    if (ha_speciale) {
        requisiti_ok++;
    }

    /* --- OUTPUT DETTAGLIATO ---
     * Mostra ogni requisito con esito positivo o negativo. */
    printf("\n");
    printf("════════════════════════════════════════════\n");
    printf("  ANALISI PASSWORD: \"%s\"\n", password);
    printf("════════════════════════════════════════════\n");
    printf("  Lunghezza (%d car.): %s\n",
           lunghezza,
           (lunghezza >= 8) ? "OK" : "INSUFFICIENTE (minimo 8)");
    printf("  Maiuscola       : %s\n", ha_maiuscola ? "OK" : "MANCANTE");
    printf("  Minuscola       : %s\n", ha_minuscola ? "OK" : "MANCANTE");
    printf("  Cifra           : %s\n", ha_cifra     ? "OK" : "MANCANTE");
    printf("  Carattere spec. : %s\n", ha_speciale  ? "OK" : "MANCANTE");
    printf("────────────────────────────────────────────\n");
    printf("  Requisiti: %d/5 soddisfatti\n", requisiti_ok);
    printf("────────────────────────────────────────────\n");

    if (requisiti_ok == 5) {
        printf("  ESITO: PASSWORD ACCETTATA\n");
    } else {
        printf("  ESITO: PASSWORD RIFIUTATA\n");
        printf("  Correggere i requisiti segnalati con MANCANTE.\n");
    }

    printf("════════════════════════════════════════════\n");

    return 0;
}
