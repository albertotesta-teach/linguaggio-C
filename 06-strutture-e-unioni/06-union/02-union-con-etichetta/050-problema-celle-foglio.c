/*
 * 050-problema-celle-foglio.c
 *
 * Il foglio delle spese della gita: celle vuote, numeri e testi
 *
 * Ogni cella di un foglio di calcolo è vuota, contiene un numero oppure
 * un testo:
 *
 *     typedef enum { VUOTA, NUMERO, TESTO } TipoCella;
 *
 *     typedef struct {
 *         TipoCella tipo;
 *         union {
 *             double numero;
 *             char testo[12];
 *         } v;
 *     } Cella;
 *
 *     Cella foglio[RIGHE][COLONNE];
 *
 * Una cella VUOTA non usa la union. Quando si scrive in una cella, il
 * contenuto diventa un NUMERO se tutto il testo scritto è un numero
 * (sscanf con %lf e un carattere dopo, che non deve esserci), altrimenti
 * un TESTO.
 *
 * Comandi (righe da 1 a 6, colonne da A a C):
 *     P               stampa il foglio
 *     M B3 contenuto  scrive nella cella
 *     V B3            svuota la cella
 *     S B             somma la colonna: solo i numeri, conta i testi
 *     Q               fine
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define RIGHE 6
#define COLONNE 3
#define LUNG_TESTO 12

typedef enum {
    VUOTA, NUMERO, TESTO
} TipoCella;

typedef struct {
    TipoCella tipo;
    union {
        double numero;
        char testo[LUNG_TESTO];
    } v;
} Cella;

void scrivi(Cella *c, const char *contenuto);
void stampa_foglio(Cella foglio[RIGHE][COLONNE]);
int leggi_cella(int *riga, int *colonna);
void svuota_riga(void);

int main(void)
{
    Cella foglio[RIGHE][COLONNE] = {{{VUOTA, {0}}}};
    char comando = ' ';
    char contenuto[32];
    char lettera;
    int riga;
    int colonna;
    int testi;
    double somma;
    int r;

    scrivi(&foglio[0][0], "Voce");
    scrivi(&foglio[0][1], "Euro");
    scrivi(&foglio[0][2], "Note");
    scrivi(&foglio[1][0], "Pullman");
    scrivi(&foglio[1][1], "1450");
    scrivi(&foglio[2][0], "Museo");
    scrivi(&foglio[2][1], "156");
    scrivi(&foglio[3][0], "Pranzo");
    scrivi(&foglio[3][1], "da definire");
    scrivi(&foglio[3][2], "chiedere");

    while (comando != 'Q') {
        printf("Comando (P, M cella contenuto, V cella, S colonna, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'P') {
            stampa_foglio(foglio);
        } else if (comando == 'M' || comando == 'V') {
            if (!leggi_cella(&riga, &colonna)) {
                printf("  Cella non valida.\n");
            } else if (comando == 'V') {
                foglio[riga][colonna].tipo = VUOTA;
            } else if (scanf(" %31[^\n]", contenuto) == 1) {
                scrivi(&foglio[riga][colonna], contenuto);
                printf("  %c%d: %s\n", 'A' + colonna, riga + 1,
                       foglio[riga][colonna].tipo == NUMERO ? "numero" : "testo");
            }
        } else if (comando == 'S') {
            lettera = ' ';
            if (scanf(" %c", &lettera) == 1) {
                lettera = (char) toupper((unsigned char) lettera);
            }
            if (lettera < 'A' || lettera >= 'A' + COLONNE) {
                printf("  Colonna non valida.\n");
            } else {
                somma = 0;
                testi = 0;
                for (r = 0; r < RIGHE; r++) {
                    switch (foglio[r][lettera - 'A'].tipo) {
                    case NUMERO:
                        somma = somma + foglio[r][lettera - 'A'].v.numero;
                        break;
                    case TESTO:
                        testi++;
                        break;
                    case VUOTA:
                        break;
                    }
                }
                printf("  Somma colonna %c: %.2f (celle di testo ignorate: %d)\n", lettera, somma,
                       testi);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        svuota_riga();                  /* un comando per riga */
    }

    return 0;
}

/* Numero se tutto il contenuto è un numero, altrimenti testo. */
void scrivi(Cella *c, const char *contenuto)
{
    double numero;
    char dopo;

    if (sscanf(contenuto, "%lf %c", &numero, &dopo) == 1) {
        c->tipo = NUMERO;
        c->v.numero = numero;
    } else {
        c->tipo = TESTO;
        strncpy(c->v.testo, contenuto, LUNG_TESTO - 1);
        c->v.testo[LUNG_TESTO - 1] = '\0';
    }
}

/* Legge una cella come B3; restituisce 0 se è fuori dal foglio. */
int leggi_cella(int *riga, int *colonna)
{
    char lettera = ' ';
    int numero = 0;
    int valida = scanf(" %c%d", &lettera, &numero) == 2;

    lettera = (char) toupper((unsigned char) lettera);
    valida = valida && lettera >= 'A' && lettera < 'A' + COLONNE && numero >= 1 &&
             numero <= RIGHE;

    if (valida) {
        *colonna = lettera - 'A';
        *riga = numero - 1;
    }
    return valida;
}

void stampa_foglio(Cella foglio[RIGHE][COLONNE])
{
    int r;
    int c;

    printf("     A            B            C\n");
    for (r = 0; r < RIGHE; r++) {
        printf("  %d ", r + 1);
        for (c = 0; c < COLONNE; c++) {
            switch (foglio[r][c].tipo) {
            case VUOTA:
                printf(" %-12s", ".");
                break;
            case NUMERO:
                printf(" %12.2f", foglio[r][c].v.numero);
                break;
            case TESTO:
                printf(" %-12s", foglio[r][c].v.testo);
                break;
            }
        }
        printf("\n");
    }
}

/* Scarta i caratteri rimasti sulla riga. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
