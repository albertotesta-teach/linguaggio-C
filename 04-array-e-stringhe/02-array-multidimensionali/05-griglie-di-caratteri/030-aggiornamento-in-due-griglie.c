/*
 * 030-aggiornamento-in-due-griglie.c
 *
 * Aggiornare una griglia "tutta insieme": perché servono due matrici
 *
 * In una simulazione lo stato al passo successivo si calcola a partire
 * dallo stato ATTUALE di tutte le celle. Se si modifica la griglia mentre
 * la si scorre, le celle esaminate dopo vedono valori già aggiornati e il
 * risultato dipende dall'ordine di scorrimento: è sbagliato.
 *
 * Esempio: un incendio in un bosco. Regola: un albero '^' prende fuoco
 * ('*') se una delle 4 celle adiacenti (sopra, sotto, sinistra, destra)
 * sta bruciando. A ogni passo il fuoco dovrebbe avanzare di UNA cella.
 *
 *   SBAGLIATO  aggiornare sul posto: scorrendo da sinistra a destra, un
 *              albero appena acceso accende subito il suo vicino a destra,
 *              e il fuoco attraversa tutta la riga in un solo passo.
 *   CORRETTO   leggere dalla griglia attuale e scrivere in una griglia
 *              nuova, poi copiare la nuova nell'attuale.
 */

#include <stdio.h>

#define RIGHE   3
#define COLONNE 10
#define ALBERO  '^'
#define FUOCO   '*'

void stampa(const char g[][COLONNE + 1], int passo);
int brucia_vicino(const char g[][COLONNE + 1], int r, int c);
void copia(char dest[][COLONNE + 1], const char sorg[][COLONNE + 1]);

int main(void)
{
    char bosco[RIGHE][COLONNE + 1] = {
        "^^^^^^^^^^",
        "*^^^^^^^^^",
        "^^^^^^^^^^"
    };
    char sul_posto[RIGHE][COLONNE + 1];
    char nuova[RIGHE][COLONNE + 1];
    int r;
    int c;
    int passo;

    /* ── SBAGLIATO: un passo aggiornando sul posto ────────────────── */
    copia(sul_posto, bosco);
    printf("=== Aggiornamento sul posto (SBAGLIATO) ===\n");
    stampa(sul_posto, 0);
    for (r = 0; r < RIGHE; r++) {
        for (c = 0; c < COLONNE; c++) {
            if (sul_posto[r][c] == ALBERO && brucia_vicino(sul_posto, r, c)) {
                sul_posto[r][c] = FUOCO;
            }
        }
    }
    stampa(sul_posto, 1);
    printf("In un solo passo il fuoco ha raggiunto tutto il bosco.\n\n");

    /* ── CORRETTO: tre passi con la seconda griglia ───────────────── */
    printf("=== Aggiornamento con due griglie (CORRETTO) ===\n");
    copia(nuova, bosco);        /* nuova parte uguale, terminatori compresi */
    stampa(bosco, 0);
    for (passo = 1; passo <= 3; passo++) {
        for (r = 0; r < RIGHE; r++) {
            for (c = 0; c < COLONNE; c++) {
                /* si LEGGE da bosco e si SCRIVE in nuova */
                if (bosco[r][c] == ALBERO && brucia_vicino(bosco, r, c)) {
                    nuova[r][c] = FUOCO;
                } else {
                    nuova[r][c] = bosco[r][c];
                }
            }
        }
        copia(bosco, nuova);        /* la nuova generazione diventa l'attuale */
        stampa(bosco, passo);
    }

    return 0;
}

void stampa(const char g[][COLONNE + 1], int passo)
{
    int r;
    int c;

    printf("passo %d\n", passo);
    for (r = 0; r < RIGHE; r++) {
        printf("  ");
        for (c = 0; c < COLONNE; c++) {
            printf("%c", g[r][c]);
        }
        printf("\n");
    }
}

/* 1 se una delle 4 celle adiacenti (non diagonali) è in fiamme. */
int brucia_vicino(const char g[][COLONNE + 1], int r, int c)
{
    int fuoco = 0;

    if (r > 0 && g[r - 1][c] == FUOCO) {
        fuoco = 1;
    }
    if (r < RIGHE - 1 && g[r + 1][c] == FUOCO) {
        fuoco = 1;
    }
    if (c > 0 && g[r][c - 1] == FUOCO) {
        fuoco = 1;
    }
    if (c < COLONNE - 1 && g[r][c + 1] == FUOCO) {
        fuoco = 1;
    }
    return fuoco;
}

/* Copia tutte le celle, compreso il '\0' finale di ogni riga. */
void copia(char dest[][COLONNE + 1], const char sorg[][COLONNE + 1])
{
    int r;
    int c;

    for (r = 0; r < RIGHE; r++) {
        for (c = 0; c <= COLONNE; c++) {      /* <= : copia anche il '\0' */
            dest[r][c] = sorg[r][c];
        }
    }
}
