/*
 * 080-problema-rapporto-multiplo.c
 *
 * Lo stesso rapporto a video, in un file nuovo e in coda a uno storico
 *
 * Ogni venerdì le classi pesano la carta raccolta per la differenziata.
 * Il referente ambientale inserisce la settimana e i chili di ciascuna
 * classe, e il rapporto va in tre posti:
 *
 *     stdout                       per controllarlo subito
 *     carta-settimana-NN.txt "w"   il rapporto completo della settimana
 *     storico-carta.txt      "a"   una sola riga di riepilogo, in coda
 *
 * Il rapporto completo è scritto da una funzione che riceve il flusso,
 * chiamata due volte; la riga dello storico ha un formato più compatto,
 * adatto a essere letta da un altro programma:
 *
 *     settimana 7: 4 classi, 31.5 kg, migliore 3B
 *
 * Alla fine il programma ristampa lo storico, che cresce di una riga a
 * ogni esecuzione.
 */

#include <stdio.h>
#include <string.h>

#define CLASSI 10

void stampa_rapporto(FILE *f, int settimana, char classi[][8], const double kg[], int n);
void ricopia(const char *nome);

int main(void)
{
    char classi[CLASSI][8];
    double kg[CLASSI];
    char nome_file[40];
    FILE *rapporto;
    FILE *storico;
    double totale = 0;
    int settimana = 0;
    int migliore = 0;
    int n = 0;
    int finito = 0;
    int letti;
    int i;

    printf("Settimana: ");
    if (scanf("%d", &settimana) != 1 || settimana < 1 || settimana > 53) {
        printf("Settimana non valida.\n");
        finito = 1;
    } else {
        printf("Classe e chili di carta (FINE per terminare):\n");
    }
    while (!finito && n < CLASSI) {
        if (scanf("%7s", classi[n]) != 1 || strcmp(classi[n], "FINE") == 0) {
            finito = 1;
        } else {
            letti = scanf("%lf", &kg[n]);
            if (letti == EOF) {
                printf("  mancano i chili di %s\n", classi[n]);
                finito = 1;
            } else if (letti == 0 || kg[n] < 0) {
                printf("  chili non validi per %s: classe scartata\n", classi[n]);
                if (letti == 0) {
                    scanf("%*s");   /* si scarta il valore non numerico */
                }
            } else {
                n++;
            }
        }
    }
    if (!finito) {
        printf("  raggiunto il massimo di %d classi\n", CLASSI);
    }

    if (n > 0) {
        for (i = 0; i < n; i++) {
            totale += kg[i];
            if (kg[i] > kg[migliore]) {
                migliore = i;
            }
        }
        printf("\n");
        stampa_rapporto(stdout, settimana, classi, kg, n);

        sprintf(nome_file, "carta-settimana-%02d.txt", settimana);
        rapporto = fopen(nome_file, "w");
        if (rapporto == NULL) {
            fprintf(stderr, "Impossibile creare %s\n", nome_file);
        } else {
            stampa_rapporto(rapporto, settimana, classi, kg, n);
            fclose(rapporto);
            printf("\nRapporto salvato in %s\n", nome_file);
        }

        storico = fopen("storico-carta.txt", "a");
        if (storico == NULL) {
            fprintf(stderr, "Impossibile aprire storico-carta.txt\n");
        } else {
            fprintf(storico, "settimana %d: %d %s, %.1f kg, migliore %s\n", settimana, n,
                    n == 1 ? "classe" : "classi", totale, classi[migliore]);
            fclose(storico);
            printf("Storico aggiornato:\n");
            ricopia("storico-carta.txt");
        }
    } else if (settimana >= 1 && settimana <= 53) {
        printf("Nessuna classe inserita.\n");
    }

    return 0;
}

void stampa_rapporto(FILE *f, int settimana, char classi[][8], const double kg[], int n)
{
    double totale = 0;
    int i;

    fprintf(f, "Raccolta della carta - settimana %d\n", settimana);
    for (i = 0; i < n; i++) {
        fprintf(f, "  %-6s %6.1f kg\n", classi[i], kg[i]);
        totale += kg[i];
    }
    fprintf(f, "  %-6s %6.1f kg (media %.1f kg per classe)\n", "Totale", totale, totale / n);
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
