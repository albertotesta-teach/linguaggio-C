/*
 * 030-strcmp-e-strncmp.c
 *
 * Confronto con <string.h>
 *
 *   strcmp(a, b)      < 0 se a viene prima di b, 0 se uguali, > 0 se dopo
 *   strncmp(a, b, n)  come strcmp, ma confronta solo i primi n caratteri
 *
 * Lo standard garantisce solo il SEGNO del risultato, non il valore: il
 * risultato va confrontato con 0, mai con -1 o 1.
 *
 *     if (strcmp(a, b) == 0)    uguali
 *     if (strcmp(a, b) < 0)     a viene prima
 *
 * strncmp(s, prefisso, strlen(prefisso)) == 0 verifica se s inizia con
 * prefisso. Il C standard non ha una funzione che ignori le maiuscole:
 * per farlo si converte prima il testo (sezione 04) oppure si usa una
 * funzione scritta a mano (sezione 01).
 *
 * Esempio: un'agenzia di viaggi confronta i codici delle prenotazioni.
 */

#include <stdio.h>
#include <string.h>

#define CODICI 6
#define LUNG   12

int main(void)
{
    char codici[CODICI][LUNG] = {
        "ROMA-0412", "MILA-0398", "ROMA-0177", "NAPO-0250", "roma-0412", "ROMA-0412"
    };
    char cercato[] = "ROMA-0412";
    char prefisso[] = "ROMA";
    int k;
    int esito;
    int primo;

    /* ── 1. strcmp: uguaglianza ───────────────────────────────────── */
    printf("=== strcmp(codice, \"%s\") ===\n", cercato);
    for (k = 0; k < CODICI; k++) {
        esito = strcmp(codici[k], cercato);
        printf("  %-10s -> %-6s", codici[k], esito == 0 ? "uguale" : "diverso");
        if (esito < 0) {
            printf(" (viene prima)\n");
        } else if (esito > 0) {
            printf(" (viene dopo)\n");
        } else {
            printf("\n");
        }
    }

    /* ── 2. strncmp: stesso inizio ────────────────────────────────── */
    printf("\n=== prenotazioni per %s (strncmp sui primi %d caratteri) ===\n",
           prefisso, (int) strlen(prefisso));
    for (k = 0; k < CODICI; k++) {
        if (strncmp(codici[k], prefisso, strlen(prefisso)) == 0) {
            printf("  %s\n", codici[k]);
        }
    }

    /* ── 3. Il primo in ordine alfabetico ─────────────────────────── */
    primo = 0;                          /* indice del primo trovato finora */
    for (k = 1; k < CODICI; k++) {
        if (strcmp(codici[k], codici[primo]) < 0) {
            primo = k;
        }
    }
    printf("\nPrimo codice in ordine alfabetico: %s\n", codici[primo]);
    printf("(le maiuscole vengono prima delle minuscole: \"roma-0412\" e' l'ultimo)\n");

    return 0;
}
