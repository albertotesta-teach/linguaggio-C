/*
 * 070-problema-modifiche-anagrafica.c
 *
 * Segreteria didattica: aggiornare i recapiti di uno studente
 *
 * A inizio anno le famiglie possono aggiornare i recapiti. L'operatore
 * della segreteria apre la scheda anagrafica, ne fa una COPIA di lavoro e
 * inserisce i nuovi valori; premendo solo Invio un campo resta invariato.
 *
 *     typedef struct {
 *         char cognome[20];
 *         char nome[20];
 *         char telefono[16];
 *         char email[40];
 *         int classe;              anno di corso, 1-5
 *     } Anagrafica;
 *
 *     Anagrafica modificata = originale;
 *
 * Alla fine il programma confronta le due schede campo per campo, elenca
 * solo i campi cambiati (valore vecchio -> nuovo) e chiede conferma. Con
 * S la copia di lavoro diventa la scheda ufficiale (originale = modificata),
 * altrimenti le modifiche si scartano.
 */

#include <stdio.h>
#include <string.h>

#define LUNG_RIGA 80

typedef struct {
    char cognome[20];
    char nome[20];
    char telefono[16];
    char email[40];
    int classe;
} Anagrafica;

void leggi_riga(char *riga, int lunghezza);

int main(void)
{
    Anagrafica originale = {"Marino", "Chiara", "0131 555 1234", "famiglia.marino@posta.it", 3};
    Anagrafica modificata = originale;
    char riga[LUNG_RIGA];
    int cambiati = 0;

    printf("Scheda di %s %s (Invio per lasciare invariato)\n", originale.cognome, originale.nome);

    printf("Telefono [%s]: ", modificata.telefono);
    leggi_riga(riga, LUNG_RIGA);
    if (riga[0] != '\0' && strlen(riga) < sizeof(modificata.telefono)) {
        strcpy(modificata.telefono, riga);
    }
    printf("Email [%s]: ", modificata.email);
    leggi_riga(riga, LUNG_RIGA);
    if (riga[0] != '\0' && strlen(riga) < sizeof(modificata.email)) {
        strcpy(modificata.email, riga);
    }
    printf("Classe [%d]: ", modificata.classe);
    leggi_riga(riga, LUNG_RIGA);
    if (riga[0] >= '1' && riga[0] <= '5' && riga[1] == '\0') {
        modificata.classe = riga[0] - '0';
    }

    printf("\nModifiche:\n");
    if (strcmp(originale.telefono, modificata.telefono) != 0) {
        printf("  telefono: %s -> %s\n", originale.telefono, modificata.telefono);
        cambiati++;
    }
    if (strcmp(originale.email, modificata.email) != 0) {
        printf("  email:    %s -> %s\n", originale.email, modificata.email);
        cambiati++;
    }
    if (originale.classe != modificata.classe) {
        printf("  classe:   %d -> %d\n", originale.classe, modificata.classe);
        cambiati++;
    }

    if (cambiati == 0) {
        printf("  nessuna\n");
    } else {
        printf("Confermi %d %s? (S/N): ", cambiati, cambiati == 1 ? "modifica" : "modifiche");
        leggi_riga(riga, LUNG_RIGA);
        if (riga[0] == 'S' || riga[0] == 's') {
            originale = modificata;
            printf("Scheda aggiornata.\n");
        } else {
            printf("Modifiche scartate.\n");
        }
    }
    printf("Scheda ufficiale: %s %s, %s, %s, classe %d\n", originale.cognome, originale.nome,
           originale.telefono, originale.email, originale.classe);

    return 0;
}

/* Legge una riga e toglie l'a capo; a fine input la riga è vuota.
 * Di una riga troppo lunga si tiene l'inizio e si scarta il resto. */
void leggi_riga(char *riga, int lunghezza)
{
    char *a_capo;
    int resto;

    if (fgets(riga, lunghezza, stdin) == NULL) {
        riga[0] = '\0';
    } else {
        a_capo = strchr(riga, '\n');
        if (a_capo != NULL) {
            *a_capo = '\0';
        } else {
            resto = getchar();
            while (resto != '\n' && resto != EOF) {
                resto = getchar();
            }
        }
    }
}
