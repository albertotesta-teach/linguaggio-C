/*
 * 040-problema-prodotto-matrici.c
 *
 * Prodotto tra matrici: listino prezzi e ordini dei negozi
 *
 * Tre negozi di una catena ordinano al grossista quattro articoli:
 *   ordini[NEGOZI][ARTICOLI]       pezzi ordinati da ogni negozio
 * Il grossista ha due listini (prezzo all'ingrosso e prezzo consigliato
 * al pubblico) per ogni articolo:
 *   prezzi[ARTICOLI][LISTINI]
 *
 * Il prodotto righe per colonne  costi = ordini x prezzi  dà, per ogni
 * negozio, la spesa con il listino all'ingrosso e il ricavo previsto con
 * il prezzo al pubblico:
 *
 *   costi[i][j] = somma per k di  ordini[i][k] * prezzi[k][j]
 *
 * Il prodotto A x B esiste solo se le COLONNE di A sono quante le RIGHE
 * di B; il risultato ha le righe di A e le colonne di B.
 *
 * Le funzioni devono lavorare su matrici di dimensioni diverse, ma nel
 * parametro il numero di colonne è fisso. Soluzione: tutte le matrici
 * vengono dichiarate MAX x MAX e si passano a parte le dimensioni
 * effettivamente usate (una matrice "più grande del necessario", usata
 * solo in parte).
 */

#include <stdio.h>

#define MAX 5

#define NEGOZI   3
#define ARTICOLI 4
#define LISTINI  2

void stampa_matrice(const double m[][MAX], int righe, int colonne);
int moltiplica(const double a[][MAX], int righe_a, int colonne_a,
               const double b[][MAX], int righe_b, int colonne_b,
               double risultato[][MAX]);

int main(void)
{
    double ordini[MAX][MAX] = {
        {10,  5, 20,  0},
        { 4, 12,  6,  8},
        { 0,  3, 15, 10}
    };
    double prezzi[MAX][MAX] = {
        {12.50, 19.90},
        { 8.00, 14.50},
        { 3.20,  5.90},
        {22.00, 34.00}
    };
    double costi[MAX][MAX];
    int esito;
    int n;

    printf("=== ORDINI (negozi x articoli) ===\n");
    stampa_matrice(ordini, NEGOZI, ARTICOLI);
    printf("\n=== PREZZI (articoli x listini: ingrosso, pubblico) ===\n");
    stampa_matrice(prezzi, ARTICOLI, LISTINI);

    esito = moltiplica(ordini, NEGOZI, ARTICOLI,
                       prezzi, ARTICOLI, LISTINI, costi);

    if (esito) {
        printf("\n=== COSTI = ORDINI x PREZZI (negozi x listini) ===\n");
        stampa_matrice(costi, NEGOZI, LISTINI);

        printf("\n  Negozio   Spesa   Ricavo   Margine\n");
        for (n = 0; n < NEGOZI; n++) {
            printf("  %7d %7.2f %8.2f %9.2f\n", n + 1,
                   costi[n][0], costi[n][1], costi[n][1] - costi[n][0]);
        }
    } else {
        printf("Dimensioni incompatibili: impossibile moltiplicare.\n");
    }

    /* Tentativo con le dimensioni nell'ordine sbagliato: prezzi x ordini
     * richiederebbe LISTINI == NEGOZI, cioè 2 == 3. */
    printf("\nProva: prezzi (4 x 2) x ordini (3 x 4)\n");
    esito = moltiplica(prezzi, ARTICOLI, LISTINI,
                       ordini, NEGOZI, ARTICOLI, costi);
    if (!esito) {
        printf("  Dimensioni incompatibili: le colonne del primo (%d) devono\n", LISTINI);
        printf("  essere quante le righe del secondo (%d).\n", NEGOZI);
    }

    return 0;
}

/* Stampa la parte righe x colonne di una matrice MAX x MAX. */
void stampa_matrice(const double m[][MAX], int righe, int colonne)
{
    int r;
    int c;

    for (r = 0; r < righe; r++) {
        for (c = 0; c < colonne; c++) {
            printf("%9.2f", m[r][c]);
        }
        printf("\n");
    }
}

/* Calcola risultato = a x b. Restituisce 1 se il prodotto è possibile,
 * 0 se le dimensioni sono incompatibili (in quel caso risultato non viene
 * toccato). Il risultato ha righe_a righe e colonne_b colonne. */
int moltiplica(const double a[][MAX], int righe_a, int colonne_a,
               const double b[][MAX], int righe_b, int colonne_b,
               double risultato[][MAX])
{
    int i;
    int j;
    int k;
    int possibile;

    possibile = (colonne_a == righe_b);

    if (possibile) {
        for (i = 0; i < righe_a; i++) {
            for (j = 0; j < colonne_b; j++) {
                /* riga i di a "per" colonna j di b */
                risultato[i][j] = 0.0;
                for (k = 0; k < colonne_a; k++) {
                    risultato[i][j] = risultato[i][j] + a[i][k] * b[k][j];
                }
            }
        }
    }
    return possibile;
}
