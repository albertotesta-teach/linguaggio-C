/*
 * 060-problema-menu-ristorante.c
 *
 * Prendere un'ordinazione dal menu di una trattoria
 *
 * Il menu è formato da tre array paralleli: nome del piatto, categoria e
 * prezzo in centesimi. Il programma:
 *   1. stampa il menu raggruppato per categoria (per ogni categoria di
 *      categorie[] si stampano i piatti che hanno quella categoria, con
 *      strcmp);
 *   2. riceve l'ordinazione: il cameriere scrive il nome di un piatto per
 *      riga, senza badare alle maiuscole, e "conto" per chiudere;
 *   3. conta le porzioni di ogni piatto in un quarto array parallelo e
 *      stampa il conto con il coperto.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define PIATTI     8
#define CATEGORIE  4
#define LUNG       26
#define DIM        40
#define COPERTO    250                  /* centesimi a persona */

int leggi_riga(char s[], int dim);
int uguali_senza_maiuscole(const char a[], const char b[]);
int cerca_piatto(const char menu[][LUNG], int n, const char nome[]);

int main(void)
{
    char piatti[PIATTI][LUNG] = {
        "Agnolotti al sugo", "Risotto ai funghi", "Brasato al Barolo",
        "Tagliata di manzo", "Bonet", "Panna cotta",
        "Insalata mista", "Patate al forno"
    };
    char categoria[PIATTI][LUNG] = {
        "Primi", "Primi", "Secondi", "Secondi", "Dolci", "Dolci",
        "Contorni", "Contorni"
    };
    int prezzi[PIATTI] = {1100, 1200, 1600, 1800, 550, 500, 450, 450};
    char categorie[CATEGORIE][LUNG] = {"Primi", "Secondi", "Contorni", "Dolci"};
    int porzioni[PIATTI] = {0};
    char riga[DIM];
    int c;
    int k;
    int coperti = 2;
    int totale;

    /* ── 1. Menu per categoria ────────────────────────────────────── */
    printf("=== TRATTORIA DEL BORGO ===\n");
    for (c = 0; c < CATEGORIE; c++) {
        printf("%s\n", categorie[c]);
        for (k = 0; k < PIATTI; k++) {
            if (strcmp(categoria[k], categorie[c]) == 0) {
                printf("  %-20s %3d.%02d\n", piatti[k], prezzi[k] / 100, prezzi[k] % 100);
            }
        }
    }

    /* ── 2. Ordinazione ───────────────────────────────────────────── */
    printf("\nTavolo da %d. Piatti ordinati (\"conto\" per chiudere):\n", coperti);
    printf("> ");
    if (!leggi_riga(riga, DIM)) {
        strcpy(riga, "conto");
    }
    while (!uguali_senza_maiuscole(riga, "conto")) {
        k = cerca_piatto(piatti, PIATTI, riga);
        if (k == -1) {
            printf("  \"%s\" non e' nel menu.\n", riga);
        } else {
            porzioni[k]++;
            printf("  + %s\n", piatti[k]);
        }
        printf("> ");
        if (!leggi_riga(riga, DIM)) {
            strcpy(riga, "conto");
        }
    }

    /* ── 3. Conto ─────────────────────────────────────────────────── */
    printf("\n=== CONTO ===\n");
    totale = coperti * COPERTO;
    for (k = 0; k < PIATTI; k++) {
        if (porzioni[k] > 0) {
            printf("  %d x %-20s %3d.%02d\n", porzioni[k], piatti[k],
                   porzioni[k] * prezzi[k] / 100, porzioni[k] * prezzi[k] % 100);
            totale = totale + porzioni[k] * prezzi[k];
        }
    }
    printf("  %d x %-20s %3d.%02d\n", coperti, "Coperto",
           coperti * COPERTO / 100, coperti * COPERTO % 100);
    printf("  %-24s %3d.%02d\n", "TOTALE", totale / 100, totale % 100);

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
    }
    return ok;
}

int uguali_senza_maiuscole(const char a[], const char b[])
{
    int i = 0;

    while (a[i] != '\0' && tolower((unsigned char) a[i]) == tolower((unsigned char) b[i])) {
        i++;
    }
    return tolower((unsigned char) a[i]) == tolower((unsigned char) b[i]);
}

int cerca_piatto(const char menu[][LUNG], int n, const char nome[])
{
    int k = 0;
    int trovato = -1;

    while (k < n && trovato == -1) {
        if (uguali_senza_maiuscole(menu[k], nome)) {
            trovato = k;
        }
        k++;
    }
    return trovato;
}
