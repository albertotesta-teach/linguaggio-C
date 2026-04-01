/*
 * 040-problema-scheda-studente.c
 *
 * Scheda studente con media voti
 *
 * L'utente inserisce i dati numerici di uno studente: numero di matricola,
 * anno di corso, tre voti di esame (interi) e il voto finale di laurea
 * (double). Il programma calcola la media aritmetica dei tre voti e
 * stampa una scheda formattata con colonne allineate.
 *
 * Mette in pratica: scanf con tipi misti, printf con larghezze di campo,
 * calcolo della media con divisione reale, zeri iniziali per la matricola.
 */

#include <stdio.h>

int main(void)
{
    /* dati anagrafici e accademici */
    int    matricola;
    int    anno_corso;       /* 1=primo anno, 2=secondo, ... */

    /* tre voti di esame (scala 18-30) */
    int    voto1;
    int    voto2;
    int    voto3;

    /* voto di laurea (scala 66-110, con eventuale lode) */
    double voto_laurea;

    /* dati calcolati */
    double media_voti;

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Inserimento dati studente ===\n\n");

    printf("Numero di matricola:    ");
    scanf("%d", &matricola);

    printf("Anno di corso (1-5):    ");
    scanf("%d", &anno_corso);

    printf("Voto esame 1 (18-30):   ");
    scanf("%d", &voto1);

    printf("Voto esame 2 (18-30):   ");
    scanf("%d", &voto2);

    printf("Voto esame 3 (18-30):   ");
    scanf("%d", &voto3);

    printf("Voto di laurea (66-110): ");
    scanf("%lf", &voto_laurea);

    /* ── calcolo ────────────────────────────────────────────────────────── */
    /* divisione per 3.0 (reale) per ottenere un risultato in virgola mobile;
     * dividere per 3 (intero) troncherebbe la parte decimale */
    media_voti = (voto1 + voto2 + voto3) / 3.0;

    /* ── output: scheda formattata ──────────────────────────────────────── */
    printf("\n");
    printf("============================================\n");
    printf("  SCHEDA STUDENTE\n");
    printf("============================================\n");
    printf("  Matricola:      %07d\n", matricola);
    printf("  Anno di corso:  %d° anno\n", anno_corso);
    printf("--------------------------------------------\n");
    printf("  Voto esame 1:   %3d / 30\n", voto1);
    printf("  Voto esame 2:   %3d / 30\n", voto2);
    printf("  Voto esame 3:   %3d / 30\n", voto3);
    printf("  Media:          %6.2f / 30\n", media_voti);
    printf("--------------------------------------------\n");
    printf("  Voto di laurea: %6.1f / 110\n", voto_laurea);
    printf("============================================\n");

    return 0;
}
