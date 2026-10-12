/*
 * 080-problema-registro-assenze.c
 *
 * Registro elettronico: ore di assenza e limite per la validità dell'anno
 *
 * Per essere ammesso allo scrutinio finale uno studente non può superare
 * il 25% del monte ore annuale (1056 ore per la classe, quindi al massimo
 * 264 ore di assenza). A fine gennaio il coordinatore controlla la
 * situazione: per ogni studente il registro ha le ore di assenza di ogni
 * mese da settembre a gennaio.
 *
 *     typedef struct {
 *         char nome[20];
 *         int ore_assenza[MESI];
 *     } Studente;
 *
 * Il programma stampa la tabella con il totale di ogni studente, la
 * percentuale sulle ore di lezione svolte finora (ore_svolte[] per mese)
 * e una stima di fine anno, proiettando la stessa percentuale sul monte
 * ore annuale. Segnala:
 *   - "a rischio"   se la stima supera il limite;
 *   - "attenzione"  se la stima supera l'80% del limite.
 * Infine stampa il mese con più assenze per tutta la classe.
 */

#include <stdio.h>

#define STUDENTI   5
#define MESI       5
#define MONTE_ORE  1056
#define LIMITE     264

typedef struct {
    char nome[20];
    int ore_assenza[MESI];
} Studente;

int main(void)
{
    const char *mesi[MESI] = {"set", "ott", "nov", "dic", "gen"};
    int ore_svolte[MESI] = {64, 132, 128, 88, 104};
    Studente classe[STUDENTI] = {
        {"Amato Giada", {2, 6, 4, 3, 5}},
        {"Bellini Tommaso", {15, 34, 32, 24, 30}},
        {"Cattaneo Sofia", {0, 3, 2, 0, 1}},
        {"Donati Kevin", {12, 27, 25, 19, 24}},
        {"Longo Martina", {5, 11, 9, 7, 8}}
    };
    int totale_svolte = 0;
    int per_mese[MESI] = {0};
    int s;
    int m;
    int totale;
    double percentuale;
    double stima;
    int mese_max = 0;

    for (m = 0; m < MESI; m++) {
        totale_svolte = totale_svolte + ore_svolte[m];
    }

    printf("  %-16s", "Studente");
    for (m = 0; m < MESI; m++) {
        printf("%5s", mesi[m]);
    }
    printf("  Totale     %%   Stima\n");

    for (s = 0; s < STUDENTI; s++) {
        printf("  %-16s", classe[s].nome);
        totale = 0;
        for (m = 0; m < MESI; m++) {
            printf("%5d", classe[s].ore_assenza[m]);
            totale = totale + classe[s].ore_assenza[m];
            per_mese[m] = per_mese[m] + classe[s].ore_assenza[m];
        }
        percentuale = 100.0 * totale / totale_svolte;
        stima = percentuale / 100 * MONTE_ORE;
        printf("  %6d  %4.1f  %6.0f", totale, percentuale, stima);
        if (stima > LIMITE) {
            printf("  a rischio");
        } else if (stima > 0.8 * LIMITE) {
            printf("  attenzione");
        }
        printf("\n");
    }

    for (m = 1; m < MESI; m++) {
        if (per_mese[m] > per_mese[mese_max]) {
            mese_max = m;
        }
    }
    printf("\nOre di lezione svolte: %d su %d\n", totale_svolte, MONTE_ORE);
    printf("Mese con piu' assenze nella classe: %s (%d ore)\n", mesi[mese_max], per_mese[mese_max]);

    return 0;
}
