/*
 * 030-operatori-di-assegnazione.c
 *
 * Operatori di assegnazione composta e incremento/decremento
 *
 * Presenta gli operatori di assegnazione composta (+=, -=, *=, /=, %=)
 * e gli operatori di incremento e decremento (++, --) nelle forme
 * prefissa e postfissa. Tutto viene dimostrato con assegnazioni dirette
 * e printf, senza strutture di controllo.
 */

#include <stdio.h>

int main(void)
{
    int valore;
    int a;
    int b;

    /* ── assegnazione semplice ───────────────────────────────────────────── */
    printf("=== Assegnazione semplice ===\n");
    valore = 10;
    printf("valore = 10  ->  %d\n", valore);

    /* ── operatori di assegnazione composta ─────────────────────────────── */
    /* Ogni operatore composto è una forma abbreviata dell'assegnazione estesa:
     *   x += n   equivale a   x = x + n   */
    printf("\n=== Assegnazione composta (partendo da valore=10) ===\n");

    valore = 10;
    valore += 5;    /* valore = valore + 5 */
    printf("dopo += 5  ->  %d\n", valore);    /* 15 */

    valore -= 3;    /* valore = valore - 3 */
    printf("dopo -= 3  ->  %d\n", valore);    /* 12 */

    valore *= 2;    /* valore = valore * 2 */
    printf("dopo *= 2  ->  %d\n", valore);    /* 24 */

    valore /= 4;    /* valore = valore / 4 */
    printf("dopo /= 4  ->  %d\n", valore);    /* 6 */

    valore %= 4;    /* valore = valore % 4 */
    printf("dopo %%= 4  ->  %d\n", valore);   /* 2 */

    /* ── uso tipico: accumulatori e contatori ───────────────────────────── */
    printf("\n=== Uso tipico: accumulatore ===\n");
    int somma = 0;
    somma += 10;
    somma += 25;
    somma += 7;
    printf("somma di 10+25+7 = %d\n", somma);

    double totale = 100.0;
    totale *= 1.22;    /* applica IVA del 22% */
    printf("100.00 EUR con IVA al 22%% = %.2f EUR\n", totale);

    /* ── incremento e decremento ────────────────────────────────────────── */
    printf("\n=== Incremento e decremento ===\n");

    /* forma prefissa (++i): prima incrementa, poi usa il valore */
    a = 5;
    b = ++a;    /* a diventa 6, poi b riceve 6 */
    printf("a=5: b = ++a  ->  a=%d, b=%d\n", a, b);

    /* forma postfissa (i++): prima usa il valore, poi incrementa */
    a = 5;
    b = a++;    /* b riceve 5, poi a diventa 6 */
    printf("a=5: b = a++  ->  a=%d, b=%d\n", a, b);

    /* stessa logica per il decremento */
    a = 5;
    b = --a;    /* a diventa 4, poi b riceve 4 */
    printf("a=5: b = --a  ->  a=%d, b=%d\n", a, b);

    a = 5;
    b = a--;    /* b riceve 5, poi a diventa 4 */
    printf("a=5: b = a--  ->  a=%d, b=%d\n", a, b);

    /* ── quando usare prefisso vs postfisso ─────────────────────────────── */
    /*
     * Se il valore di ritorno non viene usato (istruzione autonoma),
     * ++i e i++ sono equivalenti:
     *   i++;   e   ++i;   producono lo stesso effetto su i.
     *
     * La differenza emerge solo quando l'espressione è usata all'interno
     * di un'altra espressione (come nell'esempio b = ++a vs b = a++ sopra).
     *
     * Per chiarezza, preferire la forma prefissa quando il valore
     * intermedio non serve.
     */

    /* ── attenzione: doppio incremento nella stessa espressione ────────── */
    /*
     * PERICOLOSO (comportamento indefinito in C):
     *   int i = 5;
     *   int x = i++ + i++;   // non fare mai questo
     *
     * Modificare la stessa variabile più volte nella stessa espressione
     * produce comportamento indefinito. Usare sempre istruzioni separate.
     */

    return 0;
}
