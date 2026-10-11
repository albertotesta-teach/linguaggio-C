/*
 * 070-problema-orario-apertura.c
 *
 * Il negozio è aperto in questo momento?
 *
 * Una ferramenta ha questi orari:
 *
 *   da lunedì a venerdì   09:00 - 12:30   e   15:30 - 19:30
 *   sabato                09:00 - 13:00
 *   domenica              chiuso
 *
 * Dati il giorno della settimana e l'orario, il programma stabilisce se il
 * negozio è aperto. L'orario viene convertito in minuti dalla mezzanotte
 * (es. 15:30 -> 15 * 60 + 30 = 930), così ogni fascia diventa un
 * intervallo di numeri interi facile da confrontare.
 *
 * Ogni fascia è un intervallo "chiuso a sinistra, aperto a destra":
 * alle 12:30 esatte il negozio è già chiuso.
 */

#include <stdio.h>

/* Orari espressi in minuti dalla mezzanotte */
#define MATTINA_INIZIO     (9 * 60)        /* 09:00 */
#define MATTINA_FINE       (12 * 60 + 30)  /* 12:30 */
#define POMERIGGIO_INIZIO  (15 * 60 + 30)  /* 15:30 */
#define POMERIGGIO_FINE    (19 * 60 + 30)  /* 19:30 */
#define SABATO_FINE        (13 * 60)       /* 13:00 */

#define SABATO   6
#define DOMENICA 7

int main(void)
{
    int giorno;
    int ore;
    int minuti;
    int istante;          /* orario in minuti dalla mezzanotte */

    int dati_validi;
    int feriale;
    int sabato;
    int in_mattina;
    int in_pomeriggio;
    int in_mattina_sabato;
    int aperto;

    printf("=== FERRAMENTA - ORARIO DI APERTURA ===\n\n");
    printf("Giorno (1 = lunedi' ... 7 = domenica): ");
    scanf("%d", &giorno);
    printf("Ora (formato HH MM, es. 15 45): ");
    scanf("%d %d", &ore, &minuti);

    /* ── Controllo dei dati ─────────────────────────────────────────── */
    dati_validi = (giorno >= 1 && giorno <= DOMENICA)
               && (ore >= 0 && ore <= 23)
               && (minuti >= 0 && minuti <= 59);

    istante = ore * 60 + minuti;

    /* ── Condizioni elementari ─────────────────────────────────────── */
    feriale = (giorno >= 1 && giorno <= 5);
    sabato  = (giorno == SABATO);

    in_mattina        = (istante >= MATTINA_INIZIO    && istante < MATTINA_FINE);
    in_pomeriggio     = (istante >= POMERIGGIO_INIZIO && istante < POMERIGGIO_FINE);
    in_mattina_sabato = (istante >= MATTINA_INIZIO    && istante < SABATO_FINE);

    /* ── Regola completa ───────────────────────────────────────────────
     * aperto se:
     *   (feriale  E  (mattina OPPURE pomeriggio))
     *   OPPURE
     *   (sabato   E  mattina del sabato)
     * La domenica non compare: nessuno dei due blocchi può essere vero.  */
    aperto = dati_validi
          && ((feriale && (in_mattina || in_pomeriggio))
              || (sabato && in_mattina_sabato));

    /* ── Risultato ─────────────────────────────────────────────────── */
    printf("\n--- Verifica ---\n");
    printf("  Dati validi             : %d\n", dati_validi);
    printf("  Giorno feriale          : %d\n", feriale);
    printf("  Sabato                  : %d\n", sabato);
    printf("  Fascia 09:00-12:30      : %d\n", in_mattina);
    printf("  Fascia 15:30-19:30      : %d\n", in_pomeriggio);
    printf("  Fascia sabato 09-13     : %d\n", in_mattina_sabato);

    printf("\nAlle %02d:%02d del giorno %d il negozio e' %s.\n",
           ore, minuti, giorno,
           !dati_validi ? "(dati non validi)"
                        : (aperto ? "APERTO" : "CHIUSO"));

    /*
     * ERRORE COMUNE: dimenticare il controllo del giorno su una fascia.
     *   aperto = in_mattina || in_pomeriggio || in_mattina_sabato;
     * Così il negozio risulterebbe aperto anche la domenica mattina e il
     * sabato pomeriggio: ogni fascia vale solo per i giorni previsti.
     */

    return 0;
}
