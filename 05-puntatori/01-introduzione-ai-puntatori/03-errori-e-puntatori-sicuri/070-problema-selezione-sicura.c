/*
 * 070-problema-selezione-sicura.c
 *
 * Modificare un'impostazione scelta da un elenco, in modo sicuro
 *
 * Il pannello di una lavatrice permette di cambiare tre impostazioni:
 * temperatura (gradi), centrifuga (giri al minuto) e durata (minuti).
 * L'utente scrive il codice dell'impostazione e il nuovo valore, per
 * esempio "T 40" o "C 1200".
 *
 * Per ogni richiesta il programma prepara due puntatori:
 *   - valore   (int *)        l'impostazione da modificare
 *   - minimo, massimo (const int *)  i limiti ammessi, di sola lettura
 * Se il codice non esiste i puntatori restano NULL e la richiesta viene
 * scartata. Il nuovo valore viene accettato solo se è entro i limiti.
 *
 * La funzione imposta() riceve i tre puntatori e restituisce un codice di
 * esito; controlla essa stessa che non siano NULL (programmazione difensiva).
 */

#include <stdio.h>

#define DIM 40
#define ACCETTATO 0
#define NON_VALIDO 1
#define FUORI_LIMITI 2

int imposta(int *valore, const int *minimo, const int *massimo, int nuovo);

int main(void)
{
    int temperatura = 30;
    int centrifuga = 800;
    int durata = 60;
    const int limiti_temp[2] = {20, 90};
    const int limiti_centr[2] = {400, 1400};
    const int limiti_durata[2] = {15, 180};
    char riga[DIM];
    char codice;
    int nuovo;
    int *valore;
    const int *minimo;
    const int *massimo;
    int esito;

    printf("=== LAVATRICE ===\n");
    printf("Impostazione (T gradi | C giri | D minuti), riga vuota per avviare: ");
    while (fgets(riga, DIM, stdin) != NULL && riga[0] != '\n') {
        valore = NULL;
        minimo = NULL;
        massimo = NULL;
        nuovo = 0;
        if (sscanf(riga, " %c %d", &codice, &nuovo) == 2) {
            if (codice == 'T') {
                valore = &temperatura;
                minimo = &limiti_temp[0];
                massimo = &limiti_temp[1];
            } else if (codice == 'C') {
                valore = &centrifuga;
                minimo = &limiti_centr[0];
                massimo = &limiti_centr[1];
            } else if (codice == 'D') {
                valore = &durata;
                minimo = &limiti_durata[0];
                massimo = &limiti_durata[1];
            }
        }

        esito = imposta(valore, minimo, massimo, nuovo);
        if (esito == ACCETTATO) {
            printf("  impostato %d\n", *valore);
        } else if (esito == FUORI_LIMITI) {
            printf("  valore fuori dai limiti %d-%d\n", *minimo, *massimo);
        } else {
            printf("  richiesta non valida\n");
        }
        printf("Impostazione: ");
    }

    printf("\nAvvio: %d gradi, %d giri, %d minuti\n", temperatura, centrifuga, durata);

    return 0;
}

/* Scrive nuovo in *valore se i puntatori sono validi e il valore è tra
 * *minimo e *massimo. Restituisce ACCETTATO, FUORI_LIMITI o NON_VALIDO. */
int imposta(int *valore, const int *minimo, const int *massimo, int nuovo)
{
    int esito = NON_VALIDO;

    if (valore != NULL && minimo != NULL && massimo != NULL) {
        if (nuovo < *minimo || nuovo > *massimo) {
            esito = FUORI_LIMITI;
        } else {
            *valore = nuovo;
            esito = ACCETTATO;
        }
    }
    return esito;
}
