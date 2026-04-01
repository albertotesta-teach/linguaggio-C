/*
 * 040-costanti.c
 *
 * Costanti in C: #define e const
 *
 * Confronta le due tecniche per definire valori costanti in C:
 * - #define: sostituzione testuale eseguita dal preprocessore,
 *   senza tipo e senza occupare memoria come variabile.
 * - const: variabile tipizzata il cui valore non può essere modificato
 *   dopo l'inizializzazione (disponibile dal C89).
 * Mostra esempi pratici con costanti matematiche e limiti applicativi.
 */

#include <stdio.h>

/* ── costanti con #define ───────────────────────────────────────────────────
 * Il preprocessore sostituisce ogni occorrenza del nome con il valore
 * prima della compilazione. Non ha tipo, non occupa memoria come variabile,
 * non è visibile nel debugger. Per convenzione: MAIUSCOLO_CON_UNDERSCORE. */
#define PI_GRECO     3.14159265358979
#define GRAVITA      9.81        /* accelerazione di gravità (m/s²) */
#define ETA_MINIMA   18          /* età minima per accesso al servizio */
#define POSTI_MAX    50          /* capienza massima dell'aula */
#define IVA          0.22        /* aliquota IVA ordinaria italiana */

int main(void)
{
    /* ── costanti con const ─────────────────────────────────────────────────
     * const crea una variabile tipizzata che il compilatore protegge
     * da modifiche. È visibile nel debugger e rispetta le regole di tipo.
     * Preferita quando il tipo è importante (es. calcoli con double). */
    const double velocita_luce = 2.99792458e8;   /* m/s */
    const int    giorni_settimana = 7;
    const double euro_dollaro     = 1.08;        /* tasso di cambio indicativo */

    /* ── dimostrazione delle costanti #define ───────────────────────────── */
    printf("=== Costanti con #define ===\n");
    printf("Pi greco:      %.10f\n", PI_GRECO);
    printf("Gravita':      %.2f m/s^2\n", GRAVITA);
    printf("Eta' minima:   %d anni\n", ETA_MINIMA);
    printf("Posti massimi: %d\n", POSTI_MAX);
    printf("IVA:           %.0f%%\n", IVA * 100);

    /* ── dimostrazione delle costanti const ─────────────────────────────── */
    printf("\n=== Costanti con const ===\n");
    printf("Velocita' luce: %.5e m/s\n", velocita_luce);
    printf("Giorni/settim.: %d\n", giorni_settimana);
    printf("Euro/Dollaro:   %.4f\n", euro_dollaro);

    /* ── uso pratico delle costanti in calcoli ──────────────────────────── */
    double raggio       = 5.0;
    double area_cerchio = PI_GRECO * raggio * raggio;
    double prezzo_netto = 100.0;
    double prezzo_lordo = prezzo_netto * (1.0 + IVA);

    printf("\n=== Uso in calcoli ===\n");
    printf("Area cerchio (r=%.1f):  %.4f\n", raggio, area_cerchio);
    printf("Prezzo netto:  %.2f EUR\n", prezzo_netto);
    printf("Prezzo con IVA al 22%%: %.2f EUR\n", prezzo_lordo);

    /* ── differenza chiave (in commento) ───────────────────────────────── */
    /*
     * TENTATIVO DI MODIFICA — non compila:
     *
     *   velocita_luce = 0.0;   // ERRORE: assignment of read-only variable
     *   ETA_MINIMA    = 21;    // ERRORE: #define non è una variabile,
     *                          // ma la sostituzione avviene già a compile-time
     *
     * Quando usare #define:
     *   - costanti di configurazione usate nel preprocessore (#if, #ifdef)
     *   - valori usati come dimensioni di array (verrà visto nel cap. 04)
     *
     * Quando usare const:
     *   - quando il tipo è importante per la sicurezza dei calcoli
     *   - quando si vuole la visibilità nel debugger
     *   - nelle interfacce di funzione (verrà visto nel cap. 03)
     */

    return 0;
}
