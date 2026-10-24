/*
 * 070-problema-prenotazione-aule.c
 *
 * Aule informatiche: prenotazioni di una giornata
 *
 * L'istituto ha tre aule informatiche con un numero diverso di postazioni.
 * Per ogni aula si registra, ora per ora, la classe che l'ha prenotata
 * (stringa vuota se libera):
 *
 *     typedef struct {
 *         char nome[12];
 *         int postazioni;
 *         char prenotata[ORE][4];      prenotata[h] = classe dell'ora h + 1
 *     } Aula;
 *
 *     aule[a].prenotata[h]             la classe che ha l'aula a all'ora h
 *
 * Comandi:
 *     P aula ora classe studenti    prenota; rifiutata se l'aula è occupata
 *                                   o ha meno postazioni degli studenti
 *     L ora                         aule libere a quell'ora, con le postazioni
 *     T                             tabella della giornata
 *     Q                             fine
 * L'aula si indica con il suo numero (1-3), l'ora da 1 a 6.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define AULE 3
#define ORE  6

typedef struct {
    char nome[12];
    int postazioni;
    char prenotata[ORE][4];
} Aula;

void svuota_riga(void);

int main(void)
{
    Aula aule[AULE] = {
        {"Lab Alfa", 28, {"3A", "", "", "4B", "", ""}},
        {"Lab Beta", 24, {"", "5C", "5C", "", "", ""}},
        {"Lab Gamma", 16, {"", "", "", "", "", ""}}
    };
    char comando = ' ';
    char classe[4];
    int a;
    int ora;
    int studenti;
    int libere;

    while (comando != 'Q') {
        printf("Comando (P aula ora classe studenti, L ora, T, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'P') {
            if (scanf("%d %d %3s %d", &a, &ora, classe, &studenti) != 4 || a < 1 || a > AULE ||
                ora < 1 || ora > ORE || studenti <= 0) {
                printf("  Dati non validi.\n");
            } else if (aule[a - 1].prenotata[ora - 1][0] != '\0') {
                printf("  %s alla %da ora e' gia' della %s.\n", aule[a - 1].nome, ora,
                       aule[a - 1].prenotata[ora - 1]);
            } else if (studenti > aule[a - 1].postazioni) {
                printf("  %s ha solo %d postazioni.\n", aule[a - 1].nome, aule[a - 1].postazioni);
            } else {
                strcpy(aule[a - 1].prenotata[ora - 1], classe);
                printf("  Prenotato: %s, %da ora, %s.\n", aule[a - 1].nome, ora, classe);
            }
        } else if (comando == 'L') {
            if (scanf("%d", &ora) != 1 || ora < 1 || ora > ORE) {
                printf("  Ora non valida.\n");
            } else {
                libere = 0;
                for (a = 0; a < AULE; a++) {
                    if (aule[a].prenotata[ora - 1][0] == '\0') {
                        printf("  %s (%d postazioni)\n", aule[a].nome, aule[a].postazioni);
                        libere++;
                    }
                }
                printf("  Aule libere alla %da ora: %d\n", ora, libere);
            }
        } else if (comando == 'T') {
            printf("  %-10s", "Aula");
            for (ora = 1; ora <= ORE; ora++) {
                printf("  %da", ora);
            }
            printf("\n");
            for (a = 0; a < AULE; a++) {
                printf("  %-10s", aule[a].nome);
                for (ora = 0; ora < ORE; ora++) {
                    printf("  %-3s", aule[a].prenotata[ora][0] == '\0' ? "--" : aule[a].prenotata[ora]);
                }
                printf("\n");
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
