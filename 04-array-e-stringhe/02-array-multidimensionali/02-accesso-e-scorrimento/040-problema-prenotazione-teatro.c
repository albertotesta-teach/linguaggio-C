/*
 * 040-problema-prenotazione-teatro.c
 *
 * Prenotazione dei posti in un piccolo teatro
 *
 * Il teatro ha 5 file (A-E) da 8 posti. Alcuni posti sono già venduti.
 * L'operatore della biglietteria inserisce una richiesta alla volta,
 * indicando la fila con una lettera e il numero del posto (es. C 4).
 * Per ogni richiesta il programma:
 *   - controlla che fila e posto esistano;
 *   - se il posto è libero lo prenota;
 *   - se è occupato lo segnala e propone il primo posto libero della
 *     stessa fila, se esiste.
 * L'inserimento termina con la fila 'Z'. Alla fine viene stampata la
 * mappa aggiornata e il numero di posti prenotati nella sessione.
 *
 * Conversione fila -> indice di riga:  riga = lettera - 'A'
 * Conversione posto -> indice di colonna: colonna = posto - 1
 */

#include <stdio.h>

#define FILE_TEATRO 5
#define POSTI       8
#define LIBERO      0
#define OCCUPATO    1
#define FINE        'Z'

int main(void)
{
    int sala[FILE_TEATRO][POSTI] = {
        {1, 1, 0, 0, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    char lettera;
    int numero_posto;
    int riga;
    int colonna;
    int c;
    int alternativo;
    int prenotati = 0;
    int esito;          /* valore restituito da scanf */
    int scarta;         /* carattere scartato da una riga non valida */

    printf("=== TEATRO COMUNALE - BIGLIETTERIA ===\n");
    printf("File A-%c, posti 1-%d. Fila %c per terminare.\n\n",
           'A' + FILE_TEATRO - 1, POSTI, FINE);

    printf("Fila e posto (es. C 4): ");
    if (scanf(" %c", &lettera) != 1) {
        lettera = FINE;         /* input terminato: come la fila di fine */
    }

    while (lettera != FINE) {
        esito = scanf("%d", &numero_posto);
        if (esito != 1) {
            if (esito == 0) {
                /* non è un numero: si scarta il resto della riga */
                scarta = getchar();
                while (scarta != '\n' && scarta != EOF) {
                    scarta = getchar();
                }
            }
            numero_posto = 0;   /* posto non valido: risulterà inesistente */
        }
        riga = lettera - 'A';
        colonna = numero_posto - 1;

        if (riga < 0 || riga >= FILE_TEATRO || colonna < 0 || colonna >= POSTI) {
            printf("  Posto inesistente.\n");
        } else if (sala[riga][colonna] == LIBERO) {
            sala[riga][colonna] = OCCUPATO;
            prenotati++;
            printf("  Prenotato: fila %c, posto %d.\n", lettera, numero_posto);
        } else {
            /* Posto occupato: cerca il primo libero nella stessa fila.
             * La ricerca si ferma al primo trovato (flag nella condizione). */
            alternativo = -1;
            for (c = 0; c < POSTI && alternativo == -1; c++) {
                if (sala[riga][c] == LIBERO) {
                    alternativo = c;
                }
            }

            if (alternativo != -1) {
                printf("  Occupato. Primo posto libero nella fila %c: %d\n",
                       lettera, alternativo + 1);
            } else {
                printf("  Occupato. La fila %c e' completa.\n", lettera);
            }
        }

        printf("Fila e posto (es. C 4): ");
        if (scanf(" %c", &lettera) != 1) {
            lettera = FINE;     /* input terminato: come la fila di fine */
        }
    }

    /* ── Mappa finale ─────────────────────────────────────────────── */
    printf("\n=== MAPPA AGGIORNATA ===\n");
    printf("        PALCO\n     ");
    for (colonna = 0; colonna < POSTI; colonna++) {
        printf("%2d", colonna + 1);
    }
    printf("\n");
    for (riga = 0; riga < FILE_TEATRO; riga++) {
        printf("  %c  ", 'A' + riga);
        for (colonna = 0; colonna < POSTI; colonna++) {
            if (sala[riga][colonna] == LIBERO) {
                printf(" .");
            } else {
                printf(" X");
            }
        }
        printf("\n");
    }
    printf("\nPosti prenotati in questa sessione: %d\n", prenotati);

    /*
     * NOTA: le file vanno inserite in maiuscolo. Con 'c' si otterrebbe
     * riga = 'c' - 'A' = 34, fuori dai limiti: il programma lo segnala
     * come posto inesistente. Un esercizio propone di accettare anche
     * le minuscole.
     */

    return 0;
}
