/*
 * 070-problema-nome-ed-estensione.c
 *
 * Separare cartella, nome ed estensione dei file di un archivio
 *
 * Il tecnico del laboratorio ha l'elenco dei file salvati dagli studenti,
 * con il percorso completo:
 *
 *     "compiti/3B/rossi/relazione.finale.docx"
 *      cartella                 nome             estensione
 *      compiti/3B/rossi         relazione.finale docx
 *
 *   - la cartella finisce all'ULTIMA '/'  (ultima_posizione)
 *   - l'estensione inizia dopo l'ULTIMO '.' del nome: il nome stesso può
 *     contenere altri punti
 *   - un file senza '.' non ha estensione; un nome che inizia con '.'
 *     (".gitignore") è un file nascosto, senza estensione
 *
 * Ogni estensione viene poi ricondotta a un tipo, cercandola in due array
 * paralleli (estensioni conosciute e tipo), e alla fine si conta quanti
 * file ci sono per ogni tipo.
 */

#include <stdio.h>
#include <string.h>

#define FILE_ARCHIVIO 8
#define LUNG          50
#define CONOSCIUTE    7
#define LUNG_EST      6
#define TIPI          4

int ultima_posizione(const char s[], char c);
void copia_parte(char dest[], const char s[], int inizio, int n);
int cerca(const char elenco[][LUNG_EST], int n, const char parola[]);

int main(void)
{
    char percorsi[FILE_ARCHIVIO][LUNG] = {
        "compiti/3B/rossi/relazione.finale.docx",
        "compiti/3B/rossi/grafico.png",
        "compiti/3B/bianchi/esercizio1.c",
        "progetti/sito/index.html",
        "progetti/sito/logo.jpg",
        "README",
        "progetti/.gitignore",
        "compiti/4A/verdi/tesina.pdf"
    };
    char estensioni[CONOSCIUTE][LUNG_EST] = {"docx", "pdf", "png", "jpg", "c", "html", "txt"};
    int tipo_di[CONOSCIUTE] = {0, 0, 1, 1, 2, 2, 0};
    char tipi[TIPI][12] = {"documento", "immagine", "codice", "altro"};
    int quanti[TIPI] = {0};

    char cartella[LUNG];
    char nome[LUNG];
    char estensione[LUNG];
    int k;
    int barra;
    int punto;
    int lung;
    int e;
    int tipo;

    printf("%-20s %-18s %-5s %s\n", "Cartella", "Nome", "Est.", "Tipo");
    for (k = 0; k < FILE_ARCHIVIO; k++) {
        lung = (int) strlen(percorsi[k]);
        barra = ultima_posizione(percorsi[k], '/');

        /* cartella: da 0 a barra - 1; nome completo: da barra + 1 alla fine */
        if (barra == -1) {
            strcpy(cartella, "(radice)");
        } else {
            copia_parte(cartella, percorsi[k], 0, barra);
        }
        copia_parte(nome, percorsi[k], barra + 1, lung - barra - 1);

        /* estensione: dopo l'ultimo punto del nome, se non è il primo carattere */
        punto = ultima_posizione(nome, '.');
        if (punto > 0) {
            copia_parte(estensione, nome, punto + 1, (int) strlen(nome) - punto - 1);
            nome[punto] = '\0';         /* il nome si accorcia prima del punto */
        } else {
            estensione[0] = '\0';
        }

        e = cerca(estensioni, CONOSCIUTE, estensione);
        if (e == -1) {
            tipo = TIPI - 1;            /* "altro" */
        } else {
            tipo = tipo_di[e];
        }
        quanti[tipo]++;

        printf("%-20s %-18s %-5s %s\n", cartella, nome,
               estensione[0] == '\0' ? "-" : estensione, tipi[tipo]);
    }

    printf("\nRiepilogo:");
    for (tipo = 0; tipo < TIPI; tipo++) {
        printf("  %s %d", tipi[tipo], quanti[tipo]);
    }
    printf("\n");

    return 0;
}

int ultima_posizione(const char s[], char c)
{
    int i = 0;
    int posizione = -1;

    while (s[i] != '\0') {
        if (s[i] == c) {
            posizione = i;
        }
        i++;
    }
    return posizione;
}

void copia_parte(char dest[], const char s[], int inizio, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        dest[i] = s[inizio + i];
    }
    dest[n] = '\0';
}

/* Indice di parola nell'elenco, oppure -1. */
int cerca(const char elenco[][LUNG_EST], int n, const char parola[])
{
    int k = 0;
    int trovato = -1;

    while (k < n && trovato == -1) {
        if (strcmp(elenco[k], parola) == 0) {
            trovato = k;
        }
        k++;
    }
    return trovato;
}
