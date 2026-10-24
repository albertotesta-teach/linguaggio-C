/*
 * 060-problema-itinerario-gita.c
 *
 * Gita in Liguria: l'itinerario della giornata, tappa per tappa
 *
 * Il docente organizzatore scrive l'itinerario: per ogni tappa il luogo,
 * l'orario di arrivo e quello di partenza.
 *
 *     typedef struct {
 *         char luogo[16];
 *         Orario arrivo;
 *         Orario partenza;
 *     } Tappa;
 *
 *     typedef struct {
 *         char meta[16];
 *         Tappa tappe[MAX_TAPPE];
 *         int n_tappe;
 *     } Gita;
 *
 *     g.tappe[i].partenza.minuti     tre livelli: array, struct, struct
 *
 * Il programma legge le tappe nella forma "luogo hh:mm hh:mm" fino a
 * FINE. aggiungi_tappa accetta una tappa solo se:
 *   - gli orari esistono e la partenza non viene prima dell'arrivo;
 *   - l'arrivo viene dopo la partenza dalla tappa precedente;
 *   - c'è ancora posto nell'array.
 * Alla fine stampa il programma della giornata con le soste, i tempi di
 * viaggio tra una tappa e l'altra e i totali.
 */

#include <stdio.h>
#include <string.h>

#define MAX_TAPPE 6
#define LUNG 16

typedef struct {
    int ore;
    int minuti;
} Orario;

typedef struct {
    char luogo[LUNG];
    Orario arrivo;
    Orario partenza;
} Tappa;

typedef struct {
    char meta[LUNG];
    Tappa tappe[MAX_TAPPE];
    int n_tappe;
} Gita;

int in_minuti(Orario o);
int orario_valido(Orario o);
int aggiungi_tappa(Gita *g, const Tappa *t);
void stampa_gita(const Gita *g);
void svuota_riga(void);

int main(void)
{
    Gita gita = {"Cinque Terre", {{"", {0, 0}, {0, 0}}}, 0};
    Tappa nuova;
    int esito;
    int finito = 0;
    const char *messaggi[4] = {"aggiunta", "orari non validi",
                               "arrivo prima della partenza dalla tappa precedente",
                               "itinerario pieno"};

    while (!finito) {
        printf("Tappa (luogo hh:mm hh:mm, FINE): ");
        if (scanf("%15s", nuova.luogo) != 1 || strcmp(nuova.luogo, "FINE") == 0) {
            finito = 1;
        } else if (scanf("%d:%d %d:%d", &nuova.arrivo.ore, &nuova.arrivo.minuti,
                         &nuova.partenza.ore, &nuova.partenza.minuti) != 4) {
            printf("  Tappa non valida.\n");
        } else {
            esito = aggiungi_tappa(&gita, &nuova);
            printf("  %s: %s\n", nuova.luogo, messaggi[esito]);
        }
        if (!finito) {
            svuota_riga();              /* una tappa per riga */
        }
    }

    stampa_gita(&gita);

    return 0;
}

int in_minuti(Orario o)
{
    return o.ore * 60 + o.minuti;
}

int orario_valido(Orario o)
{
    return o.ore >= 0 && o.ore < 24 && o.minuti >= 0 && o.minuti < 60;
}

/* 0 aggiunta, 1 orari non validi, 2 arrivo troppo presto, 3 piena. */
int aggiungi_tappa(Gita *g, const Tappa *t)
{
    int esito = 0;

    if (!orario_valido(t->arrivo) || !orario_valido(t->partenza) ||
        in_minuti(t->partenza) < in_minuti(t->arrivo)) {
        esito = 1;
    } else if (g->n_tappe > 0 &&
               in_minuti(t->arrivo) <= in_minuti(g->tappe[g->n_tappe - 1].partenza)) {
        esito = 2;
    } else if (g->n_tappe == MAX_TAPPE) {
        esito = 3;
    } else {
        g->tappe[g->n_tappe] = *t;
        g->n_tappe++;
    }
    return esito;
}

void stampa_gita(const Gita *g)
{
    int viaggio = 0;
    int soste = 0;
    int tratto;
    int sosta;
    int i;

    printf("\nGita: %s\n", g->meta);
    for (i = 0; i < g->n_tappe; i++) {
        if (i > 0) {
            tratto = in_minuti(g->tappe[i].arrivo) - in_minuti(g->tappe[i - 1].partenza);
            printf("        viaggio %d min\n", tratto);
            viaggio = viaggio + tratto;
        }
        sosta = in_minuti(g->tappe[i].partenza) - in_minuti(g->tappe[i].arrivo);
        printf("  %02d:%02d-%02d:%02d  %-14s sosta %d min\n", g->tappe[i].arrivo.ore,
               g->tappe[i].arrivo.minuti, g->tappe[i].partenza.ore, g->tappe[i].partenza.minuti,
               g->tappe[i].luogo, sosta);
        soste = soste + sosta;
    }
    printf("Tappe %d, in viaggio %d h %02d min, in sosta %d h %02d min\n", g->n_tappe,
           viaggio / 60, viaggio % 60, soste / 60, soste % 60);
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
