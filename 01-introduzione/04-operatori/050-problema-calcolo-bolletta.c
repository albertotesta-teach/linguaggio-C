/*
 * 050-problema-calcolo-bolletta.c
 *
 * Calcolo bolletta elettrica
 *
 * L'utente inserisce la lettura precedente e attuale del contatore (kWh),
 * la potenza impegnata (kW) e la fascia oraria (1=F1, 2=F2, 3=F3).
 * Il programma calcola i kWh consumati, il costo energia, la quota fissa
 * e il totale con IVA al 10% (aliquota agevolata per uso domestico).
 *
 * Il prezzo per fascia viene selezionato con l'operatore ternario (?:),
 * che restituisce un valore in base a una condizione senza usare if/else.
 * Operatore ternario:  condizione ? valore_se_vero : valore_se_falso
 */

#include <stdio.h>

/* prezzi per kWh per fascia (tariffe indicative in EUR/kWh) */
#define PREZZO_F1   0.28    /* fascia F1: ore di punta (lun-ven 8-19) */
#define PREZZO_F2   0.22    /* fascia F2: ore intermedie              */
#define PREZZO_F3   0.18    /* fascia F3: ore fuori punta             */

/* quota fissa mensile per kW di potenza impegnata */
#define QUOTA_FISSA_PER_KW  10.50

/* aliquota IVA agevolata per uso domestico */
#define IVA_DOMESTICA  0.10

int main(void)
{
    /* dati inseriti dall'utente */
    int    lettura_precedente;
    int    lettura_attuale;
    double potenza_kw;
    int    fascia;           /* 1=F1, 2=F2, 3=F3 */

    /* dati calcolati */
    int    kwh_consumati;
    double prezzo_kwh;
    double costo_energia;
    double quota_fissa;
    double imponibile;
    double importo_iva;
    double totale;

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Calcolo bolletta elettrica ===\n\n");

    printf("Lettura precedente (kWh): ");
    scanf("%d", &lettura_precedente);

    printf("Lettura attuale   (kWh): ");
    scanf("%d", &lettura_attuale);

    printf("Potenza impegnata  (kW): ");
    scanf("%lf", &potenza_kw);

    printf("Fascia oraria (1=F1, 2=F2, 3=F3): ");
    scanf("%d", &fascia);

    /* ── calcoli ────────────────────────────────────────────────────────── */
    kwh_consumati = lettura_attuale - lettura_precedente;

    /* selezione del prezzo per fascia con operatore ternario annidato.
     * Lettura: "se fascia==1 usa PREZZO_F1,
     *           altrimenti se fascia==2 usa PREZZO_F2,
     *           altrimenti usa PREZZO_F3" */
    prezzo_kwh = (fascia == 1) ? PREZZO_F1
               : (fascia == 2) ? PREZZO_F2
               :                 PREZZO_F3;

    costo_energia = kwh_consumati * prezzo_kwh;
    quota_fissa   = potenza_kw * QUOTA_FISSA_PER_KW;

    imponibile  = costo_energia + quota_fissa;
    importo_iva = imponibile * IVA_DOMESTICA;
    totale      = imponibile + importo_iva;

    /* ── output: bolletta formattata ────────────────────────────────────── */
    printf("\n");
    printf("==========================================\n");
    printf("  BOLLETTA ELETTRICA\n");
    printf("==========================================\n");
    printf("  Lettura precedente:  %8d kWh\n",  lettura_precedente);
    printf("  Lettura attuale:     %8d kWh\n",  lettura_attuale);
    printf("  Consumo:             %8d kWh\n",  kwh_consumati);
    printf("  Fascia:              %8d\n",       fascia);
    printf("  Prezzo/kWh:         %9.4f EUR\n", prezzo_kwh);
    printf("------------------------------------------\n");
    printf("  Costo energia:      %9.2f EUR\n", costo_energia);
    printf("  Quota fissa:        %9.2f EUR\n", quota_fissa);
    printf("  Imponibile:         %9.2f EUR\n", imponibile);
    printf("  IVA 10%%:            %9.2f EUR\n", importo_iva);
    printf("==========================================\n");
    printf("  TOTALE:             %9.2f EUR\n", totale);
    printf("==========================================\n");

    return 0;
}
