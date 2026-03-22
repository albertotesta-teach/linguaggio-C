/*
 * 010-accesso-per-indice.c
 *
 * Accesso agli elementi di un array tramite indice.
 *
 * Ogni elemento di un array è accessibile direttamente specificando
 * il suo indice tra parentesi quadre. L'indice può essere una costante
 * intera, una variabile o un'espressione intera. Questo file mostra
 * le diverse forme di accesso in lettura e in scrittura, e illustra
 * cosa succede quando si tenta di accedere a un indice non valido.
 */

#include <stdio.h>

#define DIMENSIONE 6

int main(void) {

    int misure[DIMENSIONE] = {42, 17, 95, 8, 63, 31};
    int i;
    int indice;

    /* ------------------------------------------------------------------ */
    /* Accesso in lettura con indice costante.
     * L'indice è noto a compile time: il compilatore calcola l'offset. */
    printf("Accesso con indice costante:\n");
    printf("  misure[0] = %d  (primo elemento)\n", misure[0]);
    printf("  misure[2] = %d  (terzo elemento)\n", misure[2]);
    printf("  misure[5] = %d  (ultimo elemento, indice = DIMENSIONE-1)\n", misure[5]);
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Accesso in lettura con indice variabile.
     * L'indice è calcolato a runtime: utile in cicli e algoritmi. */
    i = 3;
    printf("Accesso con indice variabile (i = %d):\n", i);
    printf("  misure[i] = misure[%d] = %d\n", i, misure[i]);
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Accesso in scrittura: modifica di un singolo elemento.
     * La sintassi è identica alla lettura: si usa l'operatore di assegnazione. */
    printf("Prima della modifica: misure[1] = %d\n", misure[1]);
    misure[1] = 99;   /* sovrascrive il secondo elemento */
    printf("Dopo la modifica:     misure[1] = %d\n", misure[1]);
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Accesso con espressione come indice.
     * L'indice può essere il risultato di una qualsiasi espressione intera. */
    i = 2;
    printf("Accesso con espressione (i = %d):\n", i);
    printf("  misure[i - 1] = misure[%d] = %d\n", i - 1, misure[i - 1]);
    printf("  misure[i + 1] = misure[%d] = %d\n", i + 1, misure[i + 1]);
    printf("  misure[i * 2] = misure[%d] = %d\n", i * 2, misure[i * 2]);
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* Stampa di tutti gli elementi con ciclo for.
     * Forma standard: i parte da 0 e va fino a DIMENSIONE - 1 (incluso). */
    printf("Tutti gli elementi con ciclo for:\n");
    for (i = 0; i < DIMENSIONE; i++) {
        printf("  misure[%d] = %d\n", i, misure[i]);
    }
    printf("\n");

    /* ------------------------------------------------------------------ */
    /* ATTENZIONE: accesso fuori dai limiti (out of bounds).
     * In C il compilatore NON controlla i limiti dell'array a runtime.
     * Accedere a indici non validi produce comportamento indefinito:
     * si legge o si scrive memoria che appartiene ad altre variabili
     * o al sistema operativo, con risultati imprevedibili o crash.
     *
     * Esempio di codice ERRATO (commentato per sicurezza):
     *
     *   indice = 10;
     *   printf("%d\n", misure[indice]);   <- legge memoria fuori dall'array
     *   misure[-1] = 0;                   <- scrive prima dell'array
     *
     * La difesa corretta è sempre verificare che l'indice sia
     * compreso tra 0 e DIMENSIONE - 1 prima di usarlo. */
    indice = 4;
    if (indice >= 0 && indice < DIMENSIONE) {
        printf("Accesso sicuro: misure[%d] = %d\n", indice, misure[indice]);
    } else {
        printf("Indice %d fuori dai limiti [0, %d]\n", indice, DIMENSIONE - 1);
    }

    return 0;
}
