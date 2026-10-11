/*
 * 060-problema-indovina-numero.c
 *
 * Gioco: indovina il numero segreto
 *
 * Il computer sceglie un numero segreto tra 1 e 100. Il giocatore ha
 * al massimo 7 tentativi; dopo ogni tentativo il programma risponde
 * "troppo alto" o "troppo basso".
 *
 * Il ciclo deve terminare in due casi: numero indovinato oppure tentativi
 * esauriti. Nel corso non si esce dal ciclo con break: la condizione di
 * continuazione contiene ENTRAMBI i motivi per proseguire, uniti da AND,
 * e una variabile flag (indovinato) registra la vittoria.
 *
 *     while (!indovinato && tentativi < MAX_TENTATIVI)
 *
 * Per De Morgan, il ciclo si ferma quando
 *     indovinato || tentativi >= MAX_TENTATIVI
 * cioè esattamente nei due casi previsti.
 *
 * Il numero segreto è generato con rand(): srand(time(NULL)) inizializza
 * il generatore con l'ora corrente, così il numero cambia a ogni partita.
 * Con 7 tentativi, dimezzando ogni volta l'intervallo, si vince sempre.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MINIMO          1
#define MASSIMO       100
#define MAX_TENTATIVI   7

int main(void)
{
    int segreto;
    int proposta;
    int tentativi = 0;
    int indovinato = 0;

    srand((unsigned int) time(NULL));
    segreto = MINIMO + rand() % (MASSIMO - MINIMO + 1);

    printf("=== INDOVINA IL NUMERO ===\n");
    printf("Ho pensato un numero tra %d e %d. Hai %d tentativi.\n\n",
           MINIMO, MASSIMO, MAX_TENTATIVI);

    while (!indovinato && tentativi < MAX_TENTATIVI) {
        printf("Tentativo %d: ", tentativi + 1);
        scanf("%d", &proposta);

        if (proposta < MINIMO || proposta > MASSIMO) {
            /* Una proposta fuori intervallo non consuma un tentativo */
            printf("  Inserisci un numero tra %d e %d.\n", MINIMO, MASSIMO);
        } else {
            tentativi++;

            if (proposta == segreto) {
                indovinato = 1;
            } else if (proposta < segreto) {
                printf("  Troppo basso.\n");
            } else {
                printf("  Troppo alto.\n");
            }
        }
    }

    /* Dopo il ciclo il flag dice PERCHÉ è terminato */
    if (indovinato) {
        printf("\nIndovinato! Il numero era %d (%d tentativi).\n", segreto, tentativi);
    } else {
        printf("\nTentativi esauriti. Il numero era %d.\n", segreto);
    }

    /*
     * VERSIONE DA EVITARE (con break)
     *
     *     while (tentativi < MAX_TENTATIVI) {
     *         ...
     *         if (proposta == segreto) {
     *             break;        // uscita nascosta nel corpo del ciclo
     *         }
     *     }
     *
     * Leggendo solo la riga del while sembra che il ciclo termini soltanto
     * per i tentativi esauriti. Vedi 06-break-continue.
     */

    return 0;
}
