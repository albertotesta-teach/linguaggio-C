/*
 * 050-problema-anagrafica-studenti.c
 *
 * Segreteria: dove abitano gli studenti
 *
 * La segreteria organizza i pulmini per le uscite e deve sapere dove
 * abitano gli studenti. L'indirizzo è una struct dentro lo studente:
 *
 *     typedef struct {
 *         char via[28];
 *         char cap[6];
 *         char comune[16];
 *         char provincia[3];
 *     } Indirizzo;
 *
 *     typedef struct {
 *         char nome[20];
 *         char classe[4];
 *         Indirizzo residenza;
 *     } Studente;
 *
 * Comandi (uno per riga):
 *     C comune      studenti che abitano nel comune
 *     Z cap         studenti con quel CAP
 *     P             quanti studenti per provincia
 *     Q             fine
 *
 * Il nome del comune può contenere spazi ("Novi Ligure"): per questo si
 * legge una riga intera con fgets e l'argomento è il testo dopo la
 * lettera del comando.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STUDENTI 7
#define LUNG 40

typedef struct {
    char via[28];
    char cap[6];
    char comune[16];
    char provincia[3];
} Indirizzo;

typedef struct {
    char nome[20];
    char classe[4];
    Indirizzo residenza;
} Studente;

int main(void)
{
    Studente elenco[STUDENTI] = {
        {"Rossi Elena", "2A", {"via Marengo 12", "15121", "Alessandria", "AL"}},
        {"Greco Paolo", "2A", {"corso Italia 4", "15067", "Novi Ligure", "AL"}},
        {"Costa Marta", "3B", {"via Torino 31", "15121", "Alessandria", "AL"}},
        {"Villa Sara", "3B", {"piazza Duomo 2", "14100", "Asti", "AT"}},
        {"Neri Luca", "4C", {"via Roma 77", "15076", "Ovada", "AL"}},
        {"Fabbri Ivo", "4C", {"via Novi 5", "15067", "Novi Ligure", "AL"}},
        {"Conte Mattia", "5A", {"corso Savona 9", "14100", "Asti", "AT"}}
    };
    char province[STUDENTI][3];
    int conteggi[STUDENTI];
    int n_province;
    char riga[LUNG];
    char comando = ' ';
    char *argomento;
    int trovati;
    int i;
    int p;
    int resto;

    while (comando != 'Q') {
        printf("Comando (C comune, Z cap, P, Q): ");
        if (fgets(riga, LUNG, stdin) == NULL) {
            comando = 'Q';
        } else {
            if (strchr(riga, '\n') == NULL) {
                resto = getchar();      /* riga troppo lunga: scarta il resto */
                while (resto != '\n' && resto != EOF) {
                    resto = getchar();
                }
            }
            riga[strcspn(riga, "\n")] = '\0';
            comando = (char) toupper((unsigned char) riga[0]);
            argomento = riga + 2;
            if ((comando == 'C' || comando == 'Z') && strlen(riga) < 3) {
                printf("  Manca il comune o il CAP.\n");
            } else if (comando == 'C' || comando == 'Z') {
                trovati = 0;
                for (i = 0; i < STUDENTI; i++) {
                    if ((comando == 'C' && strcmp(elenco[i].residenza.comune, argomento) == 0) ||
                        (comando == 'Z' && strcmp(elenco[i].residenza.cap, argomento) == 0)) {
                        printf("  %-12s %s  %s, %s %s (%s)\n", elenco[i].nome, elenco[i].classe,
                               elenco[i].residenza.via, elenco[i].residenza.cap,
                               elenco[i].residenza.comune, elenco[i].residenza.provincia);
                        trovati++;
                    }
                }
                printf("  Trovati: %d\n", trovati);
            } else if (comando == 'P') {
                n_province = 0;
                for (i = 0; i < STUDENTI; i++) {
                    p = 0;
                    while (p < n_province && strcmp(province[p], elenco[i].residenza.provincia) != 0) {
                        p++;
                    }
                    if (p == n_province) {
                        strcpy(province[p], elenco[i].residenza.provincia);
                        conteggi[p] = 0;
                        n_province++;
                    }
                    conteggi[p]++;
                }
                for (p = 0; p < n_province; p++) {
                    printf("  %s: %d studenti\n", province[p], conteggi[p]);
                }
            } else if (comando != 'Q') {
                printf("  Comando sconosciuto.\n");
            }
        }
    }

    return 0;
}
