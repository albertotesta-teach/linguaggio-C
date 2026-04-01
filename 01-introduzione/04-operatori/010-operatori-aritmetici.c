/*
 * 010-operatori-aritmetici.c
 *
 * Operatori aritmetici in C
 *
 * Presenta i cinque operatori aritmetici fondamentali: addizione (+),
 * sottrazione (-), moltiplicazione (*), divisione (/) e modulo (%).
 * Il punto centrale è la distinzione tra divisione intera (tra due int)
 * e divisione reale (almeno un operando double). L'operatore modulo
 * è valido solo per interi e restituisce il resto della divisione intera.
 */

#include <stdio.h>

int main(void)
{
    int    a = 17;
    int    b = 5;
    double x = 17.0;
    double y = 5.0;

    /* ── addizione, sottrazione, moltiplicazione ────────────────────────── */
    printf("=== Operazioni di base ===\n");
    printf("a = %d,  b = %d\n\n", a, b);
    printf("a + b = %d\n", a + b);
    printf("a - b = %d\n", a - b);
    printf("a * b = %d\n", a * b);

    /* ── divisione: intera vs reale ─────────────────────────────────────── */
    /* Quando entrambi gli operandi sono int, il risultato è int:
     * la parte decimale viene TRONCATA (non arrotondata). */
    printf("\n=== Divisione intera vs reale ===\n");
    printf("17 / 5   (int / int)    = %d   <- parte decimale persa!\n", a / b);
    printf("17.0 / 5 (double / int) = %.4f <- risultato corretto\n",  x / b);
    printf("17 / 5.0 (int / double) = %.4f <- basta un operando double\n", a / y);
    printf("17.0/5.0 (double/double)= %.4f\n", x / y);

    /* cast esplicito: converte temporaneamente a in double per la divisione */
    printf("(double)a / b           = %.4f <- cast esplicito\n", (double)a / b);

    /* ── operatore modulo ───────────────────────────────────────────────── */
    /* % restituisce il resto della divisione intera.
     * Valido SOLO per operandi interi. */
    printf("\n=== Operatore modulo (%%) ===\n");
    printf("17 %% 5  = %d   (17 = 5*3 + 2)\n", a % b);
    printf("10 %% 2  = %d   (pari: resto zero)\n", 10 % 2);
    printf("11 %% 2  = %d   (dispari: resto uno)\n", 11 % 2);
    printf("17 %% 10 = %d   (ultima cifra di 17)\n", 17 % 10);
    printf("123 %% 100 = %d (ultime due cifre)\n", 123 % 100);

    /* ── operatori unari ────────────────────────────────────────────────── */
    printf("\n=== Operatori unari ===\n");
    printf("+a = %d\n", +a);    /* unario +: non cambia il valore */
    printf("-a = %d\n", -a);    /* unario -: cambia il segno */

    /* ── precedenza degli operatori ─────────────────────────────────────── */
    /* *, / e % hanno precedenza maggiore di + e -.
     * Le parentesi forzano l'ordine di valutazione. */
    printf("\n=== Precedenza ===\n");
    printf("2 + 3 * 4     = %d  (prima *)\n", 2 + 3 * 4);
    printf("(2 + 3) * 4   = %d  (parentesi prima)\n", (2 + 3) * 4);
    printf("10 - 4 / 2    = %d  (prima /)\n", 10 - 4 / 2);
    printf("(10 - 4) / 2  = %d  (parentesi prima)\n", (10 - 4) / 2);

    return 0;
}
