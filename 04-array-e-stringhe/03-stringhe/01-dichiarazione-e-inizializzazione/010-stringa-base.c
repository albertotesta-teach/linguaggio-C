/*
 * 01-stringa-base.c
 *
 * Introduzione alle stringhe in C: dichiarazione, terminatore e stampa.
 *
 * In C non esiste un tipo "stringa" nativo. Una stringa è semplicemente
 * un array di caratteri (char) terminato dal carattere speciale '\0'
 * (ASCII 0), chiamato terminatore di stringa o null terminator.
 *
 * Senza '\0' il programma non saprebbe dove finisce la stringa in memoria.
 */

#include <stdio.h>

int main(void) {

    /* Dichiarazione di una stringa come array di char.
     * La dimensione deve includere il posto per il terminatore '\0'.
     * "Mario" ha 5 caratteri, quindi servono 6 celle. */
    char nome[6] = {'M', 'a', 'r', 'i', 'o', '\0'};

    /* Stampa la stringa con il formato %s (string).
     * printf legge i caratteri uno a uno finché non trova '\0'. */
    printf("Nome: %s\n", nome);

    /* Accesso ai singoli caratteri tramite indice, come in un normale array.
     * Gli indici partono da 0. */
    printf("Primo carattere : %c\n", nome[0]);   /* 'M' */
    printf("Secondo carattere: %c\n", nome[1]);  /* 'a' */
    printf("Terminatore (ASCII): %d\n", nome[5]); /* 0 */

    /* Verifica esplicita del terminatore: nome[5] deve essere '\0' (valore 0) */
    if (nome[5] == '\0') {
        printf("La stringa termina correttamente con il carattere nullo.\n");
    }

    return 0;
}
