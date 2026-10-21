/*
 * 050-problema-prossimo-treno.c
 *
 * Tabellone della stazione: i prossimi treni
 *
 * Gli orari di partenza dei treni per il capoluogo sono memorizzati in
 * ordine crescente, in minuti dalla mezzanotte. Lo studente pendolare
 * inserisce l'ora attuale e il programma mostra il prossimo treno e i due
 * successivi, con l'attesa in minuti.
 *
 * prossimo(orari, n, adesso) restituisce il puntatore al primo orario non
 * precedente all'ora attuale, NULL se i treni della giornata sono finiti.
 * A partire da quel puntatore i treni successivi sono p + 1 e p + 2, ma
 * solo se non si supera la fine dell'array.
 *
 * Il programma legge orari hh:mm; un input non valido (ad esempio "q")
 * termina.
 */

#include <stdio.h>

#define TRENI 9
#define MOSTRATI 3

const int *prossimo(const int *orari, int n, int adesso);
void stampa_orario(int minuti);

int main(void)
{
    int orari[TRENI] = {6 * 60 + 12, 6 * 60 + 47, 7 * 60 + 15, 7 * 60 + 40,
                        8 * 60 + 25, 12 * 60 + 5, 13 * 60 + 35, 17 * 60 + 50,
                        21 * 60 + 10};
    const int *fine = orari + TRENI;
    const int *p;
    const int *q;
    int ore;
    int minuti;
    int adesso;

    printf("=== PROSSIME PARTENZE ===\n");
    printf("Ora attuale (hh:mm, q per finire): ");
    while (scanf("%d:%d", &ore, &minuti) == 2) {
        if (ore < 0 || ore > 23 || minuti < 0 || minuti > 59) {
            printf("  Ora non valida.\n");
        } else {
            adesso = ore * 60 + minuti;
            printf("  Dalle ");
            stampa_orario(adesso);
            p = prossimo(orari, TRENI, adesso);
            if (p == NULL) {
                printf(": nessun treno fino a domani, primo alle ");
                stampa_orario(orari[0]);
                printf("\n");
            } else {
                printf(":");
                for (q = p; q < fine && q < p + MOSTRATI; q++) {
                    printf("  ");
                    stampa_orario(*q);
                    if (*q == adesso) {
                        printf(" (in partenza)");
                    } else {
                        printf(" (tra %d min)", *q - adesso);
                    }
                }
                printf("\n");
            }
        }
        printf("Ora attuale (hh:mm, q per finire): ");
    }
    printf("\n");

    return 0;
}

/* Primo orario >= adesso, NULL se non ce ne sono. orari è crescente. */
const int *prossimo(const int *orari, int n, int adesso)
{
    const int *p = orari;

    while (p < orari + n && *p < adesso) {
        p++;
    }
    return p < orari + n ? p : NULL;
}

void stampa_orario(int minuti)
{
    printf("%02d:%02d", minuti / 60, minuti % 60);
}
