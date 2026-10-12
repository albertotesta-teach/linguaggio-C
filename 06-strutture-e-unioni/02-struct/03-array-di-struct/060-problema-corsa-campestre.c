/*
 * 060-problema-corsa-campestre.c
 *
 * Corsa campestre d'istituto: il podio di ogni categoria
 *
 * Alla campestre corrono insieme due categorie, allievi e juniores. Per
 * ogni atleta si registrano nome, classe, categoria e tempo in secondi:
 *
 *     typedef struct {
 *         char nome[20];
 *         char classe[4];
 *         char categoria;          'A' allievi, 'J' juniores
 *         int tempo;               secondi
 *     } Atleta;
 *
 * Il podio di una categoria NON richiede di ordinare tutto l'array: basta
 * cercare tre volte il tempo minimo tra gli atleti della categoria non
 * ancora premiati. Un array di flag premiato[] (parallelo agli atleti)
 * ricorda chi è già sul podio. Un tempo pari a 0 indica un atleta ritirato,
 * che non entra in classifica.
 *
 * Il programma stampa il podio delle due categorie, il distacco del
 * secondo e del terzo dal primo e il numero di arrivati per categoria.
 */

#include <stdio.h>

#define ATLETI 10
#define PODIO  3

typedef struct {
    char nome[20];
    char classe[4];
    char categoria;
    int tempo;
} Atleta;

int main(void)
{
    Atleta atleti[ATLETI] = {
        {"Rinaldi", "1A", 'A', 742},
        {"Gentile", "4B", 'J', 701},
        {"Pellegrini", "2C", 'A', 728},
        {"Mancini", "5A", 'J', 689},
        {"Serra", "1B", 'A', 0},
        {"Vitale", "3A", 'J', 715},
        {"Testa", "2A", 'A', 735},
        {"Fabbri", "4C", 'J', 698},
        {"Marchi", "2B", 'A', 751},
        {"Riva", "5B", 'J', 0}
    };
    const char categorie[2] = {'A', 'J'};
    const char *nomi_categorie[2] = {"ALLIEVI", "JUNIORES"};
    int premiato[ATLETI] = {0};
    int c;
    int posto;
    int i;
    int migliore;
    int tempo_primo = 0;
    int arrivati;

    for (c = 0; c < 2; c++) {
        arrivati = 0;
        for (i = 0; i < ATLETI; i++) {
            if (atleti[i].categoria == categorie[c] && atleti[i].tempo > 0) {
                arrivati++;
            }
        }
        printf("=== %s (%d arrivati) ===\n", nomi_categorie[c], arrivati);
        for (posto = 1; posto <= PODIO && posto <= arrivati; posto++) {
            /* il più veloce tra quelli della categoria non ancora premiati */
            migliore = -1;
            for (i = 0; i < ATLETI; i++) {
                if (atleti[i].categoria == categorie[c] && atleti[i].tempo > 0 && !premiato[i] &&
                    (migliore == -1 || atleti[i].tempo < atleti[migliore].tempo)) {
                    migliore = i;
                }
            }
            premiato[migliore] = 1;
            if (posto == 1) {
                tempo_primo = atleti[migliore].tempo;
            }
            printf("  %d. %-11s %s  %d'%02d\"", posto, atleti[migliore].nome, atleti[migliore].classe,
                   atleti[migliore].tempo / 60, atleti[migliore].tempo % 60);
            if (posto > 1) {
                printf("  +%d s", atleti[migliore].tempo - tempo_primo);
            }
            printf("\n");
        }
    }

    return 0;
}
