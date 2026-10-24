/*
 * 060-problema-menu-a-funzioni.c
 *
 * Borsellino elettronico della mensa: un menu fatto di funzioni
 *
 * Ogni studente ha un credito sulla tessera della mensa, in centesimi. Il
 * totem all'ingresso offre un menu numerato:
 *     1  ricarica           (da 5 a 50 euro)
 *     2  paga il pasto      (5.20 euro)
 *     3  paga la merenda    (1.50 euro)
 *     4  mostra il saldo
 *     0  esci
 *
 * Ogni voce è una funzione con lo stesso prototipo: riceve l'indirizzo del
 * credito, così può modificarlo.
 *
 *     typedef void (*Azione)(int *credito);
 *     Azione azioni[VOCI] = {ricarica, paga_pasto, paga_merenda, mostra_saldo};
 *
 * Il main non contiene una catena di if per ogni voce: stampa il menu dai
 * nomi, legge la scelta e chiama azioni[scelta - 1](&credito). Per
 * aggiungere una voce basta scrivere la funzione e inserirla nei due
 * array. Un pagamento con credito insufficiente viene rifiutato.
 */

#include <stdio.h>

#define VOCI 4
#define PASTO   520
#define MERENDA 150

typedef void (*Azione)(int *credito);

void ricarica(int *credito);
void paga_pasto(int *credito);
void paga_merenda(int *credito);
void mostra_saldo(int *credito);
void paga(int *credito, int importo, const char *cosa);
void svuota_riga(void);

int main(void)
{
    const char *voci[VOCI] = {"ricarica", "paga il pasto", "paga la merenda", "mostra il saldo"};
    Azione azioni[VOCI] = {ricarica, paga_pasto, paga_merenda, mostra_saldo};
    int credito = 830;
    int scelta = 1;
    int v;
    int letti;

    while (scelta != 0) {
        printf("\n");
        for (v = 0; v < VOCI; v++) {
            printf("  %d  %s\n", v + 1, voci[v]);
        }
        printf("  0  esci\nScelta: ");
        letti = scanf("%d", &scelta);
        if (letti == EOF) {
            scelta = 0;                 /* input terminato: come esci */
        } else if (letti == 0) {
            svuota_riga();              /* non e' un numero */
            scelta = -1;                /* voce inesistente */
        }
        if (scelta >= 1 && scelta <= VOCI) {
            azioni[scelta - 1](&credito);
        } else if (scelta != 0) {
            printf("  Voce inesistente.\n");
        }
    }
    printf("Arrivederci. Credito residuo: %d.%02d euro\n", credito / 100, credito % 100);

    return 0;
}

void ricarica(int *credito)
{
    int euro;
    int letti;

    printf("  Importo in euro (5-50): ");
    letti = scanf("%d", &euro);
    if (letti == 0) {
        svuota_riga();                  /* non e' un numero */
    }
    if (letti == 1 && euro >= 5 && euro <= 50) {
        *credito = *credito + euro * 100;
        printf("  Ricarica di %d euro eseguita.\n", euro);
    } else {
        printf("  Importo non valido.\n");
    }
}

void paga_pasto(int *credito)
{
    paga(credito, PASTO, "pasto");
}

void paga_merenda(int *credito)
{
    paga(credito, MERENDA, "merenda");
}

/* Il prototipo è quello di Azione anche se il credito viene solo letto. */
void mostra_saldo(int *credito)
{
    printf("  Saldo: %d.%02d euro\n", *credito / 100, *credito % 100);
}

/* Scala l'importo se il credito basta, altrimenti rifiuta il pagamento. */
void paga(int *credito, int importo, const char *cosa)
{
    if (*credito >= importo) {
        *credito = *credito - importo;
        printf("  Pagato: %s %d.%02d euro.\n", cosa, importo / 100, importo % 100);
    } else {
        printf("  Credito insufficiente per %s: servono %d.%02d euro.\n", cosa,
               importo / 100, importo % 100);
    }
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
