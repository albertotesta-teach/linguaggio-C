/*
 * 050-problema-durata-allenamento.c
 *
 * Cronometro di un allenamento in pista
 *
 * Durante un allenamento di corsa l'allenatore inserisce il tempo di ogni
 * giro nel formato minuti:secondi. Il programma accumula la durata totale
 * in ore, minuti e secondi, tiene il giro più veloce e alla fine stampa il
 * riepilogo.
 *
 * Le tre variabili della durata totale sono parametri di INGRESSO E USCITA:
 *   aggiungi_giro(&ore, &minuti, &secondi, m, s)   somma un giro
 *   normalizza(&ore, &minuti, &secondi)            porta i secondi e i
 *                                                  minuti oltre 59 nell'unità
 *                                                  superiore (riporto)
 * Anche il giro migliore è in ingresso e uscita: aggiorna_migliore lo
 * cambia solo se il nuovo giro è più veloce, e restituisce 1 in quel caso.
 *
 * Il programma legge un giro per riga; 0:00 termina.
 */

#include <stdio.h>

void aggiungi_giro(int *ore, int *minuti, int *secondi, int m, int s);
void normalizza(int *ore, int *minuti, int *secondi);
int aggiorna_migliore(int *migliore, int m, int s);
void svuota_riga(void);

int main(void)
{
    int ore = 0;
    int minuti = 0;
    int secondi = 0;
    int migliore = -1;                  /* in secondi, -1 = nessun giro */
    int giri = 0;
    int m = 1;
    int s = 0;
    int letti;

    printf("=== ALLENAMENTO IN PISTA ===\n");
    while (m != 0 || s != 0) {
        printf("Tempo del giro %d (mm:ss, 0:00 per finire): ", giri + 1);
        letti = scanf("%d:%d", &m, &s);
        if (letti == EOF) {
            m = 0;                      /* input terminato: come 0:00 */
            s = 0;
        } else if (letti != 2) {
            svuota_riga();              /* non è un tempo mm:ss */
            m = -1;                     /* tempo non valido */
        }
        if (m < 0 || s < 0 || s > 59) {
            printf("  Tempo non valido.\n");
        } else if (m != 0 || s != 0) {
            giri++;
            aggiungi_giro(&ore, &minuti, &secondi, m, s);
            printf("  totale %d:%02d:%02d", ore, minuti, secondi);
            if (aggiorna_migliore(&migliore, m, s)) {
                printf("   nuovo giro migliore");
            }
            printf("\n");
        }
    }

    if (giri > 0) {
        printf("\n%d giri in %d:%02d:%02d, giro migliore %d:%02d\n",
               giri, ore, minuti, secondi, migliore / 60, migliore % 60);
    }

    return 0;
}

/* Aggiunge un giro di m minuti e s secondi alla durata totale. */
void aggiungi_giro(int *ore, int *minuti, int *secondi, int m, int s)
{
    *minuti = *minuti + m;
    *secondi = *secondi + s;
    normalizza(ore, minuti, secondi);
}

/* Riporta secondi e minuti oltre 59 nell'unità superiore. */
void normalizza(int *ore, int *minuti, int *secondi)
{
    *minuti = *minuti + *secondi / 60;
    *secondi = *secondi % 60;
    *ore = *ore + *minuti / 60;
    *minuti = *minuti % 60;
}

/* Se il giro è più veloce di *migliore (o è il primo), lo memorizza e
 * restituisce 1; altrimenti restituisce 0. */
int aggiorna_migliore(int *migliore, int m, int s)
{
    int tempo = m * 60 + s;
    int aggiornato = 0;

    if (*migliore == -1 || tempo < *migliore) {
        *migliore = tempo;
        aggiornato = 1;
    }
    return aggiornato;
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
