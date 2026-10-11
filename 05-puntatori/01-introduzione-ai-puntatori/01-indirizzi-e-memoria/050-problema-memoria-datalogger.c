/*
 * 050-problema-memoria-datalogger.c
 *
 * Quante misure entrano nella memoria di un datalogger
 *
 * Una stazione meteo didattica è costruita con un microcontrollore che ha
 * a disposizione MEMORIA_DATI byte per salvare le misure. Ogni misura
 * comprende temperatura, umidità e pressione. Prima di scrivere il
 * firmware bisogna scegliere i tipi:
 *
 *   versione A  tutto in double                    (massima precisione)
 *   versione B  tutto in float
 *   versione C  numeri interi in decimi o unità:   temperatura in decimi
 *               di grado (short), umidità in % (char), pressione in hPa
 *               (short)
 *
 * Per ogni versione il programma calcola con sizeof i byte di una misura,
 * quante misure entrano in memoria e per quanti giorni si può registrare
 * con una misura ogni INTERVALLO minuti.
 */

#include <stdio.h>

#define MEMORIA_DATI 32768              /* 32 KB */
#define INTERVALLO   10                 /* minuti tra due misure */
#define MINUTI_GIORNO (24 * 60)

void stampa_versione(char nome, const char descrizione[], int byte_misura);

int main(void)
{
    double t_a = 21.5;                  /* versione A */
    double u_a = 45.0;
    double p_a = 1013.2;
    float t_b = 21.5f;                  /* versione B */
    float u_b = 45.0f;
    float p_b = 1013.2f;
    short t_c = 215;                    /* decimi di grado */
    char u_c = 45;                      /* percentuale */
    short p_c = 1013;                   /* hPa */

    printf("=== DIMENSIONAMENTO DEL DATALOGGER ===\n");
    printf("Memoria disponibile: %d byte, una misura ogni %d minuti\n\n",
           MEMORIA_DATI, INTERVALLO);
    printf("  Ver. %-34s %5s %7s %7s\n", "Tipi", "Byte", "Misure", "Giorni");

    stampa_versione('A', "double, double, double",
                    (int) (sizeof(t_a) + sizeof(u_a) + sizeof(p_a)));
    stampa_versione('B', "float, float, float",
                    (int) (sizeof(t_b) + sizeof(u_b) + sizeof(p_b)));
    stampa_versione('C', "short (decimi), char (%), short",
                    (int) (sizeof(t_c) + sizeof(u_c) + sizeof(p_c)));

    printf("\nEsempio di misura nella versione C: %d decimi = %.1f gradi, %d%%, %d hPa\n",
           t_c, t_c / 10.0, u_c, p_c);
    printf("Con gli interi si perde poco in precisione e si registra molto piu' a lungo.\n");

    return 0;
}

/* Stampa una riga della tabella: byte per misura, misure e giorni. */
void stampa_versione(char nome, const char descrizione[], int byte_misura)
{
    int misure;
    double giorni;

    misure = MEMORIA_DATI / byte_misura;
    giorni = (double) misure * INTERVALLO / MINUTI_GIORNO;
    printf("  %c    %-34s %5d %7d %7.1f\n", nome, descrizione, byte_misura, misure, giorni);
}
