/*
 * 070-problema-consumi-condominio.c
 *
 * Consumi di riscaldamento di un condominio
 *
 * Un condominio con riscaldamento centralizzato ripartisce le spese in
 * base ai consumi letti dai contabilizzatori. L'amministratore ha le
 * letture mensili (in kWh) di 6 appartamenti per i 6 mesi della stagione
 * termica (ottobre-marzo) e vuole sapere:
 *   - il consumo stagionale di ogni appartamento e la quota sul totale;
 *   - il consumo totale di ogni mese e il mese di picco;
 *   - gli appartamenti che consumano più del 120% della media;
 *   - in quale mese ogni appartamento ha consumato di più.
 *
 * Struttura dati:
 *   int consumi[APPARTAMENTI][MESI]
 *   int interni[APPARTAMENTI]       numero di interno, parallelo alle righe
 *   char mesi[MESI][4]              sigla del mese, parallela alle colonne
 *   int stagione[APPARTAMENTI]      calcolato: totale di ogni riga
 */

#include <stdio.h>

#define APPARTAMENTI 6
#define MESI         6
#define SOGLIA_PERCENTO 120

int main(void)
{
    int consumi[APPARTAMENTI][MESI] = {
        {310, 520, 780, 820, 650, 400},
        {280, 450, 700, 760, 590, 350},
        {450, 690, 980, 1050, 860, 560},
        {150, 260, 450, 430, 330, 200},
        {300, 500, 750, 800, 620, 390},
        {200, 360, 540, 560, 610, 270}
    };
    int interni[APPARTAMENTI] = {1, 2, 3, 4, 5, 6};
    char mesi[MESI][4] = {"Ott", "Nov", "Dic", "Gen", "Feb", "Mar"};
    int stagione[APPARTAMENTI];

    int a;
    int m;
    int totale_condominio = 0;
    int totale_mese;
    int max_mese = 0;
    int m_picco = 0;
    int m_max_app;
    double media;

    /* ── 1. Tabella con totale per appartamento ───────────────────── */
    printf("=== CONSUMI RISCALDAMENTO (kWh) ===\n\n");
    printf("  Interno");
    for (m = 0; m < MESI; m++) {
        printf("%6s", mesi[m]);
    }
    printf("  Stagione\n");

    for (a = 0; a < APPARTAMENTI; a++) {
        stagione[a] = 0;
        printf("  %7d", interni[a]);
        for (m = 0; m < MESI; m++) {
            printf("%6d", consumi[a][m]);
            stagione[a] = stagione[a] + consumi[a][m];
        }
        printf("%10d\n", stagione[a]);
        totale_condominio = totale_condominio + stagione[a];
    }

    /* ── 2. Totale per mese e mese di picco ───────────────────────── */
    printf("  Totale ");
    for (m = 0; m < MESI; m++) {
        totale_mese = 0;
        for (a = 0; a < APPARTAMENTI; a++) {
            totale_mese = totale_mese + consumi[a][m];
        }
        printf("%6d", totale_mese);
        if (totale_mese > max_mese) {
            max_mese = totale_mese;
            m_picco = m;
        }
    }
    printf("%10d\n\n", totale_condominio);
    printf("Mese di picco: %s (%d kWh)\n\n", mesi[m_picco], max_mese);

    /* ── 3. Quote e appartamenti sopra soglia ─────────────────────────
     * La media è calcolata sul totale stagionale degli appartamenti.   */
    media = (double) totale_condominio / APPARTAMENTI;
    printf("Consumo medio per appartamento: %.0f kWh\n", media);
    printf("Soglia di attenzione (%d%% della media): %.0f kWh\n\n",
           SOGLIA_PERCENTO, media * SOGLIA_PERCENTO / 100.0);

    printf("  Interno   Quota   Mese max\n");
    for (a = 0; a < APPARTAMENTI; a++) {
        /* mese di massimo consumo della riga a */
        m_max_app = 0;
        for (m = 1; m < MESI; m++) {
            if (consumi[a][m] > consumi[a][m_max_app]) {
                m_max_app = m;
            }
        }

        printf("  %7d  %5.1f%%   %s", interni[a],
               100.0 * stagione[a] / totale_condominio, mesi[m_max_app]);

        if (stagione[a] * 100.0 > media * SOGLIA_PERCENTO) {
            printf("   <- consumo elevato");
        }
        printf("\n");
    }

    return 0;
}
