/*
 * 010-printf-basi.c
 *
 * Basi di printf
 *
 * Presenta in modo sistematico la funzione printf: i principali
 * specificatori di formato, le sequenze di escape e la combinazione
 * di testo fisso e valori di variabili nella stessa chiamata.
 * È il punto di partenza per capire come il programma comunica
 * risultati all'utente.
 */

#include <stdio.h>

int main(void)
{
    /* variabili di esempio per i diversi tipi */
    int    contatore   = 42;
    int    negativo    = -7;
    unsigned int positivo = 300u;
    long   grande      = 1234567890L;
    double temperatura = 36.6;
    char   iniziale    = 'M';

    /* ── specificatori di formato principali ────────────────────────────── */
    printf("=== Specificatori di formato ===\n");

    /* %d stampa un intero con segno in base decimale */
    printf("Intero con segno:     %d\n", contatore);
    printf("Intero negativo:      %d\n", negativo);

    /* %u stampa un intero senza segno */
    printf("Intero senza segno:   %u\n", positivo);

    /* %ld per long, %lld per long long */
    printf("Long:                 %ld\n", grande);

    /* %f stampa un double in notazione decimale (default: 6 cifre) */
    printf("Double (default):     %f\n", temperatura);

    /* %e stampa in notazione scientifica */
    printf("Double (scientific):  %e\n", temperatura);

    /* %c stampa un singolo carattere */
    printf("Carattere:            %c\n", iniziale);

    /* %% stampa il simbolo % letterale */
    printf("Percentuale:          100%%\n");

    /* ── sequenze di escape ─────────────────────────────────────────────── */
    printf("\n=== Sequenze di escape ===\n");
    printf("A capo:        riga 1\n              riga 2\n");
    printf("Tabulazione:   col1\tcol2\tcol3\n");
    printf("Virgolette:    \"testo tra virgolette\"\n");
    printf("Barra rovescia: C:\\Users\\nome\n");

    /* ── più valori nella stessa printf ─────────────────────────────────── */
    printf("\n=== Più valori in una printf ===\n");

    /* l'ordine degli argomenti corrisponde all'ordine degli specificatori */
    printf("Contatore=%d, temperatura=%.1f, iniziale=%c\n",
           contatore, temperatura, iniziale);

    /* combinazione di testo fisso e valori: molto usata per etichette */
    printf("Il valore di contatore e': %d (decimale)\n", contatore);

    return 0;
}
