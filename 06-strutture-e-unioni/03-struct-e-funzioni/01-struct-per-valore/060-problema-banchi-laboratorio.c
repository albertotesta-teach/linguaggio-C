/*
 * 060-problema-banchi-laboratorio.c
 *
 * Laboratorio di chimica: i banchi sulla pianta della stanza
 *
 * Per riorganizzare il laboratorio il tecnico disegna i banchi sulla
 * pianta (misure in centimetri). Ogni banco è un rettangolo con i lati
 * paralleli alle pareti, descritto dall'angolo in basso a sinistra e dalle
 * dimensioni:
 *
 *     typedef struct {
 *         int x;
 *         int y;
 *         int larghezza;
 *         int profondita;
 *     } Rettangolo;
 *
 * Le funzioni ricevono i rettangoli per valore:
 *     int area(Rettangolo r);
 *     int sovrapposti(Rettangolo a, Rettangolo b);         1 se si toccano
 *     Rettangolo intersezione(Rettangolo a, Rettangolo b); parte in comune
 *     int dentro(Rettangolo stanza, Rettangolo r);         1 se r sta nella stanza
 *
 * Il programma legge la posizione di un nuovo banco e controlla che stia
 * nella stanza e che non si sovrapponga ai banchi esistenti; in caso di
 * sovrapposizione stampa l'area in comune.
 */

#include <stdio.h>

#define BANCHI 3

typedef struct {
    int x;
    int y;
    int larghezza;
    int profondita;
} Rettangolo;

int area(Rettangolo r);
int sovrapposti(Rettangolo a, Rettangolo b);
Rettangolo intersezione(Rettangolo a, Rettangolo b);
int dentro(Rettangolo stanza, Rettangolo r);
int minimo(int a, int b);
int massimo(int a, int b);

int main(void)
{
    Rettangolo stanza = {0, 0, 900, 600};
    Rettangolo banchi[BANCHI] = {
        {50, 50, 300, 80},
        {50, 250, 300, 80},
        {500, 50, 120, 400}
    };
    Rettangolo nuovo;
    int b;
    int conflitti = 0;

    printf("Stanza %d x %d cm, banchi esistenti: %d\n", stanza.larghezza, stanza.profondita, BANCHI);
    printf("Nuovo banco (x y larghezza profondita'): ");
    if (scanf("%d %d %d %d", &nuovo.x, &nuovo.y, &nuovo.larghezza, &nuovo.profondita) != 4 ||
        nuovo.larghezza <= 0 || nuovo.profondita <= 0) {
        printf("Dati non validi.\n");
    } else if (!dentro(stanza, nuovo)) {
        printf("Il banco esce dalla stanza.\n");
    } else {
        for (b = 0; b < BANCHI; b++) {
            if (sovrapposti(nuovo, banchi[b])) {
                printf("Si sovrappone al banco %d per %d cm2.\n", b + 1,
                       area(intersezione(nuovo, banchi[b])));
                conflitti++;
            }
        }
        if (conflitti == 0) {
            printf("Posizione libera: banco di %d cm2 sistemato.\n", area(nuovo));
        }
    }

    return 0;
}

int area(Rettangolo r)
{
    return r.larghezza * r.profondita;
}

/* Due rettangoli si sovrappongono se si sovrappongono sia in x sia in y. */
int sovrapposti(Rettangolo a, Rettangolo b)
{
    return a.x < b.x + b.larghezza && b.x < a.x + a.larghezza &&
           a.y < b.y + b.profondita && b.y < a.y + a.profondita;
}

/* Parte comune di due rettangoli sovrapposti. */
Rettangolo intersezione(Rettangolo a, Rettangolo b)
{
    Rettangolo r;

    r.x = massimo(a.x, b.x);
    r.y = massimo(a.y, b.y);
    r.larghezza = minimo(a.x + a.larghezza, b.x + b.larghezza) - r.x;
    r.profondita = minimo(a.y + a.profondita, b.y + b.profondita) - r.y;
    return r;
}

int dentro(Rettangolo stanza, Rettangolo r)
{
    return r.x >= stanza.x && r.y >= stanza.y &&
           r.x + r.larghezza <= stanza.x + stanza.larghezza &&
           r.y + r.profondita <= stanza.y + stanza.profondita;
}

int minimo(int a, int b)
{
    return a < b ? a : b;
}

int massimo(int a, int b)
{
    return a > b ? a : b;
}
