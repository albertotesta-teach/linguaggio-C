/*
 * 080-problema-archivio-dei-sensori.c
 *
 * Le aule sensorizzate: un blocco di letture per ogni sensore
 *
 * In alcune aule ci sono sensori di temperatura. Ogni sensore ha un
 * blocco con una lettura per ogni ora del periodo di osservazione:
 *
 *     typedef struct {
 *         char aula[12];
 *         int ore;                   dimensione del blocco
 *         double *letture;           letture[h]: temperatura all'ora h
 *     } Sensore;
 *
 * L'array dei sensori si alloca con calloc: ogni letture parte da NULL
 * e ogni ore da 0 (030-matrice-azzerata: i byte a zero valgono NULL).
 * Quando il periodo cambia, il blocco di ogni sensore si ridimensiona
 * con realloc (la prima volta realloc(NULL, ...), cioè una malloc). Le
 * ore nuove si segnano come MANCANTE finché non arriva la lettura;
 * accorciando il periodo le ultime letture si perdono.
 *
 * Ogni sensore tiene la sua dimensione: se la realloc di un sensore
 * fallisce, quel sensore resta con il periodo vecchio e gli altri sono
 * comunque coerenti.
 *
 * Comandi:
 *     P ore                  nuovo periodo di osservazione (1-168 ore)
 *     L aula ora gradi       lettura di un sensore (ora da 1)
 *     M                      media, minimo e massimo per aula
 *     Q                      fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SENSORI 8
#define MAX_ORE 168
#define MANCANTE -999.0

typedef struct {
    char aula[12];
    int ore;
    double *letture;
} Sensore;

int cambia_periodo(Sensore *s, int ore);
void riepilogo(const Sensore *s);

int main(void)
{
    Sensore *sensori;
    int n;
    int k;
    int ore;
    int ora;
    int trovato;
    double gradi;
    char aula[12];
    char comando = ' ';

    printf("Numero di sensori e nomi delle aule: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SENSORI) {
        printf("Numero non valido.\n");
    } else {
        sensori = calloc(n, sizeof *sensori);
        if (sensori == NULL) {
            printf("Memoria insufficiente.\n");
            comando = 'Q';
        }
        for (k = 0; k < n && comando != 'Q'; k++) {
            if (scanf("%11s", sensori[k].aula) != 1) {
                comando = 'Q';
            }
        }

        while (comando != 'Q') {
            printf("Comando (P, L, M, Q): ");
            if (scanf(" %c", &comando) != 1) {
                comando = 'Q';          /* input terminato: come Q */
            }
            comando = (char) toupper((unsigned char) comando);
            if (comando == 'P') {
                if (scanf("%d", &ore) != 1 || ore < 1 || ore > MAX_ORE) {
                    printf("  Periodo non valido.\n");
                } else {
                    for (k = 0; k < n; k++) {
                        if (!cambia_periodo(&sensori[k], ore)) {
                            printf("  %s: memoria insufficiente, resta a %d ore\n",
                                   sensori[k].aula, sensori[k].ore);
                        }
                    }
                    printf("  periodo di %d ore: %zu byte per sensore\n", ore,
                           ore * sizeof *sensori[0].letture);
                }
            } else if (comando == 'L') {
                if (scanf("%11s %d %lf", aula, &ora, &gradi) != 3) {
                    printf("  Dati non validi.\n");
                } else {
                    trovato = -1;
                    for (k = 0; k < n; k++) {
                        if (strcmp(sensori[k].aula, aula) == 0) {
                            trovato = k;
                        }
                    }
                    if (trovato == -1) {
                        printf("  Aula sconosciuta.\n");
                    } else if (sensori[trovato].ore == 0) {
                        printf("  Periodo non ancora impostato (comando P).\n");
                    } else if (ora < 1 || ora > sensori[trovato].ore) {
                        printf("  Ora fuori dal periodo (1-%d).\n", sensori[trovato].ore);
                    } else {
                        sensori[trovato].letture[ora - 1] = gradi;
                        printf("  %s, ora %d: %.1f gradi\n", aula, ora, gradi);
                    }
                }
            } else if (comando == 'M') {
                for (k = 0; k < n; k++) {
                    riepilogo(&sensori[k]);
                }
            } else if (comando != 'Q') {
                printf("  Comando sconosciuto.\n");
            }
            if (comando != 'Q') {
                scanf("%*[^\n]");  /* un comando per riga */
            }
        }

        for (k = 0; k < n && sensori != NULL; k++) {
            free(sensori[k].letture);
        }
        free(sensori);
    }

    return 0;
}

/* Ridimensiona il blocco del sensore; le ore nuove sono MANCANTE. */
int cambia_periodo(Sensore *s, int ore)
{
    double *tmp = realloc(s->letture, ore * sizeof *tmp);
    int h;

    if (tmp != NULL) {
        for (h = s->ore; h < ore; h++) {
            tmp[h] = MANCANTE;
        }
        s->letture = tmp;
        s->ore = ore;
    }
    return tmp != NULL;
}

void riepilogo(const Sensore *s)
{
    double somma = 0;
    double minimo = 0;
    double massimo = 0;
    int valide = 0;
    int h;

    for (h = 0; h < s->ore; h++) {
        if (s->letture[h] != MANCANTE) {
            if (valide == 0 || s->letture[h] < minimo) {
                minimo = s->letture[h];
            }
            if (valide == 0 || s->letture[h] > massimo) {
                massimo = s->letture[h];
            }
            somma = somma + s->letture[h];
            valide++;
        }
    }
    printf("  %-8s letture %d su %d", s->aula, valide, s->ore);
    if (valide > 0) {
        printf(", media %.1f, min %.1f, max %.1f", somma / valide, minimo, massimo);
    }
    printf("\n");
}
