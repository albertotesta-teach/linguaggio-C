/*
 * 060-problema-tessere-mensa.c
 *
 * Mensa scolastica: il prezzo del pasto dipende dalla fascia ISEE
 *
 * Il comune divide le famiglie in quattro fasce in base all'ISEE. Ogni
 * fascia ha un tetto ISEE e un prezzo del pasto, raccolti in una tabella
 * indicizzata dall'enum:
 *
 *     typedef enum { FASCIA_A, FASCIA_B, FASCIA_C, FASCIA_D,
 *                    NUM_FASCE } Fascia;
 *
 *     typedef struct {
 *         const char *nome;
 *         double isee_massimo;
 *         double prezzo_pasto;
 *     } Tariffa;
 *
 *     typedef struct {
 *         int numero;
 *         char nome[16];
 *         double isee;
 *         Fascia fascia;
 *         int pasti;
 *     } Tessera;
 *
 * All'avvio la fascia di ogni tessera si calcola dall'ISEE: è la prima
 * fascia il cui tetto non è superato. Il prezzo di un pasto è
 * tariffe[t.fascia].prezzo_pasto.
 *
 * Comandi:
 *     P numero    pasto consumato con la tessera
 *     S numero    scheda della tessera, con il totale del mese
 *     R           riepilogo per fascia: tessere, pasti e incasso
 *     Q           fine
 */

#include <stdio.h>

#define TESSERE 5

typedef enum {
    FASCIA_A, FASCIA_B, FASCIA_C, FASCIA_D, NUM_FASCE
} Fascia;

typedef struct {
    const char *nome;
    double isee_massimo;
    double prezzo_pasto;
} Tariffa;

typedef struct {
    int numero;
    char nome[16];
    double isee;
    Fascia fascia;
    int pasti;
} Tessera;

Fascia da_isee(double isee, const Tariffa tariffe[]);
Tessera *cerca(Tessera t[], int n, int numero);

int main(void)
{
    Tariffa tariffe[NUM_FASCE] = {
        [FASCIA_A] = {"A", 8000, 2.00},
        [FASCIA_B] = {"B", 15000, 3.50},
        [FASCIA_C] = {"C", 25000, 4.80},
        [FASCIA_D] = {"D", 1e12, 5.90}
    };
    Tessera tessere[TESSERE] = {
        {101, "Bassi Rita", 6500, FASCIA_A, 3},
        {102, "Corti Ugo", 18200, FASCIA_A, 0},
        {103, "Dini Ada", 31000, FASCIA_A, 2},
        {104, "Elia Gino", 15000, FASCIA_A, 1},
        {105, "Fumo Pia", 9800, FASCIA_A, 0}
    };
    Tessera *t;
    char comando = ' ';
    int numero;
    int quante;
    int pasti;
    double incasso;
    double totale = 0;
    Fascia f;
    int i;

    for (i = 0; i < TESSERE; i++) {
        tessere[i].fascia = da_isee(tessere[i].isee, tariffe);
    }

    while (comando != 'Q') {
        printf("Comando (P numero, S numero, R, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'P' || comando == 'S') {
            if (scanf("%d", &numero) != 1) {
                comando = 'Q';
            } else {
                t = cerca(tessere, TESSERE, numero);
                if (t == NULL) {
                    printf("  Tessera %d inesistente.\n", numero);
                } else {
                    if (comando == 'P') {
                        t->pasti++;
                    }
                    printf("  %d %-11s fascia %s, %.2f euro a pasto, pasti %d: %.2f euro\n",
                           t->numero, t->nome, tariffe[t->fascia].nome,
                           tariffe[t->fascia].prezzo_pasto, t->pasti,
                           t->pasti * tariffe[t->fascia].prezzo_pasto);
                }
            }
        } else if (comando == 'R') {
            totale = 0;
            for (f = FASCIA_A; f < NUM_FASCE; f++) {
                quante = 0;
                pasti = 0;
                for (i = 0; i < TESSERE; i++) {
                    if (tessere[i].fascia == f) {
                        quante++;
                        pasti = pasti + tessere[i].pasti;
                    }
                }
                incasso = pasti * tariffe[f].prezzo_pasto;
                totale = totale + incasso;
                printf("  fascia %s: tessere %d, pasti %2d, %6.2f euro\n", tariffe[f].nome, quante,
                       pasti, incasso);
            }
            printf("  totale %.2f euro\n", totale);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}

/* Prima fascia con il tetto non superato. */
Fascia da_isee(double isee, const Tariffa tariffe[])
{
    Fascia f = FASCIA_A;

    while (f < FASCIA_D && isee > tariffe[f].isee_massimo) {
        f++;
    }
    return f;
}

Tessera *cerca(Tessera t[], int n, int numero)
{
    Tessera *trovata = NULL;
    int i = 0;

    while (i < n && trovata == NULL) {
        if (t[i].numero == numero) {
            trovata = &t[i];
        }
        i++;
    }
    return trovata;
}
