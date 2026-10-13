/*
 * 020-array-di-valori-misti.c
 *
 * Un array di valori di tipo diverso
 *
 * Un array contiene elementi tutti dello stesso tipo. Con una union
 * etichettata l'elemento è sempre un Dato, ma ogni Dato può contenere un
 * intero, un reale o un testo: l'array diventa un elenco di valori misti,
 * come una riga di un foglio di calcolo o una risposta a un modulo.
 *
 *     Dato riga[] = {
 *         {.tipo = TESTO, .testo = "Bassi"},
 *         {.tipo = INTERO, .intero = 17},
 *         {.tipo = REALE, .reale = 7.5},
 *         ...
 *     };
 *
 * Un ciclo sull'array guarda l'etichetta di ogni elemento:
 *   - conta gli elementi di ogni tipo (array indicizzato dall'enum);
 *   - somma i soli numeri, interi e reali, in un double;
 *   - concatena i testi separandoli con uno spazio.
 *
 * Esempio: una riga del file delle iscrizioni al torneo di scacchi.
 */

#include <stdio.h>
#include <string.h>

#define VALORI 7
#define LUNG_TESTO 12

typedef enum {
    INTERO, REALE, TESTO, NUM_TIPI
} TipoDato;

typedef struct {
    TipoDato tipo;
    union {
        int intero;
        double reale;
        char testo[LUNG_TESTO];
    };
} Dato;

int main(void)
{
    Dato riga[VALORI] = {
        {.tipo = TESTO, .testo = "Bassi"},
        {.tipo = TESTO, .testo = "Rita"},
        {.tipo = INTERO, .intero = 17},
        {.tipo = REALE, .reale = 7.5},
        {.tipo = TESTO, .testo = "4B"},
        {.tipo = INTERO, .intero = 1320},
        {.tipo = REALE, .reale = 0.5}
    };
    const char *nomi[NUM_TIPI] = {[INTERO] = "interi", [REALE] = "reali", [TESTO] = "testi"};
    int conteggi[NUM_TIPI] = {0};
    char testi[VALORI * LUNG_TESTO] = "";
    double somma = 0;
    TipoDato t;
    int i;

    for (i = 0; i < VALORI; i++) {
        conteggi[riga[i].tipo]++;
        switch (riga[i].tipo) {
        case INTERO:
            somma = somma + riga[i].intero;
            break;
        case REALE:
            somma = somma + riga[i].reale;
            break;
        case TESTO:
            if (testi[0] != '\0') {
                strcat(testi, " ");
            }
            strcat(testi, riga[i].testo);
            break;
        case NUM_TIPI:
            break;
        }
    }

    for (t = INTERO; t < NUM_TIPI; t++) {
        printf("%-7s %d\n", nomi[t], conteggi[t]);
    }
    printf("Somma dei numeri: %.1f\n", somma);
    printf("Testi: %s\n", testi);

    return 0;
}
