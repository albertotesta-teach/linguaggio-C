/*
 * 040-problema-ticket-assistenza.c
 *
 * Assistenza del laboratorio: i ticket dei guasti
 *
 * Il tecnico registra i guasti dei PC come ticket. Ogni ticket ha due
 * campi enum, la priorità e lo stato:
 *
 *     typedef enum { BASSA, MEDIA, ALTA, NUM_PRIORITA } Priorita;
 *     typedef enum { APERTO, IN_LAVORAZIONE, CHIUSO, NUM_STATI } Stato;
 *
 *     typedef struct {
 *         int numero;
 *         char pc[8];
 *         Priorita priorita;
 *         Stato stato;
 *     } Ticket;
 *
 * Non tutti i cambi di stato sono permessi. Una tabella dice quali:
 *
 *     int permesso[NUM_STATI][NUM_STATI];     [da][a]
 *
 *     APERTO -> IN_LAVORAZIONE         il tecnico lo prende in carico
 *     IN_LAVORAZIONE -> CHIUSO         guasto risolto
 *     IN_LAVORAZIONE -> APERTO         rimesso in coda (manca un pezzo)
 *     CHIUSO -> APERTO                 il guasto si ripresenta
 *
 * Comandi:
 *     N pc priorita      nuovo ticket; priorità B, M oppure A
 *     L n                prende in carico il ticket n
 *     C n                chiude il ticket n
 *     R n                riapre o rimette in coda il ticket n
 *     E                  ticket non chiusi, dalla priorità più alta
 *     Q                  fine
 */

#include <stdio.h>

#define MAX_TICKET 8

typedef enum {
    BASSA, MEDIA, ALTA, NUM_PRIORITA
} Priorita;

typedef enum {
    APERTO, IN_LAVORAZIONE, CHIUSO, NUM_STATI
} Stato;

typedef struct {
    int numero;
    char pc[8];
    Priorita priorita;
    Stato stato;
} Ticket;

int cambia_stato(Ticket *t, Stato nuovo);
const char *nome_stato(Stato s);
const char *nome_priorita(Priorita p);

int main(void)
{
    Ticket ticket[MAX_TICKET] = {
        {1, "PC-03", MEDIA, APERTO},
        {2, "PC-11", ALTA, IN_LAVORAZIONE},
        {3, "PC-07", BASSA, CHIUSO}
    };
    int n_ticket = 3;
    char comando = ' ';
    char lettera;
    int numero;
    Stato nuovo = APERTO;
    int p;
    int i;

    while (comando != 'Q') {
        printf("Comando (N pc B/M/A, L n, C n, R n, E, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'N') {
            if (n_ticket == MAX_TICKET) {
                printf("  Troppi ticket.\n");
                scanf("%*s %*s");
            } else if (scanf("%7s %c", ticket[n_ticket].pc, &lettera) != 2) {
                comando = 'Q';
            } else if (lettera != 'B' && lettera != 'M' && lettera != 'A') {
                printf("  Priorita' non valida.\n");
            } else {
                ticket[n_ticket].numero = n_ticket + 1;
                ticket[n_ticket].priorita = lettera == 'A' ? ALTA : (lettera == 'M' ? MEDIA : BASSA);
                ticket[n_ticket].stato = APERTO;
                printf("  Ticket %d aperto.\n", ticket[n_ticket].numero);
                n_ticket++;
            }
        } else if (comando == 'L' || comando == 'C' || comando == 'R') {
            if (scanf("%d", &numero) != 1) {
                comando = 'Q';
            } else if (numero < 1 || numero > n_ticket) {
                printf("  Ticket %d inesistente.\n", numero);
            } else {
                switch (comando) {
                case 'L':
                    nuovo = IN_LAVORAZIONE;
                    break;
                case 'C':
                    nuovo = CHIUSO;
                    break;
                case 'R':
                    nuovo = APERTO;
                    break;
                }
                if (cambia_stato(&ticket[numero - 1], nuovo)) {
                    printf("  Ticket %d: %s\n", numero, nome_stato(nuovo));
                } else {
                    printf("  Ticket %d: da %s a %s non e' permesso.\n", numero,
                           nome_stato(ticket[numero - 1].stato), nome_stato(nuovo));
                }
            }
        } else if (comando == 'E') {
            for (p = ALTA; p >= BASSA; p--) {
                for (i = 0; i < n_ticket; i++) {
                    if (ticket[i].priorita == (Priorita) p && ticket[i].stato != CHIUSO) {
                        printf("  %d  %-6s %-6s %s\n", ticket[i].numero, ticket[i].pc,
                               nome_priorita(ticket[i].priorita), nome_stato(ticket[i].stato));
                    }
                }
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}

/* Applica il cambio solo se la tabella lo permette. */
int cambia_stato(Ticket *t, Stato nuovo)
{
    int permesso[NUM_STATI][NUM_STATI] = {
        /*                  APERTO  IN_LAV.  CHIUSO */
        [APERTO] =         {0,      1,       0},
        [IN_LAVORAZIONE] = {1,      0,       1},
        [CHIUSO] =         {1,      0,       0}
    };
    int riuscito = permesso[t->stato][nuovo];

    if (riuscito) {
        t->stato = nuovo;
    }
    return riuscito;
}

const char *nome_stato(Stato s)
{
    const char *nomi[NUM_STATI] = {[APERTO] = "aperto", [IN_LAVORAZIONE] = "in lavorazione",
                                   [CHIUSO] = "chiuso"};

    return nomi[s];
}

const char *nome_priorita(Priorita p)
{
    const char *nomi[NUM_PRIORITA] = {[BASSA] = "bassa", [MEDIA] = "media", [ALTA] = "ALTA"};

    return nomi[p];
}
