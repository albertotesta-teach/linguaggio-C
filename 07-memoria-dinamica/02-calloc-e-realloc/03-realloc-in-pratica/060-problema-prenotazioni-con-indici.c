/*
 * 060-problema-prenotazioni-con-indici.c
 *
 * Il laboratorio di informatica: postazioni che aumentano e prenotazioni
 *
 * Il laboratorio ha un certo numero di postazioni, e durante l'anno ne
 * arrivano di nuove: il blocco delle postazioni si ingrandisce con
 * realloc. Gli studenti prenotano una postazione per il pomeriggio.
 *
 *     typedef struct {
 *         char codice[16];           PC-01, PC-02, ...
 *         int funzionante;
 *     } Postazione;
 *
 *     typedef struct {
 *         char studente[20];
 *         int postazione;            INDICE nel blocco delle postazioni
 *     } Prenotazione;
 *
 * La prenotazione ricorda la postazione con il suo indice, non con un
 * puntatore: quando il blocco delle postazioni si sposta per una
 * realloc, un puntatore diventerebbe pendente, l'indice no.
 *
 * Anche l'elenco delle prenotazioni cresce di un elemento alla volta
 * (partendo da NULL).
 *
 * Comandi:
 *     N k                  arrivano k postazioni nuove
 *     G numero             la postazione si guasta: le sue prenotazioni
 *                          passano alla prima postazione libera
 *     P studente           prenota la prima postazione funzionante libera
 *     E                    elenco delle prenotazioni
 *     Q                    fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POSTAZIONI 40

typedef struct {
    char codice[16];
    int funzionante;
} Postazione;

typedef struct {
    char studente[20];
    int postazione;
} Prenotazione;

int nuove_postazioni(Postazione **pc, int *n_pc, int k);
int libera(const Postazione pc[], int n_pc, const Prenotazione pren[], int n_pren);

int main(void)
{
    Postazione *pc = NULL;
    Prenotazione *pren = NULL;
    Prenotazione *tmp;
    int n_pc = 0;
    int n_pren = 0;
    int k;
    int i;
    int scelta;
    char studente[20];
    char comando = ' ';

    printf("Postazioni iniziali: ");
    if (scanf("%d", &k) != 1 || k < 1 || k > MAX_POSTAZIONI || !nuove_postazioni(&pc, &n_pc, k)) {
        printf("Numero non valido o memoria insufficiente.\n");
        comando = 'Q';
    }

    while (comando != 'Q') {
        printf("Comando (N, G, P, E, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'N') {
            if (scanf("%d", &k) != 1 || k < 1 || n_pc + k > MAX_POSTAZIONI) {
                printf("  Numero non valido.\n");
            } else if (!nuove_postazioni(&pc, &n_pc, k)) {
                printf("  Memoria insufficiente.\n");
            } else {
                printf("  postazioni: %d (blocco in %p)\n", n_pc, (void *) pc);
            }
        } else if (comando == 'G') {
            if (scanf("%d", &k) != 1 || k < 1 || k > n_pc || !pc[k - 1].funzionante) {
                printf("  Postazione non valida.\n");
            } else {
                pc[k - 1].funzionante = 0;
                printf("  %s guasta\n", pc[k - 1].codice);
                for (i = 0; i < n_pren; i++) {
                    if (pren[i].postazione == k - 1) {
                        scelta = libera(pc, n_pc, pren, n_pren);
                        pren[i].postazione = scelta;
                        if (scelta == -1) {
                            printf("  %s resta senza postazione\n", pren[i].studente);
                        } else {
                            printf("  prenotazione di %s spostata su %s\n", pren[i].studente,
                                   pc[scelta].codice);
                        }
                    }
                }
            }
        } else if (comando == 'P') {
            scelta = libera(pc, n_pc, pren, n_pren);
            if (scanf("%19s", studente) != 1) {
                printf("  Nome mancante.\n");
            } else if (scelta == -1) {
                printf("  Nessuna postazione libera.\n");
            } else {
                tmp = realloc(pren, (n_pren + 1) * sizeof *tmp);
                if (tmp == NULL) {
                    printf("  Memoria insufficiente.\n");
                } else {
                    pren = tmp;
                    strcpy(pren[n_pren].studente, studente);
                    pren[n_pren].postazione = scelta;
                    n_pren++;
                    printf("  %s: %s\n", studente, pc[scelta].codice);
                }
            }
        } else if (comando == 'E') {
            for (i = 0; i < n_pren; i++) {
                printf("  %-10s %s\n", pren[i].studente,
                       pren[i].postazione == -1 ? "(nessuna)" : pc[pren[i].postazione].codice);
            }
            printf("  postazioni: %d, prenotazioni: %d\n", n_pc, n_pren);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q' && comando != 'E') {
            scanf("%*[^\n]");
        }
    }

    free(pc);
    free(pren);

    return 0;
}

/* Allunga il blocco di k postazioni funzionanti; 0 se realloc fallisce. */
int nuove_postazioni(Postazione **pc, int *n_pc, int k)
{
    Postazione *tmp = realloc(*pc, (*n_pc + k) * sizeof *tmp);
    int i;

    if (tmp != NULL) {
        for (i = *n_pc; i < *n_pc + k; i++) {
            snprintf(tmp[i].codice, sizeof tmp[i].codice, "PC-%02d", i + 1);
            tmp[i].funzionante = 1;
        }
        *pc = tmp;
        *n_pc = *n_pc + k;
    }
    return tmp != NULL;
}

/* Indice della prima postazione funzionante non prenotata, -1 se non c'è. */
int libera(const Postazione pc[], int n_pc, const Prenotazione pren[], int n_pren)
{
    int trovata = -1;
    int occupata;
    int i;
    int j;

    for (i = 0; i < n_pc && trovata == -1; i++) {
        occupata = !pc[i].funzionante;
        for (j = 0; j < n_pren && !occupata; j++) {
            occupata = pren[j].postazione == i;
        }
        if (!occupata) {
            trovata = i;
        }
    }
    return trovata;
}
