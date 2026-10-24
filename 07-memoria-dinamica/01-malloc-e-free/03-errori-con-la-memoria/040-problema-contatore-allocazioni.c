/*
 * 040-problema-contatore-allocazioni.c
 *
 * Un registro delle allocazioni per trovare perdite e doppi free
 *
 * Nel progetto di gruppo del registro di classe ognuno scrive la sua
 * parte e nessuno sa più quali blocchi sono stati liberati. Si decide
 * allora di non chiamare direttamente malloc e free, ma due funzioni che
 * tengono un registro:
 *
 *     int registra_malloc(Registro *r, size_t byte, const char *uso);
 *     int registra_free(Registro *r, int numero);
 *
 * registra_malloc chiama malloc, annota indirizzo, byte e uso del blocco
 * e restituisce il numero del blocco (da 1). registra_free libera il
 * blocco con quel numero, ma solo se è ancora attivo: un secondo free
 * dello stesso blocco viene segnalato e non eseguito.
 *
 *     typedef struct {
 *         void *indirizzo;
 *         size_t byte;
 *         char uso[24];
 *         int attivo;
 *     } Voce;
 *
 *     typedef struct {
 *         Voce voci[MAX_BLOCCHI];
 *         int n;
 *         size_t byte_attivi;
 *         size_t picco;          massimo di byte attivi raggiunto
 *     } Registro;
 *
 * void * è un puntatore "generico": può contenere l'indirizzo di
 * qualunque blocco, ed è il tipo che malloc restituisce e free riceve.
 *
 * Comandi (simulano le richieste delle varie parti del programma):
 *     A byte uso    alloca un blocco
 *     L numero      libera il blocco con quel numero
 *     R             rapporto dei blocchi ancora attivi
 *     Q             fine: rapporto delle perdite, poi libera tutto
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BLOCCHI 20
#define MAX_BYTE 100000

typedef struct {
    void *indirizzo;
    size_t byte;
    char uso[24];
    int attivo;
} Voce;

typedef struct {
    Voce voci[MAX_BLOCCHI];
    int n;
    size_t byte_attivi;
    size_t picco;
} Registro;

int registra_malloc(Registro *r, size_t byte, const char *uso);
int registra_free(Registro *r, int numero);
int rapporto(const Registro *r);
void libera_tutto(Registro *r);

int main(void)
{
    Registro registro;
    char comando = ' ';
    char uso[24];
    long byte;
    int numero;
    int esito;

    registro.n = 0;
    registro.byte_attivi = 0;
    registro.picco = 0;

    while (comando != 'Q') {
        printf("Comando (A, L, R, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';              /* input terminato: come Q */
        }
        comando = (char) toupper((unsigned char) comando);
        if (comando == 'A') {
            if (scanf("%ld %23s", &byte, uso) != 2 || byte < 1 || byte > MAX_BYTE) {
                printf("  Richiesta non valida.\n");
            } else {
                numero = registra_malloc(&registro, (size_t) byte, uso);
                if (numero == 0) {
                    printf("  Allocazione non riuscita.\n");
                } else {
                    printf("  blocco %d: %ld byte per %s\n", numero, byte, uso);
                }
            }
        } else if (comando == 'L') {
            if (scanf("%d", &numero) != 1) {
                printf("  Numero non valido.\n");
            } else {
                esito = registra_free(&registro, numero);
                if (esito == 1) {
                    printf("  blocco %d liberato\n", numero);
                } else if (esito == 0) {
                    printf("  blocco %d gia' liberato: doppio free evitato\n", numero);
                } else {
                    printf("  blocco %d inesistente\n", numero);
                }
            }
        } else if (comando == 'R') {
            rapporto(&registro);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
        if (comando != 'Q') {
            scanf("%*[^\n]");          /* un comando per riga */
        }
    }

    printf("\nFine del programma\n");
    if (rapporto(&registro) > 0) {
        printf("  Il programma avrebbe perso questi blocchi: li libera il registro.\n");
    }
    libera_tutto(&registro);
    printf("  Picco di memoria: %zu byte\n", registro.picco);

    return 0;
}

/* Numero del nuovo blocco (da 1), 0 se il registro è pieno o malloc
   fallisce. */
int registra_malloc(Registro *r, size_t byte, const char *uso)
{
    int numero = 0;
    void *blocco;

    if (r->n < MAX_BLOCCHI) {
        blocco = malloc(byte);
        if (blocco != NULL) {
            r->voci[r->n].indirizzo = blocco;
            r->voci[r->n].byte = byte;
            strcpy(r->voci[r->n].uso, uso);
            r->voci[r->n].attivo = 1;
            r->n++;
            numero = r->n;
            r->byte_attivi = r->byte_attivi + byte;
            if (r->byte_attivi > r->picco) {
                r->picco = r->byte_attivi;
            }
        }
    }
    return numero;
}

/* 1 liberato, 0 già liberato prima, -1 numero inesistente. */
int registra_free(Registro *r, int numero)
{
    int esito = -1;
    Voce *v;

    if (numero >= 1 && numero <= r->n) {
        v = &r->voci[numero - 1];
        if (v->attivo) {
            free(v->indirizzo);
            v->indirizzo = NULL;
            v->attivo = 0;
            r->byte_attivi = r->byte_attivi - v->byte;
            esito = 1;
        } else {
            esito = 0;
        }
    }
    return esito;
}

/* Stampa i blocchi ancora attivi e restituisce quanti sono. */
int rapporto(const Registro *r)
{
    int attivi = 0;
    int i;

    printf("  Blocchi allocati: %d, ancora attivi:\n", r->n);
    for (i = 0; i < r->n; i++) {
        if (r->voci[i].attivo) {
            printf("    %2d  %6zu byte  %s\n", i + 1, r->voci[i].byte, r->voci[i].uso);
            attivi++;
        }
    }
    if (attivi == 0) {
        printf("    nessuno\n");
    }
    printf("  Byte attivi: %zu\n", r->byte_attivi);
    return attivi;
}

void libera_tutto(Registro *r)
{
    int i;

    for (i = 1; i <= r->n; i++) {
        registra_free(r, i);
    }
}
