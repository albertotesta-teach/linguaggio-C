/*
 * 010-memory-leak.c
 *
 * Memory leak: un blocco di cui si è perso l'indirizzo
 *
 * Un blocco si può liberare solo passando a free il suo indirizzo. Se
 * l'unico puntatore che lo conosceva viene sovrascritto, il blocco resta
 * occupato fino alla fine del programma e nessuno può più liberarlo: è
 * una perdita di memoria (memory leak).
 *
 *     char *messaggio = malloc(32);
 *     ...
 *     messaggio = malloc(32);       il primo blocco è perso
 *
 * Il programma non si accorge di niente: nessun errore, nessun avviso.
 * Ma un programma che resta acceso a lungo (il server del registro
 * elettronico, il software della centralina) perde un po' di memoria a
 * ogni ciclo, finché la memoria finisce.
 *
 * La regola: prima di riusare un puntatore, si libera il blocco a cui
 * punta (oppure si conserva il suo indirizzo da un'altra parte).
 *
 * Esempio: tre avvisi da mostrare sul monitor dell'atrio, ognuno in un
 * blocco nuovo. La prima versione perde davvero due blocchi: i
 * contatori allocati e liberati lo mostrano. (Il sistema operativo
 * recupera tutta la memoria quando il programma termina, per questo qui
 * non succede niente di grave.) La seconda versione libera il blocco
 * precedente prima di allocarne uno nuovo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AVVISI 3
#define LUNG 40

int main(void)
{
    const char *testi[AVVISI] = {"Assemblea alle 10", "Palestra chiusa", "Uscita alle 12"};
    char *avviso = NULL;
    int allocati = 0;
    int liberati = 0;
    int i;

    printf("Versione con perdita:\n");
    for (i = 0; i < AVVISI; i++) {
        avviso = malloc(LUNG);              /* il blocco precedente è perso */
        if (avviso != NULL) {
            allocati++;
            strcpy(avviso, testi[i]);
            printf("  monitor: %-20s blocco %p\n", avviso, (void *) avviso);
        }
    }
    free(avviso);                           /* libera solo l'ultimo */
    liberati++;
    printf("  allocati %d, liberati %d: blocchi persi %d (%d byte)\n\n", allocati, liberati,
           allocati - liberati, (allocati - liberati) * LUNG);

    allocati = 0;
    liberati = 0;
    avviso = NULL;
    printf("Versione corretta:\n");
    for (i = 0; i < AVVISI; i++) {
        if (avviso != NULL) {
            free(avviso);                   /* prima si libera il vecchio */
            liberati++;
        }
        avviso = malloc(LUNG);
        if (avviso != NULL) {
            allocati++;
            strcpy(avviso, testi[i]);
            printf("  monitor: %-20s blocco %p\n", avviso, (void *) avviso);
        }
    }
    if (avviso != NULL) {
        free(avviso);
        liberati++;
    }
    printf("  allocati %d, liberati %d: blocchi persi %d\n", allocati, liberati,
           allocati - liberati);

    return 0;
}
