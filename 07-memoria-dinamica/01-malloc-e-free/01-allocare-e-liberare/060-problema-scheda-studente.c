/*
 * 060-problema-scheda-studente.c
 *
 * Segreteria: la scheda di fine trimestre di ogni studente
 *
 * La segreteria inserisce uno studente per riga:
 *
 *     cognome nome classe voto_italiano voto_matematica voto_inglese
 *     Bassi Marta 3B 7 8.5 6
 *
 * Per ogni riga il programma alloca una struct Studente, la fa riempire
 * dalla funzione leggi_studente, stampa la scheda e libera la struct
 * prima di passare allo studente successivo:
 *
 *     Studente *s = malloc(sizeof *s);
 *     esito = leggi_studente(s);       riceve l'indirizzo del blocco
 *     stampa_scheda(s);
 *     free(s);
 *
 * leggi_studente riceve un puntatore: scrive direttamente nel blocco
 * allocato dal chiamante e restituisce 1 se la riga è corretta, 0 se c'è
 * un errore (voto fuori da 1-10 o classe troppo lunga), -1 per FINE o
 * per la fine dell'input.
 *
 * La scheda contiene la media e l'esito: promosso se tutti i voti sono
 * almeno 6, altrimenti il numero di materie insufficienti.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATERIE 3

typedef struct {
    char cognome[20];
    char nome[20];
    char classe[4];
    double voti[MATERIE];
} Studente;

int leggi_studente(Studente *s);
void stampa_scheda(const Studente *s);

int main(void)
{
    Studente *s;
    int esito = 1;
    int schede = 0;
    int scartate = 0;

    while (esito != -1) {
        s = malloc(sizeof *s);
        if (s == NULL) {
            printf("Memoria insufficiente.\n");
            esito = -1;
        } else {
            printf("Studente (FINE per terminare): ");
            esito = leggi_studente(s);
            if (esito == 1) {
                stampa_scheda(s);
                schede++;
            } else if (esito == 0) {
                printf("  Riga non valida: scheda non creata.\n");
                scartate++;
            }
            free(s);
        }
    }
    printf("\nSchede stampate: %d, righe scartate: %d\n", schede, scartate);

    return 0;
}

int leggi_studente(Studente *s)
{
    char classe[16];
    int i;
    int esito = -1;

    if (scanf("%19s", s->cognome) == 1 && strcmp(s->cognome, "FINE") != 0) {
        esito = scanf("%19s %15s %lf %lf %lf", s->nome, classe, &s->voti[0],
                      &s->voti[1], &s->voti[2]) == 5 && strlen(classe) < sizeof s->classe;
        for (i = 0; i < MATERIE && esito; i++) {
            if (s->voti[i] < 1 || s->voti[i] > 10) {
                esito = 0;
            }
        }
        if (esito) {
            strcpy(s->classe, classe);
        }
        scanf("%*[^\n]");
    }
    return esito;
}

void stampa_scheda(const Studente *s)
{
    const char *materie[MATERIE] = {"italiano", "matematica", "inglese"};
    double somma = 0;
    int insufficienti = 0;
    int i;

    printf("  +--------------------------------+\n");
    printf("  | %-10s %-10s %-8s |\n", s->cognome, s->nome, s->classe);
    for (i = 0; i < MATERIE; i++) {
        printf("  |   %-12s %5.1f           |\n", materie[i], s->voti[i]);
        somma = somma + s->voti[i];
        if (s->voti[i] < 6) {
            insufficienti++;
        }
    }
    printf("  |   media        %5.2f           |\n", somma / MATERIE);
    if (insufficienti == 0) {
        printf("  |   esito: promosso              |\n");
    } else if (insufficienti == 1) {
        printf("  |   esito: 1 insufficienza       |\n");
    } else {
        printf("  |   esito: %d insufficienze       |\n", insufficienti);
    }
    printf("  +--------------------------------+\n");
}
