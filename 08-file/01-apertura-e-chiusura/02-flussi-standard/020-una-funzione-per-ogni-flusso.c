/*
 * 020-una-funzione-per-ogni-flusso.c
 *
 * Una funzione che scrive su qualsiasi flusso
 *
 * Se una funzione riceve il FILE * come parametro, lo stesso codice
 * scrive a video o su file a seconda di chi la chiama:
 *
 *     void stampa_orario(FILE *f);
 *
 *     stampa_orario(stdout);      a video
 *     stampa_orario(file);        nel file aperto con fopen
 *
 * Dentro la funzione si usano solo fprintf, fputs e fputc con il
 * parametro f, mai printf: printf scriverebbe sempre a video.
 *
 * La funzione non apre e non chiude il flusso: lo fa chi la chiama.
 * Chiudere stdout dentro la funzione impedirebbe al programma di
 * scrivere ancora a video.
 *
 * Il programma stampa l'orario settimanale della classe a video, lo
 * salva in orario.txt e rilegge il file per mostrare che è identico.
 */

#include <stdio.h>

#define GIORNI 5
#define ORE 5

void stampa_orario(FILE *f, const char *classe);
void ricopia(const char *nome);

int main(void)
{
    FILE *f;

    printf("A video:\n");
    stampa_orario(stdout, "4B Informatica");

    f = fopen("orario.txt", "w");
    if (f == NULL) {
        fprintf(stderr, "Impossibile creare orario.txt\n");
    } else {
        stampa_orario(f, "4B Informatica");
        fclose(f);
        printf("\nSalvato in orario.txt; il file contiene:\n");
        ricopia("orario.txt");
    }

    return 0;
}

void stampa_orario(FILE *f, const char *classe)
{
    const char *giorni[GIORNI] = {"Lun", "Mar", "Mer", "Gio", "Ven"};
    const char *materie[GIORNI][ORE] = {
        {"Ita", "Ita", "Mat", "Inf", "Inf"},
        {"Ing", "Mat", "Sto", "Sis", "Sis"},
        {"Inf", "Inf", "Inf", "Ita", "Mot"},
        {"Mat", "Mat", "Ing", "Tps", "Tps"},
        {"Sis", "Ita", "Ing", "Mat", "Rel"}
    };
    int g;
    int o;

    fprintf(f, "Orario della classe %s\n", classe);
    fputs("    ", f);
    for (o = 0; o < ORE; o++) {
        fprintf(f, "   %d^", o + 1);
    }
    fputc('\n', f);
    for (g = 0; g < GIORNI; g++) {
        fprintf(f, "%-4s", giorni[g]);
        for (o = 0; o < ORE; o++) {
            fprintf(f, "  %s", materie[g][o]);
        }
        fputc('\n', f);
    }
}

void ricopia(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int c;

    if (f == NULL) {
        fprintf(stderr, "Impossibile leggere %s\n", nome);
    } else {
        c = fgetc(f);
        while (c != EOF) {
            putchar(c);
            c = fgetc(f);
        }
        fclose(f);
    }
}
