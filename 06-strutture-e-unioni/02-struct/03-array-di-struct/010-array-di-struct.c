/*
 * 010-array-di-struct.c
 *
 * Un array di struct: una tabella in cui ogni riga è un record
 *
 * Una struct descrive un solo studente; per una classe intera serve un
 * array di struct. Ogni elemento è una struct completa:
 *
 *     Studente classe[STUDENTI] = {
 *         {"Bianchi Sara", 16, 7.8},
 *         {"Colombo Luca", 17, 6.2},
 *         ...
 *     };
 *
 *     classe[i]          lo studente i (una struct)
 *     classe[i].media    il campo media dello studente i
 *     classe[i].nome[0]  l'iniziale del suo nome
 *
 * Al posto di tre array paralleli (nomi, eta, medie) che vanno tenuti
 * allineati a mano, c'è un solo array: i dati dello stesso studente
 * restano sempre insieme. Un elemento si copia con = come ogni struct.
 *
 * Esempio: l'elenco della 3B con età e media, stampato come tabella.
 */

#include <stdio.h>

#define STUDENTI 5

typedef struct {
    char nome[20];
    int eta;
    double media;
} Studente;

int main(void)
{
    Studente classe[STUDENTI] = {
        {"Bianchi Sara", 16, 7.8},
        {"Colombo Luca", 17, 6.2},
        {"Esposito Anna", 16, 8.4},
        {"Ferrari Marco", 16, 5.9},
        {"Galli Irene", 17, 7.1}
    };
    Studente rappresentante;
    double somma = 0;
    int i;

    printf("  N.  Nome            Eta'  Media\n");
    for (i = 0; i < STUDENTI; i++) {
        printf("  %2d  %-14s  %4d  %5.1f\n", i + 1, classe[i].nome, classe[i].eta, classe[i].media);
        somma = somma + classe[i].media;
    }
    printf("\nMedia della classe: %.2f\n", somma / STUDENTI);

    /* un elemento dell'array è una struct: si copia con = */
    rappresentante = classe[2];
    printf("Rappresentante: %s (iniziale %c)\n", rappresentante.nome, rappresentante.nome[0]);

    printf("\nsizeof(Studente) = %zu, sizeof(classe) = %zu = %d x %zu\n",
           sizeof(Studente), sizeof(classe), STUDENTI, sizeof(Studente));

    return 0;
}
