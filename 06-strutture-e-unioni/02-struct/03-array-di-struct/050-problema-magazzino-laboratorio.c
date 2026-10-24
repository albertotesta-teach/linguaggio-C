/*
 * 050-problema-magazzino-laboratorio.c
 *
 * Laboratorio di elettronica: carico, prelievo e articoli sottoscorta
 *
 * Il tecnico di laboratorio gestisce il magazzino dei componenti. Per ogni
 * articolo conosce codice, descrizione, quantità presente e scorta minima
 * (sotto la quale bisogna riordinare):
 *
 *     typedef struct {
 *         char codice[8];
 *         char descrizione[28];
 *         int quantita;
 *         int scorta_minima;
 *     } Articolo;
 *
 * Comandi:
 *     P codice n    prelievo di n pezzi (rifiutato se non ci sono)
 *     C codice n    carico di n pezzi
 *     S             articoli sottoscorta, con quanti pezzi ordinare per
 *                   tornare al doppio della scorta minima
 *     Q             fine
 * Il codice si cerca nell'array con strcmp; un codice sconosciuto viene
 * segnalato. Dopo un prelievo che porta l'articolo sotto la scorta minima
 * compare un avviso.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ARTICOLI 6

typedef struct {
    char codice[8];
    char descrizione[28];
    int quantita;
    int scorta_minima;
} Articolo;

void svuota_riga(void);

int main(void)
{
    Articolo magazzino[ARTICOLI] = {
        {"R220", "Resistenza 220 ohm", 180, 50},
        {"LED-R", "LED rosso 5 mm", 64, 40},
        {"LED-V", "LED verde 5 mm", 35, 40},
        {"C100U", "Condensatore 100 uF", 22, 20},
        {"BB400", "Breadboard 400 punti", 9, 10},
        {"ARDU", "Scheda Arduino Uno", 12, 8}
    };
    char comando = ' ';
    char codice[8];
    int pezzi;
    int a;
    int sottoscorta;

    while (comando != 'Q') {
        printf("Comando (P codice n, C codice n, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'P' || comando == 'C') {
            if (scanf("%7s %d", codice, &pezzi) != 2 || pezzi <= 0) {
                printf("  Dati non validi.\n");
            } else {
                a = 0;
                while (a < ARTICOLI && strcmp(magazzino[a].codice, codice) != 0) {
                    a++;
                }
                if (a == ARTICOLI) {
                    printf("  Codice %s sconosciuto.\n", codice);
                } else if (comando == 'C') {
                    magazzino[a].quantita = magazzino[a].quantita + pezzi;
                    printf("  %s: ora %d pezzi.\n", magazzino[a].descrizione, magazzino[a].quantita);
                } else if (pezzi > magazzino[a].quantita) {
                    printf("  %s: disponibili solo %d pezzi.\n", magazzino[a].descrizione,
                           magazzino[a].quantita);
                } else {
                    magazzino[a].quantita = magazzino[a].quantita - pezzi;
                    printf("  %s: ora %d pezzi.\n", magazzino[a].descrizione, magazzino[a].quantita);
                    if (magazzino[a].quantita < magazzino[a].scorta_minima) {
                        printf("  Attenzione: sotto la scorta minima (%d).\n",
                               magazzino[a].scorta_minima);
                    }
                }
            }
        } else if (comando == 'S') {
            sottoscorta = 0;
            for (a = 0; a < ARTICOLI; a++) {
                if (magazzino[a].quantita < magazzino[a].scorta_minima) {
                    printf("  %-6s %-22s %3d (minimo %d): ordinare %d\n", magazzino[a].codice,
                           magazzino[a].descrizione, magazzino[a].quantita, magazzino[a].scorta_minima,
                           2 * magazzino[a].scorta_minima - magazzino[a].quantita);
                    sottoscorta++;
                }
            }
            printf("  Articoli sottoscorta: %d\n", sottoscorta);
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
