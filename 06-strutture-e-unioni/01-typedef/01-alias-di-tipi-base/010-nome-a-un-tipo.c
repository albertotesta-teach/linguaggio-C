/*
 * 010-nome-a-un-tipo.c
 *
 * typedef: dare un nome a un tipo che esiste già
 *
 * La parola chiave typedef introduce un NUOVO NOME per un tipo esistente:
 *
 *     typedef int Voto;          da qui in poi Voto significa int
 *     typedef double Euro;       Euro significa double
 *     typedef int Minuti;        Minuti significa int
 *
 * La sintassi è quella di una dichiarazione di variabile preceduta da
 * typedef: il nome che sarebbe stato la variabile diventa il nome del tipo.
 * Per convenzione del corso i nomi dei tipi hanno l'iniziale maiuscola.
 *
 * Il vantaggio è la leggibilità: "Euro costo" dice che cosa rappresenta il
 * dato, "double costo" dice solo come è memorizzato.
 *
 * Esempio: la giornata scolastica di uno studente, con il voto di una
 * verifica, il costo del pranzo e i minuti di studio a casa.
 */

#include <stdio.h>

/* Le typedef si scrivono di solito all'inizio del file, dopo gli #include,
 * così il nuovo nome è disponibile in tutto il programma. */
typedef int Voto;
typedef double Euro;
typedef int Minuti;

int main(void)
{
    Voto verifica_matematica = 7;
    Euro pranzo = 4.80;
    Euro merenda = 1.20;
    Minuti studio_pomeriggio = 75;
    Minuti studio_sera = 40;

    /* Le variabili si usano come quelle del tipo originale: stessi
     * operatori, stessi formati di printf (%d per int, %.2f per double). */
    printf("=== LA GIORNATA ===\n");
    printf("  Voto della verifica:  %d\n", verifica_matematica);
    printf("  Spesa del giorno:     %.2f euro\n", pranzo + merenda);
    printf("  Studio a casa:        %d minuti (%d h %d min)\n",
           studio_pomeriggio + studio_sera,
           (studio_pomeriggio + studio_sera) / 60,
           (studio_pomeriggio + studio_sera) % 60);

    /* Il nuovo nome ha esattamente la dimensione del tipo originale:
     * typedef non cambia nulla in memoria. */
    printf("\n=== DIMENSIONI ===\n");
    printf("  sizeof(Voto)   = %zu   sizeof(int)    = %zu\n", sizeof(Voto), sizeof(int));
    printf("  sizeof(Euro)   = %zu   sizeof(double) = %zu\n", sizeof(Euro), sizeof(double));
    printf("  sizeof(Minuti) = %zu   sizeof(int)    = %zu\n", sizeof(Minuti), sizeof(int));

    return 0;
}
