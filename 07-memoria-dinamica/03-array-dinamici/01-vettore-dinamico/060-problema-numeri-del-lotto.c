/*
 * 060-problema-numeri-del-lotto.c
 *
 * Statistica: frequenze e ritardi dei numeri estratti
 *
 * In un'unità di statistica la classe raccoglie le estrazioni di una
 * ruota del lotto: 5 numeri diversi da 1 a 90 per estrazione. Il numero
 * di estrazioni non è fissato, quindi vanno in un vettore dinamico:
 *
 *     typedef struct {
 *         int numeri[5];
 *     } Estrazione;
 *
 *     typedef struct {
 *         Estrazione *dati;
 *         int n;
 *         int capacita;
 *     } Archivio;
 *
 * Alla fine, per ogni numero da 1 a 90 si calcolano
 *   - la frequenza: in quante estrazioni è uscito;
 *   - il ritardo: quante estrazioni sono passate dall'ultima uscita
 *     (-1 per i numeri mai usciti, che non entrano nella classifica).
 *
 * Il programma stampa i 5 numeri più frequenti e i 5 più in ritardo, e
 * ricorda agli studenti che ogni estrazione è indipendente dalle
 * precedenti: un numero in ritardo non ha più probabilità di uscire.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMERI 5
#define MASSIMO 90
#define CLASSIFICA 5

typedef struct {
    int numeri[NUMERI];
} Estrazione;

typedef struct {
    Estrazione *dati;
    int n;
    int capacita;
} Archivio;

Archivio *crea_archivio(int capacita);
int aggiungi(Archivio *a, Estrazione e);
int lunghezza(const Archivio *a);
Estrazione elemento(const Archivio *a, int i);
void distruggi_archivio(Archivio *a);
int valida(const Estrazione *e);
void stampa_primi(const char *titolo, const int valore[]);

int main(void)
{
    Archivio *archivio = crea_archivio(4);
    Estrazione e;
    char parola[16];
    int frequenza[MASSIMO + 1] = {0};
    int ritardo[MASSIMO + 1];
    int finito = 0;
    int i;
    int k;
    int letti;

    if (archivio == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        printf("Estrazioni (5 numeri, FINE per terminare):\n");
        while (!finito) {
            if (scanf("%15s", parola) != 1 || strcmp(parola, "FINE") == 0) {
                finito = 1;
            } else {
                letti = sscanf(parola, "%d", &e.numeri[0]);
                for (k = 1; k < NUMERI && letti == k; k++) {
                    letti = letti + scanf("%d", &e.numeri[k]);
                }
                if (letti != NUMERI || !valida(&e)) {
                    printf("  estrazione non valida\n");
                    scanf("%*[^\n]");
                } else if (!aggiungi(archivio, e)) {
                    printf("Memoria insufficiente.\n");
                    finito = 1;
                }
            }
        }

        for (k = 1; k <= MASSIMO; k++) {
            ritardo[k] = -1;
        }
        for (i = 0; i < lunghezza(archivio); i++) {
            e = elemento(archivio, i);
            for (k = 0; k < NUMERI; k++) {
                frequenza[e.numeri[k]]++;
                ritardo[e.numeri[k]] = lunghezza(archivio) - 1 - i;
            }
        }

        printf("\nEstrazioni: %d\n", lunghezza(archivio));
        if (lunghezza(archivio) > 0) {
            stampa_primi("Piu' frequenti", frequenza);
            stampa_primi("Piu' in ritardo tra gli usciti", ritardo);
            printf("Ogni estrazione e' indipendente: il ritardo non aumenta la probabilita'.\n");
        }
        distruggi_archivio(archivio);
    }

    return 0;
}

Archivio *crea_archivio(int capacita)
{
    Archivio *a = malloc(sizeof *a);

    if (a != NULL) {
        a->dati = malloc(capacita * sizeof *a->dati);
        if (a->dati == NULL) {
            free(a);
            a = NULL;
        } else {
            a->n = 0;
            a->capacita = capacita;
        }
    }
    return a;
}

int aggiungi(Archivio *a, Estrazione e)
{
    Estrazione *tmp;
    int ok = 1;

    if (a->n == a->capacita) {
        tmp = realloc(a->dati, 2 * a->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            a->dati = tmp;
            a->capacita = 2 * a->capacita;
        }
    }
    if (ok) {
        a->dati[a->n] = e;
        a->n++;
    }
    return ok;
}

int lunghezza(const Archivio *a)
{
    return a->n;
}

Estrazione elemento(const Archivio *a, int i)
{
    return a->dati[i];
}

void distruggi_archivio(Archivio *a)
{
    if (a != NULL) {
        free(a->dati);
        free(a);
    }
}

/* Numeri da 1 a 90, tutti diversi. */
int valida(const Estrazione *e)
{
    int ok = 1;
    int i;
    int j;

    for (i = 0; i < NUMERI && ok; i++) {
        ok = e->numeri[i] >= 1 && e->numeri[i] <= MASSIMO;
        for (j = 0; j < i && ok; j++) {
            ok = e->numeri[i] != e->numeri[j];
        }
    }
    return ok;
}

/*
 * I CLASSIFICA numeri con il valore più alto (a parità il più piccolo),
 * tra quelli con valore positivo o nullo.
 */
void stampa_primi(const char *titolo, const int valore[])
{
    int scelto[MASSIMO + 1] = {0};
    int migliore;
    int c;
    int k;

    printf("%s:", titolo);
    for (c = 0; c < CLASSIFICA; c++) {
        migliore = 0;
        for (k = 1; k <= MASSIMO; k++) {
            if (!scelto[k] && valore[k] >= 0 &&
                (migliore == 0 || valore[k] > valore[migliore])) {
                migliore = k;
            }
        }
        if (migliore != 0) {
            scelto[migliore] = 1;
            printf("  %d (%d)", migliore, valore[migliore]);
        }
    }
    printf("\n");
}
