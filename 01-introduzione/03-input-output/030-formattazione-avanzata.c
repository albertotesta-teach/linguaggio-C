/*
 * 030-formattazione-avanzata.c
 *
 * Formattazione avanzata con printf
 *
 * Approfondisce le opzioni di formato di printf per costruire output
 * tabellare e allineato: larghezza minima del campo, allineamento a
 * sinistra, zeri iniziali, precisione decimale e notazione scientifica.
 * Queste tecniche sono fondamentali per produrre report leggibili.
 *
 * Sintassi generale dello specificatore:
 *   %[flag][larghezza][.precisione]tipo
 */

#include <stdio.h>

int main(void)
{
    /* ── larghezza minima del campo ─────────────────────────────────────── */
    /* Un numero dopo % definisce la larghezza minima in caratteri.
     * Se il valore è più corto, viene aggiunto padding a sinistra (default). */
    printf("=== Larghezza minima ===\n");
    printf("[%5d]\n",  42);      /* padding a sinistra con spazi */
    printf("[%5d]\n",  -7);      /* il segno occupa un posto */
    printf("[%5d]\n",  12345);   /* esattamente 5 cifre: nessun padding */
    printf("[%5d]\n",  123456);  /* più di 5 cifre: la larghezza è ignorata */

    /* ── allineamento a sinistra con flag - ─────────────────────────────── */
    printf("\n=== Allineamento a sinistra (flag -) ===\n");
    printf("[%-5d]\n",  42);     /* padding a destra */
    printf("[%-5d]\n",  12345);

    /* ── zeri iniziali con flag 0 ───────────────────────────────────────── */
    /* Utile per codici, numeri di matricola, date */
    printf("\n=== Zeri iniziali (flag 0) ===\n");
    printf("[%05d]\n",  42);     /* 00042 */
    printf("[%06d]\n",  1234);   /* 001234 */

    /* ── precisione per i reali ─────────────────────────────────────────── */
    /* .N dopo la larghezza indica quante cifre dopo la virgola */
    printf("\n=== Precisione decimale ===\n");
    printf("[%10.2f]\n",  3.14159);   /* larghezza 10, 2 decimali */
    printf("[%10.4f]\n",  3.14159);   /* larghezza 10, 4 decimali */
    printf("[%-10.2f]\n", 3.14159);   /* allineato a sinistra */
    printf("[%.0f]\n",    3.14159);   /* nessun decimale */

    /* ── tabella allineata ──────────────────────────────────────────────── */
    /* Esempio pratico: report di prodotti con colonne allineate */
    printf("\n=== Esempio: tabella prodotti ===\n");
    printf("%-4s  %-15s  %8s  %6s\n", "Cod", "Prodotto", "Prezzo", "Qta'");
    printf("%-4s  %-15s  %8s  %6s\n", "----", "---------------", "--------", "------");
    printf("%-4d  %-15s  %8.2f  %6d\n",  1, "Penna",    0.50,  200);
    printf("%-4d  %-15s  %8.2f  %6d\n",  2, "Quaderno", 2.90,   85);
    printf("%-4d  %-15s  %8.2f  %6d\n", 12, "Zaino",   34.99,   12);

    /* ── notazione scientifica e automatica ─────────────────────────────── */
    printf("\n=== Notazione scientifica ===\n");
    printf("%%e (scientifica): %e\n",  123456.789);   /* sempre esponente */
    printf("%%g (automatica):  %g\n",  123456.789);   /* sceglie il formato */
    printf("%%g (piccolo):     %g\n",  0.000123);     /* usa esponente se conviene */
    printf("%%g (grande):      %g\n",  1.23e10);

    return 0;
}
