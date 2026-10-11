/*
 * 040-problema-termostato.c
 *
 * Il termostato di un appartamento con tre zone
 *
 * Il pannello di controllo regola la temperatura desiderata di tre zone:
 * soggiorno, camera e bagno. Le tre temperature sono variabili separate.
 * Il pannello ha un solo paio di tasti + e -, che agiscono sulla zona
 * selezionata: per questo il programma usa un puntatore, zona_attiva, che
 * punta alla temperatura della zona scelta.
 *
 * Comandi (una lettera per riga):
 *     S, C, B   seleziona soggiorno, camera, bagno  (zona_attiva = &...)
 *     +, -      aumenta o diminuisce di mezzo grado (*zona_attiva += 5)
 *     Q         esce
 *
 * Le temperature sono in decimi di grado (215 = 21.5 °C) e devono restare
 * tra MINIMA e MASSIMA. Finché non si seleziona una zona il puntatore vale
 * NULL e i tasti + e - non hanno effetto.
 */

#include <stdio.h>

#define PASSO   5                       /* mezzo grado */
#define MINIMA  160
#define MASSIMA 260

void stampa_stato(int soggiorno, int camera, int bagno);

int main(void)
{
    int soggiorno = 205;
    int camera = 190;
    int bagno = 220;
    int *zona_attiva = NULL;
    char comando = ' ';

    printf("=== TERMOSTATO ===\n");
    stampa_stato(soggiorno, camera, bagno);

    while (comando != 'Q') {
        printf("Comando (S C B + - Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }

        if (comando == 'S') {
            zona_attiva = &soggiorno;
            printf("  zona: soggiorno\n");
        } else if (comando == 'C') {
            zona_attiva = &camera;
            printf("  zona: camera\n");
        } else if (comando == 'B') {
            zona_attiva = &bagno;
            printf("  zona: bagno\n");
        } else if (comando == '+' || comando == '-') {
            if (zona_attiva == NULL) {
                printf("  Seleziona prima una zona.\n");
            } else if (comando == '+' && *zona_attiva + PASSO > MASSIMA) {
                printf("  Massimo raggiunto (%.1f gradi).\n", MASSIMA / 10.0);
            } else if (comando == '-' && *zona_attiva - PASSO < MINIMA) {
                printf("  Minimo raggiunto (%.1f gradi).\n", MINIMA / 10.0);
            } else {
                if (comando == '+') {
                    *zona_attiva = *zona_attiva + PASSO;
                } else {
                    *zona_attiva = *zona_attiva - PASSO;
                }
                printf("  impostata %.1f gradi\n", *zona_attiva / 10.0);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    stampa_stato(soggiorno, camera, bagno);

    return 0;
}

void stampa_stato(int soggiorno, int camera, int bagno)
{
    printf("Soggiorno %.1f | Camera %.1f | Bagno %.1f\n",
           soggiorno / 10.0, camera / 10.0, bagno / 10.0);
}
