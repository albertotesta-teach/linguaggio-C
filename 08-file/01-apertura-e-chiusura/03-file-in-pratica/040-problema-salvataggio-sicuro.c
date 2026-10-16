/*
 * 040-problema-salvataggio-sicuro.c
 *
 * La biblioteca di classe: caricare un elenco e salvarlo in sicurezza
 *
 * La classe tiene in libri.txt l'elenco dei libri della biblioteca di
 * classe, un titolo per riga. Il programma:
 *
 *   1. carica il file carattere per carattere in un array di titoli
 *      (se il file non esiste, l'elenco parte vuoto);
 *   2. permette di aggiungere e togliere titoli in memoria;
 *   3. salva con il salvataggio sicuro:
 *
 *          scrivi l'elenco in libri.tmp, poi fclose
 *          remove("libri.txt")              (può fallire se non c'era)
 *          rename("libri.tmp", "libri.txt")
 *
 *      Se libri.tmp non si può creare, libri.txt resta com'era.
 *
 * Comandi:
 *     A titolo     aggiunge (il titolo può contenere spazi)
 *     R numero     rimuove il titolo con quel numero
 *     E            elenco
 *     S            salva
 *     Q            fine (avvisa se ci sono modifiche non salvate)
 */

#include <stdio.h>
#include <string.h>

#define MAX_LIBRI 50
#define MAX_TITOLO 60

int carica(const char *nome, char titoli[][MAX_TITOLO]);
int salva(const char *nome, const char *temporaneo, char titoli[][MAX_TITOLO], int n);
void elenco(char titoli[][MAX_TITOLO], int n);

int main(void)
{
    char titoli[MAX_LIBRI][MAX_TITOLO];
    char comando = ' ';
    int n;
    int numero;
    int modificato = 0;
    int i;

    n = carica("libri.txt", titoli);
    printf("Libri caricati da libri.txt: %d\n", n);
    while (comando != 'Q') {
        printf("Comando (A, R, E, S, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'A') {
            if (n == MAX_LIBRI) {
                printf("  elenco pieno\n");
                scanf("%*[^\n]");
            } else if (scanf(" %59[^\n]", titoli[n]) == 1) {
                n++;
                modificato = 1;
                printf("  aggiunto al numero %d\n", n);
            }
        } else if (comando == 'R') {
            if (scanf("%d", &numero) != 1 || numero < 1 || numero > n) {
                printf("  numero non valido\n");
                scanf("%*[^\n]");
            } else {
                printf("  rimosso: %s\n", titoli[numero - 1]);
                for (i = numero - 1; i < n - 1; i++) {
                    strcpy(titoli[i], titoli[i + 1]);
                }
                n--;
                modificato = 1;
            }
        } else if (comando == 'E') {
            elenco(titoli, n);
        } else if (comando == 'S') {
            if (salva("libri.txt", "libri.tmp", titoli, n)) {
                printf("  salvati %d titoli in libri.txt\n", n);
                modificato = 0;
            } else {
                printf("  salvataggio non riuscito: libri.txt non e' stato toccato\n");
            }
        } else if (comando == 'Q') {
            if (modificato) {
                printf("  attenzione: le ultime modifiche non sono state salvate\n");
            }
        } else {
            printf("  comando sconosciuto\n");
            scanf("%*[^\n]");
        }
    }

    return 0;
}

/* Legge un titolo per riga; restituisce quanti titoli ha caricato. */
int carica(const char *nome, char titoli[][MAX_TITOLO])
{
    FILE *f = fopen(nome, "r");
    int n = 0;
    int lunghezza = 0;
    int c;

    if (f != NULL) {
        c = fgetc(f);
        while (c != EOF && n < MAX_LIBRI) {
            if (c == '\n') {
                titoli[n][lunghezza] = '\0';
                if (lunghezza > 0) {
                    n++;
                }
                lunghezza = 0;
            } else if (lunghezza < MAX_TITOLO - 1) {
                titoli[n][lunghezza] = (char) c;
                lunghezza++;
            }
            c = fgetc(f);
        }
        if (lunghezza > 0 && n < MAX_LIBRI) {
            titoli[n][lunghezza] = '\0';
            n++;
        }
        fclose(f);
    }
    return n;
}

/* Salvataggio sicuro tramite file temporaneo; 0 se non riesce. */
int salva(const char *nome, const char *temporaneo, char titoli[][MAX_TITOLO], int n)
{
    FILE *f = fopen(temporaneo, "w");
    int ok = f != NULL;
    int i;

    if (ok) {
        for (i = 0; i < n; i++) {
            fprintf(f, "%s\n", titoli[i]);
        }
        fclose(f);
        remove(nome);
        ok = rename(temporaneo, nome) == 0;
    }
    return ok;
}

void elenco(char titoli[][MAX_TITOLO], int n)
{
    int i;

    if (n == 0) {
        printf("  elenco vuoto\n");
    }
    for (i = 0; i < n; i++) {
        printf("  %2d. %s\n", i + 1, titoli[i]);
    }
}
