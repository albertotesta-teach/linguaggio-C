/*
 * 080-problema-fusione-di-classi.c
 *
 * Due classi poco numerose diventano una: unire due elenchi ordinati
 *
 * L'anno prossimo la 4A e la 4B saranno accorpate. La segreteria ha i
 * due elenchi in ordine alfabetico e vuole l'elenco unico, sempre in
 * ordine, senza ordinarlo da capo.
 *
 * Il blocco della prima classe si ingrandisce con realloc fino a
 * contenere anche la seconda, poi i due elenchi si fondono partendo dal
 * fondo:
 *
 *     a: [Bassi Conti Ferri] [_ _]        i = ultimo di a
 *     b: [Galli Neri]                     j = ultimo di b
 *                                         k = ultima posizione libera
 *
 *     finché ci sono elementi in b:
 *         il maggiore tra a[i] e b[j] va in a[k], poi k--
 *
 * Partendo dal fondo, la posizione k è sempre libera oppure già copiata
 * altrove: nessun elemento di a viene sovrascritto prima di essere
 * spostato, e non serve un terzo array.
 *
 * Il programma legge le due classi (numero di studenti e cognomi), le
 * controlla (devono essere in ordine alfabetico) e stampa l'elenco
 * unico con la classe di provenienza.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTI 30

typedef struct {
    char cognome[20];
    char classe[4];
} Studente;

int leggi_classe(Studente **elenco, int *n, const char *classe);
int fondi(Studente **a, int n_a, const Studente b[], int n_b);

int main(void)
{
    Studente *quarta_a = NULL;
    Studente *quarta_b = NULL;
    int n_a = 0;
    int n_b = 0;
    int i;

    if (leggi_classe(&quarta_a, &n_a, "4A") && leggi_classe(&quarta_b, &n_b, "4B")) {
        printf("Blocco della 4A: %d studenti, %zu byte\n", n_a, n_a * sizeof *quarta_a);
        if (!fondi(&quarta_a, n_a, quarta_b, n_b)) {
            printf("Memoria insufficiente.\n");
        } else {
            printf("Blocco ingrandito: %d studenti, %zu byte\n\nNuova 4A:\n", n_a + n_b,
                   (n_a + n_b) * sizeof *quarta_a);
            for (i = 0; i < n_a + n_b; i++) {
                printf("  %2d. %-12s (da %s)\n", i + 1, quarta_a[i].cognome, quarta_a[i].classe);
            }
        }
    }
    free(quarta_a);
    free(quarta_b);

    return 0;
}

/* Alloca e legge una classe; 0 se i dati mancano o non sono in ordine. */
int leggi_classe(Studente **elenco, int *n, const char *classe)
{
    int ok;
    int i;

    printf("Studenti della %s e cognomi in ordine: ", classe);
    ok = scanf("%d", n) == 1 && *n >= 1 && *n <= MAX_STUDENTI;
    if (ok) {
        *elenco = malloc(*n * sizeof **elenco);
        ok = *elenco != NULL;
    }
    for (i = 0; i < *n && ok; i++) {
        ok = scanf("%19s", (*elenco)[i].cognome) == 1;
        if (ok) {
            strcpy((*elenco)[i].classe, classe);
        }
        if (ok && i > 0 && strcmp((*elenco)[i - 1].cognome, (*elenco)[i].cognome) > 0) {
            printf("  %s non e' in ordine dopo %s\n", (*elenco)[i].cognome,
                   (*elenco)[i - 1].cognome);
            ok = 0;
        }
    }
    if (!ok) {
        printf("Elenco della %s non valido.\n", classe);
    }
    return ok;
}

/* Ingrandisce *a e vi fonde b partendo dal fondo; 0 se realloc fallisce. */
int fondi(Studente **a, int n_a, const Studente b[], int n_b)
{
    Studente *tmp = realloc(*a, (n_a + n_b) * sizeof *tmp);
    int i = n_a - 1;
    int j = n_b - 1;
    int k = n_a + n_b - 1;

    if (tmp != NULL) {
        while (j >= 0) {
            if (i >= 0 && strcmp(tmp[i].cognome, b[j].cognome) > 0) {
                tmp[k] = tmp[i];
                i--;
            } else {
                tmp[k] = b[j];
                j--;
            }
            k--;
        }
        *a = tmp;
    }
    return tmp != NULL;
}
