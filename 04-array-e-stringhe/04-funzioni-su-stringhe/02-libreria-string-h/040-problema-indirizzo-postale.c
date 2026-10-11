/*
 * 040-problema-indirizzo-postale.c
 *
 * Preparare l'etichetta per una spedizione
 *
 * Un piccolo negozio online stampa le etichette dei pacchi. L'operatore
 * inserisce destinatario, via e numero civico, CAP, comune e sigla della
 * provincia; il programma controlla i dati e compone l'etichetta:
 *
 *     +--------------------------------+
 *     | Mario Rossi                    |
 *     | Via Vittorio Emanuele II 12    |
 *     | 15121 Alessandria (AL)         |
 *     +--------------------------------+
 *
 * Controlli:
 *   - il CAP deve avere esattamente 5 cifre (strlen + controllo delle cifre);
 *   - la provincia deve avere esattamente 2 lettere;
 *   - ogni riga dell'etichetta ha al massimo LARGHEZZA caratteri: se il
 *     testo non entra viene troncato con strncat e l'operatore è avvisato.
 *
 * La terza riga si costruisce a pezzi con strcpy e la funzione aggiungi(),
 * che usa strncat calcolando lo spazio rimasto.
 */

#include <stdio.h>
#include <string.h>

#define DIM       50
#define LARGHEZZA 30

int leggi_riga(char s[], int dim);
int solo_cifre(const char s[]);
int aggiungi(char dest[], int dim, const char sorg[]);
void stampa_riga(const char s[]);

int main(void)
{
    char destinatario[DIM];
    char via[DIM];
    char cap[DIM];
    char comune[DIM];
    char provincia[DIM];
    char riga[LARGHEZZA + 1];
    int completa;
    int troncate = 0;

    printf("=== ETICHETTA DI SPEDIZIONE ===\n");
    printf("Destinatario: ");
    leggi_riga(destinatario, DIM);
    printf("Via e numero civico: ");
    leggi_riga(via, DIM);

    do {
        printf("CAP (5 cifre): ");
        leggi_riga(cap, DIM);
        if (strlen(cap) != 5 || !solo_cifre(cap)) {
            printf("  CAP non valido.\n");
        }
    } while (strlen(cap) != 5 || !solo_cifre(cap));

    printf("Comune: ");
    leggi_riga(comune, DIM);

    do {
        printf("Provincia (sigla di 2 lettere): ");
        leggi_riga(provincia, DIM);
        if (strlen(provincia) != 2) {
            printf("  Sigla non valida.\n");
        }
    } while (strlen(provincia) != 2);

    /* ── Composizione e stampa ────────────────────────────────────── */
    printf("\n+--------------------------------+\n");

    riga[0] = '\0';
    completa = aggiungi(riga, LARGHEZZA + 1, destinatario);
    troncate = troncate + !completa;
    stampa_riga(riga);

    riga[0] = '\0';
    completa = aggiungi(riga, LARGHEZZA + 1, via);
    troncate = troncate + !completa;
    stampa_riga(riga);

    strcpy(riga, cap);                  /* 5 cifre: c'è sempre spazio */
    /* aggiungi() è scritta a sinistra di &&: viene chiamata sempre,
     * anche dopo un troncamento, e completa resta 0 se un pezzo non entra */
    completa = aggiungi(riga, LARGHEZZA + 1, " ");
    completa = aggiungi(riga, LARGHEZZA + 1, comune) && completa;
    completa = aggiungi(riga, LARGHEZZA + 1, " (") && completa;
    completa = aggiungi(riga, LARGHEZZA + 1, provincia) && completa;
    completa = aggiungi(riga, LARGHEZZA + 1, ")") && completa;
    troncate = troncate + !completa;
    stampa_riga(riga);

    printf("+--------------------------------+\n");
    if (troncate > 0) {
        printf("Attenzione: %d %s troppo lunga, controllare l'etichetta.\n",
               troncate, troncate == 1 ? "riga" : "righe");
    } else {
        printf("Etichetta pronta.\n");
    }

    return 0;
}

/* Legge una riga con fgets e toglie il '\n'. Se la riga è troppo lunga
 * scarta il resto. Restituisce 0 a fine input. */
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

/* 1 se s contiene solo cifre. */
int solo_cifre(const char s[])
{
    int i = 0;
    int valida = 1;

    while (s[i] != '\0' && valida) {
        if (s[i] < '0' || s[i] > '9') {
            valida = 0;
        }
        i++;
    }
    return valida;
}

/* Aggiunge sorg a dest (array di dim celle) senza superarne la dimensione.
 * Restituisce 1 se sorg è entrata tutta, 0 se è stata troncata. */
int aggiungi(char dest[], int dim, const char sorg[])
{
    int spazio_libero;

    spazio_libero = dim - (int) strlen(dest) - 1;
    strncat(dest, sorg, spazio_libero);
    return (int) strlen(sorg) <= spazio_libero;
}

/* Stampa s dentro il bordo dell'etichetta, allineata a sinistra. */
void stampa_riga(const char s[])
{
    printf("| %-*s |\n", LARGHEZZA, s);
}
