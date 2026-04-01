/*
 * 020-tipi-reali.c
 *
 * Tipi in virgola mobile in C
 *
 * Presenta float, double e long double: dimensioni, precisione e
 * notazione scientifica. Mostra la differenza pratica di precisione
 * tra float e double con un esempio di divisione. Introduce il problema
 * degli errori di arrotondamento e spiega perché confrontare reali
 * con == è pericoloso.
 */

#include <stdio.h>
#include <float.h>   /* contiene FLT_DIG, DBL_DIG, FLT_MAX, DBL_MAX, ecc. */

int main(void)
{
    /* dichiarazione di variabili reali */
    float       valore_f  = 3.14159265358979f;   /* suffisso f per float */
    double      valore_d  = 3.14159265358979;     /* double è il tipo di default */
    long double valore_ld = 3.14159265358979L;    /* suffisso L per long double */

    /* notazione scientifica: 1.5e3 equivale a 1500.0 */
    double distanza_km   = 1.496e8;   /* distanza Terra-Sole in km */
    double massa_elettrone = 9.109e-31; /* massa elettrone in kg */

    /* ── dimensioni in byte ─────────────────────────────────────────────── */
    printf("=== Dimensioni dei tipi reali ===\n");
    printf("float:        %zu byte\n", sizeof(float));
    printf("double:       %zu byte\n", sizeof(double));
    printf("long double:  %zu byte\n", sizeof(long double));

    /* ── cifre significative (da <float.h>) ─────────────────────────────── */
    /* FLT_DIG e DBL_DIG indicano quante cifre decimali sono garantite */
    printf("\n=== Cifre significative garantite ===\n");
    printf("float:        %d cifre\n", FLT_DIG);
    printf("double:       %d cifre\n", DBL_DIG);
    printf("long double:  %d cifre\n", LDBL_DIG);

    /* ── confronto di precisione ────────────────────────────────────────── */
    /* Stampando molte cifre decimali si vede dove la precisione finisce */
    printf("\n=== Precisione a confronto (pi greco) ===\n");
    printf("float:        %.20f\n", valore_f);
    printf("double:       %.20f\n", valore_d);
    printf("long double:  %.20Lf\n", valore_ld);

    /* ── notazione scientifica ──────────────────────────────────────────── */
    printf("\n=== Notazione scientifica ===\n");
    printf("Distanza Terra-Sole:  %.3e km\n", distanza_km);
    printf("Massa elettrone:      %.3e kg\n", massa_elettrone);

    /* ── errori di arrotondamento ───────────────────────────────────────── */
    printf("\n=== Attenzione agli arrotondamenti ===\n");
    printf("1.0 / 3.0 (float):   %.20f\n", (float)(1.0 / 3.0));
    printf("1.0 / 3.0 (double):  %.20f\n", 1.0 / 3.0);

    /* ── perché non usare == con i reali ────────────────────────────────── */
    /*
     * Il confronto diretto tra reali con == è pericoloso perché
     * gli errori di arrotondamento possono far risultare diversi
     * due valori che matematicamente sarebbero uguali.
     *
     *   SBAGLIATO:
     *   double x = 0.1 + 0.2;
     *   if (x == 0.3) { ... }   // potrebbe non entrare mai!
     *
     *   CORRETTO (con tolleranza):
     *   double differenza = x - 0.3;
     *   if (differenza < 0.0) differenza = -differenza;
     *   if (differenza < 1e-9) { ... }   // tolleranza piccola
     *
     * Questa tecnica verrà usata nei problemi dei capitoli successivi.
     */

    return 0;
}
