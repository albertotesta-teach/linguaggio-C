/*
 * 070-problema-comandi-magazzino.c
 *
 * Gestire un magazzino con comandi testuali
 *
 * Il magazzino di una ferramenta si gestisce scrivendo comandi su una riga:
 *
 *     CARICO viti 50        aggiunge 50 pezzi all'articolo "viti"
 *     SCARICO dadi 20       toglie 20 pezzi (se disponibili)
 *     STATO                 mostra tutte le giacenze
 *     STATO viti            mostra la giacenza di un articolo
 *     FINE                  termina
 *
 * Ogni riga si scompone con sscanf, che restituisce quanti elementi ha
 * letto:
 *
 *     n = sscanf(riga, "%15s %15s %d", comando, articolo, &quantita);
 *         n == 1  solo il comando        n == 2  comando e articolo
 *         n == 3  comando, articolo e quantità
 *
 * Comandi e articoli si accettano in maiuscolo o minuscolo: prima del
 * confronto si convertono (comando in maiuscolo, articolo in minuscolo).
 * Articoli e giacenze sono due array paralleli.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ARTICOLI 5
#define LUNG     16
#define DIM      60

int leggi_riga(char s[], int dim);
void in_maiuscolo(char s[]);
void in_minuscolo(char s[]);
int cerca_articolo(const char nome[], const char articoli[][LUNG], int n);

int main(void)
{
    char articoli[ARTICOLI][LUNG] = {"viti", "dadi", "chiodi", "tasselli", "rondelle"};
    int giacenze[ARTICOLI] = {200, 150, 500, 80, 300};
    char riga[DIM];
    char comando[LUNG];
    char articolo[LUNG];
    int quantita;
    int letti;
    int a;
    int fine = 0;

    printf("=== MAGAZZINO FERRAMENTA ===\n");
    printf("Comandi: CARICO art n | SCARICO art n | STATO [art] | FINE\n");

    while (!fine) {
        printf("> ");
        if (!leggi_riga(riga, DIM)) {
            strcpy(riga, "FINE");
        }
        letti = sscanf(riga, "%15s %15s %d", comando, articolo, &quantita);
        if (letti >= 1) {
            in_maiuscolo(comando);
        }
        if (letti >= 2) {
            in_minuscolo(articolo);
        }

        if (letti < 1) {
            printf("  Scrivi un comando.\n");
        } else if (strcmp(comando, "FINE") == 0) {
            fine = 1;
        } else if (strcmp(comando, "STATO") == 0 && letti == 1) {
            for (a = 0; a < ARTICOLI; a++) {
                printf("  %-9s %4d\n", articoli[a], giacenze[a]);
            }
        } else if (strcmp(comando, "STATO") == 0) {
            a = cerca_articolo(articolo, articoli, ARTICOLI);
            if (a == -1) {
                printf("  Articolo \"%s\" sconosciuto.\n", articolo);
            } else {
                printf("  %s: %d pezzi\n", articoli[a], giacenze[a]);
            }
        } else if (strcmp(comando, "CARICO") == 0 || strcmp(comando, "SCARICO") == 0) {
            a = (letti >= 2) ? cerca_articolo(articolo, articoli, ARTICOLI) : -1;
            if (letti < 3 || quantita <= 0) {
                printf("  Uso: %s articolo quantita' (positiva)\n", comando);
            } else if (a == -1) {
                printf("  Articolo \"%s\" sconosciuto.\n", articolo);
            } else if (strcmp(comando, "CARICO") == 0) {
                giacenze[a] = giacenze[a] + quantita;
                printf("  %s: +%d -> %d pezzi\n", articoli[a], quantita, giacenze[a]);
            } else if (quantita > giacenze[a]) {
                printf("  Disponibili solo %d %s.\n", giacenze[a], articoli[a]);
            } else {
                giacenze[a] = giacenze[a] - quantita;
                printf("  %s: -%d -> %d pezzi\n", articoli[a], quantita, giacenze[a]);
            }
        } else {
            printf("  Comando \"%s\" sconosciuto.\n", comando);
        }
    }
    printf("Sessione chiusa.\n");

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

void in_maiuscolo(char s[])
{
    int i = 0;

    while (s[i] != '\0') {
        s[i] = (char) toupper((unsigned char) s[i]);
        i++;
    }
}

void in_minuscolo(char s[])
{
    int i = 0;

    while (s[i] != '\0') {
        s[i] = (char) tolower((unsigned char) s[i]);
        i++;
    }
}

int cerca_articolo(const char nome[], const char articoli[][LUNG], int n)
{
    int k = 0;
    int trovato = -1;

    while (k < n && trovato == -1) {
        if (strcmp(nome, articoli[k]) == 0) {
            trovato = k;
        }
        k++;
    }
    return trovato;
}
