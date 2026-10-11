/*
 * 050-problema-distributore-bevande.c
 *
 * Distributore automatico di bevande
 *
 * Il distributore offre cinque prodotti, ciascuno con un codice:
 *
 *   11  Acqua naturale     0,60 euro
 *   12  Acqua frizzante    0,60 euro
 *   21  Te' al limone      1,20 euro
 *   22  Succo di frutta    1,20 euro
 *   31  Caffe' freddo      1,50 euro
 *
 * L'utente digita il codice e inserisce l'importo in centesimi.
 * Lo switch associa al codice il nome e il prezzo del prodotto
 * (i prodotti con lo stesso prezzo condividono l'assegnazione del
 * prezzo grazie ai casi raggruppati). Poi un if-else decide se
 * l'importo è sufficiente e calcola il resto.
 */

#include <stdio.h>

#define PREZZO_ACQUA  60
#define PREZZO_BIBITA 120
#define PREZZO_CAFFE  150

int main(void)
{
    int codice;
    int importo;
    int prezzo;
    int resto;
    int prodotto_valido;

    printf("=== DISTRIBUTORE AUTOMATICO ===\n");
    printf("  11  Acqua naturale     0,60\n");
    printf("  12  Acqua frizzante    0,60\n");
    printf("  21  Te' al limone      1,20\n");
    printf("  22  Succo di frutta    1,20\n");
    printf("  31  Caffe' freddo      1,50\n");
    printf("Codice prodotto: ");
    scanf("%d", &codice);

    prodotto_valido = 1;
    prezzo = 0;

    /* ── 1. Nome del prodotto ─────────────────────────────────────── */
    switch (codice) {
        case 11:
            printf("Selezionato: Acqua naturale\n");
            break;
        case 12:
            printf("Selezionato: Acqua frizzante\n");
            break;
        case 21:
            printf("Selezionato: Te' al limone\n");
            break;
        case 22:
            printf("Selezionato: Succo di frutta\n");
            break;
        case 31:
            printf("Selezionato: Caffe' freddo\n");
            break;
        default:
            printf("Codice %d inesistente.\n", codice);
            break;
    }

    /* ── 2. Prezzo: casi raggruppati per fascia di prezzo ─────────── */
    switch (codice) {
        case 11:
        case 12:
            prezzo = PREZZO_ACQUA;
            break;
        case 21:
        case 22:
            prezzo = PREZZO_BIBITA;
            break;
        case 31:
            prezzo = PREZZO_CAFFE;
            break;
        default:
            prodotto_valido = 0;
            break;
    }

    /* ── 3. Pagamento ────────────────────────────────────────────────
     * Si chiede l'importo solo se il prodotto esiste.                 */
    if (prodotto_valido) {
        printf("Prezzo: %d,%02d euro\n", prezzo / 100, prezzo % 100);
        printf("Importo inserito (centesimi): ");
        scanf("%d", &importo);

        if (importo >= prezzo) {
            resto = importo - prezzo;
            printf("Erogazione in corso... Resto: %d,%02d euro\n",
                   resto / 100, resto % 100);
        } else {
            printf("Importo insufficiente: mancano %d centesimi. Monete restituite.\n",
                   prezzo - importo);
        }
    } else {
        printf("Nessuna erogazione.\n");
    }

    /*
     * Perché due switch sullo stesso codice?
     * Il primo associa a ogni codice il proprio nome (un ramo per codice),
     * il secondo raggruppa i codici con lo stesso prezzo. Unirli in un solo
     * switch richiederebbe di ripetere ogni prezzo in ogni ramo.
     */

    return 0;
}
