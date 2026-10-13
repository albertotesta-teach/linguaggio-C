/*
 * 040-problema-rubrica-della-classe.c
 *
 * La rubrica della classe: aggiungere, cercare, modificare, cancellare
 *
 * Il rappresentante di classe tiene i contatti dei compagni per le
 * comunicazioni urgenti. La rubrica è un vettore dinamico di Contatto:
 *
 *     typedef struct {
 *         char nome[20];
 *         char telefono[16];
 *     } Contatto;
 *
 * Le quattro operazioni classiche su un elenco:
 *
 *     A nome telefono    aggiunta (nome già presente: rifiutata)
 *     C testo            ricerca: tutti i nomi che iniziano con testo
 *     M nome telefono    modifica del telefono
 *     D nome             cancellazione
 *     E                  elenco completo
 *     Q                  fine
 *
 * Per la modifica la funzione trova restituisce un puntatore al contatto
 * dentro il vettore (NULL se manca): il nuovo telefono si scrive
 * direttamente lì. Il puntatore si usa subito, prima di qualsiasi
 * aggiunta, perché un'aggiunta può spostare il blocco.
 *
 * La cancellazione toglie il contatto spostando indietro i successivi,
 * così l'elenco resta nell'ordine di inserimento.
 *
 * Un telefono valido ha solo cifre, da 6 a 15.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char nome[20];
    char telefono[16];
} Contatto;

typedef struct {
    Contatto *dati;
    int n;
    int capacita;
} Rubrica;

Rubrica *crea_rubrica(int capacita);
int aggiungi(Rubrica *r, Contatto c);
int rimuovi(Rubrica *r, int posizione);
int lunghezza(const Rubrica *r);
Contatto *elemento(Rubrica *r, int i);
int cerca(const Rubrica *r, const char *nome);
Contatto *trova(Rubrica *r, const char *nome);
void distruggi_rubrica(Rubrica *r);
int telefono_valido(const char *telefono);
int inizia_con(const char *nome, const char *testo);

int main(void)
{
    Rubrica *rubrica = crea_rubrica(2);
    Contatto c;
    Contatto *p;
    char comando = ' ';
    char testo[20];
    int trovati;
    int i;

    if (rubrica == NULL) {
        printf("Memoria insufficiente.\n");
        comando = 'Q';
    }
    while (comando != 'Q') {
        printf("Comando (A, C, M, D, E, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'A' || comando == 'M') {
            if (scanf("%19s %15s", c.nome, c.telefono) != 2 || !telefono_valido(c.telefono)) {
                printf("  Dati non validi.\n");
            } else if (comando == 'A') {
                if (trova(rubrica, c.nome) != NULL) {
                    printf("  %s e' gia' in rubrica.\n", c.nome);
                } else if (!aggiungi(rubrica, c)) {
                    printf("  Memoria insufficiente.\n");
                } else {
                    printf("  aggiunto %s (contatti: %d)\n", c.nome, lunghezza(rubrica));
                }
            } else {
                p = trova(rubrica, c.nome);
                if (p == NULL) {
                    printf("  %s non e' in rubrica.\n", c.nome);
                } else {
                    printf("  %s: %s -> %s\n", p->nome, p->telefono, c.telefono);
                    strcpy(p->telefono, c.telefono);
                }
            }
        } else if (comando == 'C') {
            trovati = 0;
            if (scanf("%19s", testo) == 1) {
                for (i = 0; i < lunghezza(rubrica); i++) {
                    p = elemento(rubrica, i);
                    if (inizia_con(p->nome, testo)) {
                        printf("  %-12s %s\n", p->nome, p->telefono);
                        trovati++;
                    }
                }
            }
            if (trovati == 0) {
                printf("  Nessun contatto trovato.\n");
            }
        } else if (comando == 'D') {
            i = -1;
            if (scanf("%19s", testo) == 1) {
                i = cerca(rubrica, testo);
            }
            if (i == -1) {
                printf("  Contatto non trovato.\n");
            } else {
                rimuovi(rubrica, i);
                printf("  cancellato %s (contatti: %d)\n", testo, lunghezza(rubrica));
            }
        } else if (comando == 'E') {
            printf("  Contatti in rubrica: %d\n", lunghezza(rubrica));
            for (i = 0; i < lunghezza(rubrica); i++) {
                p = elemento(rubrica, i);
                printf("  %2d. %-12s %s\n", i + 1, p->nome, p->telefono);
            }
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q' && comando != 'E') {
            scanf("%*[^\n]");
        }
    }
    distruggi_rubrica(rubrica);

    return 0;
}

Rubrica *crea_rubrica(int capacita)
{
    Rubrica *r = malloc(sizeof *r);

    if (r != NULL) {
        r->dati = malloc(capacita * sizeof *r->dati);
        if (r->dati == NULL) {
            free(r);
            r = NULL;
        } else {
            r->n = 0;
            r->capacita = capacita;
        }
    }
    return r;
}

int aggiungi(Rubrica *r, Contatto c)
{
    Contatto *tmp;
    int ok = 1;

    if (r->n == r->capacita) {
        tmp = realloc(r->dati, 2 * r->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            r->dati = tmp;
            r->capacita = 2 * r->capacita;
        }
    }
    if (ok) {
        r->dati[r->n] = c;
        r->n++;
    }
    return ok;
}

int rimuovi(Rubrica *r, int posizione)
{
    int ok = posizione >= 0 && posizione < r->n;
    int i;

    if (ok) {
        for (i = posizione; i < r->n - 1; i++) {
            r->dati[i] = r->dati[i + 1];
        }
        r->n--;
    }
    return ok;
}

int lunghezza(const Rubrica *r)
{
    return r->n;
}

/* Puntatore al contatto i: valido solo fino alla prossima aggiunta. */
Contatto *elemento(Rubrica *r, int i)
{
    return &r->dati[i];
}

int cerca(const Rubrica *r, const char *nome)
{
    int trovato = -1;
    int i;

    for (i = 0; i < r->n && trovato == -1; i++) {
        if (strcmp(r->dati[i].nome, nome) == 0) {
            trovato = i;
        }
    }
    return trovato;
}

/* Puntatore al contatto con quel nome, NULL se non c'è. */
Contatto *trova(Rubrica *r, const char *nome)
{
    int posizione = cerca(r, nome);
    Contatto *p = NULL;

    if (posizione != -1) {
        p = elemento(r, posizione);
    }
    return p;
}

void distruggi_rubrica(Rubrica *r)
{
    if (r != NULL) {
        free(r->dati);
        free(r);
    }
}

int telefono_valido(const char *telefono)
{
    int lunghezza_tel = (int) strlen(telefono);
    int valido = lunghezza_tel >= 6 && lunghezza_tel <= 15;
    int i;

    for (i = 0; i < lunghezza_tel && valido; i++) {
        valido = isdigit((unsigned char) telefono[i]);
    }
    return valido;
}

int inizia_con(const char *nome, const char *testo)
{
    return strncmp(nome, testo, strlen(testo)) == 0;
}
