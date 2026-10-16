/*
 * 010-piu-file-aperti.c
 *
 * Più file aperti insieme: aprire tutto o niente
 *
 * Un programma può tenere aperti più file contemporaneamente, ognuno
 * con il suo FILE *. Il numero massimo garantito è FOPEN_MAX (definito
 * in <stdio.h>, almeno 8, compresi stdin, stdout e stderr); i sistemi
 * reali ne permettono molti di più.
 *
 * Quando servono tutti, conviene aprirli in un array e, se uno fallisce,
 * chiudere quelli già aperti prima di rinunciare:
 *
 *     aperti = 0
 *     finché aperti < n e l'ultima apertura è riuscita:
 *         f[aperti] = fopen(nomi[aperti], "w")
 *         se riuscita: aperti++
 *     se aperti < n:                 una apertura è fallita
 *         chiudi f[aperti - 1] ... f[0]
 *         aperti = 0
 *
 * Così il programma non lascia file aperti a metà né file vuoti creati
 * per niente (in questo esempio i file creati restano, ma vuoti: in
 * 030-rimuovere-e-rinominare si vedrà come toglierli).
 *
 * Il programma prepara i fogli di tre turni del laboratorio, poi ripete
 * il tentativo con un nome che punta a una cartella inesistente: la
 * terza apertura fallisce e le prime due vengono chiuse.
 */

#include <stdio.h>

#define TURNI 3

int apri_tutti(FILE *f[], const char *nomi[], int n);
void chiudi_tutti(FILE *f[], int n);

int main(void)
{
    const char *nomi[TURNI] = {"turno-1.txt", "turno-2.txt", "turno-3.txt"};
    const char *nomi_errati[TURNI] = {"turno-4.txt", "turno-5.txt", "inesistente/turno-6.txt"};
    FILE *f[TURNI];
    int aperti;
    int i;

    printf("FOPEN_MAX su questo sistema: %d\n\n", FOPEN_MAX);

    printf("Primo tentativo:\n");
    aperti = apri_tutti(f, nomi, TURNI);
    if (aperti == TURNI) {
        for (i = 0; i < TURNI; i++) {
            fprintf(f[i], "Laboratorio di informatica - turno %d\n", i + 1);
        }
        chiudi_tutti(f, aperti);
        printf("  scritti e chiusi %d file\n", TURNI);
    }

    printf("Secondo tentativo:\n");
    aperti = apri_tutti(f, nomi_errati, TURNI);
    if (aperti == 0) {
        printf("  nessun file aperto: il lavoro non viene fatto\n");
    }

    return 0;
}

/* Apre tutti i file in scrittura; se uno fallisce chiude gli altri e
   restituisce 0, altrimenti restituisce n. */
int apri_tutti(FILE *f[], const char *nomi[], int n)
{
    int aperti = 0;
    int ok = 1;

    while (aperti < n && ok) {
        f[aperti] = fopen(nomi[aperti], "w");
        ok = f[aperti] != NULL;
        if (ok) {
            printf("  aperto %s\n", nomi[aperti]);
            aperti++;
        } else {
            printf("  impossibile aprire %s\n", nomi[aperti]);
        }
    }
    if (!ok) {
        chiudi_tutti(f, aperti);
        aperti = 0;
    }
    return aperti;
}

/* Chiude i primi n file, dall'ultimo aperto al primo. */
void chiudi_tutti(FILE *f[], int n)
{
    int i;

    for (i = n - 1; i >= 0; i--) {
        fclose(f[i]);
        printf("  chiuso il file %d\n", i + 1);
    }
}
