/*
 * 040-dal-testo-alla-condizione.c
 *
 * Tradurre una regola scritta in italiano in una condizione C
 *
 * Le specifiche di un problema sono scritte in linguaggio naturale:
 * "possono iscriversi i maggiorenni con meno di 65 anni".
 * Il programmatore deve trasformarle in un'espressione logica.
 * Un metodo in tre passi:
 *
 *   1. individuare le CONDIZIONI ELEMENTARI (un solo confronto ciascuna)
 *   2. riconoscere i CONNETTIVI della frase e tradurli:
 *        "e", "ma", "e anche"            ->  &&
 *        "o", "oppure"                   ->  ||
 *        "non", "tranne"                 ->  !
 *        "o... o..." (uno solo dei due)  ->  XOR, cioè  a != b  su 0/1
 *   3. aggiungere le PARENTESI per rendere esplicito come si raggruppano
 *
 * Ogni condizione viene salvata in una variabile booleana con un nome
 * descrittivo: è più leggibile e la si può riusare.
 */

#include <stdio.h>

int main(void)
{
    /* Dati di esempio (si possono cambiare per verificare le condizioni) */
    int eta = 17;
    int giorno = 7;          /* 1 = lunedì ... 7 = domenica */
    int ora = 21;
    int voto_scritto = 7;
    int voto_orale = 5;
    int carta_fedelta = 1;
    int importo = 40;
    int pagato_con_carta = 1;
    int pagato_in_contanti = 0;

    int maggiorenne_sotto_65;
    int festivo_o_sera;
    int promosso;
    int sconto;
    int pagamento_valido;

    /* ── Frase 1 ──────────────────────────────────────────────────────
     * "maggiorenne ma con meno di 65 anni"
     *   condizioni elementari:  eta >= 18     eta < 65
     *   connettivo "ma"      ->  &&
     */
    maggiorenne_sotto_65 = (eta >= 18) && (eta < 65);

    /* ── Frase 2 ──────────────────────────────────────────────────────
     * "giorno festivo oppure dopo le 20"
     *   festivo: giorno == 7  (consideriamo festiva solo la domenica)
     *   dopo le 20: ora >= 20
     *   connettivo "oppure"  ->  ||
     */
    festivo_o_sera = (giorno == 7) || (ora >= 20);

    /* ── Frase 3 ──────────────────────────────────────────────────────
     * "è promosso chi ha almeno 6 in entrambe le prove,
     *  oppure ha almeno 8 nello scritto e non meno di 5 all'orale"
     *   due blocchi uniti da "oppure", ciascuno formato da due
     *   condizioni unite da "e": le parentesi rendono chiari i blocchi
     */
    promosso = (voto_scritto >= 6 && voto_orale >= 6)
            || (voto_scritto >= 8 && voto_orale >= 5);

    /* ── Frase 4 ──────────────────────────────────────────────────────
     * "sconto per chi ha la carta fedeltà, tranne che per spese
     *  inferiori a 20 euro"
     *   "tranne" introduce una negazione: NON (importo < 20)
     *   equivale a importo >= 20
     */
    sconto = carta_fedelta && !(importo < 20);

    /* ── Frase 5 ──────────────────────────────────────────────────────
     * "si paga o con carta o in contanti" (uno solo dei due metodi)
     *   è un o esclusivo: vero se esattamente uno dei due è vero
     *   su valori 0/1 si scrive  a != b
     */
    pagamento_valido = (pagato_con_carta != pagato_in_contanti);

    /* ── Stampa dei risultati ─────────────────────────────────────── */
    printf("=== Dati ===\n");
    printf("eta = %d, giorno = %d, ora = %d\n", eta, giorno, ora);
    printf("scritto = %d, orale = %d\n", voto_scritto, voto_orale);
    printf("carta fedelta' = %d, importo = %d euro\n", carta_fedelta, importo);
    printf("carta = %d, contanti = %d\n", pagato_con_carta, pagato_in_contanti);
    printf("\n");

    printf("=== Condizioni ===\n");
    printf("Maggiorenne con meno di 65 anni:  %d\n", maggiorenne_sotto_65);
    printf("Giorno festivo oppure sera:       %d\n", festivo_o_sera);
    printf("Promosso:                         %d\n", promosso);
    printf("Diritto allo sconto:              %d\n", sconto);
    printf("Un solo metodo di pagamento:      %d\n", pagamento_valido);

    /*
     * ERRORI COMUNI NELLA TRADUZIONE
     *
     * 1) Scrivere un intervallo come in matematica:
     *        18 <= eta < 65            // ERRATO
     *    Il C calcola prima (18 <= eta), che vale 0 o 1, e poi confronta
     *    quel valore con 65: il risultato è SEMPRE 1.
     *    Corretto:  eta >= 18 && eta < 65
     *
     * 2) Sottintendere la variabile nel secondo confronto:
     *        giorno == 6 || 7          // ERRATO
     *    "7" da solo è un valore diverso da 0, quindi sempre vero.
     *    Corretto:  giorno == 6 || giorno == 7
     *
     * 3) Tradurre "e" con && quando la frase indica un elenco di casi
     *    alternativi: "sconto il sabato e la domenica"
     *        giorno == 6 && giorno == 7    // ERRATO: mai vero
     *    Un giorno non può essere sabato e domenica insieme: qui "e"
     *    significa "in entrambi i casi", cioè ||.
     *    Corretto:  giorno == 6 || giorno == 7
     */

    return 0;
}
