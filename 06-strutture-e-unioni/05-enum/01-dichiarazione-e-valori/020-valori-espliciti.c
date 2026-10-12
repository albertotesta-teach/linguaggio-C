/*
 * 020-valori-espliciti.c
 *
 * Scegliere i valori delle costanti
 *
 * A una costante si può dare un valore con =. Le costanti successive
 * continuano a contare da lì:
 *
 *     typedef enum { GENNAIO = 1, FEBBRAIO, MARZO, ... } Mese;
 *         FEBBRAIO vale 2, MARZO 3, ..., DICEMBRE 12
 *
 *     typedef enum { BASSA = 1, MEDIA, ALTA, URGENTE = 10 } Priorita;
 *         MEDIA 2, ALTA 3, URGENTE 10
 *
 * I valori possono essere qualsiasi intero, anche lontani tra loro: i
 * codici di risposta di un server web sono 200, 404, 500. Due costanti
 * possono anche avere lo stesso valore (un sinonimo):
 *
 *     typedef enum { OK = 200, NON_TROVATO = 404, ERRORE_SERVER = 500,
 *                    SUCCESSO = OK } Risposta;
 *
 * Con valori scelti a mano il numero ha un significato fuori dal
 * programma: GENNAIO = 1 coincide con il mese scritto in una data,
 * NON_TROVATO = 404 con il codice che il browser riceve.
 *
 * Esempio: tre enum con valori espliciti e i loro numeri.
 */

#include <stdio.h>

typedef enum {
    GENNAIO = 1, FEBBRAIO, MARZO, APRILE, MAGGIO, GIUGNO,
    LUGLIO, AGOSTO, SETTEMBRE, OTTOBRE, NOVEMBRE, DICEMBRE
} Mese;

typedef enum {
    BASSA = 1, MEDIA, ALTA, URGENTE = 10
} Priorita;

typedef enum {
    OK = 200, NON_TROVATO = 404, ERRORE_SERVER = 500, SUCCESSO = OK
} Risposta;

int main(void)
{
    Mese inizio_scuola = SETTEMBRE;
    Priorita guasto = URGENTE;
    Risposta pagina = NON_TROVATO;

    printf("GENNAIO = %d, SETTEMBRE = %d, DICEMBRE = %d\n", GENNAIO, SETTEMBRE, DICEMBRE);
    printf("La scuola inizia il 15/%02d\n", inizio_scuola);

    printf("\nBASSA = %d, MEDIA = %d, ALTA = %d, URGENTE = %d\n", BASSA, MEDIA, ALTA, URGENTE);
    printf("Il guasto del proiettore ha priorita' %d: %s\n", guasto,
           guasto > ALTA ? "intervento immediato" : "in coda");

    printf("\nOK = %d, NON_TROVATO = %d, ERRORE_SERVER = %d, SUCCESSO = %d\n", OK, NON_TROVATO,
           ERRORE_SERVER, SUCCESSO);
    printf("Risposta del registro elettronico: %d (%s)\n", pagina,
           pagina == SUCCESSO ? "pagina trovata" : "errore");

    return 0;
}
