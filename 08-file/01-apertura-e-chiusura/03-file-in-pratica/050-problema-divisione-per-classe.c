/*
 * 050-problema-divisione-per-classe.c
 *
 * Smistare un elenco in un file per classe
 *
 * Gli iscritti al corso di primo soccorso arrivano in un unico elenco,
 * una riga "classe cognome" per studente, in ordine sparso. Ogni
 * coordinatore vuole il file della propria classe: classe-3A.txt,
 * classe-4B.txt, ...
 *
 * Il programma tiene aperti INSIEME tutti i file delle classi incontrate:
 *
 *     classi[k]   "3A"                il nome della classe
 *     file[k]     FILE * aperto in "w"
 *     conta[k]    iscritti scritti nel file
 *
 * Per ogni riga si cerca la classe; se è nuova si apre il suo file e
 * la si aggiunge. Alla fine si chiudono tutti i file aperti.
 *
 * Il numero di classi è limitato dalla dimensione degli array (MAX_CLASSI)
 * e, in generale, da quanti file il sistema permette di aprire insieme
 * (almeno FOPEN_MAX). Se l'apertura del file di una classe fallisce, le
 * righe di quella classe vengono scartate con un messaggio su stderr.
 *
 * Alla fine il programma stampa il riepilogo e il contenuto dei file.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CLASSI 8

int cerca(char classi[][8], int n, const char *classe);
void ricopia(const char *nome);

int main(void)
{
    char classi[MAX_CLASSI][8];
    FILE *file[MAX_CLASSI];
    int conta[MAX_CLASSI];
    char classe[8];
    char cognome[30];
    char nome_file[30];
    int n = 0;
    int k;
    int scartati = 0;
    int finito = 0;
    int i;

    printf("Iscritti (classe cognome, FINE per terminare):\n");
    while (!finito) {
        if (scanf("%7s", classe) != 1 || strcmp(classe, "FINE") == 0) {
            finito = 1;
        } else if (scanf("%29s", cognome) != 1) {
            finito = 1;
        } else {
            /* 3a e 3A sono la stessa classe */
            for (i = 0; classe[i] != '\0'; i++) {
                classe[i] = (char) toupper((unsigned char) classe[i]);
            }
            k = cerca(classi, n, classe);
            if (k == -1 && n < MAX_CLASSI) {
                sprintf(nome_file, "classe-%s.txt", classe);
                file[n] = fopen(nome_file, "w");
                if (file[n] == NULL) {
                    fprintf(stderr, "  impossibile creare %s\n", nome_file);
                } else {
                    strcpy(classi[n], classe);
                    conta[n] = 0;
                    k = n;
                    n++;
                }
            }
            if (k == -1) {
                fprintf(stderr, "  scartato %s (%s)\n", cognome, classe);
                scartati++;
            } else {
                fprintf(file[k], "%s\n", cognome);
                conta[k]++;
            }
        }
    }
    for (k = 0; k < n; k++) {
        fclose(file[k]);
    }

    printf("\nFile creati: %d, iscritti scartati: %d\n", n, scartati);
    for (k = 0; k < n; k++) {
        sprintf(nome_file, "classe-%s.txt", classi[k]);
        printf("--- %s (iscritti: %d) ---\n", nome_file, conta[k]);
        ricopia(nome_file);
    }

    return 0;
}

int cerca(char classi[][8], int n, const char *classe)
{
    int trovata = -1;
    int k;

    for (k = 0; k < n && trovata == -1; k++) {
        if (strcmp(classi[k], classe) == 0) {
            trovata = k;
        }
    }
    return trovata;
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
