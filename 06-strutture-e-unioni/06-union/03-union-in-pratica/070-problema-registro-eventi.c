/*
 * 070-problema-registro-eventi.c
 *
 * Il sistema di sicurezza della scuola: un registro di eventi diversi
 *
 * La centrale registra tre tipi di evento, ognuno con i suoi dati:
 *   - PORTA: quale porta, aperta o chiusa;
 *   - SENSORE: quale sensore e il valore misurato (temperatura in gradi);
 *   - BADGE: numero del badge e nome, oppure nome vuoto per un badge non
 *     registrato.
 *
 *     typedef struct {
 *         Orario ora;
 *         TipoEvento tipo;
 *         union {
 *             struct {
 *                 char nome[12];
 *                 int aperta;
 *             } porta;
 *             struct {
 *                 char nome[12];
 *                 double valore;
 *             } sensore;
 *             struct {
 *                 int numero;
 *                 char titolare[16];
 *             } badge;
 *         };
 *     } Evento;
 *
 * Comandi:
 *     T tipo     eventi di un tipo (PORTA, SENSORE o BADGE)
 *     A          anomalie: porta aperta fuori orario (prima delle 7:00
 *                o dalle 19:00), temperatura sopra 30 gradi, badge non
 *                registrato
 *     Q          fine
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define EVENTI 8
#define APERTURA (7 * 60)
#define CHIUSURA (19 * 60)
#define TEMPERATURA_MASSIMA 30.0

typedef struct {
    int ore;
    int minuti;
} Orario;

typedef enum {
    PORTA, SENSORE, BADGE, NUM_TIPI, TIPO_NON_VALIDO
} TipoEvento;

typedef struct {
    Orario ora;
    TipoEvento tipo;
    union {
        struct {
            char nome[12];
            int aperta;
        } porta;
        struct {
            char nome[12];
            double valore;
        } sensore;
        struct {
            int numero;
            char titolare[16];
        } badge;
    };
} Evento;

TipoEvento tipo_da_testo(const char *parola);
int anomalo(const Evento *e);
void stampa(const Evento *e);
void svuota_riga(void);

int main(void)
{
    Evento registro[EVENTI] = {
        {{6, 40}, PORTA, .porta = {"ingresso", 1}},
        {{6, 42}, BADGE, .badge = {1047, "Ferri (bidello)"}},
        {{7, 55}, BADGE, .badge = {2210, "prof. Galli"}},
        {{10, 15}, SENSORE, .sensore = {"lab-chimica", 24.5}},
        {{13, 30}, SENSORE, .sensore = {"server", 31.2}},
        {{14, 5}, BADGE, .badge = {9999, ""}},
        {{18, 30}, PORTA, .porta = {"palestra", 0}},
        {{21, 10}, PORTA, .porta = {"magazzino", 1}}
    };
    char comando = ' ';
    char parola[12];
    TipoEvento tipo;
    int trovati;
    int i;

    while (comando != 'Q') {
        printf("Comando (T tipo, A, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'T') {
            if (scanf("%11s", parola) != 1) {
                printf("  Manca il tipo.\n");
            } else {
                tipo = tipo_da_testo(parola);
                if (tipo == TIPO_NON_VALIDO) {
                    printf("  Tipo sconosciuto: PORTA, SENSORE o BADGE.\n");
                } else {
                    for (i = 0; i < EVENTI; i++) {
                        if (registro[i].tipo == tipo) {
                            stampa(&registro[i]);
                        }
                    }
                }
            }
        } else if (comando == 'A') {
            trovati = 0;
            for (i = 0; i < EVENTI; i++) {
                if (anomalo(&registro[i])) {
                    stampa(&registro[i]);
                    trovati++;
                }
            }
            printf("  Anomalie: %d\n", trovati);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        svuota_riga();                  /* un comando per riga */
    }

    return 0;
}

TipoEvento tipo_da_testo(const char *parola)
{
    const char *nomi[NUM_TIPI] = {[PORTA] = "PORTA", [SENSORE] = "SENSORE", [BADGE] = "BADGE"};
    TipoEvento trovato = TIPO_NON_VALIDO;
    TipoEvento t;

    for (t = PORTA; t < NUM_TIPI; t++) {
        if (strcmp(nomi[t], parola) == 0) {
            trovato = t;
        }
    }
    return trovato;
}

/* Ogni tipo ha la sua regola. */
int anomalo(const Evento *e)
{
    int minuti = e->ora.ore * 60 + e->ora.minuti;
    int risultato = 0;

    switch (e->tipo) {
    case PORTA:
        risultato = e->porta.aperta && (minuti < APERTURA || minuti >= CHIUSURA);
        break;
    case SENSORE:
        risultato = e->sensore.valore > TEMPERATURA_MASSIMA;
        break;
    case BADGE:
        risultato = e->badge.titolare[0] == '\0';
        break;
    case NUM_TIPI:
    case TIPO_NON_VALIDO:
        break;
    }
    return risultato;
}

void stampa(const Evento *e)
{
    printf("  %02d:%02d  ", e->ora.ore, e->ora.minuti);
    switch (e->tipo) {
    case PORTA:
        printf("porta %-12s %s\n", e->porta.nome, e->porta.aperta ? "aperta" : "chiusa");
        break;
    case SENSORE:
        printf("sensore %-10s %.1f gradi\n", e->sensore.nome, e->sensore.valore);
        break;
    case BADGE:
        printf("badge %-12d %s\n", e->badge.numero,
               e->badge.titolare[0] == '\0' ? "NON REGISTRATO" : e->badge.titolare);
        break;
    case NUM_TIPI:
    case TIPO_NON_VALIDO:
        break;
    }
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
