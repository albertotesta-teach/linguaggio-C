/*
 * 080-problema-ricerca-puntatore.c
 *
 * Laboratorio di informatica: trovare e modificare il PC di una postazione
 *
 * L'inventario del laboratorio ha una scheda per ogni computer. Il tecnico
 * cerca un computer per numero di inventario e registra un intervento.
 *
 *     typedef struct {
 *         char inventario[8];      "PC-014"
 *         int postazione;
 *         int ram_gb;
 *         int guasti;
 *         int funzionante;
 *     } Computer;
 *
 *     Computer *cerca(Computer elenco[], int n, const char *inventario);
 *
 * cerca restituisce l'INDIRIZZO della scheda trovata, oppure NULL se il
 * numero non esiste. Con il puntatore restituito il chiamante legge e
 * modifica direttamente l'elemento dell'array:
 *
 *     Computer *pc = cerca(laboratorio, PC, "PC-014");
 *     if (pc != NULL) {
 *         pc->guasti++;
 *     }
 *
 * Comandi:
 *     G codice    segnala un guasto (il PC risulta non funzionante)
 *     R codice    riparato
 *     U codice n  aggiorna la RAM a n GB (solo verso l'alto)
 *     S           stato del laboratorio
 *     Q           fine
 */

#include <stdio.h>
#include <string.h>

#define PC 5

typedef struct {
    char inventario[8];
    int postazione;
    int ram_gb;
    int guasti;
    int funzionante;
} Computer;

Computer *cerca(Computer elenco[], int n, const char *inventario);
void stampa(const Computer *c);

int main(void)
{
    Computer laboratorio[PC] = {
        {"PC-011", 1, 8, 0, 1},
        {"PC-012", 2, 8, 1, 1},
        {"PC-014", 3, 4, 2, 1},
        {"PC-015", 4, 16, 0, 1},
        {"PC-019", 5, 8, 0, 1}
    };
    char comando = ' ';
    char codice[8];
    Computer *pc;
    int ram;
    int i;

    while (comando != 'Q') {
        printf("Comando (G codice, R codice, U codice n, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'G' || comando == 'R' || comando == 'U') {
            if (scanf("%7s", codice) != 1) {
                comando = 'Q';
            } else {
                pc = cerca(laboratorio, PC, codice);
                if (pc == NULL) {
                    printf("  %s non e' nell'inventario.\n", codice);
                } else if (comando == 'G') {
                    pc->guasti++;
                    pc->funzionante = 0;
                    printf("  Guasto registrato sulla postazione %d.\n", pc->postazione);
                } else if (comando == 'R') {
                    pc->funzionante = 1;
                    printf("  %s di nuovo funzionante.\n", pc->inventario);
                } else if (scanf("%d", &ram) == 1 && ram > pc->ram_gb) {
                    pc->ram_gb = ram;
                    printf("  %s ora ha %d GB.\n", pc->inventario, pc->ram_gb);
                } else {
                    printf("  La RAM si puo' solo aumentare (ora %d GB).\n", pc->ram_gb);
                }
            }
        } else if (comando == 'S') {
            for (i = 0; i < PC; i++) {
                stampa(&laboratorio[i]);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}

/* Indirizzo dell'elemento con quel numero di inventario, NULL se assente. */
Computer *cerca(Computer elenco[], int n, const char *inventario)
{
    Computer *trovato = NULL;
    int i = 0;

    while (i < n && trovato == NULL) {
        if (strcmp(elenco[i].inventario, inventario) == 0) {
            trovato = &elenco[i];
        }
        i++;
    }
    return trovato;
}

void stampa(const Computer *c)
{
    printf("  postazione %d  %s  %2d GB  guasti %d  %s\n", c->postazione, c->inventario, c->ram_gb,
           c->guasti, c->funzionante ? "ok" : "FUORI SERVIZIO");
}
