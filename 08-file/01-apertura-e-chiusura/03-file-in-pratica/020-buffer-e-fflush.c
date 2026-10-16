/*
 * 020-buffer-e-fflush.c
 *
 * Il buffer: quando i dati arrivano davvero nel file
 *
 * fputc, fputs e fprintf non scrivono subito sul disco: mettono i dati
 * in un buffer in memoria, che la libreria svuota nel file quando è
 * pieno, quando si chiama fflush o quando si chiude il file con fclose.
 * Scrivere a blocchi è molto più veloce che scrivere un carattere alla
 * volta.
 *
 *     fprintf(f, ...)      i dati sono nel buffer, NON ancora nel file
 *     fflush(f)            il buffer viene scritto nel file
 *     fclose(f)            svuota il buffer e poi chiude
 *
 * Conseguenze:
 *   - un altro programma (o un altro FILE * sullo stesso file) che legge
 *     prima di fflush o fclose non vede i dati;
 *   - se il programma termina in modo anomalo senza chiudere il file, i
 *     dati nel buffer vanno persi;
 *   - un file non chiuso alla fine di main viene chiuso da exit, ma è
 *     una cattiva abitudine contarci.
 *
 * Il programma scrive alcune righe in buffer.txt e, con un secondo
 * FILE * aperto in lettura, conta quanti caratteri si vedono nel file
 * prima di fflush, dopo fflush e dopo fclose.
 */

#include <stdio.h>

int conta_caratteri(const char *nome);

int main(void)
{
    FILE *f;

    f = fopen("buffer.txt", "w");
    if (f == NULL) {
        fprintf(stderr, "Impossibile creare buffer.txt\n");
    } else {
        fprintf(f, "Registro del laboratorio\n");
        fprintf(f, "Postazione 1: libera\n");
        printf("Dopo due fprintf:      %2d caratteri nel file\n", conta_caratteri("buffer.txt"));

        fflush(f);
        printf("Dopo fflush:           %2d caratteri nel file\n", conta_caratteri("buffer.txt"));

        fprintf(f, "Postazione 2: occupata\n");
        printf("Dopo un altro fprintf: %2d caratteri nel file\n", conta_caratteri("buffer.txt"));

        fclose(f);
        printf("Dopo fclose:           %2d caratteri nel file\n", conta_caratteri("buffer.txt"));
    }

    return 0;
}

/* Caratteri presenti nel file in questo momento, -1 se non si apre. */
int conta_caratteri(const char *nome)
{
    FILE *f = fopen(nome, "r");
    int conta = -1;

    if (f != NULL) {
        conta = 0;
        while (fgetc(f) != EOF) {
            conta++;
        }
        fclose(f);
    }
    return conta;
}
