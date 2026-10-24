/*
 * 050-problema-comandi-robot.c
 *
 * Il robot del laboratorio: un programma di comandi letti da testo
 *
 * Il robot esegue un programma scritto a righe. Ogni comando ha dati
 * diversi:
 *     MUOVI dx dy      spostamento sulla griglia
 *     RUOTA gradi      multipli di 90, positivi in senso antiorario
 *     DI testo         frase da pronunciare (fino a 31 caratteri)
 *
 *     typedef struct {
 *         TipoComando tipo;
 *         union {
 *             struct {
 *                 int dx;
 *                 int dy;
 *             } muovi;
 *             int gradi;
 *             char testo[32];
 *         };
 *     } Comando;
 *
 * Il programma lavora in due fasi:
 *   1. analisi: legge le righe fino a FINE e le trasforma in Comando,
 *      segnalando quelle sbagliate (che non entrano nel programma);
 *   2. esecuzione: per ogni comando, uno switch sull'etichetta aggiorna
 *      posizione e orientamento del robot e stampa cosa fa.
 */

#include <stdio.h>
#include <string.h>

#define MAX_COMANDI 10
#define LUNG 64

typedef enum {
    MUOVI, RUOTA, DI
} TipoComando;

typedef struct {
    TipoComando tipo;
    union {
        struct {
            int dx;
            int dy;
        } muovi;
        int gradi;
        char testo[32];
    };
} Comando;

int analizza(const char *riga, Comando *c);

int main(void)
{
    Comando programma[MAX_COMANDI];
    char riga[LUNG];
    int n = 0;
    int numero_riga = 0;
    int finito = 0;
    int resto;
    int x = 0;
    int y = 0;
    int direzione = 0;
    int i;

    printf("Programma del robot (FINE per eseguire):\n");
    while (!finito && n < MAX_COMANDI) {
        if (fgets(riga, LUNG, stdin) == NULL) {
            finito = 1;
        } else {
            if (strchr(riga, '\n') == NULL) {
                resto = getchar();      /* riga troppo lunga: scarta il resto */
                while (resto != '\n' && resto != EOF) {
                    resto = getchar();
                }
            }
            riga[strcspn(riga, "\n")] = '\0';
            numero_riga++;
            if (strcmp(riga, "FINE") == 0) {
                finito = 1;
            } else if (analizza(riga, &programma[n])) {
                n++;
            } else {
                printf("  riga %d scartata: \"%s\"\n", numero_riga, riga);
            }
        }
    }

    printf("\nEsecuzione di %d comandi\n", n);
    for (i = 0; i < n; i++) {
        switch (programma[i].tipo) {
        case MUOVI:
            x = x + programma[i].muovi.dx;
            y = y + programma[i].muovi.dy;
            printf("  muove di (%d, %d): ora in (%d, %d)\n", programma[i].muovi.dx,
                   programma[i].muovi.dy, x, y);
            break;
        case RUOTA:
            direzione = ((direzione + programma[i].gradi) % 360 + 360) % 360;
            printf("  ruota di %d gradi: ora orientato a %d gradi\n", programma[i].gradi,
                   direzione);
            break;
        case DI:
            printf("  dice: \"%s\"\n", programma[i].testo);
            break;
        }
    }
    printf("Posizione finale (%d, %d), orientamento %d gradi\n", x, y, direzione);

    return 0;
}

/* Trasforma una riga in un Comando; 0 se la riga non è valida. */
int analizza(const char *riga, Comando *c)
{
    char parola[8];
    int letti;
    int ok = 0;

    if (sscanf(riga, "%7s", parola) == 1) {
        if (strcmp(parola, "MUOVI") == 0) {
            c->tipo = MUOVI;
            ok = sscanf(riga, "%*s %d %d", &c->muovi.dx, &c->muovi.dy) == 2;
        } else if (strcmp(parola, "RUOTA") == 0) {
            c->tipo = RUOTA;
            letti = sscanf(riga, "%*s %d", &c->gradi);
            ok = letti == 1 && c->gradi % 90 == 0;
        } else if (strcmp(parola, "DI") == 0 && strlen(riga) > 3 &&
                   strlen(riga + 3) < sizeof(c->testo)) {
            c->tipo = DI;
            strcpy(c->testo, riga + 3);
            ok = 1;
        }
    }
    return ok;
}
