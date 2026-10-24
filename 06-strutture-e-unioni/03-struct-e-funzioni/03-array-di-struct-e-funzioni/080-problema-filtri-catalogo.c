/*
 * 080-problema-filtri-catalogo.c
 *
 * Catalogo della biblioteca: ricerche con filtri scelti dall'utente
 *
 * Gli studenti cercano libri nel catalogo applicando un filtro scelto da
 * un menu. Ogni filtro è una funzione che riceve un libro e un valore di
 * riferimento (un testo o un numero, scritto come stringa) e decide se il
 * libro va mostrato:
 *
 *     typedef int (*Filtro)(const Libro *l, const char *valore);
 *
 *     int per_autore(const Libro *l, const char *valore);       autore contiene il testo
 *     int per_genere(const Libro *l, const char *valore);       genere uguale
 *     int dopo_anno(const Libro *l, const char *valore);        anno >= valore
 *     int disponibile(const Libro *l, const char *valore);      copie libere (valore ignorato)
 *
 *     int mostra(const Libro catalogo[], int n, Filtro f, const char *valore);
 *
 * Il menu ha una tabella di Filtro e una di descrizioni: la scelta è
 * l'indice. mostra stampa i libri che passano il filtro e restituisce
 * quanti sono.
 *
 * Il programma legge "numero_filtro valore"; il filtro 4 richiede comunque
 * un valore (qualsiasi). 0 termina.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIBRI   7
#define FILTRI  4
#define LUNG    20

typedef struct {
    char titolo[32];
    char autore[24];
    char genere[16];
    int anno;
    int copie_libere;
} Libro;

typedef int (*Filtro)(const Libro *l, const char *valore);

int per_autore(const Libro *l, const char *valore);
int per_genere(const Libro *l, const char *valore);
int dopo_anno(const Libro *l, const char *valore);
int disponibile(const Libro *l, const char *valore);
int mostra(const Libro catalogo[], int n, Filtro f, const char *valore);
void leggi_valore(char *valore, int dimensione);
void svuota_riga(void);

int main(void)
{
    Libro catalogo[LIBRI] = {
        {"Il barone rampante", "Italo Calvino", "romanzo", 1957, 1},
        {"Le citta' invisibili", "Italo Calvino", "romanzo", 1972, 0},
        {"Fahrenheit 451", "Ray Bradbury", "fantascienza", 1953, 2},
        {"Io, robot", "Isaac Asimov", "fantascienza", 1950, 1},
        {"Se questo e' un uomo", "Primo Levi", "memorie", 1947, 3},
        {"Il sistema periodico", "Primo Levi", "racconti", 1975, 0},
        {"La luna e i falo'", "Cesare Pavese", "romanzo", 1950, 2}
    };
    Filtro filtri[FILTRI] = {per_autore, per_genere, dopo_anno, disponibile};
    const char *descrizioni[FILTRI] = {"autore contiene", "genere", "pubblicati dal", "disponibili"};
    char valore[LUNG];
    int scelta = 1;
    int f;
    int letti;

    for (f = 0; f < FILTRI; f++) {
        printf("  %d  %s\n", f + 1, descrizioni[f]);
    }
    while (scelta != 0) {
        printf("Filtro e valore (0 per finire): ");
        letti = scanf("%d", &scelta);
        if (letti == EOF) {
            scelta = 0;                 /* input terminato: come 0 */
        } else if (letti == 0) {
            svuota_riga();              /* non e' un numero */
            printf("  Filtro inesistente.\n");
            scelta = -1;                /* si continua */
        } else if (scelta >= 1 && scelta <= FILTRI) {
            leggi_valore(valore, LUNG); /* il resto della riga */
            printf("  Trovati: %d\n", mostra(catalogo, LIBRI, filtri[scelta - 1], valore));
        } else {
            svuota_riga();
            if (scelta != 0) {
                printf("  Filtro inesistente.\n");
            }
        }
    }

    return 0;
}

int per_autore(const Libro *l, const char *valore)
{
    return strstr(l->autore, valore) != NULL;
}

int per_genere(const Libro *l, const char *valore)
{
    return strcmp(l->genere, valore) == 0;
}

int dopo_anno(const Libro *l, const char *valore)
{
    return l->anno >= atoi(valore);
}

/* Il prototipo è quello di Filtro anche se il valore non serve. */
int disponibile(const Libro *l, const char *valore)
{
    (void) valore;
    return l->copie_libere > 0;
}

int mostra(const Libro catalogo[], int n, Filtro f, const char *valore)
{
    int i;
    int trovati = 0;

    for (i = 0; i < n; i++) {
        if (f(&catalogo[i], valore)) {
            printf("  %-22s %-15s %-12s %d  libere %d\n", catalogo[i].titolo, catalogo[i].autore,
                   catalogo[i].genere, catalogo[i].anno, catalogo[i].copie_libere);
            trovati++;
        }
    }
    return trovati;
}

/* Copia in valore il resto della riga, senza gli spazi iniziali; i
 * caratteri che non stanno nell'array vengono scartati. */
void leggi_valore(char *valore, int dimensione)
{
    int c;
    int i = 0;

    c = getchar();
    while (c == ' ' || c == '\t') {
        c = getchar();
    }
    while (c != '\n' && c != EOF) {
        if (i < dimensione - 1) {
            valore[i] = (char) c;
            i++;
        }
        c = getchar();
    }
    valore[i] = '\0';
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
