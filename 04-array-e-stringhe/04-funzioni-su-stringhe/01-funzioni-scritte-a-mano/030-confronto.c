/*
 * 030-confronto.c
 *
 * Confrontare due stringhe in ordine alfabetico
 *
 * Due stringhe NON si confrontano con ==: a == b confronta gli indirizzi
 * dei due array, non il loro contenuto. Serve una funzione che scorra le
 * stringhe in parallelo:
 *
 *   confronta(a, b)  restituisce
 *       un numero < 0  se a viene prima di b in ordine alfabetico
 *       0              se a e b sono uguali
 *       un numero > 0  se a viene dopo b
 *
 * Il ciclo avanza finché i caratteri sono uguali e la stringa non è finita;
 * il risultato è la differenza tra i primi due caratteri diversi.
 * L'ordine è quello dei codici ASCII, quindi:
 *   - le maiuscole vengono prima delle minuscole ('Z' = 90 < 'a' = 97);
 *   - una stringa che è l'inizio di un'altra viene prima ("Mar" < "Mario"),
 *     perché il suo '\0' (codice 0) è minore di qualsiasi carattere.
 *
 * confronta_ignorando_maiuscole(a, b) converte le lettere in minuscolo
 * prima di confrontarle, con la differenza 'a' - 'A' (32).
 */

#include <stdio.h>

#define COPPIE 6
#define LUNG   12

int confronta(const char a[], const char b[]);
int confronta_ignorando_maiuscole(const char a[], const char b[]);
char minuscola(char c);

int main(void)
{
    char prima[COPPIE][LUNG]   = {"Mario", "Anna", "Mar", "Zeta", "rossi", "Rossi"};
    char seconda[COPPIE][LUNG] = {"Mario", "Bruno", "Mario", "alfa", "Rossi", "Rosso"};
    int k;
    int esito;

    printf("=== CONFRONTO (maiuscole e minuscole distinte) ===\n");
    for (k = 0; k < COPPIE; k++) {
        esito = confronta(prima[k], seconda[k]);
        printf("  %-6s vs %-6s -> %4d  ", prima[k], seconda[k], esito);
        if (esito < 0) {
            printf("\"%s\" viene prima\n", prima[k]);
        } else if (esito > 0) {
            printf("\"%s\" viene dopo\n", prima[k]);
        } else {
            printf("uguali\n");
        }
    }

    printf("\n=== CONFRONTO IGNORANDO LE MAIUSCOLE ===\n");
    for (k = 3; k < COPPIE; k++) {
        esito = confronta_ignorando_maiuscole(prima[k], seconda[k]);
        printf("  %-6s vs %-6s -> %4d\n", prima[k], seconda[k], esito);
    }

    printf("\nAttenzione: prima[0] == seconda[0] vale %d, anche se il testo e'\n",
           prima[0] == seconda[0]);
    printf("lo stesso: == confronta gli indirizzi, non i caratteri.\n");

    return 0;
}

/* Restituisce <0, 0 o >0 come descritto in testa al file. */
int confronta(const char a[], const char b[])
{
    int i = 0;

    while (a[i] == b[i] && a[i] != '\0') {
        i++;
    }
    return a[i] - b[i];
}

/* Come confronta, ma 'A' e 'a' sono considerate uguali. */
int confronta_ignorando_maiuscole(const char a[], const char b[])
{
    int i = 0;

    while (minuscola(a[i]) == minuscola(b[i]) && a[i] != '\0') {
        i++;
    }
    return minuscola(a[i]) - minuscola(b[i]);
}

/* Restituisce la minuscola di c se c è una lettera maiuscola, altrimenti c. */
char minuscola(char c)
{
    char risultato = c;

    if (c >= 'A' && c <= 'Z') {
        risultato = c + ('a' - 'A');
    }
    return risultato;
}
