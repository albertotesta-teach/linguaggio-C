/*
 * 040-problema-equazione-secondo-grado.c
 *
 * Risoluzione di un'equazione di secondo grado  a x^2 + b x + c = 0
 *
 * Il numero di soluzioni reali dipende dal discriminante
 *     delta = b^2 - 4ac
 *   - delta > 0  due soluzioni reali distinte  x = (-b ± sqrt(delta)) / 2a
 *   - delta = 0  due soluzioni coincidenti     x = -b / 2a
 *   - delta < 0  nessuna soluzione reale
 *
 * Se a = 0 l'equazione non è di secondo grado ma di primo grado: b x + c = 0.
 * A sua volta può essere determinata (b != 0), impossibile (b = 0, c != 0)
 * o indeterminata (b = 0, c = 0: ogni x è soluzione).
 *
 * I coefficienti sono interi: così delta è calcolato in modo esatto e il
 * confronto delta == 0 non risente degli errori di arrotondamento dei
 * numeri reali (vedi 01-introduzione/02-variabili-e-tipi/020-tipi-reali.c).
 *
 * La funzione sqrt() della libreria matematica richiede #include <math.h>;
 * su Linux si compila aggiungendo -lm.
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
    int a;
    int b;
    int c;
    int delta;
    double x1;
    double x2;

    printf("=== EQUAZIONE DI SECONDO GRADO: a x^2 + b x + c = 0 ===\n\n");
    printf("Coefficiente a: ");
    scanf("%d", &a);
    printf("Coefficiente b: ");
    scanf("%d", &b);
    printf("Coefficiente c: ");
    scanf("%d", &c);

    printf("\nEquazione: %d x^2 + (%d) x + (%d) = 0\n", a, b, c);

    if (a == 0) {
        /* ── Caso degenere: equazione di primo grado ──────────────── */
        printf("a = 0: l'equazione e' di primo grado.\n");

        if (b != 0) {
            x1 = (double)(-c) / b;
            printf("Soluzione unica: x = %.4f\n", x1);
        } else if (c != 0) {
            printf("Equazione impossibile: nessuna soluzione.\n");
        } else {
            printf("Equazione indeterminata: ogni x e' soluzione.\n");
        }
    } else {
        /* ── Equazione di secondo grado ───────────────────────────── */
        delta = b * b - 4 * a * c;
        printf("Discriminante: delta = %d\n", delta);

        if (delta > 0) {
            x1 = (-b + sqrt(delta)) / (2.0 * a);
            x2 = (-b - sqrt(delta)) / (2.0 * a);
            printf("Due soluzioni reali distinte:\n");
            printf("  x1 = %.4f\n", x1);
            printf("  x2 = %.4f\n", x2);
        } else if (delta == 0) {
            x1 = -b / (2.0 * a);
            printf("Due soluzioni reali coincidenti:\n");
            printf("  x1 = x2 = %.4f\n", x1);
        } else {
            printf("Nessuna soluzione reale (delta negativo).\n");
        }
    }

    /*
     * ERRORI COMUNI
     *
     * 1) Calcolare delta senza controllare prima a == 0: con a = 0 la
     *    formula divide per 2a = 0.
     *
     * 2) Dimenticare le parentesi al denominatore:
     *        x1 = (-b + sqrt(delta)) / 2 * a;     // divide per 2 e MOLTIPLICA per a
     *        x1 = (-b + sqrt(delta)) / (2.0 * a); // corretto
     *
     * 3) Divisione intera: -b / (2 * a) con interi tronca il risultato.
     *    Basta un operando reale (2.0) per ottenere la divisione reale.
     */

    return 0;
}
