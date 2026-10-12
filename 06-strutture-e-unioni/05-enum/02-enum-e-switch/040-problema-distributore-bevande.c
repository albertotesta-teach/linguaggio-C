/*
 * 040-problema-distributore-bevande.c
 *
 * Il distributore di bevande calde del corridoio
 *
 * Il distributore ha quattro bevande, scelte con un numero da 1 a 4, e
 * accetta monete da 5 a 200 centesimi. Due enum:
 *
 *     typedef enum { CAFFE, CAPPUCCINO, TE, CIOCCOLATA, NUM_BEVANDE } Bevanda;
 *     typedef enum { EROGATA, CREDITO_INSUFFICIENTE, ESAURITA } Esito;
 *
 *     int prezzo(Bevanda b);                    switch su Bevanda
 *     Esito eroga(Bevanda b, int *credito, int scorte[]);
 *     const char *messaggio(Esito e);           switch su Esito
 *
 * eroga controlla scorte e credito, scala il prezzo e restituisce
 * l'esito; il main stampa il messaggio corrispondente.
 *
 * Comandi:
 *     M centesimi    inserisce una moneta (5, 10, 20, 50, 100, 200)
 *     B numero       sceglie la bevanda (1 caffè, 2 cappuccino, 3 tè,
 *                    4 cioccolata)
 *     R              restituisce il credito rimasto
 *     Q              fine
 */

#include <stdio.h>

typedef enum {
    CAFFE, CAPPUCCINO, TE, CIOCCOLATA, NUM_BEVANDE
} Bevanda;

typedef enum {
    EROGATA, CREDITO_INSUFFICIENTE, ESAURITA
} Esito;

int prezzo(Bevanda b);
const char *nome(Bevanda b);
Esito eroga(Bevanda b, int *credito, int scorte[]);
const char *messaggio(Esito e);
int moneta_valida(int centesimi);

int main(void)
{
    int scorte[NUM_BEVANDE] = {[CAFFE] = 10, [CAPPUCCINO] = 5, [TE] = 0, [CIOCCOLATA] = 3};
    int credito = 0;
    char comando = ' ';
    int valore;
    Bevanda scelta;
    Esito esito;

    while (comando != 'Q') {
        printf("Credito %d.%02d euro. Comando (M centesimi, B 1-4, R, Q): ", credito / 100,
               credito % 100);
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'M' || comando == 'B') {
            if (scanf("%d", &valore) != 1) {
                comando = 'Q';
            } else if (comando == 'M') {
                if (moneta_valida(valore)) {
                    credito = credito + valore;
                } else {
                    printf("  Moneta rifiutata.\n");
                }
            } else if (valore < 1 || valore > NUM_BEVANDE) {
                printf("  Scelta non valida.\n");
            } else {
                scelta = valore - 1;
                esito = eroga(scelta, &credito, scorte);
                printf("  %s (%d.%02d euro): %s\n", nome(scelta), prezzo(scelta) / 100,
                       prezzo(scelta) % 100, messaggio(esito));
            }
        } else if (comando == 'R') {
            printf("  Resto: %d.%02d euro\n", credito / 100, credito % 100);
            credito = 0;
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}

/* Prezzo in centesimi. */
int prezzo(Bevanda b)
{
    int centesimi = 0;

    switch (b) {
    case CAFFE:
        centesimi = 50;
        break;
    case CAPPUCCINO:
        centesimi = 70;
        break;
    case TE:
        centesimi = 60;
        break;
    case CIOCCOLATA:
        centesimi = 80;
        break;
    case NUM_BEVANDE:
        break;
    }
    return centesimi;
}

const char *nome(Bevanda b)
{
    const char *testo = "";

    switch (b) {
    case CAFFE:
        testo = "caffe'";
        break;
    case CAPPUCCINO:
        testo = "cappuccino";
        break;
    case TE:
        testo = "te'";
        break;
    case CIOCCOLATA:
        testo = "cioccolata";
        break;
    case NUM_BEVANDE:
        break;
    }
    return testo;
}

Esito eroga(Bevanda b, int *credito, int scorte[])
{
    Esito esito = EROGATA;

    if (scorte[b] == 0) {
        esito = ESAURITA;
    } else if (*credito < prezzo(b)) {
        esito = CREDITO_INSUFFICIENTE;
    } else {
        *credito = *credito - prezzo(b);
        scorte[b]--;
    }
    return esito;
}

const char *messaggio(Esito e)
{
    const char *testo = "";

    switch (e) {
    case EROGATA:
        testo = "erogata, buona pausa";
        break;
    case CREDITO_INSUFFICIENTE:
        testo = "credito insufficiente";
        break;
    case ESAURITA:
        testo = "esaurita";
        break;
    }
    return testo;
}

int moneta_valida(int centesimi)
{
    return centesimi == 5 || centesimi == 10 || centesimi == 20 || centesimi == 50 ||
           centesimi == 100 || centesimi == 200;
}
