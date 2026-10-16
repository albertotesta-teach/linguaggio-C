/*
 * 030-file-che-non-esiste.c
 *
 * Chiedere il nome di un file e gestire il file che non c'è
 *
 * Quando il nome arriva dall'utente, il file può non esistere: un
 * errore di battitura, l'estensione dimenticata, la cartella sbagliata.
 * L'unico modo affidabile di saperlo è provare ad aprirlo: se fopen in
 * lettura restituisce NULL, il file non si può leggere.
 *
 *     tentativi = 0;
 *     f = NULL;
 *     finché f == NULL e tentativi < 3:
 *         chiedi il nome
 *         f = fopen(nome, "r")
 *         se f == NULL: messaggio su stderr
 *         tentativi++
 *
 * Dopo il ciclo f può essere ancora NULL (tre tentativi falliti): il
 * resto del programma lo deve controllare. fclose si chiama solo se il
 * file è stato aperto; fclose(NULL) non è permesso.
 *
 * Il programma chiede il nome di un file di testo, al massimo tre volte,
 * e ne stampa il contenuto con il numero di righe.
 */

#include <stdio.h>

#define TENTATIVI 3

int main(void)
{
    FILE *f = NULL;
    char nome[60];
    int tentativi = 0;
    int righe = 0;
    int c;
    int ultimo = '\n';

    while (f == NULL && tentativi < TENTATIVI) {
        printf("Nome del file (tentativo %d di %d): ", tentativi + 1, TENTATIVI);
        if (scanf("%59s", nome) != 1) {
            tentativi = TENTATIVI;
        } else {
            f = fopen(nome, "r");
            if (f == NULL) {
                fprintf(stderr, "  %s non esiste o non si puo' leggere\n", nome);
            }
            tentativi++;
        }
    }

    if (f == NULL) {
        printf("Nessun file aperto.\n");
    } else {
        printf("--- %s ---\n", nome);
        c = fgetc(f);
        while (c != EOF) {
            putchar(c);
            if (c == '\n') {
                righe++;
            }
            ultimo = c;
            c = fgetc(f);
        }
        if (ultimo != '\n') {
            putchar('\n');
            righe++;
        }
        printf("--- righe: %d ---\n", righe);
        fclose(f);
    }

    return 0;
}
