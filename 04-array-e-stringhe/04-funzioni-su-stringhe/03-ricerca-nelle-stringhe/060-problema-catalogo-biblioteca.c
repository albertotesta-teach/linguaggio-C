/*
 * 060-problema-catalogo-biblioteca.c
 *
 * Ricerca per parola chiave nel catalogo della biblioteca scolastica
 *
 * Il catalogo è formato da array paralleli: titoli, autori, anno di
 * pubblicazione e numero di copie disponibili. L'utente scrive una parola
 * chiave e il programma elenca i libri che la contengono nel titolo O
 * nell'autore, senza distinguere maiuscole e minuscole:
 *
 *     "promessi"  -> I promessi sposi
 *     "calvino"   -> tutti i libri di Italo Calvino
 *
 * Per ignorare le maiuscole si confrontano copie in minuscolo della chiave
 * e dei campi del libro; la ricerca vera e propria è fatta da strstr.
 * I libri con 0 copie disponibili sono segnalati come "in prestito".
 * La ricerca si ripete finché si inserisce una riga vuota.
 */

#include <stdio.h>
#include <string.h>

#define LIBRI      8
#define LUNG_TITOLO 40
#define LUNG_AUTORE 24
#define DIM         40

int leggi_riga(char s[], int dim);
void in_minuscolo(char dest[], const char sorg[]);
int contiene(const char testo[], const char chiave_minuscola[]);

int main(void)
{
    char titoli[LIBRI][LUNG_TITOLO] = {
        "I promessi sposi", "Il barone rampante", "Le citta' invisibili",
        "La coscienza di Zeno", "Il sentiero dei nidi di ragno",
        "Se questo e' un uomo", "Il fu Mattia Pascal", "Marcovaldo"
    };
    char autori[LIBRI][LUNG_AUTORE] = {
        "Alessandro Manzoni", "Italo Calvino", "Italo Calvino",
        "Italo Svevo", "Italo Calvino", "Primo Levi",
        "Luigi Pirandello", "Italo Calvino"
    };
    int anni[LIBRI] = {1840, 1957, 1972, 1923, 1947, 1947, 1904, 1963};
    int copie[LIBRI] = {3, 1, 0, 2, 1, 2, 0, 4};

    char chiave[DIM];
    char chiave_min[DIM];
    int letta;
    int k;
    int trovati;

    printf("=== CATALOGO DELLA BIBLIOTECA (%d titoli) ===\n", LIBRI);
    printf("Parola chiave (riga vuota per uscire): ");
    letta = leggi_riga(chiave, DIM);

    while (letta && chiave[0] != '\0') {
        in_minuscolo(chiave_min, chiave);
        trovati = 0;
        for (k = 0; k < LIBRI; k++) {
            if (contiene(titoli[k], chiave_min) || contiene(autori[k], chiave_min)) {
                printf("  %-30s %-19s %d  %s\n", titoli[k], autori[k], anni[k],
                       copie[k] > 0 ? "disponibile" : "in prestito");
                trovati++;
            }
        }
        if (trovati == 0) {
            printf("  Nessun libro trovato per \"%s\".\n", chiave);
        } else {
            printf("  %d %s\n", trovati, trovati == 1 ? "risultato" : "risultati");
        }
        printf("Parola chiave (riga vuota per uscire): ");
        letta = leggi_riga(chiave, DIM);
    }
    printf("Buona lettura!\n");

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

void in_minuscolo(char dest[], const char sorg[])
{
    int i = 0;

    while (sorg[i] != '\0') {
        if (sorg[i] >= 'A' && sorg[i] <= 'Z') {
            dest[i] = sorg[i] + ('a' - 'A');
        } else {
            dest[i] = sorg[i];
        }
        i++;
    }
    dest[i] = '\0';
}

/* 1 se testo contiene la chiave (già in minuscolo), ignorando le maiuscole
 * di testo. La copia in minuscolo è grande quanto il campo più lungo. */
int contiene(const char testo[], const char chiave_minuscola[])
{
    char testo_min[LUNG_TITOLO];

    in_minuscolo(testo_min, testo);
    return strstr(testo_min, chiave_minuscola) != NULL;
}
