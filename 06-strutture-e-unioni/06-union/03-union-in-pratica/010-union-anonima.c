/*
 * 010-union-anonima.c
 *
 * Union anonima dentro una struct (C11)
 *
 * Con una union con nome, ogni accesso passa dal nome della union:
 *
 *     typedef struct {
 *         TipoDato tipo;
 *         union {
 *             int intero;
 *             double reale;
 *         } v;
 *     } DatoConNome;               d.v.intero
 *
 * Dal C11 la union dentro una struct può non avere nome. I suoi campi si
 * usano come se fossero campi della struct, ma continuano a condividere
 * la memoria:
 *
 *     typedef struct {
 *         TipoDato tipo;
 *         union {
 *             int intero;
 *             double reale;
 *         };
 *     } Dato;                      d.intero
 *
 * Anche l'inizializzazione con il nome dei campi diventa più corta:
 *
 *     Dato d = {.tipo = REALE, .reale = 9.81};
 *
 * Serve -std=c11 (o successivo). I nomi dei campi della union non devono
 * coincidere con quelli della struct.
 *
 * Esempio: lo stesso dato scritto nei due modi, con le dimensioni.
 */

#include <stdio.h>

typedef enum {
    INTERO, REALE
} TipoDato;

typedef struct {
    TipoDato tipo;
    union {
        int intero;
        double reale;
    } v;
} DatoConNome;

typedef struct {
    TipoDato tipo;
    union {
        int intero;
        double reale;
    };
} Dato;

int main(void)
{
    DatoConNome a = {REALE, {.reale = 9.81}};
    Dato b = {.tipo = REALE, .reale = 9.81};
    Dato c = {.tipo = INTERO, .intero = 42};

    printf("a.v.reale = %.2f   (union con nome v)\n", a.v.reale);
    printf("b.reale   = %.2f   (union anonima)\n", b.reale);
    printf("c.intero  = %d\n", c.intero);
    printf("sizeof(DatoConNome) = %zu, sizeof(Dato) = %zu: la memoria e' la stessa\n",
           sizeof(DatoConNome), sizeof(Dato));
    printf("&c.intero == &c.reale? %s\n", (void *) &c.intero == (void *) &c.reale ? "si'" : "no");

    return 0;
}
