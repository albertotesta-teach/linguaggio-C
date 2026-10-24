/*
 * 050-problema-giorni-di-lezione.c
 *
 * Il nuovo orario: ore di lezione per giorno della settimana
 *
 * Il coordinatore inserisce le ore di lezione di una classe per ogni
 * giorno, dal lunedì al sabato. I giorni sono un enum usato come indice:
 *
 *     typedef enum {
 *         LUNEDI, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI, SABATO, NUM_GIORNI
 *     } Giorno;
 *
 *     int ore[NUM_GIORNI];
 *
 * Il programma legge le ore di ogni giorno (da 0 a 8; se il valore non
 * è valido lo richiede) e stampa:
 *   - il totale settimanale, che deve essere 32 per il biennio;
 *   - il giorno con più ore (il primo, a parità);
 *   - i giorni liberi, con 0 ore.
 */

#include <stdio.h>

#define MAX_ORE 8
#define ORE_SETTIMANALI 32

typedef enum {
    LUNEDI, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI, SABATO, NUM_GIORNI
} Giorno;

void svuota_riga(void);

int main(void)
{
    const char *nomi[NUM_GIORNI] = {
        [LUNEDI] = "lunedi", [MARTEDI] = "martedi", [MERCOLEDI] = "mercoledi",
        [GIOVEDI] = "giovedi", [VENERDI] = "venerdi", [SABATO] = "sabato"
    };
    int ore[NUM_GIORNI];
    int totale = 0;
    int liberi = 0;
    int letto;
    Giorno g;
    Giorno massimo = LUNEDI;

    for (g = LUNEDI; g < NUM_GIORNI; g++) {
        ore[g] = -1;
        while (ore[g] == -1) {
            printf("Ore di %s: ", nomi[g]);
            letto = scanf("%d", &ore[g]);
            if (letto == EOF) {
                ore[g] = 0;
            } else if (letto != 1) {
                svuota_riga();          /* scarta la riga non numerica */
                printf("  Scrivi un numero.\n");
            } else if (ore[g] < 0 || ore[g] > MAX_ORE) {
                printf("  Da 0 a %d ore.\n", MAX_ORE);
                ore[g] = -1;
            }
        }
        totale = totale + ore[g];
        if (ore[g] > ore[massimo]) {
            massimo = g;
        }
    }

    printf("\nTotale: %d ore %s\n", totale,
           totale == ORE_SETTIMANALI ? "(corretto)" : "(il biennio ne prevede 32)");
    printf("Giorno piu' lungo: %s con %d ore\n", nomi[massimo], ore[massimo]);
    printf("Giorni liberi:");
    for (g = LUNEDI; g < NUM_GIORNI; g++) {
        if (ore[g] == 0) {
            printf(" %s", nomi[g]);
            liberi++;
        }
    }
    if (liberi == 0) {
        printf(" nessuno");
    }
    printf("\n");

    return 0;
}

/* Scarta i caratteri rimasti sulla riga. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
