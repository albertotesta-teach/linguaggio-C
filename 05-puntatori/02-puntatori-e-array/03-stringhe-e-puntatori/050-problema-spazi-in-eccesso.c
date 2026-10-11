/*
 * 050-problema-spazi-in-eccesso.c
 *
 * Pulizia dei testi copiati in un modulo online
 *
 * Nei moduli di iscrizione di una scuola i testi arrivano spesso con spazi
 * in eccesso: all'inizio, alla fine, ripetuti tra le parole o prima della
 * punteggiatura. Prima di salvarli bisogna normalizzarli:
 *   - nessuno spazio all'inizio e alla fine;
 *   - un solo spazio tra due parole;
 *   - nessuno spazio prima di , . ; : ! ?
 *
 * La correzione avviene SUL POSTO, nello stesso array, con due puntatori:
 *   lettura    esamina tutti i caratteri, uno alla volta;
 *   scrittura  indica dove copiare il prossimo carattere da tenere.
 * scrittura non supera mai lettura, quindi non si sovrascrive nulla che
 * debba ancora essere letto. Uno spazio non si copia subito: si ricorda
 * in spazio_in_sospeso e si scrive solo se arriva un'altra parola.
 */

#include <stdio.h>
#include <string.h>

#define TESTI 4
#define LUNG  80

int normalizza(char *testo);
int punteggiatura(char c);

int main(void)
{
    char testi[TESTI][LUNG] = {
        "   Mario    Rossi   ",
        "Via Roma ,  12",
        "Allergie :  nessuna .",
        "Sport preferiti:calcio ,   nuoto , tennis"
    };
    int i;
    int tolti;

    printf("=== NORMALIZZAZIONE DEGLI SPAZI ===\n");
    for (i = 0; i < TESTI; i++) {
        printf("  prima: [%s]\n", testi[i]);
        tolti = normalizza(testi[i]);
        printf("  dopo:  [%s]   (%d caratteri tolti)\n\n", testi[i], tolti);
    }

    return 0;
}

/* Normalizza gli spazi di testo e restituisce quanti caratteri ha tolto. */
int normalizza(char *testo)
{
    const char *lettura = testo;
    char *scrittura = testo;
    int spazio_in_sospeso = 0;
    int lunghezza_iniziale = strlen(testo);

    while (*lettura != '\0') {
        if (*lettura == ' ') {
            /* uno spazio conta solo se c'è già qualcosa prima */
            if (scrittura > testo) {
                spazio_in_sospeso = 1;
            }
        } else {
            if (spazio_in_sospeso && !punteggiatura(*lettura)) {
                *scrittura = ' ';
                scrittura++;
            }
            spazio_in_sospeso = 0;
            *scrittura = *lettura;
            scrittura++;
        }
        lettura++;
    }
    *scrittura = '\0';

    return lunghezza_iniziale - (scrittura - testo);
}

/* 1 se c è un segno di punteggiatura che non vuole lo spazio prima. */
int punteggiatura(char c)
{
    return strchr(",.;:!?", c) != NULL;
}
