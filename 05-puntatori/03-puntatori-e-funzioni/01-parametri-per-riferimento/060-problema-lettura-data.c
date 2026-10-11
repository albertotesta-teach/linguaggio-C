/*
 * 060-problema-lettura-data.c
 *
 * Prenotazione della palestra: lettura e controllo di una data
 *
 * Per prenotare la palestra comunale si inserisce la data nel formato
 * gg/mm/aaaa. Il programma controlla che la data esista (mesi da 30 e 31
 * giorni, febbraio negli anni bisestili) e, se è valida, indica anche il
 * giorno successivo, quando scade la prenotazione.
 *
 * leggi_data(&g, &m, &a) legge una riga e scrive giorno, mese e anno nelle
 * variabili del chiamante; con return comunica l'esito:
 *     1  data valida
 *     0  data non valida (formato o giorno inesistente)
 *    -1  riga vuota o fine dell'input: non ci sono altre date
 * giorno_dopo(&g, &m, &a) modifica la data sul posto (parametri in-out).
 */

#include <stdio.h>

#define LUNG 40

int leggi_data(int *g, int *m, int *a);
int giorni_del_mese(int m, int a);
void giorno_dopo(int *g, int *m, int *a);

int main(void)
{
    int giorno;
    int mese;
    int anno;
    int esito = 0;

    printf("=== PRENOTAZIONE PALESTRA ===\n");
    while (esito != -1) {
        printf("Data (gg/mm/aaaa, riga vuota per finire): ");
        esito = leggi_data(&giorno, &mese, &anno);
        if (esito == 0) {
            printf("  Data non valida.\n");
        } else if (esito == 1) {
            printf("  Prenotazione per il %02d/%02d/%04d", giorno, mese, anno);
            giorno_dopo(&giorno, &mese, &anno);
            printf(", scade il %02d/%02d/%04d\n", giorno, mese, anno);
        }
    }

    return 0;
}

/* Legge una data; restituisce 1 se valida, 0 se non valida, -1 se la riga
 * è vuota o l'input è finito. Le variabili puntate si scrivono solo se la
 * data è valida. */
int leggi_data(int *g, int *m, int *a)
{
    char riga[LUNG];
    int gg;
    int mm;
    int aa;
    int esito = -1;

    if (fgets(riga, LUNG, stdin) != NULL && riga[0] != '\n') {
        esito = 0;
        if (sscanf(riga, "%d/%d/%d", &gg, &mm, &aa) == 3 &&
            aa >= 1900 && mm >= 1 && mm <= 12 &&
            gg >= 1 && gg <= giorni_del_mese(mm, aa)) {
            *g = gg;
            *m = mm;
            *a = aa;
            esito = 1;
        }
    }
    return esito;
}

/* Giorni del mese m nell'anno a. */
int giorni_del_mese(int m, int a)
{
    int giorni = 31;

    if (m == 4 || m == 6 || m == 9 || m == 11) {
        giorni = 30;
    } else if (m == 2) {
        if ((a % 4 == 0 && a % 100 != 0) || a % 400 == 0) {
            giorni = 29;
        } else {
            giorni = 28;
        }
    }
    return giorni;
}

/* Porta la data al giorno successivo, con i cambi di mese e di anno. */
void giorno_dopo(int *g, int *m, int *a)
{
    *g = *g + 1;
    if (*g > giorni_del_mese(*m, *a)) {
        *g = 1;
        *m = *m + 1;
        if (*m > 12) {
            *m = 1;
            *a = *a + 1;
        }
    }
}
