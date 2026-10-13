/*
 * 070-problema-copia-del-registro.c
 *
 * Simulare lo scrutinio su una copia: copia superficiale e profonda
 *
 * Prima dello scrutinio il coordinatore vuole provare delle modifiche
 * ai voti (un recupero, un voto corretto) su una COPIA del registro,
 * senza toccare l'originale. Il registro contiene un puntatore:
 *
 *     typedef struct {
 *         char classe[4];
 *         int n;
 *         double *voti;              blocco nello heap
 *     } Registro;
 *
 * L'assegnamento tra struct copia i campi, quindi copia il puntatore, non
 * il blocco a cui punta (copia SUPERFICIALE):
 *
 *     Registro prova = originale;    prova.voti == originale.voti
 *
 * Le due struct condividono lo stesso array: cambiare prova.voti[2]
 * cambia anche l'originale. E alla fine i due puntatori uguali
 * porterebbero a liberare due volte lo stesso blocco (doppio free).
 *
 * La copia PROFONDA alloca un nuovo blocco e vi copia i voti:
 *
 *     int duplica(const Registro *da, Registro *a);
 *
 * Ogni registro ha il suo blocco e si libera per conto suo.
 *
 * Il programma legge la classe, il numero di voti e i voti, poi le
 * modifiche da provare (posizione e nuovo voto) fino a FINE. Le applica
 * prima a una copia profonda e poi a una copia superficiale, e dopo ogni
 * prova stampa originale e copia.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOTI 30
#define MAX_MODIFICHE 10

typedef struct {
    char classe[4];
    int n;
    double *voti;
} Registro;

int duplica(const Registro *da, Registro *a);
void stampa(const char *titolo, const Registro *r);
void applica(Registro *r, const int posizioni[], const double nuovi[], int quante);

int main(void)
{
    Registro originale;
    Registro superficiale;
    Registro profonda;
    char classe[8];
    char parola[16];
    int posizioni[MAX_MODIFICHE];
    double nuovi[MAX_MODIFICHE];
    int modifiche = 0;
    int letti = 0;
    int finito = 0;

    originale.voti = NULL;
    printf("Classe e numero di voti: ");
    if (scanf("%7s %d", classe, &originale.n) != 2 || strlen(classe) > 3 ||
        originale.n < 1 || originale.n > MAX_VOTI) {
        printf("Dati non validi.\n");
    } else {
        strcpy(originale.classe, classe);
        originale.voti = malloc(originale.n * sizeof *originale.voti);
    }

    if (originale.voti != NULL) {
        printf("Voti: ");
        while (letti < originale.n && scanf("%lf", &originale.voti[letti]) == 1) {
            letti++;
        }
        while (!finito && letti == originale.n && modifiche < MAX_MODIFICHE) {
            printf("Modifica (posizione voto, FINE): ");
            if (scanf("%15s", parola) != 1 || strcmp(parola, "FINE") == 0) {
                finito = 1;
            } else if (sscanf(parola, "%d", &posizioni[modifiche]) != 1 ||
                       scanf("%lf", &nuovi[modifiche]) != 1 || posizioni[modifiche] < 1 ||
                       posizioni[modifiche] > originale.n) {
                printf("  modifica non valida\n");
            } else {
                modifiche++;
            }
        }

        if (letti < originale.n) {
            printf("Voti mancanti.\n");
        } else {
            stampa("originale ", &originale);

            printf("\n1. Copia profonda: duplica(&originale, &copia)\n");
            if (!duplica(&originale, &profonda)) {
                printf("Memoria insufficiente.\n");
            } else {
                printf("   blocco dell'originale %p, della copia %p\n",
                       (void *) originale.voti, (void *) profonda.voti);
                applica(&profonda, posizioni, nuovi, modifiche);
                stampa("copia     ", &profonda);
                stampa("originale ", &originale);
                printf("   L'originale non cambia.\n");
                free(profonda.voti);
            }

            printf("\n2. Copia superficiale: copia = originale\n");
            superficiale = originale;
            printf("   blocco dell'originale %p, della copia %p\n",
                   (void *) originale.voti, (void *) superficiale.voti);
            applica(&superficiale, posizioni, nuovi, modifiche);
            stampa("copia     ", &superficiale);
            stampa("originale ", &originale);
            printf("   Anche l'originale e' cambiato: il blocco dei voti e' lo stesso.\n");
        }
        /* superficiale.voti è lo stesso blocco: si libera una volta sola */
        free(originale.voti);
    }

    return 0;
}

/* Copia profonda: un nuovo blocco con gli stessi voti; 0 se manca
   memoria. */
int duplica(const Registro *da, Registro *a)
{
    int i;

    *a = *da;
    a->voti = malloc(da->n * sizeof *a->voti);
    if (a->voti != NULL) {
        for (i = 0; i < da->n; i++) {
            a->voti[i] = da->voti[i];
        }
    }
    return a->voti != NULL;
}

void applica(Registro *r, const int posizioni[], const double nuovi[], int quante)
{
    int k;

    for (k = 0; k < quante; k++) {
        r->voti[posizioni[k] - 1] = nuovi[k];
    }
}

void stampa(const char *titolo, const Registro *r)
{
    int i;

    printf("   %s %s:", titolo, r->classe);
    for (i = 0; i < r->n; i++) {
        printf(" %4.1f", r->voti[i]);
    }
    printf("\n");
}
