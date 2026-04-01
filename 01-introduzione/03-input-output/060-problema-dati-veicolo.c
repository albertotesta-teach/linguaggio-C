/*
 * 060-problema-dati-veicolo.c
 *
 * Scheda tecnica di un veicolo
 *
 * L'utente inserisce i dati numerici di un veicolo: anno di immatricolazione,
 * cilindrata in cc, potenza in kW, numero di porte e prezzo di listino.
 * Il programma calcola l'anzianità del veicolo (anni trascorsi) e converte
 * la potenza da kW a CV, stampando una scheda tecnica formattata.
 *
 * Mette in pratica: scanf con tipi misti, printf con larghezze di campo,
 * costante di conversione con #define, calcoli tra interi e reali.
 */

#include <stdio.h>

#define ANNO_CORRENTE     2024
#define KW_IN_CV          1.35962   /* 1 kW = 1.35962 CV */

int main(void)
{
    /* dati inseriti dall'utente */
    int    anno_immatricolazione;
    int    cilindrata_cc;       /* cilindrata in centimetri cubici */
    double potenza_kw;          /* potenza del motore in kilowatt */
    int    num_porte;
    double prezzo_listino;      /* prezzo di listino in EUR */

    /* dati calcolati */
    int    anzianita_anni;      /* anni trascorsi dall'immatricolazione */
    double potenza_cv;          /* potenza convertita in cavalli vapore */

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Inserimento dati veicolo ===\n\n");

    printf("Anno di immatricolazione:     ");
    scanf("%d", &anno_immatricolazione);

    printf("Cilindrata (cc):              ");
    scanf("%d", &cilindrata_cc);

    printf("Potenza (kW):                 ");
    scanf("%lf", &potenza_kw);

    printf("Numero di porte:              ");
    scanf("%d", &num_porte);

    printf("Prezzo di listino (EUR):      ");
    scanf("%lf", &prezzo_listino);

    /* ── calcoli ────────────────────────────────────────────────────────── */
    anzianita_anni = ANNO_CORRENTE - anno_immatricolazione;
    potenza_cv     = potenza_kw * KW_IN_CV;

    /* ── output: scheda tecnica ─────────────────────────────────────────── */
    printf("\n");
    printf("==========================================\n");
    printf("  SCHEDA TECNICA VEICOLO\n");
    printf("==========================================\n");
    printf("  Anno immatricolazione: %d\n",      anno_immatricolazione);
    printf("  Anzianita':            %d anni\n", anzianita_anni);
    printf("------------------------------------------\n");
    printf("  Cilindrata:     %8d cc\n",         cilindrata_cc);
    printf("  Potenza:        %8.1f kW\n",        potenza_kw);
    printf("  Potenza:        %8.1f CV\n",        potenza_cv);
    printf("  Porte:          %8d\n",             num_porte);
    printf("------------------------------------------\n");
    printf("  Prezzo listino: %8.2f EUR\n",       prezzo_listino);
    printf("==========================================\n");

    return 0;
}
