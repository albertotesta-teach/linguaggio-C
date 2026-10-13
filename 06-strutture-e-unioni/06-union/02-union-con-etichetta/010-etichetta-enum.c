/*
 * 010-etichetta-enum.c
 *
 * Union con etichetta: un enum dice quale campo è valido
 *
 * Una union da sola non ricorda quale campo è stato scritto. Si mette
 * quindi in una struct, accanto a un campo enum (l'etichetta, in inglese
 * tag) che lo dice:
 *
 *     typedef enum { INTERO, REALE, TESTO } TipoDato;
 *
 *     typedef struct {
 *         TipoDato tipo;
 *         union {
 *             int intero;
 *             double reale;
 *             char testo[16];
 *         } v;
 *     } Dato;
 *
 * Regola: ogni volta che si scrive un campo della union si aggiorna
 * l'etichetta, e prima di leggere un campo si controlla l'etichetta.
 *
 *     d.tipo = REALE;
 *     d.v.reale = 21.5;
 *     if (d.tipo == REALE) ... d.v.reale ...
 *
 * È la struttura dei valori di un foglio di calcolo, dei campi di un
 * modulo, dei messaggi di un protocollo: un valore che può essere di
 * tipi diversi.
 *
 * Esempio: tre risposte a un modulo online (età, media, classe).
 */

#include <stdio.h>
#include <string.h>

typedef enum {
    INTERO, REALE, TESTO
} TipoDato;

typedef struct {
    TipoDato tipo;
    union {
        int intero;
        double reale;
        char testo[16];
    } v;
} Dato;

int main(void)
{
    Dato risposte[3];
    int i;

    risposte[0].tipo = INTERO;
    risposte[0].v.intero = 16;

    risposte[1].tipo = REALE;
    risposte[1].v.reale = 7.45;

    risposte[2].tipo = TESTO;
    strcpy(risposte[2].v.testo, "3B");

    for (i = 0; i < 3; i++) {
        printf("risposta %d: ", i + 1);
        if (risposte[i].tipo == INTERO) {
            printf("intero %d\n", risposte[i].v.intero);
        } else if (risposte[i].tipo == REALE) {
            printf("reale %.2f\n", risposte[i].v.reale);
        } else {
            printf("testo \"%s\"\n", risposte[i].v.testo);
        }
    }

    printf("\nsizeof(Dato) = %zu byte: l'etichetta (%zu) e la union (%zu), con padding\n",
           sizeof(Dato), sizeof(TipoDato), sizeof(risposte[0].v));

    return 0;
}
