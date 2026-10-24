/*
 * 060-problema-registro-del-giorno.c
 *
 * Un file per ogni giorno: il nome costruito dalla data
 *
 * Il docente della prima ora registra gli assenti in un file per
 * giorno, il cui nome si costruisce dalla data con sprintf:
 *
 *     sprintf(nome, "presenze-%02d-%02d.txt", giorno, mese);
 *                    -> "presenze-16-10.txt"
 *
 * Se il file del giorno esiste già (un collega ha già registrato
 * qualcuno), il programma chiede che cosa fare:
 *
 *     A  aggiungere in fondo      fopen(nome, "a")
 *     S  sovrascrivere            fopen(nome, "w")
 *     N  annullare                nessuna apertura
 *
 * Per sapere se esiste si prova ad aprirlo in lettura e, se riesce, lo
 * si richiude subito.
 *
 * Poi il programma legge i cognomi degli assenti fino a FINE, scrive
 * una riga "assente: cognome" per ciascuno, chiude il file e lo ristampa.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int data_valida(int giorno, int mese);
int esiste(const char *nome);
void stampa(const char *nome);

int main(void)
{
    FILE *registro = NULL;
    char nome[40];
    char cognome[30];
    char scelta = 'S';
    int giorno = 0;
    int mese = 0;
    int assenti = 0;
    int finito = 0;

    printf("Data (gg mm): ");
    if (scanf("%d %d", &giorno, &mese) != 2 || !data_valida(giorno, mese)) {
        printf("Data non valida.\n");
        scelta = 'N';
    } else {
        sprintf(nome, "presenze-%02d-%02d.txt", giorno, mese);
        if (esiste(nome)) {
            printf("%s esiste gia': A aggiungere, S sovrascrivere, N annullare? ", nome);
            if (scanf(" %c", &scelta) != 1) {
                scelta = 'N';
            }
            scelta = (char) toupper((unsigned char) scelta);
        }
    }
    if (scelta == 'A' || scelta == 'S') {
        registro = fopen(nome, scelta == 'A' ? "a" : "w");
        if (registro == NULL) {
            fprintf(stderr, "Impossibile aprire %s\n", nome);
        }
    } else if (scelta != 'N') {
        printf("Scelta non valida: nessuna modifica.\n");
    }

    if (registro != NULL) {
        printf("Assenti (FINE per terminare): ");
        while (!finito) {
            if (scanf("%29s", cognome) != 1 || strcmp(cognome, "FINE") == 0) {
                finito = 1;
            } else {
                fprintf(registro, "assente: %s\n", cognome);
                assenti++;
            }
        }
        fclose(registro);
        printf("Assenti registrati in %s: %d\n", nome, assenti);
        stampa(nome);
    } else if (scelta == 'N') {
        printf("Nessuna registrazione.\n");
    }

    return 0;
}

int data_valida(int giorno, int mese)
{
    const int giorni_mese[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return mese >= 1 && mese <= 12 && giorno >= 1 && giorno <= giorni_mese[mese];
}

int esiste(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int trovato = f != NULL;

    if (trovato) {
        fclose(f);
    }
    return trovato;
}

void stampa(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int c;

    if (f == NULL) {
        fprintf(stderr, "Impossibile leggere %s\n", nome);
    } else {
        printf("--- %s ---\n", nome);
        c = fgetc(f);
        while (c != EOF) {
            putchar(c);
            c = fgetc(f);
        }
        fclose(f);
    }
}
