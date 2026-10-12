/*
 * 020-array-come-parametro.c
 *
 * Un tipo array come parametro: il nome nasconde la dimensione, non il
 * passaggio per indirizzo
 *
 * Con typedef int Settimana[7]; i prototipi diventano molto leggibili:
 *
 *     int totale(const Settimana s);
 *     void azzera_festivi(Settimana s);
 *
 * Ma il nome non cambia le regole degli array (capitolo 05): alla funzione
 * arriva l'indirizzo del primo elemento. Quindi
 *   - const Settimana s  equivale a  const int *s;
 *   - dentro la funzione sizeof(s) è la dimensione di un indirizzo, non 28;
 *   - una funzione che riceve Settimana (senza const) modifica l'array del
 *     chiamante, perché lavora sugli stessi elementi.
 *
 * La dimensione 7 resta però scritta in un solo punto, la typedef, e chi
 * legge il prototipo sa che l'array ha un elemento per ogni giorno.
 *
 * Esempio: le ore di apertura del laboratorio di informatica.
 */

#include <stdio.h>

#define GIORNI 7

typedef int Settimana[GIORNI];

int totale(const Settimana s);
void stampa(const char *titolo, const Settimana s);
void azzera_festivi(Settimana s);

int main(void)
{
    Settimana ore_laboratorio = {6, 8, 6, 7, 5, 4, 2};

    stampa("Orario proposto", ore_laboratorio);
    /* Nel main ore_laboratorio è l'array: 28 byte. Nelle funzioni il
     * parametro s è un puntatore, const int *: sizeof(s) darebbe 8 e gcc e
     * clang lo segnalano con un avviso (-Wsizeof-array-argument). Per
     * questo le funzioni usano GIORNI e non sizeof. */
    printf("  sizeof nel main: %zu byte; nelle funzioni s e' un indirizzo da %zu byte\n",
           sizeof(ore_laboratorio), sizeof(const int *));

    /* la funzione modifica l'array del main */
    azzera_festivi(ore_laboratorio);
    stampa("\nDopo azzera_festivi", ore_laboratorio);

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

void stampa(const char *titolo, const Settimana s)
{
    int g;

    printf("%s:\n  L  M  M  G  V  S  D\n ", titolo);
    for (g = 0; g < GIORNI; g++) {
        printf("%2d ", s[g]);
    }
    printf("  totale %d ore\n", totale(s));
}

/* Il laboratorio resta chiuso la domenica: s[6] modifica il chiamante. */
void azzera_festivi(Settimana s)
{
    s[GIORNI - 1] = 0;
}
