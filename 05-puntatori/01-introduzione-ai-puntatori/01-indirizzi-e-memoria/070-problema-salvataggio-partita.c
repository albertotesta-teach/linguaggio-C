/*
 * 070-problema-salvataggio-partita.c
 *
 * Quanto spazio occupa il salvataggio di una partita
 *
 * Un piccolo gioco a livelli salva lo stato della partita copiando così
 * come sono, byte per byte, le variabili che lo descrivono. La dimensione
 * del file di salvataggio è quindi la somma delle dimensioni delle
 * variabili.
 *
 * Il programma elenca le variabili dello stato con tipo, indirizzo e
 * dimensione, calcola la dimensione del salvataggio e quanti slot di
 * salvataggio entrano in una memoria di MEMORIA_SLOT byte.
 *
 * Poi confronta due scelte per la mappa dei livelli completati:
 *   - un array di int (un intero, 0 o 1, per livello);
 *   - un array di char (basta un byte per un valore 0 o 1).
 *
 * Gli indirizzi cambiano a ogni esecuzione.
 */

#include <stdio.h>

#define LIVELLI       40
#define MEMORIA_SLOT  1024

int main(void)
{
    int vite = 3;
    long punteggio = 125400L;
    short livello = 12;
    double tempo_gioco = 5423.7;        /* secondi */
    char personaggio = 'M';
    int completati_int[LIVELLI] = {0};
    char completati_char[LIVELLI] = {0};
    size_t base;
    size_t con_int;
    size_t con_char;

    printf("=== STATO DELLA PARTITA ===\n");
    printf("  %-16s %-9s %-16s %5s\n", "Variabile", "Tipo", "Indirizzo", "Byte");
    printf("  %-16s %-9s %-16p %5zu\n", "vite", "int", (void *) &vite, sizeof(vite));
    printf("  %-16s %-9s %-16p %5zu\n", "punteggio", "long", (void *) &punteggio, sizeof(punteggio));
    printf("  %-16s %-9s %-16p %5zu\n", "livello", "short", (void *) &livello, sizeof(livello));
    printf("  %-16s %-9s %-16p %5zu\n", "tempo_gioco", "double", (void *) &tempo_gioco,
           sizeof(tempo_gioco));
    printf("  %-16s %-9s %-16p %5zu\n", "personaggio", "char", (void *) &personaggio,
           sizeof(personaggio));
    printf("  %-16s %-9s %-16p %5zu\n", "completati_int", "int[40]",
           (void *) &completati_int[0], sizeof(completati_int));
    printf("  %-16s %-9s %-16p %5zu\n", "completati_char", "char[40]",
           (void *) &completati_char[0], sizeof(completati_char));

    base = sizeof(vite) + sizeof(punteggio) + sizeof(livello)
         + sizeof(tempo_gioco) + sizeof(personaggio);
    con_int = base + sizeof(completati_int);
    con_char = base + sizeof(completati_char);

    printf("\n=== DIMENSIONE DEL SALVATAGGIO ===\n");
    printf("  livelli come int  : %4zu byte -> %2zu slot in %d byte\n",
           con_int, MEMORIA_SLOT / con_int, MEMORIA_SLOT);
    printf("  livelli come char : %4zu byte -> %2zu slot in %d byte\n",
           con_char, MEMORIA_SLOT / con_char, MEMORIA_SLOT);
    printf("  Usare char per i livelli fa risparmiare %zu byte a salvataggio.\n",
           con_int - con_char);
    printf("  (Partita di esempio: vite %d, livello %d, punteggio %ld, personaggio %c, %.0f s)\n",
           vite, livello, punteggio, personaggio, tempo_gioco);

    return 0;
}
