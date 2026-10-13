/*
 * 020-un-campo-alla-volta.c
 *
 * Scrivere un campo di una union cancella gli altri
 *
 * I campi di una union condividono gli stessi byte: scrivendo un campo si
 * sovrascrivono i byte degli altri. Ha senso leggere SOLO il campo
 * scritto per ultimo.
 *
 *     v.intero = 65;           ora v contiene un int
 *     v.reale = 3.5;           ora v contiene un double: v.intero è perso
 *
 * Leggere un altro campo non è un errore di compilazione: il programma
 * reinterpreta i byte presenti come se fossero del tipo del campo letto,
 * e il risultato non ha alcun legame con il valore scritto. Chi usa una
 * union deve sapere in ogni momento quale campo è valido (la sezione
 * 02-union-con-etichetta mostra come tenerne traccia).
 *
 * Esempio: tre scritture successive nella stessa union. Dopo ognuna si
 * leggono tutti i campi: solo uno ha un valore sensato. I valori senza
 * senso dipendono dalla macchina (questi sono di un PC little-endian).
 */

#include <stdio.h>
#include <string.h>

typedef union {
    int intero;
    double reale;
    char testo[8];
} Valore;

void mostra(const char *operazione, const Valore *v);

int main(void)
{
    Valore v;

    memset(&v, 0, sizeof(v));

    v.intero = 65;
    mostra("v.intero = 65", &v);

    v.reale = 3.5;
    mostra("v.reale = 3.5", &v);

    strcpy(v.testo, "ciao");
    mostra("strcpy(v.testo, \"ciao\")", &v);

    return 0;
}

/* Stampa tutti i campi; il testo solo se è una stringa stampabile. */
void mostra(const char *operazione, const Valore *v)
{
    int stampabile = 1;
    int i = 0;

    while (i < 8 && v->testo[i] != '\0') {
        if (v->testo[i] < ' ' || v->testo[i] > '~') {
            stampabile = 0;
        }
        i++;
    }
    printf("Dopo %s:\n", operazione);
    printf("  v.intero = %d\n", v->intero);
    printf("  v.reale  = %.10g\n", v->reale);
    printf("  v.testo  = \"%s\"\n\n", stampabile && i < 8 ? v->testo : "(byte non stampabili)");
}
