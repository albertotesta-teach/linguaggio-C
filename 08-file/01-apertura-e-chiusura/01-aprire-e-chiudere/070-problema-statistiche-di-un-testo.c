/*
 * 070-problema-statistiche-di-un-testo.c
 *
 * Statistiche di un file di testo, leggendolo una sola volta
 *
 * Prima di consegnare la relazione di laboratorio gli studenti devono
 * rispettare alcuni limiti: righe non troppo lunghe, un numero massimo
 * di righe. Il programma legge il file carattere per carattere, una
 * sola volta, e conta:
 *
 *     lettere          isalpha (solo lettere senza accento)
 *     cifre            isdigit
 *     spazi            ' ' e '\t'
 *     altri caratteri  punteggiatura, accenti, ...
 *     righe            ogni '\n', più l'ultima riga se non termina con '\n'
 *     riga più lunga   lunghezza e numero, senza contare il '\n'
 *
 * La lunghezza della riga corrente si azzera a ogni '\n'; prima di
 * azzerarla si confronta con il massimo.
 *
 * Il programma chiede il nome del file e segnala le righe oltre gli 80
 * caratteri, il limite consigliato per una relazione leggibile.
 */

#include <stdio.h>
#include <ctype.h>

#define LIMITE 80

int main(void)
{
    FILE *f;
    char nome[60];
    int lettere = 0;
    int cifre = 0;
    int spazi = 0;
    int altri = 0;
    int righe = 0;
    int lunghezza = 0;
    int massima = 0;
    int riga_massima = 0;
    int troppo_lunghe = 0;
    int c;

    printf("File da analizzare: ");
    if (scanf("%59s", nome) != 1) {
        nome[0] = '\0';
    }
    f = fopen(nome, "r");
    if (f == NULL) {
        fprintf(stderr, "Impossibile leggere \"%s\"\n", nome);
    } else {
        c = fgetc(f);
        while (c != EOF) {
            if (c == '\n') {
                righe++;
                if (lunghezza > massima) {
                    massima = lunghezza;
                    riga_massima = righe;
                }
                if (lunghezza > LIMITE) {
                    troppo_lunghe++;
                }
                lunghezza = 0;
            } else {
                lunghezza++;
                if (isalpha(c)) {
                    lettere++;
                } else if (isdigit(c)) {
                    cifre++;
                } else if (c == ' ' || c == '\t') {
                    spazi++;
                } else {
                    altri++;
                }
            }
            c = fgetc(f);
        }
        fclose(f);
        if (lunghezza > 0) {
            righe++;
            if (lunghezza > massima) {
                massima = lunghezza;
                riga_massima = righe;
            }
            if (lunghezza > LIMITE) {
                troppo_lunghe++;
            }
        }

        printf("Statistiche di %s\n", nome);
        printf("  lettere          %6d\n", lettere);
        printf("  cifre            %6d\n", cifre);
        printf("  spazi            %6d\n", spazi);
        printf("  altri caratteri  %6d\n", altri);
        printf("  righe            %6d\n", righe);
        if (righe > 0) {
            printf("  riga piu' lunga: la %d, con %d caratteri\n", riga_massima, massima);
        }
        printf("  righe oltre %d caratteri: %d\n", LIMITE, troppo_lunghe);
    }

    return 0;
}
