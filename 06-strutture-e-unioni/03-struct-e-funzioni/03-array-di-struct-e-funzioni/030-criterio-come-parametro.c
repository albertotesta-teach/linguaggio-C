/*
 * 030-criterio-come-parametro.c
 *
 * Contare e filtrare con un criterio passato come funzione
 *
 * Molte domande su un elenco hanno la stessa forma: "quanti studenti
 * soddisfano questa condizione?", "quali sono?". La condizione cambia, il
 * ciclo no. La condizione diventa una funzione che riceve UNO studente:
 *
 *     typedef int (*Criterio)(const Studente *s);
 *
 *     int insufficiente(const Studente *s);
 *     int eccellente(const Studente *s);
 *     int molte_assenze(const Studente *s);
 *
 *     int conta(const Studente classe[], int n, Criterio c);
 *     void elenca(const Studente classe[], int n, Criterio c);
 *
 * conta e elenca chiamano c(&classe[i]) per ogni elemento: con lo stesso
 * codice rispondono a domande diverse. Un array di Criterio con i nomi
 * permette di provarli tutti con un ciclo.
 */

#include <stdio.h>

#define STUDENTI 6
#define CRITERI  3

typedef struct {
    char nome[20];
    double media;
    int assenze;
} Studente;

typedef int (*Criterio)(const Studente *s);

int insufficiente(const Studente *s);
int eccellente(const Studente *s);
int molte_assenze(const Studente *s);
int conta(const Studente classe[], int n, Criterio c);
void elenca(const Studente classe[], int n, Criterio c);

int main(void)
{
    Studente classe[STUDENTI] = {
        {"Bianchi Sara", 8.6, 12},
        {"Colombo Luca", 5.4, 48},
        {"Esposito Anna", 9.1, 6},
        {"Ferrari Marco", 5.8, 31},
        {"Galli Irene", 7.2, 54},
        {"Monti Dario", 6.5, 20}
    };
    const char *domande[CRITERI] = {"media sotto 6", "media da 8.5 in su", "piu' di 40 ore di assenza"};
    Criterio criteri[CRITERI] = {insufficiente, eccellente, molte_assenze};
    int c;

    for (c = 0; c < CRITERI; c++) {
        printf("%s: %d studenti\n", domande[c], conta(classe, STUDENTI, criteri[c]));
        elenca(classe, STUDENTI, criteri[c]);
    }

    return 0;
}

int insufficiente(const Studente *s)
{
    return s->media < 6;
}

int eccellente(const Studente *s)
{
    return s->media >= 8.5;
}

int molte_assenze(const Studente *s)
{
    return s->assenze > 40;
}

int conta(const Studente classe[], int n, Criterio c)
{
    int i;
    int conteggio = 0;

    for (i = 0; i < n; i++) {
        if (c(&classe[i])) {
            conteggio++;
        }
    }
    return conteggio;
}

void elenca(const Studente classe[], int n, Criterio c)
{
    int i;

    for (i = 0; i < n; i++) {
        if (c(&classe[i])) {
            printf("  %-14s media %.1f, assenze %d\n", classe[i].nome, classe[i].media, classe[i].assenze);
        }
    }
}
