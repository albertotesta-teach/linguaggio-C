/*
 * 040-problema-contatore-chiamate.c
 *
 * Contatore globale di invocazioni di funzione
 *
 * Un sistema di diagnostica deve tenere traccia di quante volte
 * ciascuna funzione viene chiamata durante l'esecuzione del programma.
 * I contatori sono variabili globali, aggiornate all'inizio di ogni
 * funzione. Al termine il programma stampa un riepilogo delle invocazioni.
 *
 * Questo esempio mostra un caso d'uso legittimo delle variabili globali:
 * uno stato condiviso che deve sopravvivere tra chiamate successive e
 * che sarebbe scomodo passare come parametro a ogni funzione.
 */

#include <stdio.h>

/* --- Contatori globali ---
 * Un contatore per ciascuna funzione monitorata.
 * Inizializzati a zero automaticamente. */
int chiamate_calcola_sconto = 0;
int chiamate_calcola_iva    = 0;
int chiamate_stampa_prezzo  = 0;

/* Prototipi */
double calcola_sconto(double prezzo, int percentuale);
double calcola_iva(double imponibile);
void   stampa_prezzo(double prezzo_originale, double prezzo_finale);
void   stampa_riepilogo_chiamate(void);

/* --- Funzioni monitorate --- */

double calcola_sconto(double prezzo, int percentuale)
{
    double sconto, prezzo_scontato;
    chiamate_calcola_sconto = chiamate_calcola_sconto + 1;

    sconto = prezzo * percentuale / 100.0;
    prezzo_scontato = prezzo - sconto;
    return prezzo_scontato;
}

double calcola_iva(double imponibile)
{
    double prezzo_con_iva;
    chiamate_calcola_iva = chiamate_calcola_iva + 1;

    prezzo_con_iva = imponibile * 1.22;   /* IVA al 22% */
    return prezzo_con_iva;
}

void stampa_prezzo(double prezzo_originale, double prezzo_finale)
{
    chiamate_stampa_prezzo = chiamate_stampa_prezzo + 1;

    printf("  Prezzo originale: %8.2f EUR\n", prezzo_originale);
    printf("  Prezzo finale:    %8.2f EUR\n", prezzo_finale);
    printf("  Risparmio:        %8.2f EUR\n", prezzo_originale - prezzo_finale);
    printf("\n");
}

void stampa_riepilogo_chiamate(void)
{
    printf("=== Riepilogo chiamate ===\n");
    printf("  calcola_sconto:  %d\n", chiamate_calcola_sconto);
    printf("  calcola_iva:     %d\n", chiamate_calcola_iva);
    printf("  stampa_prezzo:   %d\n", chiamate_stampa_prezzo);
    printf("  Totale:          %d\n",
           chiamate_calcola_sconto + chiamate_calcola_iva + chiamate_stampa_prezzo);
}

int main(void)
{
    double prezzo, scontato, finale;

    printf("=== Listino prezzi scontati ===\n\n");

    /* Prodotto 1: sconto 10%, poi IVA */
    prezzo   = 150.00;
    scontato = calcola_sconto(prezzo, 10);
    finale   = calcola_iva(scontato);
    printf("Prodotto A (sconto 10%%, IVA 22%%):\n");
    stampa_prezzo(prezzo, finale);

    /* Prodotto 2: sconto 20%, poi IVA */
    prezzo   = 200.00;
    scontato = calcola_sconto(prezzo, 20);
    finale   = calcola_iva(scontato);
    printf("Prodotto B (sconto 20%%, IVA 22%%):\n");
    stampa_prezzo(prezzo, finale);

    /* Prodotto 3: solo IVA, nessuno sconto */
    prezzo = 80.00;
    finale = calcola_iva(prezzo);
    printf("Prodotto C (nessuno sconto, IVA 22%%):\n");
    stampa_prezzo(prezzo, finale);

    /* Prodotto 4: doppio sconto applicato in sequenza */
    prezzo   = 300.00;
    scontato = calcola_sconto(prezzo, 15);
    scontato = calcola_sconto(scontato, 5);
    finale   = calcola_iva(scontato);
    printf("Prodotto D (sconto 15%% + 5%%, IVA 22%%):\n");
    stampa_prezzo(prezzo, finale);

    stampa_riepilogo_chiamate();

    return 0;
}
