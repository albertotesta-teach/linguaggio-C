/*
 * 080-problema-ricerca-con-esito.c
 *
 * Rastrelliera delle biciclette: ingresso e uscita con la tessera
 *
 * Nel cortile della scuola c'è una rastrelliera con POSTI posti per le
 * biciclette, ciascuno con un lucchetto elettronico. posti[i] contiene il
 * numero della tessera che occupa il posto, 0 se è libero.
 *     E tessera   ingresso: la bici occupa il primo posto libero
 *     U tessera   uscita: il posto di quella tessera si libera
 *     Q           fine
 *
 * La ricerca restituisce l'ESITO con return e il PUNTATORE all'elemento
 * trovato in un parametro di uscita di tipo int **:
 *
 *     int cerca(int *v, int n, int valore, int **trovato);
 *
 *     if (cerca(posti, POSTI, 0, &posto)) {    primo posto libero
 *         *posto = tessera;
 *     }
 *
 * Se non trova, cerca restituisce 0 e mette NULL in *trovato.
 */

#include <stdio.h>

#define POSTI 6

int cerca(int *v, int n, int valore, int **trovato);
void stampa(const int *posti, int n);
void svuota_riga(void);

int main(void)
{
    int posti[POSTI] = {0, 2041, 0, 1877, 0, 0};
    int *posto;
    char comando = ' ';
    int tessera;
    int letti;

    stampa(posti, POSTI);
    while (comando != 'Q') {
        printf("Comando (E tessera, U tessera, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'E' || comando == 'U') {
            letti = scanf("%d", &tessera);
            if (letti == EOF) {
                comando = 'Q';          /* input terminato */
            } else if (letti == 0 || tessera <= 0) {
                if (letti == 0) {
                    svuota_riga();      /* non è un numero */
                }
                printf("  Tessera non valida.\n");
            } else if (comando == 'E') {
                if (cerca(posti, POSTI, tessera, &posto)) {
                    printf("  La tessera %d ha gia' una bici al posto %d.\n",
                           tessera, (int) (posto - posti) + 1);
                } else if (cerca(posti, POSTI, 0, &posto)) {
                    *posto = tessera;
                    printf("  Posto %d assegnato.\n", (int) (posto - posti) + 1);
                } else {
                    printf("  Rastrelliera piena.\n");
                }
            } else if (cerca(posti, POSTI, tessera, &posto)) {
                printf("  Posto %d liberato.\n", (int) (posto - posti) + 1);
                *posto = 0;
            } else {
                printf("  Nessuna bici con la tessera %d.\n", tessera);
            }
            stampa(posti, POSTI);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}

/* Cerca valore in v. Se lo trova scrive in *trovato l'indirizzo
 * dell'elemento e restituisce 1; altrimenti scrive NULL e restituisce 0. */
int cerca(int *v, int n, int valore, int **trovato)
{
    int *p = v;

    while (p < v + n && *p != valore) {
        p++;
    }
    if (p < v + n) {
        *trovato = p;
    } else {
        *trovato = NULL;
    }
    return *trovato != NULL;
}

void stampa(const int *posti, int n)
{
    int i;

    printf("  Rastrelliera:");
    for (i = 0; i < n; i++) {
        if (posti[i] == 0) {
            printf(" [ libero ]");
        } else {
            printf(" [%8d]", posti[i]);
        }
    }
    printf("\n");
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
