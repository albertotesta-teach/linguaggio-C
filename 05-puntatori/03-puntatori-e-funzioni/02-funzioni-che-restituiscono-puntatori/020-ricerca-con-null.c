/*
 * 020-ricerca-con-null.c
 *
 * Restituire NULL quando non si trova nulla
 *
 * Una funzione di ricerca che restituisce un puntatore ha un modo naturale
 * per dire "non trovato": restituire NULL. Il chiamante DEVE controllare il
 * risultato prima di usarlo:
 *
 *     int *trovato = cerca(v, n, valore);
 *     if (trovato != NULL) {
 *         *trovato = 0;             uso sicuro
 *     }
 *
 * Rispetto a una ricerca che restituisce l'indice (-1 se non trovato) il
 * puntatore permette di modificare subito l'elemento trovato.
 *
 * Esempio: gli armadietti degli studenti. armadietti[i] contiene il numero
 * di matricola dello studente che lo usa, 0 se è libero. Quando uno
 * studente restituisce la chiave si cerca la sua matricola e si libera
 * l'armadietto.
 */

#include <stdio.h>

#define ARMADIETTI 8

int *cerca(int *v, int n, int valore);
void stampa(const int *v, int n);

int main(void)
{
    int armadietti[ARMADIETTI] = {4120, 0, 3871, 4402, 0, 3990, 4015, 0};
    int restituzioni[3] = {4402, 5000, 3990};
    int *trovato;
    int i;

    stampa(armadietti, ARMADIETTI);

    for (i = 0; i < 3; i++) {
        trovato = cerca(armadietti, ARMADIETTI, restituzioni[i]);
        if (trovato != NULL) {
            printf("Matricola %d: armadietto n. %d liberato\n",
                   restituzioni[i], (int) (trovato - armadietti) + 1);
            *trovato = 0;
        } else {
            printf("Matricola %d: nessun armadietto assegnato\n", restituzioni[i]);
        }
    }

    /* la stessa funzione trova anche il primo armadietto libero */
    trovato = cerca(armadietti, ARMADIETTI, 0);
    if (trovato != NULL) {
        *trovato = 4560;
        printf("Nuovo studente 4560: armadietto n. %d\n", (int) (trovato - armadietti) + 1);
    }

    stampa(armadietti, ARMADIETTI);

    return 0;
}

/* Restituisce l'indirizzo del primo elemento uguale a valore, NULL se non
 * c'è. Il ciclo si ferma appena l'elemento è trovato. */
int *cerca(int *v, int n, int valore)
{
    int *p = v;

    while (p < v + n && *p != valore) {
        p++;
    }
    return p < v + n ? p : NULL;
}

void stampa(const int *v, int n)
{
    int i;

    printf("Armadietti:");
    for (i = 0; i < n; i++) {
        if (v[i] == 0) {
            printf(" [libero]");
        } else {
            printf(" [%d]", v[i]);
        }
    }
    printf("\n");
}
