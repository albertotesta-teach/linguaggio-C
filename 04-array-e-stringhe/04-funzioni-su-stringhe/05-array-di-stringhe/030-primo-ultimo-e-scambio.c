/*
 * 030-primo-ultimo-e-scambio.c
 *
 * Primo e ultimo in ordine alfabetico; scambio di due righe
 *
 * Con strcmp si trova la parola che viene prima (o dopo) in ordine
 * alfabetico, con lo stesso schema della ricerca del minimo (o massimo):
 *
 *     primo = 0;
 *     for (k = 1; k < n; k++)
 *         if (strcmp(elenco[k], elenco[primo]) < 0)  primo = k;
 *
 * Le stringhe non si assegnano con =, quindi per SCAMBIARE due righe
 * servono tre strcpy e una stringa di appoggio, come per scambiare due
 * numeri con una variabile temporanea:
 *
 *     strcpy(appoggio, a);  strcpy(a, b);  strcpy(b, appoggio);
 *
 * Ripetendo "trova il primo e portalo in cima" su elenchi sempre più corti
 * si ottiene un elenco ordinato: è l'idea dell'ordinamento per selezione,
 * che verrà trattato nel capitolo 11. Qui ci si ferma al primo passo.
 *
 * Esempio: l'elenco dei libri prestati dalla biblioteca nella settimana.
 */

#include <stdio.h>
#include <string.h>

#define LIBRI 6
#define LUNG  32

int indice_primo(const char elenco[][LUNG], int n);
int indice_ultimo(const char elenco[][LUNG], int n);
void scambia(char a[], char b[]);
void stampa(const char elenco[][LUNG], int n);

int main(void)
{
    char libri[LIBRI][LUNG] = {
        "Il barone rampante", "Marcovaldo", "Il deserto dei Tartari",
        "Cuore", "La luna e i falo'", "Il nome della rosa"
    };
    int primo;
    int ultimo;

    printf("Elenco iniziale:\n");
    stampa(libri, LIBRI);

    primo = indice_primo(libri, LIBRI);
    ultimo = indice_ultimo(libri, LIBRI);
    printf("\nPrimo in ordine alfabetico : \"%s\" (riga %d)\n", libri[primo], primo);
    printf("Ultimo in ordine alfabetico: \"%s\" (riga %d)\n", libri[ultimo], ultimo);

    scambia(libri[0], libri[primo]);
    printf("\nDopo lo scambio della riga 0 con la riga %d:\n", primo);
    stampa(libri, LIBRI);

    return 0;
}

int indice_primo(const char elenco[][LUNG], int n)
{
    int k;
    int primo = 0;

    for (k = 1; k < n; k++) {
        if (strcmp(elenco[k], elenco[primo]) < 0) {
            primo = k;
        }
    }
    return primo;
}

int indice_ultimo(const char elenco[][LUNG], int n)
{
    int k;
    int ultimo = 0;

    for (k = 1; k < n; k++) {
        if (strcmp(elenco[k], elenco[ultimo]) > 0) {
            ultimo = k;
        }
    }
    return ultimo;
}

/* Scambia il contenuto di due stringhe di al massimo LUNG - 1 caratteri. */
void scambia(char a[], char b[])
{
    char appoggio[LUNG];

    strcpy(appoggio, a);
    strcpy(a, b);
    strcpy(b, appoggio);
}

void stampa(const char elenco[][LUNG], int n)
{
    int k;

    for (k = 0; k < n; k++) {
        printf("  %d. %s\n", k, elenco[k]);
    }
}
