/*
 * 010-break-e-continue.c
 *
 * Che cosa fanno break e continue nei cicli
 *
 *   break     termina SUBITO il ciclo più interno che lo contiene;
 *             l'esecuzione riprende dopo la graffa chiusa del ciclo.
 *   continue  salta il resto del corpo e passa SUBITO all'iterazione
 *             successiva (nel for esegue prima l'aggiornamento).
 *
 * ┌──────────────────────────────────────────────────────────────────────┐
 * │ ATTENZIONE: questo è l'UNICO file del corso in cui break (fuori da    │
 * │ uno switch) e continue compaiono nel codice eseguibile. Servono solo  │
 * │ a mostrare come funzionano. Gli usi sono segnalati con "DA NON        │
 * │ IMITARE": nei file successivi si vede come farne a meno.              │
 * └──────────────────────────────────────────────────────────────────────┘
 *
 * Perché il corso li evita?
 * Un ciclo dovrebbe dichiarare nella sua intestazione QUANDO termina.
 * break e continue introducono punti di uscita o di salto nascosti nel
 * corpo: per sapere come si comporta il ciclo bisogna leggerlo tutto,
 * riga per riga. Questo rende il codice meno leggibile, più difficile da
 * verificare e più facile da rompere quando lo si modifica.
 */

#include <stdio.h>

int main(void)
{
    int i;
    int riga;
    int colonna;
    int somma;

    /* ── 1. break: ricerca del primo multiplo di 7 maggiore di 50 ───── */
    printf("=== break ===\n");
    for (i = 51; i <= 100; i++) {
        if (i % 7 == 0) {
            printf("Primo multiplo di 7 dopo 50: %d\n", i);
            break;                              /* DA NON IMITARE */
        }
    }
    /* L'intestazione dice "da 51 a 100", ma il ciclo si ferma a 56:
     * l'informazione vera è nascosta dentro il corpo. */
    printf("Il ciclo si e' fermato con i = %d (non a 101)\n\n", i);

    /* ── 2. continue: somma dei soli numeri dispari da 1 a 10 ───────── */
    printf("=== continue ===\n");
    somma = 0;
    for (i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;                           /* DA NON IMITARE */
        }
        printf("sommo %d\n", i);
        somma = somma + i;
    }
    printf("Somma dei dispari: %d\n\n", somma);

    /* ── 3. break in cicli annidati: esce solo dal ciclo INTERNO ──────
     * Un errore frequente è credere che break interrompa entrambi i
     * cicli: qui il ciclo esterno continua per tutte e tre le righe.   */
    printf("=== break in cicli annidati ===\n");
    for (riga = 1; riga <= 3; riga++) {
        for (colonna = 1; colonna <= 5; colonna++) {
            if (colonna == 3) {
                break;                          /* DA NON IMITARE */
            }
            printf("(%d,%d) ", riga, colonna);
        }
        printf("<- fine riga %d\n", riga);
    }

    /*
     * break NELLO switch è un'altra cosa: è parte della sintassi dello
     * switch, chiude il case corrente ed è ammesso dalle convenzioni
     * (vedi 03-switch). Attenzione però: un break dentro uno switch che si
     * trova in un ciclo chiude lo switch, NON il ciclo.
     */

    return 0;
}
