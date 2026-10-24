/*
 * 040-problema-voti-della-verifica.c
 *
 * I voti di una verifica, per una classe di qualsiasi numero di studenti
 *
 * Il professore inserisce quanti studenti hanno svolto la verifica e poi
 * i voti, da 1 a 10 con i mezzi voti. Il programma alloca un array di
 * esattamente n voti, poi calcola:
 *   - la media della classe;
 *   - quanti voti sono sopra la media;
 *   - l'elenco delle insufficienze (voti sotto 6), con il numero dello
 *     studente;
 *   - il voto più alto e il più basso.
 *
 * Per sapere quanti voti sono sopra la media servono due passate: la
 * prima calcola la media, la seconda confronta ogni voto con la media.
 * Per questo i voti vanno conservati, e senza malloc servirebbe un
 * array con un massimo fissato.
 *
 * Un voto non valido (fuori da 1-10, non multiplo di 0.5 o non numerico)
 * viene richiesto di nuovo.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTI 40

int leggi_voto(int studente, double *voto);
void svuota_riga(void);

int main(void)
{
    double *voti;
    int n;
    int i;
    int letti = 0;
    int sopra = 0;
    int insufficienti = 0;
    double somma = 0;
    double media;
    double massimo;
    double minimo;

    printf("Studenti presenti alla verifica (da 1 a %d): ", MAX_STUDENTI);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_STUDENTI) {
        printf("Numero non valido.\n");
    } else {
        voti = malloc(n * sizeof *voti);
        if (voti == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            while (letti < n && leggi_voto(letti + 1, &voti[letti])) {
                somma = somma + voti[letti];
                letti++;
            }
        }
        if (voti != NULL && letti < n) {
            printf("\nInput terminato: %s %d %s.\n", n - letti == 1 ? "manca" : "mancano",
                   n - letti, n - letti == 1 ? "voto" : "voti");
        } else if (voti != NULL) {
            media = somma / n;

            massimo = voti[0];
            minimo = voti[0];
            printf("\nMedia della classe: %.2f\n", media);
            printf("Insufficienze:\n");
            for (i = 0; i < n; i++) {
                if (voti[i] > media) {
                    sopra++;
                }
                if (voti[i] < 6) {
                    printf("  studente %2d: %.1f\n", i + 1, voti[i]);
                    insufficienti++;
                }
                if (voti[i] > massimo) {
                    massimo = voti[i];
                }
                if (voti[i] < minimo) {
                    minimo = voti[i];
                }
            }
            if (insufficienti == 0) {
                printf("  nessuna\n");
            }
            printf("Sopra la media: %d su %d\n", sopra, n);
            printf("Voto piu' alto: %.1f, piu' basso: %.1f\n", massimo, minimo);
        }
        free(voti);
    }

    return 0;
}

/*
 * Chiede il voto finché non è valido: da 1 a 10, multiplo di 0.5.
 * Restituisce 0 se l'input finisce prima di un voto valido.
 */
int leggi_voto(int studente, double *voto)
{
    int letto = 0;
    int valido = 0;

    while (!valido && letto != EOF) {
        printf("Voto dello studente %d: ", studente);
        letto = scanf("%lf", voto);
        if (letto == 0) {
            svuota_riga();              /* non e' un numero */
        }
        valido = letto == 1 && *voto >= 1 && *voto <= 10 &&
                 *voto * 2 == (int) (*voto * 2);
        if (!valido && letto != EOF) {
            printf("  voto non valido (da 1 a 10, anche mezzi voti)\n");
        }
    }
    return valido;
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
