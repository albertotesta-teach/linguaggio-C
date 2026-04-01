/*
 * 050-problema-biglietto-da-visita.c
 *
 * Biglietto da visita testuale
 *
 * Il programma chiede all'utente di inserire alcuni dati numerici
 * (numero di telefono cifra per cifra, anno di fondazione, numero civico)
 * e stampa un biglietto da visita formattato con bordo ASCII.
 * Non si usano stringhe né array: tutti i dati sono interi o caratteri
 * singoli, nel rispetto dei vincoli del capitolo 01-introduzione.
 *
 * Nota didattica: i nomi (nome, via, città) sono rappresentati come
 * sequenze di chiamate printf con testo fisso, per mostrare come la
 * formattazione dell'output possa essere usata in modo creativo
 * anche senza le stringhe.
 */

#include <stdio.h>

#define LARGHEZZA 40   /* larghezza interna del biglietto in caratteri */

int main(void)
{
    /* dati numerici inseriti dall'utente */
    int prefisso;        /* es. 02, 06, 011 */
    int numero;          /* parte principale del numero di telefono */
    int anno_fondazione;
    int numero_civico;
    int cap;

    /* ── input ─────────────────────────────────────────────────────────── */
    printf("=== Creazione biglietto da visita ===\n\n");

    printf("Prefisso telefonico (es. 02): ");
    scanf("%d", &prefisso);

    printf("Numero di telefono:           ");
    scanf("%d", &numero);

    printf("Anno di fondazione azienda:   ");
    scanf("%d", &anno_fondazione);

    printf("Numero civico sede:           ");
    scanf("%d", &numero_civico);

    printf("CAP sede:                     ");
    scanf("%d", &cap);

    /* ── output: biglietto formattato ───────────────────────────────────── */
    printf("\n");
    printf("+--------------------------------------+\n");
    printf("|                                      |\n");
    printf("|   MARIO ROSSI                        |\n");
    printf("|   Sviluppatore Software              |\n");
    printf("|                                      |\n");
    printf("|   ACME S.r.l.  (dal %d)          |\n", anno_fondazione);
    printf("|   Via Roma, %d                      |\n", numero_civico);
    printf("|   %d  Milano                     |\n", cap);
    printf("|                                      |\n");
    printf("|   Tel: %03d / %d          |\n", prefisso, numero);
    printf("|                                      |\n");
    printf("+--------------------------------------+\n");

    return 0;
}
