/*
 * 040-problema-scambio-posti.c
 *
 * Aula di informatica: due studenti si scambiano la postazione
 *
 * In laboratorio ogni studente ha una scheda con il nome e la postazione
 * assegnata (fila e numero del PC):
 *
 *     typedef struct {
 *         char nome[20];
 *         int fila;
 *         int pc;
 *     } Postazione;
 *
 * Il docente vuole scambiare di posto due studenti. Due struct si
 * scambiano come due int, con una variabile di appoggio:
 *
 *     temp = a;  a = b;  b = temp;
 *
 * Ma così si scambiano TUTTI i campi, nome compreso: ognuno resta al suo
 * posto e cambia solo l'etichetta della variabile. Per spostare gli
 * studenti bisogna scambiare solo i campi della postazione (fila e pc).
 *
 * Il programma legge le due schede, mostra il risultato dello scambio
 * sbagliato e di quello corretto, e controlla che i due studenti non
 * avessero già la stessa postazione.
 */

#include <stdio.h>

typedef struct {
    char nome[20];
    int fila;
    int pc;
} Postazione;

int main(void)
{
    Postazione primo;
    Postazione secondo;
    Postazione sbagliato_primo;
    Postazione sbagliato_secondo;
    Postazione temp;
    int appoggio;

    printf("Primo studente (nome fila pc): ");
    if (scanf("%19s %d %d", primo.nome, &primo.fila, &primo.pc) != 3) {
        primo.fila = 0;
    }
    printf("Secondo studente (nome fila pc): ");
    if (scanf("%19s %d %d", secondo.nome, &secondo.fila, &secondo.pc) != 3) {
        secondo.fila = 0;
    }

    if (primo.fila <= 0 || primo.pc <= 0 || secondo.fila <= 0 || secondo.pc <= 0) {
        printf("Dati non validi.\n");
    } else if (primo.fila == secondo.fila && primo.pc == secondo.pc) {
        printf("I due studenti hanno gia' la stessa postazione: controllare il registro.\n");
    } else {
        /* scambio SBAGLIATO: scambia le intere schede, nomi compresi */
        sbagliato_primo = primo;
        sbagliato_secondo = secondo;
        temp = sbagliato_primo;
        sbagliato_primo = sbagliato_secondo;
        sbagliato_secondo = temp;
        printf("\nScambio delle schede intere (sbagliato):\n");
        printf("  %-8s fila %d pc %d\n", sbagliato_primo.nome, sbagliato_primo.fila, sbagliato_primo.pc);
        printf("  %-8s fila %d pc %d\n", sbagliato_secondo.nome, sbagliato_secondo.fila, sbagliato_secondo.pc);
        printf("  ogni nome ha ancora la sua postazione: nessuno si e' spostato\n");

        /* scambio CORRETTO: solo i campi della postazione */
        appoggio = primo.fila;
        primo.fila = secondo.fila;
        secondo.fila = appoggio;
        appoggio = primo.pc;
        primo.pc = secondo.pc;
        secondo.pc = appoggio;
        printf("\nScambio di fila e pc (corretto):\n");
        printf("  %-8s fila %d pc %d\n", primo.nome, primo.fila, primo.pc);
        printf("  %-8s fila %d pc %d\n", secondo.nome, secondo.fila, secondo.pc);
    }

    return 0;
}
