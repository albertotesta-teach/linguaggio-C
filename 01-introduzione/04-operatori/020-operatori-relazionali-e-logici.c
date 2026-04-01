/*
 * 020-operatori-relazionali-e-logici.c
 *
 * Operatori relazionali e logici in C
 *
 * Mostra che ogni espressione relazionale o logica produce un valore
 * intero: 0 (falso) oppure 1 (vero). Questo valore può essere salvato
 * in una variabile int e usato come qualsiasi altro numero.
 * Non si usano if/else: gli operatori vengono dimostrati come espressioni
 * con un valore numerico, non come condizioni di controllo del flusso.
 */

#include <stdio.h>

int main(void)
{
    int eta        = 22;
    int altezza_cm = 175;
    double stipendio = 1800.0;
    int    a = 10;
    int    b = 20;

    /* ── operatori relazionali ───────────────────────────────────────────── */
    /* Ciascuna espressione vale 0 (falso) o 1 (vero).
     * Il risultato può essere assegnato a una variabile int. */
    printf("=== Operatori relazionali ===\n");
    printf("a=%d, b=%d\n\n", a, b);

    printf("a == b  -> %d\n", a == b);    /* uguale */
    printf("a != b  -> %d\n", a != b);    /* diverso */
    printf("a <  b  -> %d\n", a <  b);    /* minore */
    printf("a >  b  -> %d\n", a >  b);    /* maggiore */
    printf("a <= b  -> %d\n", a <= b);    /* minore o uguale */
    printf("a >= b  -> %d\n", a >= b);    /* maggiore o uguale */

    /* ── salvataggio del risultato in una variabile ─────────────────────── */
    /* È pratica comune salvare il risultato di un confronto in una
     * variabile int con un nome che descrive la condizione. */
    printf("\n=== Risultati salvati in variabili ===\n");

    int maggiorenne    = (eta >= 18);
    int in_range_eta   = (eta >= 18 && eta <= 65);
    int alta_statura   = (altezza_cm > 180);
    int stipendio_ok   = (stipendio >= 1500.0);

    printf("eta=%d: maggiorenne=%d\n",       eta, maggiorenne);
    printf("eta in [18,65]:    %d\n",         in_range_eta);
    printf("altezza>180cm:     %d\n",         alta_statura);
    printf("stipendio>=1500:   %d\n",         stipendio_ok);

    /* ── operatori logici ───────────────────────────────────────────────── */
    printf("\n=== Operatori logici ===\n");

    /* && (AND): vero solo se entrambi i valori sono veri (diversi da 0) */
    printf("maggiorenne && stipendio_ok  -> %d\n", maggiorenne && stipendio_ok);
    printf("alta_statura && stipendio_ok -> %d\n", alta_statura && stipendio_ok);

    /* || (OR): vero se almeno uno dei valori è vero */
    printf("alta_statura || maggiorenne  -> %d\n", alta_statura || maggiorenne);
    printf("alta_statura || (eta > 100)  -> %d\n", alta_statura || (eta > 100));

    /* ! (NOT): inverte il valore: 0 diventa 1, diverso da 0 diventa 0 */
    printf("!maggiorenne                 -> %d\n", !maggiorenne);
    printf("!alta_statura                -> %d\n", !alta_statura);

    /* ── condizioni composte tipiche ────────────────────────────────────── */
    printf("\n=== Condizioni composte ===\n");

    int accesso_consentito = (eta >= 18) && (stipendio >= 1000.0);
    int fuori_intervallo   = (altezza_cm < 150) || (altezza_cm > 210);
    int nessun_requisito   = !(maggiorenne || stipendio_ok);

    printf("accesso consentito (eta>=18 E stip>=1000): %d\n", accesso_consentito);
    printf("altezza fuori [150,210]:                   %d\n", fuori_intervallo);
    printf("nessun requisito soddisfatto:              %d\n", nessun_requisito);

    /* ── nota sul corto circuito (in commento) ──────────────────────────── */
    /*
     * VALUTAZIONE A CORTO CIRCUITO:
     *
     * Con &&: se il primo operando è 0 (falso), il secondo NON viene
     * valutato perché il risultato è già falso.
     *   es.  0 && espressione_costosa  -> espressione_costosa non eseguita
     *
     * Con ||: se il primo operando è diverso da 0 (vero), il secondo
     * NON viene valutato perché il risultato è già vero.
     *   es.  1 || espressione_costosa  -> espressione_costosa non eseguita
     *
     * Questo comportamento è garantito dallo standard C ed è importante
     * per evitare divisioni per zero o accessi a puntatori nulli
     * (argomenti dei capitoli successivi).
     */

    return 0;
}
