/*
 * 020-funzioni-con-enum.c
 *
 * Funzioni che ricevono e restituiscono un enum
 *
 * Una funzione che decide tra pochi casi può restituire un enum invece
 * di un numero "magico":
 *
 *     int valuta(double media, int insufficienze);     0? 1? 2?
 *     Esito valuta(double media, int insufficienze);    RESPINTO, ...
 *
 * Il prototipo dice al lettore quali risultati sono possibili, e il
 * codice che usa il risultato si legge senza tabelle di conversione:
 *
 *     if (valuta(m, n) == SOSPESO) ...
 *
 * Allo stesso modo una funzione può ricevere un enum come parametro:
 *
 *     const char *descrizione(Esito e);
 *
 * Esempio: lo scrutinio finale. Promosso con media almeno 6 e nessuna
 * insufficienza; giudizio sospeso con al massimo 3 insufficienze e media
 * almeno 5; altrimenti non ammesso.
 */

#include <stdio.h>

#define STUDENTI 5

typedef enum {
    NON_AMMESSO, SOSPESO, PROMOSSO, NUM_ESITI
} Esito;

typedef struct {
    char nome[16];
    double media;
    int insufficienze;
} Scheda;

Esito valuta(double media, int insufficienze);
const char *descrizione(Esito e);

int main(void)
{
    Scheda classe[STUDENTI] = {
        {"Bassi Rita", 7.4, 0},
        {"Corti Ugo", 5.9, 2},
        {"Dini Ada", 8.1, 0},
        {"Elia Gino", 4.8, 5},
        {"Fumo Pia", 6.3, 1}
    };
    int conteggi[NUM_ESITI] = {0};
    Esito esito;
    int i;

    for (i = 0; i < STUDENTI; i++) {
        esito = valuta(classe[i].media, classe[i].insufficienze);
        conteggi[esito]++;
        printf("  %-11s media %.1f, %d insuff.  %s\n", classe[i].nome, classe[i].media,
               classe[i].insufficienze, descrizione(esito));
    }
    printf("Promossi %d, sospesi %d, non ammessi %d\n", conteggi[PROMOSSO], conteggi[SOSPESO],
           conteggi[NON_AMMESSO]);

    return 0;
}

Esito valuta(double media, int insufficienze)
{
    Esito esito = NON_AMMESSO;

    if (insufficienze == 0 && media >= 6) {
        esito = PROMOSSO;
    } else if (insufficienze <= 3 && media >= 5) {
        esito = SOSPESO;
    }
    return esito;
}

const char *descrizione(Esito e)
{
    const char *testo = "";

    switch (e) {
    case PROMOSSO:
        testo = "promosso/a";
        break;
    case SOSPESO:
        testo = "giudizio sospeso";
        break;
    case NON_AMMESSO:
        testo = "non ammesso/a";
        break;
    case NUM_ESITI:             /* non è un esito: il case evita l'avviso */
        testo = "?";
        break;
    }
    return testo;
}
