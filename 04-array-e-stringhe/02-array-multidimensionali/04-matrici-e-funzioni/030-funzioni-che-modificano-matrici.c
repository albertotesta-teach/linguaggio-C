/*
 * 030-funzioni-che-modificano-matrici.c
 *
 * Funzioni che trasformano una matrice
 *
 * Poiché la matrice non viene copiata, una funzione può modificarla
 * direttamente. Il parametro è senza const. Le funzioni di questo file:
 *
 *   riempi(m, valore)        tutte le celle uguali a valore
 *   copia(dest, sorg)        copia elemento per elemento (le matrici non
 *                            si possono assegnare con =)
 *   scala(m, fattore)        moltiplica ogni cella per un fattore
 *   trasponi(m)              trasposta sul posto (matrice quadrata)
 *   ruota_destra(dest, sorg) rotazione di 90 gradi in senso orario
 *
 * Tutte lavorano su matrici quadrate N x N, così le funzioni hanno la
 * stessa firma (capitolo 03: firme uniformi tra funzioni simili).
 */

#include <stdio.h>

#define N 3

void stampa(const int m[][N], const char titolo[]);
void riempi(int m[][N], int valore);
void copia(int dest[][N], const int sorg[][N]);
void scala(int m[][N], int fattore);
void trasponi(int m[][N]);
void ruota_destra(int dest[][N], const int sorg[][N]);

int main(void)
{
    int a[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    int b[N][N];

    stampa(a, "a originale");

    copia(b, a);
    scala(b, 10);
    stampa(b, "b = copia di a, poi scala(b, 10)");
    stampa(a, "a dopo le operazioni su b (invariata)");

    copia(b, a);
    trasponi(b);
    stampa(b, "trasposta di a");

    ruota_destra(b, a);
    stampa(b, "a ruotata di 90 gradi in senso orario");

    riempi(b, 0);
    stampa(b, "riempi(b, 0)");

    return 0;
}

/* Stampa un titolo e la matrice. Il titolo è una costante stringa:
 * qui serve solo a passarla a printf. */
void stampa(const int m[][N], const char titolo[])
{
    int r;
    int c;

    printf("%s:\n", titolo);
    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            printf("%5d", m[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

void riempi(int m[][N], int valore)
{
    int r;
    int c;

    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            m[r][c] = valore;
        }
    }
}

/* dest = sorg, elemento per elemento. Prima la destinazione, poi la
 * sorgente, come in un'assegnazione. */
void copia(int dest[][N], const int sorg[][N])
{
    int r;
    int c;

    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            dest[r][c] = sorg[r][c];
        }
    }
}

void scala(int m[][N], int fattore)
{
    int r;
    int c;

    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            m[r][c] = m[r][c] * fattore;
        }
    }
}

/* Scambia le coppie [r][c] e [c][r] sopra la diagonale. */
void trasponi(int m[][N])
{
    int r;
    int c;
    int appoggio;

    for (r = 0; r < N; r++) {
        for (c = r + 1; c < N; c++) {
            appoggio = m[r][c];
            m[r][c] = m[c][r];
            m[c][r] = appoggio;
        }
    }
}

/* Rotazione oraria: la riga r della sorgente diventa la colonna
 * N - 1 - r della destinazione.  dest[c][N - 1 - r] = sorg[r][c]
 * Serve una matrice diversa dalla sorgente: scrivendo sulla stessa
 * matrice si perderebbero valori non ancora copiati. */
void ruota_destra(int dest[][N], const int sorg[][N])
{
    int r;
    int c;

    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            dest[c][N - 1 - r] = sorg[r][c];
        }
    }
}

/*
 * ERRORE COMUNE: assegnare una matrice.
 *     int b[N][N];
 *     b = a;            // ERRORE di compilazione
 * Si copia elemento per elemento, come in copia().
 */
