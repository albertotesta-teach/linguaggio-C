/*
 * 070-problema-mesi-e-stagioni.c
 *
 * Calendario delle attività: giorni del mese e stagione
 *
 * Per il calendario delle attività all'aperto il programma legge mese e
 * anno e dice quanti giorni ha il mese e in che stagione cade. Due enum:
 *
 *     typedef enum { GENNAIO = 1, FEBBRAIO, ..., DICEMBRE } Mese;
 *     typedef enum { INVERNO, PRIMAVERA, ESTATE, AUTUNNO,
 *                    NUM_STAGIONI } Stagione;
 *
 * Mese parte da 1, così coincide con il numero scritto dall'utente; per
 * indicizzare la tabella dei nomi dei mesi si usa mese - GENNAIO.
 *
 * Il numero letto è un int: prima si controlla che sia tra GENNAIO e
 * DICEMBRE, poi lo si assegna a una variabile Mese. Un enum non controlla
 * i valori da solo.
 *
 * Stagioni meteorologiche: inverno dicembre-febbraio, primavera
 * marzo-maggio, estate giugno-agosto, autunno settembre-novembre.
 * 0 termina.
 */

#include <stdio.h>

typedef enum {
    GENNAIO = 1, FEBBRAIO, MARZO, APRILE, MAGGIO, GIUGNO,
    LUGLIO, AGOSTO, SETTEMBRE, OTTOBRE, NOVEMBRE, DICEMBRE
} Mese;

typedef enum {
    INVERNO, PRIMAVERA, ESTATE, AUTUNNO, NUM_STAGIONI
} Stagione;

int main(void)
{
    const char *nomi_mesi[12] = {"gennaio", "febbraio", "marzo", "aprile", "maggio", "giugno",
                                 "luglio", "agosto", "settembre", "ottobre", "novembre",
                                 "dicembre"};
    const char *nomi_stagioni[NUM_STAGIONI] = {[INVERNO] = "inverno", [PRIMAVERA] = "primavera",
                                               [ESTATE] = "estate", [AUTUNNO] = "autunno"};
    int numero = 1;
    int anno;
    int giorni;
    Mese mese;
    Stagione stagione;

    while (numero != 0) {
        printf("Mese e anno (0 per finire): ");
        if (scanf("%d", &numero) != 1) {
            numero = 0;
        } else if (numero != 0) {
            if (scanf("%d", &anno) != 1) {
                numero = 0;
            } else if (numero < GENNAIO || numero > DICEMBRE) {
                printf("  %d non e' un mese.\n", numero);
            } else {
                mese = numero;
                if (mese == FEBBRAIO) {
                    giorni = ((anno % 4 == 0 && anno % 100 != 0) || anno % 400 == 0) ? 29 : 28;
                } else if (mese == APRILE || mese == GIUGNO || mese == SETTEMBRE || mese == NOVEMBRE) {
                    giorni = 30;
                } else {
                    giorni = 31;
                }
                if (mese == DICEMBRE || mese <= FEBBRAIO) {
                    stagione = INVERNO;
                } else if (mese <= MAGGIO) {
                    stagione = PRIMAVERA;
                } else if (mese <= AGOSTO) {
                    stagione = ESTATE;
                } else {
                    stagione = AUTUNNO;
                }
                printf("  %s %d: %d giorni, %s\n", nomi_mesi[mese - GENNAIO], anno, giorni,
                       nomi_stagioni[stagione]);
            }
        }
    }

    return 0;
}
