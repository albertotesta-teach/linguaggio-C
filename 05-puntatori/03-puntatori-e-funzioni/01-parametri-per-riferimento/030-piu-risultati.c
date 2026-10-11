/*
 * 030-piu-risultati.c
 *
 * Una funzione che produce più risultati
 *
 * return restituisce un solo valore. Quando una funzione deve produrre più
 * risultati, li scrive in parametri di USCITA: il chiamante passa gli
 * indirizzi delle variabili che riceveranno i risultati.
 *
 *     void scomponi(int totale, int *ore, int *minuti, int *secondi);
 *     scomponi(8130, &h, &m, &s);       h = 2, m = 15, s = 30
 *
 * Il return resta libero per un'informazione in più: qui converti_inverso
 * restituisce il totale e scomponi_giorni restituisce il numero di giorni.
 *
 * Esempio: la durata delle registrazioni di una videocamera di sicurezza,
 * memorizzata in secondi.
 */

#include <stdio.h>

void scomponi(int totale, int *ore, int *minuti, int *secondi);
int converti_inverso(int ore, int minuti, int secondi);
int scomponi_giorni(int totale, int *ore, int *minuti, int *secondi);

int main(void)
{
    int durate[3] = {8130, 59, 200000};
    int ore;
    int minuti;
    int secondi;
    int giorni;
    int i;

    printf("=== DURATA DELLE REGISTRAZIONI ===\n");
    for (i = 0; i < 3; i++) {
        scomponi(durate[i], &ore, &minuti, &secondi);
        printf("  %6d s = %3d h %2d min %2d s\n", durate[i], ore, minuti, secondi);
    }

    printf("\nControllo: 2 h 15 min 30 s = %d s\n", converti_inverso(2, 15, 30));

    giorni = scomponi_giorni(durate[2], &ore, &minuti, &secondi);
    printf("%d s = %d giorni, %d h %d min %d s\n", durate[2], giorni, ore, minuti, secondi);

    return 0;
}

/* Scompone totale secondi in ore, minuti e secondi. */
void scomponi(int totale, int *ore, int *minuti, int *secondi)
{
    *ore = totale / 3600;
    *minuti = totale % 3600 / 60;
    *secondi = totale % 60;
}

int converti_inverso(int ore, int minuti, int secondi)
{
    return ore * 3600 + minuti * 60 + secondi;
}

/* Come scomponi, ma le ore restano sotto 24: i giorni interi escono con
 * return. Riusa scomponi passandole gli stessi puntatori. */
int scomponi_giorni(int totale, int *ore, int *minuti, int *secondi)
{
    int giorni = totale / 86400;

    scomponi(totale % 86400, ore, minuti, secondi);
    return giorni;
}
