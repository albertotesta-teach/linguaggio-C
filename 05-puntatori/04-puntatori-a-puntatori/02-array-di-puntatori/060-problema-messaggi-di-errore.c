/*
 * 060-problema-messaggi-di-errore.c
 *
 * Stampante 3D del laboratorio: decodifica del registro errori
 *
 * La stampante 3D del laboratorio registra gli errori come codici
 * numerici. Il tecnico vuole il registro della settimana con la
 * descrizione di ogni codice e il conteggio per tipo di errore.
 *
 * Le descrizioni sono in un array di puntatori a stringhe costanti, in cui
 * il codice dell'errore è l'indice:
 *
 *     const char *descrizioni[ERRORI] = {"nessun errore", "filamento esaurito", ...};
 *
 * descrizione(codice, descrizioni) restituisce il puntatore alla stringa
 * giusta, oppure al testo "codice sconosciuto" se il codice è fuori
 * dall'array: il chiamante riceve sempre una stringa valida da stampare.
 */

#include <stdio.h>

#define ERRORI  6
#define EVENTI 10

const char *descrizione(int codice, const char *descrizioni[]);

int main(void)
{
    const char *descrizioni[ERRORI] = {
        "nessun errore",
        "filamento esaurito",
        "temperatura ugello fuori range",
        "piatto non livellato",
        "porta aperta durante la stampa",
        "file di stampa danneggiato"
    };
    int registro[EVENTI] = {1, 3, 1, 0, 5, 9, 1, 3, 4, 1};
    int conteggi[ERRORI] = {0};
    int sconosciuti = 0;
    int i;

    printf("=== REGISTRO DELLA SETTIMANA ===\n");
    for (i = 0; i < EVENTI; i++) {
        printf("  evento %2d  codice %d  %s\n", i + 1, registro[i],
               descrizione(registro[i], descrizioni));
        if (registro[i] >= 0 && registro[i] < ERRORI) {
            conteggi[registro[i]]++;
        } else {
            sconosciuti++;
        }
    }

    printf("\n=== RIEPILOGO ===\n");
    for (i = 1; i < ERRORI; i++) {
        if (conteggi[i] > 0) {
            printf("  %dx %s\n", conteggi[i], descrizioni[i]);
        }
    }
    printf("  %dx codice sconosciuto\n", sconosciuti);

    return 0;
}

/* Restituisce la descrizione del codice, o un testo di riserva se il codice
 * non ha una descrizione. */
const char *descrizione(int codice, const char *descrizioni[])
{
    const char *testo = "codice sconosciuto";

    if (codice >= 0 && codice < ERRORI) {
        testo = descrizioni[codice];
    }
    return testo;
}
