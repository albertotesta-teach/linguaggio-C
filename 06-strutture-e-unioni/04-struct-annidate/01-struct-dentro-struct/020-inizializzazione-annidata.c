/*
 * 020-inizializzazione-annidata.c
 *
 * Inizializzare una struct che contiene altre struct
 *
 * Nella lista tra graffe la struct interna ha le sue graffe:
 *
 *     Iscritto a = {"Rossi Elena", {12, 3, 2010}, {15, 9, 2025}};
 *
 * Con il nome dei campi si può indicare la struct interna intera o
 * arrivare direttamente a un suo campo:
 *
 *     Iscritto b = {.nome = "Costa Marta",
 *                   .nascita = {.giorno = 5, .mese = 7, .anno = 2010}};
 *     Iscritto c = {.nome = "Villa Sara", .nascita.anno = 2009};
 *
 * Le regole sono quelle già viste: i campi non indicati valgono zero,
 * anche dentro la struct interna, e {0} azzera tutto (qui l'ultimo posto
 * dell'elenco riceve una copia di un Iscritto azzerato). Si possono omettere
 * le graffe interne ({"Rossi Elena", 12, 3, 2010, ...}), ma il
 * compilatore avverte (-Wmissing-braces) e la lista diventa difficile da
 * leggere: in questo corso le graffe interne si scrivono sempre.
 *
 * Esempio: gli iscritti al corso pomeridiano di robotica. Una data con
 * anno zero significa "non ancora iscritto".
 */

#include <stdio.h>

#define ISCRITTI 4

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char nome[20];
    Data nascita;
    Data iscrizione;
} Iscritto;

int main(void)
{
    Iscritto corso[ISCRITTI] = {
        {"Rossi Elena", {12, 3, 2010}, {15, 9, 2025}},
        {.nome = "Costa Marta", .nascita = {.giorno = 5, .mese = 7, .anno = 2010}},
        {.nome = "Villa Sara", .nascita.anno = 2009, .iscrizione = {2, 10, 2025}}
    };
    Iscritto vuoto = {0};
    int i;

    corso[ISCRITTI - 1] = vuoto;

    printf("Corso di robotica\n");
    for (i = 0; i < ISCRITTI; i++) {
        if (corso[i].nome[0] == '\0') {
            printf("  (posto libero)\n");
        } else {
            printf("  %-12s ", corso[i].nome);
            if (corso[i].nascita.giorno == 0) {
                printf("nascita --/--/%d   ", corso[i].nascita.anno);
            } else {
                printf("nascita %02d/%02d/%d   ", corso[i].nascita.giorno, corso[i].nascita.mese,
                       corso[i].nascita.anno);
            }
            if (corso[i].iscrizione.anno == 0) {
                printf("iscrizione: non ancora\n");
            } else {
                printf("iscrizione %02d/%02d/%d\n", corso[i].iscrizione.giorno,
                       corso[i].iscrizione.mese, corso[i].iscrizione.anno);
            }
        }
    }

    return 0;
}
