/*
 * 010-parametri-per-valore.c
 *
 * Passaggio di parametri per valore
 *
 * In C, i parametri scalari (int, double, char, ...) vengono passati
 * alle funzioni PER VALORE: la funzione riceve una COPIA del dato originale.
 * Qualsiasi modifica al parametro all'interno della funzione non cambia
 * la variabile del chiamante. Questo file mostra il meccanismo e le
 * sue conseguenze pratiche.
 */

#include <stdio.h>

/* Prototipi */
void raddoppia(int numero);
void converti_celsius_fahrenheit(double celsius);
void mostra_copia(int valore);

/* --- Definizioni --- */

/* Questa funzione riceve una COPIA di "numero".
 * La modifica di "numero" non ha effetto sulla variabile originale
 * nel chiamante. */
void raddoppia(int numero)
{
    printf("  Dentro raddoppia() - prima:  numero = %d\n", numero);
    numero = numero * 2;
    printf("  Dentro raddoppia() - dopo:   numero = %d\n", numero);
    /* Quando la funzione termina, la copia locale "numero" viene distrutta.
     * La variabile originale nel main rimane invariata. */
}

/* La funzione calcola e stampa la conversione.
 * Non modifica il parametro (ma anche se lo facesse, non cambierebbe
 * la variabile del chiamante). */
void converti_celsius_fahrenheit(double celsius)
{
    double fahrenheit;

    /* La formula di conversione: F = C * 9/5 + 32 */
    fahrenheit = celsius * 9.0 / 5.0 + 32.0;

    printf("  %.1f gradi Celsius = %.1f gradi Fahrenheit\n",
           celsius, fahrenheit);
}

/* Questa funzione dimostra esplicitamente che il parametro è una copia:
 * stampa l'indirizzo di memoria del parametro locale (sarà diverso
 * dall'indirizzo della variabile originale nel main). */
void mostra_copia(int valore)
{
    printf("  Dentro mostra_copia(): valore = %d, indirizzo = %p\n",
           valore, (void *)&valore);
}

int main(void)
{
    int temperatura_stanza = 20;
    double temp_bollo = 100.0;

    /* --- Dimostrazione 1: la copia non modifica l'originale --- */
    printf("=== Dimostrazione: passaggio per valore ===\n\n");

    printf("Prima della chiamata: temperatura_stanza = %d\n",
           temperatura_stanza);
    raddoppia(temperatura_stanza);
    printf("Dopo la chiamata:     temperatura_stanza = %d\n",
           temperatura_stanza);
    /* temperatura_stanza è ancora 20: la funzione ha modificato solo la copia */

    printf("\n");

    /* --- Dimostrazione 2: uso pratico del parametro --- */
    printf("=== Conversioni di temperatura ===\n\n");
    converti_celsius_fahrenheit(0.0);
    converti_celsius_fahrenheit(temp_bollo);
    converti_celsius_fahrenheit(37.0);
    converti_celsius_fahrenheit(-40.0);

    printf("\n");

    /* --- Dimostrazione 3: indirizzi di memoria diversi --- */
    printf("=== Indirizzi di memoria ===\n\n");
    printf("Nel main: temperatura_stanza = %d, indirizzo = %p\n",
           temperatura_stanza, (void *)&temperatura_stanza);
    mostra_copia(temperatura_stanza);
    /* L'indirizzo stampato dentro la funzione sarà diverso:
     * il parametro vive in un posto diverso della memoria (stack) */

    return 0;
}
