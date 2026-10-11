/*
 * 010-lunghezza-e-copia.c
 *
 * Lunghezza e copia di una stringa con funzioni scritte a mano
 *
 * Una stringa si passa a una funzione come qualsiasi array di char: il
 * parametro si scrive  char s[]  (o  const char s[]  se la funzione non la
 * modifica). La funzione non riceve la dimensione dell'array: la fine
 * della stringa si riconosce dal terminatore '\0'.
 *
 *   lunghezza(s)                 conta i caratteri fino a '\0' (escluso)
 *   copia(dest, sorg)            copia sorg in dest, '\0' COMPRESO
 *   copia_limitata(dest, sorg, dim)
 *                                copia al massimo dim - 1 caratteri e
 *                                termina sempre dest con '\0'
 *
 * Due regole da ricordare:
 *   1. senza il '\0' finale dest non sarebbe una stringa: printf
 *      continuerebbe a leggere la memoria che segue;
 *   2. dest deve avere spazio per tutti i caratteri PIÙ il '\0'. La
 *      funzione copia() non lo può verificare: per questo esiste la
 *      versione limitata, che riceve la dimensione di dest.
 */

#include <stdio.h>

#define DIM_GRANDE  30
#define DIM_PICCOLA 8

int lunghezza(const char s[]);
void copia(char dest[], const char sorg[]);
void copia_limitata(char dest[], const char sorg[], int dim);

int main(void)
{
    char originale[DIM_GRANDE] = "Programmazione";
    char duplicato[DIM_GRANDE];
    char corta[DIM_PICCOLA];
    int i;

    /* ── 1. Lunghezza ─────────────────────────────────────────────── */
    printf("=== LUNGHEZZA ===\n");
    printf("\"%s\" ha %d caratteri\n", originale, lunghezza(originale));
    printf("\"\" (stringa vuota) ha %d caratteri\n", lunghezza(""));
    printf("Lo spazio occupato e' %d celle: i caratteri piu' il '\\0'\n\n",
           lunghezza(originale) + 1);

    /* ── 2. Copia completa ────────────────────────────────────────── */
    printf("=== COPIA ===\n");
    copia(duplicato, originale);
    printf("duplicato = \"%s\"\n", duplicato);
    printf("Celle di duplicato (codice ASCII):\n  ");
    for (i = 0; i <= lunghezza(duplicato); i++) {
        printf("%d ", duplicato[i]);
    }
    printf("\n  l'ultimo 0 e' il terminatore copiato da copia()\n");

    /* la copia e' indipendente: modificarla non cambia l'originale */
    duplicato[0] = 'p';
    printf("Dopo duplicato[0] = 'p':\n");
    printf("  originale = \"%s\"\n  duplicato = \"%s\"\n\n", originale, duplicato);

    /* ── 3. Copia in un array troppo piccolo ──────────────────────── */
    printf("=== COPIA LIMITATA (dest di %d celle) ===\n", DIM_PICCOLA);
    copia_limitata(corta, originale, DIM_PICCOLA);
    printf("corta = \"%s\" (%d caratteri + '\\0')\n", corta, lunghezza(corta));
    printf("La stringa e' stata troncata ma resta una stringa valida.\n");
    printf("Con copia(corta, originale) si sarebbe scritto oltre la fine\n");
    printf("dell'array, sovrascrivendo altre variabili.\n");

    return 0;
}

/* Restituisce il numero di caratteri di s, escluso il terminatore. */
int lunghezza(const char s[])
{
    int n = 0;

    while (s[n] != '\0') {
        n++;
    }
    return n;
}

/* Copia sorg in dest, terminatore compreso. dest deve essere abbastanza
 * grande: almeno lunghezza(sorg) + 1 celle. */
void copia(char dest[], const char sorg[])
{
    int i = 0;

    while (sorg[i] != '\0') {
        dest[i] = sorg[i];
        i++;
    }
    dest[i] = '\0';
}

/* Copia al massimo dim - 1 caratteri di sorg in dest (dim = dimensione
 * dell'array dest) e termina sempre dest con '\0'. */
void copia_limitata(char dest[], const char sorg[], int dim)
{
    int i = 0;

    while (sorg[i] != '\0' && i < dim - 1) {
        dest[i] = sorg[i];
        i++;
    }
    dest[i] = '\0';
}
