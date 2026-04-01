/*
 * 010-hello-world.c
 *
 * Il primo programma in C
 *
 * Il programma più semplice possibile in C: stampa una riga di testo
 * sullo schermo e termina. Serve a verificare che l'ambiente di sviluppo
 * funzioni correttamente e a introdurre la struttura minima di un sorgente C.
 */

#include <stdio.h>   /* libreria standard per l'input/output (printf, scanf) */

int main(void)
{
    /* printf stampa una stringa sullo standard output (lo schermo).
     * \n è la sequenza di escape per il carattere "a capo". */
    printf("Ciao, mondo!\n");

    /* main restituisce 0 per indicare al sistema operativo
     * che il programma è terminato senza errori. */
    return 0;
}
