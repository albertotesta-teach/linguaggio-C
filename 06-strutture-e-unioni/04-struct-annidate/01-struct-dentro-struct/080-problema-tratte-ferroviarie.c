/*
 * 080-problema-tratte-ferroviarie.c
 *
 * Gita a Milano: il collegamento che arriva prima, anche con un cambio
 *
 * Gli orari dei treni del mattino sono un elenco di tratte. Ogni tratta
 * ha un treno e due fermate; ogni fermata ha una stazione e un orario:
 *
 *     typedef struct {
 *         char stazione[16];
 *         Orario ora;
 *     } Fermata;
 *
 *     typedef struct {
 *         char treno[10];
 *         Fermata partenza;
 *         Fermata arrivo;
 *     } Tratta;
 *
 * Tre livelli: t.partenza.ora.ore è l'ora di partenza della tratta t.
 *
 * Il programma legge "stazione_di_partenza destinazione hh:mm" e cerca il
 * collegamento che arriva prima, partendo non prima dell'orario dato:
 *   - una tratta diretta;
 *   - oppure due tratte con un cambio nella stessa stazione, lasciando
 *     almeno 5 minuti tra l'arrivo del primo treno e la partenza del
 *     secondo.
 * A parità di arrivo vince il collegamento che parte più tardi, cioè il
 * più breve. Stampa il percorso e la durata totale. FINE termina.
 */

#include <stdio.h>
#include <string.h>

#define TRATTE 7
#define CAMBIO 5
#define LUNG 16

typedef struct {
    int ore;
    int minuti;
} Orario;

typedef struct {
    char stazione[LUNG];
    Orario ora;
} Fermata;

typedef struct {
    char treno[10];
    Fermata partenza;
    Fermata arrivo;
} Tratta;

int in_minuti(Orario o);
int migliore(int arrivo, int partenza, int arrivo_migliore, int partenza_migliore);
void svuota_riga(void);

int main(void)
{
    Tratta orario[TRATTE] = {
        {"R 10301", {"Alessandria", {6, 50}}, {"Pavia", {7, 45}}},
        {"R 10201", {"Alessandria", {7, 5}}, {"Tortona", {7, 25}}},
        {"RV 2201", {"Tortona", {7, 32}}, {"Milano", {8, 30}}},
        {"R 2405", {"Pavia", {7, 55}}, {"Milano", {8, 30}}},
        {"R 10203", {"Alessandria", {7, 40}}, {"Tortona", {8, 0}}},
        {"RV 2203", {"Tortona", {8, 10}}, {"Milano", {9, 5}}},
        {"RV 2101", {"Alessandria", {8, 15}}, {"Milano", {9, 30}}}
    };
    char da[LUNG];
    char a[LUNG];
    Orario dalle;
    int primo;
    int secondo;
    int migliore_primo;
    int migliore_secondo;
    int arrivo_migliore;
    int partenza_migliore;
    int arrivo;
    int partenza;
    int durata;
    int finito = 0;

    while (!finito) {
        printf("Viaggio (partenza destinazione hh:mm, FINE): ");
        if (scanf("%15s", da) != 1 || strcmp(da, "FINE") == 0) {
            finito = 1;
        } else if (scanf("%15s %d:%d", a, &dalle.ore, &dalle.minuti) != 3 || dalle.ore < 0 ||
                   dalle.ore > 23 || dalle.minuti < 0 || dalle.minuti > 59) {
            printf("  Richiesta non valida.\n");
        } else {
            migliore_primo = -1;
            migliore_secondo = -1;
            arrivo_migliore = 24 * 60;
            partenza_migliore = 0;
            for (primo = 0; primo < TRATTE; primo++) {
                if (strcmp(orario[primo].partenza.stazione, da) == 0 &&
                    in_minuti(orario[primo].partenza.ora) >= in_minuti(dalle)) {
                    partenza = in_minuti(orario[primo].partenza.ora);
                    /* tratta diretta */
                    arrivo = in_minuti(orario[primo].arrivo.ora);
                    if (strcmp(orario[primo].arrivo.stazione, a) == 0 &&
                        migliore(arrivo, partenza, arrivo_migliore, partenza_migliore)) {
                        arrivo_migliore = arrivo;
                        partenza_migliore = partenza;
                        migliore_primo = primo;
                        migliore_secondo = -1;
                    }
                    /* seconda tratta dalla stazione dove arriva la prima */
                    for (secondo = 0; secondo < TRATTE; secondo++) {
                        arrivo = in_minuti(orario[secondo].arrivo.ora);
                        if (strcmp(orario[secondo].partenza.stazione,
                                   orario[primo].arrivo.stazione) == 0 &&
                            strcmp(orario[secondo].arrivo.stazione, a) == 0 &&
                            in_minuti(orario[secondo].partenza.ora) >=
                                in_minuti(orario[primo].arrivo.ora) + CAMBIO &&
                            migliore(arrivo, partenza, arrivo_migliore, partenza_migliore)) {
                            arrivo_migliore = arrivo;
                            partenza_migliore = partenza;
                            migliore_primo = primo;
                            migliore_secondo = secondo;
                        }
                    }
                }
            }
            if (migliore_primo == -1) {
                printf("  Nessun collegamento da %s a %s dopo le %02d:%02d.\n", da, a, dalle.ore,
                       dalle.minuti);
            } else {
                printf("  %-8s %s %02d:%02d -> %s %02d:%02d\n", orario[migliore_primo].treno,
                       orario[migliore_primo].partenza.stazione,
                       orario[migliore_primo].partenza.ora.ore,
                       orario[migliore_primo].partenza.ora.minuti,
                       orario[migliore_primo].arrivo.stazione,
                       orario[migliore_primo].arrivo.ora.ore,
                       orario[migliore_primo].arrivo.ora.minuti);
                if (migliore_secondo != -1) {
                    printf("  %-8s %s %02d:%02d -> %s %02d:%02d\n", orario[migliore_secondo].treno,
                           orario[migliore_secondo].partenza.stazione,
                           orario[migliore_secondo].partenza.ora.ore,
                           orario[migliore_secondo].partenza.ora.minuti,
                           orario[migliore_secondo].arrivo.stazione,
                           orario[migliore_secondo].arrivo.ora.ore,
                           orario[migliore_secondo].arrivo.ora.minuti);
                }
                durata = arrivo_migliore - partenza_migliore;
                printf("  Arrivo alle %02d:%02d, durata %d h %02d min, %s\n", arrivo_migliore / 60,
                       arrivo_migliore % 60, durata / 60, durata % 60,
                       migliore_secondo == -1 ? "diretto" : "con un cambio");
            }
        }
        if (!finito) {
            svuota_riga();              /* una richiesta per riga */
        }
    }

    return 0;
}

int in_minuti(Orario o)
{
    return o.ore * 60 + o.minuti;
}

/* 1 se il nuovo collegamento arriva prima o, a pari arrivo, parte dopo. */
int migliore(int arrivo, int partenza, int arrivo_migliore, int partenza_migliore)
{
    return arrivo < arrivo_migliore ||
           (arrivo == arrivo_migliore && partenza > partenza_migliore);
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
