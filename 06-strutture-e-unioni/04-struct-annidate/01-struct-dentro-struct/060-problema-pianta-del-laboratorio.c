/*
 * 060-problema-pianta-del-laboratorio.c
 *
 * Laboratorio di fisica: banchi, porta e postazioni sulla pianta
 *
 * Sulla pianta del laboratorio (in centimetri, origine nell'angolo in
 * basso a sinistra) ogni banco è un rettangolo descritto da due punti, gli
 * angoli opposti:
 *
 *     typedef struct {
 *         int x;
 *         int y;
 *     } Punto;
 *
 *     typedef struct {
 *         char nome[8];
 *         Punto basso_sinistra;
 *         Punto alto_destra;
 *     } Banco;
 *
 * Il programma stampa per ogni banco area, centro e distanza del centro
 * dalla porta, e indica il banco più vicino alla porta (lì va il kit di
 * primo soccorso). Poi legge le coordinate di alcune postazioni (x y) e
 * dice su quale banco cadono, oppure se sono nel corridoio; -1 -1
 * termina.
 *
 * Due livelli di punti: b.basso_sinistra.x è la x dell'angolo in basso a
 * sinistra del banco b.
 */

#include <stdio.h>
#include <math.h>

#define BANCHI 4

typedef struct {
    int x;
    int y;
} Punto;

typedef struct {
    char nome[8];
    Punto basso_sinistra;
    Punto alto_destra;
} Banco;

void svuota_riga(void);

int main(void)
{
    Banco banchi[BANCHI] = {
        {"B1", {100, 100}, {340, 180}},
        {"B2", {100, 300}, {340, 380}},
        {"B3", {500, 100}, {740, 180}},
        {"B4", {500, 300}, {740, 380}}
    };
    Punto porta = {800, 0};
    Punto postazione = {0, 0};
    Punto centro;
    int area;
    double distanza;
    double minima = 0;
    int vicino = 0;
    int trovato;
    int i;
    int letti;

    printf("Banco  Area (cm2)  Centro       Distanza dalla porta\n");
    for (i = 0; i < BANCHI; i++) {
        area = (banchi[i].alto_destra.x - banchi[i].basso_sinistra.x) *
               (banchi[i].alto_destra.y - banchi[i].basso_sinistra.y);
        centro.x = (banchi[i].basso_sinistra.x + banchi[i].alto_destra.x) / 2;
        centro.y = (banchi[i].basso_sinistra.y + banchi[i].alto_destra.y) / 2;
        distanza = sqrt((double) (centro.x - porta.x) * (centro.x - porta.x) +
                        (double) (centro.y - porta.y) * (centro.y - porta.y));
        printf("%-6s %10d  (%3d, %3d)   %7.1f cm\n", banchi[i].nome, area, centro.x, centro.y,
               distanza);
        if (i == 0 || distanza < minima) {
            minima = distanza;
            vicino = i;
        }
    }
    printf("Kit di primo soccorso sul banco %s.\n\n", banchi[vicino].nome);

    while (postazione.x != -1 || postazione.y != -1) {
        printf("Postazione (x y, -1 -1 per finire): ");
        letti = scanf("%d %d", &postazione.x, &postazione.y);
        if (letti == EOF) {
            postazione.x = -1;          /* input terminato: come -1 -1 */
            postazione.y = -1;
        } else if (letti != 2) {
            svuota_riga();              /* non sono due numeri */
            printf("  Postazione non valida.\n");
            postazione.x = 0;           /* non e' la richiesta di fine */
        } else if (postazione.x != -1 || postazione.y != -1) {
            trovato = -1;
            i = 0;
            while (i < BANCHI && trovato == -1) {
                if (postazione.x >= banchi[i].basso_sinistra.x &&
                    postazione.x <= banchi[i].alto_destra.x &&
                    postazione.y >= banchi[i].basso_sinistra.y &&
                    postazione.y <= banchi[i].alto_destra.y) {
                    trovato = i;
                }
                i++;
            }
            if (trovato == -1) {
                printf("  (%d, %d): corridoio\n", postazione.x, postazione.y);
            } else {
                printf("  (%d, %d): banco %s\n", postazione.x, postazione.y, banchi[trovato].nome);
            }
        }
    }

    return 0;
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
