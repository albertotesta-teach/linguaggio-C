/*
 * 080-problema-risparmio-memoria.c
 *
 * Inventario del laboratorio: quanta memoria si risparmia con una union
 *
 * L'inventario contiene articoli di tre tipi, ognuno con dati diversi:
 *   - componente: valore e tolleranza (una resistenza, un condensatore);
 *   - strumento: marca e matricola (un oscilloscopio, un multimetro);
 *   - manuale: autore e anno.
 *
 * Prima soluzione: una struct con tutti i campi. Ogni articolo usa solo
 * i campi del suo tipo, ma occupa spazio per tutti.
 *
 * Seconda soluzione: i dati specifici in una union. Un articolo è un tipo
 * solo, quindi le tre alternative possono condividere la stessa memoria:
 *
 *     typedef struct {
 *         char codice[8];
 *         TipoArticolo tipo;
 *         union {
 *             Componente componente;
 *             Strumento strumento;
 *             Manuale manuale;
 *         } dati;
 *     } ArticoloCompatto;
 *
 * Il campo tipo dice quale alternativa è valida: è la "union con
 * etichetta" della sezione successiva.
 *
 * Il programma stampa le dimensioni delle due soluzioni, legge il numero
 * di articoli dell'inventario e calcola la memoria occupata e quella
 * risparmiata.
 */

#include <stdio.h>

#define MAX_ARTICOLI 100000

typedef enum {
    COMPONENTE, STRUMENTO, MANUALE
} TipoArticolo;

typedef struct {
    double valore;
    double tolleranza;
} Componente;

typedef struct {
    char marca[16];
    char matricola[16];
} Strumento;

typedef struct {
    char autore[24];
    int anno;
} Manuale;

typedef struct {
    char codice[8];
    TipoArticolo tipo;
    Componente componente;
    Strumento strumento;
    Manuale manuale;
} ArticoloCompleto;

typedef struct {
    char codice[8];
    TipoArticolo tipo;
    union {
        Componente componente;
        Strumento strumento;
        Manuale manuale;
    } dati;
} ArticoloCompatto;

int main(void)
{
    ArticoloCompatto esempio = {"R-0047", COMPONENTE, {{4700.0, 0.05}}};
    long articoli;
    long completa;
    long compatta;

    printf("sizeof(Componente) = %zu, sizeof(Strumento) = %zu, sizeof(Manuale) = %zu\n",
           sizeof(Componente), sizeof(Strumento), sizeof(Manuale));
    printf("sizeof(ArticoloCompleto) = %zu byte\n", sizeof(ArticoloCompleto));
    printf("sizeof(ArticoloCompatto) = %zu byte\n", sizeof(ArticoloCompatto));
    printf("Esempio: %s, %.0f ohm +/- %.0f%%\n\n", esempio.codice, esempio.dati.componente.valore,
           esempio.dati.componente.tolleranza * 100);

    printf("Articoli in inventario: ");
    if (scanf("%ld", &articoli) != 1 || articoli < 1 || articoli > MAX_ARTICOLI) {
        printf("Numero non valido (da 1 a %d).\n", MAX_ARTICOLI);
    } else {
        completa = articoli * (long) sizeof(ArticoloCompleto);
        compatta = articoli * (long) sizeof(ArticoloCompatto);
        printf("  struct con tutti i campi: %8ld byte\n", completa);
        printf("  struct con union:         %8ld byte\n", compatta);
        printf("  risparmio:                %8ld byte (%.0f%%)\n", completa - compatta,
               100.0 * (completa - compatta) / completa);
    }

    return 0;
}
