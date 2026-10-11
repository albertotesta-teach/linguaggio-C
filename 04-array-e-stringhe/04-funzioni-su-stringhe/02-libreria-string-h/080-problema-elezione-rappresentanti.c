/*
 * 080-problema-elezione-rappresentanti.c
 *
 * Spoglio delle schede per i rappresentanti di classe
 *
 * Nella classe si votano i rappresentanti: ogni studente scrive sulla
 * scheda il cognome e il nome di un candidato. Le schede sono state
 * trascritte in un array di stringhe:
 *   - una scheda vuota ("") è BIANCA;
 *   - una scheda il cui testo coincide esattamente (strcmp) con un
 *     candidato è VALIDA e il voto va a quel candidato;
 *   - ogni altro testo (nome sbagliato, persona non candidata) è NULLA.
 *
 * I candidati e i loro voti sono due array paralleli. Il programma stampa
 * lo spoglio, i risultati con le percentuali sui voti validi e gli eletti:
 * i primi due, con la segnalazione di un eventuale pareggio per il
 * secondo posto (che si risolve con un ballottaggio).
 */

#include <stdio.h>
#include <string.h>

#define CANDIDATI 4
#define SCHEDE    20
#define LUNG      24

int cerca_candidato(const char scheda[], const char candidati[][LUNG], int n);

int main(void)
{
    char candidati[CANDIDATI][LUNG] = {
        "Bianchi Luca", "Neri Giulia", "Russo Marco", "Gallo Sara"
    };
    char schede[SCHEDE][LUNG] = {
        "Neri Giulia", "Russo Marco", "Neri Giulia", "", "Bianchi Luca",
        "Gallo Sara", "Neri Giulia", "neri giulia", "Russo Marco", "Gallo Sara",
        "Bianchi Luca", "Neri Giulia", "", "Russo Marco", "Gallo Sara",
        "Verdi Paolo", "Neri Giulia", "Russo Marco", "Gallo Sara", "Neri Giula"
    };
    int voti[CANDIDATI] = {0};
    int k;
    int c;
    int bianche = 0;
    int nulle = 0;
    int valide = 0;
    int primo = 0;
    int secondo = -1;
    int pari_merito;

    /* ── 1. Spoglio ───────────────────────────────────────────────── */
    printf("=== SPOGLIO ===\n");
    for (k = 0; k < SCHEDE; k++) {
        if (strlen(schede[k]) == 0) {
            bianche++;
        } else {
            c = cerca_candidato(schede[k], candidati, CANDIDATI);
            if (c == -1) {
                nulle++;
                printf("  scheda %2d nulla: \"%s\"\n", k + 1, schede[k]);
            } else {
                voti[c]++;
                valide++;
            }
        }
    }
    printf("Schede: %d  valide: %d  bianche: %d  nulle: %d\n\n",
           SCHEDE, valide, bianche, nulle);

    /* ── 2. Risultati ─────────────────────────────────────────────── */
    printf("=== RISULTATI ===\n");
    for (c = 0; c < CANDIDATI; c++) {
        printf("  %-14s %2d voti  %5.1f%%\n", candidati[c], voti[c],
               valide > 0 ? 100.0 * voti[c] / valide : 0.0);
    }

    /* ── 3. Primo e secondo classificato ──────────────────────────── */
    for (c = 1; c < CANDIDATI; c++) {
        if (voti[c] > voti[primo]) {
            primo = c;
        }
    }
    for (c = 0; c < CANDIDATI; c++) {
        if (c != primo && (secondo == -1 || voti[c] > voti[secondo])) {
            secondo = c;
        }
    }

    printf("\nEletto: %s\n", candidati[primo]);
    pari_merito = 0;
    printf("Secondo posto con %d voti:", voti[secondo]);
    for (c = 0; c < CANDIDATI; c++) {
        if (c != primo && voti[c] == voti[secondo]) {
            if (pari_merito > 0) {
                printf(",");
            }
            printf(" %s", candidati[c]);
            pari_merito++;
        }
    }
    printf("\n");
    if (pari_merito > 1) {
        printf("Pareggio: serve un ballottaggio per il secondo rappresentante.\n");
    } else {
        printf("Eletto: %s\n", candidati[secondo]);
    }

    return 0;
}

/* Restituisce l'indice del candidato scritto sulla scheda, oppure -1. */
int cerca_candidato(const char scheda[], const char candidati[][LUNG], int n)
{
    int c = 0;
    int trovato = -1;

    while (c < n && trovato == -1) {
        if (strcmp(scheda, candidati[c]) == 0) {
            trovato = c;
        }
        c++;
    }
    return trovato;
}
