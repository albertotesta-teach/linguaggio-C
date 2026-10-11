/*
 * 020-array-di-puntatori-a-variabili.c
 *
 * Un array di puntatori a variabili separate
 *
 * Un array di puntatori può raccogliere in un elenco variabili che nel
 * programma sono separate, per elaborarle con un ciclo:
 *
 *     int *sensori[3] = {&aula, &laboratorio, &palestra};
 *
 *     *sensori[i]          la variabile i-esima (lettura e scrittura)
 *
 * Le variabili restano dove sono: l'array contiene solo i loro indirizzi.
 * Modificare *sensori[1] modifica direttamente laboratorio.
 *
 * Esempio: le temperature di tre locali della scuola, in decimi di grado,
 * aggiornate da un ciclo che applica la correzione del termostato.
 */

#include <stdio.h>

#define LOCALI 3
#define OBIETTIVO 200                   /* 20.0 gradi */

int main(void)
{
    int aula = 185;
    int laboratorio = 214;
    int palestra = 162;
    int *sensori[LOCALI] = {&aula, &laboratorio, &palestra};
    const char *nomi[LOCALI] = {"aula", "laboratorio", "palestra"};
    int i;

    printf("=== LETTURA TRAMITE L'ARRAY ===\n");
    for (i = 0; i < LOCALI; i++) {
        printf("  %-12s sensori[%d] = %p   *sensori[%d] = %.1f gradi\n",
               nomi[i], i, (void *) sensori[i], i, *sensori[i] / 10.0);
    }

    /* il termostato avvicina ogni locale all'obiettivo di 1 grado */
    for (i = 0; i < LOCALI; i++) {
        if (*sensori[i] < OBIETTIVO) {
            *sensori[i] = *sensori[i] + 10;
        } else if (*sensori[i] > OBIETTIVO) {
            *sensori[i] = *sensori[i] - 10;
        }
    }

    printf("\n=== DOPO UN'ORA, LETTURA DIRETTA DELLE VARIABILI ===\n");
    printf("  aula %.1f, laboratorio %.1f, palestra %.1f\n",
           aula / 10.0, laboratorio / 10.0, palestra / 10.0);

    return 0;
}
