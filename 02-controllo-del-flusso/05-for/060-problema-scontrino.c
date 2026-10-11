/*
 * 060-problema-scontrino.c
 *
 * Scontrino di una cassa
 *
 * La cassiera dichiara quanti articoli diversi ci sono nel carrello, poi
 * per ciascuno inserisce prezzo unitario e quantità. Il programma stampa
 * ogni riga dello scontrino man mano, poi:
 *   - il numero totale di pezzi;
 *   - il subtotale;
 *   - lo sconto del 5% se la spesa supera 100 euro;
 *   - il totale da pagare;
 *   - la riga con l'importo più alto (numero della riga e importo).
 *
 * Il numero di articoli è noto prima del ciclo: si usa un for. Gli articoli
 * non vengono memorizzati (niente array): ogni riga viene elaborata subito
 * con accumulatori e con la ricerca del massimo.
 */

#include <stdio.h>

#define SOGLIA_SCONTO      100.0
#define PERCENTUALE_SCONTO   5.0

int main(void)
{
    int numero_articoli;
    int riga;
    double prezzo;
    int quantita;
    double importo_riga;
    double subtotale = 0.0;
    double sconto = 0.0;
    int pezzi = 0;
    double importo_massimo = 0.0;
    int riga_massima = 0;

    printf("=== CASSA ===\n");

    do {
        printf("Numero di articoli diversi: ");
        scanf("%d", &numero_articoli);
    } while (numero_articoli <= 0);

    for (riga = 1; riga <= numero_articoli; riga++) {
        printf("\nArticolo %d\n", riga);

        do {
            printf("  Prezzo unitario: ");
            scanf("%lf", &prezzo);
        } while (prezzo <= 0.0);

        do {
            printf("  Quantita': ");
            scanf("%d", &quantita);
        } while (quantita <= 0);

        importo_riga = prezzo * quantita;
        subtotale = subtotale + importo_riga;
        pezzi = pezzi + quantita;

        /* Ricerca del massimo: la prima riga inizializza */
        if (riga == 1 || importo_riga > importo_massimo) {
            importo_massimo = importo_riga;
            riga_massima = riga;
        }

        printf("  %d x %.2f = %.2f euro\n", quantita, prezzo, importo_riga);
    }

    if (subtotale > SOGLIA_SCONTO) {
        sconto = subtotale * PERCENTUALE_SCONTO / 100.0;
    }

    printf("\n================================\n");
    printf("  Articoli diversi : %8d\n", numero_articoli);
    printf("  Pezzi totali     : %8d\n", pezzi);
    printf("  Subtotale        : %8.2f\n", subtotale);
    if (sconto > 0.0) {
        printf("  Sconto %.0f%%        : %8.2f\n", PERCENTUALE_SCONTO, -sconto);
    }
    printf("  TOTALE EURO      : %8.2f\n", subtotale - sconto);
    printf("================================\n");
    printf("Riga piu' costosa: n. %d (%.2f euro)\n", riga_massima, importo_massimo);

    /*
     * NOTA: qui si usano i double per semplicità. In un vero gestionale
     * gli importi si memorizzano in centesimi interi (vedi
     * 03-switch/050-problema-distributore-bevande.c) per evitare errori
     * di arrotondamento.
     */

    return 0;
}
