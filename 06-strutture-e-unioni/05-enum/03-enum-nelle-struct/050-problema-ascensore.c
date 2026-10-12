/*
 * 050-problema-ascensore.c
 *
 * L'ascensore della scuola come macchina a stati
 *
 * L'ascensore serve il piano terra e tre piani (da 0 a 3). In ogni
 * istante è in uno stato:
 *
 *     typedef enum {
 *         PORTE_APERTE, PORTE_CHIUSE, IN_SALITA, IN_DISCESA
 *     } Stato;
 *
 *     typedef struct {
 *         int piano;
 *         int destinazione;
 *         Stato stato;
 *     } Ascensore;
 *
 * La funzione passo fa avanzare l'ascensore di un passo con uno switch
 * sullo stato:
 *   - PORTE_APERTE: se la destinazione è un altro piano chiude le porte;
 *   - PORTE_CHIUSE: sale, scende oppure, se è già al piano, apre;
 *   - IN_SALITA / IN_DISCESA: si sposta di un piano; arrivato alla
 *     destinazione apre le porte.
 *
 * Il programma legge le chiamate (il piano, -1 per finire) e per ognuna
 * stampa tutti i passi fino all'apertura delle porte al piano chiamato.
 */

#include <stdio.h>

#define PIANI 4

typedef enum {
    PORTE_APERTE, PORTE_CHIUSE, IN_SALITA, IN_DISCESA
} Stato;

typedef struct {
    int piano;
    int destinazione;
    Stato stato;
} Ascensore;

void passo(Ascensore *a);
const char *nome(Stato s);

int main(void)
{
    Ascensore ascensore = {0, 0, PORTE_APERTE};
    int chiamata = 0;
    int passi;

    while (chiamata != -1) {
        printf("Chiamata al piano (0-3, -1 per finire): ");
        if (scanf("%d", &chiamata) != 1) {
            chiamata = -1;
        } else if (chiamata != -1 && (chiamata < 0 || chiamata >= PIANI)) {
            printf("  Il piano %d non esiste.\n", chiamata);
        } else if (chiamata != -1) {
            ascensore.destinazione = chiamata;
            passi = 0;
            if (ascensore.piano == chiamata && ascensore.stato == PORTE_APERTE) {
                printf("  Gia' al piano %d con le porte aperte.\n", chiamata);
            }
            while (ascensore.piano != ascensore.destinazione || ascensore.stato != PORTE_APERTE) {
                passo(&ascensore);
                passi++;
                printf("  piano %d  %s\n", ascensore.piano, nome(ascensore.stato));
            }
            if (passi > 0) {
                printf("  Arrivato in %d passi.\n", passi);
            }
        }
    }

    return 0;
}

void passo(Ascensore *a)
{
    switch (a->stato) {
    case PORTE_APERTE:
        if (a->destinazione != a->piano) {
            a->stato = PORTE_CHIUSE;
        }
        break;
    case PORTE_CHIUSE:
        if (a->destinazione > a->piano) {
            a->stato = IN_SALITA;
        } else if (a->destinazione < a->piano) {
            a->stato = IN_DISCESA;
        } else {
            a->stato = PORTE_APERTE;
        }
        break;
    case IN_SALITA:
        a->piano++;
        if (a->piano == a->destinazione) {
            a->stato = PORTE_APERTE;
        }
        break;
    case IN_DISCESA:
        a->piano--;
        if (a->piano == a->destinazione) {
            a->stato = PORTE_APERTE;
        }
        break;
    }
}

const char *nome(Stato s)
{
    const char *testo = "";

    switch (s) {
    case PORTE_APERTE:
        testo = "porte aperte";
        break;
    case PORTE_CHIUSE:
        testo = "porte chiuse";
        break;
    case IN_SALITA:
        testo = "in salita";
        break;
    case IN_DISCESA:
        testo = "in discesa";
        break;
    }
    return testo;
}
