/*
 * 080-problema-classifica-unita.c
 *
 * Gara di atletica: la classifica unica di due batterie
 *
 * I 100 metri si sono corsi in due batterie. I tempi di ciascuna batteria
 * sono già in ordine crescente (in centesimi di secondo). Per la classifica
 * finale bisogna FONDERE i due elenchi in un unico elenco ordinato, senza
 * riordinare tutto da capo.
 *
 * Si usano tre puntatori:
 *   pa   il primo tempo non ancora usato della batteria A
 *   pb   il primo tempo non ancora usato della batteria B
 *   pc   la prossima posizione libera della classifica
 * A ogni passo si copia in *pc il minore tra *pa e *pb e si fa avanzare il
 * puntatore usato. Quando una batteria è finita si copiano i tempi rimasti
 * dell'altra. Un quarto puntatore, pv, scrive in parallelo la batteria di
 * provenienza ('A' o 'B').
 */

#include <stdio.h>

#define ATLETI_A 5
#define ATLETI_B 4
#define TOTALE   (ATLETI_A + ATLETI_B)

int main(void)
{
    int batteria_a[ATLETI_A] = {1185, 1212, 1240, 1301, 1355};
    int batteria_b[ATLETI_B] = {1179, 1226, 1238, 1290};
    int classifica[TOTALE];
    char provenienza[TOTALE];
    const int *pa = &batteria_a[0];
    const int *fine_a = pa + ATLETI_A;
    const int *pb = &batteria_b[0];
    const int *fine_b = pb + ATLETI_B;
    int *pc = &classifica[0];
    char *pv = &provenienza[0];
    int posto;

    /* fusione finché entrambe le batterie hanno tempi */
    while (pa < fine_a && pb < fine_b) {
        if (*pa <= *pb) {
            *pc = *pa;
            *pv = 'A';
            pa++;
        } else {
            *pc = *pb;
            *pv = 'B';
            pb++;
        }
        pc++;
        pv++;
    }

    /* tempi rimasti: al massimo uno dei due cicli viene eseguito */
    while (pa < fine_a) {
        *pc = *pa;
        *pv = 'A';
        pa++;
        pc++;
        pv++;
    }
    while (pb < fine_b) {
        *pc = *pb;
        *pv = 'B';
        pb++;
        pc++;
        pv++;
    }

    printf("=== CLASSIFICA FINALE 100 METRI ===\n");
    for (posto = 0; posto < TOTALE; posto++) {
        printf("  %d. %2d.%02d s   batteria %c", posto + 1,
               classifica[posto] / 100, classifica[posto] % 100, provenienza[posto]);
        if (posto < 3) {
            printf("   medaglia");
        }
        printf("\n");
    }
    printf("Posizioni scritte: pc - &classifica[0] = %d\n", (int) (pc - &classifica[0]));

    return 0;
}
