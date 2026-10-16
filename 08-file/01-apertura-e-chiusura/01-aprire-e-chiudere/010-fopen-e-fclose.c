/*
 * 010-fopen-e-fclose.c
 *
 * Aprire un file, usarlo e chiuderlo
 *
 * Un programma non lavora direttamente sul file del disco: fopen
 * restituisce un puntatore a FILE, una "maniglia" con cui le altre
 * funzioni leggono e scrivono. La struttura FILE è gestita dalla
 * libreria: il programma non ne usa mai i campi.
 *
 *     FILE *f = fopen("saluto.txt", "w");    nome e modalità
 *
 *     if (f == NULL) {
 *         ... il file non si può aprire ...
 *     } else {
 *         ... uso del file ...
 *         fclose(f);                         sempre, una volta sola
 *     }
 *
 * fopen restituisce NULL se il file non si può aprire (file inesistente
 * in lettura, cartella senza permessi, nome non valido): il controllo è
 * obbligatorio, come per malloc.
 *
 * Per scrivere testo: fputs(stringa, f), fputc(carattere, f) e
 * fprintf(f, formato, ...), che funziona come printf. Per leggere un
 * carattere alla volta: fgetc(f), che restituisce il carattere letto
 * oppure EOF alla fine del file.
 *
 * Attenzione: il risultato di fgetc va in un int, non in un char. EOF
 * è un valore negativo diverso da tutti i caratteri: in un char non si
 * distinguerebbe da un carattere valido.
 *
 * Il programma scrive due righe in saluto.txt, chiude il file, lo
 * riapre in lettura e lo stampa carattere per carattere.
 */

#include <stdio.h>

int main(void)
{
    FILE *f;
    int c;
    int caratteri = 0;

    f = fopen("saluto.txt", "w");
    if (f == NULL) {
        fprintf(stderr, "Impossibile creare saluto.txt\n");
    } else {
        fputs("Benvenuti al corso di C!\n", f);
        fprintf(f, "Lezione %d: apertura e chiusura dei file.\n", 1);
        fclose(f);
        printf("Scritto saluto.txt\n");

        f = fopen("saluto.txt", "r");
        if (f == NULL) {
            fprintf(stderr, "Impossibile leggere saluto.txt\n");
        } else {
            printf("Contenuto di saluto.txt:\n");
            c = fgetc(f);
            while (c != EOF) {
                putchar(c);
                caratteri++;
                c = fgetc(f);
            }
            fclose(f);
            printf("Caratteri letti: %d\n", caratteri);
        }
    }

    return 0;
}
