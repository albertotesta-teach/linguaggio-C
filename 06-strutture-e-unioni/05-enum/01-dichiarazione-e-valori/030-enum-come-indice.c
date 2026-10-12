/*
 * 030-enum-come-indice.c
 *
 * Usare le costanti come indici degli array
 *
 * Le costanti partono da 0 e salgono di uno: sono gli indici di un
 * array. Una costante in più alla fine conta gli elementi:
 *
 *     typedef enum {
 *         LUNEDI, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI, SABATO,
 *         NUM_GIORNI                     vale 6: quanti sono i giorni
 *     } Giorno;
 *
 *     int ore[NUM_GIORNI];
 *     ore[MERCOLEDI] = 5;
 *
 * Se si aggiunge un giorno prima di NUM_GIORNI, la dimensione degli
 * array si adegua da sola.
 *
 * Una tabella di stringhe indicizzata dall'enum dà il nome di ogni
 * costante. Con l'inizializzazione per indice ([MERCOLEDI] = ...) ogni
 * nome sta accanto alla sua costante, qualunque sia l'ordine:
 *
 *     const char *nomi[NUM_GIORNI] = {
 *         [LUNEDI] = "lunedi", [MARTEDI] = "martedi", ...
 *     };
 *
 * Esempio: le ore di lezione della 3B, giorno per giorno.
 */

#include <stdio.h>

typedef enum {
    LUNEDI, MARTEDI, MERCOLEDI, GIOVEDI, VENERDI, SABATO, NUM_GIORNI
} Giorno;

int main(void)
{
    const char *nomi[NUM_GIORNI] = {
        [LUNEDI] = "lunedi", [MARTEDI] = "martedi", [MERCOLEDI] = "mercoledi",
        [GIOVEDI] = "giovedi", [VENERDI] = "venerdi", [SABATO] = "sabato"
    };
    int ore[NUM_GIORNI] = {[LUNEDI] = 6, [MARTEDI] = 5, [MERCOLEDI] = 5, [GIOVEDI] = 6,
                           [VENERDI] = 5, [SABATO] = 0};
    int totale = 0;
    Giorno g;

    printf("NUM_GIORNI = %d\n", NUM_GIORNI);
    for (g = LUNEDI; g < NUM_GIORNI; g++) {
        printf("  %-10s %d ore\n", nomi[g], ore[g]);
        totale = totale + ore[g];
    }
    printf("Totale settimanale: %d ore\n", totale);
    printf("Il %s si esce prima: %d ore\n", nomi[MERCOLEDI], ore[MERCOLEDI]);

    return 0;
}
