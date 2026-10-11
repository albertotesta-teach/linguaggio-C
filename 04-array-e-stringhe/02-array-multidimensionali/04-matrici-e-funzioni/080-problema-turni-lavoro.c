/*
 * 080-problema-turni-lavoro.c
 *
 * Pianificazione settimanale dei turni di un bar
 *
 * Il titolare di un bar pianifica le ore di 5 dipendenti nei 7 giorni
 * della settimana: la matrice ore[DIPENDENTI][GIORNI] contiene le ore di
 * lavoro previste (0 = riposo). Ogni dipendente ha un contratto con un
 * numero di ore settimanali (array parallelo alle righe); ogni giorno
 * servono almeno MIN_PERSONE dipendenti in servizio.
 *
 * Il programma verifica la pianificazione:
 *   - ore settimanali di ogni dipendente rispetto al contratto
 *     (in linea, straordinario, ore mancanti);
 *   - giorni di riposo: ognuno deve averne almeno 1;
 *   - per ogni giorno, persone in servizio e ore totali; segnala i giorni
 *     scoperti (meno di MIN_PERSONE).
 *
 * Funzioni:
 *   ore_settimanali(ore, d)      somma della riga d
 *   giorni_riposo(ore, d)        zeri nella riga d
 *   persone_in_servizio(ore, g)  celle non nulle nella colonna g
 *   ore_giorno(ore, g)           somma della colonna g
 */

#include <stdio.h>

#define DIPENDENTI 5
#define GIORNI     7
#define LUNG       12
#define MIN_PERSONE 3
#define MIN_RIPOSI  1

int ore_settimanali(const int ore[][GIORNI], int d);
int giorni_riposo(const int ore[][GIORNI], int d);
int persone_in_servizio(const int ore[][GIORNI], int g);
int ore_giorno(const int ore[][GIORNI], int g);

int main(void)
{
    int ore[DIPENDENTI][GIORNI] = {
        {8, 8, 0, 8, 8, 8, 0},
        {6, 6, 6, 6, 0, 6, 6},
        {0, 4, 4, 4, 0, 8, 8},
        {8, 8, 8, 8, 8, 4, 4},
        {4, 4, 4, 0, 0, 4, 0}
    };
    char nomi[DIPENDENTI][LUNG] = {"Marco", "Giulia", "Ahmed", "Sofia", "Luca"};
    int contratto[DIPENDENTI] = {40, 36, 30, 40, 20};
    char giorni[GIORNI][4] = {"Lun", "Mar", "Mer", "Gio", "Ven", "Sab", "Dom"};

    int d;
    int g;
    int totale;
    int riposi;
    int persone;

    /* ── 1. Tabella dei turni ─────────────────────────────────────── */
    printf("=== TURNI DELLA SETTIMANA (ore) ===\n\n");
    printf("  %-8s", "");
    for (g = 0; g < GIORNI; g++) {
        printf("%5s", giorni[g]);
    }
    printf("  Totale Contratto\n");

    for (d = 0; d < DIPENDENTI; d++) {
        printf("  %-8s", nomi[d]);
        for (g = 0; g < GIORNI; g++) {
            if (ore[d][g] == 0) {
                printf("%5s", "-");
            } else {
                printf("%5d", ore[d][g]);
            }
        }
        printf("%8d%10d\n", ore_settimanali(ore, d), contratto[d]);
    }

    /* ── 2. Verifica per dipendente ───────────────────────────────── */
    printf("\n--- Verifica per dipendente ---\n");
    for (d = 0; d < DIPENDENTI; d++) {
        totale = ore_settimanali(ore, d);
        riposi = giorni_riposo(ore, d);

        printf("  %-8s", nomi[d]);
        if (totale == contratto[d]) {
            printf("ore in linea con il contratto");
        } else if (totale > contratto[d]) {
            printf("%d ore di straordinario", totale - contratto[d]);
        } else {
            printf("mancano %d ore", contratto[d] - totale);
        }
        printf(", %d %s di riposo", riposi, riposi == 1 ? "giorno" : "giorni");
        if (riposi < MIN_RIPOSI) {
            printf("  <- NESSUN RIPOSO");
        }
        printf("\n");
    }

    /* ── 3. Copertura dei giorni ──────────────────────────────────── */
    printf("\n--- Copertura giornaliera (minimo %d persone) ---\n", MIN_PERSONE);
    for (g = 0; g < GIORNI; g++) {
        persone = persone_in_servizio(ore, g);
        printf("  %s: %d persone, %2d ore", giorni[g], persone, ore_giorno(ore, g));
        if (persone < MIN_PERSONE) {
            printf("  <- SCOPERTO");
        }
        printf("\n");
    }

    return 0;
}

int ore_settimanali(const int ore[][GIORNI], int d)
{
    int g;
    int totale = 0;

    for (g = 0; g < GIORNI; g++) {
        totale = totale + ore[d][g];
    }
    return totale;
}

int giorni_riposo(const int ore[][GIORNI], int d)
{
    int g;
    int riposi = 0;

    for (g = 0; g < GIORNI; g++) {
        if (ore[d][g] == 0) {
            riposi++;
        }
    }
    return riposi;
}

int persone_in_servizio(const int ore[][GIORNI], int g)
{
    int d;
    int persone = 0;

    for (d = 0; d < DIPENDENTI; d++) {
        if (ore[d][g] > 0) {
            persone++;
        }
    }
    return persone;
}

int ore_giorno(const int ore[][GIORNI], int g)
{
    int d;
    int totale = 0;

    for (d = 0; d < DIPENDENTI; d++) {
        totale = totale + ore[d][g];
    }
    return totale;
}
