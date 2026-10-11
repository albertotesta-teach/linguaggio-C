/*
 * 010-elenco-di-parole.c
 *
 * Un elenco di parole come matrice di caratteri
 *
 * Un elenco di N parole, ciascuna di al massimo LUNG - 1 caratteri, si
 * memorizza in una matrice di char:
 *
 *     char elenco[N][LUNG];
 *
 *   elenco[k]      è la riga k: una stringa a tutti gli effetti, che si
 *                  passa a printf, strlen, strcpy, strcmp, fgets...
 *   elenco[k][i]   è il carattere i della parola k
 *
 * Ogni riga occupa sempre LUNG celle, anche se la parola è corta: lo
 * spazio che avanza dopo il '\0' resta inutilizzato.
 *
 * Il programma inizializza un elenco di materie, ne legge un secondo da
 * tastiera (le città di provenienza degli studenti di un gruppo) e mostra
 * lunghezze e occupazione della memoria.
 */

#include <stdio.h>
#include <string.h>

#define MATERIE  5
#define STUDENTI 4
#define LUNG     16

int leggi_riga(char s[], int dim);

int main(void)
{
    char materie[MATERIE][LUNG] = {
        "Italiano", "Matematica", "Informatica", "Inglese", "Storia"
    };
    char citta[STUDENTI][LUNG];
    int k;
    int occupati = 0;

    /* ── 1. Elenco inizializzato ──────────────────────────────────── */
    printf("=== MATERIE ===\n");
    for (k = 0; k < MATERIE; k++) {
        printf("  %d. %-12s %2d caratteri, iniziale '%c'\n", k + 1, materie[k],
               (int) strlen(materie[k]), materie[k][0]);
        occupati = occupati + (int) strlen(materie[k]) + 1;
    }
    printf("Memoria: %d celle riservate (%d x %d), %d usate dalle parole\n\n",
           (int) sizeof(materie), MATERIE, LUNG, occupati);

    /* ── 2. Elenco letto da tastiera ──────────────────────────────── */
    printf("=== CITTA' DI PROVENIENZA ===\n");
    for (k = 0; k < STUDENTI; k++) {
        printf("Citta' dello studente %d: ", k + 1);
        leggi_riga(citta[k], LUNG);
    }

    printf("\nElenco inserito:\n");
    for (k = 0; k < STUDENTI; k++) {
        printf("  [%s]\n", citta[k]);
    }
    printf("Le parentesi mostrano che fgets ha letto anche gli spazi,\n");
    printf("e che il testo oltre i %d caratteri e' stato scartato.\n", LUNG - 1);

    return 0;
}

int leggi_riga(char s[], int dim)
{
    int ok = 0;
    int n;
    int c;

    if (fgets(s, dim, stdin) != NULL) {
        ok = 1;
        n = (int) strlen(s);
        if (n > 0 && s[n - 1] == '\n') {
            s[n - 1] = '\0';
        } else {
            c = getchar();
            while (c != '\n' && c != EOF) {
                c = getchar();
            }
        }
    } else {
        s[0] = '\0';
    }
    return ok;
}
