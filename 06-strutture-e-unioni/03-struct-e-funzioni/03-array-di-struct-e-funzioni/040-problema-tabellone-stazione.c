/*
 * 040-problema-tabellone-stazione.c
 *
 * Stazione di Alessandria: il tabellone delle partenze
 *
 * Il tabellone mostra le partenze della mattina. Ogni treno ha numero,
 * destinazione, orario previsto (in minuti dalla mezzanotte), ritardo e
 * binario; un treno soppresso ha ritardo -1.
 *
 *     typedef struct {
 *         char numero[8];
 *         char destinazione[16];
 *         int partenza;            minuti dalla mezzanotte
 *         int ritardo;             -1 = soppresso
 *         int binario;
 *     } Partenza;
 *
 * Le funzioni lavorano sull'array:
 *     void stampa_tabellone(const Partenza t[], int n);
 *     const Partenza *prossima(const Partenza t[], int n, int ora, const char *dest);
 *     int registra_ritardo(Partenza t[], int n, const char *numero, int minuti);
 *
 * prossima restituisce il puntatore al primo treno per quella destinazione
 * che parte (con il ritardo) dall'ora indicata in poi, o NULL.
 * registra_ritardo modifica l'elemento giusto dell'array e restituisce 0
 * se il treno non esiste.
 *
 * Comandi: R numero minuti, S numero (soppresso), P hh:mm destinazione,
 * T (tabellone), Q.
 */

#include <stdio.h>
#include <string.h>

#define TRENI 6

typedef struct {
    char numero[8];
    char destinazione[16];
    int partenza;
    int ritardo;
    int binario;
} Partenza;

void stampa_tabellone(const Partenza t[], int n);
const Partenza *prossima(const Partenza t[], int n, int ora, const char *dest);
int registra_ritardo(Partenza t[], int n, const char *numero, int minuti);
void stampa_ora(int minuti);

int main(void)
{
    Partenza tabellone[TRENI] = {
        {"R10220", "Genova", 7 * 60 + 5, 0, 2},
        {"RV2132", "Torino", 7 * 60 + 12, 0, 1},
        {"R10404", "Pavia", 7 * 60 + 20, 0, 4},
        {"R10222", "Genova", 7 * 60 + 35, 0, 2},
        {"FR9512", "Milano", 7 * 60 + 41, 0, 3},
        {"RV2134", "Torino", 8 * 60 + 12, 0, 1}
    };
    const Partenza *treno;
    char comando = ' ';
    char numero[8];
    char destinazione[16];
    int minuti;
    int ore;

    while (comando != 'Q') {
        printf("Comando (R numero min, S numero, P hh:mm destinazione, T, Q): ");
        if (scanf(" %c", &comando) != 1) {
            comando = 'Q';
        }
        if (comando == 'R' || comando == 'S') {
            minuti = -1;
            if (scanf("%7s", numero) != 1 || (comando == 'R' && scanf("%d", &minuti) != 1)) {
                comando = 'Q';
            } else if (comando == 'R' && minuti < 0) {
                printf("  Ritardo non valido.\n");
            } else if (registra_ritardo(tabellone, TRENI, numero, minuti)) {
                printf("  %s aggiornato.\n", numero);
            } else {
                printf("  Treno %s non in tabellone.\n", numero);
            }
        } else if (comando == 'P') {
            if (scanf("%d:%d %15s", &ore, &minuti, destinazione) != 3) {
                comando = 'Q';
            } else {
                treno = prossima(tabellone, TRENI, ore * 60 + minuti, destinazione);
                if (treno == NULL) {
                    printf("  Nessun treno per %s.\n", destinazione);
                } else {
                    printf("  Prossimo per %s: %s, binario %d, parte alle ", destinazione,
                           treno->numero, treno->binario);
                    stampa_ora(treno->partenza + treno->ritardo);
                    printf("\n");
                }
            }
        } else if (comando == 'T') {
            stampa_tabellone(tabellone, TRENI);
        } else if (comando != 'Q') {
            printf("  Comando sconosciuto.\n");
        }
    }

    return 0;
}

void stampa_tabellone(const Partenza t[], int n)
{
    int i;

    printf("  Ora    Treno   Destinazione  Bin  Stato\n");
    for (i = 0; i < n; i++) {
        printf("  ");
        stampa_ora(t[i].partenza);
        printf("  %-7s %-13s %3d  ", t[i].numero, t[i].destinazione, t[i].binario);
        if (t[i].ritardo == -1) {
            printf("SOPPRESSO\n");
        } else if (t[i].ritardo > 0) {
            printf("ritardo %d'\n", t[i].ritardo);
        } else {
            printf("in orario\n");
        }
    }
}

/* Primo treno non soppresso per dest che parte da "ora" in poi. */
const Partenza *prossima(const Partenza t[], int n, int ora, const char *dest)
{
    const Partenza *trovato = NULL;
    int i = 0;

    while (i < n && trovato == NULL) {
        if (strcmp(t[i].destinazione, dest) == 0 && t[i].ritardo != -1 &&
            t[i].partenza + t[i].ritardo >= ora) {
            trovato = &t[i];
        }
        i++;
    }
    return trovato;
}

int registra_ritardo(Partenza t[], int n, const char *numero, int minuti)
{
    int i = 0;
    int trovato = 0;

    while (i < n && !trovato) {
        if (strcmp(t[i].numero, numero) == 0) {
            t[i].ritardo = minuti;
            trovato = 1;
        }
        i++;
    }
    return trovato;
}

void stampa_ora(int minuti)
{
    printf("%02d:%02d", minuti / 60, minuti % 60);
}
