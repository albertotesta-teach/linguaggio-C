/*
 * 080-problema-carta-imbarco.c
 *
 * Viaggio d'istruzione: il controllo delle carte d'imbarco al gate
 *
 * La 5A parte in aereo per il viaggio d'istruzione. Al gate un
 * accompagnatore controlla la carta d'imbarco di ogni studente prima di
 * farlo passare. Due tipi diversi descrivono i dati:
 *
 *     typedef struct {                typedef struct {
 *         char codice[8];                 char cognome[20];
 *         int gate;                       char volo[8];
 *         int chiusura_ore;               char posto[4];
 *         int chiusura_minuti;        } CartaImbarco;
 *     } Volo;
 *
 * Il volo della classe è fisso. Per ogni studente si leggono l'ora attuale
 * e i dati della carta (cognome, volo, posto). Esito:
 *   - "volo sbagliato" se il codice del volo non è quello della classe;
 *   - "imbarco chiuso" se l'ora attuale è uguale o successiva alla chiusura;
 *   - altrimenti "passa", con il posto assegnato.
 * Il cognome FINE termina e il programma stampa quanti studenti sono
 * passati.
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char codice[8];
    int gate;
    int chiusura_ore;
    int chiusura_minuti;
} Volo;

typedef struct {
    char cognome[20];
    char volo[8];
    char posto[4];
} CartaImbarco;

void svuota_riga(void);

int main(void)
{
    Volo classe = {"FR1452", 14, 9, 35};
    CartaImbarco carta;
    int ore;
    int minuti;
    int passati = 0;
    int fine = 0;
    int letti;

    printf("Volo %s, gate %d, chiusura imbarco %02d:%02d\n", classe.codice, classe.gate,
           classe.chiusura_ore, classe.chiusura_minuti);
    while (!fine) {
        printf("Cognome (FINE per terminare): ");
        if (scanf("%19s", carta.cognome) != 1) {
            fine = 1;                   /* input terminato: come FINE */
        } else if (strcmp(carta.cognome, "FINE") == 0) {
            fine = 1;
        } else {
            svuota_riga();              /* un cognome per riga */
            printf("Ora attuale, volo e posto (hh mm volo posto): ");
            letti = scanf("%d %d %7s %3s", &ore, &minuti, carta.volo, carta.posto);
            if (letti != EOF) {
                svuota_riga();          /* scarta il resto della riga */
            }
            if (letti == EOF) {
                printf("\n  Dati incompleti.\n");
                fine = 1;
            } else if (letti != 4) {
                printf("  %s: dati non validi, ripetere.\n", carta.cognome);
            } else if (strcmp(carta.volo, classe.codice) != 0) {
                printf("  %s: volo sbagliato (%s invece di %s).\n", carta.cognome, carta.volo,
                       classe.codice);
            } else if (ore * 60 + minuti >= classe.chiusura_ore * 60 + classe.chiusura_minuti) {
                printf("  %s: imbarco chiuso.\n", carta.cognome);
            } else {
                printf("  %s: passa, posto %s.\n", carta.cognome, carta.posto);
                passati++;
            }
        }
    }
    printf("Studenti imbarcati: %d\n", passati);

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
