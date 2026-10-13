/*
 * 050-problema-presenze-del-mese.c
 *
 * Il registro delle presenze di un mese: giorni per studenti
 *
 * Il coordinatore di classe riporta le assenze del mese. Il numero di
 * studenti e di giorni di lezione si legge all'inizio; la tabella delle
 * assenze è una matrice giorni x studenti in un solo blocco:
 *
 *     int *assente = calloc(giorni * studenti, sizeof *assente);
 *
 *     assente[g * studenti + s] = 1;     lo studente s era assente il giorno g
 *
 * calloc fa partire tutti da presenti (0): si segnano solo le assenze.
 *
 * Per ogni giorno si scrivono i numeri degli studenti assenti (da 1),
 * terminati da 0. Alla fine il programma stampa:
 *   - la tabella del mese (A assente, . presente);
 *   - le assenze di ogni studente, con un avviso sopra il 25% dei giorni
 *     (la soglia oltre la quale l'anno non è valido, se continua così);
 *   - il giorno con più assenti.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTI 30
#define MAX_GIORNI 25

int main(void)
{
    int *assente;
    int studenti;
    int giorni;
    int g;
    int s;
    int numero;
    int conta;
    int peggiore = 0;
    int assenti_peggiore = -1;
    int finito = 0;

    printf("Studenti e giorni di lezione: ");
    if (scanf("%d %d", &studenti, &giorni) != 2 || studenti < 1 || studenti > MAX_STUDENTI ||
        giorni < 1 || giorni > MAX_GIORNI) {
        printf("Dati non validi (studenti 1-%d, giorni 1-%d).\n", MAX_STUDENTI, MAX_GIORNI);
    } else {
        assente = calloc(giorni * studenti, sizeof *assente);
        if (assente == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            for (g = 0; g < giorni && !finito; g++) {
                printf("Giorno %d, assenti (0 per finire): ", g + 1);
                numero = -1;
                while (numero != 0 && !finito) {
                    if (scanf("%d", &numero) != 1) {
                        finito = 1;
                    } else if (numero < 0 || numero > studenti) {
                        printf("  studente %d inesistente\n", numero);
                    } else if (numero > 0) {
                        assente[g * studenti + numero - 1] = 1;
                    }
                }
            }

            printf("\n        ");
            for (g = 0; g < giorni; g++) {
                printf("%d", (g + 1) % 10);
            }
            printf("  assenze\n");
            for (s = 0; s < studenti; s++) {
                conta = 0;
                printf("stud %2d ", s + 1);
                for (g = 0; g < giorni; g++) {
                    printf("%c", assente[g * studenti + s] ? 'A' : '.');
                    conta = conta + assente[g * studenti + s];
                }
                printf("  %2d", conta);
                if (conta * 4 > giorni) {
                    printf("  oltre il 25%%");
                }
                printf("\n");
            }

            for (g = 0; g < giorni; g++) {
                conta = 0;
                for (s = 0; s < studenti; s++) {
                    conta = conta + assente[g * studenti + s];
                }
                if (conta > assenti_peggiore) {
                    assenti_peggiore = conta;
                    peggiore = g;
                }
            }
            printf("Giorno con piu' assenti: %d (%d su %d)\n", peggiore + 1, assenti_peggiore,
                   studenti);
            free(assente);
        }
    }

    return 0;
}
