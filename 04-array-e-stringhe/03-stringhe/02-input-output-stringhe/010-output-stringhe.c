/*
 * 010-output-stringhe.c
 *
 * Le diverse funzioni di output per le stringhe in C.
 *
 * In C esistono più modi per stampare una stringa a video.
 * Ognuno ha caratteristiche diverse che è importante conoscere:
 *
 *   printf("%s", s) → stampa la stringa senza aggiungere nulla
 *   puts(s)         → stampa la stringa e aggiunge automaticamente '\n'
 *   putchar(c)      → stampa un singolo carattere
 *
 * Conoscere le differenze evita errori di formattazione nell'output.
 */

#include <stdio.h>

int main(void) {

    /* Stringa di esempio su cui mostrare i diversi metodi di output */
    char messaggio[] = "Benvenuto nel sistema";

    /* Singolo carattere per dimostrare putchar */
    char iniziale = 'A';

    /* Indice per scorrere la stringa con putchar */
    int i;

    /* --- METODO 1: printf con %s ---
     * Il formato %s stampa tutti i caratteri fino a '\0'.
     * Non aggiunge automaticamente il ritorno a capo: occorre \n esplicito. */
    printf("--- printf con %%s ---\n");
    printf("%s\n", messaggio);
    printf("Dopo printf: siamo sulla riga successiva grazie a \\n esplicito.\n\n");

    /* --- METODO 2: puts ---
     * puts stampa la stringa e aggiunge AUTOMATICAMENTE '\n' alla fine.
     * È più semplice di printf quando non serve formattazione. */
    printf("--- puts ---\n");
    puts(messaggio);
    printf("Dopo puts: il ritorno a capo era automatico.\n\n");

    /* --- METODO 3: printf con formattazione avanzata ---
     * Con printf possiamo controllare la larghezza del campo con %-30s
     * (allineamento a sinistra, campo di 30 caratteri).
     * Utile per creare output tabulare. */
    printf("--- printf con larghezza fissa ---\n");
    printf("%-30s %s\n", "Campo allineato a sinistra:", "valore");
    printf("%-30s %s\n", messaggio, "<-- occupa 30 caratteri");
    printf("\n");

    /* --- METODO 4: putchar su singolo carattere ---
     * putchar stampa un solo char alla volta.
     * Utile quando si vuole controllare ogni carattere individualmente. */
    printf("--- putchar su singolo carattere ---\n");
    printf("Carattere singolo: ");
    putchar(iniziale);   /* stampa 'A' */
    putchar('\n');       /* ritorno a capo manuale */
    printf("\n");

    /* --- METODO 5: putchar in ciclo ---
     * Scorrendo la stringa carattere per carattere con un ciclo while
     * e usando putchar, otteniamo lo stesso effetto di printf("%s").
     * Questo metodo mostra chiaramente come printf legge la stringa
     * internamente: un carattere alla volta fino a '\0'. */
    printf("--- putchar in ciclo (equivalente a printf) ---\n");
    i = 0;
    while (messaggio[i] != '\0') {
        putchar(messaggio[i]); /* stampa il carattere in posizione i */
        i++;                   /* avanza al carattere successivo */
    }
    putchar('\n'); /* aggiunge il ritorno a capo finale */
    printf("\n");

    /* --- CONFRONTO puts vs printf ---
     * Differenza chiave: puts aggiunge '\n', printf no.
     * Il codice seguente produce due righe diverse: */
    printf("--- Confronto: puts aggiunge \\n, printf no ---\n");
    printf("Con printf: ");
    printf("%s", "prima");   /* nessun \n */
    printf("%s", " seconda"); /* continua sulla stessa riga */
    printf("\n");

    printf("Con puts:   ");
    puts("prima");            /* aggiunge \n automaticamente */
    /* "seconda" finirà sulla riga dopo */
    puts("seconda");

    return 0;
}
