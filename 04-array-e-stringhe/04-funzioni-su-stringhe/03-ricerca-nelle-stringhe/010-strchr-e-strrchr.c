/*
 * 010-strchr-e-strrchr.c
 *
 * Cercare un carattere in una stringa
 *
 *   strchr(s, c)    cerca la PRIMA occorrenza del carattere c in s
 *   strrchr(s, c)   cerca l'ULTIMA occorrenza
 *
 * Entrambe restituiscono un puntatore al carattere trovato, oppure NULL se
 * il carattere non c'è. I puntatori saranno trattati nel capitolo 05: per
 * ora il risultato si usa solo per sapere SE il carattere è presente.
 *
 *     if (strchr(s, '@') != NULL)     s contiene almeno una '@'
 *
 * Quando serve la POSIZIONE si usano due funzioni scritte a mano che
 * restituiscono l'indice (oppure -1):
 *
 *     prima_posizione(s, c)     indice della prima occorrenza
 *     ultima_posizione(s, c)    indice dell'ultima occorrenza
 *
 * e una terza funzione, copia_parte(dest, s, inizio, n), copia in dest gli
 * n caratteri di s che partono dall'indice inizio: con le posizioni trovate
 * si estraggono così i pezzi del codice.
 *
 * Esempio: controlli su codici di magazzino nel formato CAT-NUMERO-LOTTO.
 */

#include <stdio.h>
#include <string.h>

#define CODICI 5
#define LUNG   20

int prima_posizione(const char s[], char c);
int ultima_posizione(const char s[], char c);
void copia_parte(char dest[], const char s[], int inizio, int n);

int main(void)
{
    char codici[CODICI][LUNG] = {
        "ELE-0042-A7", "ALI-118", "ABB0091B2", "ELE-0077-B1-R", "ALI-0003-C4"
    };
    int k;
    int primo;
    int ultimo;
    char categoria[LUNG];
    char lotto[LUNG];

    /* ── 1. strchr: il carattere è presente? ──────────────────────── */
    printf("=== PRESENZA DEL TRATTINO (strchr) ===\n");
    for (k = 0; k < CODICI; k++) {
        printf("  %-14s %s\n", codici[k],
               strchr(codici[k], '-') != NULL ? "contiene '-'" : "senza '-'");
    }

    /* ── 2. Posizioni della prima e dell'ultima occorrenza ────────── */
    printf("\n=== POSIZIONI DEL TRATTINO ===\n");
    printf("  %-14s %6s %6s  %s\n", "Codice", "primo", "ultimo", "Categoria / lotto");
    for (k = 0; k < CODICI; k++) {
        primo = prima_posizione(codici[k], '-');
        ultimo = ultima_posizione(codici[k], '-');
        printf("  %-14s %6d %6d  ", codici[k], primo, ultimo);
        if (primo == -1) {
            printf("formato non riconosciuto\n");
        } else if (primo == ultimo) {
            printf("manca il lotto\n");
        } else {
            /* la categoria va da 0 a primo - 1, il lotto da ultimo + 1 */
            copia_parte(categoria, codici[k], 0, primo);
            copia_parte(lotto, codici[k], ultimo + 1,
                        (int) strlen(codici[k]) - ultimo - 1);
            printf("%s / %s\n", categoria, lotto);
        }
    }

    /* ── 3. strrchr restituisce NULL come strchr ─────────────────── */
    printf("\nstrrchr(\"%s\", 'Z') %s NULL\n", codici[0],
           strrchr(codici[0], 'Z') == NULL ? "==" : "!=");

    return 0;
}

/* Indice della prima occorrenza di c in s, oppure -1. */
int prima_posizione(const char s[], char c)
{
    int i = 0;
    int posizione = -1;

    while (s[i] != '\0' && posizione == -1) {
        if (s[i] == c) {
            posizione = i;
        }
        i++;
    }
    return posizione;
}

/* Indice dell'ultima occorrenza di c in s, oppure -1: si scorre tutta la
 * stringa aggiornando la posizione a ogni occorrenza. */
int ultima_posizione(const char s[], char c)
{
    int i = 0;
    int posizione = -1;

    while (s[i] != '\0') {
        if (s[i] == c) {
            posizione = i;
        }
        i++;
    }
    return posizione;
}

/* Copia in dest gli n caratteri di s a partire dall'indice inizio. */
void copia_parte(char dest[], const char s[], int inizio, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        dest[i] = s[inizio + i];
    }
    dest[n] = '\0';
}
