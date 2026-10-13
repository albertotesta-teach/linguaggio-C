/*
 * 040-problema-registro-dei-ritardi.c
 *
 * Gli ingressi in ritardo dell'anno scolastico
 *
 * Il collaboratore all'ingresso registra ogni studente che entra in
 * ritardo: data, nome e minuti. Quanti ingressi ci saranno in un anno non
 * si sa: le registrazioni vanno in un vettore dinamico di struct.
 *
 *     typedef struct {
 *         int giorno;
 *         int mese;
 *         char studente[20];
 *         int minuti;
 *     } Ritardo;
 *
 *     typedef struct {
 *         Ritardo *dati;
 *         int n;
 *         int capacita;
 *     } Registro;
 *
 * Il programma usa il registro solo con le sue funzioni (crea, aggiungi,
 * lunghezza, elemento, distruggi); aggiungi raddoppia la capacità quando
 * il registro è pieno (parte da 4 posti). Il programma legge righe
 * "gg/mm nome minuti" fino a FINE, poi stampa:
 *   - gli ingressi per mese, da settembre a giugno;
 *   - la data con più ingressi in ritardo;
 *   - gli studenti con almeno 3 ritardi (avviso alla famiglia).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AVVISO 3

typedef struct {
    int giorno;
    int mese;
    char studente[20];
    int minuti;
} Ritardo;

typedef struct {
    Ritardo *dati;
    int n;
    int capacita;
} Registro;

Registro *crea_registro(int capacita);
int aggiungi(Registro *r, Ritardo nuovo);
void distruggi_registro(Registro *r);
int lunghezza(const Registro *r);
int capacita(const Registro *r);
Ritardo elemento(const Registro *r, int i);
int data_valida(int giorno, int mese);
int conta_studente(const Registro *r, const char *nome, int fino_a);
int conta_data(const Registro *r, int giorno, int mese);

int main(void)
{
    const char *nomi_mesi[12] = {"gen", "feb", "mar", "apr", "mag", "giu",
                                 "lug", "ago", "set", "ott", "nov", "dic"};
    const int ordine[10] = {9, 10, 11, 12, 1, 2, 3, 4, 5, 6};
    Registro *registro = crea_registro(4);
    Ritardo r;
    char parola[16];
    int per_mese[13] = {0};
    int finito = 0;
    int massimo = 0;
    int peggiore = -1;
    int conta;
    int i;
    int k;

    if (registro == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        printf("Ritardi (gg/mm nome minuti, FINE per terminare):\n");
        while (!finito) {
            if (scanf("%15s", parola) != 1 || strcmp(parola, "FINE") == 0) {
                finito = 1;
            } else if (sscanf(parola, "%d/%d", &r.giorno, &r.mese) != 2 ||
                       scanf("%19s %d", r.studente, &r.minuti) != 2 ||
                       !data_valida(r.giorno, r.mese) || r.minuti < 1) {
                printf("  riga non valida\n");
                scanf("%*[^\n]");
            } else if (!aggiungi(registro, r)) {
                printf("  Memoria insufficiente.\n");
                finito = 1;
            }
        }

        printf("\nIngressi in ritardo: %d (capacita' %d)\n", lunghezza(registro),
               capacita(registro));
        for (i = 0; i < lunghezza(registro); i++) {
            per_mese[elemento(registro, i).mese]++;
            conta = conta_data(registro, elemento(registro, i).giorno, elemento(registro, i).mese);
            if (conta > massimo) {
                massimo = conta;
                peggiore = i;
            }
        }
        for (k = 0; k < 10; k++) {
            printf("  %s %2d\n", nomi_mesi[ordine[k] - 1], per_mese[ordine[k]]);
        }
        if (peggiore != -1) {
            printf("Data con piu' ritardi: %02d/%02d (%d)\n", elemento(registro, peggiore).giorno,
                   elemento(registro, peggiore).mese, massimo);
        }
        printf("Avviso alla famiglia (almeno %d ritardi):\n", AVVISO);
        for (i = 0; i < lunghezza(registro); i++) {
            r = elemento(registro, i);
            conta = conta_studente(registro, r.studente, lunghezza(registro));
            if (conta_studente(registro, r.studente, i) == 0 && conta >= AVVISO) {
                printf("  %s: %d ritardi\n", r.studente, conta);
            }
        }
        distruggi_registro(registro);
    }

    return 0;
}

Registro *crea_registro(int capacita)
{
    Registro *r = malloc(sizeof *r);

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

int aggiungi(Registro *r, Ritardo nuovo)
{
    Ritardo *tmp;
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
        r->dati[r->n] = nuovo;
        r->n++;
    }
    return ok;
}

void distruggi_registro(Registro *r)
{
    if (r != NULL) {
        free(r->dati);
        free(r);
    }
}

int lunghezza(const Registro *r)
{
    return r->n;
}

int capacita(const Registro *r)
{
    return r->capacita;
}

/* L'elemento i (0 <= i < lunghezza): una copia della struct. */
Ritardo elemento(const Registro *r, int i)
{
    return r->dati[i];
}

/* Mesi di scuola (settembre-giugno) e giorno da 1 a 31. */
/* Giorno esistente in un mese di scuola (luglio e agosto esclusi). */
int data_valida(int giorno, int mese)
{
    const int giorni_mese[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    return mese >= 1 && mese <= 12 && mese != 7 && mese != 8 && giorno >= 1 &&
           giorno <= giorni_mese[mese];
}

/* Ritardi dello studente tra le prime fino_a registrazioni. */
int conta_studente(const Registro *r, const char *nome, int fino_a)
{
    int conta = 0;
    int i;

    for (i = 0; i < fino_a; i++) {
        if (strcmp(r->dati[i].studente, nome) == 0) {
            conta++;
        }
    }
    return conta;
}

int conta_data(const Registro *r, int giorno, int mese)
{
    int conta = 0;
    int i;

    for (i = 0; i < r->n; i++) {
        if (r->dati[i].giorno == giorno && r->dati[i].mese == mese) {
            conta++;
        }
    }
    return conta;
}
