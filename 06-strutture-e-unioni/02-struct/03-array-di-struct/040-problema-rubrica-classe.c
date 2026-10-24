/*
 * 040-problema-rubrica-classe.c
 *
 * Rubrica della classe: ricerca dei contatti per inizio del cognome
 *
 * Il rappresentante di classe tiene una rubrica con cognome, nome,
 * telefono e ruolo di ogni contatto (studente, docente, genitore):
 *
 *     typedef struct {
 *         char cognome[20];
 *         char nome[16];
 *         char telefono[16];
 *         char ruolo[10];
 *     } Contatto;
 *
 *     Contatto rubrica[CONTATTI];
 *
 * Comandi:
 *     C testo    contatti il cui cognome inizia con il testo (strncmp)
 *     R ruolo    tutti i contatti con quel ruolo
 *     E          elenco completo
 *     Q          fine
 * Per ogni ricerca il programma stampa quanti contatti ha trovato.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define CONTATTI 8
#define LUNG 20

typedef struct {
    char cognome[20];
    char nome[16];
    char telefono[16];
    char ruolo[10];
} Contatto;

void svuota_riga(void);

int main(void)
{
    Contatto rubrica[CONTATTI] = {
        {"Barbieri", "Giorgia", "347 1122334", "studente"},
        {"Bassi", "Andrea", "333 5566778", "studente"},
        {"Benedetti", "Laura", "0131 222333", "docente"},
        {"Caruso", "Matteo", "349 9988776", "studente"},
        {"Caputo", "Rosa", "340 4455667", "genitore"},
        {"Fontana", "Diego", "0131 444555", "docente"},
        {"Lombardi", "Noemi", "338 7766554", "studente"},
        {"Bassi", "Paola", "335 1212121", "genitore"}
    };
    char comando = ' ';
    char testo[LUNG];
    int i;
    int trovati;

    while (comando != 'Q') {
        printf("Comando (C cognome, R ruolo, E, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'C' || comando == 'R') {
            if (scanf("%19s", testo) != 1) {
                comando = 'Q';
            } else {
                trovati = 0;
                for (i = 0; i < CONTATTI; i++) {
                    if ((comando == 'C' && strncmp(rubrica[i].cognome, testo, strlen(testo)) == 0) ||
                        (comando == 'R' && strcmp(rubrica[i].ruolo, testo) == 0)) {
                        printf("  %-10s %-8s %-12s %s\n", rubrica[i].cognome, rubrica[i].nome,
                               rubrica[i].telefono, rubrica[i].ruolo);
                        trovati++;
                    }
                }
                printf("  Trovati: %d\n", trovati);
            }
        } else if (comando == 'E') {
            for (i = 0; i < CONTATTI; i++) {
                printf("  %d. %-10s %-8s %-12s %s\n", i + 1, rubrica[i].cognome, rubrica[i].nome,
                       rubrica[i].telefono, rubrica[i].ruolo);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        svuota_riga();                  /* un comando per riga */
    }

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
