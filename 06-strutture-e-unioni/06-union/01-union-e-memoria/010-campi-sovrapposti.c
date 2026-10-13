/*
 * 010-campi-sovrapposti.c
 *
 * union: campi che occupano la stessa memoria
 *
 * Una union si dichiara come una struct, ma i suoi campi non stanno uno
 * dopo l'altro: cominciano tutti allo stesso indirizzo e si
 * sovrappongono.
 *
 *     typedef union {
 *         int intero;
 *         double reale;
 *         char testo[8];
 *     } Valore;
 *
 * Conseguenze:
 *   - sizeof(Valore) è la dimensione del campo più grande (più
 *     l'eventuale allineamento), non la somma dei campi;
 *   - &v.intero, &v.reale e &v.testo sono lo stesso indirizzo;
 *   - in ogni momento la union contiene UN solo valore.
 *
 * Una struct con gli stessi campi può contenerli tutti insieme, ma occupa
 * la somma delle dimensioni. La union serve quando le alternative si
 * escludono: un dato è un numero intero OPPURE un reale OPPURE un testo.
 *
 * Esempio: lo stesso trio di campi in una struct e in una union.
 */

#include <stdio.h>

typedef union {
    int intero;
    double reale;
    char testo[8];
} Valore;

typedef struct {
    int intero;
    double reale;
    char testo[8];
} TreValori;

int main(void)
{
    Valore v;
    TreValori s;

    printf("sizeof(int) = %zu, sizeof(double) = %zu, sizeof(char[8]) = %zu\n", sizeof(int),
           sizeof(double), sizeof(char[8]));
    printf("sizeof(TreValori) = %zu byte (i campi uno dopo l'altro)\n", sizeof(TreValori));
    printf("sizeof(Valore)    = %zu byte (i campi sovrapposti)\n\n", sizeof(Valore));

    printf("Indirizzi nella struct:\n");
    printf("  &s.intero = %p\n  &s.reale  = %p\n  &s.testo  = %p\n", (void *) &s.intero,
           (void *) &s.reale, (void *) &s.testo);
    printf("Indirizzi nella union:\n");
    printf("  &v.intero = %p\n  &v.reale  = %p\n  &v.testo  = %p\n", (void *) &v.intero,
           (void *) &v.reale, (void *) &v.testo);
    printf("Nella union i tre indirizzi sono %s.\n",
           (void *) &v.intero == (void *) &v.reale && (void *) &v.reale == (void *) &v.testo
               ? "uguali"
               : "diversi");

    return 0;
}
