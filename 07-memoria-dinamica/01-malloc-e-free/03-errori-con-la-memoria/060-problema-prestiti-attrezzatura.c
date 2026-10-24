/*
 * 060-problema-prestiti-attrezzatura.c
 *
 * Il magazzino di educazione fisica: un blocco per ogni prestito
 *
 * Il magazzino presta palloni, racchette e cronometri. Ogni prestito è
 * una struct allocata quando l'oggetto esce e liberata quando rientra.
 * Il registro è un array di puntatori: NULL indica uno scaffale libero.
 *
 *     Prestito *scaffale[POSIZIONI];     tutti NULL all'inizio
 *
 *     uscita:   scaffale[k] = malloc(sizeof *scaffale[k]);
 *     rientro:  free(scaffale[k]);
 *               scaffale[k] = NULL;
 *
 * Mettere NULL dopo free è ciò che rende sicuro il programma: lo stesso
 * scaffale può essere riusato, un secondo rientro dello stesso numero
 * viene riconosciuto (scaffale vuoto) invece di diventare un doppio
 * free, e alla fine basta liberare i puntatori non NULL.
 *
 * Due contatori, allocati e liberati, permettono di controllare a fine
 * programma che nessun blocco sia rimasto in memoria.
 *
 * Comandi:
 *     U oggetto studente    uscita: assegna il primo scaffale libero
 *     R numero              rientro dallo scaffale indicato
 *     E                     elenco dei prestiti in corso
 *     Q                     fine: chiude i prestiti rimasti aperti
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define POSIZIONI 4

typedef struct {
    char oggetto[16];
    char studente[20];
} Prestito;

int primo_libero(Prestito *scaffale[]);
void elenco(Prestito *scaffale[]);

int main(void)
{
    Prestito *scaffale[POSIZIONI];
    char oggetto[16];
    char studente[20];
    char comando = ' ';
    int allocati = 0;
    int liberati = 0;
    int k;

    for (k = 0; k < POSIZIONI; k++) {
        scaffale[k] = NULL;
    }

    while (comando != 'Q') {
        printf("Comando (U, R, E, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'U') {
            k = primo_libero(scaffale);
            if (scanf("%15s %19s", oggetto, studente) != 2) {
                printf("  Dati non validi.\n");
            } else if (k == -1) {
                printf("  Registro pieno: nessuno scaffale libero.\n");
            } else {
                scaffale[k] = malloc(sizeof *scaffale[k]);
                if (scaffale[k] == NULL) {
                    printf("  Memoria insufficiente.\n");
                } else {
                    allocati++;
                    strcpy(scaffale[k]->oggetto, oggetto);
                    strcpy(scaffale[k]->studente, studente);
                    printf("  %s a %s: scaffale %d\n", oggetto, studente, k + 1);
                }
            }
        } else if (comando == 'R') {
            if (scanf("%d", &k) != 1 || k < 1 || k > POSIZIONI) {
                printf("  Scaffale non valido.\n");
            } else if (scaffale[k - 1] == NULL) {
                printf("  Scaffale %d vuoto: niente da far rientrare.\n", k);
            } else {
                printf("  rientrato %s da %s\n", scaffale[k - 1]->oggetto,
                       scaffale[k - 1]->studente);
                free(scaffale[k - 1]);
                scaffale[k - 1] = NULL;
                liberati++;
            }
        } else if (comando == 'E') {
            elenco(scaffale);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q') {
            scanf("%*[^\n]");          /* un comando per riga */
        }
    }

    printf("\nChiusura del magazzino\n");
    for (k = 0; k < POSIZIONI; k++) {
        if (scaffale[k] != NULL) {
            printf("  da recuperare: %s (%s)\n", scaffale[k]->oggetto, scaffale[k]->studente);
            free(scaffale[k]);
            scaffale[k] = NULL;
            liberati++;
        }
    }
    printf("  blocchi allocati %d, liberati %d", allocati, liberati);
    if (allocati == liberati) {
        printf(": nessun blocco rimasto in memoria\n");
    } else {
        printf(": ERRORE, %d blocchi persi\n", allocati - liberati);
    }

    return 0;
}

/* Indice del primo scaffale libero, -1 se sono tutti occupati. */
int primo_libero(Prestito *scaffale[])
{
    int libero = -1;
    int k;

    for (k = 0; k < POSIZIONI && libero == -1; k++) {
        if (scaffale[k] == NULL) {
            libero = k;
        }
    }
    return libero;
}

void elenco(Prestito *scaffale[])
{
    int k;

    for (k = 0; k < POSIZIONI; k++) {
        if (scaffale[k] == NULL) {
            printf("  %d  libero\n", k + 1);
        } else {
            printf("  %d  %-14s %s\n", k + 1, scaffale[k]->oggetto, scaffale[k]->studente);
        }
    }
}
