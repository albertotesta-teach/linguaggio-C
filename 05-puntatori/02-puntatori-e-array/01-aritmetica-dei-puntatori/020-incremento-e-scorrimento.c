/*
 * 020-incremento-e-scorrimento.c
 *
 * Scorrere un array spostando il puntatore
 *
 *     p++     p passa all'elemento successivo  (p = p + 1)
 *     p--     p torna all'elemento precedente  (p = p - 1)
 *
 * Il ciclo tipico usa due puntatori: quello che si sposta e fine, che
 * contiene l'indirizzo subito DOPO l'ultimo elemento.
 *
 *     fine = &v[0] + N;
 *     for (p = &v[0]; p < fine; p++) {
 *         ... *p ...
 *     }
 *
 * fine si può calcolare e confrontare, ma non si deve mai dereferenziare:
 * dopo l'ultimo elemento non c'è nulla che appartenga all'array.
 *
 * Esempio: i passi giornalieri registrati da un contapassi in una settimana.
 */

#include <stdio.h>

#define GIORNI    7
#define OBIETTIVO 8000

int main(void)
{
    int passi[GIORNI] = {6420, 8150, 4980, 10230, 7600, 12890, 3150};
    const int *fine = &passi[0] + GIORNI;
    const int *p;
    int giorno = 1;
    int totale = 0;
    int raggiunti = 0;

    printf("=== CONTAPASSI: SCORRIMENTO CON p++ ===\n");
    for (p = &passi[0]; p < fine; p++) {
        printf("  giorno %d   p = %p   *p = %5d", giorno, (void *) p, *p);
        if (*p >= OBIETTIVO) {
            printf("   obiettivo raggiunto");
            raggiunti++;
        }
        printf("\n");
        totale = totale + *p;
        giorno++;
    }
    printf("Totale %d passi, media %d al giorno, obiettivo raggiunto %d volte su %d\n",
           totale, totale / GIORNI, raggiunti, GIORNI);

    printf("\n=== ULTIMI 3 GIORNI, DAL PIU' RECENTE (p--) ===\n");
    p = fine - 1;
    giorno = GIORNI;
    while (p >= fine - 3) {
        printf("  giorno %d: %5d passi\n", giorno, *p);
        p--;
        giorno--;
    }

    return 0;
}
