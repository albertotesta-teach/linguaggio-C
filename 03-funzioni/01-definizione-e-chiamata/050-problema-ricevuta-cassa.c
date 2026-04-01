/*
 * 050-problema-ricevuta-cassa.c
 *
 * Ricevuta fiscale di un supermercato
 *
 * Un sistema di cassa deve stampare una ricevuta fiscale formattata.
 * La ricevuta ha una struttura fissa: intestazione del negozio,
 * elenco dei prodotti acquistati, riepilogo con IVA e totale,
 * e un piede con data e numero ricevuta. Ogni parte è gestita
 * da una funzione separata per facilitare la manutenzione.
 */

#include <stdio.h>

/* Prototipi */
void stampa_intestazione_negozio(void);
void stampa_separatore_ricevuta(void);
void stampa_prodotti(void);
void stampa_riepilogo(void);
void stampa_piede_ricevuta(void);
void stampa_ricevuta(void);

/* --- Implementazioni --- */

void stampa_intestazione_negozio(void)
{
    printf("        SUPERMERCATO BIANCHI\n");
    printf("       Corso Italia 45 - Torino\n");
    printf("       P.IVA 01234567890\n");
    printf("       Tel. 011-9876543\n");
}

void stampa_separatore_ricevuta(void)
{
    printf("------------------------------------\n");
}

void stampa_prodotti(void)
{
    /* Ogni riga della ricevuta: descrizione, quantità, prezzo unitario,
     * prezzo totale della riga. I dati sono fissi in questa versione.
     */
    printf("%-20s %3s %6s %7s\n", "Prodotto", "Qta", "Prezzo", "Totale");
    stampa_separatore_ricevuta();
    printf("%-20s %3d %6.2f %7.2f\n", "Latte intero 1L",   2, 1.35,  2.70);
    printf("%-20s %3d %6.2f %7.2f\n", "Pane di casa",       1, 2.20,  2.20);
    printf("%-20s %3d %6.2f %7.2f\n", "Passata pomodoro",   3, 0.99,  2.97);
    printf("%-20s %3d %6.2f %7.2f\n", "Olio extravergine",  1, 6.50,  6.50);
    printf("%-20s %3d %6.2f %7.2f\n", "Pasta 500g",         4, 1.10,  4.40);
}

void stampa_riepilogo(void)
{
    /* I valori sono calcolati a mano per coerenza con i prodotti sopra.
     * Nel capitolo sui parametri impareremo a calcolarli dinamicamente.
     */
    double subtotale = 18.77;
    double iva       =  0.94;  /* IVA media al 5% applicata agli alimentari */
    double totale    = 19.71;

    stampa_separatore_ricevuta();
    printf("Subtotale (IVA escl.):     %7.2f\n", subtotale);
    printf("IVA (5%% alimentari):       %7.2f\n", iva);
    stampa_separatore_ricevuta();
    printf("TOTALE:                    %7.2f\n", totale);
    stampa_separatore_ricevuta();
    printf("Pagamento: CARTA           %7.2f\n", totale);
    printf("Resto:                     %7.2f\n", 0.00);
}

void stampa_piede_ricevuta(void)
{
    printf("\n");
    printf("  Scontrino N. 00247  Cassa: 03\n");
    printf("  Data: 20/03/2024   Ora: 10:42\n");
    printf("\n");
    printf("  Grazie per la visita!\n");
    printf("  Conservare lo scontrino.\n");
}

void stampa_ricevuta(void)
{
    stampa_intestazione_negozio();
    stampa_separatore_ricevuta();
    stampa_prodotti();
    stampa_riepilogo();
    stampa_piede_ricevuta();
}

int main(void)
{
    stampa_ricevuta();
    return 0;
}
