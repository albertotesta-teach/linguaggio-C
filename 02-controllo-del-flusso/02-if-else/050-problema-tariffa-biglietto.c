/*
 * 050-problema-tariffa-biglietto.c
 *
 * Calcolo del prezzo di un biglietto per un museo civico
 *
 * Tariffe:
 *   - bambini sotto i 6 anni         gratis
 *   - ragazzi da 6 a 17 anni         6,00 euro
 *   - studenti universitari 18-26    7,00 euro (con tessera universitaria)
 *   - adulti dai 65 anni in su       8,00 euro
 *   - tutti gli altri                12,00 euro
 *
 * Il martedì ogni biglietto a pagamento ha 2,00 euro di sconto.
 *
 * Il prezzo viene scelto con una catena else-if: l'ordine dei controlli
 * è importante perché le fasce d'età non devono sovrapporsi. Lo sconto
 * del martedì è un if separato, perché si somma alla tariffa già scelta.
 * Gli importi sono in centesimi per lavorare con numeri interi esatti.
 */

#include <stdio.h>

#define GRATIS            0
#define PREZZO_RAGAZZI    600
#define PREZZO_STUDENTI   700
#define PREZZO_SENIOR     800
#define PREZZO_INTERO    1200
#define SCONTO_MARTEDI    200

#define MARTEDI 2

int main(void)
{
    int eta;
    int studente;
    int giorno;
    int prezzo;
    int dati_validi;

    printf("=== MUSEO CIVICO - BIGLIETTERIA ===\n\n");
    printf("Eta' del visitatore: ");
    scanf("%d", &eta);
    printf("Tessera universitaria (1 = si', 0 = no): ");
    scanf("%d", &studente);
    printf("Giorno della visita (1 = lunedi' ... 7 = domenica): ");
    scanf("%d", &giorno);

    dati_validi = (eta >= 0 && eta <= 120)
               && (studente == 0 || studente == 1)
               && (giorno >= 1 && giorno <= 7);

    if (!dati_validi) {
        printf("\nDati non validi: impossibile calcolare il prezzo.\n");
    } else {
        /* ── Scelta della tariffa ─────────────────────────────────────
         * La tariffa studenti richiede DUE condizioni: età nella fascia
         * e tessera. Se una manca si prosegue con i controlli successivi
         * e il visitatore paga la tariffa per la sua età.                */
        if (eta < 6) {
            prezzo = GRATIS;
            printf("\nTariffa: bambini (gratis)\n");
        } else if (eta <= 17) {
            prezzo = PREZZO_RAGAZZI;
            printf("\nTariffa: ragazzi\n");
        } else if (eta <= 26 && studente) {
            prezzo = PREZZO_STUDENTI;
            printf("\nTariffa: studenti universitari\n");
        } else if (eta >= 65) {
            prezzo = PREZZO_SENIOR;
            printf("\nTariffa: over 65\n");
        } else {
            prezzo = PREZZO_INTERO;
            printf("\nTariffa: intero\n");
        }

        /* ── Sconto del martedì ───────────────────────────────────────
         * Un if separato (non un altro else-if): lo sconto non è una
         * tariffa alternativa ma si applica in aggiunta. Il controllo
         * prezzo > 0 evita un prezzo negativo per i biglietti gratuiti. */
        if (giorno == MARTEDI && prezzo > 0) {
            prezzo = prezzo - SCONTO_MARTEDI;
            printf("Sconto del martedi': -%d,%02d euro\n",
                   SCONTO_MARTEDI / 100, SCONTO_MARTEDI % 100);
        }

        printf("Prezzo da pagare: %d,%02d euro\n", prezzo / 100, prezzo % 100);
    }

    /*
     * ERRORE COMUNE: catena con l'ordine sbagliato.
     *
     *     if (eta <= 17)        { ragazzi }
     *     else if (eta < 6)     { gratis }    // mai raggiunto
     *
     * Un bambino di 4 anni soddisfa già eta <= 17 e pagherebbe 6 euro.
     */

    return 0;
}
