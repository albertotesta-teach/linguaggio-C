/*
 * 070-problema-rubrica-modificabile.c
 *
 * Una rubrica con aggiunta, ricerca e cancellazione
 *
 * La rubrica del cellulare di servizio di un'associazione sportiva può
 * contenere al massimo MAX contatti. Nomi e numeri sono due elenchi
 * paralleli di stringhe gestiti come ARRAY A TAPPO (capitolo 04, array
 * monodimensionali): la variabile n indica quanti contatti sono presenti
 * e le righe da n in poi non sono usate.
 *
 * Operazioni del menu:
 *   1 Aggiungi  in coda (riga n), se c'è posto e il nome non esiste già
 *   2 Cerca     tutti i contatti che contengono il testo (strstr)
 *   3 Cancella  il contatto con quel nome: le righe successive si spostano
 *               indietro di una posizione con strcpy, poi n diminuisce
 *   4 Elenco
 *   0 Esci
 */

#include <stdio.h>
#include <string.h>

#define MAX  5
#define LUNG 24
#define DIM  40

int leggi_riga(char s[], int dim);
int cerca_esatto(const char nomi[][LUNG], int n, const char nome[]);

int main(void)
{
    char nomi[MAX][LUNG] = {"Allenatore Marco", "Magazzino", "Presidente"};
    char numeri[MAX][LUNG] = {"333 1234567", "0131 445566", "347 7654321"};
    int n = 3;
    char riga[DIM];
    char nome[DIM];
    char numero[DIM];
    int scelta = -1;
    int k;
    int pos;
    int trovati;

    while (scelta != 0) {
        printf("\n[%d/%d] 1 Aggiungi  2 Cerca  3 Cancella  4 Elenco  0 Esci\n> ", n, MAX);
        if (!leggi_riga(riga, DIM)) {
            scelta = 0;                 /* input terminato: si esce */
        } else if (sscanf(riga, "%d", &scelta) != 1) {
            scelta = -1;                /* non è un numero */
        }

        if (scelta == 1) {
            if (n == MAX) {
                printf("  Rubrica piena: cancella un contatto.\n");
            } else {
                printf("  Nome: ");
                leggi_riga(nome, LUNG);
                printf("  Numero: ");
                leggi_riga(numero, LUNG);
                if (nome[0] == '\0' || numero[0] == '\0') {
                    printf("  Nome e numero sono obbligatori.\n");
                } else if (cerca_esatto(nomi, n, nome) != -1) {
                    printf("  \"%s\" e' gia' in rubrica.\n", nome);
                } else {
                    strcpy(nomi[n], nome);
                    strcpy(numeri[n], numero);
                    n++;
                    printf("  Aggiunto.\n");
                }
            }
        } else if (scelta == 2) {
            printf("  Testo da cercare: ");
            leggi_riga(nome, DIM);
            trovati = 0;
            for (k = 0; k < n; k++) {
                if (strstr(nomi[k], nome) != NULL) {
                    printf("  %-18s %s\n", nomi[k], numeri[k]);
                    trovati++;
                }
            }
            if (trovati == 0) {
                printf("  Nessun contatto.\n");
            }
        } else if (scelta == 3) {
            printf("  Nome da cancellare: ");
            leggi_riga(nome, DIM);
            pos = cerca_esatto(nomi, n, nome);
            if (pos == -1) {
                printf("  \"%s\" non e' in rubrica.\n", nome);
            } else {
                /* le righe dopo pos si spostano indietro di uno */
                for (k = pos; k < n - 1; k++) {
                    strcpy(nomi[k], nomi[k + 1]);
                    strcpy(numeri[k], numeri[k + 1]);
                }
                n--;
                printf("  Cancellato.\n");
            }
        } else if (scelta == 4) {
            for (k = 0; k < n; k++) {
                printf("  %d. %-18s %s\n", k + 1, nomi[k], numeri[k]);
            }
        } else if (scelta != 0) {
            printf("  Scelta non valida.\n");
        }
    }
    printf("Rubrica chiusa con %d contatti.\n", n);

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
    } else {
        s[0] = '\0';
    }
    return ok;
}

int cerca_esatto(const char nomi[][LUNG], int n, const char nome[])
{
    int k = 0;
    int trovato = -1;

    while (k < n && trovato == -1) {
        if (strcmp(nomi[k], nome) == 0) {
            trovato = k;
        }
        k++;
    }
    return trovato;
}
