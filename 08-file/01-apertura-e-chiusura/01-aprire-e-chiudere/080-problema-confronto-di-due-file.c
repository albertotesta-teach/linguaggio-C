/*
 * 080-problema-confronto-di-due-file.c
 *
 * Due file sono uguali? Dove differiscono per la prima volta?
 *
 * Il docente ha consegnato a ogni studente lo stesso file di dati e
 * vuole verificare che nessuno l'abbia modificato. Il programma apre i
 * due file insieme e li legge in parallelo, un carattere da ciascuno,
 * tenendo il conto di riga e colonna:
 *
 *     a = fgetc(primo);  b = fgetc(secondo);
 *     finché a == b e a != EOF:
 *         se a == '\n': riga++, colonna = 1   altrimenti colonna++
 *         a = fgetc(primo);  b = fgetc(secondo);
 *
 * All'uscita dal ciclo:
 *     a == b (entrambi EOF)   i file sono identici
 *     a == EOF o b == EOF     un file è l'inizio dell'altro, più corto
 *     altrimenti              prima differenza in (riga, colonna)
 *
 * Se il secondo file non si apre, il primo, già aperto, va chiuso.
 * Il programma mostra i due caratteri diversi, scrivendo "a capo" e
 * "fine del file" invece dei caratteri invisibili.
 */

#include <stdio.h>

void descrivi(int c);

int main(void)
{
    FILE *primo = NULL;
    FILE *secondo = NULL;
    char nome_primo[60];
    char nome_secondo[60];
    int riga = 1;
    int colonna = 1;
    int a;
    int b;

    printf("Primo file: ");
    if (scanf("%59s", nome_primo) == 1) {
        printf("Secondo file: ");
        if (scanf("%59s", nome_secondo) == 1) {
            primo = fopen(nome_primo, "r");
        }
    }
    if (primo == NULL) {
        fprintf(stderr, "Impossibile leggere il primo file\n");
    } else {
        secondo = fopen(nome_secondo, "r");
        if (secondo == NULL) {
            fprintf(stderr, "Impossibile leggere %s\n", nome_secondo);
            fclose(primo);
        }
    }

    if (secondo != NULL) {
        a = fgetc(primo);
        b = fgetc(secondo);
        while (a == b && a != EOF) {
            if (a == '\n') {
                riga++;
                colonna = 1;
            } else {
                colonna++;
            }
            a = fgetc(primo);
            b = fgetc(secondo);
        }
        fclose(primo);
        fclose(secondo);

        if (a == b) {
            /* l'ultima riga conta anche se non finisce con a capo */
            printf("I file sono identici. Righe confrontate: %d\n",
                   colonna > 1 ? riga : riga - 1);
        } else {
            printf("Prima differenza alla riga %d, colonna %d:\n", riga, colonna);
            printf("  %-20s ", nome_primo);
            descrivi(a);
            printf("  %-20s ", nome_secondo);
            descrivi(b);
        }
    }

    return 0;
}

void descrivi(int c)
{
    if (c == EOF) {
        printf("fine del file\n");
    } else if (c == '\n') {
        printf("a capo\n");
    } else {
        printf("'%c'\n", c);
    }
}
