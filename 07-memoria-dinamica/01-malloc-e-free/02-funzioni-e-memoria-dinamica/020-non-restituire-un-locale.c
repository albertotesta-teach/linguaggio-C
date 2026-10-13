/*
 * 020-non-restituire-un-locale.c
 *
 * Non si restituisce l'indirizzo di una variabile locale
 *
 * Un array locale vive nello stack della funzione: quando la funzione
 * termina, quella memoria viene riusata dalle chiamate successive.
 * Questa versione è SBAGLIATA:
 *
 *     char *etichetta(const char *aula, int posto)
 *     {
 *         char testo[16];
 *         snprintf(testo, 16, "%s-%02d", aula, posto);
 *         return testo;               indirizzo di memoria che sparisce
 *     }
 *
 * Il chiamante riceve un puntatore pendente: punta a memoria che non è
 * più della funzione. A volte sembra funzionare, poi la prima chiamata
 * successiva la sovrascrive. gcc e clang lo segnalano con un avviso
 * ("address of local variable returned"): per questo la versione
 * sbagliata compare solo in questo commento.
 *
 * Ci sono due modi corretti:
 *
 *   1. la memoria la fornisce il chiamante, la funzione la riempie:
 *          void scrivi_etichetta(char testo[], const char *aula, int posto);
 *
 *   2. la funzione alloca nello heap e restituisce il blocco; il
 *      chiamante lo libera:
 *          char *crea_etichetta(const char *aula, int posto);
 *
 * Esempio: le etichette dei banchi del laboratorio (LAB1-07). Con il
 * primo modo lo stesso buffer viene riscritto a ogni chiamata; con il
 * secondo ogni etichetta ha il suo blocco e si possono tenere tutte.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNG_ETICHETTA 16
#define BANCHI 3

void scrivi_etichetta(char testo[], const char *aula, int posto);
char *crea_etichetta(const char *aula, int posto);

int main(void)
{
    char buffer[LUNG_ETICHETTA];
    char *etichette[BANCHI];
    int i;

    printf("1. Memoria del chiamante (un solo buffer):\n");
    for (i = 0; i < BANCHI; i++) {
        scrivi_etichetta(buffer, "LAB1", i + 1);
        printf("  %s all'indirizzo %p\n", buffer, (void *) buffer);
    }

    printf("\n2. Memoria allocata dalla funzione (un blocco per etichetta):\n");
    for (i = 0; i < BANCHI; i++) {
        etichette[i] = crea_etichetta("LAB2", i + 1);
    }
    for (i = 0; i < BANCHI; i++) {
        if (etichette[i] != NULL) {
            printf("  %s all'indirizzo %p\n", etichette[i], (void *) etichette[i]);
        }
    }
    for (i = 0; i < BANCHI; i++) {
        free(etichette[i]);
    }

    return 0;
}

void scrivi_etichetta(char testo[], const char *aula, int posto)
{
    snprintf(testo, LUNG_ETICHETTA, "%s-%02d", aula, posto);
}

char *crea_etichetta(const char *aula, int posto)
{
    char *testo = malloc(LUNG_ETICHETTA);

    if (testo != NULL) {
        snprintf(testo, LUNG_ETICHETTA, "%s-%02d", aula, posto);
    }
    return testo;
}
