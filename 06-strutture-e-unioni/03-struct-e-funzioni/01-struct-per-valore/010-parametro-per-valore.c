/*
 * 010-parametro-per-valore.c
 *
 * Una struct passata a una funzione arriva come COPIA
 *
 * Una struct si passa a una funzione come un int: il parametro riceve una
 * copia di tutti i campi (anche degli array contenuti nella struct).
 *
 *     void stampa(Tessera t);          t è una copia
 *     void ricarica_sbagliata(Tessera t, double euro);
 *
 * Dentro la funzione si può leggere e modificare la copia, ma le modifiche
 * non arrivano alla variabile del chiamante. Per cambiare la struct del
 * chiamante ci sono due strade:
 *   - restituire la struct modificata (020-struct-restituita);
 *   - passare l'indirizzo della struct (sezione 02-puntatori-a-struct).
 *
 * Esempio: la ricarica della tessera della mensa, prima sbagliata (la
 * copia viene ricaricata, la tessera no) e poi corretta con il valore
 * restituito.
 */

#include <stdio.h>

typedef struct {
    int numero;
    char intestatario[20];
    double credito;
} Tessera;

void stampa(Tessera t);
void ricarica_sbagliata(Tessera t, double euro);
Tessera ricaricata(Tessera t, double euro);

int main(void)
{
    Tessera tessera = {1024, "Bianchi Sara", 3.50};

    stampa(tessera);

    ricarica_sbagliata(tessera, 20.00);
    printf("Dopo ricarica_sbagliata:  ");
    stampa(tessera);

    tessera = ricaricata(tessera, 20.00);
    printf("Dopo tessera = ricaricata(...): ");
    stampa(tessera);

    return 0;
}

void stampa(Tessera t)
{
    printf("tessera %d (%s): credito %.2f euro\n", t.numero, t.intestatario, t.credito);
}

/* Modifica solo la copia locale: il chiamante non vede nulla. */
void ricarica_sbagliata(Tessera t, double euro)
{
    t.credito = t.credito + euro;
    printf("  dentro la funzione la copia ha %.2f euro\n", t.credito);
}

/* Restituisce una nuova Tessera con il credito aumentato. */
Tessera ricaricata(Tessera t, double euro)
{
    t.credito = t.credito + euro;
    return t;
}
