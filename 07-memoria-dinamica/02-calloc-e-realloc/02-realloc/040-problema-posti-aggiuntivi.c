/*
 * 040-problema-posti-aggiuntivi.c
 *
 * Il corso di fotografia: la segreteria aggiunge o toglie posti
 *
 * Il corso pomeridiano parte con un certo numero di posti. Se le
 * richieste sono tante la segreteria ottiene un'aula più grande e
 * aggiunge posti; se l'aula grande non è più disponibile, ne toglie. Il
 * blocco degli iscritti cambia dimensione con realloc:
 *
 *     typedef struct {
 *         char nome[20];
 *         char classe[4];
 *     } Iscritto;
 *
 *     tmp = realloc(iscritti, nuova_capienza * sizeof *iscritti);
 *
 * Il risultato va in un puntatore temporaneo: se realloc fallisce, gli
 * iscritti già presenti restano dove sono e la capienza non cambia. Non
 * si possono togliere posti già occupati: la nuova capienza deve essere
 * almeno il numero di iscritti.
 *
 * Comandi:
 *     I nome classe    iscrive (se c'è posto)
 *     A k              aggiunge k posti
 *     T k              toglie k posti liberi
 *     E                elenco con posti liberi
 *     Q                fine
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POSTI 60

typedef struct {
    char nome[20];
    char classe[4];
} Iscritto;

int cambia_capienza(Iscritto **iscritti, int *capienza, int nuova);

int main(void)
{
    Iscritto *iscritti;
    int capienza;
    int n = 0;
    int k;
    int i;
    char nome[20];
    char classe[8];
    char comando = ' ';

    printf("Posti iniziali (da 1 a %d): ", MAX_POSTI);
    if (scanf("%d", &capienza) != 1 || capienza < 1 || capienza > MAX_POSTI) {
        printf("Numero non valido.\n");
    } else {
        iscritti = malloc(capienza * sizeof *iscritti);
        if (iscritti == NULL) {
            printf("Memoria insufficiente.\n");
        } else {
            while (comando != 'Q') {
                printf("Comando (I, A, T, E, Q): ");
                if (scanf(" %c", &comando) != 1) {
                    comando = 'Q';
                }
                if (comando == 'I') {
                    if (scanf("%19s %7s", nome, classe) != 2 || strlen(classe) > 3) {
                        printf("  Dati non validi.\n");
                    } else if (n == capienza) {
                        printf("  Corso pieno (%d posti): %s in attesa.\n", capienza, nome);
                    } else {
                        strcpy(iscritti[n].nome, nome);
                        strcpy(iscritti[n].classe, classe);
                        n++;
                        printf("  iscrizione di %s (%d/%d)\n", nome, n, capienza);
                    }
                } else if (comando == 'A' || comando == 'T') {
                    if (scanf("%d", &k) != 1 || k < 1) {
                        printf("  Numero non valido.\n");
                    } else if (comando == 'A' && capienza + k > MAX_POSTI) {
                        printf("  Al massimo %d posti.\n", MAX_POSTI);
                    } else if (comando == 'T' && capienza - k < n) {
                        printf("  Posti liberi solo %d: non se ne possono togliere %d.\n",
                               capienza - n, k);
                    } else if (comando == 'T' && capienza - k == 0) {
                        printf("  Il corso deve avere almeno un posto.\n");
                    } else if (!cambia_capienza(&iscritti, &capienza,
                                                comando == 'A' ? capienza + k : capienza - k)) {
                        printf("  Memoria insufficiente: capienza invariata.\n");
                    } else {
                        printf("  Nuova capienza: %d posti (%zu byte)\n", capienza,
                               capienza * sizeof *iscritti);
                    }
                } else if (comando == 'E') {
                    for (i = 0; i < n; i++) {
                        printf("  %2d. %-12s %s\n", i + 1, iscritti[i].nome, iscritti[i].classe);
                    }
                    printf("  posti liberi: %d su %d\n", capienza - n, capienza);
                } else if (comando != 'Q') {
                    printf("  Comando sconosciuto.\n");
                }
                if (comando != 'Q' && comando != 'E') {
                    scanf("%*[^\n]");
                }
            }
            free(iscritti);
        }
    }

    return 0;
}

/*
 * Porta il blocco a nuova posti. Riceve l'indirizzo del puntatore e della
 * capienza per aggiornarli solo se realloc riesce; restituisce 0 se
 * fallisce (il blocco vecchio resta valido).
 */
int cambia_capienza(Iscritto **iscritti, int *capienza, int nuova)
{
    Iscritto *tmp = realloc(*iscritti, nuova * sizeof *tmp);

    if (tmp != NULL) {
        *iscritti = tmp;
        *capienza = nuova;
    }
    return tmp != NULL;
}
