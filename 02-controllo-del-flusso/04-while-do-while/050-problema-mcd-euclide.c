/*
 * 050-problema-mcd-euclide.c
 *
 * Massimo comun divisore con l'algoritmo di Euclide
 *
 * Un pasticciere ha 84 cioccolatini e 60 caramelle e vuole preparare
 * sacchetti tutti uguali usando tutti i dolci: quanti sacchetti al massimo?
 * La risposta è il massimo comun divisore MCD(84, 60) = 12.
 *
 * L'algoritmo di Euclide (circa 300 a.C.) si basa su una proprietà:
 *     MCD(a, b) = MCD(b, a % b)
 * e MCD(a, 0) = a. Si sostituisce ripetutamente la coppia (a, b) con
 * (b, a % b) finché b non diventa 0: a quel punto a è il MCD.
 *
 *     a    b    a % b
 *     84   60   24
 *     60   24   12
 *     24   12    0
 *     12    0         -> MCD = 12
 *
 * Il numero di passi non è noto in anticipo: serve un while.
 * Dal MCD si ricava anche il minimo comune multiplo:
 *     mcm(a, b) = a / MCD(a, b) * b
 */

#include <stdio.h>

int main(void)
{
    int primo;
    int secondo;
    int a;
    int b;
    int resto;
    int passo;
    int mcd;
    int mcm;

    printf("=== MCD CON L'ALGORITMO DI EUCLIDE ===\n\n");

    /* Entrambi i numeri devono essere positivi */
    do {
        printf("Primo numero (positivo): ");
        scanf("%d", &primo);
    } while (primo <= 0);

    do {
        printf("Secondo numero (positivo): ");
        scanf("%d", &secondo);
    } while (secondo <= 0);

    /* Si lavora su copie per conservare i valori originali */
    a = primo;
    b = secondo;
    passo = 0;

    printf("\n  Passo |     a |     b | a %% b\n");
    printf("  ------|-------|-------|------\n");

    while (b != 0) {
        resto = a % b;
        passo++;
        printf("  %5d | %5d | %5d | %5d\n", passo, a, b, resto);

        /* la coppia (a, b) diventa (b, a % b) */
        a = b;
        b = resto;
    }

    mcd = a;
    mcm = primo / mcd * secondo;   /* prima la divisione: riduce il rischio di overflow */

    printf("\nMCD(%d, %d) = %d   (trovato in %d passi)\n", primo, secondo, mcd, passo);
    printf("mcm(%d, %d) = %d\n", primo, secondo, mcm);

    if (mcd == 1) {
        printf("I due numeri sono primi tra loro.\n");
    }

    /*
     * NOTA: se il primo numero è minore del secondo, il primo passo li
     * scambia automaticamente: con a = 60 e b = 84, a % b vale 60 e la
     * nuova coppia è (84, 60). Non serve controllare quale sia il maggiore.
     */

    return 0;
}
