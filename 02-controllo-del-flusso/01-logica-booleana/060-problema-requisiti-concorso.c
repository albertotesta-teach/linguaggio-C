/*
 * 060-problema-requisiti-concorso.c
 *
 * Verifica dei requisiti di ammissione a un concorso pubblico
 *
 * Il bando di un concorso comunale prevede questi requisiti:
 *
 *   1. età compresa tra 18 e 35 anni (estremi inclusi);
 *   2. titolo di studio almeno pari al diploma;
 *   3. superamento della prova preselettiva: punteggio di almeno 60/100,
 *      oppure almeno 50/100 per chi possiede la laurea.
 *
 * Il candidato è ammesso solo se soddisfa TUTTI i requisiti.
 * Il programma calcola ogni requisito come variabile booleana, stampa
 * un riepilogo requisito per requisito e infine l'esito.
 * I dati inseriti vengono controllati: se non sono validi l'esito è
 * "dati non validi" invece di "ammesso" o "non ammesso".
 */

#include <stdio.h>

#define ETA_MIN           18
#define ETA_MAX           35
#define PUNTEGGIO_MIN     60
#define PUNTEGGIO_MIN_LAU 50

/* Codici del titolo di studio */
#define NESSUN_TITOLO 0
#define DIPLOMA       1
#define LAUREA        2

int main(void)
{
    int eta;
    int titolo;
    int punteggio;

    int dati_validi;
    int requisito_eta;
    int requisito_titolo;
    int requisito_prova;
    int ammesso;

    printf("=== CONCORSO COMUNALE - VERIFICA REQUISITI ===\n\n");
    printf("Eta' del candidato: ");
    scanf("%d", &eta);
    printf("Titolo di studio (0 = nessuno, 1 = diploma, 2 = laurea): ");
    scanf("%d", &titolo);
    printf("Punteggio della prova preselettiva (0-100): ");
    scanf("%d", &punteggio);

    /* ── Controllo dei dati ─────────────────────────────────────────
     * Il titolo deve essere uno dei tre codici previsti e il punteggio
     * deve stare nell'intervallo [0, 100]: due condizioni "dentro un
     * intervallo" unite da AND.                                         */
    dati_validi = (titolo >= NESSUN_TITOLO && titolo <= LAUREA)
               && (punteggio >= 0 && punteggio <= 100)
               && (eta > 0);

    /* ── Requisiti ───────────────────────────────────────────────── */
    requisito_eta    = (eta >= ETA_MIN && eta <= ETA_MAX);
    requisito_titolo = (titolo >= DIPLOMA);

    /* Due modi alternativi di superare la prova: OR tra due blocchi.
     * Il secondo blocco vale solo per i laureati: AND interno.        */
    requisito_prova  = (punteggio >= PUNTEGGIO_MIN)
                    || (titolo == LAUREA && punteggio >= PUNTEGGIO_MIN_LAU);

    /* Ammesso: tutti i requisiti veri (AND) e dati corretti */
    ammesso = dati_validi && requisito_eta && requisito_titolo && requisito_prova;

    /* ── Riepilogo ───────────────────────────────────────────────── */
    printf("\n--- Riepilogo ---\n");
    printf("  Dati inseriti validi           : %s\n", dati_validi      ? "SI'" : "NO");
    printf("  Eta' tra %d e %d anni          : %s\n", ETA_MIN, ETA_MAX,
           requisito_eta    ? "SI'" : "NO");
    printf("  Almeno il diploma              : %s\n", requisito_titolo ? "SI'" : "NO");
    printf("  Prova preselettiva superata    : %s\n", requisito_prova  ? "SI'" : "NO");

    /* Esito su tre valori con due ternari annidati:
     * prima si guarda se i dati sono validi, poi se il candidato è ammesso. */
    printf("\nEsito: %s\n",
           !dati_validi ? "DATI NON VALIDI"
                        : (ammesso ? "AMMESSO" : "NON AMMESSO"));

    /*
     * ERRORE COMUNE: dimenticare le parentesi nel requisito della prova.
     *   punteggio >= 60 || titolo == LAUREA && punteggio >= 50
     * Per la precedenza il risultato sarebbe lo stesso (&& lega più di ||),
     * ma gcc -Wall segnala il dubbio e chi legge deve fermarsi a ragionare:
     * le parentesi rendono evidenti i due modi di superare la prova.
     */

    return 0;
}
