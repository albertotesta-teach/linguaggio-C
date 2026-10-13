/*
 * 020-doppio-free-e-puntatore-pendente.c
 *
 * Dopo free: il puntatore pendente e il doppio free
 *
 * free restituisce il blocco ma non cambia il puntatore: p contiene
 * ancora lo stesso indirizzo, che però non è più del programma. p è un
 * puntatore pendente (dangling pointer). Due errori tipici:
 *
 *     free(p);
 *     printf("%s", p->aula);      uso dopo free: legge memoria non sua
 *     free(p);                    doppio free: il programma può bloccarsi
 *
 * Il comportamento non è definito: a volte sembra funzionare, a volte il
 * programma termina con un errore, a volte si rompe più avanti in un
 * punto che non c'entra. Per questo qui i due errori compaiono solo nel
 * commento.
 *
 * La difesa più semplice: subito dopo free si mette il puntatore a NULL.
 *
 *     free(p);
 *     p = NULL;
 *
 * Da quel momento un controllo p != NULL dice se il blocco c'è ancora,
 * e una seconda free(p) diventa free(NULL), che per lo standard non fa
 * nulla. La funzione libera(&p) fa le due cose insieme: riceve
 * l'indirizzo del puntatore (un puntatore a puntatore) per poterlo
 * azzerare.
 *
 * Attenzione alle copie: se q = p, dopo libera(&p) q punta ancora al
 * blocco liberato. Ogni blocco deve avere un solo puntatore
 * "proprietario", quello che si usa per liberarlo.
 *
 * Esempio: la prenotazione di un'aula, annullata due volte per errore.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char aula[12];
    char docente[20];
    int ora;
} Prenotazione;

void libera(Prenotazione **p);
void annulla(Prenotazione **p);

int main(void)
{
    Prenotazione *prenotazione = malloc(sizeof *prenotazione);

    if (prenotazione == NULL) {
        printf("Memoria insufficiente.\n");
    } else {
        strcpy(prenotazione->aula, "LAB2");
        strcpy(prenotazione->docente, "prof. Galli");
        prenotazione->ora = 3;
        printf("Prenotata %s alla %da ora (%s), blocco %p\n", prenotazione->aula,
               prenotazione->ora, prenotazione->docente, (void *) prenotazione);

        annulla(&prenotazione);
        printf("Dopo l'annullamento il puntatore vale %p\n", (void *) prenotazione);
        annulla(&prenotazione);
    }

    return 0;
}

/* free e azzeramento insieme: il chiamante non resta con un indirizzo
   pendente. */
void libera(Prenotazione **p)
{
    free(*p);
    *p = NULL;
}

void annulla(Prenotazione **p)
{
    if (*p == NULL) {
        printf("Nessuna prenotazione da annullare.\n");
    } else {
        printf("Annullata la prenotazione di %s.\n", (*p)->aula);
        libera(p);
    }
}
