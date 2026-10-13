/*
 * 050-problema-riga-sicura.c
 *
 * La bacheca dei messaggi: righe di lunghezza qualsiasi senza overflow
 *
 * La bacheca digitale della scuola mostra messaggi di al massimo 30
 * caratteri. Gli studenti li scrivono da tastiera, e qualcuno scrive
 * righe molto più lunghe.
 *
 * La riga si legge con fgets in un buffer fisso di 32 byte: fgets non
 * scrive mai più di 31 caratteri più il '\0', quindi il buffer non può
 * traboccare. Se nel buffer non c'è il '\n', la riga era più lunga: il
 * resto è ancora nell'input e va consumato carattere per carattere con
 * getchar, contandolo, altrimenti verrebbe letto come riga successiva.
 *
 *     if (strchr(buffer, '\n') == NULL) {
 *         ... legge con getchar fino al '\n' ...
 *     }
 *
 * Un messaggio accettato si copia in un blocco grande esattamente
 * strlen + 1 byte; il buffer si riusa per la riga successiva. Errori da
 * evitare:
 *   - leggere con scanf("%s") o gets in un array piccolo (overflow);
 *   - allocare strlen byte dimenticando il '\0' (si scrive un byte fuori
 *     dal blocco).
 *
 * La bacheca contiene al massimo 5 messaggi; FINE termina.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARATTERI 30
#define DIM_BUFFER (MAX_CARATTERI + 2)
#define MAX_MESSAGGI 5

int leggi_riga(char buffer[], int dimensione, int *lunghezza);

int main(void)
{
    char *bacheca[MAX_MESSAGGI];
    char buffer[DIM_BUFFER];
    char *messaggio;
    int n = 0;
    int lunghezza;
    int finito = 0;
    int i;

    printf("Messaggi per la bacheca (al massimo %d caratteri, FINE per terminare)\n",
           MAX_CARATTERI);
    while (!finito && n < MAX_MESSAGGI) {
        printf("> ");
        if (!leggi_riga(buffer, DIM_BUFFER, &lunghezza) || strcmp(buffer, "FINE") == 0) {
            finito = 1;
        } else if (lunghezza > MAX_CARATTERI) {
            printf("  troppo lungo: %d caratteri, massimo %d\n", lunghezza, MAX_CARATTERI);
        } else if (lunghezza == 0) {
            printf("  messaggio vuoto\n");
        } else {
            messaggio = malloc(lunghezza + 1);
            if (messaggio == NULL) {
                printf("  Memoria insufficiente.\n");
                finito = 1;
            } else {
                strcpy(messaggio, buffer);
                bacheca[n] = messaggio;
                n++;
                printf("  pubblicato (%d byte)\n", lunghezza + 1);
            }
        }
    }

    printf("\n+--------------------------------+\n");
    for (i = 0; i < n; i++) {
        printf("| %-30s |\n", bacheca[i]);
        free(bacheca[i]);
    }
    printf("+--------------------------------+\n");

    return 0;
}

/*
 * Legge una riga nel buffer senza superarne la dimensione. In *lunghezza
 * scrive la lunghezza vera della riga, anche se nel buffer ne è entrata
 * solo una parte. Restituisce 0 a fine input.
 */
int leggi_riga(char buffer[], int dimensione, int *lunghezza)
{
    int letta = fgets(buffer, dimensione, stdin) != NULL;
    char *a_capo;
    int c;

    *lunghezza = 0;
    if (letta) {
        a_capo = strchr(buffer, '\n');
        if (a_capo != NULL) {
            *a_capo = '\0';
            *lunghezza = (int) strlen(buffer);
        } else {
            *lunghezza = (int) strlen(buffer);
            c = getchar();
            while (c != '\n' && c != EOF) {
                (*lunghezza)++;
                c = getchar();
            }
        }
    }
    return letta;
}
