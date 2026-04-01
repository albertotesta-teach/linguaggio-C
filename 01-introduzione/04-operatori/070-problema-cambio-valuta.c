/*
 * 070-problema-cambio-valuta.c
 *
 * Convertitore di valuta con commissione
 *
 * L'utente inserisce un importo in EUR e sceglie la valuta di destinazione
 * (1=USD, 2=GBP, 3=JPY, 4=CHF). Il programma seleziona il tasso di cambio
 * con l'operatore ternario annidato, calcola la commissione con *=
 * e stampa il dettaglio della conversione.
 *
 * Tassi e commissione sono costanti #define (valori indicativi).
 * Zero if/else: tutta la logica di selezione è espressa con l'operatore ?:
 */

#include <stdio.h>

/* tassi di cambio EUR -> valuta (valori indicativi) */
#define TASSO_USD  1.085
#define TASSO_GBP  0.857
#define TASSO_JPY  161.5
#define TASSO_CHF  0.963

/* commissione applicata sulla conversione */
#define COMMISSIONE  0.015   /* 1.5% */

int main(void)
{
    double importo_eur;
    int    scelta;           /* 1=USD, 2=GBP, 3=JPY, 4=CHF */

    double tasso;            /* tasso di cambio selezionato */
    double importo_convertito;
    double importo_commissione;
    double importo_netto;    /* dopo la commissione */

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Convertitore di valuta ===\n\n");

    printf("Importo in EUR: ");
    scanf("%lf", &importo_eur);

    printf("Valuta di destinazione:\n");
    printf("  1 - Dollaro USA (USD)\n");
    printf("  2 - Sterlina    (GBP)\n");
    printf("  3 - Yen giapp.  (JPY)\n");
    printf("  4 - Franco sviz.(CHF)\n");
    printf("Scelta: ");
    scanf("%d", &scelta);

    /* ── selezione del tasso con operatore ternario annidato ────────────── */
    tasso = (scelta == 1) ? TASSO_USD
          : (scelta == 2) ? TASSO_GBP
          : (scelta == 3) ? TASSO_JPY
          :                 TASSO_CHF;   /* default: CHF per qualsiasi altra scelta */

    /* ── calcoli ────────────────────────────────────────────────────────── */
    importo_convertito   = importo_eur * tasso;

    /* la commissione è calcolata sull'importo convertito con *= */
    importo_commissione  = importo_convertito;
    importo_commissione *= COMMISSIONE;   /* importo_commissione = convertito * 1.5% */

    importo_netto = importo_convertito - importo_commissione;

    /* ── selezione del simbolo della valuta con operatore ternario ───────── */
    /* %s stampa la stringa restituita dall'operatore ternario */
    printf("\n=== Dettaglio conversione ===\n");
    printf("Importo originale:   %10.2f EUR\n",  importo_eur);
    printf("Valuta:              %10s\n",
           (scelta == 1) ? "USD"
         : (scelta == 2) ? "GBP"
         : (scelta == 3) ? "JPY"
         :                 "CHF");
    printf("Tasso di cambio:     %10.4f\n",       tasso);
    printf("Importo convertito:  %10.2f\n",       importo_convertito);
    printf("Commissione (1.5%%): %10.2f\n",       importo_commissione);
    printf("------------------------------\n");
    printf("Importo netto:       %10.2f\n",       importo_netto);

    return 0;
}
