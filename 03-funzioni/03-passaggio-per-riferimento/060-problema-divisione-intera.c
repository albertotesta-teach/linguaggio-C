/*
 * 060-problema-divisione-intera.c
 *
 * Convertitore di misure: ore/minuti/secondi e euro/centesimi
 *
 * Due conversioni pratiche che producono ciascuna due risultati interi
 * collegati tra loro: non si può restituirli separatamente con due
 * chiamate distinte perché derivano dalla stessa divisione.
 * Il passaggio per riferimento è la soluzione naturale.
 *
 * Conversione 1: secondi totali → ore, minuti, secondi residui
 * Conversione 2: importo in centesimi → euro, centesimi residui
 */

#include <stdio.h>

/* Prototipi */
void secondi_in_hms(int secondi_tot, int *ore, int *minuti, int *sec);
void centesimi_in_euro(int centesimi_tot, int *euro, int *centesimi);
void stampa_durata(int secondi_tot);
void stampa_importo(int centesimi_tot);

/* --- Definizioni --- */

/* Converte un numero di secondi in ore, minuti e secondi residui.
 * Esempio: 3725 secondi → 1 ora, 2 minuti, 5 secondi */
void secondi_in_hms(int secondi_tot, int *ore, int *minuti, int *sec)
{
    *ore    = secondi_tot / 3600;
    *minuti = (secondi_tot % 3600) / 60;
    *sec    = secondi_tot % 60;
}

/* Converte un importo espresso in centesimi in euro e centesimi residui.
 * Esempio: 1275 centesimi → 12 euro, 75 centesimi */
void centesimi_in_euro(int centesimi_tot, int *euro, int *centesimi)
{
    *euro      = centesimi_tot / 100;
    *centesimi = centesimi_tot % 100;
}

void stampa_durata(int secondi_tot)
{
    int ore, minuti, sec;
    secondi_in_hms(secondi_tot, &ore, &minuti, &sec);
    printf("  %5d secondi  →  %dh %02dm %02ds\n",
           secondi_tot, ore, minuti, sec);
}

void stampa_importo(int centesimi_tot)
{
    int euro, centesimi;
    centesimi_in_euro(centesimi_tot, &euro, &centesimi);
    printf("  %5d centesimi →  %d EUR e %02d cent\n",
           centesimi_tot, euro, centesimi);
}

int main(void)
{
    printf("=== Conversione durate ===\n\n");
    stampa_durata(0);
    stampa_durata(59);
    stampa_durata(60);
    stampa_durata(3600);
    stampa_durata(3725);
    stampa_durata(7384);
    stampa_durata(86399);   /* un secondo prima della mezzanotte */

    printf("\n=== Conversione importi ===\n\n");
    stampa_importo(0);
    stampa_importo(99);
    stampa_importo(100);
    stampa_importo(1275);
    stampa_importo(9999);
    stampa_importo(25000);

    return 0;
}
