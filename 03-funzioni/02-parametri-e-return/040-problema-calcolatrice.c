/*
 * 040-problema-calcolatrice.c
 *
 * Calcolatrice a quattro operazioni
 *
 * Una calcolatrice semplice legge due operandi e un operatore dall'utente
 * ed esegue l'operazione richiesta. Ogni operazione è implementata in una
 * funzione separata che riceve i due operandi e restituisce il risultato.
 * La stampa del risultato è responsabilità esclusiva del main, tramite
 * stampa_risultato(). Nessuna funzione di calcolo stampa nulla.
 */

#include <stdio.h>

/* Prototipi */
double op_somma(double a, double b);
double op_differenza(double a, double b);
double op_prodotto(double a, double b);
double op_quoziente(double a, double b);
void   stampa_risultato(double a, char op, double b, double risultato);

/* --- Funzioni di calcolo --- */

double op_somma(double a, double b)
{
    double risultato;
    risultato = a + b;
    return risultato;
}

double op_differenza(double a, double b)
{
    double risultato;
    risultato = a - b;
    return risultato;
}

double op_prodotto(double a, double b)
{
    double risultato;
    risultato = a * b;
    return risultato;
}

/* In caso di divisione per zero restituisce 0.0 come valore convenzionale.
 * Questa soluzione semplifica il programma ma non distingue il caso di
 * errore dal risultato legittimo: un chiamante non può sapere se 0.0
 * è il risultato di una divisione valida oppure di una per zero.
 * Tecniche più robuste per segnalare errori dalle funzioni verranno
 * introdotte nei capitoli successivi. */
double op_quoziente(double a, double b)
{
    double risultato;
    if (b == 0.0) {
        risultato = 0.0;
    } else {
        risultato = a / b;
    }
    return risultato;
}

/* Stampa la riga di risultato nel formato: a op b = risultato */
void stampa_risultato(double a, char op, double b, double risultato)
{
    printf("  %.2f %c %.2f = %.2f\n", a, op, b, risultato);
}

int main(void)
{
    double a, b, risultato;
    char operatore;

    printf("=== Calcolatrice ===\n");
    printf("Inserire: numero operatore numero\n");
    printf("Operatori supportati: + - * /\n");
    printf("> ");
    scanf("%lf %c %lf", &a, &operatore, &b);

    if (operatore == '+') {
        risultato = op_somma(a, b);
        stampa_risultato(a, operatore, b, risultato);
    } else if (operatore == '-') {
        risultato = op_differenza(a, b);
        stampa_risultato(a, operatore, b, risultato);
    } else if (operatore == '*') {
        risultato = op_prodotto(a, b);
        stampa_risultato(a, operatore, b, risultato);
    } else if (operatore == '/') {
        risultato = op_quoziente(a, b);
        stampa_risultato(a, operatore, b, risultato);
    } else {
        printf("  Operatore '%c' non riconosciuto.\n", operatore);
    }

    return 0;
}
