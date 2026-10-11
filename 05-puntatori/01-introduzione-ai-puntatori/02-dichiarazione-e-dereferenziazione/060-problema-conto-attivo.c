/*
 * 060-problema-conto-attivo.c
 *
 * Operazioni sul conto selezionato di una cassa comune
 *
 * L'associazione dei genitori gestisce quattro "salvadanai" (gita,
 * biblioteca, sport, festa di fine anno), i cui saldi in euro sono in un
 * array. Il tesoriere seleziona un salvadanaio e poi registra versamenti
 * e prelievi su quello.
 *
 * Il puntatore attivo contiene l'indirizzo dell'elemento selezionato:
 *
 *     attivo = &saldi[k];      selezione del salvadanaio k
 *     *attivo += importo;      versamento sul salvadanaio selezionato
 *
 * Comandi (una riga ciascuno):
 *     N k        seleziona il salvadanaio k (da 1 a 4)
 *     V importo  versamento
 *     P importo  prelievo (solo se il saldo è sufficiente)
 *     F          fine e riepilogo
 */

#include <stdio.h>

#define SALVADANAI 4
#define LUNG       12
#define DIM        40

int main(void)
{
    char nomi[SALVADANAI][LUNG] = {"Gita", "Biblioteca", "Sport", "Festa"};
    int saldi[SALVADANAI] = {350, 120, 80, 0};
    int *attivo = NULL;
    int indice_attivo = -1;
    char riga[DIM];
    char comando = ' ';
    int valore;
    int letti;
    int k;

    printf("=== CASSA DEI GENITORI ===\n");
    while (comando != 'F') {
        printf("Comando (N k | V euro | P euro | F): ");
        if (fgets(riga, DIM, stdin) == NULL) {
            comando = 'F';
            letti = 1;
        } else {
            letti = sscanf(riga, " %c %d", &comando, &valore);
        }

        if (letti < 1) {
            printf("  Comando vuoto.\n");
        } else if (comando == 'N') {
            if (letti == 2 && valore >= 1 && valore <= SALVADANAI) {
                attivo = &saldi[valore - 1];
                indice_attivo = valore - 1;
                printf("  Selezionato %s (saldo %d euro)\n", nomi[indice_attivo], *attivo);
            } else {
                printf("  Numero di salvadanaio non valido.\n");
            }
        } else if (comando == 'V' || comando == 'P') {
            if (attivo == NULL) {
                printf("  Nessun salvadanaio selezionato.\n");
            } else if (letti < 2 || valore <= 0) {
                printf("  Importo non valido.\n");
            } else if (comando == 'P' && valore > *attivo) {
                printf("  Saldo insufficiente in %s: %d euro.\n", nomi[indice_attivo], *attivo);
            } else {
                if (comando == 'V') {
                    *attivo = *attivo + valore;
                } else {
                    *attivo = *attivo - valore;
                }
                printf("  %s: nuovo saldo %d euro\n", nomi[indice_attivo], *attivo);
            }
        } else if (comando != 'F') {
            printf("  Comando sconosciuto.\n");
        }
    }

    printf("\n=== RIEPILOGO ===\n");
    for (k = 0; k < SALVADANAI; k++) {
        printf("  %-11s %5d euro%s\n", nomi[k], saldi[k],
               &saldi[k] == attivo ? "   <- ultimo selezionato" : "");
    }

    return 0;
}
