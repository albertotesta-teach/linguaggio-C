/*
 * 010-realloc-casi-limite.c
 *
 * realloc con NULL e con dimensione zero
 *
 * Due casi particolari:
 *
 *   1. realloc(NULL, byte) si comporta come malloc(byte). Così un elenco
 *      può partire VUOTO, con il puntatore a NULL e n = 0, e ogni
 *      aggiunta usa sempre realloc, senza un caso speciale per la prima:
 *
 *          char **titoli = NULL;
 *          int n = 0;
 *          tmp = realloc(titoli, (n + 1) * sizeof *titoli);
 *
 *   2. realloc(p, 0) va evitato. Fino al C17 il risultato dipende dalla
 *      libreria (può liberare il blocco e restituire NULL, oppure
 *      restituire un blocco di 0 byte), e dal C23 il comportamento non è
 *      definito. Per svuotare si scrive in modo esplicito:
 *
 *          free(p);
 *          p = NULL;
 *          n = 0;
 *
 * Esempio: l'elenco dei libri consigliati per l'estate parte vuoto, si
 * riempie con tre titoli usando solo realloc, poi viene svuotato con free
 * e riempito di nuovo da zero.
 */

#include <stdio.h>
#include <stdlib.h>

#define TITOLI 3

int aggiungi(const char ***elenco, int *n, const char *titolo);
void stampa(const char **elenco, int n);

int main(void)
{
    const char *estate[TITOLI] = {"Il barone rampante", "Marcovaldo", "Lessico famigliare"};
    const char **elenco = NULL;
    int n = 0;
    int i;

    printf("Elenco vuoto: puntatore %s, n = %d\n", elenco == NULL ? "NULL" : "non NULL", n);
    for (i = 0; i < TITOLI; i++) {
        if (aggiungi(&elenco, &n, estate[i])) {
            printf("aggiunto \"%s\" (titoli: %d)\n", estate[i], n);
        }
    }
    stampa(elenco, n);

    free(elenco);
    elenco = NULL;
    n = 0;
    printf("\nElenco svuotato con free: n = %d\n", n);

    if (aggiungi(&elenco, &n, "Il giornalino di Gian Burrasca")) {
        printf("Si riparte da NULL (titoli: %d)\n", n);
    }
    stampa(elenco, n);
    free(elenco);

    return 0;
}

/* Allunga l'elenco di un posto; la prima volta *elenco è NULL. */
int aggiungi(const char ***elenco, int *n, const char *titolo)
{
    const char **tmp = realloc(*elenco, (*n + 1) * sizeof *tmp);

    if (tmp != NULL) {
        tmp[*n] = titolo;
        *elenco = tmp;
        (*n)++;
    }
    return tmp != NULL;
}

void stampa(const char **elenco, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("  %d. %s\n", i + 1, elenco[i]);
    }
}
