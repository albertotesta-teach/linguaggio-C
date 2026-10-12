/*
 * 030-dimensione-e-allineamento.c
 *
 * sizeof di una struct: i campi e lo spazio di allineamento
 *
 * Il processore legge più velocemente un int se il suo indirizzo è un
 * multiplo di 4 (un double, di 8). Per questo il compilatore può lasciare
 * dei byte vuoti (padding) tra i campi di una struct e alla sua fine:
 * sizeof di una struct può essere MAGGIORE della somma dei campi.
 *
 *     typedef struct {         char      1 byte  + 3 di padding
 *         char stanza;         int       4 byte
 *         int valore;          char      1 byte  + 3 di padding
 *         char unita;      }   totale   12 byte, ma i dati sono 6
 *
 * Mettendo i campi grandi per primi il padding si riduce. La posizione di
 * ogni campo dall'inizio della struct si legge con offsetof, definita in
 * <stddef.h>.
 *
 * I valori esatti dipendono dal compilatore e dal processore: quelli
 * stampati qui sono tipici dei PC a 64 bit.
 *
 * Esempio: le letture dei sensori della serra, memorizzate a migliaia in
 * una centralina con poca memoria.
 */

#include <stdio.h>
#include <stddef.h>

#define LETTURE 10000

typedef struct {
    char stanza;
    int valore;
    char unita;
} Lettura;

typedef struct {
    int valore;
    char stanza;
    char unita;
} LetturaCompatta;

int main(void)
{
    printf("=== Lettura: char, int, char ===\n");
    printf("  stanza: offset %2zu, %zu byte\n", offsetof(Lettura, stanza), sizeof(char));
    printf("  valore: offset %2zu, %zu byte\n", offsetof(Lettura, valore), sizeof(int));
    printf("  unita:  offset %2zu, %zu byte\n", offsetof(Lettura, unita), sizeof(char));
    printf("  sizeof(Lettura) = %zu (dati: %zu)\n\n", sizeof(Lettura), 2 * sizeof(char) + sizeof(int));

    printf("=== LetturaCompatta: int, char, char ===\n");
    printf("  valore: offset %2zu\n", offsetof(LetturaCompatta, valore));
    printf("  stanza: offset %2zu\n", offsetof(LetturaCompatta, stanza));
    printf("  unita:  offset %2zu\n", offsetof(LetturaCompatta, unita));
    printf("  sizeof(LetturaCompatta) = %zu\n\n", sizeof(LetturaCompatta));

    printf("Per %d letture: %zu byte contro %zu byte\n", LETTURE,
           LETTURE * sizeof(Lettura), LETTURE * sizeof(LetturaCompatta));

    return 0;
}
