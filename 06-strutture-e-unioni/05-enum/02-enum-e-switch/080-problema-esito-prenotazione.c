/*
 * 080-problema-esito-prenotazione.c
 *
 * Aula magna: una prenotazione può fallire per motivi diversi
 *
 * Le classi prenotano l'aula magna per un'ora, dal lunedì al venerdì,
 * dalla 1ª alla 6ª ora. L'aula ha 120 posti e una classe non può avere
 * più di una prenotazione nella stessa settimana. La funzione che
 * prenota restituisce un enum con l'esito, un valore per ogni motivo:
 *
 *     typedef enum {
 *         PRENOTATA, GIORNO_NON_VALIDO, ORA_NON_VALIDA, POSTI_INSUFFICIENTI,
 *         GIA_OCCUPATA, CLASSE_GIA_PRENOTATA
 *     } Esito;
 *
 *     Esito prenota(char aula[GIORNI][ORE][4], const char *classe,
 *                   int studenti, int giorno, int ora);
 *     const char *messaggio(Esito e);
 *
 * Il main non deve sapere come si controllano le regole: stampa il
 * messaggio dell'esito con uno switch. aula[g][o] contiene la classe che
 * ha prenotato, oppure "" se l'ora è libera.
 *
 * Il programma legge "classe studenti giorno ora" (giorno da 1 a 5, ora
 * da 1 a 6) fino a FINE, poi stampa il calendario della settimana.
 */

#include <stdio.h>
#include <string.h>

#define GIORNI 5
#define ORE 6
#define POSTI 120

typedef enum {
    PRENOTATA, GIORNO_NON_VALIDO, ORA_NON_VALIDA, POSTI_INSUFFICIENTI, GIA_OCCUPATA,
    CLASSE_GIA_PRENOTATA
} Esito;

Esito prenota(char aula[GIORNI][ORE][4], const char *classe, int studenti, int giorno, int ora);
const char *messaggio(Esito e);

int main(void)
{
    char aula[GIORNI][ORE][4] = {{""}};
    const char *giorni[GIORNI] = {"lun", "mar", "mer", "gio", "ven"};
    char classe[8];
    int studenti;
    int giorno;
    int ora;
    int finito = 0;
    int g;
    int o;

    while (!finito) {
        printf("Prenotazione (classe studenti giorno ora, FINE): ");
        if (scanf("%7s", classe) != 1 || strcmp(classe, "FINE") == 0) {
            finito = 1;
        } else if (scanf("%d %d %d", &studenti, &giorno, &ora) != 3) {
            printf("  Richiesta non valida.\n");
            finito = 1;
        } else if (strlen(classe) > 3) {
            printf("  Classe %s non valida.\n", classe);
        } else {
            printf("  %s\n", messaggio(prenota(aula, classe, studenti, giorno, ora)));
        }
    }

    printf("\n     ");
    for (g = 0; g < GIORNI; g++) {
        printf(" %-4s", giorni[g]);
    }
    printf("\n");
    for (o = 0; o < ORE; o++) {
        printf("  %da ", o + 1);
        for (g = 0; g < GIORNI; g++) {
            printf(" %-4s", aula[g][o][0] == '\0' ? "-" : aula[g][o]);
        }
        printf("\n");
    }

    return 0;
}

/* Controlla le regole nell'ordine e registra la prenotazione. */
Esito prenota(char aula[GIORNI][ORE][4], const char *classe, int studenti, int giorno, int ora)
{
    Esito esito = PRENOTATA;
    int g;
    int o;

    if (giorno < 1 || giorno > GIORNI) {
        esito = GIORNO_NON_VALIDO;
    } else if (ora < 1 || ora > ORE) {
        esito = ORA_NON_VALIDA;
    } else if (studenti > POSTI) {
        esito = POSTI_INSUFFICIENTI;
    } else if (aula[giorno - 1][ora - 1][0] != '\0') {
        esito = GIA_OCCUPATA;
    } else {
        for (g = 0; g < GIORNI; g++) {
            for (o = 0; o < ORE; o++) {
                if (strcmp(aula[g][o], classe) == 0) {
                    esito = CLASSE_GIA_PRENOTATA;
                }
            }
        }
        if (esito == PRENOTATA) {
            strcpy(aula[giorno - 1][ora - 1], classe);
        }
    }
    return esito;
}

const char *messaggio(Esito e)
{
    const char *testo = "";

    switch (e) {
    case PRENOTATA:
        testo = "Prenotazione registrata.";
        break;
    case GIORNO_NON_VALIDO:
        testo = "Giorno non valido: da 1 (lunedi') a 5 (venerdi').";
        break;
    case ORA_NON_VALIDA:
        testo = "Ora non valida: dalla 1a alla 6a.";
        break;
    case POSTI_INSUFFICIENTI:
        testo = "L'aula magna ha solo 120 posti.";
        break;
    case GIA_OCCUPATA:
        testo = "Ora gia' occupata da un'altra classe.";
        break;
    case CLASSE_GIA_PRENOTATA:
        testo = "La classe ha gia' una prenotazione questa settimana.";
        break;
    }
    return testo;
}
