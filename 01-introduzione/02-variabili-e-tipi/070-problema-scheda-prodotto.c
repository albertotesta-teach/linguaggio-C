/*
 * 070-problema-scheda-prodotto.c
 *
 * Scheda prodotto a magazzino
 *
 * L'utente inserisce i dati numerici di un prodotto:
 * codice identificativo, prezzo unitario, quantità disponibile e
 * percentuale di sconto. Il programma calcola il valore totale del
 * magazzino, il prezzo scontato unitario e stampa una scheda prodotto
 * formattata con allineamento a colonne.
 *
 * Mette in pratica: tipi misti (int e double), operazioni aritmetiche
 * tra tipi diversi, formattazione monetaria con %.2f e allineamento
 * dei campi con specificatori di larghezza.
 */

#include <stdio.h>

#define LARGHEZZA_ETICHETTA 22   /* larghezza colonna etichette nella scheda */

int main(void)
{
    /* dati inseriti dall'utente */
    int    codice;           /* codice numerico del prodotto */
    double prezzo_unitario;  /* prezzo senza sconto (EUR) */
    int    quantita;         /* pezzi disponibili in magazzino */
    double sconto_percento;  /* percentuale di sconto (es. 15.0 per 15%) */

    /* dati calcolati */
    double fattore_sconto;   /* es. 0.15 per uno sconto del 15% */
    double prezzo_scontato;  /* prezzo dopo lo sconto */
    double valore_magazzino; /* prezzo unitario * quantità (senza sconto) */
    double risparmio;        /* quanto si risparmia per unità */

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Inserimento dati prodotto ===\n\n");

    printf("Codice prodotto:          ");
    scanf("%d", &codice);

    printf("Prezzo unitario (EUR):    ");
    scanf("%lf", &prezzo_unitario);

    printf("Quantita' in magazzino:   ");
    scanf("%d", &quantita);

    printf("Sconto (%%, es. 15.0):    ");
    scanf("%lf", &sconto_percento);

    /* ── calcoli ────────────────────────────────────────────────────────── */
    fattore_sconto   = sconto_percento / 100.0;
    risparmio        = prezzo_unitario * fattore_sconto;
    prezzo_scontato  = prezzo_unitario - risparmio;

    /* il valore di magazzino è calcolato al prezzo pieno (senza sconto):
     * rappresenta il valore contabile dei beni presenti */
    valore_magazzino = prezzo_unitario * (double)quantita;
    /* (double) è un cast esplicito: converte quantita da int a double
     * prima della moltiplicazione, evitando possibili problemi di overflow
     * con interi grandi. */

    /* ── output: scheda prodotto ────────────────────────────────────────── */
    printf("\n");
    printf("====================================\n");
    printf("  SCHEDA PRODOTTO\n");
    printf("====================================\n");
    printf("  Codice:           %06d\n",   codice);
    printf("  Prezzo pieno:     %8.2f EUR\n", prezzo_unitario);
    printf("  Sconto:           %8.1f %%\n",  sconto_percento);
    printf("  Risparmio:        %8.2f EUR\n", risparmio);
    printf("  Prezzo scontato:  %8.2f EUR\n", prezzo_scontato);
    printf("------------------------------------\n");
    printf("  Quantita':        %8d pz\n",   quantita);
    printf("  Valore magazzino: %8.2f EUR\n", valore_magazzino);
    printf("====================================\n");

    return 0;
}
