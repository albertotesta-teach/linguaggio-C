/*
 * 010-vettore-di-struct.c
 *
 * Un vettore dinamico di struct e il puntatore a un suo elemento
 *
 * Il vettore contiene struct Studente. Per modificare un elemento senza
 * copiarlo, la funzione elemento restituisce un PUNTATORE alla struct
 * dentro il vettore:
 *
 *     Studente *elemento(Classe *c, int i)
 *     {
 *         return &c->dati[i];
 *     }
 *
 *     Studente *s = elemento(classe, 0);
 *     s->assenze++;                   modifica direttamente il vettore
 *
 * Attenzione: il puntatore punta dentro il blocco c->dati. Se aggiungi
 * deve crescere, realloc può spostare il blocco altrove e il vecchio
 * puntatore resta "appeso" a memoria liberata:
 *
 *     Studente *s = elemento(classe, 0);
 *     aggiungi(classe, nuovo);        può chiamare realloc
 *     s->assenze++;                   ERRORE se il blocco si è spostato
 *
 * Regola: il puntatore restituito da elemento vale solo fino alla
 * prossima aggiunta. Dopo un'aggiunta si richiede di nuovo.
 *
 * Il programma stampa l'indirizzo del blocco prima e dopo le aggiunte
 * per mostrare quando si sposta, poi usa il puntatore nel modo corretto.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[20];
    int assenze;
} Studente;

typedef struct {
    Studente *dati;
    int n;
    int capacita;
} Classe;

Classe *crea_classe(int capacita);
int aggiungi(Classe *c, Studente s);
int lunghezza(const Classe *c);
int capacita(const Classe *c);
Studente *elemento(Classe *c, int i);
void distruggi_classe(Classe *c);
Studente nuovo_studente(const char *nome);

int main(void)
{
    Classe *classe = crea_classe(2);
    const char *nomi[] = {"Bianchi", "Rossi", "Verdi", "Neri", "Russo"};
    Studente *s;
    void *prima;
    int ok;
    int i;

    if (classe == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        ok = 1;
        for (i = 0; i < 5 && ok; i++) {
            prima = (void *) elemento(classe, 0);
            ok = aggiungi(classe, nuovo_studente(nomi[i]));
            if (ok) {
                printf("aggiunto %-8s  capacita %d  primo elemento a %p", nomi[i],
                       capacita(classe), (void *) elemento(classe, 0));
                if (i > 0 && prima != (void *) elemento(classe, 0)) {
                    printf("  <- blocco spostato");
                }
                printf("\n");
            }
        }
        if (!ok) {
            printf("Memoria insufficiente.\n");
        }

        /* Uso corretto: si chiede il puntatore DOPO l'ultima aggiunta. */
        s = elemento(classe, 1);
        s->assenze += 3;
        s = elemento(classe, 3);
        s->assenze += 1;

        printf("\nRegistro delle assenze:\n");
        for (i = 0; i < lunghezza(classe); i++) {
            s = elemento(classe, i);
            printf("  %-8s %d\n", s->nome, s->assenze);
        }
    }
    distruggi_classe(classe);

    return 0;
}

Classe *crea_classe(int capacita)
{
    Classe *c = malloc(sizeof *c);

    if (c != NULL) {
        c->dati = malloc(capacita * sizeof *c->dati);
        if (c->dati == NULL) {
            free(c);
            c = NULL;
        } else {
            c->n = 0;
            c->capacita = capacita;
        }
    }
    return c;
}

int aggiungi(Classe *c, Studente s)
{
    Studente *tmp;
    int ok = 1;

    if (c->n == c->capacita) {
        tmp = realloc(c->dati, 2 * c->capacita * sizeof *tmp);
        if (tmp == NULL) {
            ok = 0;
        } else {
            c->dati = tmp;
            c->capacita = 2 * c->capacita;
        }
    }
    if (ok) {
        c->dati[c->n] = s;
        c->n++;
    }
    return ok;
}

int lunghezza(const Classe *c)
{
    return c->n;
}

int capacita(const Classe *c)
{
    return c->capacita;
}

/* Puntatore all'elemento i: valido solo fino alla prossima aggiunta. */
Studente *elemento(Classe *c, int i)
{
    return &c->dati[i];
}

void distruggi_classe(Classe *c)
{
    if (c != NULL) {
        free(c->dati);
        free(c);
    }
}

Studente nuovo_studente(const char *nome)
{
    Studente s;

    strncpy(s.nome, nome, sizeof s.nome - 1);
    s.nome[sizeof s.nome - 1] = '\0';
    s.assenze = 0;
    return s;
}
