/*
 * 080-problema-tariffe-parcheggio.c
 *
 * Parcheggio multipiano: quale tariffa conviene?
 *
 * Il parcheggio multipiano vicino alla scuola offre tre tariffe:
 *   - oraria:            1.50 euro per ogni ora iniziata;
 *   - prima ora gratis:  la prima ora è gratuita, poi 2.00 euro per ogni
 *                        ora iniziata;
 *   - giornaliera:       9.00 euro fissi, qualunque sia la durata.
 *
 * Ogni tariffa è una funzione che riceve i minuti di sosta e restituisce il
 * costo. Il tipo ha un nome:
 *
 *     typedef double (*Tariffa)(int minuti);
 *
 *     Tariffa piu_conveniente(int minuti, const Tariffa tariffe[], int n);
 *
 * piu_conveniente RESTITUISCE una funzione: quella con il costo più basso
 * per la durata indicata. Il main la chiama per conoscere il costo e,
 * confrontando il puntatore restituito con gli elementi della tabella,
 * ricava il nome della tariffa.
 *
 * Il programma legge la durata della sosta in minuti (0 termina) e stampa
 * il costo con ogni tariffa e quella più conveniente.
 */

#include <stdio.h>

#define TARIFFE 3

typedef double (*Tariffa)(int minuti);

double oraria(int minuti);
double prima_ora_gratis(int minuti);
double giornaliera(int minuti);
int ore_iniziate(int minuti);
Tariffa piu_conveniente(int minuti, const Tariffa tariffe[], int n);

int main(void)
{
    const char *nomi[TARIFFE] = {"oraria", "prima ora gratis", "giornaliera"};
    const Tariffa tariffe[TARIFFE] = {oraria, prima_ora_gratis, giornaliera};
    Tariffa migliore;
    int minuti = 1;
    int t;

    while (minuti != 0) {
        printf("Durata della sosta in minuti (0 per finire): ");
        if (scanf("%d", &minuti) != 1) {
            minuti = 0;
        }
        if (minuti > 0) {
            for (t = 0; t < TARIFFE; t++) {
                printf("  %-17s %5.2f euro\n", nomi[t], tariffe[t](minuti));
            }
            migliore = piu_conveniente(minuti, tariffe, TARIFFE);
            /* il nome si trova confrontando il puntatore con la tabella */
            t = 0;
            while (t < TARIFFE && tariffe[t] != migliore) {
                t++;
            }
            printf("  Conviene: %s (%.2f euro)\n", nomi[t], migliore(minuti));
        } else if (minuti < 0) {
            printf("  Durata non valida.\n");
            minuti = 1;
        }
    }

    return 0;
}

int ore_iniziate(int minuti)
{
    return (minuti + 59) / 60;
}

double oraria(int minuti)
{
    return 1.50 * ore_iniziate(minuti);
}

double prima_ora_gratis(int minuti)
{
    double costo = 0;

    if (minuti > 60) {
        costo = 2.00 * ore_iniziate(minuti - 60);
    }
    return costo;
}

/* Il prototipo deve essere quello di Tariffa anche se i minuti non servono. */
double giornaliera(int minuti)
{
    (void) minuti;
    return 9.00;
}

/* La tariffa con il costo più basso (la prima, a parità). */
Tariffa piu_conveniente(int minuti, const Tariffa tariffe[], int n)
{
    Tariffa scelta = tariffe[0];
    int i;

    for (i = 1; i < n; i++) {
        if (tariffe[i](minuti) < scelta(minuti)) {
            scelta = tariffe[i];
        }
    }
    return scelta;
}
