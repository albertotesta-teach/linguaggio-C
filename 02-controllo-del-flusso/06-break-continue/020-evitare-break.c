/*
 * 020-evitare-break.c
 *
 * Come scrivere i cicli senza break
 *
 * Regola: tutte le ragioni per cui un ciclo può terminare devono comparire
 * nella sua CONDIZIONE. Quando la ragione è un evento che si verifica nel
 * corpo (un valore trovato, un errore), lo si registra in una variabile
 * booleana (flag) e la si aggiunge alla condizione.
 *
 *   CON break (da evitare)          SENZA break
 *   ----------------------          -----------------------------------
 *   while (cond) {                  fine = 0;
 *       ...                         while (cond && !fine) {
 *       if (evento) {                   ...
 *           break;                      if (evento) {
 *       }                                   fine = 1;
 *       altre istruzioni;               } else {
 *   }                                       altre istruzioni;
 *                                       }
 *                                   }
 *
 * Il programma mostra tre casi tipici. Per ognuno, la versione con break
 * è riportata nel commento, quella corretta è il codice eseguito.
 */

#include <stdio.h>

int main(void)
{
    int i;
    int trovato;
    int numero;
    int riga;
    int colonna;
    int bersaglio_trovato;
    int riga_trovata = 0;
    int colonna_trovata = 0;
    double saldo;
    double rata = 250.0;
    int mesi;

    /* ── 1. Ricerca del primo elemento che soddisfa una condizione ────
     *
     *   CON break:
     *       for (i = 51; i <= 100; i++) {
     *           if (i % 7 == 0) {
     *               break;
     *           }
     *       }
     *
     *   SENZA break: il flag "trovato" entra nella condizione del for.
     *   Attenzione: il for incrementa i anche dopo l'ultima iterazione,
     *   quindi il valore trovato va salvato in un'altra variabile.      */
    printf("=== 1. Primo multiplo di 7 dopo 50 ===\n");
    trovato = 0;
    numero = 0;
    for (i = 51; i <= 100 && !trovato; i++) {
        if (i % 7 == 0) {
            trovato = 1;
            numero = i;
        }
    }
    if (trovato) {
        printf("Trovato: %d\n\n", numero);
    } else {
        printf("Nessun multiplo di 7 nell'intervallo.\n\n");
    }

    /* ── 2. Ciclo che termina per un evento: la condizione naturale ───
     *
     *   CON break:
     *       while (1) {                   // "ciclo infinito" voluto
     *           saldo = saldo - rata;
     *           mesi++;
     *           if (saldo <= 0) {
     *               break;
     *           }
     *       }
     *
     *   SENZA break: il while (1) nasconde la vera condizione, che si
     *   può scrivere direttamente nell'intestazione.                     */
    printf("=== 2. Mesi per estinguere un debito ===\n");
    saldo = 1800.0;
    mesi = 0;
    while (saldo > 0) {
        saldo = saldo - rata;
        mesi++;
    }
    printf("Con rate da %.2f euro servono %d mesi (ultima rata parziale).\n\n",
           rata, mesi);

    /* ── 3. Uscita da due cicli annidati ──────────────────────────────
     *
     *   Con break si esce solo dal ciclo interno: per fermare anche
     *   l'esterno servirebbe un secondo controllo dopo il ciclo interno.
     *   Con il flag, lo stesso controllo compare in entrambe le
     *   condizioni e i due cicli si fermano insieme.
     *
     *   Cerchiamo la prima casella (riga, colonna) di una griglia 5 x 5
     *   in cui riga * colonna vale 12.                                   */
    printf("=== 3. Ricerca in una griglia ===\n");
    bersaglio_trovato = 0;
    for (riga = 1; riga <= 5 && !bersaglio_trovato; riga++) {
        for (colonna = 1; colonna <= 5 && !bersaglio_trovato; colonna++) {
            if (riga * colonna == 12) {
                bersaglio_trovato = 1;
                riga_trovata = riga;
                colonna_trovata = colonna;
            }
        }
    }
    if (bersaglio_trovato) {
        printf("Prima casella con prodotto 12: riga %d, colonna %d\n",
               riga_trovata, colonna_trovata);
    }

    /*
     * VANTAGGIO
     * In tutte e tre le versioni corrette, leggendo SOLO l'intestazione
     * del ciclo si sa quando termina:
     *     i <= 100 && !trovato
     *     saldo > 0
     *     riga <= 5 && !bersaglio_trovato
     */

    return 0;
}
