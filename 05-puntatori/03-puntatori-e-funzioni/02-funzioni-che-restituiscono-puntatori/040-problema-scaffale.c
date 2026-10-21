/*
 * 040-problema-scaffale.c
 *
 * Magazzino del laboratorio: carico e scarico per codice
 *
 * Il magazzino del laboratorio di elettronica conserva componenti
 * identificati da un codice numerico. Due array paralleli contengono codici
 * e quantità. Il tecnico registra i movimenti:
 *     C codice n    carico di n pezzi
 *     S codice n    scarico di n pezzi (solo se ce ne sono abbastanza)
 *     Q             fine, con l'inventario aggiornato
 *
 * La funzione quantita_di cerca il codice e restituisce l'INDIRIZZO della
 * quantità corrispondente (NULL se il codice non esiste). Il main modifica
 * la quantità direttamente tramite quel puntatore, senza conoscere la
 * posizione nell'array.
 */

#include <stdio.h>

#define ARTICOLI 5

int *quantita_di(const int *codici, int *quantita, int n, int codice);
void inventario(const int *codici, const int *quantita, int n);
void svuota_riga(void);

int main(void)
{
    int codici[ARTICOLI] = {1001, 1002, 2010, 2011, 3050};
    int quantita[ARTICOLI] = {40, 25, 120, 8, 15};
    int *q;
    char comando = ' ';
    int codice;
    int n;
    int letti;

    inventario(codici, quantita, ARTICOLI);
    while (comando != 'Q') {
        printf("Movimento (C codice n, S codice n, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'C' || comando == 'S') {
            letti = scanf("%d %d", &codice, &n);
            if (letti == EOF) {
                comando = 'Q';          /* input terminato */
            } else if (letti != 2 || n <= 0) {
                if (letti != 2) {
                    svuota_riga();      /* non sono due numeri */
                }
                printf("  Dati non validi.\n");
            } else {
                q = quantita_di(codici, quantita, ARTICOLI, codice);
                if (q == NULL) {
                    printf("  Codice %d inesistente.\n", codice);
                } else if (comando == 'C') {
                    *q = *q + n;
                    printf("  Codice %d: caricati %d, ora %d pezzi\n", codice, n, *q);
                } else if (*q >= n) {
                    *q = *q - n;
                    printf("  Codice %d: scaricati %d, ora %d pezzi\n", codice, n, *q);
                } else {
                    printf("  Codice %d: solo %d pezzi disponibili\n", codice, *q);
                }
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }
    inventario(codici, quantita, ARTICOLI);

    return 0;
}

/* Restituisce l'indirizzo della quantità dell'articolo con il codice dato,
 * NULL se il codice non c'è. codici e quantita sono paralleli: la
 * posizione trovata in codici vale anche per quantita. */
int *quantita_di(const int *codici, int *quantita, int n, int codice)
{
    int i = 0;

    while (i < n && codici[i] != codice) {
        i++;
    }
    return i < n ? quantita + i : NULL;
}

void inventario(const int *codici, const int *quantita, int n)
{
    int i;

    printf("Inventario:");
    for (i = 0; i < n; i++) {
        printf("  %d: %d", codici[i], quantita[i]);
    }
    printf("\n");
}

/* Scarta i caratteri rimasti sulla riga dopo un inserimento errato. */
void svuota_riga(void)
{
    int c;

    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}
