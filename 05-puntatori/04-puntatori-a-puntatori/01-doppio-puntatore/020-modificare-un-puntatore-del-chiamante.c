/*
 * 020-modificare-un-puntatore-del-chiamante.c
 *
 * Una funzione che cambia dove punta un puntatore del chiamante
 *
 * Per modificare un int del chiamante una funzione riceve un int *.
 * Allo stesso modo, per modificare un PUNTATORE del chiamante (cioè
 * cambiare la variabile a cui punta) la funzione riceve l'indirizzo del
 * puntatore, un int **:
 *
 *     void scegli_coda(int **coda, int *c1, int *c2, int *c3);
 *     scegli_coda(&mia_coda, &cassa1, &cassa2, &cassa3);
 *     dentro la funzione:  *coda = c2;      mia_coda ora punta a cassa2
 *
 * Se la funzione ricevesse solo int *coda, cambierebbe la propria copia
 * del puntatore e il chiamante non vedrebbe nulla.
 *
 * Esempio: al supermercato il cliente si mette nella cassa con meno
 * persone in fila; quando si mette in coda, la fila di quella cassa cresce.
 */

#include <stdio.h>

void scegli_coda_copia(int *coda, int *c1, int *c2, int *c3);
void scegli_coda(int **coda, int *c1, int *c2, int *c3);

int main(void)
{
    int cassa1 = 4;
    int cassa2 = 2;
    int cassa3 = 5;
    int *mia_coda = &cassa1;
    int cliente;

    printf("Code iniziali: %d %d %d\n", cassa1, cassa2, cassa3);

    scegli_coda_copia(mia_coda, &cassa1, &cassa2, &cassa3);
    printf("Dopo scegli_coda_copia: mia_coda punta ancora alla cassa 1? %s\n",
           mia_coda == &cassa1 ? "si'" : "no");

    for (cliente = 1; cliente <= 4; cliente++) {
        scegli_coda(&mia_coda, &cassa1, &cassa2, &cassa3);
        *mia_coda = *mia_coda + 1;      /* il cliente si mette in fila */
        printf("Cliente %d -> cassa %d.  Code: %d %d %d\n", cliente,
               mia_coda == &cassa1 ? 1 : (mia_coda == &cassa2 ? 2 : 3),
               cassa1, cassa2, cassa3);
    }

    return 0;
}

/* SBAGLIATA: modifica solo la copia locale del puntatore. */
void scegli_coda_copia(int *coda, int *c1, int *c2, int *c3)
{
    coda = c1;
    if (*c2 < *coda) {
        coda = c2;
    }
    if (*c3 < *coda) {
        coda = c3;
    }
    printf("  dentro scegli_coda_copia: coda punta a una fila di %d persone\n", *coda);
}

/* Fa puntare il puntatore del chiamante alla cassa con la fila più corta
 * (a parità, quella con il numero più basso). */
void scegli_coda(int **coda, int *c1, int *c2, int *c3)
{
    *coda = c1;
    if (*c2 < **coda) {
        *coda = c2;
    }
    if (*c3 < **coda) {
        *coda = c3;
    }
}
