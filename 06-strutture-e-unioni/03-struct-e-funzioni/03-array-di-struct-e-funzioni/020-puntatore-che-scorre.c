/*
 * 020-puntatore-che-scorre.c
 *
 * Scorrere un array di struct con un puntatore
 *
 * L'aritmetica dei puntatori (capitolo 05) vale anche per le struct: se p
 * punta a un elemento, p + 1 punta all'elemento successivo, cioè
 * sizeof(Tipo) byte più avanti.
 *
 *     const Treno *p;
 *     const Treno *fine = treni + n;
 *
 *     for (p = treni; p < fine; p++) {
 *         ... p->ritardo ...
 *     }
 *
 * La posizione dell'elemento puntato è p - treni. Una funzione può
 * restituire il puntatore all'elemento trovato, come nella sezione 02.
 *
 * Esempio: il tabellone degli arrivi della stazione vicino alla scuola,
 * con il ritardo di ogni treno.
 */

#include <stdio.h>

#define TRENI 5

typedef struct {
    char numero[8];
    char provenienza[16];
    int ritardo;
} Treno;

const Treno *piu_in_ritardo(const Treno treni[], int n);
int puntuali(const Treno treni[], int n);

int main(void)
{
    Treno arrivi[TRENI] = {
        {"R 10213", "Acqui Terme", 0},
        {"R 10215", "Ovada", 7},
        {"RV 2131", "Genova", 15},
        {"R 10217", "Novi Ligure", 3},
        {"R 10219", "Tortona", 0}
    };
    const Treno *p;
    const Treno *peggiore;

    printf("  Pos  Treno    Provenienza      Ritardo   indirizzo\n");
    for (p = arrivi; p < arrivi + TRENI; p++) {
        printf("  %3d  %-8s %-15s %4d min   %p\n", (int) (p - arrivi), p->numero, p->provenienza,
               p->ritardo, (void *) p);
    }
    printf("  (gli indirizzi crescono di sizeof(Treno) = %zu byte)\n", sizeof(Treno));

    peggiore = piu_in_ritardo(arrivi, TRENI);
    printf("\nRitardo maggiore: %s da %s, %d minuti (posizione %d)\n", peggiore->numero,
           peggiore->provenienza, peggiore->ritardo, (int) (peggiore - arrivi));
    printf("Treni puntuali: %d su %d\n", puntuali(arrivi, TRENI), TRENI);

    return 0;
}

/* Puntatore al treno con il ritardo maggiore (il primo, a parità). */
const Treno *piu_in_ritardo(const Treno treni[], int n)
{
    const Treno *p;
    const Treno *peggiore = treni;

    for (p = treni + 1; p < treni + n; p++) {
        if (p->ritardo > peggiore->ritardo) {
            peggiore = p;
        }
    }
    return peggiore;
}

int puntuali(const Treno treni[], int n)
{
    const Treno *p;
    int conteggio = 0;

    for (p = treni; p < treni + n; p++) {
        if (p->ritardo == 0) {
            conteggio++;
        }
    }
    return conteggio;
}
