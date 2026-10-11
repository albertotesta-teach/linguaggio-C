/*
 * 050-problema-battaglia-navale.c
 *
 * Battaglia navale in solitario
 *
 * Il programma usa DUE griglie della stessa dimensione:
 *   flotta[][]   la posizione segreta delle navi ('N' = nave, '.' = mare)
 *   tiri[][]     ciò che vede il giocatore: '?' non colpita, 'O' acqua,
 *                'X' nave colpita
 *
 * Il giocatore indica la cella con una lettera per la riga (A-F) e un
 * numero per la colonna (1-8), per esempio C 4. Ha a disposizione 20
 * colpi. La partita termina quando tutte le parti di nave sono state
 * colpite oppure quando i colpi sono finiti; alla fine viene mostrata la
 * flotta.
 *
 * Una cella già colpita non consuma un colpo.
 */

#include <stdio.h>

#define RIGHE   6
#define COLONNE 8
#define COLPI   20

#define NAVE     'N'
#define MARE     '.'
#define IGNOTA   '?'
#define ACQUA    'O'
#define COLPITA  'X'

void inizializza_tiri(char t[][COLONNE + 1]);
void stampa_griglia(const char g[][COLONNE + 1]);
int conta_celle(const char g[][COLONNE + 1], char simbolo);

int main(void)
{
    char flotta[RIGHE][COLONNE + 1] = {
        "NNNN....",
        "........",
        "..N...N.",
        "..N...N.",
        "..N.....",
        "....NN.."
    };
    char tiri[RIGHE][COLONNE + 1];
    char lettera;
    int colonna_utente;
    int r;
    int c;
    int colpi_rimasti = COLPI;
    int da_affondare;

    inizializza_tiri(tiri);
    da_affondare = conta_celle(flotta, NAVE);

    printf("=== BATTAGLIA NAVALE ===\n");
    printf("Parti di nave da colpire: %d, colpi disponibili: %d\n", da_affondare, COLPI);
    stampa_griglia(tiri);

    while (da_affondare > 0 && colpi_rimasti > 0) {
        printf("Colpo (es. C 4), rimasti %d: ", colpi_rimasti);
        scanf(" %c %d", &lettera, &colonna_utente);
        r = lettera - 'A';
        c = colonna_utente - 1;

        if (r < 0 || r >= RIGHE || c < 0 || c >= COLONNE) {
            printf("  Cella inesistente.\n");
        } else if (tiri[r][c] != IGNOTA) {
            printf("  Cella gia' colpita.\n");
        } else {
            colpi_rimasti--;
            if (flotta[r][c] == NAVE) {
                tiri[r][c] = COLPITA;
                da_affondare--;
                printf("  COLPITO!\n");
            } else {
                tiri[r][c] = ACQUA;
                printf("  Acqua.\n");
            }
            stampa_griglia(tiri);
        }
    }

    if (da_affondare == 0) {
        printf("Flotta affondata con %d colpi!\n", COLPI - colpi_rimasti);
    } else {
        printf("Colpi esauriti: restano %d parti di nave.\n", da_affondare);
        printf("La flotta era:\n");
        stampa_griglia(flotta);
    }

    return 0;
}

void inizializza_tiri(char t[][COLONNE + 1])
{
    int r;
    int c;

    for (r = 0; r < RIGHE; r++) {
        for (c = 0; c < COLONNE; c++) {
            t[r][c] = IGNOTA;
        }
        t[r][COLONNE] = '\0';
    }
}

/* Stampa una griglia con le coordinate usate dal giocatore. */
void stampa_griglia(const char g[][COLONNE + 1])
{
    int r;
    int c;

    printf("\n    ");
    for (c = 0; c < COLONNE; c++) {
        printf("%d ", c + 1);
    }
    printf("\n");
    for (r = 0; r < RIGHE; r++) {
        printf("  %c ", 'A' + r);
        for (c = 0; c < COLONNE; c++) {
            printf("%c ", g[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

int conta_celle(const char g[][COLONNE + 1], char simbolo)
{
    int r;
    int c;
    int n = 0;

    for (r = 0; r < RIGHE; r++) {
        for (c = 0; c < COLONNE; c++) {
            if (g[r][c] == simbolo) {
                n++;
            }
        }
    }
    return n;
}
