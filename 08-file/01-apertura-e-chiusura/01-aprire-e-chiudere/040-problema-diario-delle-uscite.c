/*
 * 040-problema-diario-delle-uscite.c
 *
 * Il diario delle uscite didattiche: un file che cresce a ogni esecuzione
 *
 * Il coordinatore annota le uscite didattiche della classe man mano che
 * si svolgono. Il diario è il file diario.txt, una riga per uscita:
 *
 *     12/10 Museo Egizio di Torino
 *     03/11 Laboratorio di chimica all'universita'
 *
 * Il file si apre in modalità "a": ogni esecuzione AGGIUNGE le nuove
 * voci in fondo senza toccare quelle già scritte. Se il file non
 * esiste ancora, "a" lo crea. Con "w" ogni esecuzione cancellerebbe
 * il diario.
 *
 * Il programma legge da tastiera una riga "gg/mm meta" alla volta (la
 * meta può contenere spazi) fino a FINE, scarta le righe senza meta e le
 * date non valide, chiude il file e lo
 * riapre in lettura per stampare tutto il diario con le righe numerate.
 */

#include <stdio.h>
#include <string.h>

int data_valida(int giorno, int mese);
int stampa_numerata(const char *nome);

int main(void)
{
    FILE *diario;
    char riga[100];
    char data[16];
    char meta[60];
    int giorno;
    int mese;
    char extra;
    int campi;
    int resto;
    int aggiunte = 0;
    int finito = 0;

    diario = fopen("diario.txt", "a");
    if (diario == NULL) {
        fprintf(stderr, "Impossibile aprire diario.txt\n");
        finito = 1;
    } else {
        printf("Uscite (gg/mm meta, FINE per terminare):\n");
    }
    while (!finito) {
        if (fgets(riga, sizeof riga, stdin) == NULL) {
            finito = 1;
        } else {
            if (strchr(riga, '\n') == NULL) {
                /* riga troppo lunga: si scarta il resto */
                resto = getchar();
                while (resto != '\n' && resto != EOF) {
                    resto = getchar();
                }
            }
            campi = sscanf(riga, "%15s %59[^\n]", data, meta);
            if (campi >= 1 && strcmp(data, "FINE") == 0) {
                finito = 1;
            } else if (campi == 1) {
                printf("  manca la meta: %s\n", data);
            } else if (campi == 2) {
                /* extra: la data deve finire subito dopo il mese */
                if (sscanf(data, "%d/%d%c", &giorno, &mese, &extra) != 2 ||
                    !data_valida(giorno, mese)) {
                    printf("  data non valida: %s\n", data);
                } else {
                    fprintf(diario, "%02d/%02d %s\n", giorno, mese, meta);
                    aggiunte++;
                }
            }
            /* campi < 1: riga vuota, ignorata */
        }
    }
    if (diario != NULL) {
        fclose(diario);
        printf("Voci aggiunte: %d\n\nDiario delle uscite:\n", aggiunte);
        if (!stampa_numerata("diario.txt")) {
            fprintf(stderr, "Impossibile leggere diario.txt\n");
        }
    }

    return 0;
}

int data_valida(int giorno, int mese)
{
    const int giorni_mese[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return mese >= 1 && mese <= 12 && giorno >= 1 && giorno <= giorni_mese[mese];
}

/* Stampa il file con il numero davanti a ogni riga; 0 se non si apre. */
int stampa_numerata(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int ok = f != NULL;
    int riga = 0;
    int inizio_riga = 1;
    int c;

    if (ok) {
        c = fgetc(f);
        while (c != EOF) {
            if (inizio_riga) {
                riga++;
                printf("%3d. ", riga);
            }
            putchar(c);
            inizio_riga = c == '\n';
            c = fgetc(f);
        }
        fclose(f);
    }
    return ok;
}
