/*
 * 020-piu-puntatori-stessa-variabile.c
 *
 * Più puntatori, una variabile; un puntatore, più variabili
 *
 * Un puntatore è una variabile come le altre: si può copiare e si può far
 * puntare altrove.
 *
 *     q = p;       copia l'INDIRIZZO: ora p e q puntano alla stessa variabile
 *     *q = *p;     copia il VALORE: la variabile puntata da q prende il valore
 *                  di quella puntata da p (le variabili restano due)
 *     p = &y;      p ora punta a un'altra variabile
 *
 * Quando due puntatori indicano la stessa variabile, una modifica fatta
 * tramite uno è visibile tramite l'altro.
 *
 * Esempio: i posti liberi di due sale di un cinema e i puntatori usati da
 * due casse che vendono biglietti.
 */

#include <stdio.h>

int main(void)
{
    int sala_a = 120;
    int sala_b = 150;
    int *cassa_1;
    int *cassa_2;

    /* ── 1. Due puntatori alla stessa variabile ───────────────────── */
    cassa_1 = &sala_a;
    cassa_2 = cassa_1;                  /* copia dell'indirizzo */
    printf("=== Le due casse vendono per la sala A ===\n");
    printf("  cassa_1 = %p, cassa_2 = %p, &sala_a = %p\n",
           (void *) cassa_1, (void *) cassa_2, (void *) &sala_a);

    *cassa_1 = *cassa_1 - 4;            /* la cassa 1 vende 4 biglietti */
    *cassa_2 = *cassa_2 - 2;            /* la cassa 2 ne vende 2 */
    printf("  posti liberi in sala A: %d (120 - 4 - 2)\n\n", sala_a);

    /* ── 2. Un puntatore cambia variabile ─────────────────────────── */
    cassa_2 = &sala_b;
    printf("=== La cassa 2 passa alla sala B ===\n");
    *cassa_2 = *cassa_2 - 5;
    printf("  sala A: %d   sala B: %d\n", sala_a, sala_b);
    printf("  cassa_1 == cassa_2? %s\n\n", cassa_1 == cassa_2 ? "si'" : "no");

    /* ── 3. Copiare il valore, non l'indirizzo ────────────────────── */
    printf("=== *cassa_2 = *cassa_1 ===\n");
    *cassa_2 = *cassa_1;
    printf("  sala B ridotta come la A: sala A %d, sala B %d (stesso numero, sale diverse)\n",
           sala_a, sala_b);
    *cassa_1 = *cassa_1 - 10;
    printf("  dopo altri 10 biglietti in sala A: sala A %d, sala B %d\n", sala_a, sala_b);

    return 0;
}
