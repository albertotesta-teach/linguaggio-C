/*
 * 060-problema-consumo-acqua.c
 *
 * Contatore dell'acqua: dai metri cubi letti ai litri consumati
 *
 * Una famiglia annota a fine mese la lettura del contatore dell'acqua, in
 * metri cubi. La lettura cresce sempre: il consumo del mese è la
 * differenza tra due letture consecutive. Il programma calcola:
 *   - il consumo di ogni mese, in metri cubi e in litri (1 m³ = 1000 l);
 *   - il consumo medio giornaliero di ogni mese, in litri per persona;
 *   - il mese con il consumo più alto;
 *   - i mesi oltre la soglia di 150 litri per persona al giorno indicata
 *     dal gestore (la famiglia è di 3 persone).
 *
 * Due nomi distinguono le unità di misura:
 *
 *     typedef double MetriCubi;
 *     typedef double Litri;
 *
 *     MetriCubi consumo(MetriCubi prima, MetriCubi dopo);
 *     Litri in_litri(MetriCubi volume);
 *
 * I nomi aiutano chi legge, ma il compilatore non controlla le unità:
 * passare dei Litri a in_litri sarebbe accettato (vedi 030).
 */

#include <stdio.h>

#define MESI 6
#define SOGLIA_GIORNALIERA 150.0
#define PERSONE 3

typedef double MetriCubi;
typedef double Litri;

MetriCubi consumo(MetriCubi prima, MetriCubi dopo);
Litri in_litri(MetriCubi volume);

int main(void)
{
    const char *mesi[MESI] = {"gennaio", "febbraio", "marzo", "aprile", "maggio", "giugno"};
    int giorni[MESI] = {31, 28, 31, 30, 31, 30};
    /* letture[0] è la lettura del 31 dicembre, letture[m + 1] quella di fine mese m */
    MetriCubi letture[MESI + 1] = {1284.6, 1295.3, 1304.9, 1315.8, 1326.1, 1338.4, 1353.0};
    MetriCubi del_mese;
    Litri al_giorno;
    int m;
    int massimo = 0;
    int oltre = 0;

    printf("  Mese       Consumo m3   Litri   Litri/persona/giorno\n");
    for (m = 0; m < MESI; m++) {
        del_mese = consumo(letture[m], letture[m + 1]);
        al_giorno = in_litri(del_mese) / giorni[m] / PERSONE;
        printf("  %-10s %9.1f  %7.0f  %12.0f%s\n", mesi[m], del_mese, in_litri(del_mese),
               al_giorno, al_giorno > SOGLIA_GIORNALIERA ? "   oltre soglia" : "");
        if (al_giorno > SOGLIA_GIORNALIERA) {
            oltre++;
        }
        if (del_mese > consumo(letture[massimo], letture[massimo + 1])) {
            massimo = m;
        }
    }

    printf("\nConsumo totale del semestre: %.1f m3 (%.0f litri)\n",
           consumo(letture[0], letture[MESI]), in_litri(consumo(letture[0], letture[MESI])));
    printf("Mese con il consumo piu' alto: %s (%.1f m3)\n", mesi[massimo],
           consumo(letture[massimo], letture[massimo + 1]));
    printf("Mesi oltre %.0f litri per persona al giorno: %d\n", SOGLIA_GIORNALIERA, oltre);

    return 0;
}

MetriCubi consumo(MetriCubi prima, MetriCubi dopo)
{
    return dopo - prima;
}

Litri in_litri(MetriCubi volume)
{
    return volume * 1000;
}
