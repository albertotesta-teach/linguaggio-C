/*
 * 010-array-di-stringhe-costanti.c
 *
 * Un elenco di stringhe come array di puntatori
 *
 * Finora un elenco di parole era una matrice di caratteri:
 *
 *     char giorni[7][10] = {"lunedi", ...};
 *
 * Ogni riga ha la stessa lunghezza (10 char), anche se "sab" ne usa 4.
 * In alternativa si può usare un ARRAY DI PUNTATORI, in cui ogni elemento
 * punta a un letterale:
 *
 *     const char *giorni[7] = {"lunedi", ...};
 *
 *   - ogni elemento è un const char * (8 byte): l'array occupa 7 * 8 byte,
 *     più i testi, ciascuno lungo quanto serve;
 *   - giorni[i] si usa come una stringa: printf("%s", giorni[i]);
 *   - giorni[i][0] è il primo carattere della i-esima stringa;
 *   - i testi sono letterali: si possono leggere ma non modificare, mentre
 *     si può far puntare giorni[i] a un altro testo.
 *
 * Esempio: i giorni di apertura della biblioteca, in forma lunga e breve.
 */

#include <stdio.h>
#include <string.h>

#define GIORNI 7

int main(void)
{
    char matrice[GIORNI][10] = {"lunedi", "martedi", "mercoledi", "giovedi",
                                "venerdi", "sabato", "domenica"};
    const char *giorni[GIORNI] = {"lunedi", "martedi", "mercoledi", "giovedi",
                                  "venerdi", "sabato", "domenica"};
    const char *brevi[GIORNI] = {"lun", "mar", "mer", "gio", "ven", "sab", "dom"};
    int i;
    int caratteri = 0;

    printf("=== MEMORIA ===\n");
    printf("  char matrice[7][10]:     %zu byte (7 righe da 10)\n", sizeof(matrice));
    printf("  const char *giorni[7]:   %zu byte di puntatori", sizeof(giorni));
    for (i = 0; i < GIORNI; i++) {
        caratteri = caratteri + (int) strlen(giorni[i]) + 1;
    }
    printf(" + %d byte di testo\n", caratteri);

    printf("\n=== OGNI ELEMENTO E' UNA STRINGA ===\n");
    for (i = 0; i < GIORNI; i++) {
        printf("  giorni[%d] = %-10s brevi[%d] = %s   iniziale giorni[%d][0] = %c   (%zu lettere)\n",
               i, giorni[i], i, brevi[i], i, giorni[i][0], strlen(giorni[i]));
    }

    /* la domenica la biblioteca è chiusa: si cambia il puntatore, non il testo */
    brevi[6] = "---";
    printf("\nOrario: ");
    for (i = 0; i < GIORNI; i++) {
        printf("%s ", brevi[i]);
    }
    printf("\n");
    /* brevi[0][0] = 'L';   errore: il letterale non si modifica */

    return 0;
}
