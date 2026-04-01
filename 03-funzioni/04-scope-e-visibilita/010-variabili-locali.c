/*
 * 010-variabili-locali.c
 *
 * Variabili locali: durata e visibilità
 *
 * Una variabile locale è dichiarata all'interno di un blocco (una funzione
 * o un blocco delimitato da graffe). Essa:
 *   - esiste solo per la durata del blocco in cui è dichiarata
 *   - è invisibile al di fuori di quel blocco
 *   - viene creata ogni volta che il blocco viene eseguito e
 *     distrutta quando il blocco termina
 *
 * Due funzioni diverse possono usare variabili con lo stesso nome:
 * si tratta di variabili distinte, in locazioni di memoria distinte.
 */

#include <stdio.h>

/* Prototipi */
void funzione_a(void);
void funzione_b(void);
void dimostra_blocchi(void);

/* funzione_a ha una variabile locale chiamata "valore" */
void funzione_a(void)
{
    int valore = 10;   /* "valore" locale a funzione_a */
    printf("funzione_a: valore = %d  (indirizzo: %p)\n",
           valore, (void *)&valore);
}

/* funzione_b ha anch'essa una variabile chiamata "valore",
 * completamente indipendente da quella di funzione_a */
void funzione_b(void)
{
    int valore = 99;   /* "valore" locale a funzione_b: variabile diversa */
    printf("funzione_b: valore = %d  (indirizzo: %p)\n",
           valore, (void *)&valore);
}

/* Le variabili locali vivono solo nel blocco in cui sono dichiarate.
 * Blocchi annidati con graffe creano scope separati. */
void dimostra_blocchi(void)
{
    int x = 1;
    printf("blocco esterno: x = %d\n", x);

    {
        /* Questo blocco interno ha il proprio scope.
         * La variabile y esiste solo qui. */
        int y = 2;
        printf("blocco interno: x = %d, y = %d\n", x, y);
        /* x è ancora visibile perché dichiarata nel blocco esterno */
    }

    /* Qui y non esiste più: il suo blocco è terminato.
     * Tentare di usare y qui sarebbe un errore di compilazione. */
    printf("blocco esterno (dopo il blocco interno): x = %d\n", x);
    /* printf("y = %d\n", y);  <-- ERRORE: y non è visibile qui */
}

int main(void)
{
    printf("=== Variabili locali in funzioni diverse ===\n\n");

    /* Le due chiamate usano variabili "valore" distinte.
     * Gli indirizzi stampati saranno diversi. */
    funzione_a();
    funzione_b();
    funzione_a();   /* una nuova "valore" viene creata e distrutta */

    printf("\n=== Variabili locali in blocchi annidati ===\n\n");
    dimostra_blocchi();

    printf("\n=== Variabile locale al main ===\n\n");
    {
        int locale_main = 42;
        printf("locale_main = %d\n", locale_main);
        /* locale_main non è visibile in funzione_a o funzione_b */
    }

    return 0;
}
