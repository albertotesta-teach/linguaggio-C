/*
 * 010-funzione-che-alloca.c
 *
 * Una funzione che alloca un blocco e lo restituisce al chiamante
 *
 * Un blocco ottenuto con malloc non appartiene a una funzione: resta
 * valido finché qualcuno non chiama free, anche dopo che la funzione che
 * l'ha allocato è terminata. Una funzione può quindi preparare un array
 * e restituirne l'indirizzo:
 *
 *     int *crea_tabellina(int numero, int n)
 *     {
 *         int *v = malloc(n * sizeof *v);
 *         ...riempie v...
 *         return v;                   restituisce l'indirizzo del blocco
 *     }
 *
 *     int *t = crea_tabellina(7, 10);
 *     if (t != NULL) {
 *         ... t[0] ... t[9] ...
 *         free(t);                    lo libera chi lo ha ricevuto
 *     }
 *
 * La variabile locale v sparisce con la funzione, ma il blocco a cui
 * puntava no: il suo indirizzo è stato copiato in t. Se la malloc
 * fallisce la funzione restituisce NULL, e il chiamante lo controlla.
 *
 * Esempio: le tabelline per il ripasso di matematica della primaria, con
 * il numero di righe scelto.
 */

#include <stdio.h>
#include <stdlib.h>

int *crea_tabellina(int numero, int n);

int main(void)
{
    int *tabellina;
    int numeri[3] = {7, 9, 12};
    int righe[3] = {5, 10, 3};
    int k;
    int i;

    for (k = 0; k < 3; k++) {
        tabellina = crea_tabellina(numeri[k], righe[k]);
        if (tabellina == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            printf("Tabellina del %d (%d righe, blocco in %p):", numeri[k], righe[k],
                   (void *) tabellina);
            for (i = 0; i < righe[k]; i++) {
                printf(" %d", tabellina[i]);
            }
            printf("\n");
            free(tabellina);
        }
    }

    return 0;
}

/* Restituisce un blocco di n int con numero x 1 ... numero x n, o NULL. */
int *crea_tabellina(int numero, int n)
{
    int *v = malloc(n * sizeof *v);
    int i;

    if (v != NULL) {
        for (i = 0; i < n; i++) {
            v[i] = numero * (i + 1);
        }
    }
    return v;
}
