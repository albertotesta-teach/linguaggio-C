/*
 * 050-problema-elenco-di-parole.c
 *
 * Il vocabolario di un tema: le parole distinte e quante volte compaiono
 *
 * Per aiutare gli studenti a variare il lessico, il programma elenca le
 * parole distinte di un tema con il numero di ripetizioni. Il numero di
 * parole distinte non si conosce prima, quindi due blocchi crescono di
 * un elemento per ogni parola nuova:
 *
 *     char **parole = NULL;      parole[i]: blocco con la parola i
 *     int *conta = NULL;         conta[i]: ripetizioni della parola i
 *
 *     tmp = realloc(parole, (n + 1) * sizeof *parole);
 *
 * Ogni parola è un blocco a parte, della sua lunghezza: l'array di
 * puntatori contiene solo gli indirizzi. Le parole si confrontano in
 * minuscolo; una parola è una sequenza di lettere (massimo 30).
 *
 * Il programma legge il testo riga per riga fino a FINE e stampa le
 * parole ripetute almeno 3 volte (i candidati a un sinonimo), il numero
 * di parole e di parole distinte. Alla fine libera prima ogni parola e
 * poi i due array.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LUNG 200
#define MAX_PAROLA 31
#define RIPETUTA 3

int cerca(char *parole[], int n, const char *parola);
int aggiungi(char ***parole, int **conta, int n, const char *parola);

int main(void)
{
    char **parole = NULL;
    int *conta = NULL;
    char riga[LUNG];
    char parola[MAX_PAROLA];
    int n = 0;
    int totale = 0;
    int finito = 0;
    int lunghezza;
    int posizione;
    int i;
    int j;

    printf("Testo del tema (FINE per terminare):\n");
    while (!finito) {
        if (fgets(riga, LUNG, stdin) == NULL || strcmp(riga, "FINE\n") == 0 ||
            strcmp(riga, "FINE") == 0) {
            finito = 1;
        } else {
            i = 0;
            while (riga[i] != '\0' && !finito) {
                lunghezza = 0;
                while (isalpha((unsigned char) riga[i])) {
                    if (lunghezza < MAX_PAROLA - 1) {
                        parola[lunghezza] = (char) tolower((unsigned char) riga[i]);
                        lunghezza++;
                    }
                    i++;
                }
                parola[lunghezza] = '\0';
                if (lunghezza > 0) {
                    totale++;
                    posizione = cerca(parole, n, parola);
                    if (posizione != -1) {
                        conta[posizione]++;
                    } else if (aggiungi(&parole, &conta, n, parola)) {
                        n++;
                    } else {
                        printf("Memoria insufficiente.\n");
                        finito = 1;
                    }
                } else {
                    i++;
                }
            }
        }
    }

    printf("\nParole: %d, distinte: %d\n", totale, n);
    printf("Ripetute almeno %d volte:\n", RIPETUTA);
    for (j = 0; j < n; j++) {
        if (conta[j] >= RIPETUTA) {
            printf("  %-12s %d\n", parole[j], conta[j]);
        }
    }

    for (j = 0; j < n; j++) {
        free(parole[j]);
    }
    free(parole);
    free(conta);

    return 0;
}

int cerca(char *parole[], int n, const char *parola)
{
    int trovata = -1;
    int i;

    for (i = 0; i < n && trovata == -1; i++) {
        if (strcmp(parole[i], parola) == 0) {
            trovata = i;
        }
    }
    return trovata;
}

/*
 * Allunga i due array di un elemento e copia la parola in un blocco
 * nuovo. Se un'allocazione fallisce restituisce 0: gli array restano
 * validi e utilizzabili con n elementi.
 */
int aggiungi(char ***parole, int **conta, int n, const char *parola)
{
    char **tmp_parole = realloc(*parole, (n + 1) * sizeof *tmp_parole);
    int *tmp_conta;
    char *copia;
    int ok = tmp_parole != NULL;

    if (ok) {
        *parole = tmp_parole;
        tmp_conta = realloc(*conta, (n + 1) * sizeof *tmp_conta);
        ok = tmp_conta != NULL;
        if (ok) {
            *conta = tmp_conta;
        }
    }
    if (ok) {
        copia = malloc((strlen(parola) + 1) * sizeof *copia);
        ok = copia != NULL;
        if (ok) {
            strcpy(copia, parola);
            (*parole)[n] = copia;
            (*conta)[n] = 1;
        }
    }
    return ok;
}
