/*
 * 030-conversioni-testo-numero.c
 *
 * Da testo a numero e da numero a testo
 *
 * La stringa "42" non è il numero 42: sono due caratteri, '4' e '2'.
 * Per convertire:
 *
 *   atoi(s)    <stdlib.h>  stringa -> int     "42"     -> 42
 *   atof(s)    <stdlib.h>  stringa -> double  "3.75"   -> 3.75
 *   sscanf(s, formato, ...)  come scanf, ma legge da una stringa e
 *              restituisce quanti valori ha convertito
 *   snprintf(dest, dim, formato, ...)  come printf, ma scrive in una
 *              stringa di dim celle senza mai superarla; restituisce la
 *              lunghezza che il testo AVREBBE avuto: se è >= dim il testo
 *              è stato troncato
 *
 * atoi e atof non segnalano gli errori: "12abc" diventa 12 e "abc" diventa
 * 0, come se l'utente avesse scritto "0". Per controllare l'input è
 * meglio sscanf, che dice quanti valori è riuscito a leggere; aggiungendo
 * %c in fondo al formato si scopre se dopo il numero c'è altro testo.
 *
 * Nell'output le stringhe sono stampate tra parentesi quadre per rendere
 * visibili gli spazi iniziali, che atoi e sscanf saltano.
 *
 * (Esiste anche sprintf, che non conosce la dimensione di dest: come strcpy
 * può scrivere oltre la fine dell'array. Si preferisce snprintf.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROVE 5
#define LUNG  12
#define DIM_ETICHETTA 20

int main(void)
{
    char testi[PROVE][LUNG] = {"42", "3.75", "12abc", "abc", "  7"};
    char etichetta[DIM_ETICHETTA];
    int k;
    int n;
    int letti;
    char resto;
    char locali[2][16] = {"Aula", "Laboratorio"};
    int numeri[2] = {12, 3};
    int piani[2] = {2, 1};
    int lunghezza;

    /* ── 1. atoi e atof ───────────────────────────────────────────── */
    printf("=== atoi e atof ===\n");
    for (k = 0; k < PROVE; k++) {
        printf("  [%s]%*s atoi = %3d   atof = %5.2f\n", testi[k],
               6 - (int) strlen(testi[k]), "", atoi(testi[k]), atof(testi[k]));
    }

    /* ── 2. sscanf per controllare la conversione ─────────────────── */
    printf("\n=== sscanf(s, \"%%d%%c\") ===\n");
    for (k = 0; k < PROVE; k++) {
        letti = sscanf(testi[k], "%d%c", &n, &resto);
        printf("  [%s]: ", testi[k]);
        if (letti == 1) {
            printf("numero intero valido: %d\n", n);
        } else if (letti == 2) {
            printf("dopo il numero %d c'e' altro testo\n", n);
        } else {
            printf("non e' un numero\n");
        }
    }

    /* ── 3. snprintf per comporre una stringa ─────────────────────── */
    printf("\n=== snprintf ===\n");
    for (k = 0; k < 2; k++) {
        lunghezza = snprintf(etichetta, sizeof(etichetta), "%s %d - piano %d",
                             locali[k], numeri[k], piani[k]);
        printf("  etichetta = \"%s\"", etichetta);
        if (lunghezza >= (int) sizeof(etichetta)) {
            printf(" (troncata: servivano %d caratteri)", lunghezza);
        }
        printf("\n");
    }

    return 0;
}
