/*
 * 050-problema-presenze-palestra.c
 *
 * Palestra della scuola: presenze di un mese, settimana per settimana
 *
 * La palestra è aperta nel pomeriggio ai corsi sportivi. Il custode
 * registra le presenze di ogni giorno per quattro settimane e chiede:
 *   - il totale di ogni settimana e la settimana più frequentata;
 *   - per ogni giorno della settimana, il totale del mese (tutti i lunedì,
 *     tutti i martedì, ...), per decidere in quale giorno servono più
 *     istruttori;
 *   - il giorno più affollato di tutto il mese.
 *
 *     typedef int Settimana[GIORNI];
 *     typedef Settimana Mese[SETTIMANE];
 *
 *     int totale(const Settimana s);
 *     int giorno_massimo(const Settimana s);     indice del giorno
 *
 * I totali per giorno della settimana formano a loro volta una Settimana:
 * le stesse funzioni servono sia per una riga del mese sia per i totali.
 */

#include <stdio.h>

#define GIORNI    6
#define SETTIMANE 4

typedef int Settimana[GIORNI];
typedef Settimana Mese[SETTIMANE];

int totale(const Settimana s);
int giorno_massimo(const Settimana s);

int main(void)
{
    const char *nomi[GIORNI] = {"lun", "mar", "mer", "gio", "ven", "sab"};
    Mese presenze = {
        {34, 41, 28, 39, 45, 18},
        {31, 44, 30, 42, 47, 22},
        {29, 39, 33, 40, 51, 15},
        {36, 46, 27, 43, 49, 20}
    };
    Settimana per_giorno = {0};
    int s;
    int g;
    int migliore = 0;
    int max_s = 0;
    int max_g = 0;

    printf("  Settimana ");
    for (g = 0; g < GIORNI; g++) {
        printf("%5s", nomi[g]);
    }
    printf("  Totale\n");

    for (s = 0; s < SETTIMANE; s++) {
        printf("  %9d ", s + 1);
        for (g = 0; g < GIORNI; g++) {
            printf("%5d", presenze[s][g]);
            per_giorno[g] = per_giorno[g] + presenze[s][g];
        }
        printf("  %6d\n", totale(presenze[s]));
        if (totale(presenze[s]) > totale(presenze[migliore])) {
            migliore = s;
        }
        /* il giorno più affollato della settimana s, confrontato con il
         * record del mese */
        if (presenze[s][giorno_massimo(presenze[s])] > presenze[max_s][max_g]) {
            max_s = s;
            max_g = giorno_massimo(presenze[s]);
        }
    }

    printf("  %9s ", "Mese");
    for (g = 0; g < GIORNI; g++) {
        printf("%5d", per_giorno[g]);
    }
    printf("  %6d\n", totale(per_giorno));

    printf("\nSettimana piu' frequentata: la %d (%d presenze)\n", migliore + 1,
           totale(presenze[migliore]));
    printf("Giorno della settimana con piu' presenze nel mese: %s (%d)\n",
           nomi[giorno_massimo(per_giorno)], per_giorno[giorno_massimo(per_giorno)]);
    printf("Giorno piu' affollato del mese: %s della settimana %d (%d presenze)\n",
           nomi[max_g], max_s + 1, presenze[max_s][max_g]);

    return 0;
}

int totale(const Settimana s)
{
    int somma = 0;
    int g;

    for (g = 0; g < GIORNI; g++) {
        somma = somma + s[g];
    }
    return somma;
}

/* Indice del giorno con più presenze (il primo, a parità). */
int giorno_massimo(const Settimana s)
{
    int migliore = 0;
    int g;

    for (g = 1; g < GIORNI; g++) {
        if (s[g] > s[migliore]) {
            migliore = g;
        }
    }
    return migliore;
}
