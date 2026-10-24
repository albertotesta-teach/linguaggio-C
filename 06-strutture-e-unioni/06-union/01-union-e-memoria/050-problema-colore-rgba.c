/*
 * 050-problema-colore-rgba.c
 *
 * Il sito della scuola: schiarire, scurire e rendere grigi i colori
 *
 * Un colore RGBA è un numero a 32 bit 0xRRGGBBAA: rosso, verde, blu e
 * trasparenza (alfa), un byte ciascuno. Con una union si legge il colore
 * intero o un canale alla volta:
 *
 *     typedef enum { ALFA, BLU, VERDE, ROSSO, NUM_CANALI } Canale;
 *
 *     typedef union {
 *         uint32_t codice;
 *         uint8_t canale[NUM_CANALI];
 *     } Colore;
 *
 *     c.canale[ROSSO]
 *
 * L'enum elenca i canali nell'ordine in cui stanno in memoria su una
 * macchina little-endian: il byte meno significativo (AA) è canale[0].
 *
 * Comandi (il colore si scrive come RRGGBB, alfa vale FF):
 *     S RRGGBB p    schiarisce del p per cento verso il bianco
 *     D RRGGBB p    scurisce del p per cento verso il nero
 *     G RRGGBB      grigio con la stessa luminosità:
 *                   0.299 R + 0.587 G + 0.114 B
 *     Q             fine
 */

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

typedef enum {
    ALFA, BLU, VERDE, ROSSO, NUM_CANALI
} Canale;

typedef union {
    uint32_t codice;
    uint8_t canale[NUM_CANALI];
} Colore;

Colore schiarisci(Colore c, int percento);
Colore scurisci(Colore c, int percento);
Colore grigio(Colore c);
void stampa(const char *nome, Colore c);
void svuota_riga(void);

int main(void)
{
    char comando = ' ';
    unsigned long rgb;
    int percento = 0;
    Colore c;

    while (comando != 'Q') {
        printf("Comando (S RRGGBB p, D RRGGBB p, G RRGGBB, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'S' || comando == 'D' || comando == 'G') {
            if (scanf("%6lx", &rgb) != 1 ||
                (comando != 'G' &&
                 (scanf("%d", &percento) != 1 || percento < 0 || percento > 100))) {
                printf("  Dati non validi.\n");
            } else {
                c.codice = (uint32_t) ((rgb << 8) | 0xFF);
                stampa("originale", c);
                if (comando == 'S') {
                    stampa("schiarito", schiarisci(c, percento));
                } else if (comando == 'D') {
                    stampa("scurito", scurisci(c, percento));
                } else {
                    stampa("grigio", grigio(c));
                }
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        svuota_riga();                  /* un comando per riga */
    }

    return 0;
}

/* Ogni canale si avvicina a 255 del percento indicato; alfa non cambia. */
Colore schiarisci(Colore c, int percento)
{
    Canale k;

    for (k = BLU; k < NUM_CANALI; k++) {
        c.canale[k] = (uint8_t) (c.canale[k] + (255 - c.canale[k]) * percento / 100);
    }
    return c;
}

Colore scurisci(Colore c, int percento)
{
    Canale k;

    for (k = BLU; k < NUM_CANALI; k++) {
        c.canale[k] = (uint8_t) (c.canale[k] - c.canale[k] * percento / 100);
    }
    return c;
}

Colore grigio(Colore c)
{
    uint8_t luminosita = (uint8_t) (0.299 * c.canale[ROSSO] + 0.587 * c.canale[VERDE] +
                                    0.114 * c.canale[BLU] + 0.5);

    c.canale[ROSSO] = luminosita;
    c.canale[VERDE] = luminosita;
    c.canale[BLU] = luminosita;
    return c;
}

void stampa(const char *nome, Colore c)
{
    printf("  %-10s #%08lX   R %3d  G %3d  B %3d  A %3d\n", nome, (unsigned long) c.codice,
           c.canale[ROSSO], c.canale[VERDE], c.canale[BLU], c.canale[ALFA]);
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
