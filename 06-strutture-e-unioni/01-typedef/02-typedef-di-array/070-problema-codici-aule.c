/*
 * 070-problema-codici-aule.c
 *
 * Segreteria: comporre e scomporre i codici delle aule
 *
 * Ogni aula dell'istituto ha un codice di 5 caratteri nel formato E P-NN:
 * la lettera dell'edificio, la cifra del piano, un trattino e il numero
 * dell'aula su due cifre. Ad esempio B2-07 è l'aula 7 al secondo piano
 * dell'edificio B.
 *
 *     typedef char Codice[6];
 *
 *     void componi(Codice c, char edificio, int piano, int numero);
 *     int scomponi(const Codice c, char *edificio, int *piano, int *numero);
 *
 * componi scrive nella Codice del chiamante (riceve l'indirizzo del primo
 * carattere); scomponi controlla il formato, restituisce 1 se è valido e
 * scrive le tre parti nei parametri di uscita.
 *
 * Il programma compone i codici delle aule a partire dai dati della
 * segreteria, li stampa e poi risponde alle richieste: per ogni codice
 * letto indica edificio, piano, numero e capienza, oppure "codice non
 * valido" o "aula inesistente". FINE termina.
 */

#include <stdio.h>
#include <string.h>

#define AULE 6
#define LUNG_RIGA 40

typedef char Codice[6];

void componi(Codice c, char edificio, int piano, int numero);
int scomponi(const Codice c, char *edificio, int *piano, int *numero);

int main(void)
{
    char edifici[AULE] = {'A', 'A', 'A', 'B', 'B', 'C'};
    int piani[AULE] = {0, 1, 1, 2, 2, 0};
    int numeri[AULE] = {3, 12, 14, 7, 9, 1};
    int capienza[AULE] = {28, 30, 24, 26, 32, 60};
    Codice codici[AULE];
    Codice richiesto;
    char riga[LUNG_RIGA];
    char *a_capo;
    int resto;
    char edificio;
    int piano;
    int numero;
    int a;
    int fine = 0;

    printf("Codici delle aule:\n");
    for (a = 0; a < AULE; a++) {
        componi(codici[a], edifici[a], piani[a], numeri[a]);
        printf("  %s  (%d posti)\n", codici[a], capienza[a]);
    }

    while (!fine) {
        printf("Codice da cercare (FINE per terminare): ");
        if (fgets(riga, LUNG_RIGA, stdin) == NULL) {
            fine = 1;
        } else {
            a_capo = strchr(riga, '\n');
            if (a_capo != NULL) {
                *a_capo = '\0';
            } else {
                resto = getchar();      /* riga troppo lunga: scarta il resto */
                while (resto != '\n' && resto != EOF) {
                    resto = getchar();
                }
            }
            if (strcmp(riga, "FINE") == 0) {
                fine = 1;
            } else if (strlen(riga) != 5) {
                printf("  Codice non valido.\n");
            } else {
                strcpy(richiesto, riga);
                if (!scomponi(richiesto, &edificio, &piano, &numero)) {
                    printf("  Codice non valido.\n");
                } else {
                    a = 0;
                    while (a < AULE && strcmp(codici[a], richiesto) != 0) {
                        a++;
                    }
                    printf("  Edificio %c, piano %d, aula %d: ", edificio, piano, numero);
                    if (a < AULE) {
                        printf("%d posti.\n", capienza[a]);
                    } else {
                        printf("aula inesistente.\n");
                    }
                }
            }
        }
    }

    return 0;
}

/* Scrive in c il codice nel formato E P-NN. */
void componi(Codice c, char edificio, int piano, int numero)
{
    c[0] = edificio;
    c[1] = (char) ('0' + piano);
    c[2] = '-';
    c[3] = (char) ('0' + numero / 10);
    c[4] = (char) ('0' + numero % 10);
    c[5] = '\0';
}

/* 1 se c ha il formato E P-NN (edificio A-Z); in quel caso scrive le parti. */
int scomponi(const Codice c, char *edificio, int *piano, int *numero)
{
    int valido = c[0] >= 'A' && c[0] <= 'Z' && c[1] >= '0' && c[1] <= '9' && c[2] == '-' &&
                 c[3] >= '0' && c[3] <= '9' && c[4] >= '0' && c[4] <= '9';

    if (valido) {
        *edificio = c[0];
        *piano = c[1] - '0';
        *numero = (c[3] - '0') * 10 + (c[4] - '0');
    }
    return valido;
}
