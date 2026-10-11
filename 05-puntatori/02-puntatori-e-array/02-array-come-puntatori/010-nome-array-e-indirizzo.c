/*
 * 010-nome-array-e-indirizzo.c
 *
 * Il nome di un array è l'indirizzo del primo elemento
 *
 * In quasi tutte le espressioni il nome di un array viene convertito
 * nell'indirizzo del suo primo elemento:
 *
 *     v          equivale a   &v[0]
 *     v + i      equivale a   &v[i]
 *     v[i]       equivale a   *(v + i)
 *
 * Per questo si può scrivere p = v e poi usare p[i] come se p fosse un
 * array. Array e puntatore però NON sono la stessa cosa:
 *   - sizeof(v) è la dimensione di tutto l'array, sizeof(p) quella di un
 *     indirizzo;
 *   - p è una variabile e si può spostare (p++), v no: v = ... e v++ sono
 *     errori di compilazione.
 *
 * Esempio: i posti liberi nelle aule studio di una biblioteca.
 */

#include <stdio.h>

#define AULE 5

int main(void)
{
    int liberi[AULE] = {14, 3, 0, 22, 9};
    int *p = liberi;                    /* come p = &liberi[0] */
    int i;

    printf("=== IL NOME DELL'ARRAY ===\n");
    printf("  liberi     = %p\n", (void *) liberi);
    printf("  &liberi[0] = %p   (stesso indirizzo)\n", (void *) &liberi[0]);
    printf("  p          = %p\n", (void *) p);

    printf("\n=== QUATTRO MODI DI LEGGERE LO STESSO ELEMENTO ===\n");
    printf("  %-6s %10s %13s %6s %10s\n", "aula", "liberi[i]", "*(liberi + i)", "p[i]", "*(p + i)");
    for (i = 0; i < AULE; i++) {
        printf("  %-6d %10d %13d %6d %10d\n", i + 1, liberi[i], *(liberi + i), p[i], *(p + i));
    }

    printf("\n=== ARRAY E PUNTATORE NON SONO LA STESSA COSA ===\n");
    printf("  sizeof(liberi) = %2zu byte  (tutto l'array: %d int)\n", sizeof(liberi), AULE);
    printf("  sizeof(p)      = %2zu byte  (un indirizzo)\n", sizeof(p));
    printf("  Numero di aule calcolato: sizeof(liberi) / sizeof(liberi[0]) = %zu\n",
           sizeof(liberi) / sizeof(liberi[0]));

    /* p si può spostare, liberi no */
    p++;
    printf("\nDopo p++: p[0] = %d (aula 2), liberi[0] = %d (sempre aula 1)\n", p[0], liberi[0]);
    /* liberi++;   errore di compilazione: il nome di un array non si sposta */

    return 0;
}
