/*
 * 030-puntatori-invalidati.c
 *
 * Dopo realloc i puntatori dentro il blocco non valgono più
 *
 * Se realloc sposta il blocco, libera quello vecchio. Ogni puntatore che
 * indicava un elemento del blocco vecchio diventa pendente:
 *
 *     Studente *capoclasse = &classe[2];
 *     tmp = realloc(classe, ...);         classe può essersi spostata
 *     capoclasse->voto                    SBAGLIATO: memoria liberata
 *
 * Gli INDICI invece restano validi: l'elemento numero 2 è sempre
 * classe[2], ovunque si trovi il blocco.
 *
 *     int capoclasse = 2;
 *     tmp = realloc(classe, ...);
 *     classe = tmp;
 *     classe[capoclasse].voto             corretto
 *
 * Regola: per ricordare un elemento di un blocco che può cambiare
 * dimensione si conserva il suo indice, non il suo indirizzo.
 *
 * Esempio: la classe ha un capoclasse; poi arrivano due studenti nuovi e
 * il blocco si ingrandisce. Prima della realloc il programma alloca un
 * piccolo blocco subito dopo, così è probabile che la realloc sposti i
 * dati. L'indirizzo del capoclasse si salva come numero (uintptr_t, da
 * <stdint.h>) solo per confrontarlo: il vecchio puntatore non si usa
 * più.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    char nome[16];
    double voto;
} Studente;

int main(void)
{
    const char *nomi[5] = {"Marta", "Luca", "Sara", "Paolo", "Anna"};
    Studente *classe = malloc(3 * sizeof *classe);
    Studente *disturbo = malloc(sizeof *disturbo);
    Studente *tmp;
    int capoclasse = 2;
    uintptr_t indirizzo_prima;
    int i;

    if (classe == NULL || disturbo == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        for (i = 0; i < 3; i++) {
            strcpy(classe[i].nome, nomi[i]);
            classe[i].voto = 6 + i;
        }
        indirizzo_prima = (uintptr_t) &classe[capoclasse];
        printf("Capoclasse: %s, elemento %d, in %p\n", classe[capoclasse].nome, capoclasse,
               (void *) &classe[capoclasse]);

        tmp = realloc(classe, 5 * sizeof *classe);
        if (tmp == NULL) {
            printf("Memoria insufficiente: la classe resta di 3.\n");
        } else {
            classe = tmp;
            for (i = 3; i < 5; i++) {
                strcpy(classe[i].nome, nomi[i]);
                classe[i].voto = 6 + i;
            }
            printf("Dopo realloc l'elemento %d sta in %p\n", capoclasse,
                   (void *) &classe[capoclasse]);
            if ((uintptr_t) &classe[capoclasse] != indirizzo_prima) {
                printf("Il blocco si e' spostato: un puntatore salvato prima sarebbe pendente.\n");
            } else {
                printf("Il blocco e' rimasto al suo posto, ma non si poteva saperlo prima.\n");
            }
            printf("Con l'indice: capoclasse %s, voto %.1f\n", classe[capoclasse].nome,
                   classe[capoclasse].voto);
        }
    }

    free(classe);
    free(disturbo);

    return 0;
}
