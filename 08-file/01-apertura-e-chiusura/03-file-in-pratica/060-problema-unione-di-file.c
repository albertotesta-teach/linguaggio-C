/*
 * 060-problema-unione-di-file.c
 *
 * Unire più file in uno solo
 *
 * Alla fine del corso di primo soccorso la segreteria vuole un unico
 * file con gli elenchi di tutte le classi. Il programma chiede il nome
 * del file da creare e poi i nomi dei file da unire, fino a FINE:
 *
 *     destinazione = fopen(nome, "w")
 *     per ogni nome letto:
 *         origine = fopen(nome_letto, "r")
 *         se NULL: avviso su stderr e si passa al successivo
 *         altrimenti: intestazione, copia carattere per carattere, fclose
 *     fclose(destinazione)
 *
 * In ogni momento sono aperti al massimo due file: la destinazione,
 * per tutta la durata, e un'origine alla volta. Ogni origine si chiude
 * prima di aprire la successiva.
 *
 * Il nome della destinazione non può comparire tra le origini: il file
 * leggerebbe se stesso mentre cresce. Se un file non termina con '\n',
 * il programma aggiunge l'a capo, così l'intestazione successiva inizia
 * su una riga nuova.
 */

#include <stdio.h>
#include <string.h>

void ricopia(const char *nome);

int main(void)
{
    FILE *destinazione = NULL;
    FILE *origine;
    char nome_destinazione[60];
    char nome[60];
    int uniti = 0;
    int mancanti = 0;
    int caratteri = 0;
    int finito = 0;
    int ultimo;
    int c;

    printf("File da creare: ");
    if (scanf("%59s", nome_destinazione) == 1) {
        destinazione = fopen(nome_destinazione, "w");
        if (destinazione == NULL) {
            fprintf(stderr, "Impossibile creare %s\n", nome_destinazione);
        }
    }
    finito = destinazione == NULL;
    if (!finito) {
        printf("File da unire (FINE per terminare):\n");
    }
    while (!finito) {
        if (scanf("%59s", nome) != 1 || strcmp(nome, "FINE") == 0) {
            finito = 1;
        } else if (strcmp(nome, nome_destinazione) == 0) {
            fprintf(stderr, "  %s e' il file di destinazione: saltato\n", nome);
        } else {
            origine = fopen(nome, "r");
            if (origine == NULL) {
                fprintf(stderr, "  %s non trovato: saltato\n", nome);
                mancanti++;
            } else {
                fprintf(destinazione, "=== %s ===\n", nome);
                ultimo = '\n';
                c = fgetc(origine);
                while (c != EOF) {
                    fputc(c, destinazione);
                    caratteri++;
                    ultimo = c;
                    c = fgetc(origine);
                }
                if (ultimo != '\n') {
                    fputc('\n', destinazione);
                }
                fclose(origine);
                uniti++;
                printf("  aggiunto %s\n", nome);
            }
        }
    }
    if (destinazione != NULL) {
        fclose(destinazione);
        printf("%s: file uniti %d, mancanti %d, caratteri copiati %d\n", nome_destinazione,
               uniti, mancanti, caratteri);
        ricopia(nome_destinazione);
    }

    return 0;
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
