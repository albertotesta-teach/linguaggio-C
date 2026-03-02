/*
 * 030-scansione-con-ciclo.c
 *
 * Pattern fondamentale: scansione di una stringa carattere per carattere.
 *
 * Scorrere una stringa con un ciclo while è il pattern base per
 * qualsiasi elaborazione testuale in C. Ad ogni iterazione si esamina
 * un carattere e si decide cosa fare: contarlo, modificarlo, stamparlo.
 *
 * In questo esempio si contano le categorie di caratteri presenti
 * in un testo: vocali, consonanti, cifre, spazi e altri simboli.
 *
 * Tecnica di classificazione:
 *   - Vocali:     confronto con 'a','e','i','o','u' (maiuscole e minuscole)
 *   - Cifre:      carattere >= '0' && carattere <= '9'
 *   - Spazi:      carattere == ' '
 *   - Consonanti: lettera che non è vocale
 *   - Altri:      tutto il resto (punteggiatura, simboli)
 */

#include <stdio.h>

int main(void) {

    /* Testo da analizzare */
    char testo[] = "Il C e' un linguaggio potente: usa 42 istruzioni!";

    /* Contatori per ogni categoria */
    int num_vocali     = 0;
    int num_consonanti = 0;
    int num_cifre      = 0;
    int num_spazi      = 0;
    int num_altri      = 0;
    int totale         = 0;

    /* Carattere corrente e flag di classificazione */
    char c;
    int  è_vocale;
    int  è_lettera;

    /* Indice per scorrere la stringa */
    int i;

    printf("=== ANALISI CARATTERI DI UN TESTO ===\n\n");
    printf("Testo: \"%s\"\n\n", testo);

    /* --- SCANSIONE PRINCIPALE ---
     * Scorriamo il testo un carattere alla volta.
     * Per ogni carattere determiniamo la sua categoria
     * e incrementiamo il contatore corrispondente. */
    i = 0;
    while (testo[i] != '\0') {

        c = testo[i]; /* carattere corrente */

        /* Verifica se è una vocale (maiuscola o minuscola) */
        è_vocale = (c == 'a' || c == 'e' || c == 'i' ||
                    c == 'o' || c == 'u' ||
                    c == 'A' || c == 'E' || c == 'I' ||
                    c == 'O' || c == 'U');

        /* Verifica se è una lettera dell'alfabeto */
        è_lettera = ((c >= 'a' && c <= 'z') ||
                     (c >= 'A' && c <= 'Z'));

        /* Classificazione e conteggio */
        if (c == ' ') {
            num_spazi++;                  /* spazio */
        } else if (c >= '0' && c <= '9') {
            num_cifre++;                  /* cifra numerica */
        } else if (è_vocale) {
            num_vocali++;                 /* vocale */
        } else if (è_lettera) {
            num_consonanti++;             /* consonante (lettera non vocale) */
        } else {
            num_altri++;                  /* punteggiatura, simboli, ecc. */
        }

        totale++;
        i++;
    }

    /* --- STAMPA RISULTATI ---
     * Riepilogo delle categorie trovate con conteggi e percentuali. */
    printf("%-15s %6s %8s\n", "Categoria", "Numero", "Percent.");
    printf("-------------------------------\n");
    printf("%-15s %6d %7d%%\n", "Vocali",      num_vocali,
           (num_vocali * 100) / totale);
    printf("%-15s %6d %7d%%\n", "Consonanti",  num_consonanti,
           (num_consonanti * 100) / totale);
    printf("%-15s %6d %7d%%\n", "Cifre",       num_cifre,
           (num_cifre * 100) / totale);
    printf("%-15s %6d %7d%%\n", "Spazi",       num_spazi,
           (num_spazi * 100) / totale);
    printf("%-15s %6d %7d%%\n", "Altri",       num_altri,
           (num_altri * 100) / totale);
    printf("-------------------------------\n");
    printf("%-15s %6d\n", "Totale", totale);

    return 0;
}
