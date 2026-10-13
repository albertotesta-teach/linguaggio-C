/*
 * 070-problema-elenco-senza-doppioni.c
 *
 * I volontari dell'open day: un elenco in cui ogni nome compare una volta
 *
 * Gli studenti si offrono volontari per l'open day scrivendo il proprio
 * nome; qualcuno si iscrive due volte, qualcuno poi si ritira. L'elenco
 * è un vettore dinamico di nomi con due operazioni in più:
 *
 *     int aggiungi_se_manca(Elenco *e, const char *nome);
 *         1 aggiunto, 0 già presente, -1 memoria insufficiente
 *
 *     int rimuovi_valore(Elenco *e, const char *nome);
 *         cerca il nome e lo rimuove spostando i successivi; 0 se manca
 *
 * I nomi si confrontano senza distinguere maiuscole e minuscole ("rossi"
 * e "Rossi" sono la stessa persona) e si salvano con l'iniziale
 * maiuscola.
 *
 * Comandi:
 *     I nome     iscrizione
 *     R nome     ritiro
 *     E          elenco
 *     Q          fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char testo[20];
} Nome;

typedef struct {
    Nome *dati;
    int n;
    int capacita;
} Elenco;

Elenco *crea_elenco(int capacita);
int aggiungi_se_manca(Elenco *e, const char *nome);
int rimuovi_valore(Elenco *e, const char *nome);
int cerca(const Elenco *e, const char *nome);
int lunghezza(const Elenco *e);
Nome elemento(const Elenco *e, int i);
void distruggi_elenco(Elenco *e);
void sistema(char nome[]);

int main(void)
{
    Elenco *volontari = crea_elenco(2);
    char nome[20];
    char comando = ' ';
    int esito;
    int i;

    if (volontari == NULL) {
        printf("Memoria insufficiente.\n");
        comando = 'Q';
    }
    while (comando != 'Q') {
        printf("Comando (I, R, E, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'I' || comando == 'R') {
            if (scanf("%19s", nome) != 1) {
                printf("  Nome mancante.\n");
            } else {
                sistema(nome);
                if (comando == 'I') {
                    esito = aggiungi_se_manca(volontari, nome);
                    if (esito == 1) {
                        printf("  iscrizione di %s (volontari: %d)\n", nome, lunghezza(volontari));
                    } else if (esito == 0) {
                        printf("  %s e' gia' nell'elenco\n", nome);
                    } else {
                        printf("  Memoria insufficiente.\n");
                    }
                } else if (rimuovi_valore(volontari, nome)) {
                    printf("  ritiro di %s (volontari: %d)\n", nome, lunghezza(volontari));
                } else {
                    printf("  %s non e' nell'elenco\n", nome);
                }
            }
        } else if (comando == 'E') {
            for (i = 0; i < lunghezza(volontari); i++) {
                printf("  %d. %s\n", i + 1, elemento(volontari, i).testo);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q' && comando != 'E') {
            scanf("%*[^\n]");
        }
    }
    distruggi_elenco(volontari);

    return 0;
}

Elenco *crea_elenco(int capacita)
{
    Elenco *e = malloc(sizeof *e);

    if (e != NULL) {
        e->dati = malloc(capacita * sizeof *e->dati);
        if (e->dati == NULL) {
            free(e);
            e = NULL;
        } else {
            e->n = 0;
            e->capacita = capacita;
        }
    }
    return e;
}

int aggiungi_se_manca(Elenco *e, const char *nome)
{
    Nome *tmp;
    int esito = 1;

    if (cerca(e, nome) != -1) {
        esito = 0;
    } else if (e->n == e->capacita) {
        tmp = realloc(e->dati, 2 * e->capacita * sizeof *tmp);
        if (tmp == NULL) {
            esito = -1;
        } else {
            e->dati = tmp;
            e->capacita = 2 * e->capacita;
        }
    }
    if (esito == 1) {
        strcpy(e->dati[e->n].testo, nome);
        e->n++;
    }
    return esito;
}

int rimuovi_valore(Elenco *e, const char *nome)
{
    int posizione = cerca(e, nome);
    int i;

    if (posizione != -1) {
        for (i = posizione; i < e->n - 1; i++) {
            e->dati[i] = e->dati[i + 1];
        }
        e->n--;
    }
    return posizione != -1;
}

int cerca(const Elenco *e, const char *nome)
{
    int trovato = -1;
    int i;

    for (i = 0; i < e->n && trovato == -1; i++) {
        if (strcmp(e->dati[i].testo, nome) == 0) {
            trovato = i;
        }
    }
    return trovato;
}

int lunghezza(const Elenco *e)
{
    return e->n;
}

Nome elemento(const Elenco *e, int i)
{
    return e->dati[i];
}

void distruggi_elenco(Elenco *e)
{
    if (e != NULL) {
        free(e->dati);
        free(e);
    }
}

/* Iniziale maiuscola, resto minuscolo: così il confronto è uniforme. */
void sistema(char nome[])
{
    int i;

    for (i = 0; nome[i] != '\0'; i++) {
        if (i == 0) {
            nome[i] = (char) toupper((unsigned char) nome[i]);
        } else {
            nome[i] = (char) tolower((unsigned char) nome[i]);
        }
    }
}
