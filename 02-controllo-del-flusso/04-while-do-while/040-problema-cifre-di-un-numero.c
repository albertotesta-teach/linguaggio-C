/*
 * 040-problema-cifre-di-un-numero.c
 *
 * Analisi delle cifre di un numero intero
 *
 * Dato un numero intero non negativo, il programma calcola:
 *   - quante cifre ha;
 *   - la somma delle sue cifre;
 *   - il numero letto al contrario (es. 1203 -> 3021);
 *   - se è palindromo, cioè uguale al suo inverso (es. 12321).
 *
 * Tecnica: con l'aritmetica intera
 *     n % 10   restituisce l'ultima cifra   (1203 % 10 = 3)
 *     n / 10   toglie l'ultima cifra        (1203 / 10 = 120)
 * Ripetendo queste due operazioni finché il numero non diventa 0 si
 * visitano tutte le cifre, da destra verso sinistra.
 *
 * Il ciclo che conta le cifre è un do-while: anche il numero 0 ha una
 * cifra, quindi il corpo va eseguito almeno una volta.
 */

#include <stdio.h>

int main(void)
{
    int numero;
    int resto;          /* copia di lavoro che viene "consumata" cifra per cifra */
    int cifra;
    int numero_cifre;
    int somma_cifre;
    int inverso;

    /* ── Lettura con validazione ──────────────────────────────────── */
    do {
        printf("Inserisci un numero intero non negativo: ");
        scanf("%d", &numero);
        if (numero < 0) {
            printf("  Il numero deve essere >= 0.\n");
        }
    } while (numero < 0);

    /* ── 1. Numero di cifre (do-while: lo 0 ha una cifra) ────────── */
    resto = numero;
    numero_cifre = 0;
    do {
        numero_cifre++;
        resto = resto / 10;
    } while (resto > 0);

    /* ── 2. Somma delle cifre e numero inverso ────────────────────────
     * Un solo while calcola entrambi. Per costruire l'inverso si
     * "sposta a sinistra" il risultato parziale (* 10) e si aggiunge
     * la cifra appena estratta.                                        */
    resto = numero;
    somma_cifre = 0;
    inverso = 0;

    printf("\nCifre da destra a sinistra: ");
    while (resto > 0) {
        cifra = resto % 10;
        printf("%d ", cifra);
        somma_cifre = somma_cifre + cifra;
        inverso = inverso * 10 + cifra;
        resto = resto / 10;
    }
    if (numero == 0) {
        printf("0");
    }
    printf("\n");

    /* ── Risultati ────────────────────────────────────────────────── */
    printf("Numero di cifre   : %d\n", numero_cifre);
    printf("Somma delle cifre : %d\n", somma_cifre);
    printf("Numero inverso    : %d\n", inverso);

    if (inverso == numero) {
        printf("%d e' palindromo.\n", numero);
    } else {
        printf("%d non e' palindromo.\n", numero);
    }

    /*
     * NOTE
     * - Il numero originale non viene modificato: i cicli lavorano sulla
     *   copia "resto". Servirà alla fine per il confronto con l'inverso.
     * - Gli zeri iniziali dell'inverso si perdono: l'inverso di 120 è 21
     *   (e infatti 120 non è palindromo).
     * - Un int può contenere numeri fino a circa 2 miliardi: l'inverso di
     *   un numero di 10 cifre potrebbe superare questo limite.
     */

    return 0;
}
