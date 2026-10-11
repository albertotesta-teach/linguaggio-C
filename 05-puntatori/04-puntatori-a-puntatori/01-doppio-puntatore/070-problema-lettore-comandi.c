/*
 * 070-problema-lettore-comandi.c
 *
 * Domotica dell'aula: un lettore di comandi testuali
 *
 * L'aula del laboratorio ha luce, tapparelle e climatizzatore comandati da
 * una scheda programmabile, che riceve righe di comandi separati da ';':
 *     SET luce 80; SET aria 22; GET luce
 * SET imposta un dispositivo al valore dato, GET ne mostra il valore.
 *
 * Le funzioni di lettura ricevono l'indirizzo del puntatore di lettura
 * (const char **) e lo fanno avanzare:
 *     leggi_parola(&p, parola, max)    una parola di lettere
 *     leggi_numero(&p, &n)             un numero
 *     salta_separatori(&p)             spazi e ';'
 * In questo modo ogni funzione riprende da dove si è fermata la precedente.
 *
 * Il programma legge una riga di comandi alla volta; una riga vuota
 * termina.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LUNG        100
#define LUNG_PAROLA 16
#define DISPOSITIVI 3

void salta_separatori(const char **p);
int leggi_parola(const char **p, char *parola, int max);
int leggi_numero(const char **p, int *numero);
int cerca_dispositivo(const char nomi[][LUNG_PAROLA], const char *nome);

int main(void)
{
    char nomi[DISPOSITIVI][LUNG_PAROLA] = {"luce", "tapparelle", "aria"};
    int valori[DISPOSITIVI] = {0, 100, 20};
    char riga[LUNG];
    char comando[LUNG_PAROLA];
    char nome[LUNG_PAROLA];
    const char *p;
    char *a_capo;
    int d;
    int n;
    int continua = 1;

    while (continua) {
        printf("Comandi (riga vuota per finire): ");
        if (fgets(riga, LUNG, stdin) == NULL) {
            continua = 0;
        } else {
            a_capo = strchr(riga, '\n');
            if (a_capo != NULL) {
                *a_capo = '\0';
            }
            continua = riga[0] != '\0';
            p = riga;
            salta_separatori(&p);
            while (*p != '\0') {
                leggi_parola(&p, comando, LUNG_PAROLA);
                leggi_parola(&p, nome, LUNG_PAROLA);
                d = cerca_dispositivo(nomi, nome);
                if (d == -1) {
                    printf("  %s %s: dispositivo sconosciuto\n", comando, nome);
                } else if (strcmp(comando, "GET") == 0) {
                    printf("  %s = %d\n", nomi[d], valori[d]);
                } else if (strcmp(comando, "SET") == 0 && leggi_numero(&p, &n)) {
                    valori[d] = n;
                    printf("  %s -> %d\n", nomi[d], n);
                } else {
                    printf("  %s %s: comando non valido\n", comando, nome);
                }
                /* il comando finisce al ';' successivo */
                while (*p != '\0' && *p != ';') {
                    p++;
                }
                salta_separatori(&p);
            }
        }
    }

    return 0;
}

/* Salta spazi e punti e virgola. */
void salta_separatori(const char **p)
{
    while (**p == ' ' || **p == ';') {
        (*p)++;
    }
}

/* Copia in parola le lettere successive (al massimo max - 1) e sposta *p
 * dopo la parola. Restituisce il numero di lettere lette. */
int leggi_parola(const char **p, char *parola, int max)
{
    int k = 0;

    while (**p == ' ') {
        (*p)++;
    }
    while (isalpha((unsigned char) **p)) {
        if (k < max - 1) {
            parola[k] = **p;
            k++;
        }
        (*p)++;
    }
    parola[k] = '\0';
    return k;
}

/* Legge un numero intero e sposta *p dopo l'ultima cifra; 1 se riuscita. */
int leggi_numero(const char **p, int *numero)
{
    int letto = 0;

    while (**p == ' ') {
        (*p)++;
    }
    *numero = 0;
    while (isdigit((unsigned char) **p)) {
        *numero = *numero * 10 + (**p - '0');
        (*p)++;
        letto = 1;
    }
    return letto;
}

/* Indice del dispositivo con il nome dato, -1 se non esiste. */
int cerca_dispositivo(const char nomi[][LUNG_PAROLA], const char *nome)
{
    int i = 0;

    while (i < DISPOSITIVI && strcmp(nomi[i], nome) != 0) {
        i++;
    }
    return i < DISPOSITIVI ? i : -1;
}
