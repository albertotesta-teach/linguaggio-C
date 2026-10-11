/*
 * 030-puntatori-const.c
 *
 * const e puntatori: che cosa non si può modificare
 *
 * La parola const, messa in posizioni diverse, protegge cose diverse:
 *
 *   const int *p        puntatore a un int costante: tramite p si può
 *                       LEGGERE ma non scrivere (*p = 1 è un errore);
 *                       p può puntare altrove
 *
 *   int *const p = &x   puntatore costante: p punterà SEMPRE a x;
 *                       *p si può modificare
 *
 *   const int *const p  né p né *p si possono modificare
 *
 * Si legge da destra verso sinistra: "p è un puntatore costante a int",
 * "p è un puntatore a int costante".
 *
 * L'uso più frequente è nei parametri: una funzione che riceve
 * const int *valore promette di non modificare la variabile del chiamante.
 * Le istruzioni vietate sono nei commenti: il compilatore le rifiuterebbe.
 */

#include <stdio.h>

void stampa_temperatura(const int *decimi);

int main(void)
{
    int interna = 215;
    int esterna = 87;
    const int *sola_lettura = &interna;
    int *const sensore = &esterna;
    const int massima = 300;
    const int *const limite = &massima;

    /* ── const int * : si legge, si cambia variabile, non si scrive ── */
    printf("sola_lettura -> %d\n", *sola_lettura);
    /* *sola_lettura = 200;     ERRORE: la variabile puntata è di sola lettura */
    sola_lettura = &esterna;            /* permesso: punta a un'altra variabile */
    printf("sola_lettura -> %d (ora punta a esterna)\n", *sola_lettura);

    /* ── int *const : si scrive, ma non si cambia variabile ───────── */
    *sensore = 92;                      /* permesso: modifica esterna */
    /* sensore = &interna;      ERRORE: il puntatore è costante */
    printf("esterna = %d (scritta tramite sensore)\n", esterna);

    /* ── const int *const : nulla si può modificare ───────────────── */
    printf("limite -> %d\n", *limite);
    /* *limite = 350;           ERRORE */
    /* limite = &interna;       ERRORE */

    printf("\nFunzione con parametro const int *:\n");
    stampa_temperatura(&interna);
    stampa_temperatura(&esterna);

    return 0;
}

/* Stampa una temperatura in decimi di grado. Il parametro è const: la
 * funzione non può modificare la variabile del chiamante. */
void stampa_temperatura(const int *decimi)
{
    /* *decimi = 0;             ERRORE: parametro di sola lettura */
    printf("  %.1f gradi\n", *decimi / 10.0);
}
