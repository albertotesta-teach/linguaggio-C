/*
 * 080-problema-archivio-foto.c
 *
 * L'archivio fotografico del giornalino: memoria su due livelli
 *
 * Ogni foto dell'archivio è una struct allocata, e la sua didascalia è
 * un secondo blocco della lunghezza esatta del testo:
 *
 *     typedef struct {
 *         int anno;
 *         char autore[16];
 *         char *didascalia;          blocco di strlen + 1 byte
 *     } Foto;
 *
 *     Foto *archivio[MAX_FOTO];      array di puntatori
 *
 *     archivio[i] ──► +-----------+
 *                     | anno      |
 *                     | autore    |      +----------------------+
 *                     | didascalia ────► | "Festa di fine anno" |
 *                     +-----------+      +----------------------+
 *
 * Per ogni foto ci sono due blocchi, e l'ordine in cui si liberano conta:
 * prima la didascalia, poi la struct. Liberando prima la struct, il
 * puntatore alla didascalia non si potrebbe più leggere e quel blocco
 * resterebbe perso.
 *
 * Cambiare una didascalia (senza realloc, che arriverà più avanti):
 * si alloca il blocco nuovo, si copia il testo, si libera il vecchio e
 * si aggiorna il puntatore. Se la malloc fallisce la vecchia didascalia
 * resta valida.
 *
 * Eliminare una foto: si liberano i suoi due blocchi e si spostano
 * indietro i puntatori successivi (si spostano solo gli indirizzi, non le
 * foto).
 *
 * Comandi:
 *     A anno autore didascalia    aggiunge (didascalia = resto della riga)
 *     C numero didascalia         cambia la didascalia
 *     D numero                    elimina la foto
 *     M                           mostra l'archivio
 *     Q                           fine: libera tutto
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOTO 10
#define LUNG 80

typedef struct {
    int anno;
    char autore[16];
    char *didascalia;
} Foto;

char *copia_testo(const char *testo);
Foto *crea_foto(int anno, const char *autore, const char *didascalia);
void distruggi_foto(Foto *f);
int cambia_didascalia(Foto *f, const char *nuova);
void leggi_resto(char testo[]);
void mostra(Foto *archivio[], int n);

int main(void)
{
    Foto *archivio[MAX_FOTO];
    char testo[LUNG];
    char autore[16];
    char comando = ' ';
    int n = 0;
    int anno;
    int numero;
    int i;

    while (comando != 'Q') {
        printf("Comando (A, C, D, M, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'A') {
            if (scanf("%d %15s", &anno, autore) != 2 || anno < 1900 || anno > 2100) {
                printf("  Dati non validi.\n");
                scanf("%*[^\n]");
            } else {
                leggi_resto(testo);
                if (testo[0] == '\0') {
                    printf("  Manca la didascalia.\n");
                } else if (n == MAX_FOTO) {
                    printf("  Archivio pieno.\n");
                } else {
                    archivio[n] = crea_foto(anno, autore, testo);
                    if (archivio[n] == NULL) {
                        printf("  Memoria insufficiente.\n");
                    } else {
                        n++;
                        printf("  foto %d aggiunta (didascalia di %zu byte)\n", n,
                               strlen(testo) + 1);
                    }
                }
            }
        } else if (comando == 'C') {
            if (scanf("%d", &numero) != 1 || numero < 1 || numero > n) {
                printf("  Foto inesistente.\n");
                scanf("%*[^\n]");
            } else {
                leggi_resto(testo);
                if (testo[0] == '\0') {
                    printf("  Manca la didascalia.\n");
                } else if (cambia_didascalia(archivio[numero - 1], testo)) {
                    printf("  didascalia della foto %d cambiata\n", numero);
                } else {
                    printf("  Memoria insufficiente: didascalia invariata.\n");
                }
            }
        } else if (comando == 'D') {
            if (scanf("%d", &numero) != 1 || numero < 1 || numero > n) {
                printf("  Foto inesistente.\n");
            } else {
                distruggi_foto(archivio[numero - 1]);
                for (i = numero - 1; i < n - 1; i++) {
                    archivio[i] = archivio[i + 1];
                }
                n--;
                printf("  foto %d eliminata\n", numero);
            }
            scanf("%*[^\n]");
        } else if (comando == 'M') {
            mostra(archivio, n);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
            scanf("%*[^\n]");
        }
    }

    for (i = 0; i < n; i++) {
        distruggi_foto(archivio[i]);
    }
    printf("Archivio chiuso: foto liberate %d, blocchi liberati %d\n", n, 2 * n);

    return 0;
}

/* Un blocco con una copia del testo, della lunghezza giusta. */
char *copia_testo(const char *testo)
{
    char *copia = malloc(strlen(testo) + 1);

    if (copia != NULL) {
        strcpy(copia, testo);
    }
    return copia;
}

/* Struct e didascalia; NULL (senza perdite) se una malloc fallisce. */
Foto *crea_foto(int anno, const char *autore, const char *didascalia)
{
    Foto *f = malloc(sizeof *f);

    if (f != NULL) {
        f->didascalia = copia_testo(didascalia);
        if (f->didascalia == NULL) {
            free(f);
            f = NULL;
        } else {
            f->anno = anno;
            strcpy(f->autore, autore);
        }
    }
    return f;
}

/* Prima la didascalia, poi la struct. */
void distruggi_foto(Foto *f)
{
    if (f != NULL) {
        free(f->didascalia);
        free(f);
    }
}

/* Nuovo blocco, poi free del vecchio; 0 se la malloc fallisce. */
int cambia_didascalia(Foto *f, const char *nuova)
{
    char *copia = copia_testo(nuova);

    if (copia != NULL) {
        free(f->didascalia);
        f->didascalia = copia;
    }
    return copia != NULL;
}

/*
 * Il resto della riga (al massimo LUNG - 1 caratteri), senza gli spazi
 * iniziali e finali; stringa vuota se la riga è finita. %*[ ] salta gli
 * spazi ma non il '\n', quindi non si legge mai la riga successiva.
 */
void leggi_resto(char testo[])
{
    int i;

    testo[0] = '\0';
    scanf("%*[ ]");
    if (scanf("%79[^\n]", testo) == 1) {
        i = (int) strlen(testo);
        while (i > 0 && testo[i - 1] == ' ') {
            i--;
        }
        testo[i] = '\0';
    }
    scanf("%*[^\n]");
}

void mostra(Foto *archivio[], int n)
{
    int i;

    if (n == 0) {
        printf("  archivio vuoto\n");
    }
    for (i = 0; i < n; i++) {
        printf("  %d. [%d, %s] %s\n", i + 1, archivio[i]->anno, archivio[i]->autore,
               archivio[i]->didascalia);
    }
}
