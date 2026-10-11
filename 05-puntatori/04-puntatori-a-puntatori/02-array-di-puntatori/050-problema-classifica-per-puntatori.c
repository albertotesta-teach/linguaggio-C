/*
 * 050-problema-classifica-per-puntatori.c
 *
 * Gara di orientamento: correzione della classifica
 *
 * Alla gara di orientamento la classifica provvisoria è stata compilata
 * all'arrivo. Dopo il controllo dei cartellini, la giuria corregge alcune
 * posizioni scambiando due concorrenti alla volta (ad esempio per una
 * penalità). I nomi e i tempi restano nei loro array: la classifica è
 * fatta di due array di PUNTATORI paralleli,
 *     const char *nome_al_posto[N]    puntano ai nomi
 *     const int *tempo_al_posto[N]    puntano ai tempi
 * e uno scambio di posizioni scambia solo i puntatori.
 *
 * Comandi:
 *     S a b   scambia i concorrenti alle posizioni a e b
 *     Q       fine
 * Dopo ogni scambio il programma stampa la classifica e controlla se i
 * tempi sono in ordine crescente.
 */

#include <stdio.h>

#define CONCORRENTI 5

void scambia_nomi(const char **a, const char **b);
void scambia_tempi(const int **a, const int **b);
void stampa(const char *nomi[], const int *tempi[], int n);
int in_ordine(const int *tempi[], int n);

int main(void)
{
    const char *nomi[CONCORRENTI] = {"Pietro", "Alice", "Irene", "Tommaso", "Nadia"};
    int tempi[CONCORRENTI] = {1830, 1795, 1912, 1801, 1880};   /* secondi */
    const char *nome_al_posto[CONCORRENTI];
    const int *tempo_al_posto[CONCORRENTI];
    char comando = ' ';
    int a;
    int b;
    int i;

    for (i = 0; i < CONCORRENTI; i++) {
        nome_al_posto[i] = nomi[i];
        tempo_al_posto[i] = &tempi[i];
    }
    stampa(nome_al_posto, tempo_al_posto, CONCORRENTI);

    while (comando != 'Q') {
        printf("Comando (S a b, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'S') {
            if (scanf("%d %d", &a, &b) != 2 || a < 1 || b < 1 ||
                a > CONCORRENTI || b > CONCORRENTI) {
                printf("  Posizioni non valide.\n");
                comando = 'Q';
            } else {
                scambia_nomi(&nome_al_posto[a - 1], &nome_al_posto[b - 1]);
                scambia_tempi(&tempo_al_posto[a - 1], &tempo_al_posto[b - 1]);
                stampa(nome_al_posto, tempo_al_posto, CONCORRENTI);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}

void scambia_nomi(const char **a, const char **b)
{
    const char *temp = *a;

    *a = *b;
    *b = temp;
}

void scambia_tempi(const int **a, const int **b)
{
    const int *temp = *a;

    *a = *b;
    *b = temp;
}

void stampa(const char *nomi[], const int *tempi[], int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("  %d. %-8s %2d:%02d\n", i + 1, nomi[i], *tempi[i] / 60, *tempi[i] % 60);
    }
    if (in_ordine(tempi, n)) {
        printf("  Classifica in ordine di tempo.\n");
    } else {
        printf("  Attenzione: tempi non in ordine.\n");
    }
}

/* 1 se ogni tempo è minore o uguale al successivo. */
int in_ordine(const int *tempi[], int n)
{
    int i;
    int ordinata = 1;

    for (i = 0; i < n - 1; i++) {
        if (*tempi[i] > *tempi[i + 1]) {
            ordinata = 0;
        }
    }
    return ordinata;
}
