/*
 * 040-problema-resto-in-monete.c
 *
 * Distributore di bevande: il resto in monete
 *
 * Il distributore della scuola ha una scorta limitata di monete per ogni
 * taglio. A ogni acquisto calcola il resto da dare, usando prima le monete
 * più grandi ma senza superare quelle disponibili. Se non riesce a dare il
 * resto esatto rifiuta la vendita e restituisce l'importo inserito.
 *
 * La funzione eroga_resto produce TRE risultati:
 *   - return:        1 se il resto è esatto, 0 altrimenti;
 *   - usate[]:       quante monete di ogni taglio servono (array di uscita);
 *   - *mancante:     i centesimi che non si riescono a dare.
 * Tagli e scorta si passano come const int *: eroga_resto li legge soltanto.
 * Solo se la vendita va a buon fine il main toglie le monete dalla scorta.
 *
 * Importi in centesimi. Il programma legge coppie "prezzo inserito";
 * con 0 0 termina.
 */

#include <stdio.h>

#define TAGLI 6

int eroga_resto(int resto, const int *tagli, const int *scorta, int *usate, int *mancante);
void svuota_riga(void);

int main(void)
{
    int tagli[TAGLI] = {200, 100, 50, 20, 10, 5};
    int scorta[TAGLI] = {2, 3, 1, 4, 5, 2};
    int usate[TAGLI];
    int prezzo = 1;
    int inserito = 0;
    int mancante;
    int letti;
    int t;

    printf("=== DISTRIBUTORE: RESTO IN MONETE ===\n");
    while (prezzo != 0) {
        printf("\nPrezzo e importo inserito in centesimi (0 0 per finire): ");
        letti = scanf("%d %d", &prezzo, &inserito);
        if (letti == EOF) {
            prezzo = 0;                 /* input terminato: come 0 0 */
        } else if (letti != 2) {
            svuota_riga();              /* non sono due numeri */
            prezzo = -1;                /* importo non valido */
        }
        if (prezzo < 0 || (prezzo > 0 && inserito < prezzo)) {
            printf("  Importo non valido.\n");
        } else if (prezzo > 0 && inserito == prezzo) {
            printf("  Importo esatto: nessun resto.\n");
        } else if (prezzo > 0) {
            if (eroga_resto(inserito - prezzo, tagli, scorta, usate, &mancante)) {
                printf("  Resto %.2f euro:", (inserito - prezzo) / 100.0);
                for (t = 0; t < TAGLI; t++) {
                    if (usate[t] > 0) {
                        printf("  %d x %d cent", usate[t], tagli[t]);
                        scorta[t] = scorta[t] - usate[t];
                    }
                }
                printf("\n");
            } else {
                printf("  Resto non disponibile (mancano %d cent): vendita annullata.\n",
                       mancante);
            }
            printf("  Scorta:");
            for (t = 0; t < TAGLI; t++) {
                printf("  %d cent: %d", tagli[t], scorta[t]);
            }
            printf("\n");
        }
    }

    return 0;
}

/* Calcola le monete per dare resto con la scorta disponibile.
 * Scrive in usate[t] le monete di ogni taglio e in *mancante i centesimi
 * che restano scoperti; restituisce 1 se il resto è esatto. */
int eroga_resto(int resto, const int *tagli, const int *scorta, int *usate, int *mancante)
{
    int t;
    int n;

    for (t = 0; t < TAGLI; t++) {
        n = resto / tagli[t];
        if (n > scorta[t]) {
            n = scorta[t];
        }
        usate[t] = n;
        resto = resto - n * tagli[t];
    }
    *mancante = resto;
    return resto == 0;
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
