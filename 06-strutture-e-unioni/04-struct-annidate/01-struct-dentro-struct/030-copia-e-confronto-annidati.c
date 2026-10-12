/*
 * 030-copia-e-confronto-annidati.c
 *
 * Copiare e confrontare struct che contengono struct
 *
 * L'assegnamento copia TUTTI i campi, anche quelli delle struct interne:
 *
 *     Colloquio spostato = originale;      copia anche giorno e ora
 *
 * Si può assegnare anche solo una parte, se ha lo stesso tipo:
 *
 *     spostato.ora = libero.ora;           copia un Orario intero
 *
 * Il confronto con == resta vietato, a ogni livello: non si può scrivere
 * a == b né a.giorno == b.giorno. Si confrontano i campi semplici,
 * scendendo fino all'ultimo livello:
 *
 *     a.giorno.giorno == b.giorno.giorno && a.giorno.mese == ...
 *
 * Esempio: i colloqui con i genitori. Un colloquio viene spostato in un
 * altro orario; poi si controlla se due colloqui dello stesso docente
 * cadono nello stesso momento.
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    int ore;
    int minuti;
} Orario;

typedef struct {
    char docente[16];
    char famiglia[16];
    Data giorno;
    Orario ora;
} Colloquio;

int main(void)
{
    Colloquio originale = {"prof. Galli", "fam. Ferri", {20, 11, 2025}, {16, 30}};
    Colloquio libero = {"prof. Galli", "", {20, 11, 2025}, {17, 10}};
    Colloquio spostato;
    Colloquio altro = {"prof. Galli", "fam. Riva", {20, 11, 2025}, {17, 10}};
    int stesso_momento;

    spostato = originale;
    spostato.ora = libero.ora;

    printf("Originale: %s, %s, %02d/%02d alle %02d:%02d\n", originale.docente, originale.famiglia,
           originale.giorno.giorno, originale.giorno.mese, originale.ora.ore, originale.ora.minuti);
    printf("Spostato:  %s, %s, %02d/%02d alle %02d:%02d\n", spostato.docente, spostato.famiglia,
           spostato.giorno.giorno, spostato.giorno.mese, spostato.ora.ore, spostato.ora.minuti);
    printf("(l'originale non cambia: la copia e' indipendente)\n");

    /* if (spostato == altro)                 errore di compilazione */
    /* if (spostato.giorno == altro.giorno)   errore anche qui       */
    stesso_momento = strcmp(spostato.docente, altro.docente) == 0 &&
                     spostato.giorno.giorno == altro.giorno.giorno &&
                     spostato.giorno.mese == altro.giorno.mese &&
                     spostato.giorno.anno == altro.giorno.anno &&
                     spostato.ora.ore == altro.ora.ore &&
                     spostato.ora.minuti == altro.ora.minuti;

    printf("\n%s e %s con %s alla stessa ora? %s\n", spostato.famiglia, altro.famiglia,
           spostato.docente, stesso_momento ? "si', conflitto" : "no");

    return 0;
}
