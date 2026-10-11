/*
 * 010-passaggio-matrice-a-funzione.c
 *
 * Passare una matrice a una funzione
 *
 * Come un array, una matrice passata a una funzione NON viene copiata:
 * la funzione riceve l'indirizzo della prima riga e lavora sulla memoria
 * del chiamante. Le modifiche sono quindi visibili nel main.
 *
 * Nel parametro va indicato il NUMERO DI COLONNE; il numero di righe si
 * passa come parametro separato:
 *
 *     void stampa(const int m[][COLONNE], int righe);
 *
 * Perché le colonne sono obbligatorie? La matrice è in memoria riga dopo
 * riga (01-dichiarazione-e-inizializzazione/030). Per trovare m[r][c] la
 * funzione calcola la posizione  r * COLONNE + c : senza COLONNE non
 * saprebbe dove inizia la riga r.
 *
 * Il qualificatore const segnala che la funzione legge la matrice senza
 * modificarla.
 *
 * Una singola riga m[r] è un array monodimensionale: si può passare a
 * qualsiasi funzione scritta per gli array.
 */

#include <stdio.h>

#define RIGHE   3
#define COLONNE 4

/* Prototipi */
void stampa_matrice(const int m[][COLONNE], int righe);
void raddoppia(int m[][COLONNE], int righe);
int somma_array(const int v[], int n);

int main(void)
{
    int m[RIGHE][COLONNE] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int r;

    printf("=== Matrice originale ===\n");
    stampa_matrice(m, RIGHE);

    /* ── 1. La funzione modifica la matrice del chiamante ─────────── */
    raddoppia(m, RIGHE);
    printf("\n=== Dopo raddoppia(m, RIGHE) ===\n");
    stampa_matrice(m, RIGHE);

    /* ── 2. Passare solo le prime righe ───────────────────────────────
     * Il numero di righe è un parametro: si può elaborare una parte
     * della matrice.                                                   */
    printf("\n=== Solo le prime 2 righe ===\n");
    stampa_matrice(m, 2);

    /* ── 3. Una riga come array monodimensionale ──────────────────────
     * m[r] ha tipo "array di COLONNE interi": somma_array, scritta per
     * gli array, funziona senza modifiche.                            */
    printf("\n=== Somma di ogni riga con somma_array(m[r], COLONNE) ===\n");
    for (r = 0; r < RIGHE; r++) {
        printf("  riga %d: %d\n", r, somma_array(m[r], COLONNE));
    }

    return 0;
}

/* Stampa le prime "righe" righe della matrice come tabella. */
void stampa_matrice(const int m[][COLONNE], int righe)
{
    int r;
    int c;

    for (r = 0; r < righe; r++) {
        for (c = 0; c < COLONNE; c++) {
            printf("%5d", m[r][c]);
        }
        printf("\n");
    }
}

/* Raddoppia ogni elemento: senza const, perché scrive nella matrice. */
void raddoppia(int m[][COLONNE], int righe)
{
    int r;
    int c;

    for (r = 0; r < righe; r++) {
        for (c = 0; c < COLONNE; c++) {
            m[r][c] = m[r][c] * 2;
        }
    }
}

/* Funzione "da array": restituisce la somma dei primi n elementi. */
int somma_array(const int v[], int n)
{
    int i;
    int somma = 0;

    for (i = 0; i < n; i++) {
        somma = somma + v[i];
    }
    return somma;
}

/*
 * ERRORI COMUNI
 *
 * 1) Omettere le colonne nel parametro:
 *        void stampa_matrice(const int m[][], int righe);   // ERRORE
 *
 * 2) Passare una matrice con un numero di colonne diverso:
 *        int altra[3][5];
 *        stampa_matrice(altra, 3);   // warning: tipo incompatibile
 *    La funzione accetta solo matrici con esattamente COLONNE colonne.
 *
 * 3) Chiamare con le parentesi: stampa_matrice(m[][], RIGHE) è un errore
 *    di sintassi; si passa solo il nome: stampa_matrice(m, RIGHE).
 */
