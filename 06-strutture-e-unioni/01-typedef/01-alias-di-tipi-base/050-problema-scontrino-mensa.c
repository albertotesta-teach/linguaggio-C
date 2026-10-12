/*
 * 050-problema-scontrino-mensa.c
 *
 * Mensa scolastica: lo scontrino con le quantità e lo sconto studenti
 *
 * Alla cassa della mensa l'operatore inserisce il codice di un prodotto e
 * poi la quantità; il codice 0 chiude lo scontrino. Il programma stampa le righe con il
 * subtotale e, alla fine, il totale. Con la tessera studenti (S) si ha uno
 * sconto del 10% se il totale supera 8 euro.
 *
 * Due nomi rendono chiaro il ruolo di ogni numero:
 *
 *     typedef double Euro;          prezzi e importi
 *     typedef int Quantita;         pezzi acquistati
 *
 *     Euro subtotale(Euro prezzo, Quantita pezzi);
 *     Euro sconto(Euro totale, int percentuale);
 *
 * Il listino è un array di Euro; il codice del prodotto è l'indice + 1.
 */

#include <stdio.h>

#define PRODOTTI 6
#define SOGLIA_SCONTO 8.0
#define PERCENTUALE 10

typedef double Euro;
typedef int Quantita;

Euro subtotale(Euro prezzo, Quantita pezzi);
Euro sconto(Euro totale, int percentuale);

int main(void)
{
    const char *nomi[PRODOTTI] = {"Primo piatto", "Secondo piatto", "Contorno",
                                  "Frutta", "Acqua 0.5 l", "Yogurt"};
    Euro listino[PRODOTTI] = {3.20, 3.90, 1.50, 0.80, 0.50, 1.10};
    Euro totale = 0;
    Euro riduzione = 0;
    Quantita pezzi;
    int codice = 1;
    char tessera;
    int k;

    printf("Listino:\n");
    for (k = 0; k < PRODOTTI; k++) {
        printf("  %d  %-15s %5.2f\n", k + 1, nomi[k], listino[k]);
    }

    while (codice != 0) {
        printf("Codice prodotto (0 per chiudere): ");
        if (scanf("%d", &codice) != 1) {
            codice = 0;
        }
        if (codice >= 1 && codice <= PRODOTTI) {
            printf("Quantita': ");
            if (scanf("%d", &pezzi) == 1 && pezzi > 0) {
                totale = totale + subtotale(listino[codice - 1], pezzi);
                printf("  %2d x %-15s %6.2f\n", pezzi, nomi[codice - 1],
                       subtotale(listino[codice - 1], pezzi));
            } else {
                printf("  Quantita' non valida, prodotto non aggiunto.\n");
            }
        } else if (codice != 0) {
            printf("  Codice inesistente.\n");
        }
    }

    printf("Tessera studenti? (S/N): ");
    if (scanf(" %c", &tessera) == 1 && tessera == 'S' && totale > SOGLIA_SCONTO) {
        riduzione = sconto(totale, PERCENTUALE);
    }

    printf("\n  Totale            %6.2f\n", totale);
    if (riduzione > 0) {
        printf("  Sconto %d%%         -%5.2f\n", PERCENTUALE, riduzione);
    }
    printf("  Da pagare         %6.2f euro\n", totale - riduzione);

    return 0;
}

Euro subtotale(Euro prezzo, Quantita pezzi)
{
    return prezzo * pezzi;
}

/* Importo dello sconto, arrotondato al centesimo. */
Euro sconto(Euro totale, int percentuale)
{
    int centesimi = (int) (totale * percentuale + 0.5);

    return centesimi / 100.0;
}
