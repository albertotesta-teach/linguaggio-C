/*
 * 060-problema-taglie-magazzino.c
 *
 * Le magliette della scuola: scorte per taglia
 *
 * Il comitato studentesco vende le magliette con il logo della scuola.
 * Le taglie sono un enum e le scorte un array indicizzato dalla taglia:
 *
 *     typedef enum { XS, S, M, L, XL, XXL, NUM_TAGLIE } Taglia;
 *
 *     int scorte[NUM_TAGLIE];
 *
 * Comandi:
 *     V taglia quantita    vendita (se le scorte bastano)
 *     C taglia quantita    carico di nuove magliette
 *     S                    stato: scorte di ogni taglia, con "ESAURITA" e
 *                          "da riordinare" sotto le 5 magliette
 *     Q                    fine
 *
 * La taglia si scrive come sigla (M, XL...): si cerca la sigla nella
 * tabella dei nomi e la sua posizione è la costante dell'enum. Una
 * posizione uguale a NUM_TAGLIE significa che la sigla non esiste.
 */

#include <stdio.h>
#include <string.h>

#define SOGLIA_RIORDINO 5

typedef enum {
    XS, S, M, L, XL, XXL, NUM_TAGLIE
} Taglia;

int main(void)
{
    const char *sigle[NUM_TAGLIE] = {[XS] = "XS", [S] = "S", [M] = "M",
                                     [L] = "L", [XL] = "XL", [XXL] = "XXL"};
    int scorte[NUM_TAGLIE] = {[XS] = 4, [S] = 12, [M] = 20, [L] = 15, [XL] = 6, [XXL] = 0};
    char comando = ' ';
    char sigla[8];
    int quantita;
    Taglia t;

    while (comando != 'Q') {
        printf("Comando (V taglia n, C taglia n, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'V' || comando == 'C') {
            if (scanf("%7s %d", sigla, &quantita) != 2) {
                comando = 'Q';
            } else {
                t = XS;
                while (t < NUM_TAGLIE && strcmp(sigle[t], sigla) != 0) {
                    t++;
                }
                if (t == NUM_TAGLIE) {
                    printf("  Taglia %s inesistente.\n", sigla);
                } else if (quantita <= 0) {
                    printf("  Quantita' non valida.\n");
                } else if (comando == 'C') {
                    scorte[t] = scorte[t] + quantita;
                    printf("  Taglia %s: %d magliette.\n", sigle[t], scorte[t]);
                } else if (scorte[t] == 0) {
                    printf("  Taglia %s esaurita.\n", sigle[t]);
                } else if (quantita > scorte[t]) {
                    printf("  Taglia %s: ne restano solo %d.\n", sigle[t], scorte[t]);
                } else {
                    scorte[t] = scorte[t] - quantita;
                    printf("  Vendita registrata: taglia %s, ne restano %d.\n", sigle[t],
                           scorte[t]);
                }
            }
        } else if (comando == 'S') {
            for (t = XS; t < NUM_TAGLIE; t++) {
                printf("  %-3s %3d", sigle[t], scorte[t]);
                if (scorte[t] == 0) {
                    printf("  ESAURITA");
                } else if (scorte[t] < SOGLIA_RIORDINO) {
                    printf("  da riordinare");
                }
                printf("\n");
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}
