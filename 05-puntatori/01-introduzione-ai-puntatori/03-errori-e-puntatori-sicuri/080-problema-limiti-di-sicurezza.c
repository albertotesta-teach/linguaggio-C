/*
 * 080-problema-limiti-di-sicurezza.c
 *
 * Il controllo di sicurezza di una pressa industriale
 *
 * Nel laboratorio di meccanica una pressa idraulica è sorvegliata da un
 * programma che legge la pressione a intervalli regolari. I limiti di
 * sicurezza sono costanti e nessuna parte del programma deve poterli
 * cambiare; il sensore scrive sempre nella stessa variabile.
 *
 * I puntatori esprimono queste regole:
 *
 *     int *const sensore = &pressione;
 *         il sensore punterà sempre a pressione (il puntatore è costante),
 *         ma può scriverci le nuove letture
 *
 *     const int *const soglia_allarme = &ALLARME;
 *     const int *const soglia_arresto = &ARRESTO;
 *         né il puntatore né il valore possono cambiare
 *
 * Per ogni lettura il programma stabilisce lo stato (normale, allarme,
 * arresto). Dopo un arresto la pressa resta ferma: le letture successive
 * vengono solo registrate. Al termine stampa il numero di allarmi e il
 * valore massimo letto.
 */

#include <stdio.h>

#define LETTURE 10

int main(void)
{
    const int ALLARME = 180;            /* bar */
    const int ARRESTO = 210;
    int pressione = 0;
    int letture[LETTURE] = {120, 150, 175, 182, 168, 190, 205, 214, 160, 140};

    int *const sensore = &pressione;
    const int *const soglia_allarme = &ALLARME;
    const int *const soglia_arresto = &ARRESTO;

    int k;
    int allarmi = 0;
    int massima = 0;
    int ferma = 0;

    printf("Soglie: allarme %d bar, arresto %d bar\n", *soglia_allarme, *soglia_arresto);
    for (k = 0; k < LETTURE; k++) {
        *sensore = letture[k];          /* il sensore scrive nella sua variabile */
        if (pressione > massima) {
            massima = pressione;
        }

        printf("  lettura %2d: %3d bar  ", k + 1, pressione);
        if (ferma) {
            printf("(pressa ferma)\n");
        } else if (pressione >= *soglia_arresto) {
            ferma = 1;
            printf("ARRESTO DI EMERGENZA\n");
        } else if (pressione >= *soglia_allarme) {
            allarmi++;
            printf("allarme\n");
        } else {
            printf("normale\n");
        }
    }

    /* sensore = &massima;          ERRORE: il puntatore è costante      */
    /* *soglia_arresto = 250;       ERRORE: il valore è di sola lettura  */

    printf("\nAllarmi: %d, pressione massima: %d bar, pressa %s\n", allarmi, massima,
           ferma ? "in arresto" : "in funzione");

    return 0;
}
