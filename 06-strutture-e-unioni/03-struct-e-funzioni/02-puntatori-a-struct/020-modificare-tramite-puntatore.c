/*
 * 020-modificare-tramite-puntatore.c
 *
 * Una funzione che modifica la struct del chiamante
 *
 * Per modificare un int del chiamante una funzione riceve un int *. Allo
 * stesso modo, per modificare una struct riceve l'indirizzo della struct:
 *
 *     void ricarica(Tessera *t, double euro);
 *     ricarica(&tessera, 20.00);
 *
 *     dentro la funzione:  t->credito = t->credito + euro;
 *
 * Rispetto al passaggio per valore (sezione 01-struct-per-valore):
 *   - non si copia la struct, si passano solo 8 byte;
 *   - le modifiche arrivano al chiamante, senza bisogno di return;
 *   - il valore restituito resta libero per l'esito dell'operazione.
 *
 * Esempio: la tessera della mensa. ricarica modifica il credito; paga
 * restituisce 1 se il pagamento è riuscito e 0 se il credito non basta,
 * e in quel caso la tessera non cambia.
 */

#include <stdio.h>

typedef struct {
    int numero;
    char intestatario[20];
    double credito;
    int pasti;
} Tessera;

void ricarica(Tessera *t, double euro);
int paga(Tessera *t, double prezzo);
void stampa(Tessera t);

int main(void)
{
    Tessera tessera = {1024, "Bianchi Sara", 3.50, 0};

    stampa(tessera);

    ricarica(&tessera, 10.00);
    printf("Dopo ricarica(&tessera, 10.00): ");
    stampa(tessera);

    if (paga(&tessera, 5.20)) {
        printf("Primo pasto pagato:  ");
        stampa(tessera);
    }
    if (paga(&tessera, 5.20)) {
        printf("Secondo pasto pagato: ");
        stampa(tessera);
    }
    if (!paga(&tessera, 5.20)) {
        printf("Terzo pasto rifiutato: credito insufficiente. ");
        stampa(tessera);
    }

    return 0;
}

void ricarica(Tessera *t, double euro)
{
    t->credito = t->credito + euro;
}

/* Scala il prezzo solo se il credito basta; restituisce l'esito. */
int paga(Tessera *t, double prezzo)
{
    int riuscito = t->credito >= prezzo;

    if (riuscito) {
        t->credito = t->credito - prezzo;
        t->pasti++;
    }
    return riuscito;
}

void stampa(Tessera t)
{
    printf("tessera %d: credito %.2f euro, pasti consumati %d\n", t.numero, t.credito, t.pasti);
}
