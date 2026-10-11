/*
 * 050-problema-posti-sul-treno.c
 *
 * Prenotazione di posti vicini su una carrozza
 *
 * Una carrozza ha POSTI posti numerati da 1 in fila; posti[i] vale 1 se il
 * posto è occupato, 0 se è libero. Un gruppo di k persone vuole sedersi in
 * posti consecutivi: il programma cerca il primo gruppo di k posti liberi
 * vicini, lo prenota e mostra la carrozza aggiornata.
 *
 * Funzioni:
 *   cerca_liberi(posti, n, k)  posizione del primo posto di k posti liberi
 *                              consecutivi, -1 se non ci sono
 *   occupa(inizio, fine)       segna occupati i posti da inizio (incluso)
 *                              a fine (escluso): si chiama con
 *                              occupa(posti + i, posti + i + k)
 *   stampa_carrozza(posti, n)
 *
 * Il programma legge il numero di persone di ogni gruppo; 0 termina.
 */

#include <stdio.h>

#define POSTI 20

int cerca_liberi(const int *posti, int n, int k);
void occupa(int *inizio, int *fine);
void stampa_carrozza(const int *posti, int n);

int main(void)
{
    int posti[POSTI] = {0, 1, 1, 0, 0, 0, 1, 0, 0, 1,
                        1, 1, 0, 0, 0, 0, 1, 0, 1, 1};
    int k = 1;
    int i;

    printf("=== PRENOTAZIONE POSTI VICINI ===\n");
    stampa_carrozza(posti, POSTI);

    while (k != 0) {
        printf("\nPersone nel gruppo (0 per finire): ");
        if (scanf("%d", &k) != 1) {
            k = 0;
        }

        if (k < 0 || k > POSTI) {
            printf("  Numero non valido.\n");
        } else if (k > 0) {
            i = cerca_liberi(posti, POSTI, k);
            if (i == -1) {
                printf("  Nessun gruppo di %d posti vicini libero.\n", k);
            } else {
                occupa(posti + i, posti + i + k);
                if (k == 1) {
                    printf("  Prenotato il posto %d.\n", i + 1);
                } else {
                    printf("  Prenotati i posti dal %d al %d.\n", i + 1, i + k);
                }
                stampa_carrozza(posti, POSTI);
            }
        }
    }

    return 0;
}

/* Scorre i posti contando quelli liberi consecutivi; quando il conteggio
 * arriva a k la ricerca termina. */
int cerca_liberi(const int *posti, int n, int k)
{
    const int *p;
    int consecutivi = 0;
    int trovato = -1;

    for (p = posti; p < posti + n && trovato == -1; p++) {
        if (*p == 0) {
            consecutivi++;
        } else {
            consecutivi = 0;
        }
        if (consecutivi == k) {
            trovato = (p - posti) - k + 1;
        }
    }
    return trovato;
}

/* Segna occupati i posti nell'intervallo [inizio, fine). */
void occupa(int *inizio, int *fine)
{
    int *p;

    for (p = inizio; p < fine; p++) {
        *p = 1;
    }
}

/* Stampa il numero dei posti liberi e XX per quelli occupati. */
void stampa_carrozza(const int *posti, int n)
{
    int i;
    int liberi = 0;

    printf("  ");
    for (i = 0; i < n; i++) {
        if (posti[i] == 0) {
            printf("[%2d]", i + 1);
            liberi++;
        } else {
            printf("[XX]");
        }
    }
    printf("\n  Posti liberi: %d su %d\n", liberi, n);
}
