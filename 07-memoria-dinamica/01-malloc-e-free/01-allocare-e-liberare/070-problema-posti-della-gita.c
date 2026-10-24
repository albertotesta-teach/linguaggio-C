/*
 * 070-problema-posti-della-gita.c
 *
 * Gita di fine anno: iscrizioni sui posti del pullman
 *
 * Il numero di posti dipende dal pullman prenotato: si legge all'inizio
 * e l'elenco dei partecipanti si alloca con esattamente quei posti.
 *
 *     typedef struct {
 *         char nome[20];
 *         char classe[4];
 *         double versato;
 *         int autorizzazione;        1 se il modulo firmato è consegnato
 *     } Partecipante;
 *
 *     Partecipante *posti = malloc(capienza * sizeof *posti);
 *
 * I partecipanti occupano le posizioni da 0 a iscritti - 1 (come un array
 * a tappo, ma con la capienza scelta durante l'esecuzione).
 *
 * Comandi:
 *     I nome classe euro   iscrive versando un acconto (fino alla quota)
 *     V posto euro         versamento successivo
 *     A posto              autorizzazione consegnata
 *     E                    elenco con quanto manca e autorizzazione
 *     R                    riepilogo: posti liberi, chi non può partire
 *     Q                    fine
 *
 * La quota della gita è 85 euro. Può partire solo chi ha versato
 * tutta la quota e consegnato l'autorizzazione.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define QUOTA 85.0
#define MAX_POSTI 80

typedef struct {
    char nome[20];
    char classe[4];
    double versato;
    int autorizzazione;
} Partecipante;

void elenco(const Partecipante posti[], int iscritti);
void riepilogo(const Partecipante posti[], int iscritti, int capienza);

int main(void)
{
    Partecipante *posti;
    int capienza;
    int iscritti = 0;
    int posto;
    double euro;
    char nome[20];
    char classe[8];
    char comando = ' ';

    printf("Posti del pullman (da 1 a %d): ", MAX_POSTI);
    if (scanf("%d", &capienza) != 1 || capienza < 1 || capienza > MAX_POSTI) {
        printf("Numero di posti non valido.\n");
    } else {
        posti = malloc(capienza * sizeof *posti);
        if (posti == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            printf("Elenco di %d posti: %zu byte\n", capienza, capienza * sizeof *posti);
            while (comando != 'Q') {
                printf("Comando (I, V, A, E, R, Q): ");
                if (scanf(" %c", &comando) != 1) {
                    comando = 'Q';      /* input terminato: come Q */
                }
                comando = (char) toupper((unsigned char) comando);
                if (comando == 'I') {
                    if (scanf("%19s %7s %lf", nome, classe, &euro) != 3 ||
                        strlen(classe) > 3 || euro < 0 || euro > QUOTA) {
                        printf("  Dati non validi.\n");
                    } else if (iscritti == capienza) {
                        printf("  Pullman pieno: %s non iscritto.\n", nome);
                    } else {
                        strcpy(posti[iscritti].nome, nome);
                        strcpy(posti[iscritti].classe, classe);
                        posti[iscritti].versato = euro;
                        posti[iscritti].autorizzazione = 0;
                        iscritti++;
                        printf("  %s al posto %d\n", nome, iscritti);
                    }
                } else if (comando == 'V') {
                    if (scanf("%d %lf", &posto, &euro) != 2 || posto < 1 || posto > iscritti ||
                        euro <= 0 || posti[posto - 1].versato + euro > QUOTA) {
                        printf("  Versamento non valido.\n");
                    } else {
                        posti[posto - 1].versato = posti[posto - 1].versato + euro;
                        printf("  %s: versati %.2f euro\n", posti[posto - 1].nome,
                               posti[posto - 1].versato);
                    }
                } else if (comando == 'A') {
                    if (scanf("%d", &posto) != 1 || posto < 1 || posto > iscritti) {
                        printf("  Posto non valido.\n");
                    } else {
                        posti[posto - 1].autorizzazione = 1;
                        printf("  Autorizzazione di %s consegnata.\n", posti[posto - 1].nome);
                    }
                } else if (comando == 'E') {
                    elenco(posti, iscritti);
                } else if (comando == 'R') {
                    riepilogo(posti, iscritti, capienza);
                } else if (comando != 'Q') {
                    printf("  Comando sconosciuto.\n");
                }
                if (comando != 'Q') {
                    scanf("%*[^\n]");  /* un comando per riga */
                }
            }
            free(posti);
        }
    }

    return 0;
}

void elenco(const Partecipante posti[], int iscritti)
{
    int i;

    for (i = 0; i < iscritti; i++) {
        printf("  %2d %-12s %-3s manca %6.2f  %s\n", i + 1, posti[i].nome, posti[i].classe,
               QUOTA - posti[i].versato,
               posti[i].autorizzazione ? "autorizzato" : "senza autorizzazione");
    }
}

void riepilogo(const Partecipante posti[], int iscritti, int capienza)
{
    int i;
    int pronti = 0;
    double raccolto = 0;

    printf("  Posti occupati %d su %d, liberi %d\n", iscritti, capienza, capienza - iscritti);
    for (i = 0; i < iscritti; i++) {
        raccolto = raccolto + posti[i].versato;
        if (posti[i].versato > QUOTA - 0.005 && posti[i].autorizzazione) {
            pronti++;
        } else {
            printf("  non puo' ancora partire: %s\n", posti[i].nome);
        }
    }
    printf("  Pronti a partire: %d, raccolti %.2f euro su %.2f\n", pronti, raccolto,
           iscritti * QUOTA);
}
