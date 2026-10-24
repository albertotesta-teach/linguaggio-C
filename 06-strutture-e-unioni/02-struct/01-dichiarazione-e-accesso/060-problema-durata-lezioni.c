/*
 * 060-problema-durata-lezioni.c
 *
 * Orario scolastico: la durata delle lezioni di una giornata
 *
 * La segreteria controlla l'orario provvisorio di una classe: per ogni
 * lezione si inseriscono l'ora di inizio e quella di fine. Un orario è
 * fatto di ore e minuti:
 *
 *     typedef struct {
 *         int ore;
 *         int minuti;
 *     } Orario;
 *
 * Per ogni lezione il programma
 *   - controlla che i due orari siano validi (ore 0-23, minuti 0-59) e che
 *     la fine venga dopo l'inizio;
 *   - calcola la durata in minuti contando i minuti dalla mezzanotte;
 *   - segnala le lezioni più lunghe di 60 minuti o più corte di 50;
 *   - segnala una lezione che inizia prima della fine della precedente.
 * Alla fine stampa il tempo totale di lezione. Un inizio "0 0" termina.
 */

#include <stdio.h>

#define DURATA_MINIMA  50
#define DURATA_MASSIMA 60

typedef struct {
    int ore;
    int minuti;
} Orario;

int valido(int ore, int minuti);
void svuota_riga(void);

int main(void)
{
    Orario inizio = {1, 0};
    Orario fine = {0, 0};
    Orario fine_precedente = {0, 0};
    int da_mezzanotte_inizio;
    int da_mezzanotte_fine;
    int durata;
    int totale = 0;
    int lezione = 1;
    int letti;

    while (!(inizio.ore == 0 && inizio.minuti == 0)) {
        printf("Lezione %d - inizio (ore minuti, 0 0 per finire): ", lezione);
        letti = scanf("%d %d", &inizio.ore, &inizio.minuti);
        if (letti == EOF) {
            inizio.ore = 0;             /* input terminato: come 0 0 */
            inizio.minuti = 0;
        } else if (letti != 2) {
            svuota_riga();              /* non sono due numeri */
            printf("  Orario non valido.\n");
            inizio.ore = -1;            /* non e' la richiesta di fine */
        } else if (!(inizio.ore == 0 && inizio.minuti == 0)) {
            printf("Lezione %d - fine   (ore minuti): ", lezione);
            letti = scanf("%d %d", &fine.ore, &fine.minuti);
            if (letti != 2) {
                if (letti != EOF) {
                    svuota_riga();      /* non sono due numeri */
                }
                fine.ore = -1;          /* orario non valido */
            }
            da_mezzanotte_inizio = inizio.ore * 60 + inizio.minuti;
            da_mezzanotte_fine = fine.ore * 60 + fine.minuti;
            if (!valido(inizio.ore, inizio.minuti) || !valido(fine.ore, fine.minuti)) {
                printf("  Orario non valido.\n");
            } else if (da_mezzanotte_fine <= da_mezzanotte_inizio) {
                printf("  La fine deve venire dopo l'inizio.\n");
            } else {
                durata = da_mezzanotte_fine - da_mezzanotte_inizio;
                printf("  %02d:%02d - %02d:%02d  %d minuti", inizio.ore, inizio.minuti,
                       fine.ore, fine.minuti, durata);
                if (durata > DURATA_MASSIMA) {
                    printf("  (troppo lunga)");
                } else if (durata < DURATA_MINIMA) {
                    printf("  (troppo corta)");
                }
                if (da_mezzanotte_inizio < fine_precedente.ore * 60 + fine_precedente.minuti) {
                    printf("  (si sovrappone alla precedente)");
                }
                printf("\n");
                totale = totale + durata;
                fine_precedente.ore = fine.ore;
                fine_precedente.minuti = fine.minuti;
                lezione++;
            }
        }
    }
    printf("Lezioni registrate: %d, tempo totale %d h %02d min\n", lezione - 1, totale / 60, totale % 60);

    return 0;
}

int valido(int ore, int minuti)
{
    return ore >= 0 && ore <= 23 && minuti >= 0 && minuti <= 59;
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
