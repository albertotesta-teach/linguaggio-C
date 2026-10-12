/*
 * 030-typedef-struct.c
 *
 * typedef e struct: un nome comodo per un tipo davvero nuovo
 *
 * Nel sottocapitolo 01-typedef Euro e Chilometri erano due nomi dello
 * stesso double, e il compilatore li mescolava senza dire nulla. Con
 * struct ogni dichiarazione crea un tipo NUOVO, diverso da tutti gli altri
 * anche se ha gli stessi campi:
 *
 *     typedef struct {
 *         double valore;
 *     } Euro;
 *
 *     typedef struct {
 *         double valore;
 *     } Chilometri;
 *
 *     Euro prezzo = {1.79};
 *     Chilometri distanza = {290};
 *     prezzo = distanza;           errore: tipi incompatibili
 *
 * Le due forme per dare il nome:
 *     struct studente { ... };                 il tipo si chiama "struct studente"
 *     typedef struct { ... } Studente;         il tipo si chiama "Studente"
 * Da qui in poi il corso usa la seconda forma, con l'iniziale maiuscola.
 */

#include <stdio.h>

typedef struct {
    double valore;
} Euro;

typedef struct {
    double valore;
} Chilometri;

typedef struct {
    double valore;
} KmPerLitro;

/* forma con il nome dopo struct: si può usare anche "struct gita" */
typedef struct gita {
    char meta[20];
    int studenti;
} Gita;

int main(void)
{
    Gita uscita = {"Genova", 46};
    struct gita stessa_uscita = {"Genova", 46};
    Chilometri distanza = {2 * 145.0};
    KmPerLitro consumo = {3.5};
    Euro prezzo = {1.79};
    Euro costo;

    /* prezzo = distanza;      errore: incompatible types when assigning
     *                          to type 'Euro' from type 'Chilometri' */

    costo.valore = distanza.valore / consumo.valore * prezzo.valore;

    printf("Gita a %s per %d studenti (stesso tipo: %s, %d)\n",
           uscita.meta, uscita.studenti, stessa_uscita.meta, stessa_uscita.studenti);
    printf("Distanza %.0f km, consumo %.1f km/l, gasolio %.2f euro/l\n",
           distanza.valore, consumo.valore, prezzo.valore);
    printf("Costo del carburante: %.2f euro\n", costo.valore);
    printf("Per persona: %.2f euro\n", costo.valore / uscita.studenti);

    printf("\nEuro, Chilometri e KmPerLitro hanno lo stesso campo double,\n"
           "ma sono tre tipi diversi: assegnarne uno a un altro e' un errore.\n");

    return 0;
}
