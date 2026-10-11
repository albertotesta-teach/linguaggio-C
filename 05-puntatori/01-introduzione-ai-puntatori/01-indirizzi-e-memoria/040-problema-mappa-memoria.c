/*
 * 040-problema-mappa-memoria.c
 *
 * La mappa della memoria di una scheda studente
 *
 * Il programma di gestione della segreteria tiene in memoria la scheda di
 * uno studente: matricola, età, sezione, media e i voti dell'ultimo
 * periodo. Per capire quanta memoria serve e come è organizzata, lo
 * sviluppatore vuole una "mappa": per ogni dato il tipo, l'indirizzo e i
 * byte occupati, più il totale.
 *
 * Osservazioni che la mappa rende evidenti:
 *   - ogni variabile ha un indirizzo diverso;
 *   - l'array voti[] è un unico blocco: i suoi elementi sono consecutivi;
 *   - il totale delle dimensioni dice quanta memoria servirebbe per 1000
 *     schede uguali.
 *
 * Gli indirizzi cambiano a ogni esecuzione.
 */

#include <stdio.h>

#define VOTI    6
#define SCHEDE  1000

int main(void)
{
    long matricola = 2026001;
    int eta = 16;
    char sezione = 'C';
    double media = 7.4;
    int voti[VOTI] = {7, 8, 6, 8, 7, 8};
    char nome[20] = "Giulia Ferri";
    size_t totale;
    int k;

    printf("=== MAPPA DELLA MEMORIA: %s ===\n", nome);
    printf("  %-12s %-9s %-16s %s\n", "Dato", "Tipo", "Indirizzo", "Byte");
    printf("  %-12s %-9s %-16p %zu\n", "matricola", "long", (void *) &matricola, sizeof(matricola));
    printf("  %-12s %-9s %-16p %zu\n", "eta", "int", (void *) &eta, sizeof(eta));
    printf("  %-12s %-9s %-16p %zu\n", "sezione", "char", (void *) &sezione, sizeof(sezione));
    printf("  %-12s %-9s %-16p %zu\n", "media", "double", (void *) &media, sizeof(media));
    printf("  %-12s %-9s %-16p %zu\n", "nome", "char[20]", (void *) &nome[0], sizeof(nome));
    printf("  %-12s %-9s %-16p %zu\n", "voti", "int[6]", (void *) &voti[0], sizeof(voti));

    printf("\nDettaglio dell'array voti (elementi consecutivi):\n");
    for (k = 0; k < VOTI; k++) {
        printf("    voti[%d] = %d  %p\n", k, voti[k], (void *) &voti[k]);
    }

    totale = sizeof(matricola) + sizeof(eta) + sizeof(sezione) + sizeof(media)
           + sizeof(nome) + sizeof(voti);
    printf("\nByte occupati da una scheda: %zu\n", totale);
    printf("Per %d schede servirebbero circa %zu byte (%.1f KB)\n",
           SCHEDE, totale * SCHEDE, totale * SCHEDE / 1024.0);

    return 0;
}
