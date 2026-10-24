/*
 * 070-problema-catalogo-media.c
 *
 * Biblioteca scolastica: libri, DVD e riviste nello stesso catalogo
 *
 * Tutti i materiali hanno titolo e disponibilità; i dati specifici
 * cambiano con il tipo:
 *   - libro: autore e pagine;
 *   - DVD: regista e durata in minuti;
 *   - rivista: numero e anno.
 *
 *     typedef struct {
 *         TipoMedia tipo;
 *         char titolo[28];
 *         int disponibile;
 *         union {
 *             Libro libro;
 *             Dvd dvd;
 *             Rivista rivista;
 *         } info;
 *     } Media;
 *
 * I campi comuni stanno fuori dalla union, così le ricerche e i prestiti
 * non devono guardare il tipo; solo la stampa dei dettagli usa uno
 * switch sull'etichetta. Le riviste si consultano in biblioteca e non si
 * prestano.
 *
 * Comandi:
 *     E          elenco con i dettagli di ogni tipo
 *     C parola   materiali con la parola nel titolo
 *     P n        prestito del materiale n
 *     R n        restituzione del materiale n
 *     Q          fine
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATERIALI 6

typedef enum {
    LIBRO, DVD, RIVISTA
} TipoMedia;

typedef struct {
    char autore[20];
    int pagine;
} Libro;

typedef struct {
    char regista[20];
    int minuti;
} Dvd;

typedef struct {
    int numero;
    int anno;
} Rivista;

typedef struct {
    TipoMedia tipo;
    char titolo[28];
    int disponibile;
    union {
        Libro libro;
        Dvd dvd;
        Rivista rivista;
    } info;
} Media;

void stampa(int n, const Media *m);
void svuota_riga(void);

int main(void)
{
    Media catalogo[MATERIALI] = {
        {LIBRO, "Il sistema periodico", 1, {.libro = {"Primo Levi", 240}}},
        {DVD, "Il nome della rosa", 1, {.dvd = {"J.-J. Annaud", 130}}},
        {RIVISTA, "Le Scienze", 1, {.rivista = {687, 2025}}},
        {LIBRO, "Il nome della rosa", 0, {.libro = {"Umberto Eco", 503}}},
        {DVD, "Il sistema solare", 1, {.dvd = {"BBC", 58}}},
        {LIBRO, "Fahrenheit 451", 1, {.libro = {"Ray Bradbury", 176}}}
    };
    char comando = ' ';
    char parola[20];
    int n;
    int trovati;
    int i;

    while (comando != 'Q') {
        printf("Comando (E, C parola, P n, R n, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'E') {
            for (i = 0; i < MATERIALI; i++) {
                stampa(i + 1, &catalogo[i]);
            }
        } else if (comando == 'C') {
            if (scanf("%19s", parola) != 1) {
                printf("  Manca la parola.\n");
            } else {
                trovati = 0;
                for (i = 0; i < MATERIALI; i++) {
                    if (strstr(catalogo[i].titolo, parola) != NULL) {
                        stampa(i + 1, &catalogo[i]);
                        trovati++;
                    }
                }
                printf("  Trovati: %d\n", trovati);
            }
        } else if (comando == 'P' || comando == 'R') {
            if (scanf("%d", &n) != 1) {
                printf("  Numero non valido.\n");
            } else if (n < 1 || n > MATERIALI) {
                printf("  Materiale %d inesistente.\n", n);
            } else if (catalogo[n - 1].tipo == RIVISTA) {
                printf("  Le riviste si consultano in biblioteca.\n");
            } else if (comando == 'P' && !catalogo[n - 1].disponibile) {
                printf("  \"%s\" e' gia' in prestito.\n", catalogo[n - 1].titolo);
            } else if (comando == 'R' && catalogo[n - 1].disponibile) {
                printf("  \"%s\" non era in prestito.\n", catalogo[n - 1].titolo);
            } else {
                catalogo[n - 1].disponibile = comando == 'R';
                printf("  \"%s\": %s\n", catalogo[n - 1].titolo,
                       comando == 'P' ? "prestito registrato" : "restituito");
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        svuota_riga();                  /* un comando per riga */
    }

    return 0;
}

void stampa(int n, const Media *m)
{
    printf("  %d  %-21s ", n, m->titolo);
    switch (m->tipo) {
    case LIBRO:
        printf("libro    %s, %d pagine", m->info.libro.autore, m->info.libro.pagine);
        break;
    case DVD:
        printf("DVD      %s, %d minuti", m->info.dvd.regista, m->info.dvd.minuti);
        break;
    case RIVISTA:
        printf("rivista  n. %d, %d", m->info.rivista.numero, m->info.rivista.anno);
        break;
    }
    printf("%s\n", m->disponibile ? "" : "  (in prestito)");
}

/* Scarta i caratteri rimasti sulla riga. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
