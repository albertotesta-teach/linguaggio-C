/*
 * 070-problema-lettura-scheda.c
 *
 * Catalogo della biblioteca: inserire un nuovo libro con controlli
 *
 * Il bibliotecario inserisce i dati di un libro appena arrivato. La
 * funzione di lettura riempie la struct del chiamante e restituisce
 * l'esito:
 *
 *     typedef struct {
 *         char titolo[40];
 *         char autore[30];
 *         int anno;
 *         int pagine;
 *         char isbn[14];           13 cifre
 *     } Libro;
 *
 *     int leggi_libro(Libro *l);
 *
 * leggi_libro restituisce 1 se tutti i dati sono validi; altrimenti
 * stampa il campo sbagliato e restituisce 0. I controlli:
 *   - titolo e autore non vuoti;
 *   - anno tra 1450 e 2026, pagine tra 1 e 5000;
 *   - ISBN di 13 cifre con la cifra di controllo corretta: si moltiplicano
 *     le cifre alternativamente per 1 e per 3; la somma deve essere un
 *     multiplo di 10.
 *
 * Il programma ripete la richiesta finché la scheda non è valida (al
 * massimo 3 tentativi) e poi la stampa.
 */

#include <stdio.h>
#include <string.h>

#define LUNG 80
#define TENTATIVI 3

typedef struct {
    char titolo[40];
    char autore[30];
    int anno;
    int pagine;
    char isbn[14];
} Libro;

int leggi_libro(Libro *l);
int leggi_testo(const char *domanda, char *dest, int dimensione);
int isbn_valido(const char *isbn);
void stampa(const Libro *l);

int main(void)
{
    Libro nuovo;
    int tentativo = 1;
    int valido = 0;

    while (!valido && tentativo <= TENTATIVI) {
        printf("--- Tentativo %d ---\n", tentativo);
        valido = leggi_libro(&nuovo);
        tentativo++;
    }
    if (valido) {
        printf("\nScheda inserita:\n");
        stampa(&nuovo);
    } else {
        printf("\nInserimento annullato dopo %d tentativi.\n", TENTATIVI);
    }

    return 0;
}

/* Riempie *l campo per campo; si ferma al primo campo non valido. */
int leggi_libro(Libro *l)
{
    char riga[LUNG];
    int ok = leggi_testo("Titolo: ", l->titolo, sizeof(l->titolo)) &&
             leggi_testo("Autore: ", l->autore, sizeof(l->autore));

    if (!ok) {
        printf("  Titolo e autore non possono essere vuoti o troppo lunghi.\n");
    } else {
        ok = leggi_testo("Anno e pagine: ", riga, LUNG) &&
             sscanf(riga, "%d %d", &l->anno, &l->pagine) == 2 &&
             l->anno >= 1450 && l->anno <= 2026 && l->pagine >= 1 && l->pagine <= 5000;
        if (!ok) {
            printf("  Anno (1450-2026) o pagine (1-5000) non validi.\n");
        } else {
            ok = leggi_testo("ISBN (13 cifre): ", l->isbn, sizeof(l->isbn)) && isbn_valido(l->isbn);
            if (!ok) {
                printf("  ISBN non valido.\n");
            }
        }
    }
    return ok;
}

/* Legge una riga non vuota che stia in dest; restituisce 1 se riuscito. */
int leggi_testo(const char *domanda, char *dest, int dimensione)
{
    char riga[LUNG];
    char *a_capo;
    int ok = 0;

    printf("%s", domanda);
    if (fgets(riga, LUNG, stdin) != NULL) {
        a_capo = strchr(riga, '\n');
        if (a_capo != NULL) {
            *a_capo = '\0';
        }
        ok = riga[0] != '\0' && (int) strlen(riga) < dimensione;
        if (ok) {
            strcpy(dest, riga);
        }
    }
    return ok;
}

/* 13 cifre; somma con pesi alternati 1 e 3 multipla di 10. */
int isbn_valido(const char *isbn)
{
    int somma = 0;
    int i = 0;
    int cifre = 1;

    while (isbn[i] != '\0' && cifre) {
        cifre = isbn[i] >= '0' && isbn[i] <= '9';
        somma = somma + (isbn[i] - '0') * (i % 2 == 0 ? 1 : 3);
        i++;
    }
    return cifre && i == 13 && somma % 10 == 0;
}

void stampa(const Libro *l)
{
    printf("  %s, %s (%d), %d pagine, ISBN %s\n", l->titolo, l->autore, l->anno, l->pagine, l->isbn);
}
