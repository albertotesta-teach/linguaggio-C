/*
 * 070-problema-cronometro.c
 *
 * Gara di nuoto d'istituto: tempi in decimi di secondo
 *
 * Alla gara dei 100 metri stile libero il cronometrista legge per ogni
 * atleta minuti, secondi e decimi. Per confrontare i tempi conviene
 * trasformarli in un solo numero intero, i decimi di secondo:
 *
 *     typedef int Decimi;
 *     Decimi in_decimi(int minuti, int secondi, int decimi);
 *     void stampa_tempo(Decimi t);          formato 1'05"3
 *
 * Il programma legge i tempi dei cinque atleti, stampa il vincitore e, per
 * ognuno, il distacco dal migliore. Un tempo con secondi o decimi fuori
 * intervallo viene richiesto di nuovo.
 */

#include <stdio.h>

#define ATLETI 5

typedef int Decimi;

Decimi in_decimi(int minuti, int secondi, int decimi);
void stampa_tempo(Decimi t);

int main(void)
{
    const char *nomi[ATLETI] = {"Bianchi", "Esposito", "Ferrari", "Russo", "Colombo"};
    Decimi tempi[ATLETI];
    int minuti;
    int secondi;
    int decimi;
    int letti;
    int a = 0;
    int migliore = 0;

    while (a < ATLETI) {
        printf("Tempo di %-8s (minuti secondi decimi): ", nomi[a]);
        letti = scanf("%d %d %d", &minuti, &secondi, &decimi);
        if (letti != 3) {
            printf("  Inserimento interrotto.\n");
            a = ATLETI + 1;
        } else if (minuti < 0 || secondi < 0 || secondi > 59 || decimi < 0 || decimi > 9) {
            printf("  Tempo non valido, ripetere.\n");
        } else {
            tempi[a] = in_decimi(minuti, secondi, decimi);
            if (tempi[a] < tempi[migliore]) {
                migliore = a;
            }
            a++;
        }
    }

    if (a == ATLETI) {
        printf("\nVincitore: %s con ", nomi[migliore]);
        stampa_tempo(tempi[migliore]);
        printf("\n\n  Atleta     Tempo     Distacco\n");
        for (a = 0; a < ATLETI; a++) {
            printf("  %-9s ", nomi[a]);
            stampa_tempo(tempi[a]);
            printf("    +");
            stampa_tempo(tempi[a] - tempi[migliore]);
            printf("\n");
        }
    }

    return 0;
}

Decimi in_decimi(int minuti, int secondi, int decimi)
{
    return (minuti * 60 + secondi) * 10 + decimi;
}

/* Stampa t nel formato m'ss"d, ad esempio 1'05"3. */
void stampa_tempo(Decimi t)
{
    printf("%d'%02d\"%d", t / 600, t / 10 % 60, t % 10);
}
