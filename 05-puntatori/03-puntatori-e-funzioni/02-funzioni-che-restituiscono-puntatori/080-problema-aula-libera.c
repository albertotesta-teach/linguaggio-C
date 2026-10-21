/*
 * 080-problema-aula-libera.c
 *
 * Supplenze: l'aula libera più vicina
 *
 * Al primo piano della scuola ci sono AULE aule numerate da 1 lungo un
 * corridoio; occupata[i] vale 1 se l'aula i + 1 è occupata nell'ora
 * corrente. Quando un docente chiede un'aula, se quella richiesta è
 * occupata gli si assegna la libera più vicina lungo il corridoio (a
 * parità di distanza, quella con il numero più basso).
 *
 * piu_vicina(occupata, AULE, richiesta) restituisce il puntatore
 * all'elemento dell'aula assegnata, NULL se sono tutte occupate. Il
 * chiamante la segna come occupata scrivendo tramite il puntatore e ne
 * ricava il numero con p - occupata + 1.
 *
 * Il programma legge i numeri di aula richiesti; 0 termina.
 */

#include <stdio.h>

#define AULE 10

int *piu_vicina(int *occupata, int n, int richiesta);
void stampa_corridoio(const int *occupata, int n);
void svuota_riga(void);

int main(void)
{
    int occupata[AULE] = {1, 0, 1, 1, 1, 0, 1, 1, 0, 1};
    int richiesta = 1;
    int *aula;
    int letti;

    stampa_corridoio(occupata, AULE);
    while (richiesta != 0) {
        printf("Aula richiesta (1-%d, 0 per finire): ", AULE);
        letti = scanf("%d", &richiesta);
        if (letti == EOF) {
            richiesta = 0;              /* input terminato: come 0 */
        } else if (letti == 0) {
            svuota_riga();              /* non è un numero */
            richiesta = -1;             /* aula inesistente */
        }
        if (richiesta < 0 || richiesta > AULE) {
            printf("  Aula inesistente.\n");
        } else if (richiesta != 0) {
            aula = piu_vicina(occupata, AULE, richiesta);
            if (aula == NULL) {
                printf("  Nessuna aula libera.\n");
            } else {
                *aula = 1;
                if (aula - occupata + 1 == richiesta) {
                    printf("  Assegnata l'aula %d.\n", richiesta);
                } else {
                    printf("  Aula %d occupata: assegnata l'aula %d.\n",
                           richiesta, (int) (aula - occupata) + 1);
                }
                stampa_corridoio(occupata, AULE);
            }
        }
    }

    return 0;
}

/* Cerca l'aula libera più vicina alla richiesta allargando la distanza:
 * prima la richiesta stessa, poi a distanza 1 (sinistra, destra), 2, ...
 * Restituisce l'indirizzo dell'elemento trovato o NULL. */
int *piu_vicina(int *occupata, int n, int richiesta)
{
    int centro = richiesta - 1;
    int *trovata = NULL;
    int d;

    /* le posizioni si controllano come indici, prima di costruire il
     * puntatore: un indirizzo fuori dall'array non va nemmeno calcolato */
    for (d = 0; d < n && trovata == NULL; d++) {
        if (centro - d >= 0 && *(occupata + centro - d) == 0) {
            trovata = occupata + centro - d;
        } else if (centro + d < n && *(occupata + centro + d) == 0) {
            trovata = occupata + centro + d;
        }
    }
    return trovata;
}

void stampa_corridoio(const int *occupata, int n)
{
    int i;

    printf("  Corridoio:");
    for (i = 0; i < n; i++) {
        if (occupata[i]) {
            printf(" [%2d X]", i + 1);
        } else {
            printf(" [%2d  ]", i + 1);
        }
    }
    printf("\n");
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
