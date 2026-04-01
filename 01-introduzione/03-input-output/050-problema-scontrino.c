/*
 * 050-problema-scontrino.c
 *
 * Scontrino di tre articoli
 *
 * L'utente inserisce prezzo unitario e quantità di tre articoli.
 * Il programma calcola i subtotali, il totale imponibile, l'IVA al 22%
 * e il totale ivato, stampando uno scontrino formattato con colonne
 * allineate e separatori ASCII.
 *
 * Mette in pratica: scanf con tipi misti (double e int), printf con
 * larghezze di campo e precisione monetaria, calcoli tra interi e reali.
 */

#include <stdio.h>

#define IVA 0.22   /* aliquota IVA ordinaria italiana */

int main(void)
{
    /* dati dei tre articoli */
    double prezzo1;
    int    quantita1;
    double prezzo2;
    int    quantita2;
    double prezzo3;
    int    quantita3;

    /* subtotali e totali */
    double subtotale1;
    double subtotale2;
    double subtotale3;
    double totale_imponibile;
    double importo_iva;
    double totale_ivato;

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Inserimento articoli ===\n\n");

    printf("Articolo 1 - prezzo unitario (EUR): ");
    scanf("%lf", &prezzo1);
    printf("Articolo 1 - quantita':             ");
    scanf("%d", &quantita1);

    printf("Articolo 2 - prezzo unitario (EUR): ");
    scanf("%lf", &prezzo2);
    printf("Articolo 2 - quantita':             ");
    scanf("%d", &quantita2);

    printf("Articolo 3 - prezzo unitario (EUR): ");
    scanf("%lf", &prezzo3);
    printf("Articolo 3 - quantita':             ");
    scanf("%d", &quantita3);

    /* ── calcoli ────────────────────────────────────────────────────────── */
    /* cast (double) per evitare che la quantità intera influenzi il tipo
     * del risultato in contesti di moltiplicazione mista */
    subtotale1 = prezzo1 * (double)quantita1;
    subtotale2 = prezzo2 * (double)quantita2;
    subtotale3 = prezzo3 * (double)quantita3;

    totale_imponibile = subtotale1 + subtotale2 + subtotale3;
    importo_iva       = totale_imponibile * IVA;
    totale_ivato      = totale_imponibile + importo_iva;

    /* ── output: scontrino formattato ───────────────────────────────────── */
    printf("\n");
    printf("+-------------------------------------+\n");
    printf("|        SCONTRINO FISCALE            |\n");
    printf("+-------------------------------------+\n");
    printf("| %-18s  %4s  %8s |\n", "Articolo", "Qta'", "Importo");
    printf("+-------------------------------------+\n");
    printf("| %-18s  %4d  %8.2f |\n", "Articolo 1", quantita1, subtotale1);
    printf("| %-18s  %4d  %8.2f |\n", "Articolo 2", quantita2, subtotale2);
    printf("| %-18s  %4d  %8.2f |\n", "Articolo 3", quantita3, subtotale3);
    printf("+-------------------------------------+\n");
    printf("| %-23s  %8.2f |\n", "Totale imponibile",   totale_imponibile);
    printf("| %-23s  %8.2f |\n", "IVA 22%",             importo_iva);
    printf("+-------------------------------------+\n");
    printf("| %-23s  %8.2f |\n", "TOTALE",              totale_ivato);
    printf("+-------------------------------------+\n");

    return 0;
}
