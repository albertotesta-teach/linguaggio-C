/*
 * 080-problema-trasferimento-tra-conti.c
 *
 * Riconoscere se due indirizzi indicano la stessa variabile
 *
 * Il gestionale del bar della scuola tiene il credito di tre tessere
 * prepagate (in centesimi). La funzione trasferisci(da, a, importo)
 * sposta credito da una tessera all'altra: riceve gli INDIRIZZI delle due
 * tessere (parametri per riferimento, capitolo 03) perché deve modificarle.
 *
 * Prima di eseguire il trasferimento la funzione controlla che:
 *   - le due tessere non siano la stessa: se da == a gli indirizzi sono
 *     uguali, quindi si tratta della stessa variabile;
 *   - il credito della tessera di origine sia sufficiente.
 *
 * Confrontare gli indirizzi (da == a) è diverso dal confrontare i valori
 * (*da == *a): due tessere diverse possono avere lo stesso credito.
 *
 * La funzione restituisce un codice di esito che il main traduce in testo.
 */

#include <stdio.h>

#define OK            0
#define STESSA_TESSERA 1
#define CREDITO_BASSO 2
#define IMPORTO_ERRATO 3

int trasferisci(int *da, int *a, int importo);
void stampa_tessere(int t1, int t2, int t3);

int main(void)
{
    int tessera_1 = 1500;
    int tessera_2 = 400;
    int tessera_3 = 1500;
    char esiti[4][32] = {
        "eseguito", "stessa tessera", "credito insufficiente", "importo non valido"
    };
    int esito;

    printf("Indirizzi: tessera_1 %p, tessera_2 %p, tessera_3 %p\n",
           (void *) &tessera_1, (void *) &tessera_2, (void *) &tessera_3);
    stampa_tessere(tessera_1, tessera_2, tessera_3);

    /* stesso valore non significa stessa variabile */
    printf("tessera_1 e tessera_3 hanno lo stesso credito (tessera_1 == tessera_3)? %s\n",
           tessera_1 == tessera_3 ? "si'" : "no");
    printf("Sono la stessa tessera (&tessera_1 == &tessera_3)? %s\n",
           &tessera_1 == &tessera_3 ? "si'" : "no");

    esito = trasferisci(&tessera_1, &tessera_2, 600);
    printf("\nDa 1 a 2, 6.00 euro: %s\n", esiti[esito]);
    stampa_tessere(tessera_1, tessera_2, tessera_3);

    esito = trasferisci(&tessera_2, &tessera_2, 200);
    printf("\nDa 2 a 2, 2.00 euro: %s\n", esiti[esito]);

    esito = trasferisci(&tessera_2, &tessera_3, 5000);
    printf("Da 2 a 3, 50.00 euro: %s\n", esiti[esito]);

    esito = trasferisci(&tessera_3, &tessera_1, -100);
    printf("Da 3 a 1, -1.00 euro: %s\n", esiti[esito]);
    stampa_tessere(tessera_1, tessera_2, tessera_3);

    return 0;
}

/* Sposta importo centesimi da *da ad *a. Restituisce un codice di esito. */
int trasferisci(int *da, int *a, int importo)
{
    int esito = OK;

    if (da == a) {
        esito = STESSA_TESSERA;
    } else if (importo <= 0) {
        esito = IMPORTO_ERRATO;
    } else if (*da < importo) {
        esito = CREDITO_BASSO;
    } else {
        *da = *da - importo;
        *a = *a + importo;
    }
    return esito;
}

void stampa_tessere(int t1, int t2, int t3)
{
    printf("Crediti: tessera 1 %d.%02d  tessera 2 %d.%02d  tessera 3 %d.%02d euro\n",
           t1 / 100, t1 % 100, t2 / 100, t2 % 100, t3 / 100, t3 % 100);
}
