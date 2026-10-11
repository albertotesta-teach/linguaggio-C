/*
 * 030-differenza-e-confronto.c
 *
 * Sottrarre e confrontare due puntatori
 *
 * Due puntatori allo STESSO array si possono sottrarre e confrontare:
 *
 *     q - p      quanti elementi separano p da q (non quanti byte)
 *     p < q      l'elemento puntato da p viene prima di quello puntato da q
 *     p == q     p e q puntano allo stesso elemento
 *
 * In particolare p - &v[0] è l'INDICE dell'elemento puntato da p.
 * Il risultato di una differenza ha tipo ptrdiff_t (un intero con segno):
 * negli esempi si assegna a un int.
 *
 * Confrontare o sottrarre puntatori ad array diversi non ha significato.
 *
 * Esempio: il profilo di un sentiero di montagna, con la quota misurata a
 * ogni chilometro. Un puntatore indica la cima, un altro il primo punto
 * oltre il limite del bosco.
 */

#include <stdio.h>

#define PUNTI  8
#define LIMITE 2000                     /* limite del bosco, in metri */

int main(void)
{
    int quote[PUNTI] = {1200, 1450, 1730, 1980, 2210, 2150, 2390, 2240};
    const int *inizio = &quote[0];
    const int *fine = inizio + PUNTI;
    const int *p;
    const int *cima = inizio;
    const int *oltre_bosco = NULL;
    int km;

    for (p = inizio; p < fine; p++) {
        if (*p > *cima) {
            cima = p;
        }
        if (oltre_bosco == NULL && *p >= LIMITE) {
            oltre_bosco = p;
        }
    }

    printf("=== PROFILO DEL SENTIERO ===\n");
    printf("Punti misurati: fine - inizio = %d\n", (int) (fine - inizio));

    km = cima - inizio;
    printf("Cima: %d m al km %d   (cima - inizio = %d)\n", *cima, km, km);
    if (cima == fine - 1) {
        printf("La cima e' l'ultimo punto del sentiero.\n");
    } else {
        printf("Dopo la cima il sentiero continua per %d km.\n",
               (int) (fine - 1 - cima));
    }

    if (oltre_bosco != NULL) {
        km = oltre_bosco - inizio;
        printf("Oltre il bosco (%d m) dal km %d\n", LIMITE, km);
        if (oltre_bosco < cima) {
            printf("Si esce dal bosco %d km prima della cima.\n",
                   (int) (cima - oltre_bosco));
        } else {
            printf("Si esce dal bosco proprio sulla cima.\n");
        }
    } else {
        printf("Il sentiero resta sempre nel bosco.\n");
    }

    return 0;
}
