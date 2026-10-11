/*
 * 020-puntatore-a-riga.c
 *
 * Un puntatore che indica una riga intera
 *
 * Il nome di una matrice int m[R][C] diventa l'indirizzo della prima
 * RIGA, cioè un puntatore a un array di C int:
 *
 *     int (*riga)[C];          puntatore a una riga di C int
 *     riga = m;                punta alla riga 0
 *     riga++;                  passa alla riga successiva (C * 4 byte dopo)
 *     (*riga)[j]               elemento j della riga puntata
 *
 * Le parentesi sono essenziali: int *riga[C] sarebbe un array di C
 * puntatori a int (sezione 02).
 *
 * Una funzione che riceve una matrice con parametro int m[][C] riceve in
 * realtà proprio un int (*m)[C].
 *
 * Esempio: le vendite mensili (in pezzi) di quattro negozi di una catena
 * di cartolerie, nel primo semestre.
 */

#include <stdio.h>

#define NEGOZI 4
#define MESI   6

int totale_riga(const int (*riga)[MESI]);

int main(void)
{
    int vendite[NEGOZI][MESI] = {
        {120, 95, 140, 160, 110, 180},
        {80, 70, 90, 85, 100, 120},
        {200, 180, 210, 190, 230, 260},
        {60, 65, 70, 50, 55, 90}
    };
    const char *negozi[NEGOZI] = {"Centro", "Stazione", "Universita'", "Periferia"};
    int (*riga)[MESI];
    int (*migliore)[MESI] = vendite;
    int j;

    printf("=== SCORRIMENTO PER RIGHE CON riga++ ===\n");
    for (riga = vendite; riga < vendite + NEGOZI; riga++) {
        printf("  %-12s", negozi[riga - vendite]);
        for (j = 0; j < MESI; j++) {
            printf(" %4d", (*riga)[j]);
        }
        printf("   totale %4d\n", totale_riga(riga));
        if (totale_riga(riga) > totale_riga(migliore)) {
            migliore = riga;
        }
    }

    printf("\nNegozio con piu' vendite: %s (%d pezzi)\n",
           negozi[migliore - vendite], totale_riga(migliore));
    printf("sizeof(*riga) = %zu byte: riga++ avanza di una riga intera.\n", sizeof(*riga));

    return 0;
}

/* Somma degli elementi della riga puntata. */
int totale_riga(const int (*riga)[MESI])
{
    int j;
    int somma = 0;

    for (j = 0; j < MESI; j++) {
        somma = somma + (*riga)[j];
    }
    return somma;
}
